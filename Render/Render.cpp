
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
                                               Model *model) const {
  vector<VertexOutput> clipVer;
  // tọa độ clip (sau chiếu phối cảnh, trước chia phối cảnh NDC)
  for (int i = 0; i < vbo.getSize(); i++) {
    VertexOutput verRes = p.vertexShader(vbo[i], model->getWorldMatrix(),
                                         scene.get_camera()->getViewMatrix(),
                                         scene.get_camera()->getProjectionMatrix());
    clipVer.push_back(verRes);
  }
  // sắp xếp các điểm tahfn htam giác
  return p.assemble(clipVer, ibo.getData());
}

/**
 * @param triOut tam giác sau phép chiếu phối cảnh
 * @return tọa độ các điểm trong tam giác trong không gian màn hình đã qua nôi suy thuộc tính
 * @return posision point of the triangle in screen space after rasterization
 */
vector<VertexOutput> Render::VPbuffer(const TriangleOutput &triOut) const {
  Triangle tri = Triangle{
    Vec4(triOut.v0.posClip.x, triOut.v0.posClip.y,
         triOut.v0.posClip.z, triOut.v0.posClip.w),
    Vec4(triOut.v1.posClip.x, triOut.v1.posClip.y,
         triOut.v1.posClip.z, triOut.v1.posClip.w),
    Vec4(triOut.v2.posClip.x, triOut.v2.posClip.y,
         triOut.v2.posClip.z, triOut.v2.posClip.w)
  };
  Vec3 res0 = p.toScreen(width, height, tri.v0);

  Vec3 res1 = p.toScreen(width, height, tri.v1);

  Vec3 res2 = p.toScreen(width, height, tri.v2);
  VertexOutput v0 = triOut.v0;
  VertexOutput v1 = triOut.v1;
  VertexOutput v2 = triOut.v2;

  //tọa độ các điểm trong không gian màn hình
  // get position scrren
  v0.posScreen = Vec3(res0.x, res0.y, res0.z);
  v1.posScreen = Vec3(res1.x, res1.y, res1.z);
  v2.posScreen = Vec3(res2.x, res2.y, res2.z);
  return p.rasterization(v0, v1, v2, tri);
}

// render
void Render::present() {
  const int l = scene.get_models().size();
  frameBuffer.clear();
  for (int i = 0; i < l; i++) {
    // vertex in clip space(after projection), assemble vertex to triangle
    vector<TriangleOutput> tris =
        getTriangleClip(vbos[i], ibos[i], scene.get_models()[i]);
    for (auto &tri: tris) {
      // check back face
      if (p.backFaceCull(tri) == true) {
        // primitive clipping Triangles
        vector<TriangleOutput> temps = p.primitiveClipping(tri);
        for (auto &temp: temps) {
          // rasterization
          vector<VertexOutput> vps = VPbuffer(temp);
          // fragment shader
          for (auto &v: vps) {
            // lỗi đâu đó trong thuật toán cắt tam giác, dùng tạm hạ sách vậy
            if (v.posScreen.y >= height || v.posScreen.x >= width)
              continue;
            // zbuffer
            if (frameBuffer.getZBuffer()[v.posScreen.y][v.posScreen.x] > v.posScreen.z) {
              // lighting
              //  ánh sáng (ambient + diffuse)
              FragmentPayLoad fragmentPayLoad(v.normal, v.posScreen.z, v.posWorld, v.color);
              FragmentShader fragmentShader;
              fragmentShader.getFragmentPayLoad() = fragmentPayLoad;
              frameBuffer.set(v.posScreen.x, v.posScreen.y, v.posScreen.z, fragmentShader.shade());
            }
          }
        }
      }
    }
  }
  cameraInfo();
  // system("pause");
  frameBuffer.display();
}

// degbug log
// thông tin camera trên terminal thứ 2
void Render::cameraInfo() const {
  auto &log = DebugLogger::Instance();
  log.LogAt(1, 1, "CAMERA POS");
  log.LogAt(1, 2,
            "X: " + std::to_string(scene.get_camera()->pos.x) +
            " Y: " + std::to_string(scene.get_camera()->pos.y) +
            " Z: " + std::to_string(scene.get_camera()->pos.z));
  log.LogAt(1, 3, "YAW: " + std::to_string(scene.get_camera()->yaw));
  log.LogAt(1, 4, "PITCH: " + std::to_string(scene.get_camera()->pitch));
  log.LogAt(1, 5,
            "FORWARD: " + std::to_string(scene.get_camera()->getForward().x) + " " +
            std::to_string(scene.get_camera()->getForward().y) + " " +
            std::to_string(scene.get_camera()->getForward().z));
}



