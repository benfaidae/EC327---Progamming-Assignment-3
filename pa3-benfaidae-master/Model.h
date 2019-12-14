#ifndef MODEL_H
#define MODEL_H

#include "GameObject.h"
#include "Pokemon.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
#include <iostream>

class View;

class Model{

private:
	int time;

	GameObject** object_ptrs;
	int num_objects;

	Pokemon** pokemon_ptrs;
	int num_pokemon;

	PokemonCenter** center_ptrs;
	int num_centers;

	PokemonGym** gym_ptrs;
	int num_gyms;

	Model(Model &);

public:
	Model();
	~Model();

	Pokemon * GetPokemonPtr(int id);
	PokemonCenter * GetPokemonCenterPtr(int id);
	PokemonGym * GetPokemonGymPtr(int id);
	bool Update();
	void Display(View& view);
	void ShowStatus();

};

#endif