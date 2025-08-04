#include "GameRender.h"

GameRender::GameRender(const int &width, const int &height)
    : renderer(width, height) {

}
void GameRender::drawWorld(const World &world) {
  auto list = world.getVisualBlockPos();
  for (auto &v : list) {
    drawBlock(BlockType::STONE, v);
  }
}
void GameRender::drawBlock(const BlockType &block, const Vec3 &position) {
  if (block == BlockType::STONE)
    renderer.drawBlock(position, &m);
  renderer.loadFromModel(&m);
}
