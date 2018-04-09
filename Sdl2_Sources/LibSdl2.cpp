/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 08/04/18 
*/

#include <memory>
#include "LibSdl2.hpp"

sdl2::LibSdl2::LibSdl2(unsigned int width, unsigned int height, unsigned int scale)
	: ALib(width, height, scale, 70, "Lib Sdl2"), _textureSave()
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	if (TTF_Init() == -1)
		throw std::runtime_error(TTF_GetError());
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
		throw std::runtime_error(IMG_GetError());
	_window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width *  scale, height * scale, SDL_WINDOW_RESIZABLE);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}

sdl2::LibSdl2::~LibSdl2()
{
	SDL_DestroyWindow(_window);
	TTF_Quit();
	IMG_Quit();
	for (auto &elemMap : _textureSave) {
		SDL_DestroyTexture(elemMap.second);
	}
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
}

bool sdl2::LibSdl2::display()
{
	SDL_Delay(16);
	SDL_RenderPresent(_renderer);
	return true;
}

bool sdl2::LibSdl2::resize(int width, int height)
{
	SDL_SetWindowSize(_window, width * _scale, height * _scale);
	_height = static_cast<unsigned int>(height);
	_width = static_cast<unsigned int>(width);
	return true;
}

bool sdl2::LibSdl2::clear()
{
	SDL_RenderPresent(_renderer);
	SDL_SetRenderDrawColor(_renderer, _backColor.argb.red, _backColor.argb.green, _backColor.argb.blue, _backColor.argb.alpha);
	SDL_RenderClear(_renderer);
	if (_spriteBackground) {
		SDL_Rect square = {0, 0, static_cast<int>(_width * _scale), static_cast<int>( _height * _scale)};
		SDL_RenderCopy(_renderer, _background, nullptr, &square);
	}
	return true;
}

grph::KeyEvent sdl2::LibSdl2::getKeyEvent()
{
	grph::KeyEvent event = {grph::NOTHING, 0};
	SDL_Event SdlEvent;

	SDL_PollEvent(&SdlEvent);
	if(SdlEvent.key.state != SDL_PRESSED)
		return event;
	event.key = static_cast<char>(SdlEvent.key.keysym.sym);
	if (sdl2::KeyEventMap.find(SdlEvent.key.keysym.sym) != sdl2::KeyEventMap.end()) {
		event.type = sdl2::KeyEventMap.at(SdlEvent.key.keysym.sym);
		return event;
	}
	if (SdlEvent.type == SDL_WINDOWEVENT_CLOSE || SdlEvent.type == SDL_QUIT)
		event.type = grph::KeyType::QUIT;
	event.type =grph::TEXT;
	return (event);
}

bool sdl2::LibSdl2::drawSprite(int x1, int y1, int w, int h, grph::ISprite const& sprite)
{
	if (sprite.getPath().empty())
		drawSquare(x1, y1, w, h, _scale, sprite.getSubColor());
	else
		drawTexture(x1, y1, w, h, _scale, sprite.getPath());
	return true;
}

void sdl2::LibSdl2::drawSquare(int x1, int y1, int w, int h, int scale, grph::ARGB const& C)
{
	SDL_Rect square = {x1 * scale, y1 * scale, w * scale, h * scale};

	SDL_SetRenderDrawColor(_renderer, C.argb.red, C.argb.green, C.argb.blue, C.argb.alpha);
	SDL_RenderFillRect(_renderer, &square);
}

bool sdl2::LibSdl2::setBackGround(grph::ISprite const& sprite)
{
	if (not sprite.getPath().empty()) {
		_background = manageTexture(sprite.getPath());
		_spriteBackground = true;
	}
	else {
		_spriteBackground = false;
		_backColor.argb.red = sprite.getRed();
		_backColor.argb.green = sprite.getGreen();
		_backColor.argb.blue = sprite.getBlue();
		_backColor.argb.alpha = sprite.getAlpha();
	}
	return true;
}

bool sdl2::LibSdl2::drawText(int x, int y, unsigned int fontSize, std::string const& text, grph::ARGB const& color)
{
	SDL_Rect square = {x * static_cast<int>(_scale), y * static_cast<int>(_height), 1, 1};
	TTF_Font* font = TTF_OpenFont("fonts/arial.ttf", fontSize + _scale);
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(),
		{color.argb.red, color.argb.green, color.argb.blue, color.argb.alpha});
	SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);

	SDL_QueryTexture(texture, nullptr, nullptr, &square.w, &square.h);
	SDL_RenderCopy(_renderer, texture, nullptr, &square);
	TTF_CloseFont(font);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	return true;
}

void sdl2::LibSdl2::drawTexture(int x1, int y1, int w, int h, int scale, std::string const& path)
{
	SDL_Rect square = {x1 * scale, y1 * scale, w  * scale + (scale /4), h * scale + (scale /4)};
	auto texture = manageTexture(path);
	SDL_RenderCopy(_renderer, texture, nullptr, &square);
}

SDL_Texture* sdl2::LibSdl2::manageTexture(std::string const& path)
{
	if (_textureSave.find(path) != _textureSave.end())
		return _textureSave.at(path);
	auto surface = IMG_Load(path.c_str());
	if (!surface)
		throw std::runtime_error(SDL_GetError());
	auto texture = SDL_CreateTextureFromSurface(_renderer, surface);
	_textureSave[path] = texture;
	SDL_FreeSurface(surface);
	return _textureSave.at(path);
}

extern "C"
{
	std::unique_ptr<grph::ILib> create(int width, int height)
	{
		return std::make_unique<sdl2::LibSdl2>(width, height, 20);
	}

	std::string name()
	{
		return LIBSDL2_NAME;
	}
}