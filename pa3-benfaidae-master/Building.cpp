#include "Building.h"
#include <iostream>

using namespace std;

Building::Building() : GameObject('B') {
	display_code = 'B';
	pokemon_count = 0;
	cout << "Building default constructed." << endl;
}

Building::Building(char in_code, int in_id, Point2D in_loc) : GameObject('B') {
	id_num = in_id;
	location = in_loc;
	display_code = in_code;
	state = 0;
	cout << "Building constructed." << endl;
}

void Building::AddOnePokemon() {
	pokemon_count += 1;
}

void Building::RemoveOnePokemon() {
	pokemon_count -= 1;
}

void Building::ShowStatus() {
	if(pokemon_count == 0 || pokemon_count > 1) {
		cout << "	" << pokemon_count << " pokemon are in this building" << endl;
	}

	else if(pokemon_count == 1) {
		cout << "	" << pokemon_count << " pokemon is in this building" << endl;
	}

}
	
bool Building::ShouldBeVisible() {
	return true;
}



