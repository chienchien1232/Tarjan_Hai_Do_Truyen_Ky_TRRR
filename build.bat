@echo off
setlocal enabledelayedexpansion

:: Kết nối với trình biên dịch
set "COMPILER_PATH=%~dp0.compiler\bin"
set "PATH=!COMPILER_PATH!;%PATH%"

echo =========================================

echo    DANGG dep trai dang build game...

echo =========================================

:: 1. Biên dịch
:: Thêm -static để tránh lỗi thiếu DLL nếu bạn dùng thư viện tĩnh
:: Hoặc đảm bảo raylib.dll nằm cùng thư mục với HaiDo.exe
g++ "Src/main.cpp" -o "HaiDo.exe" -I"Include" -I"Src" -L"Lib" -lraylib -lopengl32 -lgdi32 -lwinmm

if %errorlevel% equ 0 (
    echo [OK] Lam duoc roi!
    echo Dang khoi chay game...
    echo -----------------------------------------
    
    :: 2. Chạy trực tiếp thay vì dùng 'start' để dễ thấy lỗi Terminal nếu có
    .\HaiDo.exe
    
    :: Nếu muốn dùng start, hãy thêm /d để chỉ định thư mục làm việc
    :: start "" /d "%~dp0" "HaiDo.exe"
) else (
    echo -----------------------------------------
    echo [LOI] Co loi trong luc bien dich.
    echo -----------------------------------------
)
pause