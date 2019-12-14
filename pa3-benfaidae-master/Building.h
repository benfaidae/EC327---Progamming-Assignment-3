#ifndef BUILDING_H
#define BUILDING_H

#include "GameObject.h"
#include "Point2D.h"
#include <iostream>

class Point2D;
class GameObject;

class Building : public GameObject {

private:
	unsigned int pokemon_count;

public:
	Building();
	Building(char in_code, int in_id, Point2D in_loc);

	void AddOnePokemon();
	void RemoveOnePokemon();
	void ShowStatus();
	bool ShouldBeVisible();

};

#endif