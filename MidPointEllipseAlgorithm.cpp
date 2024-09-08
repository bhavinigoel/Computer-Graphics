#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

bool isFirstClick = true;
float centerX, centerY, radiusX, radiusY;

void handleMouseClick(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        float adjustedX = static_cast<float>(mouseX);
        float adjustedY = static_cast<float>(600 - mouseY);  // Convert to OpenGL coordinate system

        if (isFirstClick) {
            centerX = adjustedX;
            centerY = adjustedY;
            isFirstClick = false;
            std::cout << "Center: (" << centerX << ", " << centerY << ")\n";
        }
        else {
            radiusX = std::abs(adjustedX - centerX);
            radiusY = std::abs(adjustedY - centerY);
            std::cout << "Radii: (" << radiusX << ", " << radiusY << ")\n";
        }
    }
}

// Midpoint Ellipse Algorithm
void drawEllipse(float centerX, float centerY, float radiusX, float radiusY) {
    float dx, dy, d1, d2, x, y;
    x = 0;
    y = radiusY;

    // Decision parameter for region 1
    d1 = (radiusY * radiusY) - (radiusX * radiusX * radiusY) + (0.25 * radiusX * radiusX);
    dx = 2 * radiusY * radiusY * x;
    dy = 2 * radiusX * radiusX * y;

    // For region 1
    while (dx < dy) {
        glBegin(GL_POINTS);
        glVertex2f(centerX + x, centerY + y);
        glVertex2f(centerX - x, centerY + y);
        glVertex2f(centerX + x, centerY - y);
        glVertex2f(centerX - x, centerY - y);
        glEnd();

        if (d1 < 0) {
            x++;
            dx = dx + (2 * radiusY * radiusY);
            d1 = d1 + dx + (radiusY * radiusY);
        }
        else {
            x++;
            y--;
            dx = dx + (2 * radiusY * radiusY);
            dy = dy - (2 * radiusX * radiusX);
            d1 = d1 + dx - dy + (radiusY * radiusY);
        }
    }

    // Decision parameter for region 2
    d2 = ((radiusY * radiusY) * ((x + 0.5) * (x + 0.5))) + ((radiusX * radiusX) * ((y - 1) * (y - 1))) - (radiusX * radiusX * radiusY * radiusY);

    // For region 2
    while (y >= 0) {
        glBegin(GL_POINTS);
        glVertex2f(centerX + x, centerY + y);
        glVertex2f(centerX - x, centerY + y);
        glVertex2f(centerX + x, centerY - y);
        glVertex2f(centerX - x, centerY - y);
        glEnd();

        if (d2 > 0) {
            y--;
            dy = dy - (2 * radiusX * radiusX);
            d2 = d2 + (radiusX * radiusX) - dy;
        }
        else {
            y--;
            x++;
            dx = dx + (2 * radiusY * radiusY);
            dy = dy - (2 * radiusX * radiusX);
            d2 = d2 + dx - dy + (radiusX * radiusX);
        }
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Midpoint Ellipse Example", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Set the mouse button callback
    glfwSetMouseButtonCallback(window, handleMouseClick);

    // Set up the viewport and projection
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Set the color for the ellipse
        glColor3f(1.0f, 1.0f, 1.0f); // White color

        // Draw the ellipse if both radii are set
        if (!isFirstClick) {
            drawEllipse(centerX, centerY, radiusX, radiusY);
        }

        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
