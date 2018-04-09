/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 19/03/18 
*/

#include <dirent.h>
#include <cstring>
#include <iostream>
#include <dlfcn.h>
#include <algorithm>
#include <iterator>
#include "LibLoader.hpp"

static void save_libs_paths(std::string const& dirPath, std::vector<std::string>& vec)
{
	unsigned char const isFile = 0x8;
	DIR *directory;
	struct dirent* entry;

	directory = opendir(dirPath.c_str());
	if (directory == nullptr)
		throw arcd::OpenDirException(dirPath);
	while ((entry = readdir(directory))) {
		if (entry->d_type == isFile) {
			auto path = dirPath + "/" + entry->d_name;
			if (std::find(vec.begin(), vec.end(), path) == vec.end())
				vec.emplace_back(path);
		}
	}
}

static void* load_dynamic_lib(std::string const& path)
{
	void* handler;

	handler = dlopen(path.c_str(), RTLD_NOW);
	if (handler == nullptr)
		throw arcd::DlfncException("dlopen", path);
	return handler;
}

arcd::LibLoader::LibLoader(std::string const& gamesDir, std::string const& grphDir, std::string const& argGrph)
	: _gameLibs(), _grphLibs(), _actualGame(), _actualGrph()
{
	(void)(gamesDir);
	_grphLibs.emplace_back(argGrph);
	try {
		save_libs_paths(grphDir, _grphLibs);
		save_libs_paths(gamesDir, _gameLibs);
	}
	catch (arcd::OpenDirException& e) {
		std::cout << e.what() << std::endl;
		std::exit(84);
	}
	_actualGrph = _grphLibs.begin();
	if (_gameLibs.empty())
		_actualGame = _gameLibs.end();
	else {
		_actualGame = _gameLibs.begin();
		dlGame();
	}
}

void arcd::LibLoader::dlGrph()
{
	if (_grphHandler != nullptr) {
		auto err = dlclose(_grphHandler);
		if (err != 0)
			throw arcd::DlfncException("dlclose", "");
	}
	_grphHandler = load_dynamic_lib(*_actualGrph);
}

std::unique_ptr<grph::ILib> arcd::LibLoader::loadGrphLib(int width, int height, arcd::libChoice choice)
{
	std::unique_ptr<grph::ILib> (*func)(int, int);
	void* ptr;

	bidirectional_iteration(_grphLibs, _actualGrph, choice);
	dlGrph();
	ptr = dlsym(_grphHandler, "create");
	if (ptr == nullptr)
		throw arcd::DlfncException("dlsym", "create");
	func = reinterpret_cast<std::unique_ptr<grph::ILib>(*)(int, int)>(ptr);
	return func(width, height);
}

void arcd::LibLoader::dlGame()
{
	if (_gameHandler != nullptr) {
		auto err = dlclose(_gameHandler);
		if (err != 0)
			throw arcd::DlfncException("dlclose", "");
	}
	_gameHandler = load_dynamic_lib(*_actualGame);
}

std::unique_ptr<GameEngine::IGame> arcd::LibLoader::loadGameLib(std::string const& playerName, arcd::libChoice choice)
{
	std::unique_ptr<GameEngine::IGame> (*func)();
	void* ptr;

	(void)(playerName);
	bidirectional_iteration(_gameLibs, _actualGame, choice);
	dlGrph();
	ptr = dlsym(_gameHandler, "create");
	if (ptr == nullptr)
		throw arcd::DlfncException("dlsym", "create");
	func = reinterpret_cast<std::unique_ptr<GameEngine::IGame>(*)()>(ptr);
	return func();
}

void arcd::LibLoader::switchGrphLib(libChoice choice)
{
	bidirectional_iteration(_grphLibs, _actualGrph, choice);
	dlGrph();
}

void arcd::LibLoader::switchGameLib(libChoice choice)
{
	bidirectional_iteration(_gameLibs, _actualGame, choice);
	dlGame();
}


void arcd::LibLoader::bidirectional_iteration(std::vector<std::string>& vec,
                                              std::vector<std::string>::iterator& it,
                                              arcd::libChoice choice)
{
	if (choice != arcd::SAME_LIB) {
		if (choice == arcd::NEXT_LIB) {
			it = std::next(it);
			if (it == vec.end())
				it = vec.begin();
		}
		else {
			if (it == vec.begin())
				it = vec.end();
			it = std::prev(it);
		}
	}
}

std::string arcd::LibLoader::getGrphName()
{
	std::string (*func)();
	void* ptr;

	if (_grphHandler == nullptr) {
		return "[ NO GRAPHIC ]";
	}
	ptr = dlsym(_grphHandler, "name");
	if (ptr == nullptr)
		throw arcd::DlfncException("dlsym", "name");
	func = reinterpret_cast<std::string(*)()>(ptr);
	return func();
}

std::string arcd::LibLoader::getGameName()
{
	std::string(*func)();
	void* ptr;

	if (_gameHandler == nullptr) {
		return "[ NO GAME ]";
	}
	ptr = dlsym(_gameHandler, "name");
	if (ptr == nullptr)
		throw arcd::DlfncException("dlsym", "name");
	func = reinterpret_cast<std::string(*)()>(ptr);
	return func();
}



