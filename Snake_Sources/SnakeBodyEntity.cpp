/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 05/04/18 
*/

#include "SnakeBodyEntity.hpp"

snake::SnakeBodyEntity::SnakeBodyEntity(int x, int y, game::GameMap& map, game::DataBridge& data)
	: Entity(x, y, map, data, true, true, true, 0, "snakebody", "./Snake_Sources/spriteSnake/snakebody")
{
	_force.reset(0);
	_force.setMag(0);
}

void snake::SnakeBodyEntity::update()
{
	_map.moveEntity(*this);
	_lastCoord = _newCoord;
}
