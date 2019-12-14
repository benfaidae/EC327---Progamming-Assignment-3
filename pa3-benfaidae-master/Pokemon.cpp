#include "Pokemon.h"
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

Pokemon::Pokemon() : GameObject('P') {
	this -> speed = 5; 
	this -> is_in_gym = false; 
	this -> is_in_center = false; 
	this -> stamina = 20; 
	this -> pokemon_dollars = 0; 
	this -> training_units_to_buy = 0;
    this -> stamina_points_to_buy = 0;
   	this -> current_center = NULL;
	this -> current_gym = NULL;
	this -> location = Point2D();

	cout << "Pokemon default constructed." << endl;
}

Pokemon::Pokemon(char in_code) : GameObject(in_code){
	this -> speed = 5; 
	this -> is_in_gym = false; 
	this -> is_in_center = false; 
	this -> stamina = 20; 
	this -> pokemon_dollars = 0; 
	this -> training_units_to_buy = 0;
    this -> stamina_points_to_buy = 0;
	this -> state = STOPPED;
	this -> display_code = in_code;
	this -> current_center = NULL;
	this -> current_gym = NULL;
	this -> location = Point2D();

	cout << "Pokemon constructed." << endl;
}

Pokemon::Pokemon(std::string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc) : GameObject(in_loc, in_id, in_code) {
	this -> speed = in_speed; 
	this -> stamina = 20; 
	this -> name = in_name; 
	this -> id_num = in_id;
	this -> display_code = in_code;
	this -> current_center = NULL;
	this -> current_gym = NULL;
	this -> location = in_loc;
	cout << "Pokemon constructed." << endl;
}

void Pokemon::StartMoving(Point2D dest) {
	if(dest.x == location.x && dest.y == location.y) {
		cout <<  display_code << id_num << ": I'm already there. See?" << endl;
	}
	if(IsExhausted() == 1) {
		cout <<  display_code << id_num << ": I am exhausted. I may move but you cannot see me." << endl;
	}
	else {
		SetupDestination(dest);
		state = MOVING;
		cout <<  display_code << id_num << ": On my way." << endl;
	}
}

void Pokemon::StartMovingToCenter(PokemonCenter* center) {
	this -> destination = center -> GetLocation();
	this -> state = MOVING_TO_CENTER;
	if(IsExhausted() == 1) {
		cout << display_code << " " << id_num << ": I am exhausted so can't move to recover stamina..." << endl;
	}
	if(destination.x == location.x && location.y == destination.y){
		cout << display_code << " " << id_num << ": I am already at the Pokemon Center!" << endl;
	}
	else {
		cout << display_code << " " << id_num << ": On my way to center " << (center -> GetId()) << endl;
		SetupDestination(destination);
	}
}

void Pokemon::StartMovingToGym(PokemonGym* gym) {
	this -> destination = gym -> GetLocation();
	this -> state = MOVING_TO_GYM;
	if(IsExhausted() == 1) {
		cout << display_code << " " << id_num << ": I am exhausted so I shouldn't be going to the gym.." << endl;
	}
	if(destination.x == location.x && destination.y == location.y){
		cout << display_code << " " << id_num << ": I am already at the Pokemon Gym!" << endl;
	}
	else {
		cout << display_code << " " << id_num << ": On my way to gym " << gym -> GetId() << endl;
		SetupDestination(destination);
	}
}

void Pokemon::StartTraining(unsigned int num_training_units) {
	Point2D gymLoc = current_gym -> GetLocation();

	if(IsExhausted() == 1) {
		cout << display_code << " " << id_num << ": I am exhausted so no more training for me..." << endl;
	}
	else if(location.x != gymLoc.x || location.y !=gymLoc.y) {
		cout << display_code << " " << id_num << ": I can only train in a Pokemon Gym!" << endl;
	}
	else if(current_gym -> IsBeaten() == 1) {
		cout << display_code << " " <<  id_num << ": Cannot train! This Pokemon Gym is already beaten!" << endl;
	}
	else {
		this -> state = TRAINING_IN_GYM;
		cout << "Starting to train at Pokemon Gym " << current_gym -> GetId() << " with " << num_training_units << " training units" << endl;
		this -> training_units_to_buy = (current_gym -> GetNumTrainingUnitsRemaining());
	}
}

void Pokemon::StartRecoveringStamina(unsigned int num_stamina_points) {
	double cost = current_center -> GetDollarCost(num_stamina_points);
	Point2D centLoc = current_center -> GetLocation();
	if(pokemon_dollars < cost) {
		cout << display_code << " " <<  id_num << ": Not enough money to recover stamina." << endl;
	}
	else if(current_center -> GetNumStaminaPointsRemaining() != 1) {
		cout << display_code << " " <<  id_num << ": Cannot recover! No stamina points remaining in this Pokemon Center." << endl;
	}
	else if(location.x != centLoc.x || location.y != centLoc.y) {
		cout << display_code << " " <<  id_num << ": I can only recover stamina at a Pokemon Center!" << endl;
	}
	else {
		cout << display_code << " " << id_num << ": Started recovering " << stamina << " at Pokemon Center " << current_center -> GetId() << endl;
		this -> state = RECOVERING_STAMINA;
		this -> stamina_points_to_buy = current_center -> GetNumStaminaPointsRemaining();
	}
}

void Pokemon::Stop() {
	this -> state = STOPPED;
	cout <<  display_code << " " <<  id_num << ": Stopping..." << endl;
}

bool Pokemon::IsExhausted() {
	if(stamina == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Pokemon::ShouldBeVisible() {
	if(IsExhausted() == 0) {
		return true;
	}
	else {
		return false;
	}
}

void Pokemon::SetupDestination(Point2D dest) {
	this -> destination = dest;
	this -> delta = (destination-location)*(speed/GetDistanceBetween(destination, location));
}

double GetRandomAmountOfPokemonDollars() {
	srand(time(NULL));
	double randDoll = (double)rand() * 0.0 + 2.0;
	return randDoll; 
}

bool Pokemon::Update() {
	switch(state) {
		case STOPPED:
			return false;
			break;

		case MOVING:
			if(UpdateLocation()) {
				state = STOPPED;
				return true;
				break;
			}
			else {
				state = MOVING;
				ShowStatus();
				return false;
				break;
			}

		case MOVING_TO_CENTER:
			if(UpdateLocation()) {
				state = IN_CENTER;
				return true;
				break;
			}
			else {
				state = MOVING;
				return false;
				break;
			}
		case MOVING_TO_GYM:
			if(UpdateLocation()) {
				state = IN_GYM;
				return true;
				break;
			}
			else {
				state = MOVING_TO_GYM;
				return false;
				break;
			}

		case IN_CENTER:
			return false;
			break;

		case IN_GYM:
			return false;
			break;

		case TRAINING_IN_GYM:
			stamina -= current_gym -> GetStaminaCost(training_units_to_buy); //
			pokemon_dollars -= current_gym -> GetDollarCost(training_units_to_buy); //
			cout << "**" << name << " completed " << training_units_to_buy << " training unit(s)!**" << endl;
			cout << "**" << name << " gained " << current_gym -> TrainPokemon(training_units_to_buy) << " experience point(s)!**" << endl;
			state = IN_GYM;
			return true;
			break;

		case RECOVERING_STAMINA:
			stamina += current_center -> DistributeStamina(current_center -> GetNumStaminaPointsRemaining());
			pokemon_dollars -= current_center -> GetDollarCost(current_center -> GetNumStaminaPointsRemaining());
			cout << "**" << name << " recovered " << stamina << " stamina point(s)!**" << endl;
			state = IN_CENTER;
			return true;
			break;
	}
	return false;
}

bool Pokemon::UpdateLocation() {
	if(fabs(destination.x - location.x) <= fabs(delta.x) && fabs(destination.y - location.y) <= fabs(delta.y)) {
		cout << display_code << GetId() << ": I'm there!" << endl;
		this -> location = destination;
		return true;
	}
	else {
		location = location + delta;
		cout << display_code << id_num << ": step..." << endl;
		return false;
	}
}

void Pokemon::ShowStatus() {
	switch(state) {
		case STOPPED:
			cout << name << " status: "<< display_code << id_num << " at " << location <<" stopped" << endl;
			cout << "	Stamina: " << stamina << endl;
			cout << "	Pokemon Dollars: " << pokemon_dollars << endl;
			cout << "	Experience Points: " << training_units_to_buy << endl;
			break;

		case MOVING:
			cout << name << " status: "<< display_code << id_num  << " moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << endl;
			cout << "	Stamina: " << stamina << endl;
			cout << "	Pokemon Dollars: " << pokemon_dollars << endl;
			cout << "	Experience Points: " << training_units_to_buy << endl;
			break;

		case MOVING_TO_CENTER:
			cout << name << " status: "<< display_code << id_num  << " heading to Pokemon Center " << current_center -> GetId() << " at a speed of " << speed << " at each step of "<< delta << endl;
			cout << "	Stamina: " << stamina << endl;
			cout << "	Pokemon Dollars: " << pokemon_dollars << endl;
			cout << "	Experience Points: " << training_units_to_buy << endl;
			break;

		case MOVING_TO_GYM:
			cout << name << " status: "<< display_code << id_num  << " heading to Pokemon Gym " << current_gym -> GetId() << " at a speed of " << speed << " at each step of "<< delta << endl;
			cout << "	Stamina: " << stamina << endl;
			cout << "	Pokemon Dollars: " << pokemon_dollars << endl;
			cout << "	Experience Points: " << training_units_to_buy << endl;
			break;

		case IN_CENTER:
			cout << name << " status: "<< display_code << id_num  << " inside Pokemon Center " << current_center -> GetId() << endl;
			cout << "	Stamina: " << stamina << endl;
			cout << "	Pokemon Dollars: " << pokemon_dollars << endl;
			cout << "	Experience Points: " << training_units_to_buy << endl;
			break;

		case IN_GYM:
			cout << name << " status: "<< display_code << id_num  << " inside Pokemon Gym " << current_gym -> GetId() << endl;
			cout << "	Stamina: " << stamina << endl;
			cout << "	Pokemon Dollars: " << pokemon_dollars << endl;
			cout << "	Experience Points: " << training_units_to_buy << endl;
			break;

		case TRAINING_IN_GYM:
			cout << name << " status: "<< display_code << id_num  << " training in Pokemon Gym " << current_gym -> GetId() << endl;
			cout << "	Stamina: " << stamina << endl;
			cout << "	Pokemon Dollars: " << pokemon_dollars << endl;
			cout << "	Experience Points: " << training_units_to_buy << endl;
			break;

		case RECOVERING_STAMINA:
			cout << name << " status: "<< display_code << id_num  << " recovering stamina in Pokemon Center " << current_center-> GetId() << endl;
			cout << "	Stamina: " << stamina << endl;
			cout << "	Pokemon Dollars: " << pokemon_dollars << endl;
			cout << "	Experience Points: " << training_units_to_buy << endl;
			break;	
	}
}


