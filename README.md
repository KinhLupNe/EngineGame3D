# EngineGame3D

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg) ![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)
![Dependencies](https://img.shields.io/badge/Dependencies-None-critical)

EngineGame3D là một trình kết xuất 3D chạy trong terminal được viết hoàn toàn bằng C++20. Dự án mang tính học thuật: tái hiện pipeline đồ hoạ từ đầu mà không sử dụng OpenGL, SDL hay các thư viện bên ngoài. Engine hiển thị kết quả bằng ký tự ASCII ngay trong cửa sổ console. 


## Demo

![demo cube](./assets/demo.jpg)


https://github.com/user-attachments/assets/3aa335b5-0aa1-4bc7-b1d4-7adcd95303ec



## Kiến trúc

```text

          ┌────────┐
          │ Object │ 
          └────┬───┘
               ▼
               │
               │   neibor-face culling 
               │ 
               ▼
          ┌────────┐
          │ Scene  │
          └────┬───┘
               ▼
        ┌────────────┐
        │   Model    │────────┐
        └────┬───────┘        │
             ▼                ▼
        ┌────────┐      ┌────────┐
        │ Mesh   │─────▶│ Buffer │
        └────────┘      └────────┘
                               │
              ┌────────────────────────────────────┐
              ▼                                    ▼
        Vertex Shader ──▶ Clipping & Culling ──▶ Assembly ──▶ Rasterization
                         (Frustum 6-plane)       (to triangle)   │
                                                                 │ 
                                                                 ▼
                                                          fragment-shader(lighting)
                                                                   │
                                                                   │
                                                                   ▼
                                                         ASCII Rendering
```

## Trước pipline
1.**Model Object**  model tạo bởi các mesh có mặt gần nhau sẽ được tối ưu bằng thuật toán Neirbor-face culling
## Pipeline
1. **Vertex shader** – chuyển đổi đỉnh bằng ma trận `Model * View * Projection`.
2. **Cắt xén** – thuật toán Sutherland–Hodgman với sáu mặt phẳng frustum.
3. **Loại bỏ mặt sau** – loại bỏ tam giác quay lưng với camera.
4. **Lắp ráp primitive** – chuyển bộ chỉ số thành các tam giác.
5. **NDC → Viewport** – ánh xạ toạ độ lên không gian terminal.
6. **Rasterization** – vẽ cạnh tam giác bằng thuật toán nội suy tuyến tính đơn giản.

## Cấu trúc thư mục

```
Core/       Tiện ích Buffer và Camera, ánh sáng
Geometry/   Định nghĩa Mesh, Model và Vertex
Pipeline/   Logic pipeline và cắt xén
Render/     Bộ kết xuất ASCII
Scene/      Quản lý cảnh
Math/       Toán vector và ma trận
Engine3D.cpp  Điểm vào chương trình
Tools hàm tiện ích
Game/ game dựa trên engine
Debug/ nơi code debug log
```

## Biên dịch

### Yêu cầu

- CMake 3.8 trở lên
- Trình biên dịch hỗ trợ C++20 (MSVC, GCC, Clang)

### Cấu hình và build
``` terminal
Chỉnh chiều ngang terminal lên trên 300, chiều dọc trên 105 , cũng như chỉnh kí tự nhỏ xuống khoảng 6.

```bash
cmake -S . -B build
cmake --build build
```

Hoặc sử dụng preset nếu có:

```bash
cmake --preset x64-debug
cmake --build out/build/x64-debug
```

## Chạy

Sau khi build, chạy file thực thi (`Engine3D.exe` trên Windows).
Có rất nhiều game mà tôi sẽ phát triển dựa vào engine này, bạn vào thư mục game, chỉ cần gọi ra là trải nghiệm game đó

## Giấy phép

MIT License

---

Dự án được tạo ra cho mục đích học tập và tái hiện các thành phần chính của pipeline đồ hoạ bằng tay.

