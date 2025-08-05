#include "Render.h"
#include "../Debugger/DebugLogger.h"
#include "../Math/Math.h"
#include "../Pipeline/FragmentShader.h"
//  get Triangle in clip space (model ->view->project ->triangle)
#ifdef byte
#undef byte
#endif
vector<TriangleOutput> Render::getTriangleClip(const VertexBuffer &vbo,
                                               const IndexBuffer &ibo,
                                               Model *model) {
  vector<TriangleOutput> res;
  vector<VertexOutput> clipVer;
  for (int i = 0; i < vbo.getSize(); i++) {
    VertexOutput res;

    res = p.vertexShader(vbo[i], model->getWorldMatrix(),
                         scene.camera->getViewMatrix(),
                         scene.camera->getProjectionMatrix());
    clipVer.push_back(res);
  }
  res = p.assemble(clipVer, ibo.data);
  return res;
}
// rassterization(tri(after backFaceCull, primitiveClipping) )
vector<VertexOutput> Render::VPbuffer(const TriangleOutput &triOut) {
  Triangle tri = Triangle{Vec4(triOut.v0.posClip.x, triOut.v0.posClip.y,
                               triOut.v0.posClip.z, triOut.v0.posClip.w),
                          Vec4(triOut.v1.posClip.x, triOut.v1.posClip.y,
                               triOut.v1.posClip.z, triOut.v1.posClip.w),
                          Vec4(triOut.v2.posClip.x, triOut.v2.posClip.y,
                               triOut.v2.posClip.z, triOut.v2.posClip.w)};
  Vec3 res0 = p.toScreen(width, height, tri.v0);

  Vec3 res1 = p.toScreen(width, height, tri.v1);

  Vec3 res2 = p.toScreen(width, height, tri.v2);
  VertexOutput v0 = triOut.v0;
  VertexOutput v1 = triOut.v1;
  VertexOutput v2 = triOut.v2;
  v0.posScreen = Vec3(res0.x, res0.y, res0.z);
  v1.posScreen = Vec3(res1.x, res1.y, res1.z);
  v2.posScreen = Vec3(res2.x, res2.y, res2.z);

  // cout << v0.normal.x << " " << v0.normal.y << " " << v0.normal.z << endl;
  // cout << v1.normal.x << " " << v1.normal.y << " " << v1.normal.z << endl;
  // cout << v2.normal.x << " " << v2.normal.y << " " << v2.normal.z << endl;

  return p.rasterization(v0, v1, v2, tri);
}

void Render::present() {
  int l = scene.models.size();
  frameBuffer.clear();
  for (int i = 0; i < l; i++) {
    // vertex in clip space(after projection), assemble vertex to triangle
    vector<TriangleOutput> tris =
        getTriangleClip(vbos[i], ibos[i], scene.models[i]);
    // cout << vbos[i][5].normalize.x << " " << vbos[i][5].normalize.y << " "
    //    << vbos[i][5].normalize.z << endl;
    //
    for (auto &tri : tris) {
      // check back face
      // cout << tri.v0.normal.x << " " << tri.v0.normal.y << " "
      //   << tri.v0.normal.z << endl;
      if (p.backFaceCull(tri) == true) {
        // primitive clipping Triangles
        vector<TriangleOutput> temps = p.primitiveClipping(tri);
        for (auto &temp : temps) {
          // cout << temp.v0.normal.x << " " << temp.v0.normal.y << " "
          //    << temp.v0.normal.z << endl;
          // cout << temp.v1.normal.x << " " << temp.v1.normal.y << " "
          //    << temp.v1.normal.z << endl;
          // cout << temp.v2.normal.x << " " << temp.v2.normal.y << " "
          //     << temp.v2.normal.z << endl;

          // rasterization
          vector<VertexOutput> vps = VPbuffer(temp);
          // fragment shader
          //
          for (auto &v : vps) {
            // lỗi đâu đó trong thuật toán cắt tam giác, dùng tạm hạ sách vậy
            if (v.posScreen.y >= height || v.posScreen.x >= width)
              continue;
            if (frameBuffer.getZBuffer()[v.posScreen.y][v.posScreen.x] >
                v.posScreen.z) {
              FragmentPayLoad fragmentPayLoad(v.normal, v.posScreen.z,
                                              v.posView, v.color);
              // cout << v.normal.x << " " << v.normal.y << " " << v.normal.z
              // << endl;
              FragmentShader fragmentShader;
              fragmentShader.fragmentPayLoad = fragmentPayLoad;
              char shade = fragmentShader.shade();

              frameBuffer.set(v.posScreen.x, v.posScreen.y, v.posScreen.z,
                              shade);
            }
          }
        }
      }
    }
  }
  cameraInfo();
  frameBuffer.display();
}

void Render::cameraInfo() {
  auto &log = DebugLogger::Instance();
  log.LogAt(1, 1, "CAMERA POS");
  log.LogAt(1, 2,
            "X: " + std::to_string(scene.camera->pos.x) +
                " Y: " + std::to_string(scene.camera->pos.y) +
                " Z: " + std::to_string(scene.camera->pos.z));
  log.LogAt(1, 3, "YAW: " + std::to_string(scene.camera->yaw));
  log.LogAt(1, 4, "PITCH: " + std::to_string(scene.camera->pitch));
  log.LogAt(1, 5,
            "FORWARD: " + std::to_string(scene.camera->getForward().x) + " " +
                std::to_string(scene.camera->getForward().y) + " " +
                std::to_string(scene.camera->getForward().z));
}

// API
void Render::drawBlock(Vec3 pos, Mesh *mesh) {
  this->scene.drawBlock(pos, mesh);
}
