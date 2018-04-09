/*
** EPITECH SnakeDataBridge::PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 01/04/18 
*/

#include <DataBridge.hpp>
#include "Entity.hpp"

unsigned int game::Entity::genID()
{
	static unsigned int NB = 0;
	NB++;
	return NB;
}

game::Entity::Entity(int x, int y, game::GameMap& map, game::DataBridge& data,
                     bool visibility, bool kinematic, bool borderJump, unsigned int layout,
                     std::string const& type, std::string const& spriteConfig)
	: _newCoord(x, y), _lastCoord(x, y), _bornCoord(x, y),
	_map(map), _data(data), _force(0,0), _sprite(nullptr), _visibility(visibility), _kinematic(kinematic),
	_borderJump(borderJump), _layout(layout), _type(type)
{
	_id = genID();
	if (spriteConfig.empty())
		_sprite = std::make_unique<grph::Sprite>("", 0x00FFFFFF, 0);
	else
		_sprite = std::make_unique<grph::Sprite>(spriteConfig);
}

bool game::Entity::move()
{
	if(not _alive or not _active)
		return false;
	_newCoord.X += (_force.getX());
	_newCoord.Y += (_force.getY());
	return true;
}

bool game::Entity::translate(math::Vector2D const& vec)
{
	if(not _alive or not _active)
		return false;
	_newCoord.X += (vec.getX());
	_newCoord.Y += (vec.getY());
	return true;
}

game::EntityVec* game::Entity::getColisions()
{
	return _lastColision;
}

bool game::Entity::checkColisions(int x, int y)
{
	EntityVec* entities;

	if (not _kinematic)
		return false;
	entities =_map.getAllAt(x, y, _borderJump);
	if (entities == nullptr) {
		return true;
	}
	return std::find_if(entities->begin(), entities->end(),
	[this](EntityPtr const& m)-> bool {return m && m->getId() != this->getId()&& m->isKinematic();}) != entities->end();
}

bool game::Entity::doColisions()
{
	math::Vector2D vec(_force.getX(), _force.getY());
	XYCoord coord(_lastCoord.X, _lastCoord.Y);
	int startX = getLastX();
	int startY = getLastY();
	int endX = getX();
	int endY = getY();

	vec.normalize();
	while (startX != endX or startY != endY) {
		if (checkColisions(startX + static_cast<int>(vec.getX()),
			startY + static_cast<int>(vec.getY()))) {
			_newCoord.X = startX;
			_newCoord.Y = startY;
			_lastColision = _map.getAllAt(startX + static_cast<int>(vec.getX()),
				startY + static_cast<int>(vec.getY()), _borderJump);
			return true;
		}
		coord.X += vec.getX();
		coord.Y += vec.getY();
		startX = static_cast<int>(coord.X);
		startY = static_cast<int>(coord.Y);
	}
	if (checkColisions(endX, endY)) {
		_newCoord.X = startX - vec.getX();
		_newCoord.Y = startY - vec.getY();
		_lastColision = _map.getAllAt(startX + static_cast<int>(vec.getX()),
			startY + static_cast<int>(vec.getY()), _borderJump);
		return true;
	}
	_lastColision = nullptr;
	return false;
}

bool game::Entity::doContact()
{
	math::Vector2D vec(_force.getX(), _force.getY());
	XYCoord coord(_lastCoord.X, _lastCoord.Y);
	int startX = getLastX();
	int startY = getLastY();
	int endX = getX();
	int endY = getY();

	vec.normalize();
	_contacts.clear();
	while (startX != endX or startY != endY) {
		auto ptr =  _map.getAllAt(startX, startY, _borderJump);
		if (ptr)
			_contacts.push_back(ptr);
		coord.X += vec.getX();
		coord.Y += vec.getY();
		startX = static_cast<int>(coord.X);
		startY = static_cast<int>(coord.Y);

	}
	auto ptr =  _map.getAllAt(startX, startY, _borderJump);
	if (ptr)
		_contacts.push_back(ptr);
	return true;
}

void game::Entity::rollBack()
{
	_newCoord.X = _lastCoord.X;
	_newCoord.Y = _lastCoord.Y;
}

void game::Entity::update()
{
	if (not _alive or not _active)
		return;
	move();
	if (not math::Vector2D::double_equals(_force.getMag(), 0)){
		doColisions();
		doContact();
	}
	_map.moveEntity(*this);
	_lastCoord = _newCoord;
}

void game::Entity::reset()
{
	_alive = true;
	_newCoord.X = _bornCoord.X;
	_newCoord.Y = _bornCoord.Y;
	_lastCoord.X = _bornCoord.X;
	_lastCoord.Y = _bornCoord.Y;
}

void game::Entity::kill()
{
	_alive = false;
}

void game::Entity::resurect()
{
	_alive = true;
}

bool game::Entity::isAlive() const
{
	return _alive;
}

bool game::Entity::canBorderJump() const
{
	return _borderJump;
}

void game::Entity::setBorderJump(bool val)
{
	_borderJump = val;
}

bool game::Entity::isVisible() const
{
	if (not _alive)
		return false;
	return _visibility;
}

void game::Entity::setVisibility(bool val)
{
	_visibility = val;
}

bool game::Entity::isKinematic() const
{
	if (not _alive)
		return false;
	return _kinematic;
}

void game::Entity::setKinematic(bool val)
{
	_kinematic = val;
}

unsigned int game::Entity::getLayout() const
{
	return _layout;
}

void game::Entity::setLayout(unsigned int val)
{
	_layout = val;
}

std::string const& game::Entity::getType() const
{
	return _type;
}

unsigned int game::Entity::getId() const
{
	return _id;
}

int game::Entity::getX() const
{
	return static_cast<int>(_newCoord.X);
}

int game::Entity::getY() const
{
	return static_cast<int>(_newCoord.Y);
}

int game::Entity::getLastX() const
{
	return static_cast<int>(_lastCoord.X);
}

int game::Entity::getLastY() const
{
	return static_cast<int>(_lastCoord.Y);
}


math::Vector2D& game::Entity::vector()
{
	return _force;
}

void game::Entity::changeVector(math::Vector2D const& vec)
{
	_force.setX(vec.getX());
	_force.setY(vec.getY());
}

void game::Entity::setSprite(std::string const& spriteConfig)
{
	if (spriteConfig.empty())
		_sprite = std::make_unique<grph::Sprite>("", 0x00FFFFFF, 0);
	else
		_sprite = std::make_unique<grph::Sprite>(spriteConfig);
}

grph::ISprite& game::Entity::getSprite() const
{
	return *_sprite;
}

bool game::Entity::operator==(game::IEntity const& rhs) const
{
	return this->getId() == rhs.getId();
}

std::vector<game::EntityVec*>& game::Entity::getContacts()
{
	return _contacts;
}

bool game::Entity::teleport(int x, int y)
{
	_newCoord.X = x;
	_newCoord.Y = y;
	return  true;
}

void game::Entity::activate()
{
	_active = true;
}

void game::Entity::deactivate()
{
	_active = false;
}

bool game::Entity::isActive() const
{
	return _active;
}
