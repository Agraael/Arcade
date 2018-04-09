/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 14/03/18 
*/

#include <fstream>
#include "Sprite.hpp"

grph::Sprite::Sprite(std::string const& path, unsigned int val, char termChar)
	: _path(path), _subColor(), _termChar(termChar)
{
	_subColor.val = val;
	if (not _path.empty())
		checkFile();
}

grph::Sprite::Sprite(std::string const& file_path)
	: _path(""), _subColor({0}), _termChar(0)
{
	std::string line;
	std::ifstream file(file_path);

	if (not file.is_open())
		throw SpriteException("Sprite", "cannot open sprite config file :" + _path);
	getline(file, line);
	_termChar = line.c_str()[0];
	getline(file, line);
	_path = line;
	if (not _path.empty())
		checkFile();
	getline(file, line);
	_subColor.val = static_cast<unsigned int>(std::stol(line, nullptr, 16));
}


std::string const& grph::Sprite::getPath() const
{
	return _path;
}

void grph::Sprite::setPath(std::string const& path)
{
	_path = path;
}

unsigned int grph::Sprite::getVal() const
{
	return _subColor.val;
}

void grph::Sprite::setVal(unsigned int val)
{
	_subColor.val = val;
}

unsigned char grph::Sprite::getAlpha() const
{
	return _subColor.argb.alpha;
}

unsigned char grph::Sprite::getRed() const
{
	return _subColor.argb.red;
}

unsigned char grph::Sprite::getGreen() const
{
	return _subColor.argb.green;
}

unsigned char grph::Sprite::getBlue() const
{
	return _subColor.argb.blue;
}

void grph::Sprite::setAlpha(unsigned char alpha)
{
	_subColor.argb.alpha = alpha;
}

void grph::Sprite::setRed(unsigned char red)
{
	_subColor.argb.red = red;
}

void grph::Sprite::setGreen(unsigned char green)
{
	_subColor.argb.green = green;
}

void grph::Sprite::setBlue(unsigned char blue)
{
	_subColor.argb.blue = blue;
}

grph::ARGB const& grph::Sprite::getSubColor() const
{
	return _subColor;
}

void grph::Sprite::setSubColor(grph::ARGB const& subColor)
{
	_subColor = subColor;
}

char grph::Sprite::getTermChar() const
{
	return _termChar;
}

void grph::Sprite::setTermChar(char termChar)
{
	_termChar = termChar;
}

void grph::Sprite::checkFile()
{
	std::ifstream file(_path);

	if (not file.is_open())
		throw SpriteException("Sprite", "cannot open sprite file :" + _path);
}



