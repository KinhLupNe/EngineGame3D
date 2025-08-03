#ifndef DEBUG_LOGGER_H
#define DEBUG_LOGGER_H
#ifndef WINVER
#define WINVER 0x0501
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

// Rút gọn Windows headers, nhưng vẫn include console API
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN

#include <string>

class DebugLogger {
public:
  // Lấy instance duy nhất (và spawn PSLogger lần đầu)
  static DebugLogger &Instance();

  // Gửi log tới PSLogger để in đè tại (x, y)
  void LogAt(int x, int y, const std::string &msg);

private:
  DebugLogger();
  ~DebugLogger();

  DebugLogger(const DebugLogger &) = delete;
  DebugLogger &operator=(const DebugLogger &) = delete;

  // Kết nối Named Pipe nếu chưa có
  void EnsurePipe();

  // HANDLE của Named Pipe client
  static HANDLE hPipe;
};

#endif
