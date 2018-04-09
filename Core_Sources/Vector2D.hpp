/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 28/03/18 
*/

#ifndef LIBCACA_MATHVECTOR2D_HPP
#define LIBCACA_MATHVECTOR2D_HPP

#include <cmath>
#include <complex>
#include <ostream>

namespace math
{
	class Vector2D
	{
	public:
		explicit Vector2D(double x, double y);      // create a vector with x and y , and calc the radiant with it
		explicit Vector2D(double radiant);          // create a vector with a radiant angle, x and y are set with cosinus and sinus
		explicit Vector2D(int angle);               // same but degre angle , with is converted to radiant

		void reset(double x, double y);
		void reset(double radiant);
		void reset(int angle);
		Vector2D(Vector2D const&) = default;
		~Vector2D() = default;
		Vector2D& operator=(Vector2D const&) = default;

		static double AngleToRadiant(int angle) noexcept;
		static int RadiantToAngle(double radiant) noexcept ;

		double getX() const;
		void setX(double x);
		double getY() const;
		void setY(double y);
		double getRadiant() const;
		void setRadiant(double radiant);
		int getAngle() const;
		void setAngle(int angle);
		void rotate(double radiant);
		void rotate(int angle);
		void normalize();
		double getMag() const;             // calc the vector magnitude(lenght)
		void setMag(double mag);

		void mult(double nb);
		void div(double nb);
		void add(double nb);
		void sub(double nb);

//		void mult(Vector2D const& vec);
//		void div(Vector2D const& vec);
		void add(Vector2D const& vec);
		void sub(Vector2D const& vec);

		static bool double_equals(double a, double b, double epsilon = 0.001);
	private:
		double _x;
		double _y;
		double _radiant;

		void rotateXY(double radiant);
		void calcXY(double radiant);
		void calcRadiant(double x, double y);
	};

	std::ostream& operator<<(std::ostream& os, Vector2D const& d);
}

#endif //LIBCACA_MATHVECTOR2D_HPP