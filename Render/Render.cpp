#include "Render.h"
//  get Triangle in clip space (model ->view->project ->triangle)
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

  return p.rasterization(v0, v1, v2, tri);
}

void Render::present() {
  int l = scene.models.size();
  frameBuffer.clear();
  for (int i = 0; i < l; i++) {
    // vertex in clip space(after projection), assemble vertex to triangle
    vector<TriangleOutput> tris =
        getTriangleClip(vbos[i], ibos[i], scene.models[i]);
    //
    for (auto &tri : tris) {
      // check back face
      if (p.backFaceCull(tri) == true) {
        // primitive clipping Triangles
        vector<TriangleOutput> temps = p.primitiveClipping(tri);
        for (auto &temp : temps) {
          // rasterization
          vector<VertexOutput> vps = VPbuffer(temp);
          // fragment shader
          //
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
  frameBuffer.display();
}

;
