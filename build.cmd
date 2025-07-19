@echo off

cd E:\IT\devGame3D\Engine3D


cmake --preset x64-debug
if errorlevel 1 exit /b 1


cmake --build out\build\x64-debug
if errorlevel 1 exit /b 1


cd E:\IT\devGame3D\Engine3D\out\build\x64-debug

echo.
echo Đã build xong và đang ở:
echo %CD%
pause
