#include <graphics.h>
#include <math.h>

void drawConcentricPolygons(int n, int numberOfPolygons, int centerX, int centerY, int radiusStep) {
    double angleStep = (2 * M_PI) / n;

    for (int i = 1; i <= numberOfPolygons; i++) {
        int currentRadius = i * radiusStep;
        int poly[2 * n];  // This will store alternating x and y coordinates

        for (int j = 0; j < n; j++) {
            poly[2 * j] = centerX + currentRadius * cos(j * angleStep);    // x-coordinate
            poly[2 * j + 1] = centerY + currentRadius * sin(j * angleStep); // y-coordinate
        }

        drawpoly(n, poly);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int n = 6; // Number of sides
    int numberOfPolygons = 5; // Number of concentric polygons
    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;
    int radiusStep = 20;

    drawConcentricPolygons(n, numberOfPolygons, centerX, centerY, radiusStep);

    getch();
    closegraph();
    return 0;
}
