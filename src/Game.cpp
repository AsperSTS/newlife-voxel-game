#include "Game.h"
bool Game::initializeWindow(){
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // For compatibility, use the compatibility profile instead of core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    window = glfwCreateWindow(width, height, "VoxelGamev0.01 - FPS: 0", nullptr, nullptr);
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    std::cout<<"Setting up the input mode\n";


    // Print OpenGL version
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    
    // Setup input callbacks
    setupCallbacks();
    
    // Initialize mouse position
    lastX = width / 2.0;
    lastY = height / 2.0;
    firstMouse = true;
    
    return true;
}

void Game::setupCallbacks() {
    // Set the user pointer to this instance for callbacks
    glfwSetWindowUserPointer(window, this);
    
    // Key callback
    glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods) {
        Game* game = static_cast<Game*>(glfwGetWindowUserPointer(w));
        game->keyCallback(key, scancode, action, mods);
    });
    
    // Mouse movement callback
    glfwSetCursorPosCallback(window, [](GLFWwindow* w, double xpos, double ypos) {
        Game* game = static_cast<Game*>(glfwGetWindowUserPointer(w));
        game->mouseCallback(xpos, ypos);
    });
    
    // Mouse button callback
    glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods) {
        Game* game = static_cast<Game*>(glfwGetWindowUserPointer(w));
        game->mouseButtonCallback(button, action, mods);
    });
}

void Game::keyCallback(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    
    // Track key states
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            keyPressed[key] = true;
        } else if (action == GLFW_RELEASE) {
            keyPressed[key] = false;
        }
    }
}

void Game::mouseCallback(double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Reversed: y-coordinates go from bottom to top
    
    lastX = xpos;
    lastY = ypos;
    
    camera.processMouseMovement(xoffset, yoffset);
}

void Game::mouseButtonCallback(int button, int action, int mods) {
    // Handle mouse clicks for adding/removing voxels
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // Add voxel in front of the camera
        grid.addVoxel(
            camera.getPosX() + camera.getFrontX() * 2.0f,
            camera.getPosY() + camera.getFrontY() * 2.0f,
            camera.getPosZ() + camera.getFrontZ() * 2.0f,
            0.7f, 0.2f, 0.2f  // Red-ish color
        );
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        // Remove voxel in front of the camera
        grid.removeVoxel(
            camera.getPosX() + camera.getFrontX() * 2.0f,
            camera.getPosY() + camera.getFrontY() * 2.0f,
            camera.getPosZ() + camera.getFrontZ() * 2.0f
        );
    }
}

void Game::handleInput() {
    // Process keyboard input for camera movement
    if (keyPressed[GLFW_KEY_W]) {
        camera.moveForward();
    }
    if (keyPressed[GLFW_KEY_S]) {
        camera.moveBackward();
    }
    if (keyPressed[GLFW_KEY_A]) {
        camera.moveLeft();
    }
    if (keyPressed[GLFW_KEY_D]) {
        camera.moveRight();
    }
    if (keyPressed[GLFW_KEY_UP]){
        camera.moveUp();
    }
    if (keyPressed[GLFW_KEY_DOWN]){
        camera.moveDown();
    }
}

void Game::setupOpenGL() {
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    
    // Disable lighting for now to ensure visibility
    glDisable(GL_LIGHTING);
    
    // Setup projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Field of view: 45 degrees, aspect ratio, near and far clipping planes
    float aspect = (float)width / (float)height;
    float fovY = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    
    // Set up a perspective projection matrix manually
    float f = 1.0f / tan((fovY * 3.14159f / 180.0f) / 2.0f);
    float projMatrix[16] = {
        f / aspect, 0, 0, 0,
        0, f, 0, 0,
        0, 0, (farPlane + nearPlane) / (nearPlane - farPlane), -1,
        0, 0, (2 * farPlane * nearPlane) / (nearPlane - farPlane), 0
    };
    
    glLoadMatrixf(projMatrix);
    
    // Switch to modelview matrix
    glMatrixMode(GL_MODELVIEW);
    
    // Set background color to light gray
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

/*
    PUBLIC
*/

bool Game::initialize() {
    return initializeWindow();
}

void Game::run() {
    setupOpenGL();
    
    double previousTime = glfwGetTime();
    int frameCount = 0;

    // Main game loop
    while (!glfwWindowShouldClose(window)) {

        double currentTime = glfwGetTime();
        frameCount++;

        if (currentTime - previousTime >= 1.0) {
            std::string title = "VoxelGamev0.01 - FPS: " + std::to_string(frameCount);
            glfwSetWindowTitle(window, title.c_str());
    
            frameCount = 0;
            previousTime = currentTime;
        }

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Game loop here
        handleInput();
        update();
        render();

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::update() {
    // Update game state
}

void Game::render() {
    // Reset modelview matrix
    glLoadIdentity();
    
    // Apply camera transformation using our custom view matrix function
    camera.applyViewMatrix();
    
    // Draw 3D Cartesian coordinate system
    grid.drawCoordinateSystem();
    
    // Draw voxels
    grid.drawVoxels();
}

Game::~Game() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}
