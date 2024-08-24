#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

enum LineDrawingAlgorithm {
    ALGO_NONE,
    ALGO_SIMPLE_DDA,
    ALGO_SYMMETRIC_DDA,
    ALGO_BRESENHAM
};

bool isFirstClick = true;
bool shouldDrawLine = false;
float point1X, point1Y, point2X, point2Y;
LineDrawingAlgorithm currentAlgorithm = ALGO_NONE;

// Function prototypes
void drawLineWithSimpleDDA(float point1X, float point1Y, float point2X, float point2Y);
void drawLineWithSymmetricDDA(float point1X, float point1Y, float point2X, float point2Y);
void drawLineWithBresenham(int point1X, int point1Y, int point2X, int point2Y);
void handleMouseClick(GLFWwindow* window, int button, int action, int mods);

int main() {
    char applyLineAlgorithm;
    std::cout << "Do you want to apply a line drawing algorithm? (y/n): ";
    std::cin >> applyLineAlgorithm;

    if (applyLineAlgorithm == 'y' || applyLineAlgorithm == 'Y') {
        int algorithmChoice;
        std::cout << "Choose an algorithm: \n";
        std::cout << "1) Simple DDA\n";
        std::cout << "2) Symmetric DDA\n";
        std::cout << "3) Bresenham\n";
        std::cout << "Enter your choice (1/2/3): ";
        std::cin >> algorithmChoice;

        switch (algorithmChoice) {
        case 1:
            currentAlgorithm = ALGO_SIMPLE_DDA;
            break;
        case 2:
            currentAlgorithm = ALGO_SYMMETRIC_DDA;
            break;
        case 3:
            currentAlgorithm = ALGO_BRESENHAM;
            break;
        default:
            std::cerr << "Invalid choice. Exiting.\n";
            return -1;
        }
    }
    else {
        std::cout << "No line drawing algorithm chosen. Exiting.\n";
        return 0;
    }

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Line Drawing Algorithms", NULL, NULL);
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

        // Set the color for the line
        glColor3f(1.0f, 1.0f, 1.0f); // White color

        // Draw the line if both points are set
        if (shouldDrawLine) {
            switch (currentAlgorithm) {
            case ALGO_SIMPLE_DDA:
                drawLineWithSimpleDDA(point1X, point1Y, point2X, point2Y);
                break;
            case ALGO_SYMMETRIC_DDA:
                drawLineWithSymmetricDDA(point1X, point1Y, point2X, point2Y);
                break;
            case ALGO_BRESENHAM:
                drawLineWithBresenham(static_cast<int>(point1X), static_cast<int>(point1Y), static_cast<int>(point2X), static_cast<int>(point2Y));
                break;
            default:
                break;
            }
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

// Simple DDA line drawing algorithm
void drawLineWithSimpleDDA(float point1X, float point1Y, float point2X, float point2Y) {
    float deltaX = point2X - point1X;
    float deltaY = point2Y - point1Y;

    int numSteps = std::max(std::abs(deltaX), std::abs(deltaY));

    float xStep = deltaX / static_cast<float>(numSteps);
    float yStep = deltaY / static_cast<float>(numSteps);

    float currentX = point1X;
    float currentY = point1Y;

    glBegin(GL_POINTS);
    for (int i = 0; i <= numSteps; i++) {
        glVertex2f(currentX, currentY);
        currentX += xStep;
        currentY += yStep;
    }
    glEnd();
}

// Symmetric DDA line drawing algorithm
void drawLineWithSymmetricDDA(float point1X, float point1Y, float point2X, float point2Y) {
    float deltaX = point2X - point1X;
    float deltaY = point2Y - point1Y;

    float numSteps = std::max(std::abs(deltaX), std::abs(deltaY));
    float stepSize = 1.0f / numSteps; // Small step size for symmetric DDA

    float xStep = stepSize * deltaX;
    float yStep = stepSize * deltaY;

    float currentX = point1X;
    float currentY = point1Y;

    glBegin(GL_POINTS);
    for (int i = 0; i <= numSteps; i++) {
        glVertex2f(currentX, currentY);
        currentX += xStep;
        currentY += yStep;
    }
    glEnd();
}

// Bresenham line drawing algorithm
void drawLineWithBresenham(int point1X, int point1Y, int point2X, int point2Y) {
    int deltaX = point2X - point1X;
    int deltaY = point2Y - point1Y;
    int absDeltaX = abs(deltaX);
    int absDeltaY = abs(deltaY);
    int error = 2 * absDeltaY - absDeltaX;
    int twoDeltaY = 2 * absDeltaY;
    int twoDeltaYDeltaX = 2 * (absDeltaY - absDeltaX);
    int x, y, xEnd;

    if (point1X > point2X) {
        x = point2X;
        y = point2Y;
        xEnd = point1X;
    }
    else {
        x = point1X;
        y = point1Y;
        xEnd = point2X;
    }

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

    while (x < xEnd) {
        x++;
        if (error < 0) {
            error += twoDeltaY;
        }
        else {
            if (deltaY < 0) {
                y--;
            }
            else {
                y++;
            }
            error += twoDeltaYDeltaX;
        }
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
    }
}

// Mouse button callback to capture points
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
