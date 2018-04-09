/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 27/03/18 
*/

#include "GameMenu.hpp"

arcd::GameMenu::GameMenu(arcd::LibLoader& loader)
	: _loader(loader), _graphic(nullptr)
{}

bool arcd::GameMenu::start()
{
	grph::KeyEvent event = {grph::NOTHING, 0};
	bool text_mode = false;

	_graphic = _loader.loadGrphLib(MENU_WIDTH, MENU_HEIGHT, arcd::SAME_LIB);
	do {
		drawMenu(text_mode);
		_graphic->display();
		event = _graphic->getKeyEvent();
		_graphic->clear();
		if (event.type == grph::TAB)
			text_mode = !text_mode;
		if (not text_mode)
			switchLib(event.type);
		if (text_mode)
			textType(event);
		if (event.type == grph::QUIT) {
			_graphic = nullptr;
			return false;
		}
	} while (event.type != grph::ENTER);
	_graphic = nullptr;
	return true;
}

void arcd::GameMenu::drawTextCentered(unsigned int y, std::string const& text, grph::ARGB const& color)
{
	auto len = static_cast<unsigned int>(text.size());;
	_graphic->drawText(_graphic->getWidth() / 2 - (len / 2), y, 1, text, color);
}

void arcd::GameMenu::textType(grph::KeyEvent const& event)
{
	if (event.type == grph::BACKSPACE and not _playerName.empty())
		_playerName.pop_back();
	else if (_playerName.size() < 15 && event.type == grph::TEXT)
		_playerName.push_back(event.key);
}

void arcd::GameMenu::drawMenu(bool text_mode)
{
	grph::ARGB color = {0x00FFFFFF};
	std::string tmp = _playerName;

	drawTextCentered(1, "WELCOME TO ARCADE !!!", {0x00FFFF00});
	drawTextCentered(2, "---------------------------------", {0x00FFFF00});
	drawTextCentered(3, "Choose your graphics", {0x00FFFFFF});
	drawTextCentered(4, "<= [2]  " + _loader.getGrphName() + "  [3] =>", {0x00FF55FF});
	drawTextCentered(6, "Choose your game", {0x00FFFFFF});
	drawTextCentered(7, "<= [4]  " + _loader.getGameName() + "  [5] =>", {0x00FF55FF});
	drawTextCentered(9, "Choose your Name", {0x00FFFFFF});
	if (text_mode) {
		color.val = 0x00FFFF00;
		tmp = "[ " + _playerName + " ]";
	}
	if (_playerName.empty())
		drawTextCentered(10, "(press TAB to change your name)", color);
	else
		drawTextCentered(10, tmp, color);
}

std::string const& arcd::GameMenu::getPlayerName() const
{
	if (_playerName.empty())
		_playerName = "Guest";
	return _playerName;
}

void arcd::GameMenu::switchLib(grph::KeyType type)
{
	switch (type) {
	case grph::NEXT_GAME:
		_loader.switchGameLib(arcd::NEXT_LIB);
		break;
	case grph::PREV_GAME:
		_loader.switchGameLib(arcd::PREV_LIB);
		break;
	case grph::NEXT_LIB:
		_graphic = nullptr;
		_graphic = _loader.loadGrphLib(MENU_WIDTH, MENU_HEIGHT, arcd::NEXT_LIB);
		break;
	case grph::PREV_LIB:
		_graphic = nullptr;
		_graphic = _loader.loadGrphLib(MENU_WIDTH, MENU_HEIGHT, arcd::PREV_LIB);
		break;
	default:
		break;
	}
}


