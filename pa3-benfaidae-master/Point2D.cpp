#include "Point2D.h"
#include <cmath>
#include <iostream>

using namespace std;

Point2D::Point2D() {
	x = 0.0; 
	y = 0.0;
}

Point2D::Point2D(double in_x, double in_y) {
	x = in_x;
	y = in_y;
}

std::ostream& operator<<(std::ostream& os, const Point2D & p1) {
	os << "(" << p1.x << ", " << p1.y << ")" << endl;
	return os;
}

Point2D operator+(Point2D & p1, Vector2D & v1) {
	Point2D pAdd;
	pAdd.x = p1.x + v1.x;
	pAdd.y = p1.y + v1.y;
	return pAdd;
}

Vector2D operator-(Point2D & p1, Point2D & p2) {
	Vector2D vSubt;
	vSubt.x = p1.x - p2.x;
	vSubt.y = p1.y - p2.y;
	return vSubt;
}

double GetDistanceBetween(Point2D p1, Point2D p2) {
	double xDist = p2.x - p1.x; 
	double yDist = p2.y - p1.y;

	xDist *= xDist;
	yDist *= yDist;

	double distance = sqrt(xDist + yDist);
	return distance;
}



