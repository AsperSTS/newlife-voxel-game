#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream> 
#include <vector>
#include <memory>

class Game {
private:
    GLFWwindow* window;
    const int width = 800;
    const int height = 600;
    
    bool initializeWindow() {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return false;
        }

        // OpenGL 3.3 core profile
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, "Voxel Game", nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK) {
            std::cerr << "Failed to initialize GLEW" << std::endl;
            return false;
        }

        return true;
    }

public:
    Game() : window(nullptr) {}

    bool initialize() {
        return initializeWindow();
    }

    void run() {
        while (!glfwWindowShouldClose(window)) {
            // Clear the screen
            glClear(GL_COLOR_BUFFER_BIT);
            
            // Game loop here
            update();
            render();

            // Swap buffers and poll events
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void update() {
        // Update game state
    }

    void render() {
        // Render game objects
    }

    ~Game() {
        if (window) {
            glfwDestroyWindow(window);
        }
        glfwTerminate();
    }
};

int main() {
    Game game;
    
    if (!game.initialize()) {
        return -1;
    }

    game.run();
    return 0;
}
