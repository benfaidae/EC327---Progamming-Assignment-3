#include "Vector2D.h"
#include "Point2D.h"
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Pokemon.h"
#include "Model.h"
#include "View.h"
#include "GameCommand.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
	
	View v;

	cout << "EC327: Introduction to Software Engineering" << endl;
	cout << "Fall 2019" << endl;
	cout << "Programming Assignment 3" << endl;

	cout <<"                                   ,'\\		                         			 \n"
		   "    _.----.        ____         ,'  _\\   ___    ___     ____					 \n"
 		   "_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.			 \n"
		   "\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |		     \n"
		   " \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |          \n"
           "  \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |             \n"
           "   \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |           \n"
           "    \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    | 		 \n"
           "     \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |          \n"
           "      \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |            \n"
           "       \\_.-'       |__|    `-._ |              '-.|     '-.| |   |              \n"
           "                                `'                            '-._|"            << endl;

	Model m;
	m.ShowStatus();
	m.Display(v);

	char command;
	int x, y, ID, ID1, ID2, stamina_amount, unit_amount;

	while(true) {

		bool validCommand = true;

		cout << "Enter Command: ";
		cin >> command;

		switch(command) {
			case 'm':
				cin >> ID;
				cin >> x;
				cin >> y;
				DoMoveCommand(m, ID, Point2D(x, y));
				m.Display(v);
				m.Update();
				break;

			case 'g':
				cin >> ID1 >> ID2;
				DoMoveToGymCommand(m, ID1, ID2);
				m.Display(v);
				break;

			case 'c':
				cin >> ID1 >> ID2;
				DoMoveToCenterCommand(m, ID1, ID2);
				m.Display(v);
				break;

			case 's':
				cin >> ID;
				DoStopCommand(m, ID);
				m.Display(v);
				break;

			case 'r':
				cin >> ID1 >> ID2 >> stamina_amount;
				DoRecoverInCenterCommand(m, ID1,stamina_amount);
				m.Display(v);
				break;

			case 't':
				cin >> ID1 >> ID2 >> unit_amount;
				DoTrainInGymCommand(m, ID1, unit_amount);
				m.Display(v);
				break;

			case 'v': 
				DoGoCommand(m, v);
				m.Display(v);
				break;

			case 'x':
				DoRunCommand(m, v);
				m.Display(v);
				break;

			case 'q':
				m.~Model();
				exit(0);
				break;
			default: 
				cout << "ERROR: Please enter a valid command!" << endl;
		}

	}
	return 0;
}
