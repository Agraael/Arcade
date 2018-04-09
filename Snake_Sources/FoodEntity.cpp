/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 06/04/18 
*/

#include <algorithm>
#include "FoodEntity.hpp"

snake::FoodEntity::FoodEntity(int x, int y, game::GameMap& map, game::DataBridge& data)
	: Entity(x, y, map, data, true, false, false, 0, "food", "./Snake_Sources/spriteSnake/food")
{}

void snake::FoodEntity::update()
{
	int W = _map.getWidth();
	int H = _map.getHeight();
	int x = std::rand() % W;
	int y = std::rand() % H;

	while (not checkTeleport(x, y)) {

		x = std::rand() % W;
		y = std::rand() % H;
	}
	_newCoord.X = x;
	_newCoord.Y = y;
	Entity::update();
}

bool snake::FoodEntity::checkTeleport(int x, int y)
{
	game::EntityVec* entities = _map.getAllAt(x, y, false);

	if (entities == nullptr)
		return false;
	return not (std::find_if(entities->begin(), entities->end(),
		[this](game::EntityPtr const& m)-> bool {return m && m->getId() != this->getId();}) != entities->end());
}
