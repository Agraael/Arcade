/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 14/03/18 
*/
namespace grph
{
	class Sprite;
}

#ifndef LIBCACA_SPRITE_HPP
#define LIBCACA_SPRITE_HPP

#include <string>
	#include "ISprite.hpp"

namespace grph
{
	class SpriteException
		: public std::exception
	{
	public:
		explicit SpriteException(std::string const& where, std::string const& error)
			: _msg(where + " : " + error)
		{
		};

		char const* what() const noexcept final
		{
			return _msg.c_str();
		};
	private:
		std::string const _msg;
	};

	class Sprite
		: public grph::ISprite
	{
	public:
		Sprite(std::string const& path, unsigned int val, char termChar);
		explicit Sprite(std::string const& file_path);
		~Sprite() final = default;

		std::string const& getPath() const final;
		void setPath(std::string const& path) final;
		ARGB const& getSubColor() const final;
		void setSubColor(ARGB const& subColor) final;

		unsigned int getVal() const final;
		unsigned char getAlpha() const final;
		unsigned char getRed() const final;
		unsigned char getGreen() const final;
		unsigned char getBlue() const final;
		void setVal(unsigned int val) final;
		void setAlpha(unsigned char alpha) final;
		void setRed(unsigned char red) final;
		void setGreen(unsigned char green) final;
		void setBlue(unsigned char blue) final;
		char getTermChar() const final;
		void setTermChar(char termChar) final;

	private:

		void checkFile();
		std::string _path; // path de la texture
		grph::ARGB _subColor; // couleur de substitution
		char _termChar; // caractère pour les lib en mode terminal / ou caca
	};
}

#endif //LIBCACA_SPRITE_HPP
