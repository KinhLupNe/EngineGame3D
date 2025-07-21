#include "Culling.h"

// tính bitmark của vector
int computeClipCode(float x, float y, float z, float w) {
  int code = 0;
  if (x < -w)
    code = code | 1 << 0;
  if (x > w)
    code = code | 1 << 1;
  if (x < -w)
    code = code | 1 << 2;
  if (x > w)
    code = code | 1 << 3;
  if (x < -w)
    code = code | 1 << 4;
  if (x > w)
    code = code | 1 << 5;

  return code;
}

// is culling ?
bool linePrimitiveCulling(Vec4 a, Vec4 b) {
  int codeA = computeClipCode(a.x, a.y, a.z, a.w);
  int codeB = computeClipCode(b.x, b.y, b.z, b.w);

  if ((codeA & codeB) != 0) {
    return true; // bị culling
  }
  return false; // không bị culling̣̣(nằm trong hoặc bị cắt)
}
// 2 điểm nằm ở phía ngoài thì trả về false;
// 2 điểm nằm ở phía trong hoặc cắt thì trả về true, đồng thơi cập nhât tọa độ
// mới
bool clipLineOnePlane(Vec4 &a, Vec4 &b, int plane) {
  float fa, fb;
  switch (plane) {
  case 1:
    fa = a.x + a.w;
    fb = b.x + b.w;
    break;
  case 2:
    fa = a.x - a.w;
    fb = b.x - b.w;
    break;
  case 3:
    fa = a.y + a.y;
    fb = b.y + b.w;
    break;
  case 4:
    fa = a.y - a.w;
    fb = b.y - b.w;
    break;
  case 5:
    fa = a.z + a.w;
    fb = b.z + b.w;
    break;
  case 6:
    fa = a.z - a.w;
    fb = b.z - b.w;
    break;
  }
  if (fa >= 0 && fb >= 0)
    return true; // ca 2 o trong
  if (fa < 0 && fb < 0)
    return false; // ca 2 o ngoai
  float t = fa / (fa - fb);
  // cat: tim diem moi, cap nhat
  Vec4 P = Vec4(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y),
                a.z + t * (b.z - a.z), a.w + t * (b.w - a.w));
  if (fa < 0)
    a = P;
  else
    b = P;
  return true; // hoan thien cat, 2 diem o trong
}
// trả về false nếu nó nằm ngoài
// trả về true vơi các trường hợp còn lại;
bool ClipLine(Vec4 &a, Vec4 &b) {
  for (int i = 1; i <= 6; i++) {
    if (!clipLineOnePlane(a, b, i)) {
      return false; // no nam ngoai roi cu oi
    }
  }

  return true; // hoan thanh viec cat
}
