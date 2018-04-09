/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 13/03/18 
*/

#ifndef LIBCACA_ILIB_HPP
#define LIBCACA_ILIB_HPP

#include <string>
#include "Sprite.hpp"

namespace grph
{
	const unsigned int USEC_60FPS_DELAY = 16666;

	enum KeyType
	{
		NOTHING,
		QUIT,
		NEXT_GAME, PREV_GAME,
		NEXT_LIB, PREV_LIB,
		RESTART, MENU,
		UP, DOWN, LEFT, RIGHT,
		BACKSPACE, TEXT, TAB,
		ENTER, OTHER
	};

	struct KeyEvent
	{
		grph::KeyType type;
		char key;
	};

	class ILib
	{
	public:
		virtual ~ILib() = default;
		virtual bool display() = 0;
		virtual bool clear() = 0;
		virtual bool resize(int width, int height) = 0;
		virtual bool drawSprite(int x1, int y1, int x2, int y2, ISprite const& sprite) = 0;
		virtual bool setBackGround(ISprite const& sprite) = 0;
		virtual bool drawText(int x, int y, unsigned int fontSize, std::string const& text, grph::ARGB const& color) = 0;
		virtual grph::KeyEvent getKeyEvent() = 0;

		virtual unsigned int getWidthScale() const = 0;
		virtual unsigned int getHeightScale() const = 0;
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		virtual unsigned int getScale() const = 0;
		virtual int getDelay() const = 0;
	};
}

#endif //LIBCACA_ILIB_HPP
