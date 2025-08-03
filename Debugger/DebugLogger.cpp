
// DebugLogger.cpp
#include "DebugLogger.h"

#include <cwchar> // std::wcscpy
#include <sstream>

// Initialize static member
HANDLE DebugLogger::hPipe = INVALID_HANDLE_VALUE;

DebugLogger &DebugLogger::Instance() {
  static DebugLogger inst;
  return inst;
}

DebugLogger::DebugLogger() {
  // 1) Spawn PSLogger.exe từ thư mục build
  wchar_t exePath[MAX_PATH];
  GetModuleFileNameW(nullptr, exePath, MAX_PATH);
  std::wstring path(exePath);
  // Loại bỏ tên file (Engine3D.exe)
  auto pos = path.find_last_of(L"\\/");
  if (pos != std::wstring::npos)
    path = path.substr(0, pos);
  // Loại tiếp thư mục x64-debug → còn ...\out\build
  pos = path.find_last_of(L"\\/");
  if (pos != std::wstring::npos)
    path = path.substr(0, pos);
  // Ghép thêm đường dẫn tới PSLogger.exe
  std::wstring psPath = path + L"\\out\\bin\\PSLogger.exe";

  // Copy vào buffer mutable
  wchar_t cmdLine[MAX_PATH];
  std::wcscpy(cmdLine, psPath.c_str());

  STARTUPINFOW si{sizeof(si)};
  PROCESS_INFORMATION pi{};
  if (CreateProcessW(nullptr, // lpApplicationName
                     cmdLine, // lpCommandLine
                     nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr,
                     nullptr, &si, &pi)) {
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
  }
  // Chờ PSLogger khởi xong pipe
  Sleep(200);
}

DebugLogger::~DebugLogger() {
  if (hPipe != INVALID_HANDLE_VALUE)
    CloseHandle(hPipe);
}

void DebugLogger::EnsurePipe() {
  if (hPipe == INVALID_HANDLE_VALUE) {
    hPipe = CreateFileW(L"\\\\.\\pipe\\Engine3DLogger", GENERIC_WRITE, 0,
                        nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
  }
}

void DebugLogger::LogAt(int x, int y, const std::string &msg) {
  EnsurePipe();
  if (hPipe == INVALID_HANDLE_VALUE)
    return;
  std::ostringstream oss;
  oss << x << ' ' << y << ' ' << msg << '\n';
  std::string s = oss.str();
  DWORD written;
  WriteFile(hPipe, s.data(), (DWORD)s.size(), &written, nullptr);
}
