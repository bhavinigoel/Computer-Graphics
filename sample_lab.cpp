#include<graphics.h>
#include<bits/stdc++.h>
using namespace std;

vector<pair<int,int>>translate(vector<pair<int,int>>&points, int move) 
{
     for(int i = 0; i < points.size(); i++)
     {
        points[i].first += move;
     }
     return points;   
}

pair<int, int> rotatePoint(int x, int y, int pivotX, int pivotY, float radians) 
{
    int newX = pivotX + (x - pivotX) * cos(radians) - (y - pivotY) * sin(radians);
    int newY = pivotY + (x - pivotX) * sin(radians) + (y - pivotY) * cos(radians);
    return make_pair(newX, newY);
}

vector<pair<int, int>> Rotation(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) 
{
    int angle = 45;
    float radians = angle * M_PI / 180.0;
    int pivotX = 250, pivotY = 250;

    vector<pair<int, int>> points = {
        rotatePoint(x1, y1, pivotX, pivotY, radians),
        rotatePoint(x2, y2, pivotX, pivotY, radians),
        rotatePoint(x3, y3, pivotX, pivotY, radians),
        rotatePoint(x4, y4, pivotX, pivotY, radians)
    };

    return points;
}

int main()
{
int gd = DETECT, gm;
initgraph(&gd, &gm, "");

//Square :-
int x1 = 200, y1 = 200, x2 = 300, y2 = 200, x3 = 300, y3 = 300, x4 = 200, y4 = 300;
line(x1, y1, x2, y2);
line(x2, y2, x3, y3);
line(x3, y3, x4, y4);
line(x4, y4, x1, y1);

char key = getch();

vector<pair<int,int>> points = Rotation(200,200,300,200,300,300,200,300);
int x = 450, y = 250, r = 71;
circle(x, y, r);
putpixel(450,250,WHITE); 

if(key == 77)
{
line(points[0].first, points[0].second, points[1].first, points[1].second);
line(points[1].first, points[1].second, points[2].first, points[2].second); 
line(points[2].first, points[2].second, points[3].first, points[3].second); 
line(points[3].first, points[3].second, points[0].first, points[0].second);
}

//translate :-
while(true)
{
    char key = getch();
    int move = 0;

    if(key == 27)
    {
        exit(0);
    }
    else if(key == 77)
    {
        move = 5;
    }
    else if(key == 75)
    {
        move = -5;
    }
    vector<pair<int,int>>new_points = translate(points,move);
    cleardevice();
    circle(x, y, r);
    putpixel(450,250,WHITE);
    line(new_points[0].first, new_points[0].second, new_points[1].first, new_points[1].second);
    line(new_points[1].first, new_points[1].second, new_points[2].first, new_points[2].second); 
    line(new_points[2].first, new_points[2].second, new_points[3].first, new_points[3].second); 
    line(new_points[3].first, new_points[3].second, new_points[0].first, new_points[0].second); 
}

getch();
closegraph();
return 0;
}

"Write a C++ program using the graphics.h library to demonstrate basic 2D transformations on a shape (like a square). The program should:

Draw a square on the screen.
Allow the square to rotate around a fixed pivot point (e.g., the center of the screen) by a specified angle when a certain key is pressed.
Allow the user to translate (move) the square left or right by a certain distance using arrow keys.
Implement a basic interactive user interface using the keyboard for controlling the square:
Use the arrow keys to move the square (left or right).
Use a specific key (e.g., the right arrow key) to rotate the square by 45 degrees.
The program should update the drawing on the screen after each key press.
Implement an exit condition, like pressing the ESC key to exit the program.