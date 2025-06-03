#include <graphics.h>
#include <math.h>

// Function to draw lines from the center to vertices of a circle
void drawLinesToCircleVertices(int centerX, int centerY, int radius, int sides) {
    double angleStep = 2 * M_PI / sides; // Angle step for each vertex
    int x, y;

    for (int i = 0; i < sides; i++) {
        x = centerX + radius * cos(i * angleStep);
        y = centerY + radius * sin(i * angleStep);
        line(centerX, centerY, x, y); // Draw line from center to vertex
    }
}

// Function to draw lines from the center to vertices of a square
void drawLinesToSquareVertices(int centerX, int centerY, int size) {
    int halfSize = size / 2;

    // Vertices of the square
    int x1 = centerX - halfSize, y1 = centerY - halfSize; // Top-left
    int x2 = centerX + halfSize, y2 = centerY - halfSize; // Top-right
    int x3 = centerX + halfSize, y3 = centerY + halfSize; // Bottom-right
    int x4 = centerX - halfSize, y4 = centerY + halfSize; // Bottom-left

    // Draw lines from the center to each vertex
    line(centerX, centerY, x1, y1);
    line(centerX, centerY, x2, y2);
    line(centerX, centerY, x3, y3);
    line(centerX, centerY, x4, y4);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Common center
    int centerX = 300, centerY = 250;

    // Circle parameters
    int circleRadius = 100;
    int circleSides = 6; // Number of vertices (e.g., hexagon)
    circle(centerX, centerY, circleRadius); // Draw the circle
    drawLinesToCircleVertices(centerX, centerY, circleRadius, circleSides);

    // Square parameters
    int squareSize = 200;
    rectangle(centerX - squareSize / 2, centerY - squareSize / 2,
              centerX + squareSize / 2, centerY + squareSize / 2); // Draw the square
    drawLinesToSquareVertices(centerX, centerY, squareSize);

    getch();
    closegraph();
    return 0;
}
