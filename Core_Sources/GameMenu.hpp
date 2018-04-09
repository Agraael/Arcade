/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 27/03/18 
*/

#ifndef LIBCACA_GAMEMENU_HPP
#define LIBCACA_GAMEMENU_HPP

#include <bits/unique_ptr.h>
#include <ILib.hpp>
#include "LibLoader.hpp"

namespace arcd
{
	#define MENU_WIDTH 40
	#define MENU_HEIGHT 40

	class GameMenu
	{
	public:
		explicit GameMenu(arcd::LibLoader& loader);
		GameMenu(GameMenu const&) = delete;
		~GameMenu() = default;
		GameMenu& operator=(GameMenu const&) = delete;

		bool start();
		std::string const& getPlayerName() const;
	private:
		void drawMenu(bool text_mode);
		void drawTextCentered(unsigned int y, std::string const& text, grph::ARGB const& color);
		void textType(grph::KeyEvent const& event);
		void switchLib(grph::KeyType type);

		arcd::LibLoader& _loader;
		std::unique_ptr<grph::ILib> _graphic;
		std::string _grphName = "";
//		std::string _gameName;
		mutable std::string _playerName = "";
	};
}

#endif //LIBCACA_GAMEMENU_HPP
