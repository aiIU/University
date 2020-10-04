SET build_path=c:\cmake-build\lab2_qt
SET project_path=%~dp0

mkdir %build_path%                   

"cmake.exe" -G"Visual Studio 15 2017" -A"x64" -B"%build_path%" -H"%project_path%"

cd /d %build_path%

cmake-gui %~dp0