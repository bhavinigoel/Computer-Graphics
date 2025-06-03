#include <graphics.h>
#include <stdio.h>

// Define region codes for the Cohen-Sutherland algorithm
#define INSIDE 0 // 0000
#define LEFT 1   // 0001
#define RIGHT 2  // 0010
#define BOTTOM 4 // 0100
#define TOP 8    // 1000

// Define clipping rectangle boundaries
int x_min, y_min, x_max, y_max;

// Function to compute region code
int computeCode(int x, int y) {
    int code = INSIDE;

    if (x < x_min)
        code |= LEFT;
    else if (x > x_max)
        code |= RIGHT;
    if (y < y_min)
        code |= BOTTOM;
    else if (y > y_max)
        code |= TOP;

    return code;
}

// Cohen-Sutherland line clipping algorithm
void cohenSutherlandClip(int x1, int y1, int x2, int y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    int accept = 0;

    while (1) {
        if ((code1 == 0) && (code2 == 0)) {
            // Both endpoints are inside the rectangle
            accept = 1;
            break;
        } else if (code1 & code2) {
            // Both endpoints are outside the rectangle in the same region
            break;
        } else {
            // Line needs clipping
            int code_out;
            int x, y;

            // Pick the point outside the rectangle
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            // Find the intersection point
            if (code_out & TOP) {
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            } else if (code_out & BOTTOM) {
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            } else if (code_out & RIGHT) {
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            } else if (code_out & LEFT) {
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            // Replace the point outside the rectangle with the intersection point
            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        // Draw the clipped line
        setcolor(WHITE);
        line(x1, y1, x2, y2);
    }
}

// Driver code
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Define the clipping rectangle boundaries
    x_min = 100;
    y_min = 100;
    x_max = 300;
    y_max = 300;

    // Draw the clipping rectangle
    rectangle(x_min, y_min, x_max, y_max);

    // Define a line segment (outside the clipping area)
    int x1 = 50, y1 = 50, x2 = 350, y2 = 350;

    // Draw the original line in RED
    setcolor(RED);
    line(x1, y1, x2, y2);

    // Perform line clipping
    cohenSutherlandClip(x1, y1, x2, y2);

    getch();
    closegraph();
    return 0;
}
