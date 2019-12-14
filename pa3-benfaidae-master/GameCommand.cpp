#include "GameCommand.h"
#include "Model.h"
#include "View.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "Pokemon.h"
#include "GameObject.h"
#include <iostream>


using namespace std;

void DoMoveCommand(Model & model, int pokemon_id, Point2D p1) {
	Pokemon* pokemon_ptr = model.GetPokemonPtr(pokemon_id);
	(*pokemon_ptr).StartMoving(p1);
	cout << "Moving " << pokemon_id << " to " << p1 << "." << endl; 
}

void DoMoveToCenterCommand(Model & model, int pokemon_id, int center_id) {
	Pokemon* pokemon_ptr = model.GetPokemonPtr(pokemon_id);
	PokemonCenter* center_ptr = model.GetPokemonCenterPtr(center_id);
	Point2D destination = center_ptr -> GetLocation();
	(*pokemon_ptr).StartMoving(destination);
	cout << "Moving " << pokemon_id << " to " << destination << "." << endl;
}

void DoMoveToGymCommand(Model & model, int pokemon_id, int gym_id) {
	Pokemon* pokemon_ptr = model.GetPokemonPtr(pokemon_id);
	PokemonGym* gym_ptr = model.GetPokemonGymPtr(gym_id);
	(*pokemon_ptr).StartMovingToGym(gym_ptr);
	Point2D destination = gym_ptr -> GetLocation();
	cout << "Moving " << pokemon_id << " to " << destination << "." << endl;
}

void DoStopCommand(Model & model, int pokemon_id) {
	Pokemon* pokemon_ptr = model.GetPokemonPtr(pokemon_id);
	(*pokemon_ptr).Stop();
}

void DoTrainInGymCommand(Model & model, int pokemon_id, unsigned int training_units){
	Pokemon* pokemon_ptr = model.GetPokemonPtr(pokemon_id);
	(*pokemon_ptr).StartTraining(training_units);
}

void DoRecoverInCenterCommand(Model & model, int pokemon_id, unsigned int stamina_points){
	Pokemon* pokemon_ptr = model.GetPokemonPtr(pokemon_id);
	(*pokemon_ptr).StartRecoveringStamina(stamina_points);
}

void DoGoCommand(Model & model, View & view) {
	cout << "Advancing one tick." << endl;
	model.Update();
	model.ShowStatus();
}

void DoRunCommand(Model & model, View & view) {
	cout << "Advancing one tick." << endl;
}