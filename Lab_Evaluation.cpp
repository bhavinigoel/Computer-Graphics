#include <graphics.h>
#include <math.h>
#include <iostream>

using namespace std;

void drawLinesToCircleVertices(int centerX, int centerY, int radius, int sides)
{
    double angleStep = 2 * M_PI / sides;
    int x, y;

    for (int i = 0; i < sides; i++)
    {
        x = centerX + radius * cos(i * angleStep);
        y = centerY + radius * sin(i * angleStep);

        line(centerX, centerY, x, y);
    }
}

void pattern(int centerX, int centerY, int radius, int sides, int width)
{
    int end;
    int endy;
    end = centerX + radius;
    endy = centerY + radius;
    double angleStep = 2 * M_PI / sides;
    int x, y;
    int x1, y1;

    for (int i = 1; i < 10; i = i + 3)
    {

        for (int inc = 1; inc < radius; inc = inc + width)
        {
            x = centerX + inc * cos(i * angleStep);
            y = centerY + inc * sin(i * angleStep);
            x1 = centerX + inc * cos((i + 1) * angleStep);
            y1 = centerY + inc * sin((i + 1) * angleStep);

            line(x, y, x1, y1);
        }
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    int radius;
    int width;


    int centerX = 300, centerY = 250;
    cout << "Enter the radius of the circle";
    cin >> radius;
    cout << "Enter the width for line pattern";
    cin>>width;

    int circleRadius = radius;
    int circleSides = 8;
    circle(centerX, centerY, circleRadius);
    drawLinesToCircleVertices(centerX, centerY, circleRadius, circleSides);
    pattern(centerX, centerY, circleRadius, circleSides,width);

    getch();
    closegraph();
    return 0;
}