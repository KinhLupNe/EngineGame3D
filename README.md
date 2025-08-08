# EngineGame3D

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg) ![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey) ![Dependencies](https://img.shields.io/badge/Dependencies-None-critical)

EngineGame3D is a small educational 3D software renderer for the terminal.  The engine is written in modern C++20 and rebuilds the
graphics pipeline from scratch without using OpenGL, SDL, or other external libraries.  It transforms meshes through the full
Model → View → Projection pipeline and renders the result as ASCII characters directly in the console.

## Features

- Render basic primitives and mesh models.
- Model, world, camera, clip, and viewport transformations.
- Six-plane frustum clipping and backface culling.
- ASCII line rasterization.
- Keyboard controls for moving the model (`W/S`, `A/D`, `Z/C`).

## Demo

![demo cube](./assets/demo.jpg)
![demo hust](./assets/demo1.jpg)

## Architecture

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

1. **Vertex shader** – transforms vertices using `Model * View * Projection`.
2. **Clipping** – Sutherland–Hodgman clipping against six frustum planes.
3. **Backface culling** – removes triangles facing away from the camera.
4. **Primitive assembly** – converts index buffers to triangles.
5. **NDC → Viewport mapping** – maps coordinates to terminal space.
6. **Rasterization** – draws triangle edges with a simple line interpolation algorithm.

## Directory Structure

```
Core/       Buffer and Camera utilities
Geometry/   Mesh, Model, and Vertex definitions
Pipeline/   Pipeline logic and culling
Render/     ASCII renderer
Scene/      Scene management
Math/       Vector and matrix math
Engine3D.cpp  Entry point
```

## Build

### Prerequisites

- CMake 3.8 or later
- A compiler with C++20 support (MSVC, GCC, Clang)

### Configure and Build

```bash
cmake -S . -B build
cmake --build build
```

Or using presets if available:

```bash
cmake --preset x64-debug
cmake --build out/build/x64-debug
```

## Run

After building, run the produced executable (`Engine3D.exe` on Windows).  A terminal window will display an ASCII-rendered cube that
can be moved with the keyboard controls listed above.

## Roadmap

- [ ] Flat shading
- [ ] Depth (Z) buffer visualization
- [ ] Triangle filling
- [ ] Multiple models and camera movement

## License

MIT License

---

This project was created for learning purposes and reimplements key pieces of a graphics pipeline by hand.
