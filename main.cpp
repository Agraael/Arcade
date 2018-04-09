/*
** EPITECH PROJECT, 2021
** libcaca
** File description:
** Created by kraken,
*/

#include <iostream>
#include <memory>
#include <GameMap.hpp>
#include "ILib.hpp"
#include "LibLoader.hpp"
#include "Arcade.hpp"
#include "Vector2D.hpp"

int main(int argc, char** argv)
{
	std::srand(static_cast<unsigned int>(time(0)));
	try {
		if (argc > 1) {
			arcd::Arcade arcade(argv[1]);
			arcade.start();
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::exit(84);
	}
	return 0;
}