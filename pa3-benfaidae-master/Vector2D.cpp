#include "Vector2D.h"
#include <iostream>

using namespace std;

Vector2D::Vector2D() {
	x = 0.0;
	y = 0.0;
}

Vector2D::Vector2D(double in_x, double in_y) {
	x = in_x;
	y = in_y;
}

Vector2D operator*(Vector2D const& v1, const double & d) {
	Vector2D vMult;
	vMult.x = v1.x * d;
	vMult.y = v1.y * d;
	return vMult;
}

Vector2D operator/(Vector2D const& v1, const double & d) {
	Vector2D vDiv;
	vDiv.x = v1.x / d;
	vDiv.y = v1.y / d;
	return vDiv;
}

std::ostream& operator<<(std::ostream& os, const Vector2D & v1) {
	os << "<" << v1.x << ", " << v1.y << ">" << endl;
	return os;
}
