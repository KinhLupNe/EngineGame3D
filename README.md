# EngineGame3D

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg) ![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)
![Dependencies](https://img.shields.io/badge/Dependencies-None-critical)

EngineGame3D là một trình kết xuất 3D chạy trong terminal được viết hoàn toàn bằng C++20. Dự án mang tính học thuật: tái hiện pipeline đồ hoạ từ đầu mà không sử dụng OpenGL, SDL hay các thư viện bên ngoài. Engine thực hiện đầy đủ pipeline Model → View → Projection và hiển thị kết quả bằng ký tự ASCII ngay trong cửa sổ console.

## Tính năng

- Kết xuất các primitive cơ bản và mô hình mesh.
- Các phép biến đổi Model, World, Camera, Clip và Viewport.
- Cắt xén sáu mặt phẳng frustum và loại bỏ mặt sau.
- Quét raster hoá đường ASCII.
- Điều khiển bàn phím để di chuyển mô hình (`W/S`, `A/D`, `Z/C`).

## Demo

![demo cube](./assets/demo.jpg)
<video controls src="./demo.mp4" style="max-width:100%; height:auto;">
  Trình duyệt của bạn không hỗ trợ phát video.
</video>

## Kiến trúc

```text
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
                                                                  ▼
                                                         ASCII Rendering
```

## Pipeline

1. **Vertex shader** – chuyển đổi đỉnh bằng ma trận `Model * View * Projection`.
2. **Cắt xén** – thuật toán Sutherland–Hodgman với sáu mặt phẳng frustum.
3. **Loại bỏ mặt sau** – loại bỏ tam giác quay lưng với camera.
4. **Lắp ráp primitive** – chuyển bộ chỉ số thành các tam giác.
5. **NDC → Viewport** – ánh xạ toạ độ lên không gian terminal.
6. **Rasterization** – vẽ cạnh tam giác bằng thuật toán nội suy tuyến tính đơn giản.

## Cấu trúc thư mục

```
Core/       Tiện ích Buffer và Camera
Geometry/   Định nghĩa Mesh, Model và Vertex
Pipeline/   Logic pipeline và cắt xén
Render/     Bộ kết xuất ASCII
Scene/      Quản lý cảnh
Math/       Toán vector và ma trận
Engine3D.cpp  Điểm vào chương trình
```

## Biên dịch

### Yêu cầu

- CMake 3.8 trở lên
- Trình biên dịch hỗ trợ C++20 (MSVC, GCC, Clang)

### Cấu hình và build

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

Sau khi build, chạy file thực thi (`Engine3D.exe` trên Windows). Cửa sổ terminal sẽ hiển thị một khối lập phương bằng ký tự ASCII; bạn có thể di chuyển mô hình bằng các phím đã liệt kê ở trên.

## Lộ trình

- [ ] Tô phẳng (flat shading)
- [ ] Minh hoạ bộ đệm độ sâu (Depth/Z)
- [ ] Tô đầy tam giác
- [ ] Nhiều mô hình và di chuyển camera

## Giấy phép

MIT License

---

Dự án được tạo ra cho mục đích học tập và tái hiện các thành phần chính của pipeline đồ hoạ bằng tay.

