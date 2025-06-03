#include <graphics.h>
#include <math.h>
#include <iostream>

using namespace std;

float degToRad(float degree) {
    return degree * (M_PI / 180.0);
}

void drawMulticoloredDashedLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = max(abs(dx), abs(dy));

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;
    int colors[] = {BLUE, GREEN, RED};

    for (int i = 0; i < steps; i++) {
        if (i % 10 < 5) {
            setcolor(colors[(i / 5) % 3]);
            putpixel((int)x, (int)y, colors[(i / 5) % 3]);
        }
        x += xInc;
        y += yInc;
    }
}


void drawPlainDashedLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = max(abs(dx), abs(dy));

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;
    setcolor(WHITE);

    for (int i = 0; i < steps; i++) {
        if (i % 10 < 5) {
            putpixel((int)x, (int)y, WHITE);
        }
        x += xInc;
        y += yInc;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int sides;
    cout << "Enter the number of sides for the polygon: ";
    cin >> sides;

    if (sides < 3) {
        cout << "A polygon must have at least 3 sides!";
        closegraph();
        return 0;
    }

    int centerX = getmaxx() / 2;  
    int centerY = getmaxy() / 2;  
    int radius = 100;             
    float angleStep = 360.0 / sides;  
    float rotationAngle = 0; 

    int x[sides], y[sides];

    while (true) {
   
        for (int i = 0; i < sides; i++) {
            float angle = i * angleStep + rotationAngle;
            x[i] = centerX + radius * cos(degToRad(angle));
            y[i] = centerY - radius * sin(degToRad(angle));

          
            if (i % 2 == 0) {
                drawPlainDashedLine(centerX, centerY, x[i], y[i]);
            } else {
                drawMulticoloredDashedLine(centerX, centerY, x[i], y[i]);
            }

   
            setcolor(WHITE);
            char label[3];
            sprintf(label, "%d", i + 1);
            outtextxy(x[i] + 10, y[i] + 10, label);  
        }


        for (int i = 0; i < sides; i++) {
            line(x[i], y[i], x[(i + 1) % sides], y[(i + 1) % sides]);
        }


        if (kbhit()) {
            getch();  
            rotationAngle += angleStep;  

            
            for (int i = 0; i < sides; i++) {
                setcolor(BLACK);
                line(centerX, centerY, x[i], y[i]);
                line(x[i], y[i], x[(i + 1) % sides], y[(i + 1) % sides]);
            }
        }
    }

    closegraph();
    return 0;
}
