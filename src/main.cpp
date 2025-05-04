#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include <iostream>
// #include <vector>
// #include <memory>
// #include <cmath>
// #include <unordered_map>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Voxel.h"
#include "Grid.h"
#include "Game.h"


/**
 * Main function to initialize and run the game
 */
int main() {
    Game game;
    
    if (!game.initialize()) {
        return -1;
    }

    game.run();
    return 0;
}