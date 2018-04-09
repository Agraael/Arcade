/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 29/03/18 
*/

#ifndef LIBCACA_LIBSNAKE_HPP
#define LIBCACA_LIBSNAKE_HPP

#include "AGame.hpp"
#include "GameMap.hpp"
#include "SnakeEntity.hpp"
#include "WallEntity.hpp"
#include "SnakeDataBridge.hpp"
#include "FoodEntity.hpp"

namespace snake
{
	#define LIBSNAKE_NAME "SNAKE"

	class LibSnake
		: public GameEngine::AGame
	{
	public:
		LibSnake();
		LibSnake(LibSnake const&) = delete;
		~LibSnake() final = default;
		LibSnake& operator=(LibSnake const&) = delete;

		void restart() final;
		void updateGame(grph::KeyEvent const& event);
		void genGameDisplay(grph::ILib& graphic);
		void play(grph::ILib* graphic, grph::KeyEvent evnt) final;

	protected:
		void refresh() final;
	private:
		std::unique_ptr<game::GameMap> _map = nullptr;
		snake::SnakeDataBridge _data;
		game::EntityPtr _player = nullptr;
		grph::Sprite _background;

		game::EntityMap _construct = {
			{'_', [](int x, int y, game::GameMap& map, game::DataBridge& data){(void)(x),(void)(y),(void)(map),(void)(data);return nullptr;}},
			{'S', [](int x, int y, game::GameMap& map, game::DataBridge& data){return std::make_shared<snake::SnakeEntity>(x, y, map, data);}},
			{'W', [](int x, int y, game::GameMap& map, game::DataBridge& data){return std::make_shared<snake::WallEntity>(x, y, map, data);}},
			{'F', [](int x, int y, game::GameMap& map, game::DataBridge& data){return std::make_shared<snake::FoodEntity>(x, y, map, data);}},
		};
		bool _start = false;
		bool _pause = false;

	};
}

#endif //LIBCACA_LIBSNAKE_HPP
