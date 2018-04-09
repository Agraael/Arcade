/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 01/04/18 
*/

#ifndef LIBCACA_AENTITY_HPP
#define LIBCACA_AENTITY_HPP

#include "IEntity.hpp"
#include "DataBridge.hpp"

namespace game
{
	class Entity
		: public game::IEntity
	{
	public:
		Entity(int x, int y, game::GameMap& map, DataBridge& data,
		       bool visibility = true, bool kinematic = false, bool borderJump = false, unsigned int layout = 0,
		       std::string const& type = "entity", std::string const& spriteConfig = "");
		Entity(Entity const&) = delete;
		~Entity() override = default;
		Entity& operator=(Entity const&) = delete;

		bool move() final;
		bool translate(math::Vector2D const& vec) final;
		bool teleport(int x, int y) final;
		game::EntityVec* getColisions() final;
		bool doColisions() final;
		bool doContact() final;
		std::vector<game::EntityVec*>& getContacts() final;
		void rollBack() final;
		void update() override;

		void reset() final;
		void kill() final;
		void resurect() final;
		bool isAlive() const final;
		void activate() final;
		void deactivate() final;
		bool isActive() const final;

		bool canBorderJump() const final;
		void setBorderJump(bool val) final;
		bool isVisible() const final;
		void setVisibility(bool val) final;
		bool isKinematic() const final;
		void setKinematic(bool val) final;
		unsigned int getLayout() const final;
		void setLayout(unsigned int val) final;

		std::string const& getType() const final;
		unsigned int getId() const final;
		int getX() const final;
		int getY() const final;
		int getLastX() const final;
		int getLastY() const final;

		math::Vector2D& vector() final;
		void changeVector(math::Vector2D const& vec) final;
		void setSprite(std::string const& spriteConfig) final;
		grph::ISprite& getSprite() const final;

		bool operator==(game::IEntity const& rhs) const final;

	protected:
		XYCoord _newCoord;
		XYCoord _lastCoord;
		XYCoord _bornCoord;
		game::GameMap& _map;
		game::DataBridge& _data;
		math::Vector2D _force;
		std::unique_ptr<grph::ISprite> _sprite;
		bool _visibility;
		bool _kinematic;
		bool _borderJump;
		unsigned int _layout;
		bool _alive = true;
		unsigned int _id = 0;
		std::string const _type;
		EntityVec* _lastColision = nullptr;
		std::vector<game::EntityVec*> _contacts = std::vector<game::EntityVec*>();
		unsigned int genID();
		bool checkColisions(int x, int y);
		bool _active = true;
	};
}

#endif //LIBCACA_AENTITY_HPP
