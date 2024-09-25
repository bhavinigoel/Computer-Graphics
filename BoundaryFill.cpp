#include <graphics.h>
#include <stack>
#include <iostream>

using namespace std;

void setPixel(int x, int y, int fillColor) {
    putpixel(x, y, fillColor);
}

int getPixel(int x, int y) {
    return getpixel(x, y);
}

void boundaryFill4(int x, int y, int fillColor, int boundaryColor) {
    int currentColor = getPixel(x, y);
    if (currentColor != boundaryColor && currentColor != fillColor) {
        setPixel(x, y, fillColor);
        boundaryFill4(x + 1, y, fillColor, boundaryColor);
        boundaryFill4(x - 1, y, fillColor, boundaryColor);
        boundaryFill4(x, y + 1, fillColor, boundaryColor);
        boundaryFill4(x, y - 1, fillColor, boundaryColor);
    }
}

void drawBoundary() {
    setcolor(RED);
    rectangle(100, 100, 200, 200);  // Draws a boundary rectangle
}

void display() {
    cleardevice();

    // Draw the boundary before filling
    drawBoundary();

    // Fill the region starting from the bottom (150, 101), slightly above the boundary line
    boundaryFill4(150, 101, GREEN, RED);  // Fill with green color starting just above the bottom edge
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    display();

    getch();
    closegraph();
    return 0;
}
