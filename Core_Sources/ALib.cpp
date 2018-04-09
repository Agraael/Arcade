/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 13/03/18 
*/

#include "ALib.hpp"

grph::ALib::ALib(unsigned int width, unsigned int height, unsigned int scale, int delay, std::string const& name)
	: _width(width), _height(height), _scale(scale), _name(name), _delay(delay)
{}

unsigned int grph::ALib::getWidthScale() const
{
	return _width /_scale;
}

unsigned int grph::ALib::getHeightScale() const
{
	return _height / _scale;
}

unsigned int grph::ALib::getWidth() const
{
	return _width;
}

unsigned int grph::ALib::getHeight() const
{
	return _height;
}

unsigned int grph::ALib::getScale() const
{
	return _scale;
}

int grph::ALib::getDelay() const
{
	return _delay;
}
