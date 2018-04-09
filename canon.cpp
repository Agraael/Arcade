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
//		TEST:
		if (argc > 1) {
			arcd::LibLoader loader("games", "libs", argv[1]);
			std::unique_ptr<grph::ILib> graphic = loader.loadGrphLib(70, 30, arcd::SAME_LIB);
			grph::KeyEvent event =  {grph::NOTHING, 0};
			grph::Sprite sprite1("", 0x00FFFFFF, 0);
			grph::Sprite background("", 0x00222222, 0);
			grph::Sprite sprite2("./Snake_Sources/spriteSnake/wall");
			double posX = 1;
			double posY = 29;
			math::Vector2D canon(4,-4);
			math::Vector2D gravity(0,0.02);
			math::Vector2D force(0, 0);
			double power = 1;
			bool fire = false;
			graphic->setBackGround(background);
			do {
				std::stringstream ss;

				ss << "canon -> " << canon << " power " << power;
				graphic->drawText(1, 1, 1, ss.str(),{0x00FFFFFF});
				graphic->drawSprite(static_cast<int>(1 + canon.getX()), static_cast<int>(28 + canon.getY()), 2, 2, sprite1);

				graphic->drawSprite(static_cast<int>(posX), static_cast<int>(posY),
					1, 1, sprite2);
				graphic->display();
				event = graphic->getKeyEvent();
				graphic->clear();
				if (event.type == grph::RIGHT)
					canon.rotate(10);
				if (event.type == grph::LEFT)
					canon.rotate(-10);
				if (event.type == grph::UP)
					power += 0.01;
				if (event.type == grph::DOWN)
					power -= 0.01;

				if (event.type == grph::ENTER) {
					fire = true;
					force = canon;
					force.setMag(power);
					std::cout << force << force.getMag() << std::endl;
				}
				if (fire) {
					force.sub(0.001);
					force.add(gravity);
					posX += force.getX();
					posY += force.getY();
				}
//				if (event.type == grph::BACKSPACE)
//					goto TEST;
			} while (event.type != grph::QUIT);
			graphic = nullptr;
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::exit(84);
	}
	return 0;
}