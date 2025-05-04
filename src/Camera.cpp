#include "Camera.h"

// Updates the camera's directional vectors based on yaw and pitch
void Camera::updateCameraVectors() {
    // Calculate the new front vector
    // Convert degrees to radians
    float yawRad = yaw * 3.14159f / 180.0f;
    float pitchRad = pitch * 3.14159f / 180.0f;
    
    frontX = cos(yawRad) * cos(pitchRad);
    frontY = sin(pitchRad);
    frontZ = sin(yawRad) * cos(pitchRad);
    
    // Normalize the front vector
    float length = sqrt(frontX * frontX + frontY * frontY + frontZ * frontZ);
    frontX /= length;
    frontY /= length;
    frontZ /= length;
}

void Camera::moveUp(){ // Test function
    posY -=  speed;
}
void Camera::moveDown(){
    posY += speed;
}
// Move the camera forward
void Camera::moveForward() {
    posX += frontX * speed;
    posY += frontY * speed;
    posZ += frontZ * speed;
}

// Move the camera backward
void Camera::moveBackward() {
    posX -= frontX * speed;
    posY -= frontY * speed;
    posZ -= frontZ * speed;
}

// Move the camera to the left
void Camera::moveLeft() {
    // Cross product of front and up vector to get the right vector
    float rightX = frontZ * upY - frontY * upZ;
    float rightY = frontX * upZ - frontZ * upX;
    float rightZ = frontY * upX - frontX * upY;
    
    // Normalize the right vector
    float length = sqrt(rightX * rightX + rightY * rightY + rightZ * rightZ);
    rightX /= length;
    rightY /= length;
    rightZ /= length;
    
    // Move left (opposite of right)
    posX -= rightX * speed;
    posY -= rightY * speed;
    posZ -= rightZ * speed;
}

// Move the camera to the right
void Camera::moveRight() {
    // Cross product of front and up vector to get the right vector
    float rightX = frontZ * upY - frontY * upZ;
    float rightY = frontX * upZ - frontZ * upX;
    float rightZ = frontY * upX - frontX * upY;
    
    // Normalize the right vector
    float length = sqrt(rightX * rightX + rightY * rightY + rightZ * rightZ);
    rightX /= length;
    rightY /= length;
    rightZ /= length;
    
    // Move right
    posX += rightX * speed;
    posY += rightY * speed;
    posZ += rightZ * speed;
}

// Process mouse movement for camera rotation
void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    yaw -= xoffset * 0.1f;
    pitch -= yoffset * 0.1f;
    
    // Constrain pitch to avoid camera flipping
    if (constrainPitch) {
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
    }
    
    // Update the camera vectors based on the updated angles
    updateCameraVectors();
}

// Calculate and apply view matrix for OpenGL
void Camera::applyViewMatrix() {
    // Create a look-at matrix without using gluLookAt
    // This is a manual implementation of the view matrix
    
    // 1. Calculate camera right vector
    float rightX, rightY, rightZ;
    rightX = frontZ * upY - frontY * upZ;
    rightY = frontX * upZ - frontZ * upX;
    rightZ = frontY * upX - frontX * upY;
    
    // Normalize right vector
    float rightLength = sqrt(rightX * rightX + rightY * rightY + rightZ * rightZ);
    rightX /= rightLength;
    rightY /= rightLength;
    rightZ /= rightLength;
    
    // 2. Recalculate up vector (to ensure orthogonality)
    float newUpX, newUpY, newUpZ;
    newUpX = rightY * frontZ - rightZ * frontY;
    newUpY = rightZ * frontX - rightX * frontZ;
    newUpZ = rightX * frontY - rightY * frontX;
    
    // 3. Create the view matrix
    float viewMatrix[16] = {
        rightX, newUpX, -frontX, 0,
        rightY, newUpY, -frontY, 0,
        rightZ, newUpZ, -frontZ, 0,
        0, 0, 0, 1
    };
    
    // 4. Apply translation
    float translation[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        -posX, -posY, -posZ, 1
    };
    
    // Apply the view transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // First apply rotation
    glMultMatrixf(viewMatrix);
    
    // Then apply translation
    // We can do this with a simple translation instead of matrix multiplication
    glTranslatef(-posX, -posY, -posZ);
}

// Getters for camera properties
float Camera::getPosX() const { return posX; }
float Camera::getPosY() const { return posY; }
float Camera::getPosZ() const { return posZ; }
float Camera::getFrontX() const { return frontX; }
float Camera::getFrontY() const { return frontY; }
float Camera::getFrontZ() const { return frontZ; }