#include "World.h"

void World::init() {
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < width; j++) {
            setBlock(j, 0, i, BlockType::STONE); // Set the ground to stone
        }
    }
}

/**
 * @brief khởi tạo ban đầu cho world
 * @param width chiều rộng  x
 * @param height chiều cao y
 * @param depth chiều sâu z
 */
World::World(int width, int height, int depth)
    : width(width), height(height), depth(depth) {
    data.resize(width * height * depth, BlockType::AIR);
}

void World::setBlock(int x, int y, int z, BlockType blockType) {
    if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth) {
        return;
    }
    data[x + y * width + z * width * height] = blockType;
}

BlockType World::getDataBlock(int x, int y, int z) const {
    if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth) {
        return BlockType::AIR;
    }
    return data[x + y * width + z * width * height];
}

std::vector<Vec3> World::getVisualBlockPos() const {
    std::vector<Vec3> res;
    for (int z = 0; z < depth; z++) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (getDataBlock(x, y, z) != BlockType::AIR) {
                    res.push_back(Vec3(x, y, z));
                }
            }
        }
    }
    return res;
}


