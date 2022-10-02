# simple-audio-player
a retro-style audio player written in **C** and **SDL**

### Features
  - supports mp3, wav, ogg
  - drag and drop support
  - support multimedia keys
  - default location (bin/music/)

## Building for Windows
you need to install [vcpkg](https://vcpkg.io/en/getting-started.html) to get the following dependencies
```shell
.\vcpkg install sdl2:x64-windows sdl2-image:x64-windows sdl2-mixer:x64-windows sdl2-ttf:x64-windows
```
to compile the project, you need to install 
  - [CMake](https://cmake.org/download/) and 
  - [Visual Studio 2022](https://visualstudio.microsoft.com/) (MinGW not supported)

clone the repository and enter the cloned repository
```shell
git clone https://github.com/ThirulogeswarenVenkatraman/simple-audio-player.git
cd simple-audio-player
```
create a directory named ``build`` inside the base folder containing CMakeLists.txt
```shell
mkdir build
cd build 
```
from newly created ``build`` directory, run the following to generate VS build files
```shell
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
``` 
then run the following to build the project
```shell
cmake --build . --config Release
```
the executable will be placed in `bin\Release\simple-audio-player.exe`  
make sure to place the `assets\` folder and required DLLs inside the folder containing .exe
## Linux Dependencies

#### On Debian/Ubuntu
```shell
sudo apt install gcc libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```
you need the latest version of [sdl-mixer](https://github.com/libsdl-org/SDL_mixer)

```shell
git clone https://github.com/libsdl-org/SDL_mixer
cd SDL_mixer
./configure
make
sudo make install
```
then add the following line to ``.bashrc`` located in your home folder ``/home/username``
```shell
export LD_LIBRARY_PATH=/usr/local/lib/
```
#### On Arch
```shell
sudo pacman -S gcc make sdl2 sdl2_image sdl2_mixer sdl2_ttf
```
## Building for Linux
after installing dependencies, clone the repository
```shell
git clone https://github.com/ThirulogeswarenVenkatraman/simple-audio-player.git
cd simple-audio-player
```
from the cloned repository, run `ccmp.bash` to build the project

## Building for MacOS
you need to install [homebrew](https://brew.sh) to get the following dependencies
```shell
brew install make cmake sdl2 sdl2_image sdl2_mixer sdl2_ttf
```
then clone the repository and enter the cloned repository 
```shell
git clone https://github.com/ThirulogeswarenVenkatraman/simple-audio-player.git
cd simple-audio-player
```
create a directory named ``build`` inside the base folder containing CMakeLists.txt
```shell
mkdir build
cd build
```
from newly created ``build`` directory, run: ``cmake ..`` to generate build files  
then run the following to build the project
```shell
cmake --build .
```
