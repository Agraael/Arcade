/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 04/04/18 
*/

#ifndef LIBCACA_SNAKEENTITY_HPP
#define LIBCACA_SNAKEENTITY_HPP

#include <list>
#include <utility>
#include <Entity.hpp>
#include "DataBridge.hpp"
#include "SnakeDataBridge.hpp"

namespace snake
{
	class SnakeEntity
		: public game::Entity
	{
	public:
		SnakeEntity(int x, int y, game::GameMap& map, game::DataBridge& data);
		SnakeEntity(SnakeEntity const&) = delete;
		~SnakeEntity() final = default;
		SnakeEntity& operator=(SnakeEntity const&) = delete;

		void update() final;
	private:
		void putTailPositions();
		void checkFoodContact();
		void rotate();

		snake::SnakeDataBridge* _snakeData = nullptr;
		game::EntityVec _snakePart = game::EntityVec();
		std::list<std::pair<int, int>> _tailPos = {};
		unsigned int _snakeSize = 4;
	};
}

#endif //LIBCACA_SNAKEENTITY_HPP
