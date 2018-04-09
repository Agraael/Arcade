/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 31/03/18 
*/

#include <GameMap.hpp>
#include <Entity.hpp>

game::GameMap::GameMap(std::string const& path, game::DataBridge& data,
                       game::EntityMap& construct)
	: _path(path), _maping(), _data(data),  _construct(construct)
{
	std::ifstream file(path);
	std::string line;

	if (not file.is_open())
		throw GameMapException(__func__, "file not found or cannot be open");
	std::getline(file, line);
	if (!checkFormat(line))
		throw GameMapException(__func__, "incorrect map file header : [MAP:(width):(height)]");
	fillMap(file);
}

inline bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

bool game::GameMap::checkFormat(std::string const& headerLine)
{
	bool res = false;
	std::string type;
	std::string width;
	std::string height;

	auto delim1 = std::find(headerLine.begin(), headerLine.end(), ':');
	std::copy(headerLine.begin() + 1, delim1, std::back_inserter(type));
	auto delim2 = std::find(delim1 + 1, headerLine.end(), ':');
	std::copy(delim1 + 1, delim2, std::back_inserter(width));
	delim1 = delim2;
	delim2 = std::find(delim1 + 1, headerLine.end(), ']');
	std::copy(delim1 + 1, delim2, std::back_inserter(height));
	if (type == "MAP" && is_number(width) && is_number(height) && delim2 + 1 == headerLine.end()) {
		_width = static_cast<unsigned int>(std::stoi(width));
		_height = static_cast<unsigned int>(std::stoi(height));
		res = true;
	}
	return res;
}

void game::GameMap::fillMap(std::ifstream& file)
{
	std::string line;
	unsigned int YNb = 0;

	_maping.resize(_height, std::vector<game::EntityVec>(_width));
	typename maping::iterator itY = _maping.begin();
	while (getline(file, line)){
		unsigned int XNb = 0;
		auto itX = itY->begin();
		for (auto& c : line) {
			if (_construct.find(c) == _construct.end()) {
				std::string error = "undifined element -> ";
				error += c;
				throw GameMapException(__func__, error);
			}
			if (line.size() != _width)
				throw GameMapException(__func__, "map definition width is incorrect :" + std::to_string(line.size()));
			auto func = _construct.at(c);
			(*itX).push_back(func(XNb, YNb, *this, _data));
			++itX;
			++XNb;
		}
		++YNb;
		++itY;
	}
	if (YNb != _height)
		throw GameMapException(__func__, "map definition height is incorrect :" + std::to_string(YNb));
}

game::EntityVec* game::GameMap::getAllAt(int x, int y, bool borderBlock)
{
	if (not BorderJumpXY(x, y, borderBlock)) {
		return nullptr;
	}
	return &_maping[y][x];
}

std::shared_ptr<game::EntityVec> game::GameMap::getListOf(std::string const& type)
{
	std::shared_ptr<game::EntityVec> list;

	list = std::make_shared<EntityVec>();
	for (auto& itY : _maping) {
		for (auto& itX : itY) {
			for (auto& item : itX) {
				if (item && item->getType() == type)
					list->push_back(item);
			}
		}
	}
	return list;
}

bool game::GameMap::BorderJumpXY(int& x, int& y, bool jump)
{
	bool isOut = false;
	auto W = static_cast<int>(_width);
	auto H = static_cast<int>(_height);

	if ((x < 0 or x >= W) or (y < 0 or y >= H))
		isOut = true;
	if (isOut and jump) {
		x = x % W;
		y = y % H;
		x += (x < 0) ? W : 0;
		y += (y < 0) ? H : 0;
		return true;
	}
	return not isOut;
}

void game::GameMap::dump()
{
	for (auto& itY : _maping) {
		for (auto& itX : itY) {
			std::cout << "(";
			std::cout << itX.size();
			for (auto& item : itX) {
				if (item)
					std::cout << "[" << item->getX() << "," <<  item->getY() << "]";
				else
					std::cout << "[X]";
			}
			std::cout << ")";
		}
		std::cout << std::endl;
	}
}

void game::GameMap::drawEntity(game::IEntity& entity, grph::ILib& graphic)
{
	int x = entity.getX();
	int y = entity.getY();

	BorderJumpXY(x, y, entity.canBorderJump());
	if (entity.isVisible())
		graphic.drawSprite(x, y, 1, 1, entity.getSprite());
}

bool IsMarkedToDelete(const game::EntityPtr & o)
{
	return o == nullptr;
}

void game::GameMap::draw(grph::ILib& graphic)
{
	for (auto& itY : _maping) {
		for (auto& itX : itY) {
			for (auto& item : itX) {
				if (item)
					drawEntity(*item, graphic);
			}
		}
	}
}

unsigned int game::GameMap::getWidth() const
{
	return _width;
}

unsigned int game::GameMap::getHeight() const
{
	return _height;
}

bool game::GameMap::addEntity(game::EntityPtr& entity)
{
	int x = entity->getX();
	int y = entity->getY();

	if (not BorderJumpXY(x, y, entity->canBorderJump()))
		return false;
	auto find = std::find(_maping[y][x].begin(), _maping[y][x].end(), entity);
	if (find != _maping[y][x].end())
		return false;
	_maping[y][x].push_back(entity);
	return true;
}

bool game::GameMap::removeEntity(game::EntityPtr& entity)
{
	int x = entity->getX();
	int y = entity->getY();

	if (not BorderJumpXY(x, y, entity->canBorderJump()))
		return false;
	auto find = std::find(_maping[y][x].begin(), _maping[y][x].end(), entity);
	if (find == _maping[y][x].end())
		return false;
	*find = nullptr;
	return true;
}

bool game::GameMap::moveEntity(game::EntityPtr& entity)
{
	int newX = entity->getX();
	int newY = entity->getY();
	int lastX = entity->getLastX();
	int lastY = entity->getLastX();

	if (newX == lastX and newY == lastY)
		return false;
	if (not BorderJumpXY(newX, newY, entity->canBorderJump()))
		return false;
	if (not BorderJumpXY(lastX, lastY, entity->canBorderJump()))
		return false;
	if (newX == lastX and newY == lastY)
		return false;
	auto find = std::find(_maping[lastY][lastX].begin(), _maping[lastY][lastX].end(), entity);
	if (find == _maping[lastY][lastX].end())
		return false;
	_maping[newY][newX].push_back(entity);
	_maping[lastY][lastX].erase(find);
	return true;
}

bool game::GameMap::moveEntity(game::IEntity& entity)
{
	int newX = entity.getX();
	int newY = entity.getY();
	int lastX = entity.getLastX();
	int lastY = entity.getLastY();

	if (not BorderJumpXY(newX, newY, entity.canBorderJump()))
		return false;
	if (not BorderJumpXY(lastX, lastY, entity.canBorderJump()))
		return false;
	if (newX == lastX and newY == lastY)
		return false;
	for (auto& item : _maping[lastY][lastX]) {
		if (item and *item == entity) {
			auto find = std::find(_maping[lastY][lastX].begin(), _maping[lastY][lastX].end(), item);
			_maping[newY][newX].push_back(item);
			_maping[lastY][lastX].erase(find);
		}
	}
	return true;
}
