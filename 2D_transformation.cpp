#include <graphics.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

// Function to apply translation
void translate(int *x, int *y, int numVertices, int tx, int ty) {
    for (int i = 0; i < numVertices; i++) {
        x[i] += tx;
        y[i] += ty;
    }
}

// Function to apply scaling
void scale(int *x, int *y, int numVertices, float sx, float sy) {
    for (int i = 0; i < numVertices; i++) {
        x[i] = (int)(x[i] * sx);
        y[i] = (int)(y[i] * sy);
    }
}

// Function to apply rotation
void rotate(int *x, int *y, int numVertices, float angle) {
    float rad = angle * (PI / 180); // Convert angle to radians
    for (int i = 0; i < numVertices; i++) {
        int originalX = x[i];
        int originalY = y[i];
        x[i] = (int)(originalX * cos(rad) - originalY * sin(rad));
        y[i] = (int)(originalX * sin(rad) + originalY * cos(rad));
    }
}

// Function to draw the polygon
void drawPolygon(int *x, int *y, int numVertices, int color) {
    setcolor(color);
    for (int i = 0; i < numVertices; i++) {
        int next = (i + 1) % numVertices; // Loop back to the first vertex
        line(x[i], y[i], x[next], y[next]);
    }
}

// Driver code
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Define the polygon vertices
    int x[] = {100, 150, 200, 150};  // x-coordinates of vertices
    int y[] = {100, 50, 100, 150};   // y-coordinates of vertices
    int numVertices = sizeof(x) / sizeof(x[0]);

    // Draw the original polygon in RED
    drawPolygon(x, y, numVertices, RED);

    // Translation
    int tx = 100, ty = 50;
    translate(x, y, numVertices, tx, ty);
    drawPolygon(x, y, numVertices, GREEN);

    // Scaling
    float sx = 1.5, sy = 1.5; // Scale factors
    scale(x, y, numVertices, sx, sy);
    drawPolygon(x, y, numVertices, BLUE);

    // Rotation
    float angle = 30; // Rotate 30 degrees
    rotate(x, y, numVertices, angle);
    drawPolygon(x, y, numVertices, WHITE);

    getch();
    closegraph();
    return 0;
}
