#include <graphics.h>
#include <stdio.h>

void drawInnerGrid(int x, int y, int size, int divisions) {
    int cellSize = size / divisions; // Size of each smaller cell

    // Draw vertical lines inside the square
    for (int i = 1; i < divisions; i++) {
        line(x + i * cellSize, y, x + i * cellSize, y + size);
    }

    // Draw horizontal lines inside the square
    for (int i = 1; i < divisions; i++) {
        line(x, y + i * cellSize, x + size, y + i * cellSize);
    }

    // Draw the outer border of the square
    rectangle(x, y, x + size, y + size);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int x = 100;          // Top-left X position of the square
    int y = 100;          // Top-left Y position of the square
    int size = 200;       // Size of the outer square
    int divisions = 5;    // Number of divisions (e.g., 5x5 grid)

    drawInnerGrid(x, y, size, divisions);
    

    getch();
    closegraph();
    return 0;
}
