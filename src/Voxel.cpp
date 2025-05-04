#include "Voxel.h"

void Voxel::draw() {
    if (!active) return;
    
    float halfSize = size / 2.0f;
    
    // We're using immediate mode to ensure compatibility
    // In a more modern OpenGL implementation, we would use VBOs
    glBegin(GL_QUADS);
    
    // Set color for the voxel
    glColor3f(r, g, b);
    
    // Front face
    glVertex3f(x - halfSize, y - halfSize, z + halfSize);
    glVertex3f(x + halfSize, y - halfSize, z + halfSize);
    glVertex3f(x + halfSize, y + halfSize, z + halfSize);
    glVertex3f(x - halfSize, y + halfSize, z + halfSize);
    
    // Back face
    glVertex3f(x - halfSize, y - halfSize, z - halfSize);
    glVertex3f(x - halfSize, y + halfSize, z - halfSize);
    glVertex3f(x + halfSize, y + halfSize, z - halfSize);
    glVertex3f(x + halfSize, y - halfSize, z - halfSize);
    
    // Top face
    glVertex3f(x - halfSize, y + halfSize, z - halfSize);
    glVertex3f(x - halfSize, y + halfSize, z + halfSize);
    glVertex3f(x + halfSize, y + halfSize, z + halfSize);
    glVertex3f(x + halfSize, y + halfSize, z - halfSize);
    
    // Bottom face
    glVertex3f(x - halfSize, y - halfSize, z - halfSize);
    glVertex3f(x + halfSize, y - halfSize, z - halfSize);
    glVertex3f(x + halfSize, y - halfSize, z + halfSize);
    glVertex3f(x - halfSize, y - halfSize, z + halfSize);
    
    // Left face
    glVertex3f(x - halfSize, y - halfSize, z - halfSize);
    glVertex3f(x - halfSize, y - halfSize, z + halfSize);
    glVertex3f(x - halfSize, y + halfSize, z + halfSize);
    glVertex3f(x - halfSize, y + halfSize, z - halfSize);
    
    // Right face
    glVertex3f(x + halfSize, y - halfSize, z - halfSize);
    glVertex3f(x + halfSize, y + halfSize, z - halfSize);
    glVertex3f(x + halfSize, y + halfSize, z + halfSize);
    glVertex3f(x + halfSize, y - halfSize, z + halfSize);
    
    glEnd();
}

// Toggle the active state of the voxel
void Voxel::toggleActive() {
    active = !active;
}

// Check if a point is inside this voxel
bool Voxel::containsPoint(float px, float py, float pz) {
    float halfSize = size / 2.0f;
    return (px >= x - halfSize && px <= x + halfSize &&
            py >= y - halfSize && py <= y + halfSize &&
            pz >= z - halfSize && pz <= z + halfSize);
}