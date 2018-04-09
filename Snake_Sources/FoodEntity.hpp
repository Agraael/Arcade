/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 06/04/18 
*/

#ifndef LIBCACA_FOODENTITY_HPP
#define LIBCACA_FOODENTITY_HPP

#include <Entity.hpp>

namespace snake
{
	class FoodEntity
		: public game::Entity
	{
	public:
		FoodEntity(int x, int y, game::GameMap& map, game::DataBridge& data);
		FoodEntity(FoodEntity const&) = delete;
		~FoodEntity() final = default;
		FoodEntity& operator=(FoodEntity const&) = delete;

		void update() override;
	private:
		bool checkTeleport(int x, int y);
	};
}

#endif //LIBCACA_FOODENTITY_HPP
