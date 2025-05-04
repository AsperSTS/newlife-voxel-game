#include "Grid.h"

// Draw the coordinate grid (the 3D Cartesian coordinate system)
void Grid::drawCoordinateSystem() {
    // Make lines thicker for better visibility
    glLineWidth(2.0f);
    
    // X-axis (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(-gridSize * cellSize, 0.0f, 0.0f);
    glVertex3f(gridSize * cellSize, 0.0f, 0.0f);
    glEnd();
    
    // Y-axis (Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, -gridSize * cellSize, 0.0f);
    glVertex3f(0.0f, gridSize * cellSize, 0.0f);
    glEnd();
    
    // Z-axis (Blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, -gridSize * cellSize);
    glVertex3f(0.0f, 0.0f, gridSize * cellSize);
    glEnd();
    
    // Reset line width
    glLineWidth(1.0f);
    
    // Draw grid lines for X-Z plane (ground)
    glColor3f(0.5f, 0.5f, 0.5f); // Gray
    glBegin(GL_LINES);
    // Draw lines along X axis
    for (int i = -gridSize; i <= gridSize; i++) {
        if (i == 0) continue; // Skip the axis line as it's already drawn
        glVertex3f(i * cellSize, 0.0f, -gridSize * cellSize);
        glVertex3f(i * cellSize, 0.0f, gridSize * cellSize);
    }
    // Draw lines along Z axis
    for (int i = -gridSize; i <= gridSize; i++) {
        if (i == 0) continue; // Skip the axis line as it's already drawn
        glVertex3f(-gridSize * cellSize, 0.0f, i * cellSize);
        glVertex3f(gridSize * cellSize, 0.0f, i * cellSize);
    }
    glEnd();
}

// Draw all voxels
void Grid::drawVoxels() {
    for (const auto& voxel : voxels) {
        voxel->draw();
    }
}

// Add a voxel at the specified position
void Grid::addVoxel(float x, float y, float z, float r, float g, float b) {
    voxels.push_back(std::make_shared<Voxel>(x, y, z, cellSize, r, g, b));
}

// Remove a voxel at the specified position
bool Grid::removeVoxel(float x, float y, float z) {
    for (auto it = voxels.begin(); it != voxels.end(); ++it) {
        if ((*it)->containsPoint(x, y, z)) {
            voxels.erase(it);
            return true;
        }
    }
    return false;
}