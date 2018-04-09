/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 04/04/18 
*/

#ifndef LIBCACA_WALLENTITY_HPP
#define LIBCACA_WALLENTITY_HPP

#include <Entity.hpp>
#include "GameMap.hpp"
#include "DataBridge.hpp"

namespace snake
{
	class WallEntity
		: public game::Entity
	{
	public:
		WallEntity(int x, int y, game::GameMap& map, game::DataBridge& data);
		WallEntity(WallEntity const&) = delete;
		~WallEntity() final = default;
		WallEntity& operator=(WallEntity const&) = delete;

	private:
	};
}

#endif //LIBCACA_WALLENTITY_HPP
