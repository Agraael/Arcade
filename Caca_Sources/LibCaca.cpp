/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 13/03/18 
*/

#include <iostream>
#include <map>
#include "LibCaca.hpp"

caca::LibCaca::LibCaca(unsigned int width, unsigned int height, unsigned int scale)
	: ALib(width, height, scale, 60, "Lib Caca"),
	_canvas(new Canvas(_width, _height)),
	_caca(new Caca(_canvas)),
	_event(new Event()) {
	_caca->setDisplayTime(grph::USEC_60FPS_DELAY);
	_caca->setTitle("Arcade");
}

caca::LibCaca::~LibCaca()
{
	delete _canvas;
	delete _caca;
	delete _event;
}

bool caca::LibCaca::display()
{
	_caca->Display();
	return true;
}

bool caca::LibCaca::clear()
{
	_canvas->setColorARGB(_background, _background);
	_canvas->Clear();
	return true;
}

bool caca::LibCaca::resize(int width, int height)
{
	delete _canvas;
	delete _caca;
	delete _event;
	_canvas = new Canvas(width, height);
	_caca = new Caca(_canvas);
	_event = new Event();
	_caca->setDisplayTime(10000);
	_caca->setTitle("Arcade");
	return true;
}

static uint16_t argb_32_to_16(grph::ARGB const& color)
{
	uint16_t argb = 0x0000;

	argb = static_cast<uint16_t>(argb + (color.argb.alpha / 16 << 12));
	argb = static_cast<uint16_t>(argb + (color.argb.red / 16 << 8));
	argb = static_cast<uint16_t>(argb + (color.argb.green / 16 << 4));
	argb = static_cast<uint16_t>(argb + (color.argb.blue / 16));
	return argb;
}

bool caca::LibCaca::drawSprite(int x1, int y1, int w, int h, grph::ISprite const& sprite)
{
	x1 *= _scale;
	y1 *= _scale;
	w *= _scale;
	h *= _scale;
	if (sprite.getTermChar() == 0)
		_canvas->setColorARGB(_background, argb_32_to_16(sprite.getSubColor()));
	else
		_canvas->setColorARGB(argb_32_to_16(sprite.getSubColor()), _background);
	_canvas->fillBox(x1, y1, w * _scale, h * _scale, static_cast<uint32_t>(sprite.getTermChar()));
	return true;
}

bool caca::LibCaca::setBackGround(grph::ISprite const& sprite)
{
	_background = argb_32_to_16(sprite.getSubColor());
	return true;
}

bool caca::LibCaca::drawText(int x, int y, unsigned int fontSize, std::string const& text, grph::ARGB const& color)
{
	char* char_text = new char[text.size()+1];

	(void)(fontSize);
	std::copy(text.begin(), text.end(), char_text);
	char_text[text.size()] = '\0';
	_canvas->setColorARGB(argb_32_to_16(color), _background);
	_canvas->putStr(x, y, char_text);
	delete[] char_text;
	return true;
}

grph::KeyEvent caca::LibCaca::getKeyEvent()
{
	grph::KeyEvent event = {grph::NOTHING, 0};

	if (_caca->getEvent(Event::CACA_EVENT_KEY_PRESS, _event, 0) == 1) {
		auto type = caca_get_event_key_ch(&_event->e);
		if (caca::keyEventMap.find(type) != caca::keyEventMap.end())
			event.type = caca::keyEventMap.at(type);
		else {
			event.type = grph::TEXT;
			caca_utf32_to_utf8(&event.key, caca_get_event_key_utf32(&_event->e));
		}
	}
	return event;
}

extern "C"
{
	std::unique_ptr<grph::ILib> create(int width, int height)
	{
		return std::make_unique<caca::LibCaca>(width, height, 1);
	}

	std::string name()
	{
		return LIBCACA_NAME;
	}
}