@echo off
cd ..
git submodule update --init --recursive
cd libs/glfw
git checkout 3.4
echo GLFW Set to 3.4 Release
pause
