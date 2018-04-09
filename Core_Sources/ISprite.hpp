/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 04/04/18 
*/

#ifndef LIBCACA_ISPRITE_HPP
#define LIBCACA_ISPRITE_HPP

#include <string>

namespace grph
{
	union ARGB
	{
		unsigned int val = 0;
		struct hex
		{
			unsigned char blue;
			unsigned char green;
			unsigned char red;
			unsigned char alpha;
		} argb;
	};

	class ISprite
	{
	public:
		virtual ~ISprite() = default;

		virtual std::string const& getPath() const = 0;
		virtual void setPath(std::string const& path) = 0;
		virtual ARGB const& getSubColor() const = 0;
		virtual void setSubColor(ARGB const& subColor) = 0;

		virtual unsigned int getVal() const = 0;
		virtual unsigned char getAlpha() const = 0;
		virtual unsigned char getRed() const = 0;
		virtual unsigned char getGreen() const = 0;
		virtual unsigned char getBlue() const = 0;
		virtual void setVal(unsigned int val) = 0;
		virtual void setAlpha(unsigned char alpha) = 0;
		virtual void setRed(unsigned char red) = 0;
		virtual void setGreen(unsigned char green) = 0;
		virtual void setBlue(unsigned char blue) = 0;
		virtual char getTermChar() const = 0;
		virtual void setTermChar(char termChar) = 0;
	};
}

#endif //LIBCACA_ISPRITE_HPP