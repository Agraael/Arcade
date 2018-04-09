/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 27/03/18 
*/

#ifndef LIBCACA_ARCADE_HPP
#define LIBCACA_ARCADE_HPP

#include "LibLoader.hpp"
#include "GameMenu.hpp"
#include "GameManager.hpp"

namespace arcd
{
	enum ArcadeStatus
	{
		ARCD_QUIT, ARCD_END, ARCD_RESTART
	};

	class Arcade
	{
	public:
		explicit Arcade(std::string const& arg);
		Arcade(Arcade const&) = delete;
		~Arcade() = default;
		Arcade& operator=(Arcade const&) = delete;

		void start();
	private:
		arcd::LibLoader _loader;
		arcd::GameMenu _menu;
		arcd::GameManager _game;

	};
}

#endif //LIBCACA_ARCADE_HPP
