/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 06/04/18 
*/

#ifndef LIBCACA_LIBSFML_HPP
#define LIBCACA_LIBSFML_HPP

#include <memory>
#include <map>
#include "ALib.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "SFML/Graphics.hpp"
#pragma GCC diagnostic pop

namespace caca
{
	const std::vector<std::pair<sf::Keyboard::Key, grph::KeyType>> KeyEventVec = {
		{sf::Keyboard::Escape, grph::QUIT},
		{sf::Keyboard::Up, grph::UP},
		{sf::Keyboard::Down, grph::DOWN},
		{sf::Keyboard::Left, grph::LEFT},
		{sf::Keyboard::Right, grph::RIGHT},
		{sf::Keyboard::BackSpace, grph::BACKSPACE},
		{sf::Keyboard::Tab, grph::TAB},
		{sf::Keyboard::Return, grph::ENTER},
		{sf::Keyboard::Num2, grph::PREV_LIB},
		{sf::Keyboard::Num3, grph::NEXT_LIB},
		{sf::Keyboard::Num4, grph::PREV_GAME},
		{sf::Keyboard::Num5, grph::NEXT_GAME},
	};

	#define LIBSFML_NAME "Lib Sfml"

	class LibSfml
		: public grph::ALib
	{
	public:
		LibSfml(unsigned int widht, unsigned int height, unsigned int scale);
		LibSfml(LibSfml const&) = delete;
		~LibSfml() final;
		LibSfml& operator=(LibSfml const&) = delete;
		bool display() final;
		bool clear() final;
		bool resize(int width, int height) final;
		bool drawSprite(int x1, int y1, int x2, int y2, grph::ISprite const& sprite) final;
		bool setBackGround(grph::ISprite const& sprite) final;
		bool drawText(int x, int y, unsigned int fontSize, std::string const& text, grph::ARGB const& color) final;
		grph::KeyEvent getKeyEvent() final;
	private:
		void drawSquare(float x1, float y1, float x2, float y2, float scale, grph::ARGB const& C);
		void drawTexture(float x1, float y1, float x2, float y2, float scale, std::string const& path);
		std::shared_ptr<sf::Texture>& manageTexture(std::string const& path);
		sf::RenderWindow* _window = nullptr;
		std::map<std::string, std::shared_ptr<sf::Texture>> _textureSave;
		bool _spriteBackground = false;
		std::__shared_ptr<sf::Texture> _background = nullptr;
		grph::ARGB _backColor = {0x00000000};
	};
}

#endif //LIBCACA_LIBSFML_HPP
