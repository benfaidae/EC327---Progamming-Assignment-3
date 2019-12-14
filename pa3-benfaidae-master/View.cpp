#include "View.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include <iostream>


using namespace std;

View::View() {
	this -> size = 11;
	this -> scale = 2;
	this -> origin = Point2D();
}

bool View::GetSubscripts(int &out_x, int &out_y, Point2D location) {
	Vector2D sub = (location - origin)/scale;
	out_x = sub.x;
	out_y = sub.y;
	if(out_x >= 0 && out_x <= 10 && out_y >= 0 && out_y <= 10)
		return true;
	else {
		cout << "An object is outside the display" << endl;
		return false;
	}
}

void View::Plot(GameObject* ptr) {
	int out_x, out_y;
	if(GetSubscripts(out_x, out_y, (*ptr).GetLocation())) {
		if(grid[10 - out_y][out_x][0] == '.')
			(*ptr).DrawSelf(grid[10 - out_y][out_x]);
		else {
			grid[10 - out_y][out_x][0] = '*';
			grid[10 - out_y][out_x][1] = ' ';
		}
	}
} 

void View::Draw()
{
    for (int i = 0; i < view_maxsize/2 + 1; i++) {
        if (i%2 == 0 && i < 5)
            cout << 20 - 2*i;
        else if (i%2 == 0 && i >5)
            cout << 20 - 2*i << " ";
        else
            cout << "  ";

        for (int j = 0; j < view_maxsize/2 + 1; j++) {
            cout << grid[i][j][0];
            if (grid[i][j][0] != '.' && grid[i][j][1] != ' ')
                cout << int(grid[i][j][1]);
            else
                cout << grid[i][j][1];
        }
        cout << endl;
    }
    cout << "  0   4   8   12  16  20" << endl;
}

void View::Clear() {
	for (int i = 0; i < view_maxsize; i++) {
		for (int j = 0; j < view_maxsize; j++){
			grid[i][j][0] = '.';
			grid[i][j][1] = ' ';
		}
	}
}
