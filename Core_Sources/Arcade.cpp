/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 27/03/18 
*/

#include "Arcade.hpp"

arcd::Arcade::Arcade(std::string const& arg)
	: _loader("./games", "./libs", arg),
	_menu(_loader), _game(_loader)
{
}

void arcd::Arcade::start()
{
	if(_menu.start()) {
		if (_game.start(_menu.getPlayerName()))
			start();
	}
}
