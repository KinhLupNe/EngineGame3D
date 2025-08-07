#ifndef GAMERENDER_H
#define GAMERENDER_H

#include "..//..//Render/Render.h"
#include "..//World/World.h"

class GameRender {
    // private:

private:
    Render renderer;
    Mesh mBlock = Mesh::createCube(1.0f, 1.0f, 1.0f);
    Mesh nWorld;
    World *world;

public:
    GameRender() = default;

    GameRender(const int &width, const int &height);

    ~GameRender() = default;

    //TODO: cung cấp api hữu ích cho game dev

    //--------getter , setter------------
    Render &getRenderer() {
        return renderer;
    }

    void setRenderer(const Render &renderer) {
        this->renderer = renderer;
    }

    Mesh getMBlock() {
        return mBlock;
    }

    void setMBlock(const Mesh &m_block) {
        mBlock = m_block;
    }

    Mesh &getNWorld() {
        return nWorld;
    }

    void setNWorld(const Mesh &n_world) {
        nWorld = n_world;
    }

    World *getWorld() const {
        return world;
    }

    void setWorld(World *world) {
        this->world = world;
    }
};
#endif
