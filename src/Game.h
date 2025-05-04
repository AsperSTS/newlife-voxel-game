#ifndef GAME_H // Convención: nombre del archivo en mayúsculas, _H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

#include "Camera.h"
#include "Grid.h"
/**
 * Game class to manage the game loop and rendering
 */
class Game {
    private:
        GLFWwindow* window;
        const int width = 1728;
        const int height = 972;
        
        Camera camera;
        Grid grid;
        
        // Mouse input tracking
        double lastX, lastY;
        bool firstMouse;
        
        // Key states
        std::unordered_map<int, bool> keyPressed;
        
        bool initializeWindow();
        
        void setupCallbacks();
        
        void keyCallback(int key, int scancode, int action, int mods);
        
        void mouseCallback(double xpos, double ypos);
        
        void mouseButtonCallback(int button, int action, int mods);
        
        void handleInput();
        
        void setupOpenGL();
    
    public:
        Game() : window(nullptr), firstMouse(true) {}
    
        bool initialize();
    
        void run();
    
        void update();
    
        void render();
    
        ~Game();
    };

#endif