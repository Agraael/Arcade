/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 05/04/18 
*/

#ifndef LIBCACA_SNAKEBODYENTITY_HPP
#define LIBCACA_SNAKEBODYENTITY_HPP

#include <Entity.hpp>
#include "SnakeDataBridge.hpp"

namespace snake
{
	class SnakeBodyEntity
		: public game::Entity
	{
	public:
		SnakeBodyEntity(int x, int y, game::GameMap& map, game::DataBridge& data);
		SnakeBodyEntity(SnakeBodyEntity const&) = delete;
		~SnakeBodyEntity() final = default;
		SnakeBodyEntity& operator=(SnakeBodyEntity const&) = delete;

		void update() final;
	private:
	};
}

#endif //LIBCACA_SNAKEBODYENTITY_HPP
