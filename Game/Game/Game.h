#ifndef GAME_H
#define GAME_H
#include "../GameRender/GameRender.h"

#include "../Enities/Player.h"
class Game {
public:
  GameRender gameRender;
  Camera cam;
  World world;
  Player player;
  Model model;

  Game();
  ~Game();

  void init();

  void updateLogic();

  void updateRender();
};
#endif
