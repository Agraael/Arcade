/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 04/04/18 
*/

#include "WallEntity.hpp"
#include "DataBridge.hpp"

snake::WallEntity::WallEntity(int x, int y, game::GameMap& map, game::DataBridge& data)
	: Entity(x, y, map, data, true, true, false, 0, "wall", "./Snake_Sources/spriteSnake/wall")
{}
