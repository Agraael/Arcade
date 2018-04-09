/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 08/04/18 
*/

#ifndef LIBCACA_LIBSDL2_HPP
#define LIBCACA_LIBSDL2_HPP

#include <ALib.hpp>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace sdl2
{
	const std::map<int, grph::KeyType> KeyEventMap = {
		{SDLK_ESCAPE, grph::QUIT},
		{SDLK_UP, grph::UP},
		{SDLK_DOWN, grph::DOWN},
		{SDLK_LEFT, grph::LEFT},
		{SDLK_RIGHT, grph::RIGHT},
		{SDLK_BACKSPACE, grph::BACKSPACE},
		{SDLK_TAB, grph::TAB},
		{SDLK_RETURN, grph::ENTER},
		{233, grph::PREV_LIB},
		{34, grph::NEXT_LIB},
		{39, grph::PREV_GAME},
		{40, grph::NEXT_GAME},
		{SDLK_2, grph::PREV_LIB},
		{SDLK_3, grph::NEXT_LIB},
		{SDLK_4, grph::PREV_GAME},
		{SDLK_5, grph::NEXT_GAME},
	};

	#define LIBSDL2_NAME "SDL2"

	class LibSdl2
	: public grph::ALib
	{
	public:
		LibSdl2(unsigned int widht, unsigned int height, unsigned int scale);
		LibSdl2(LibSdl2 const&) = delete;
		~LibSdl2() final;
		LibSdl2& operator=(LibSdl2 const&) = delete;
		bool display() final;
		bool clear() final;
		bool resize(int width, int height) final;
		bool drawSprite(int x1, int y1, int x2, int y2, grph::ISprite const& sprite) final;
		bool setBackGround(grph::ISprite const& sprite) final;
		bool drawText(int x, int y, unsigned int fontSize, std::string const& text, grph::ARGB const& color) final;
		grph::KeyEvent getKeyEvent() final;
	private:
		void drawSquare(int x1, int y1, int x2, int y2, int scale, grph::ARGB const& C);
		void drawTexture(int x1, int y1, int x2, int y2, int scale, std::string const& path);
		SDL_Texture* manageTexture(std::string const& path);
		SDL_Window* _window = nullptr;
		SDL_Renderer* _renderer = nullptr;
		std::map<std::string, SDL_Texture*> _textureSave;
		SDL_Texture* _background = nullptr;
		grph::ARGB _backColor = {0x00000000};
		bool _spriteBackground = false;
	};
}

#endif //LIBCACA_LIBSDL2_HPP
