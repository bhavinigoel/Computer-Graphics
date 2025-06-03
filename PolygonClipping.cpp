#include <graphics.h>
#include <stdio.h>

// Clipping boundaries
int x_min, y_min, x_max, y_max;

// Function to find intersection point
void findIntersection(int x1, int y1, int x2, int y2, int *x, int *y, int edge) {
    float slope = (float)(y2 - y1) / (x2 - x1);
    switch (edge) {
        case 0: // Left edge
            *x = x_min;
            *y = y1 + slope * (x_min - x1);
            break;
        case 1: // Right edge
            *x = x_max;
            *y = y1 + slope * (x_max - x1);
            break;
        case 2: // Bottom edge
            *x = x1 + (float)(y_min - y1) / slope;
            *y = y_min;
            break;
        case 3: // Top edge
            *x = x1 + (float)(y_max - y1) / slope;
            *y = y_max;
            break;
    }
}

// Function to check whether point (x, y) is inside the clipping window
int isInside(int x, int y, int edge) {
    switch (edge) {
        case 0: return x >= x_min; // Left edge
        case 1: return x <= x_max; // Right edge
        case 2: return y >= y_min; // Bottom edge
        case 3: return y <= y_max; // Top edge
    }
    return 0;
}

// Function to clip a polygon against a single edge
void clipPolygon(int *x, int *y, int *numVertices, int edge) {
    int new_x[20], new_y[20];
    int newCount = 0;
    for (int i = 0; i < *numVertices; i++) {
        int k = (i + 1) % *numVertices;
        int ix = x[i], iy = y[i];
        int kx = x[k], ky = y[k];
        int i_inside = isInside(ix, iy, edge);
        int k_inside = isInside(kx, ky, edge);
        if (i_inside && k_inside) {
            // Both points are inside: add the second point (kx, ky)
            new_x[newCount] = kx;
            new_y[newCount] = ky;
            newCount++;
        } else if (i_inside && !k_inside) {
            // Exiting the clipping region: add intersection point
            int x_int, y_int;
            findIntersection(ix, iy, kx, ky, &x_int, &y_int, edge);
            new_x[newCount] = x_int;
            new_y[newCount] = y_int;
            newCount++;
        } else if (!i_inside && k_inside) {
            // Entering the clipping region: add intersection point and second point
            int x_int, y_int;
            findIntersection(ix, iy, kx, ky, &x_int, &y_int, edge);
            new_x[newCount] = x_int;
            new_y[newCount] = y_int;
            newCount++;
            new_x[newCount] = kx;
            new_y[newCount] = ky;
            newCount++;
        }
        // Don't modify the vertex order or swap the order of insertion
    }
    // Update the vertices of the polygon with the newly clipped polygon
    *numVertices = newCount;
    for (int i = 0; i < newCount; i++) {
        x[i] = new_x[i];
        y[i] = new_y[i];
    }
}

// Function to perform Sutherland-Hodgman polygon clipping
void sutherlandHodgmanClip(int *x, int *y, int numVertices) {
    // Clip against each edge (left, right, bottom, top)
    for (int edge = 0; edge < 4; edge++) {
        clipPolygon(x, y, &numVertices, edge);
    }
    // Draw the clipped polygon in green
    setcolor(GREEN);
    for (int i = 0; i < numVertices; i++) {
        int next = (i + 1) % numVertices;
        line(x[i], y[i], x[next], y[next]); // Corrected function call
    }
}

// Driver code
int main() {
    int gd = DETECT, gm;
    char driver[] = ""; // Corrected from string literal to char array
    initgraph(&gd, &gm, driver);

    // Define the clipping rectangle boundaries
    x_min = 100;
    y_min = 100;
    x_max = 300;
    y_max = 300;

    // Draw the clipping rectangle in yellow
    setcolor(YELLOW);
    rectangle(x_min, y_min, x_max, y_max);

    // Define the polygon vertices
    int x[] = {50, 150, 350, 250};
    int y[] = {50, 300, 300, 150};
    int numVertices = 4;

    // Draw the original polygon in red
    setcolor(RED);
    for (int i = 0; i < numVertices; i++) {
        int next = (i + 1) % numVertices;
        line(x[i], y[i], x[next], y[next]); // Corrected function call
    }

    // Perform polygon clipping
    sutherlandHodgmanClip(x, y, numVertices);

    getch();
    closegraph();
    return 0;
}
