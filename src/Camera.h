#ifndef CAMERA_H // Convención: nombre del archivo en mayúsculas, _H
#define CAMERA_H

#include <cmath>
#include <GLFW/glfw3.h>

/**
 * Camera class to handle 3D movement and perspective
 */
class Camera {
    private:
        float posX, posY, posZ;    // Camera position
        float frontX, frontY, frontZ; // Camera direction
        float upX, upY, upZ;       // Up vector
        float yaw, pitch;          // Euler angles
        float speed;               // Movement speed
    
    public:
        Camera() : 
            posX(0.0f), posY(-2.0f), posZ(10.0f),  // Position camera higher and further back
    
            frontX(0.0f), frontY(0.0f), frontZ(-1.0f),
            upX(0.0f), upY(1.0f), upZ(0.0f),
            yaw(-90.0f), pitch(0.0f),
            speed(0.1f) {  // Increase movement speed
                updateCameraVectors();
        }
        
        // Updates the camera's directional vectors based on yaw and pitch
        void updateCameraVectors();
        
        void moveUp();
        void moveDown();
        // Move the camera forward
        void moveForward();
        
        // Move the camera backward
        void moveBackward();
        
        // Move the camera to the left
        void moveLeft();
        
        // Move the camera to the right
        void moveRight();
        
        // Process mouse movement for camera rotation
        void processMouseMovement(float xoffset, float yoffset, bool constrainPitch= true);
        
        // Calculate and apply view matrix for OpenGL
        void applyViewMatrix();
        
        // Getters for camera properties
        float getPosX() const;
        float getPosY() const;
        float getPosZ() const;
        float getFrontX() const;
        float getFrontY() const;
        float getFrontZ() const;
};

#endif