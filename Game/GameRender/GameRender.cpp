/**
 * @file GamgRender.h
 * @brief khởi tạo engine, world
 * @detail trên thiết kế là nơi xử lí hiện cho game
 * @detail cup cấp api cho game dev từ engine, không chạm vào quá sâu chi tiết engine
 * @detail thực tế thì chưa có thời gian làm :v
 */
#include "GameRender.h"

GameRender::GameRender(const int &width, const int &height)
    : renderer(width, height) {
}


