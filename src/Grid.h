#ifndef GRID_H // Convención: nombre del archivo en mayúsculas, _H
#define GRID_H

#include <vector>
#include <memory>

#include "Voxel.h"
/**
 * Grid class to represent the 3D coordinate system and voxel world
 */
class Grid {
    private:
        int gridSize;         // Number of grid lines in each direction
        float cellSize;       // Size of each grid cell
        std::vector<std::shared_ptr<Voxel>> voxels; // Collection of voxels
    
    public:
        Grid(int gridSize = 20, float cellSize = 1.0f) : gridSize(gridSize), cellSize(cellSize) {
            // Initialize with some example voxels
            // Create a ground plane of voxels
            for (int x = -5; x <= 5; x++) {
                for (int z = -5; z <= 5; z++) {
                    // Create a checkered pattern
                    float color = ((x + z) % 2 == 0) ? 0.2f : 0.8f;
                    
                    voxels.push_back(std::make_shared<Voxel>(
                        x * cellSize, -1.0f, z * cellSize, cellSize,
                        color, color * 0.8f, color * 0.6f
                    ));
                }
            }
            
            // Add some blocks above the ground
            voxels.push_back(std::make_shared<Voxel>(0, 0.0f, 0, cellSize, 1.0f, 0.0f, 0.0f)); // Red
            voxels.push_back(std::make_shared<Voxel>(2.0f, 0.0f, 0, cellSize, 0.0f, 1.0f, 0.0f)); // Green
            voxels.push_back(std::make_shared<Voxel>(0, 0.0f, 2.0f, cellSize, 0.0f, 0.0f, 1.0f)); // Blue
            
            // Add a small tower
            for (int y = 0; y < 3; y++) {
                voxels.push_back(std::make_shared<Voxel>(-2.0f, y * cellSize, -2.0f, cellSize, 
                    0.8f, 0.8f, 0.2f)); // Yellow-ish
            }
        }
        
        // Draw the coordinate grid (the 3D Cartesian coordinate system)
        void drawCoordinateSystem();
        
        // Draw all voxels
        void drawVoxels();
        
        // Add a voxel at the specified position
        void addVoxel(float x, float y, float z, float r, float g, float b);
        
        // Remove a voxel at the specified position
        bool removeVoxel(float x, float y, float z);
    };

#endif