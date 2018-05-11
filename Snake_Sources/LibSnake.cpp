/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 29/03/18 
*/

#include <memory>
#include "LibSnake.hpp"

snake::LibSnake::LibSnake()
	: AGame(), _data(), _background("./Snake_Sources/spriteSnake/background")
{
	_map = std::make_unique<game::GameMap>("./Snake_Sources/mapSnake/lvl1.map", _data, _construct);
	_player = (*_map->getListOf("snake"))[0];
	_width = _map->getWidth();
	_height = _map->getHeight();
}

void snake::LibSnake::restart()
{
	_map = std::make_unique<game::GameMap>("./Snake_Sources/mapSnake/lvl1.map", _data, _construct);
	_player = (*_map->getListOf("snake"))[0];
	_start = false;
	_pause = false;
	_data.setFoodCount(0);
}

void snake::LibSnake::updateGame(grph::KeyEvent const& event)
{
	_data.setEvent(event);
	_player->update();
}

void snake::LibSnake::genGameDisplay(grph::ILib& graphic)
{
	graphic.setBackGround(_background);
	graphic.drawText(3, 3, 3, "Food Eaten : " + std::to_string(_data.getFoodCount()), {0x00FFFFFF});
	_map->draw(graphic);
	if (not _start)
		graphic.drawText(_width / 2 - 20, _height / 3, 18, "Press Enter to start !", {0x00FFFFFF});
	if (_pause)
		graphic.drawText(_width / 2 - 12, _height / 3, 22, "PAUSE", {0x00FFFFFF});
	if (not _player->isActive())
		graphic.drawText(_width / 2 - 18, _height / 3, 22, "LOL T'A PERDU !!!", {0x00FFFFFF});

}

void snake::LibSnake::refresh()
{}

void snake::LibSnake::play(grph::ILib* graphic, grph::KeyEvent event)
{
	if (event.type == grph::ENTER)
		_start = true;
	if (event.key == 'p' && _start)
		_pause = !_pause;
	if (event.type == grph::BACKSPACE)
		restart();
	if (_start and not _pause)
		updateGame(event);
	if (graphic != nullptr) {
		genGameDisplay(*graphic);
		graphic->display();
		graphic->clear();
	}
}

extern "C"
{
	std::unique_ptr<GameEngine::IGame> create()
	{
		return std::make_unique<snake::LibSnake>();
	}

	std::string name()
	{
		return LIBSNAKE_NAME;
	}
}