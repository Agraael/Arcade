/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 28/03/18 
*/

#include "Vector2D.hpp"

math::Vector2D::Vector2D(double x, double y)
	: _x(x), _y(y), _radiant(std::atan2(y, x))
{}

math::Vector2D::Vector2D(double radiant)
	: _x(0), _y(0),
	_radiant(radiant)
{
	calcXY(_radiant);
}

math::Vector2D::Vector2D(int angle)
	: _x(0), _y(0),
	_radiant(math::Vector2D::AngleToRadiant(angle))
{
	calcXY(_radiant);
}

double math::Vector2D::AngleToRadiant(int angle) noexcept
{
	return angle * (M_PI / 180);
}

int math::Vector2D::RadiantToAngle(double radiant) noexcept
{
	return static_cast<int>(round(radiant * (180 / M_PI)));
}

double math::Vector2D::getX() const
{
	return _x;
}

void math::Vector2D::setX(double x)
{
	_x = x;
	calcRadiant(_x, _y);
}

double math::Vector2D::getY() const
{
	return _y;
}

void math::Vector2D::setY(double y)
{
	_y = y;
	calcRadiant(_x, _y);
}

double math::Vector2D::getRadiant() const
{
	return _radiant;
}

int math::Vector2D::getAngle() const
{
	return math::Vector2D::RadiantToAngle(_radiant);
}

void math::Vector2D::rotateXY(double radiant)
{
	double old_x = _x;
	double old_y = _y;

	_x = (std::cos(radiant) * old_x) - (std::sin(radiant) * old_y);
	_y = (std::sin(radiant) * old_x) + (std::cos(radiant) * old_y);
	_x = round(_x * 10000) / 10000;
	_y = round(_y * 10000) / 10000;
}

void math::Vector2D::calcXY(double radiant)
{
	_x = std::cos(radiant);
	_y = std::sin(radiant);
	_x = round(_x * 10000) / 10000;
	_y = round(_y * 10000) / 10000;
}

void math::Vector2D::calcRadiant(double x, double y)
{
	_radiant = std::atan2(y,x);
}



void math::Vector2D::rotate(double radiant)
{
	rotateXY(radiant);
	calcRadiant(_x, _y);
}

void math::Vector2D::rotate(int angle)
{
	rotateXY(math::Vector2D::AngleToRadiant(angle));
	calcRadiant(_x, _y);
}

void math::Vector2D::setRadiant(double radiant)
{
	rotateXY(radiant - _radiant);
	calcRadiant(_x, _y);
}

void math::Vector2D::setAngle(int angle)
{
	rotateXY(math::Vector2D::AngleToRadiant(angle - getAngle()));
	calcRadiant(_x, _y);
}

void math::Vector2D::mult(double nb)
{
	_x *= nb;
	_y *= nb;
}

void math::Vector2D::div(double nb)
{
	_x /= nb;
	_y /= nb;
}

void math::Vector2D::add(double nb)
{
	_x += nb;
	_y += nb;
}

void math::Vector2D::sub(double nb)
{
	_x -= nb;
	_y -= nb;
}

bool math::Vector2D::double_equals(double a, double b, double epsilon)
{
	return std::abs(a - b) < epsilon;
}

double math::Vector2D::getMag() const
{
	return std::sqrt(_x * _x + _y *_y);
}


void math::Vector2D::setMag(double mag)
{
	normalize();
	mult(mag);
}

void math::Vector2D::normalize()
{
	double m = getMag();
	if (not double_equals(m, 0.0) and not double_equals(m, 1.0))
		div(m);
}

void math::Vector2D::add(math::Vector2D const& vec)
{
	_x += vec._x;
	_y += vec._y;
	calcRadiant(_x, _y);
}

void math::Vector2D::sub(math::Vector2D const& vec)
{
	_x -= vec._x;
	_y -= vec._y;
	calcRadiant(_x, _y);
}

void math::Vector2D::reset(double x, double y)
{
	_x = x;
	_y = y;
	calcRadiant(_x, _y);
}

void math::Vector2D::reset(double radiant)
{
	_radiant = radiant;
	calcXY(_radiant);
}

void math::Vector2D::reset(int angle)
{
	_radiant = math::Vector2D::AngleToRadiant(angle);
	calcXY(_radiant);
}

std::ostream& math::operator<<(std::ostream& os, Vector2D const& d)
{
	os << "[" << d.getX() << "," << d.getY() << "][" << d.getAngle() <<"°]";
	return os;
}


