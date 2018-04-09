//
// Created by ludovica on 04/04/18.
//

#ifndef CPP_ARCADE_AGAME_HPP
#define CPP_ARCADE_AGAME_HPP

#include <memory>
#include <vector>
#include <list>
#include <iostream>
#include <chrono>
#include <thread>

#include "IGame.hpp"
#include "ILib.hpp"

namespace GameEngine
{
	class AGame
		: public IGame
	{
	protected:
		grph::ILib* _graphic = nullptr;
		int _width = 0;
		int _height = 0;
		void refresh() override = 0;
	public:
		AGame() = default;
		~AGame() override = default;
		AGame(AGame const&) = delete;
		AGame& operator=(AGame const&) = delete;

		void play(grph::ILib* graphic, grph::KeyEvent evnt) override = 0;
		void restart() override = 0;
		int getWidth() const final;
		int getHeight() const final;
	};
}

#endif //CPP_ARCADE_AGAME_HPP
