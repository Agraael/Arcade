/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 13/03/18 
*/

#ifndef LIBCACA_ALIB_HPP
#define LIBCACA_ALIB_HPP

#include "ILib.hpp"

namespace grph
{
	class ALib
		: public grph::ILib
	{
	public:
		ALib(unsigned int width, unsigned int height, unsigned int scale, int delay, std::string const& name);
		ALib(ALib const&) = delete;
		~ALib() override = default;
		ALib& operator=(ALib const&) = delete;

		bool display() override = 0;
		bool clear() override = 0;
		bool resize(int width, int height) override = 0;
		bool drawSprite(int x1, int y1, int x2, int y2, ISprite const& sprite) override = 0;
		bool setBackGround(ISprite const& sprite) override = 0;
		bool drawText(int x, int y, unsigned int fontSize, std::string const& text, grph::ARGB const& color) override = 0;
		grph::KeyEvent getKeyEvent() override = 0;

		unsigned int getWidthScale() const final;
		unsigned int getHeightScale() const final;
		unsigned int getWidth() const final;
		unsigned int getHeight() const final;
		unsigned int getScale() const final;
		int getDelay() const final;

	protected:

		unsigned int _width;
		unsigned int _height;
		unsigned int _scale;
		std::string const _name;
		int _delay;
	};
}

#endif //LIBCACA_ALIB_HPP
