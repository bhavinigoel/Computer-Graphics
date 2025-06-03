#include <graphics.h>
#include <stdio.h>

// Define clipping window boundaries
int x_min = 100, y_min = 100, x_max = 300, y_max = 300;

// Liang-Barsky line clipping function
void liangBarskyClip(int x1, int y1, int x2, int y2) {
    float t0 = 0.0, t1 = 1.0;
    float dx = x2 - x1;
    float dy = y2 - y1;

    // P[i] and Q[i] values for the four edges of the clipping window
    float p[] = {-dx, dx, -dy, dy};
    float q[] = {x1 - x_min, x_max - x1, y1 - y_min, y_max - y1};

    for (int i = 0; i < 4; i++) {
        if (p[i] == 0) {  // Parallel line case
            if (q[i] < 0) {  // Line is outside the boundary
                return;  // Reject line
            }
        } else {
            float t = q[i] / p[i];
            if (p[i] < 0) {
                if (t > t1) return;  // Reject the line
                if (t > t0) t0 = t;  // Update t0
            } else {
                if (t < t0) return;  // Reject the line
                if (t < t1) t1 = t;  // Update t1
            }
        }
    }

    // Compute clipped line coordinates
    int clipped_x1 = x1 + t0 * dx;
    int clipped_y1 = y1 + t0 * dy;
    int clipped_x2 = x1 + t1 * dx;
    int clipped_y2 = y1 + t1 * dy;

    // Draw the clipped line in green
    setcolor(GREEN);
    line(clipped_x1, clipped_y1, clipped_x2, clipped_y2);
}

// Driver code
int main() {
    int gd = DETECT, gm;
    char driver[] = "";
    initgraph(&gd, &gm, driver);

    // Define the clipping rectangle boundaries
    setcolor(YELLOW);
    rectangle(x_min, y_min, x_max, y_max);  // Draw the clipping window in yellow

    // Define a line to be clipped
    int x1 = 50, y1 = 50, x2 = 350, y2 = 350;

    // Draw the original line in red
    setcolor(RED);
    line(x1, y1, x2, y2);

    // Perform Liang-Barsky line clipping
    liangBarskyClip(x1, y1, x2, y2);

    getch();
    closegraph();
    return 0;
}
