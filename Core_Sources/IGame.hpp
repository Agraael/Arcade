/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** game interface
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "ILib.hpp"

namespace GameEngine
{
	class IGame
	{
	protected:
		virtual void refresh() = 0;
	public:
		virtual ~IGame() = default;
		virtual void play(grph::ILib* graphic, grph::KeyEvent evnt) = 0;
		virtual void restart() = 0;
		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;
	};
}

#endif