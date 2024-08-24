#include <GLFW/glfw3.h>
#include <iostream>

bool isFirstClick = true;
bool shouldDrawLine = false;
float point1X, point1Y, point2X, point2Y;
int lineType = -1; // -1 for unknown, 0 for dotted, 1 for dashed

void handleMouseClick(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        float adjustedX = static_cast<float>(mouseX);
        float adjustedY = static_cast<float>(600 - mouseY);  // Convert to OpenGL coordinate system

        if (isFirstClick) {
            point1X = adjustedX;
            point1Y = adjustedY;
            isFirstClick = false;
            shouldDrawLine = false;
            std::cout << "Point 1: (" << point1X << ", " << point1Y << ")\n";
        }
        else {
            point2X = adjustedX;
            point2Y = adjustedY;
            shouldDrawLine = true;
            isFirstClick = true;
            std::cout << "Point 2: (" << point2X << ", " << point2Y << ")\n";
        }
    }
}

void drawLine(float point1X, float point1Y, float point2X, float point2Y) {
    glLineWidth(5.0f);

    if (lineType == 0) { // Dotted line
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(3, 0xAAAA); // Dotted line pattern
    }
    else if (lineType == 1) { // Dashed line
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(4, 0xF0F0); // Dashed line pattern
    }

    glBegin(GL_LINES);
    glVertex2f(point1X, point1Y);
    glVertex2f(point2X, point2Y);
    glEnd();

    glDisable(GL_LINE_STIPPLE);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Line Example", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Set the mouse button callback
    glfwSetMouseButtonCallback(window, handleMouseClick);

    // Ask the user to choose the line type
    std::cout << "Choose a line type:\n";
    std::cout << "0. Dotted line\n";
    std::cout << "1. Dashed line\n";
    std::cout << "Enter your choice: ";
    std::cin >> lineType;

    // Set up the viewport and projection
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Set the color for the line
        glColor3f(1.0f, 0.0f, 1.0f); // White color

        // Draw the line if both points are set
        if (shouldDrawLine) {
            drawLine(point1X, point1Y, point2X, point2Y);
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
