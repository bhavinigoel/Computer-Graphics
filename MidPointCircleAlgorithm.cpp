#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

bool isFirstClick = true;
float centerX, centerY, radius;

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
            float dx = adjustedX - centerX;
            float dy = adjustedY - centerY;
            radius = sqrtf(dx * dx + dy * dy);
            std::cout << "Radius: " << radius << "\n";
        }
    }
}

void drawCircle(float centerX, float centerY, float radius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        float x = centerX + cosf(angle) * radius;
        float y = centerY + sinf(angle) * radius;
        glVertex2f(x, y);
    }
    glEnd();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Circle Example", NULL, NULL);
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

        // Set the color for the circle
        glColor3f(1.0f, 1.0f, 1.0f); // White color

        // Draw the circle if both points are set
        if (!isFirstClick) {
            drawCircle(centerX, centerY, radius);
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
