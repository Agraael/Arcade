/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 19/03/18 
*/

#ifndef LIBCACA_LIBLOADER_HPP
#define LIBCACA_LIBLOADER_HPP

#include <dlfcn.h>
#include <string>
#include <vector>
#include <ILib.hpp>
#include <memory>
#include <cstring>
#include <IGame.hpp>

namespace arcd
{
	class OpenDirException
		: public std::exception
	{
	public:
		explicit OpenDirException(std::string const& path)
			: _msg(path + " : " + strerror(errno))
		{};
		char const* what() const noexcept final
		{
			return _msg.c_str();
		};
	private:
		std::string const _msg;
	};

	class DlfncException
		: public std::exception
	{
	public:
		explicit DlfncException(std::string const& func, std::string const& elem)
			: _msg(func + " -> " + elem + " : " + dlerror())
		{};
		char const* what() const noexcept final
		{
			return _msg.c_str();
		};
	private:
		std::string const _msg;
	};

	enum libChoice
	{
		NEXT_LIB, PREV_LIB, SAME_LIB
	};

	class LibLoader
	{
	public:
		LibLoader(std::string const& gamesDir, std::string const& grphDir, std::string const& argGrph);
		LibLoader(LibLoader const&) = delete;
		~LibLoader() = default;
		LibLoader& operator=(LibLoader const&) = delete;

		void dlGrph();
		std::unique_ptr<grph::ILib> loadGrphLib(int width, int height, libChoice choice);
		void dlGame();
		std::unique_ptr<GameEngine::IGame> loadGameLib(std::string const& playerName, libChoice choice);
		void switchGrphLib(libChoice choice);
		void switchGameLib(libChoice choice);
		std::string getGrphName();
		std::string getGameName();

	private:
		std::vector<std::string> _gameLibs;
		std::vector<std::string> _grphLibs;
		std::vector<std::string>::iterator _actualGame;
		std::vector<std::string>::iterator _actualGrph;
		void* _gameHandler = nullptr;
		void* _grphHandler = nullptr;

		void bidirectional_iteration(std::vector<std::string>& vec,
		                             std::vector<std::string>::iterator& it,
		                             arcd::libChoice choice);
	};
}

#endif //LIBCACA_LIBLOADER_HPP
