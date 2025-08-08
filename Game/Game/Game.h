/**
 * @file Game.h
 * @brief main game / Khởi tạo, chứa mọi thông sô, logic, render của game
 */
#ifndef GAME_H
#define GAME_H
#include "../Entities/Player.h"
#include "../GameRender/GameRender.h"

class Game {
private:
  GameRender gameRender;
  Camera cam;
  World world;
  Player player;
  std::vector<Model> models;

  // khởi tạo thông số ban đầu của game và enigne
  void init();

public:
  Game();

  ~Game();

  void updateLogic();

  void updateRender();

  // -------------------setter getter--------------------------------
  GameRender &getGameRender() { return gameRender; }

  void setGameRender(const GameRender &gameRender) {
    this->gameRender = gameRender;
  }

  Camera &getCam() { return cam; }

  void setCam(const Camera &cam) { this->cam = cam; }

  World &getWorld() { return world; }

  void setWorld(const World &world) { this->world = world; }

  Player &getPlayer() { return player; }

  void setPlayer(const Player &player) { this->player = player; }
};
#endif
