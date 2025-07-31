#include "Render.h"
//  get Triangle in clip space (model ->view->project ->triangle)
vector<Triangle> Render::getTriangleClip(const VertexBuffer &vbo,
                                         const IndexBuffer &ibo, Model *model) {
  vector<Triangle> res;
  vector<Vec4> clipVer;
  for (int i = 0; i < vbo.getSize(); i++) {
    Vec4 a = Vec4(vbo[i].positon.x, vbo[i].positon.y, vbo[i].positon.z, 1);
    Vec4 b = p.vertexShader(a, model->getWorldMatrix(),
                            scene.camera->getViewMatrix(),
                            scene.camera->getProjectionMatrix());
    clipVer.push_back(b);
  }
  res = p.assemble(clipVer, ibo.data);
  return res;
}
// rassterization(tri(after backFaceCull, primitiveClipping) )
vector<Vec3> Render::VPbuffer(const Triangle &tri) {
  Vec3 res0 = p.toScreen(width, height, tri.v0);

  Vec3 res1 = p.toScreen(width, height, tri.v1);

  Vec3 res2 = p.toScreen(width, height, tri.v2);
  return p.rasterization(res0, res1, res2, tri);
}

void Render::present() {
  int l = scene.models.size();
  frameBuffer.clear();
  for (int i = 0; i < l; i++) {
    // vertex in clip space(after projection), assemble vertex to triangle
    vector<Triangle> tris = getTriangleClip(vbos[i], ibos[i], scene.models[i]);
    //
    for (auto &tri : tris) {
      // check back face
      if (p.backFaceCull(tri) == true) {
        // primitive clipping Triangles
        vector<Triangle> temps = p.primitiveClipping(tri);
        for (auto &temp : temps) {
          // rasterization
          vector<Vec3> vps = VPbuffer(temp);
          for (auto &v : vps) {
            if (frameBuffer.getZBuffer()[v.y][v.x] > v.z) {
              frameBuffer.set(v.x, v.y, v.z,
                              FrameBuffer::tBufferFromZBuffer(v.z));
            }
          }
        }
      }
    }
  }
}

;
