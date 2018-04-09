/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 29/03/18 
*/

#ifndef LIBCACA_GAMEMANAGER_HPP
#define LIBCACA_GAMEMANAGER_HPP

#include <IGame.hpp>
#include "LibLoader.hpp"

namespace arcd
{
	class GameManager
	{
	public:
		explicit GameManager(arcd::LibLoader& loader);
		GameManager(GameManager const&) = delete;
		~GameManager() = default;
		GameManager& operator=(GameManager const&) = delete;

		bool start(std::string const& playerName);

	private:
		arcd::LibLoader& _loader;
		std::unique_ptr<grph::ILib> _graphic;
		std::unique_ptr<GameEngine::IGame> _game;
	};
}

#endif //LIBCACA_GAMEMANAGER_HPP
