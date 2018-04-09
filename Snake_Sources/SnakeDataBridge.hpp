/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 05/04/18 
*/

#ifndef LIBCACA_SNAKEDATABRIDGE_HPP
#define LIBCACA_SNAKEDATABRIDGE_HPP

#include "DataBridge.hpp"
#include "ILib.hpp"

namespace snake
{
	class SnakeDataBridge
		: public game::DataBridge
	{
	public:
		SnakeDataBridge() = default;
		~SnakeDataBridge() final = default;

		unsigned int getFoodCount() const {
			return _foodCount;
		}
		void setFoodCount(unsigned int foodCount){
			_foodCount = foodCount;
		}
		void addFood() {
			_foodCount += 1;
		}
	private:
		unsigned int _foodCount = 0;
	};
}

#endif //LIBCACA_SNAKEDATABRIDGE_HPP
