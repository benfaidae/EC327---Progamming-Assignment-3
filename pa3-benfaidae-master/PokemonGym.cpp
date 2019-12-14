#include "PokemonGym.h"
#include <iostream>

using namespace std;

PokemonGym::PokemonGym() : Building() {
	display_code = 'G';
	state = NOT_BEATEN;
	max_number_of_training_units = 10;
	num_training_units_remaining = max_number_of_training_units;
	stamina_cost_per_training_unit = 1;
	dollar_cost_per_training_unit = 1.0;
	experience_points_per_training_unit = 2;
	cout << "PokemonGym default constructed." << endl;
}

PokemonGym::PokemonGym(unsigned int max_training_units, unsigned int stamina_cost, 
	double dollar_cost, unsigned int exp_points_per_unit, int in_id, Point2D in_loc) : Building('G', in_id, in_loc) {
	max_number_of_training_units = max_training_units;
	stamina_cost_per_training_unit = stamina_cost; 
	experience_points_per_training_unit = exp_points_per_unit;
	dollar_cost_per_training_unit = dollar_cost;
	state = NOT_BEATEN;
	num_training_units_remaining = max_number_of_training_units; 
	cout << "PokemonGym constructed." << endl;
}

double PokemonGym::GetDollarCost(unsigned int unit_qty) {
	double tcost = (1 * unit_qty);
	return tcost;
}

unsigned int PokemonGym::GetStaminaCost(unsigned int unit_qty) {
	int scost = (1 * unit_qty);
	return scost;
}

unsigned int PokemonGym::GetNumTrainingUnitsRemaining() {
	return num_training_units_remaining;
}

bool PokemonGym::IsAbleToTrain(unsigned int unit_qty, double budget, unsigned int stamina) {
	int scost = GetStaminaCost(unit_qty);
	int tcost = GetDollarCost(unit_qty);
	if(scost <= budget && tcost <= budget) {
		return true; 
	}
	else {
		return false;
	}
}

unsigned int PokemonGym::TrainPokemon(unsigned int training_units) {
	unsigned int expTrain;
	GetNumTrainingUnitsRemaining();
	num_training_units_remaining -= training_units; 
	unsigned int gymTrainingUnits = max_number_of_training_units;
	if(training_units > gymTrainingUnits) {
		expTrain = training_units * experience_points_per_training_unit;
	}
	else {
		expTrain = num_training_units_remaining * experience_points_per_training_unit;
	}
	return expTrain;
}

bool PokemonGym::Update() {
	GetNumTrainingUnitsRemaining();
	if(num_training_units_remaining == 0) {
		state = BEATEN;
		display_code = 'g';
		cout << display_code << " " << id_num << " has been beaten." << endl;
		return true;
	}
	else 
		return false;
	
}

bool PokemonGym::IsBeaten() {
	if(num_training_units_remaining == 0) 
		return true;
	
	else 
		return false;
}

void PokemonGym::ShowStatus() {
	cout << "Pokemon Gym Status: " << display_code << id_num << " located at " << location <<endl;
	Building::ShowStatus();
	cout << "	Max number of training units: "<< max_number_of_training_units << endl;
	cout << "	Stamina cost per training unit: " << stamina_cost_per_training_unit << endl;
	cout << "	Pokemon dollar per training unit: " << dollar_cost_per_training_unit << endl;
	cout << "	Experience points per training unit: " << experience_points_per_training_unit << endl;
	cout << "	" << num_training_units_remaining << " training unit(s) are remaining for this gym" << endl;


}
