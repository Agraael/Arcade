/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 13/03/18 
*/

#ifndef LIBCACA_LIBCACA_HPP
#define LIBCACA_LIBCACA_HPP

#include <memory>
#include <map>
#include "ALib.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "caca++.h"
#pragma GCC diagnostic pop

namespace caca
{
	const std::map<int, grph::KeyType> keyEventMap =
		{
			{CACA_KEY_ESCAPE, grph::QUIT},
			{CACA_KEY_UP, grph::UP},
			{CACA_KEY_DOWN, grph::DOWN},
			{CACA_KEY_LEFT, grph::LEFT},
			{CACA_KEY_RIGHT, grph::RIGHT},
			{CACA_KEY_BACKSPACE, grph::BACKSPACE},
			{CACA_KEY_TAB, grph::TAB},
			{13, grph::ENTER},
			{50, grph::PREV_LIB},
			{51, grph::NEXT_LIB},
			{52, grph::PREV_GAME},
			{53, grph::NEXT_GAME},
		};

	#define LIBCACA_NAME "Lib du Caca"

	class LibCaca
		: public grph::ALib
	{
	public:
		LibCaca(unsigned int width, unsigned int height, unsigned int scale);
		LibCaca(LibCaca const&) = delete;
		~LibCaca() final;
		LibCaca& operator=(LibCaca const&) = delete;
		bool display() final;
		bool clear() final;
		bool resize(int width, int height) final;
		bool drawSprite(int x1, int y1, int x2, int y2, grph::ISprite const& sprite) final;
		bool setBackGround(grph::ISprite const& sprite) final;
		bool drawText(int x, int y, unsigned int fontSize, std::string const& text, grph::ARGB const& color) final;
		grph::KeyEvent getKeyEvent() final;
	private:
		Canvas* _canvas;
		Caca* _caca;
		Event* _event;
		uint16_t _background = 0x0000;
	};
}

#endif //LIBCACA_LIBCACA_HPP
