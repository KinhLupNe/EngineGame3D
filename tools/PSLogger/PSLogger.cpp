// PSLogger.cpp
// PSLogger.cpp
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0501
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

int main() {
  std::wcout << L"PSLogger: Khởi động, sẽ chờ kết nối liên tục...\n";

  while (true) {
    // 1) Tạo 1 instance của Named Pipe
    HANDLE hPipe =
        CreateNamedPipeW(L"\\\\.\\pipe\\Engine3DLogger", PIPE_ACCESS_INBOUND,
                         PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 1, 0,
                         0, NMPWAIT_USE_DEFAULT_WAIT, nullptr);
    if (hPipe == INVALID_HANDLE_VALUE) {
      std::wcerr << L"PSLogger: CreateNamedPipeW lỗi " << GetLastError()
                 << L"\n";
      return 1;
    }

    std::wcout << L"PSLogger: Đang chờ kết nối...\n";
    BOOL connected = ConnectNamedPipe(hPipe, nullptr) ||
                     GetLastError() == ERROR_PIPE_CONNECTED;
    if (!connected) {
      std::wcerr << L"PSLogger: ConnectNamedPipe lỗi " << GetLastError()
                 << L"\n";
      CloseHandle(hPipe);
      continue;
    }
    std::wcout << L"PSLogger: Đã kết nối. Nhập Ctrl-C để thoát.\n";

    // 2) Nhận và in log cho đến khi client đóng pipe
    std::vector<char> buf;
    buf.reserve(256);
    char ch;
    DWORD rd;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    while (ReadFile(hPipe, &ch, 1, &rd, nullptr) && rd) {
      if (ch != '\n') {
        buf.push_back(ch);
      } else {
        buf.push_back('\0');
        std::istringstream iss(buf.data());
        int x, y;
        if (iss >> x >> y) {
          std::string msg;
          std::getline(iss, msg);
          COORD coord{SHORT(x), SHORT(y)};
          SetConsoleCursorPosition(hOut, coord);
          DWORD written;
          WriteConsoleA(hOut, msg.c_str(), DWORD(msg.size()), &written,
                        nullptr);
        }
        buf.clear();
      }
    }

    // 3) Client đã disconnect, ta đóng pipe và vòng lặp sẽ tạo lại
    CloseHandle(hPipe);
    std::wcout << L"PSLogger: Client đóng kết nối, quay lại chờ mới...\n";
  }

  return 0;
}
