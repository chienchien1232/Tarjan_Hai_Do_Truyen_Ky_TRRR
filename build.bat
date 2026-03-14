@echo off
setlocal enabledelayedexpansion

:: Kết nối với trình biên dịch
set "COMPILER_PATH=%~dp0.compiler\bin"
set "PATH=!COMPILER_PATH!;%PATH%"

echo =========================================
echo   DANG BIEN DICH: TARJAN HAI DO TRUYEN KY
echo =========================================

:: Sử dụng dấu ngoặc kép bao quanh đường dẫn để tránh lỗi dấu ngoặc đơn ()
g++ "Src/main.cpp" -o "HaiDo.exe" -I"Include" -I"Src" -L"Lib" -lraylib -lopengl32 -lgdi32 -lwinmm

if %errorlevel% equ 0 (
    echo [OK] Bien dich thanh cong!
    echo Dang khoi chay game...
    echo -----------------------------------------
    start "" "HaiDo.exe"
) else (
    echo -----------------------------------------
    echo [LOI] Co loi trong qua trinh build.
    echo -----------------------------------------
    pause
)