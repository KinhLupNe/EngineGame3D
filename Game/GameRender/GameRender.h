#ifndef GAMERENDER_H
#define GAMERENDER_H
#include "..//..//Core/Camera.h"
#include "..//..//Render/Render.h"
#include "..//World/Block.h"
#include "..//World/World.h"
class GameRender {
  // private:

public:
  Render renderer;
  Mesh mBlock = Mesh::createCube(1.0f, 1.0f, 1.0f);
  Mesh nWorld;
  World *world;

  GameRender() = default;
  GameRender(const int &width, const int &height);
  ~GameRender() = default;
  //  void init(int width, int height);

  // void setCamera(const Camera *camera);
  void drawWorld(const World &world);
  void drawBlock(const BlockType &block, const Vec3 &position);
  // void drawText(const std::string &text, const Vec2 &position);
  // void present();
};
#endif
