@echo off
chcp 65001 >nul
setlocal EnableExtensions EnableDelayedExpansion

REM Find latest Visual Studio with C++ tools (via vswhere)
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" goto NOVSWHERE

for /f "usebackq delims=" %%I in (`
  "%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
`) do set "VSINST=%%~I"

if not defined VSINST goto NOVS

set "VSDEVCMD=%VSINST%\Common7\Tools\VsDevCmd.bat"
if not exist "%VSDEVCMD%" goto NOVS

REM Load MSVC environment for x64
call "%VSDEVCMD%" -arch=x64 >nul || goto ERR

REM Project root
cd /d E:\IT\devGame3D\Engine3D || goto ERR

REM Configure (Ninja + MSVC via preset)
cmake --preset x64-debug || goto ERR

REM Build
cmake --build out\build\x64-debug -j || goto ERR

pushd out\build\x64-debug
echo.
echo Build OK. Current dir:
echo %CD%
popd
goto :EOF

:NOVSWHERE
echo [ERROR] vswhere.exe not found:
echo   %VSWHERE%
echo Install Visual Studio Installer or add vswhere to PATH.
goto :EOF

:NOVS
echo [ERROR] Visual Studio with C++ toolset not found.
goto :EOF

:ERR
echo [ERROR] Build failed. ErrorLevel=%ERRORLEVEL%
goto :EOF
