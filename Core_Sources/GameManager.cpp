/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 29/03/18 
*/

#include <iostream>
#include <SnakeEntity.hpp>
#include <WallEntity.hpp>
#include "GameManager.hpp"
#include "IEntity.hpp"
#include "Entity.hpp"

arcd::GameManager::GameManager(arcd::LibLoader& loader)
: _loader(loader), _graphic(nullptr), _game(nullptr)
{}

bool arcd::GameManager::start(std::string const& playerName)
{
	grph::KeyEvent event = {grph::NOTHING, 0};

	_game = _loader.loadGameLib(playerName, arcd::SAME_LIB);
	_graphic = _loader.loadGrphLib(_game->getWidth(), _game->getHeight(), arcd::SAME_LIB);
	do {
		event = _graphic->getKeyEvent();
		_game->play(_graphic.get(), event);
		if (event.type == grph::NEXT_LIB) {
			_graphic = nullptr;
			_graphic = _loader.loadGrphLib(_game->getWidth(), _game->getHeight(), arcd::NEXT_LIB);
		}
		if (event.type == grph::PREV_LIB) {
			_graphic = nullptr;
			_graphic = _loader.loadGrphLib(_game->getWidth(), _game->getHeight(), arcd::PREV_LIB);
		}
		if (event.type == grph::QUIT) {
			_graphic = nullptr;
			return false;
		}
	} while (event.type != grph::TAB);
	_graphic = nullptr;
	return true;
}
