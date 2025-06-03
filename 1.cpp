#include <graphics.h>
#include <math.h>

// Function to draw a regular polygon
void drawRegularPolygon(int centerX, int centerY, int sides, int radius) {
    double angleStep = 2 * M_PI / sides; // Angle between vertices
    int x1, y1, x2, y2;

    for (int i = 0; i < sides; i++) {
        x1 = centerX + radius * cos(i * angleStep);
        y1 = centerY + radius * sin(i * angleStep);
        x2 = centerX + radius * cos((i + 1) * angleStep);
        y2 = centerY + radius * sin((i + 1) * angleStep);

        line(x1, y1, x2, y2);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Draw a circle
    int circleX = 100, circleY = 100, circleRadius = 50;
    circle(circleX, circleY, circleRadius);

    // Draw a square
    int squareX = 200, squareY = 200, squareSize = 100;
    rectangle(squareX, squareY, squareX + squareSize, squareY + squareSize);

    // Draw a regular polygon (hexagon in this case)
    int polygonX = 400, polygonY = 100, polygonSides = 3, polygonRadius = 50;
    drawRegularPolygon(polygonX, polygonY, polygonSides, polygonRadius);

    // Draw a rectangle
    int rectX1 = 500, rectY1 = 250, rectX2 = 450, rectY2 = 300;
    rectangle(rectX1, rectY1, rectX2, rectY2);

    getch();
    closegraph();
    return 0;
}


#include <graphics.h>

// Function to draw concentric circles
void drawConcentricCircles(int centerX, int centerY, int initialRadius, int step, int count) {
    for (int i = 0; i < count; i++) {
        circle(centerX, centerY, initialRadius + i * step);
    }
}

// Function to draw concentric squares
void drawConcentricSquares(int centerX, int centerY, int initialSize, int step, int count) {
    for (int i = 0; i < count; i++) {
        int halfSize = (initialSize + i * step) / 2;
        rectangle(centerX - halfSize, centerY - halfSize,
                  centerX + halfSize, centerY + halfSize);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Set the common center for concentric shapes
    int centerX = 300, centerY = 250;

    // Draw concentric circles
    int initialCircleRadius = 30; // Starting radius
    int circleStep = 20;          // Gap between circles
    int circleCount = 5;          // Number of concentric circles
    drawConcentricCircles(centerX, centerY, initialCircleRadius, circleStep, circleCount);

    // Draw concentric squares
    int initialSquareSize = 60; // Starting size
    int squareStep = 30;        // Gap between squares
    int squareCount = 5;        // Number of concentric squares
    drawConcentricSquares(centerX, centerY, initialSquareSize, squareStep, squareCount);

    getch();
    closegraph();
    return 0;
}
