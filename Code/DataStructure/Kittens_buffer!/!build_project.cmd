SET build_path=C:\cmake-build\Kittens\Kittens_buffer
SET project_path=%~dp0

mkdir %build_path%

cmake.exe -G"Visual Studio 15 2017" -A"x64" -T"host=x64" -B"%build_path%" -H"%project_path%"
cmake.exe --build %build_path% --config Release