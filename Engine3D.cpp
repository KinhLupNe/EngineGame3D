
#include "Engine3D.h"
#include "Core/Buffer.h"
#include "Debugger/DebugLogger.h"
#include "Game/Game/Game.h"
#include "Geometry/Mesh.h"
#include "Math/Math.h"
#include <chrono>
#include <conio.h>
#include <cstdlib>
#include <random>
#include <string>
#include <windows.h>
#include "Utilities/UtilitiesManager.h"
#include <fstream>
using namespace std;

//thông số màn hình
#define WIDTH 300
#define HEIGHT 105

int main() {
  // khởi tạo game
  Game game = Game();
  hide_cursor();

  // Xử lý fps tối ưu hiệu năng
  const double FPS_SET = 60.0;
  const double UPS_SET = 60.0;
  const double timePerFrame = 1e9 / FPS_SET;
  const double timePerUpdate = 1e9 / UPS_SET;

  // Thời điểm bắt đầu vòng lặp
  auto previousTime = std::chrono::high_resolution_clock::now();
  auto lastCheck = previousTime;

  int updates = 0;
  int frames = 0;
  double deltaU = 0.0;
  double deltaF = 0.0;

  // Game lopp / Vàng lặp game
  while (true) {
    // FPS UPS/ xử lý fps ps
    auto currentTime = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration<double, std::nano>(currentTime - previousTime).count();
    previousTime = currentTime;

    deltaU += elapsed / timePerUpdate;
    deltaF += elapsed / timePerFrame;

    // logic update / nơi logic của game cập nhật
    if (deltaU >= 1.0) {
      game.updateLogic();
      updates++;
      deltaU -= 1.0;
    }
    // render update / nơi hiển thị
    if (deltaF >= 1.0) {
      setColor(5, 0);
      game.updateRender();
      frames++;
      deltaF -= 1.0;
    }

    if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastCheck).count() >= 1) {
      lastCheck = currentTime;
      // debug log / hiện thị thông tin fps, ups trên cửa sổ thứ 2
      DebugLogger::Instance().LogAt(1, 9, "fps: " + std::to_string(frames) + " | ups: " + std::to_string(updates));
      frames = 0;
      updates = 0;
    }

    // theo chatGPT bảo cho máy nghỉ 1ms để khỏi quá tải, mất ổn dinh//
    Sleep(1);
  }

  return 0;
}
