#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <utility> // For std::pair
#include <cmath>   // For fabs

// Screen dimensions
const int WIDTH = 800, HEIGHT = 600;

// Image representation (3 colors for simplicity)
const int rows = 3;
const int cols = 3;
std::vector<std::vector<int>> img = {
    {1, 1, 1},
    {1, 1, 0},
    {1, 0, 1}
};

// Color definitions
const float colors[4][3] = {
    {1.0f, 1.0f, 1.0f}, // Color 0 (White)
    {0.0f, 0.0f, 1.0f}, // Color 1 (Blue)
    {1.0f, 0.0f, 0.0f}, // Color 2 (Red)
    {0.0f, 1.0f, 0.0f}  // Color 3 (Green)
};

// Flood fill algorithm
void dfs(std::vector<std::vector<int>>& img, int x, int y, int prevClr, int newClr) {
    if (img[x][y] != prevClr)
        return;

    // Marking it as the new color
    img[x][y] = newClr;

    // Moving up, right, down and left one by one
    int n = img.size();
    int m = img[0].size();
    if (x - 1 >= 0)
        dfs(img, x - 1, y, prevClr, newClr);
    if (y + 1 < m)
        dfs(img, x, y + 1, prevClr, newClr);
    if (x + 1 < n)
        dfs(img, x + 1, y, prevClr, newClr);
    if (y - 1 >= 0)
        dfs(img, x, y - 1, prevClr, newClr);
}

// Flood fill function
void floodFill(int x, int y, int newClr) {
    int prevClr = img[x][y];
    if (prevClr == newClr)
        return;
    dfs(img, x, y, prevClr, newClr);
}

// Draw the grid
void drawGrid() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            glColor3f(colors[img[i][j]][0], colors[img[i][j]][1], colors[img[i][j]][2]);
            glBegin(GL_QUADS);
            glVertex2f(j * (WIDTH / cols), i * (HEIGHT / rows));
            glVertex2f((j + 1) * (WIDTH / cols), i * (HEIGHT / rows));
            glVertex2f((j + 1) * (WIDTH / cols), (i + 1) * (HEIGHT / rows));
            glVertex2f(j * (WIDTH / cols), (i + 1) * (HEIGHT / rows));
            glEnd();
        }
    }
    glFlush();
}

// Mouse click callback
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Convert the mouse coordinates to grid coordinates
        int x = static_cast<int>(mouseY / (HEIGHT / rows));
        int y = static_cast<int>(mouseX / (WIDTH / cols));

        // Perform flood fill on the clicked position
        floodFill(x, y, 3); // Change to color index 3 (Green)
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Flood Fill Algorithm (OpenGL)", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Set the mouse button callback
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen to white
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the grid
        drawGrid();

        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
