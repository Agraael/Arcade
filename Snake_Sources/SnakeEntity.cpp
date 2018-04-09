/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 04/04/18 
*/

#include "SnakeEntity.hpp"
#include "DataBridge.hpp"
#include "SnakeBodyEntity.hpp"

snake::SnakeEntity::SnakeEntity(int x, int y, game::GameMap& map, game::DataBridge& data)
	: Entity(x, y, map, data, true, true, true, 0, "snake", "./Snake_Sources/spriteSnake/snake")
{
	_snakeData = dynamic_cast<snake::SnakeDataBridge*>(&data);
	_force.reset(-90);
	_force.setMag(0.17);
	_snakePart.push_back(std::make_shared<snake::SnakeBodyEntity>(getX(), getY(), _map, _data));
	_snakePart.push_back(std::make_shared<snake::SnakeBodyEntity>(getX(), getY(), _map, _data));
	_snakePart.push_back(std::make_shared<snake::SnakeBodyEntity>(getX(), getY(), _map, _data));
	for (auto& part : _snakePart) {
		_map.addEntity(part);
	}
}

void snake::SnakeEntity::update()
{
	if (not _active or not _alive)
		return;;
	rotate();
	Entity::update();
	checkFoodContact();
	putTailPositions();
	auto it = _snakePart.begin();
	auto cnt = 0;
	for (auto& po : _tailPos) {
		if (it != _snakePart.end() && cnt != 0) {
			(*it++)->teleport(po.first, po.second);
		}
		++cnt;
	}
	for (auto& part : _snakePart) {
		part->update();
	}
	if (_lastColision != nullptr)
		deactivate();
}

void snake::SnakeEntity::putTailPositions()
{
	math::Vector2D vec(_force.getX(), _force.getY());
	game::XYCoord coord(_lastCoord.X, _lastCoord.Y);
	int startX = getLastX();
	int startY = getLastY();
	int endX = getX();
	int endY = getY();

	vec.normalize();
	while (startX != endX or startY != endY) {
		std::pair<int, int> pos(startX, startY);
		if ( std::find(_tailPos.begin(), _tailPos.end(), pos) == _tailPos.end())
			_tailPos.emplace_front(pos);
		if (_tailPos.size() > _snakeSize)
			_tailPos.pop_back();
		coord.X += vec.getX();
		coord.Y += vec.getY();
		startX = static_cast<int>(coord.X);
		startY = static_cast<int>(coord.Y);
	}
	std::pair<int, int> pos(startX, startY);
	if ( std::find(_tailPos.begin(), _tailPos.end(), pos) == _tailPos.end())
		_tailPos.emplace_front(pos);
	if (_tailPos.size() > _snakeSize)
		_tailPos.pop_back();
}

void snake::SnakeEntity::checkFoodContact()
{
	for (auto& contact : _contacts) {
		for (auto& item : (*contact)) {
			if (item && item->getType() == "food") {
				item->update();
				_snakeData->addFood();
				_snakeSize += 1;
				game::EntityPtr ptr = std::make_shared<snake::SnakeBodyEntity>(getX(), getY(), _map, _data);
				_snakePart.push_back(ptr);
				_map.addEntity(ptr);
			}
		}
	}
}

void snake::SnakeEntity::rotate()
{
	if ((_snakeData->getEvent()).type == grph::RIGHT && _force.getAngle() != 180) {
		_force.setAngle(0);
		_sprite->setPath("Snake_Sources/snakeTextures/snakeHeadRight.png");
	}
	if ((_snakeData->getEvent()).type == grph::LEFT && _force.getAngle() != 0) {
		_force.setAngle(180);
		_sprite->setPath("Snake_Sources/snakeTextures/snakeHeadLeft.png");
	}
	if ((_snakeData->getEvent()).type == grph::UP && _force.getAngle() != 90) {
		_force.setAngle(-90);
		_sprite->setPath("Snake_Sources/snakeTextures/snakeHeadFront.png");
	}
	if ((_snakeData->getEvent()).type == grph::DOWN && _force.getAngle() != -90) {
		_force.setAngle(90);
		_sprite->setPath("Snake_Sources/snakeTextures/snakeHeadBack.png");
	}
	if ((_snakeData->getEvent()).key == 'z')
		_force.setMag(1);
	else if ((_snakeData->getEvent()).key == 's')
		_force.setMag(0.005);
	else
		_force.setMag(0.17);

}
