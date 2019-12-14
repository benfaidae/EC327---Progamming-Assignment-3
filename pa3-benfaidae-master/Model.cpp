#include "Model.h"
#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Pokemon.h"
#include "View.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Model::Model() {
	time = 0; 
	this -> num_objects = 6;
	this -> num_pokemon = 2;
	this -> num_centers = 2;
	this -> num_gyms = 2;

	object_ptrs = new GameObject* [num_objects];
	pokemon_ptrs = new Pokemon* [num_pokemon];
	center_ptrs = new PokemonCenter* [num_centers];
	gym_ptrs = new PokemonGym* [num_gyms];

	pokemon_ptrs[0] = new Pokemon("Pikachu", 1, 'P' , 2, Point2D(5,1));
	pokemon_ptrs[1] = new Pokemon("Bulbasaur", 2, 'P' ,1, Point2D(10, 1));

	center_ptrs[0] = new PokemonCenter(1, 1, 100, Point2D(1, 20));
	center_ptrs[1] = new PokemonCenter(2, 2, 200, Point2D(10, 20));

	gym_ptrs[0] = new PokemonGym(10, 1, 2, 3, 1, Point2D());
	gym_ptrs[1] = new PokemonGym(20, 5, 7.5, 8, 2, Point2D(5, 5));

	object_ptrs[0] = pokemon_ptrs[0];
	object_ptrs[1] = pokemon_ptrs[1];
	object_ptrs[2] = center_ptrs[0];
	object_ptrs[3] = center_ptrs[1];
	object_ptrs[4] = gym_ptrs[0];
	object_ptrs[5] = gym_ptrs[1];

	cout << "Model default constructed." << endl;

}

Model::~Model() {
	for(int i = 0; i < num_objects; i++) {
		delete object_ptrs[i];
	}
	cout << "Model destructed." << endl;
}

Pokemon* Model::GetPokemonPtr(int id) {
	for(int i = 0; i < num_pokemon; i++) {
		if((*pokemon_ptrs[i]).GetId() == id)
			return pokemon_ptrs[i];
	}
	return NULL;
}

PokemonCenter* Model::GetPokemonCenterPtr(int id) {
	for(int i = 0; i < num_centers; i++) {
		if((*center_ptrs[i]).GetId() == id)
			return center_ptrs[i];
	}
	return NULL;
}

PokemonGym* Model::GetPokemonGymPtr(int id) {
	for(int i = 0; i < num_gyms; i++) {
		if((*gym_ptrs[i]).GetId() == id)
			return gym_ptrs[i];
	}
	return NULL;
}

bool Model::Update() {
	time++;
	bool beaten = true;
	int count = 0;

	for(int i = 0; i < num_gyms && beaten; i++) {
		if((*gym_ptrs[i]).IsBeaten() == true) {
			cout << "GAME OVER: You win! All Pokemon Gyms beaten!" << endl;
			exit(0);
		}
		else {
			beaten = false;
		}
	}

	for(int i = 0; i < num_pokemon && beaten; i++) {
		if((*pokemon_ptrs[i]).IsExhausted() == true) {
			cout << "GAME OVER: You lost! All of your Pokemon are tired!" << endl;
			exit(0);
		}
		else {
			beaten = false;
		}
	}
	for (int i = 0; i < num_objects; i++){
        if((*object_ptrs[i]).Update()) {
            for (int j = i + 1; j < num_objects; j++)
            {
                (*object_ptrs[j]).Update();
            }
            return true;
        }
    }
    return false;
}


void Model::Display(View& view){
	view.Clear();
	for(int i = 0; i < view_maxsize/2 + 1; i++) {
		for(int j = 0; j < view_maxsize/2 +1; j++) {
			char* mgrid = view.grid[i][j];
			*mgrid = '.';
			*(mgrid + 1) = ' ';
		}
	}
	for(int i = 0; i < num_objects; i++) {
		view.Plot(object_ptrs[i]);
	}
	view.Draw();
}
void Model::ShowStatus() {
	cout << "Time: " << time << endl;
	for(int i = 0; i < num_pokemon; i++) {
		(*pokemon_ptrs[i]).ShowStatus();
	}
	
	for(int i = 0; i < num_centers; i++) {
		(*center_ptrs[i]).ShowStatus();
	}
	
	for(int i = 0; i < num_gyms; i++) {
		(*gym_ptrs[i]).ShowStatus();
	}
}
