/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 29/03/18 
*/

#ifndef LIBCACA_MAPLOADER_HPP
#define LIBCACA_MAPLOADER_HPP

#include <string>
#include <utility>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <algorithm>
#include <memory>
#include <IEntity.hpp>
#include <functional>
#include <ILib.hpp>
#include "IGame.hpp"
#include "DataBridge.hpp"

namespace game
{
	class IEntity;
	class GameMap;

	using EntityFunc = std::function<std::shared_ptr<IEntity>(int, int, game::GameMap&, game::DataBridge&)>;
	using EntityPtr = std::shared_ptr<game::IEntity>;
	using EntityVec = std::vector<game::EntityPtr>;
	using EntityMap = std::map<char, EntityFunc>;

	class GameMapException
		: public std::exception
	{
	public:
		explicit GameMapException(std::string const& where, std::string const& error)
			: _msg(where + " : " + error)
		{};
		char const* what() const noexcept final
		{
			return _msg.c_str();
		};
	private:
		std::string const _msg;
	};

	using maping = std::vector<std::vector<game::EntityVec>>;

	class GameMap
	{
	public:
		explicit GameMap(std::string const& path, game::DataBridge& data, game::EntityMap& construct);
		GameMap(GameMap const&) = delete;
		~GameMap() = default;
		GameMap& operator=(GameMap const&) = delete;

		EntityVec* getAllAt(int x, int y, bool borderBlock);
		std::shared_ptr<game::EntityVec> getListOf(std::string const& type);
		bool addEntity(EntityPtr& entity);
		bool removeEntity(EntityPtr& entity);
		bool moveEntity(game::EntityPtr& entity);
		bool moveEntity(game::IEntity& entity);
		bool BorderJumpXY(int &x, int &y, bool jump);
		void dump();
		void draw(grph::ILib& graphic);
		unsigned int getWidth() const;
		unsigned int getHeight() const;
	private:
		bool checkFormat(std::string const& headerLine);
		void fillMap(std::ifstream& file);
		void drawEntity(game::IEntity& entity, grph::ILib& graphic);

		std::string const _path;
		maping _maping;
		game::DataBridge& _data;
		EntityMap& _construct;
		unsigned int _width = 0;
		unsigned int _height = 0;

	};
}

#endif //LIBCACA_MAPLOADER_HPP
