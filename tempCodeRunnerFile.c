#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main() {
    int gd = DETECT, gm, n, *x, i, k = 0;

    int w[] = {220, 140, 420, 140, 420, 340, 220, 340, 220, 140};  // Window coordinates

    initgraph(&gd, &gm, "");  // Initialize graphics (path is empty for compatibility)

    // Draw the clipping window
    printf("Window:\n");
    setcolor(RED);
    drawpoly(5, w);

    // Input polygon vertices
    printf("Enter the number of vertices of the polygon: ");
    scanf("%d", &n);

    x = (int*)malloc((n * 2 + 2) * sizeof(int));  // Allocate memory for vertices
    printf("Enter the coordinates of points:\n");
    for (i = 0; i < n * 2; i += 2) {
        printf("(x%d, y%d): ", k, k);
        scanf("%d %d", &x[i], &x[i + 1]);
        k++;
    }

    // Close the polygon by repeating the first vertex at the end
    x[n * 2] = x[0];
    x[n * 2 + 1] = x[1];

    setcolor(WHITE);
    drawpoly(n + 1, x);  // Draw the input polygon

    printf("\nPress a button to clip the polygon...");
    getch();

    // Redraw clipping window and fill outside area to simulate clipping
    setcolor(RED);
    drawpoly(5, w);
    setfillstyle(SOLID_FILL, BLACK);
    floodfill(2, 2, RED);

    gotoxy(1, 1);  // Bring cursor to start position
    printf("\nThis is the clipped polygon..");
    getch();

    cleardevice();
    closegraph();
    free(x);  // Free allocated memory
    return 0;
}
