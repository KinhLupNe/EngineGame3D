
#include "Engine3D.h"
#include "Core/Buffer.h"
#include "Core/Camera.h"
#include "Core/VoxelGrid.h"
#include "Debugger/DebugLogger.h"
#include "Game/Game/Game.h"
#include "Game/GameRender/GameRender.h"
#include "Game/World/World.h"
#include "Geometry/Mesh.h"
#include "Geometry/Model.h"
#include "Math/Math.h"
#include "Pipeline/Pipeline.h"
#include "Render/Render.h"
#include "Scene/Scene.h"
#include <chrono>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <random>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;
#define WIDTH 200
#define HEIGHT 70

#include <cstdlib>
#include <fstream>

char buf[HEIGHT][WIDTH];
float zbuf[HEIGHT][WIDTH];
void resetZbuffer() {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      zbuf[i][j] = 100.0f;
    }
  }
}
void gotoXY(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void setColor(int textColor, int bgColor) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}
void hide_cursor() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;

  // Lấy thông tin hiện tại của con trỏ
  GetConsoleCursorInfo(hConsole, &cursorInfo);

  // Ẩn con tr
  cursorInfo.bVisible = FALSE;
  SetConsoleCursorInfo(hConsole, &cursorInfo);
}

std::string build_frame() {
  std::string frame;
  frame.reserve(HEIGHT * (WIDTH + 1));
  for (int i = 0; i < HEIGHT; i++) {
    frame.append(buf[i], WIDTH);
    frame.push_back('\n');
  }
  return frame;
}

int main() {
  // Render render = Render(WIDTH, HEIGHT);
  /*GameRender gameRender = GameRender(WIDTH, HEIGHT);
  Camera cam = Camera(Vec3(0, 0, 8), 0, 0, 0.5f, 100.0f,
                      (float(WIDTH) / float(HEIGHT)) * 0.5f, 3.14 / 3);

  gameRender.renderer.scene.camera = &cam;
  // tạo world và load vào trong gameRender
  World world = World(5, 1, 5);
  world.init();
  gameRender.world = &world;
  // tạo grid, load world vào grid, build mesh của world đẩy vào trong
  // gameRender
  VoxelGrid grid(16, 16, 16);
  grid.loadGridFromWord(gameRender.world);
  Mesh::buildMesh(grid, gameRender.nWorld);

  // gameRender.drawWorld(world);
  //  tạo model chứ mesh thế giới
  Model model = Model(Vec3(0, 0, 0), &gameRender.nWorld);
  // load vào trong vbos, ibos;
  gameRender.renderer.loadFromModel(model);
  gameRender.renderer.scene.addModel(&model);*/
  Game game = Game();
  hide_cursor();
  // fps
  const double FPS_SET = 60.0;
  const double UPS_SET = 60.0;

  // Tính thời gian mỗi frame/update tính theo nanosecond
  const double timePerFrame = 1e9 / FPS_SET;
  const double timePerUpdate = 1e9 / UPS_SET;

  // Thời điểm bắt đầu vòng lặp
  auto previousTime = std::chrono::high_resolution_clock::now();
  auto lastCheck = previousTime;

  int updates = 0;
  int frames = 0;
  double deltaU = 0.0;
  double deltaF = 0.0;

  /*Mesh cube = Mesh::createCube(1, 1, 1);
  Model model(&cube);
  Model model1(&cube);

  render.loadFromModel(model)
  render.loadFromModel(model1);

  Camera cam = Camera(Vec3(0, 0, 50), 0, 0, 0.1f, 100.0f,
                      (float(WIDTH) / float(HEIGHT)) * 0.5f, 3.14 / 3);

  model.position = Vec3(10, 0, 10);
  //  model.rotation = Vec3(3.14 / 6, 3.14 / 6, 3.14 / 6);
  model1.position = Vec3(25, 5, 15);
  model1.rotation = Vec3(3.14 / 6, 3.14 / 6, 3.14 / 6);

  Scene scene;
  scene.camera = &cam;
  scene.addModel(&model);
  scene.addModel(&model1);
  render.scene = scene;
*/
  // scene :: camera + model
  // buffer :: vbo + ibo

  while (true) {
    // render.scene.camera->camAngle =
    //  render.scene.camera->camAngle + Vec3(-3.14 / 100, 0, 0);
    // render.scene.models[0]->rotation =
    //  render.scene.models[0]->rotation +
    //(Vec3(3.14 / 100, 3.14 / 100, 3.14 / 100));
    /*render.scene.models[1]->rotation =
        render.scene.models[0]->rotation +
        (Vec3(3.14 / 200, 3.14 / 200, 3.14 / 200));*/

    // fps
    auto currentTime = std::chrono::high_resolution_clock::now();
    // Tính khoảng thời gian trôi qua (nanosecond)
    double elapsed =
        std::chrono::duration<double, std::nano>(currentTime - previousTime)
            .count();
    previousTime = currentTime;

    // 2. Cộng dồn delta cho update và frame
    deltaU += elapsed / timePerUpdate;
    deltaF += elapsed / timePerFrame;

    // 3. Nếu đủ 1 unit thì chạy update logic
    if (deltaU >= 1.0) {
      // --- update game logic tại đây ---
      game.updateLogic();
      updates++;
      deltaU -= 1.0;
    }

    // 4. Nếu đủ 1 unit thì render 1 frame
    if (deltaF >= 1.0) {
      // --- render / present tại đây ---
      setColor(5, 0);
      game.updateRender();
      frames++;
      deltaF -= 1.0;
    }

    // 5. Mỗi 1 giây in ra FPS và UPS, rồi reset bộ đếm
    if (std::chrono::duration_cast<std::chrono::seconds>(currentTime -
                                                         lastCheck)
            .count() >= 1) {
      lastCheck = currentTime;
      auto &log = DebugLogger::Instance();
      log.LogAt(1, 9,
                "fps: " + std::to_string(frames) +
                    " | ups: " + std::to_string(updates));
      frames = 0;
      updates = 0;
    }

    Sleep(1);
    // (Tuỳ chọn) sleep 1ms để tránh busy-wait quá nặng
    // std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  return 0;
}
