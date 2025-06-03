#include <graphics.h>
#include <math.h>

void fillQuadrants(int centerX, int centerY) {

    setfillstyle(SOLID_FILL, RED);
    floodfill(centerX + 10, centerY - 10, WHITE);

    setfillstyle(SOLID_FILL, GREEN);
    floodfill(centerX - 10, centerY - 10, WHITE);

   
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(centerX - 10, centerY + 10, WHITE);

    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(centerX + 10, centerY + 10, WHITE);
}

void drawConcentricPolygons(int n, int numberOfPolygons, int centerX, int centerY, int radiusStep) {
    double angleStep = (2 * M_PI) / n;

    for (int i = 1; i <= numberOfPolygons; i++) {
        int currentRadius = i * radiusStep;
        int poly[2 * n];  

        for (int j = 0; j < n; j++) {
            poly[2 * j] = centerX + currentRadius * cos(j * angleStep);    
            poly[2 * j + 1] = centerY + currentRadius * sin(j * angleStep); 
        }

 
        drawpoly(n, poly);

    
        line(poly[2 * (n - 1)], poly[2 * (n - 1) + 1], poly[0], poly[1]);
    }
}

void drawAxes(int centerX, int centerY, int maxRadius) {
    
    line(centerX, centerY - maxRadius, centerX, centerY + maxRadius);

    line(centerX - maxRadius, centerY, centerX + maxRadius, centerY);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int n = 6; 
    int numberOfPolygons = 5; 
    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;
    int radiusStep = 40;


    int maxRadius = numberOfPolygons * radiusStep;

   
    drawConcentricPolygons(n, numberOfPolygons, centerX, centerY, radiusStep);


    drawAxes(centerX, centerY, maxRadius);

    fillQuadrants(centerX, centerY);

    getch();
    closegraph();
    return 0;
}
