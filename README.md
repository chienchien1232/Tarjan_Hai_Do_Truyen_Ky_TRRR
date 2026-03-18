HƯỚNG DẪN CODE NHÓM - HẢI ĐỒ TRUYỀN KỲ ⚓
1. Lấy code về máy (Chỉ làm lần đầu):
Mở Terminal tại thư mục muốn lưu và gõ:
git clone https://github.com/chienchien1232/Tarjan_Hai_Do_Truyen_Ky_TRRR.git

2. Quy trình code mỗi ngày (BẮT BUỘC):

Trước khi code: Gõ git pull để cập nhật code mới nhất của cả nhóm.

Trong khi code: Tạo file riêng trong thư mục Src để làm (Ví dụ: ThuatToan_An.cpp, Map_Binh.cpp), hạn chế sửa chung một file để tránh lỗi.

Code xong: Gõ bộ 3 lệnh để đẩy code lên:

git add .

git commit -m "Tên: Việc đã làm (Vd: Xong thuật toán)"

git push

3. Cách chạy thử game:
Mở Terminal trong VS Code và gõ: .\build.bat

⚠️ Lưu ý: Không tự ý xóa file của người khác và không sửa file build.bat.
Để chạy được dự án, máy các bạn cần cài đặt bộ công cụ sau:
C++ Compiler (MinGW-w64):
Phải cài đặt MinGW (thường qua MSYS2) và quan trọng nhất là phải Add Path vào biến môi trường (Environment Variables) của Windows.
Cách kiểm tra: Gõ g++ --version vào Terminal. Nếu hiện ra phiên bản là OK.
Visual Studio Code Extensions:
Cài Extension C/C++ (của Microsoft) để được gợi ý code.
Thư viện đồ họa (Đã đính kèm):
Dự án đã có sẵn folder Lib và Include. Mọi người không được xóa các file .dll trong thư mục gốc. Nếu thiếu những file này, game sẽ báo lỗi "vcredist" hoặc "missing .dll".
Terinal:git add README.md
Nên dùng PowerShell hoặc Command Prompt tích hợp sẵn trong VS Code để chạy lệnh .\build.bat