/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 30/03/18 
*/

#ifndef LIBCACA_IENTITY_HPP
#define LIBCACA_IENTITY_HPP

#include <GameMap.hpp>
#include <memory>
#include <Sprite.hpp>
#include <functional>
#include "Vector2D.hpp"
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

	struct XYCoord
	{
		XYCoord(double x, double y) : X(x), Y(y) {}

		bool operator==(XYCoord const& rhs) const {
			return std::tie(X, Y) == std::tie(rhs.X, rhs.Y);
		}

		bool operator!=(XYCoord const& rhs) const {
			return !(rhs == *this);
		}
		double X;
		double Y;
	};

	class IEntity
	{
	public:
		virtual ~IEntity() = default;
		virtual bool move() = 0;
		virtual bool translate(math::Vector2D const& vec) = 0;
		virtual bool teleport(int x, int y) = 0;
		virtual game::EntityVec* getColisions() = 0;
		virtual bool doColisions() = 0;
		virtual bool doContact() = 0;
		virtual std::vector<game::EntityVec*>& getContacts() = 0;
		virtual void update() = 0;
		virtual void rollBack() = 0;

		virtual void reset() = 0;
		virtual void kill() = 0;
		virtual void resurect() = 0;
		virtual bool isAlive() const = 0;
		virtual void activate() = 0;
		virtual void deactivate() = 0;
		virtual bool isActive() const = 0;

		virtual bool canBorderJump() const = 0;
		virtual void setBorderJump(bool val) = 0;
		virtual bool isVisible() const = 0;
		virtual void setVisibility(bool val) = 0;
		virtual bool isKinematic() const = 0;
		virtual void setKinematic(bool val) = 0;
		virtual unsigned int getLayout() const = 0;
		virtual void setLayout(unsigned int val) = 0;

		virtual std::string const& getType() const = 0;
		virtual unsigned int getId() const = 0;
		virtual int getX() const = 0;
		virtual int getY() const = 0;
		virtual int getLastX() const = 0;
		virtual int getLastY() const = 0;

		virtual math::Vector2D& vector() = 0;
		virtual void changeVector(math::Vector2D const& vec) = 0;
		virtual void setSprite(std::string const& spriteConfig) = 0;
		virtual grph::ISprite& getSprite() const = 0;

		virtual bool operator==(game::IEntity const& rhs) const = 0;
	private:
	};
}

#endif //LIBCACA_IENTITY_HPP
