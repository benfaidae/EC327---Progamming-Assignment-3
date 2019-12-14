#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <iostream>

class Vector2D {

public: 
	
	double x;
	double y;

	Vector2D();
	Vector2D(double in_x, double in_y);

	friend Vector2D operator*(Vector2D const& v1, const double & d);
	friend Vector2D operator/(Vector2D const& v1, const double & d);
	friend std::ostream& operator<<(std::ostream& os, const Vector2D & v1);

};

#endif