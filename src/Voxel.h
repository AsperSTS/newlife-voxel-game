#ifndef VOXEL_H // Convención: nombre del archivo en mayúsculas, _H
#define VOXEL_H

#include <GLFW/glfw3.h>

/**
 * Voxel class to represent a single voxel in the game world
 */
class Voxel {
    private:
        float x, y, z;    // Position
        float size;       // Size of the voxel
        float r, g, b;    // Color
        bool active;      // Whether the voxel is active (visible)
    
    public:
        Voxel(float x, float y, float z, float size, float r, float g, float b) :
            x(x), y(y), z(z), size(size), r(r), g(g), b(b), active(true) {}
        
        void draw();
        
        // Toggle the active state of the voxel
        void toggleActive();
        
        // Check if a point is inside this voxel
        bool containsPoint(float px, float py, float pz);
    };

#endif // VOXEL_H