#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <cmath>

using namespace std;

void Midpoint_Circle(int xi, int yi, int r) {
    int x = 0, y = r;
    int pk = 1 - r;

    while (x <= y) {
        putpixel(xi + x, yi + y, WHITE);
        putpixel(xi - x, yi + y, WHITE);
        putpixel(xi + x, yi - y, WHITE);
        putpixel(xi - x, yi - y, WHITE);
        putpixel(xi + y, yi + x, WHITE);
        putpixel(xi - y, yi + x, WHITE);
        putpixel(xi + y, yi - x, WHITE);
        putpixel(xi - y, yi - x, WHITE);

        if (pk < 0) {
            pk += 2 * x + 3;
        } else {
            pk += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void DDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = max(abs(dx), abs(dy));
    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        putpixel(round(x), round(y), WHITE);
        x += xIncrement;
        y += yIncrement;
    }
}

void FloodFill(int x, int y, int fill_color, int boundary_color) {
    int current = getpixel(x, y);
    if (current != fill_color && current != boundary_color) {
        putpixel(x, y, fill_color);
        FloodFill(x + 1, y, fill_color, boundary_color);
        FloodFill(x - 1, y, fill_color, boundary_color);
        FloodFill(x, y + 1, fill_color, boundary_color);
        FloodFill(x, y - 1, fill_color, boundary_color);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int xi, yi;
    cout << "Enter center (xi, yi): ";
    cin >> xi >> yi;

    // Draw concentric circles
    for (int r = 20; r <= 100; r += 20) {
        Midpoint_Circle(xi, yi, r);
    }

    // Radius for DDA
    int radius = 100; 
    float dl = radius * sqrt(2) / 2; 

    // Draw radial lines
    DDA(xi - radius, yi, xi + radius, yi);     // Horizontal line
    DDA(xi, yi - radius, xi, yi + radius);     // Vertical line
    DDA(xi - dl, yi - dl, xi + dl, yi + dl);   // Diagonal line 1
    DDA(xi - dl, yi + dl, xi + dl, yi - dl);   // Diagonal line 2

    // Perform Flood Fill for each quadrant
    FloodFill(xi - 10, yi - 10, RED, WHITE);   // Top-left quadrant
    FloodFill(xi - 10, yi + 10, BLUE, WHITE);    // Bottom-left quadrant
    FloodFill(xi + 10, yi - 10, GREEN, WHITE);  // Top-right quadrant
    FloodFill(xi + 10, yi + 10, YELLOW, WHITE); // Bottom-right quadrant

    getch();
    closegraph();
    return 0;
}
