/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 06/04/18 
*/

#include <iostream>
#include "LibSfml.hpp"

caca::LibSfml::LibSfml(unsigned int widht, unsigned int height, unsigned int scale)
	: ALib(widht, height, scale, 70, "Lib Sfml"), _textureSave(), _background()
{
	_window = new sf::RenderWindow(sf::VideoMode(_width * scale, _height * scale),
		"Arcade", sf::Style::Default, sf::ContextSettings());
	_window->setFramerateLimit(60);
	_window->setKeyRepeatEnabled(true);
}

caca::LibSfml::~LibSfml()
{
	_window->close();
	delete _window;
}

bool caca::LibSfml::display()
{
	_window->display();
	return true;
}

bool caca::LibSfml::clear()
{
	_window->clear();
	if (_spriteBackground) {
		sf::Sprite sprite;
		float sizeX = static_cast<float>(_background->getSize().x);
		float sizeY = static_cast<float>(_background->getSize().y);
		sprite.setTexture(*_background);
		sprite.setScale((1 / (sizeX / static_cast<float>(_scale *_width))), (1 / (sizeY / static_cast<float>(_scale * _height))));
		sprite.setPosition(0, 0);
		_window->draw(sprite);
	}
	else {
		sf::RectangleShape square(sf::Vector2f(static_cast<float>(_width * _scale),static_cast<float>(_height * _scale)));
		sf::Color color(_backColor.argb.red, _backColor.argb.green, _backColor.argb.blue);;
		square.setPosition(0, 0);
		square.setFillColor(color);
		_window->draw(square);
	}
	return true;
}

bool caca::LibSfml::resize(int width, int height)
{
	_window->close();
	delete _window;
	_width = static_cast<unsigned int>(width);
	_height = static_cast<unsigned int>(height);
	_window = new sf::RenderWindow(sf::VideoMode(_width * _scale, _height * _scale),
		"Arcade", sf::Style::Default, sf::ContextSettings());
	_window->setFramerateLimit(60);
	_window->setKeyRepeatEnabled(false);
	return true;
}

bool caca::LibSfml::drawSprite(int x1, int y1, int w, int h, grph::ISprite const& sprite)
{
	auto f_x1 = static_cast<float>(x1 * _scale);
	auto f_y1 = static_cast<float>(y1 * _scale);
	auto f_w = static_cast<float>(w * _scale);
	auto f_h = static_cast<float>(h * _scale);
	auto f_scale = static_cast<float>(_scale);

	if (sprite.getPath().empty())
		drawSquare(f_x1, f_y1, f_w, f_h, f_scale, sprite.getSubColor());
	else
		drawTexture(f_x1, f_y1, f_w, f_h, f_scale, sprite.getPath());
	return true;
}

std::shared_ptr<sf::Texture>& caca::LibSfml::manageTexture(std::string const& path)
{
	if (_textureSave.find(path) != _textureSave.end())
		return _textureSave.at(path);
	_textureSave[path] = std::make_shared<sf::Texture>();
	if (not _textureSave[path]->loadFromFile(path)) {
		throw;
	}
	return _textureSave.at(path);

}

void caca::LibSfml::drawTexture(float x1, float y1, float w, float h, float scale, std::string const& path)
{
	std::shared_ptr<sf::Texture> texture;
	sf::Sprite sprite;

	texture = manageTexture(path);
	float sizeX = static_cast<float>(texture->getSize().x);
	float sizeY = static_cast<float>(texture->getSize().y);
	sprite.setTexture(*texture);
	sprite.setScale(1 / (sizeX / (w + (scale / 4))),
		1 / (sizeY / (h  + (scale / 4))));
	sprite.setPosition(x1, y1);
	_window->draw(sprite);
}

void caca::LibSfml::drawSquare(float x1, float y1, float w, float h, float scale, grph::ARGB const& C)
{
	(void)(scale);
	sf::RectangleShape square(sf::Vector2f(w, h));
	sf::Color color(C.argb.red, C.argb.green, C.argb.blue);;

	square.setPosition(x1, y1);
	square.setFillColor(color);
	_window->draw(square);
}

bool caca::LibSfml::setBackGround(grph::ISprite const& sprite)
{
	if (not sprite.getPath().empty()) {
		_spriteBackground = true;
		_background = manageTexture(sprite.getPath());
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

bool caca::LibSfml::drawText(int x, int y, unsigned int fontSize, std::string const& text, grph::ARGB const& color)
{
	sf::Font font;
	sf::Text texte;
	sf::Color C(color.argb.red, color.argb.green, color.argb.blue);;

	x = x * this->_scale;
	y = y * this->_scale;
	font.loadFromFile("fonts/arial.ttf");
	texte.setFont(font);
	texte.setString(text);
	texte.setCharacterSize(_scale + fontSize);
	texte.setFillColor(C);
	texte.setPosition(static_cast<float>(x), static_cast<float>(y));
	_window->draw(texte);
	return true;
}

grph::KeyEvent caca::LibSfml::getKeyEvent()
{
	grph::KeyEvent event = {grph::NOTHING, 0};
	sf::Event sfEvent;

	_window->pollEvent(sfEvent);
	for (auto& item : KeyEventVec) {
		if (sf::Keyboard::isKeyPressed(item.first)) {
			event.type = item.second;
			return event;
		}
	}
	event.key = static_cast<char>(sfEvent.text.unicode);
	if (sfEvent.type == sf::Event::KeyPressed)
		event.type = grph::TEXT;
	return event;
}

extern "C"
{
	std::unique_ptr<grph::ILib> create(int width, int height)
	{
		return std::make_unique<caca::LibSfml>(width, height, 15);
	}

	std::string name()
	{
		return LIBSFML_NAME;
	}
}