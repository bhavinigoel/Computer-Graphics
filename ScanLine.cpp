#include <graphics.h>
#include <iostream>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

// Function to find the intersection points of a polygon with a scan line
void findIntersections(Point poly[], int n, int scanLine, int intersections[], int &count) {
    count = 0;
    for (int i = 0; i < n; i++) {
        int x1 = poly[i].x;
        int y1 = poly[i].y;
        int x2 = poly[(i + 1) % n].x;
        int y2 = poly[(i + 1) % n].y;

        // Check if the scan line intersects the edge
        if ((y1 <= scanLine && y2 > scanLine) || (y2 <= scanLine && y1 > scanLine)) {
            // Find the x-coordinate of the intersection point
            int x = x1 + (scanLine - y1) * (x2 - x1) / (y2 - y1);
            intersections[count++] = x;
        }
    }
}

// Scan Line Polygon Fill function
void scanLinePolygonFill(Point poly[], int n, int fillColor) {
    // Find the min and max y-coordinates of the polygon
    int ymin = poly[0].y, ymax = poly[0].y;
    for (int i = 1; i < n; i++) {
        ymin = min(ymin, poly[i].y);
        ymax = max(ymax, poly[i].y);
    }

    // Loop through each scan line from ymin to ymax
    for (int scanLine = ymin; scanLine <= ymax; scanLine++) {
        int intersections[20]; // To store intersection points on the scan line
        int count;

        // Find intersection points of the polygon with the current scan line
        findIntersections(poly, n, scanLine, intersections, count);

        // Sort the intersection points in ascending order of x-coordinates
        sort(intersections, intersections + count);

        // Fill between pairs of intersections
        for (int i = 0; i < count; i += 2) {
            line(intersections[i], scanLine, intersections[i + 1], scanLine);
            setcolor(fillColor);
        }
    }
}

// Function to draw a polygon
void drawPolygon(Point poly[], int n) {
    for (int i = 0; i < n; i++) {
        line(poly[i].x, poly[i].y, poly[(i + 1) % n].x, poly[(i + 1) % n].y);
    }
}

// Main function
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Define the polygon points
    Point poly[] = {{200, 200}, {300, 100}, {400, 200}, {300, 300}};
    int n = sizeof(poly) / sizeof(poly[0]);

    // Draw the polygon
    setcolor(RED);
    drawPolygon(poly, n);

    // Fill the polygon using scan line algorithm
    scanLinePolygonFill(poly, n, GREEN);

    getch();
    closegraph();
    return 0;
}
