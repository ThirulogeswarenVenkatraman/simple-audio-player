# simple-audio-player
a retro-style audio player written in **C** and **SDL**

### Features
  - supports mp3, wav, ogg
  - drag and drop support
  - support multimedia keys
  - default location (bin/music/)

## Building for Windows

To compile simple-audio-player
  - install [CMake](https://cmake.org/download/)
  - install [Visual Studio 2022](https://visualstudio.microsoft.com/) (MinGW not supported)

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
from newly created ``build`` directory, run: ``cmake ..`` to generate platform specific build files

then run the following to build the project
```shell
cmake --build . --config Release
```
the executable will be placed in `bin\Release\simple-audio-player.exe`  
make sure to place the `assets\` folder and required DLLs inside the folder containing .exe
## Linux Dependencies

#### On Debian/Ubuntu
```shell
sudo apt install gcc make libsdl2-2.0-0 libsdl2-image-2.0-0 libsdl2-ttf-2.0-0 
```
you need the latest version of [sdl-mixer](https://github.com/libsdl-org/SDL_mixer)

```shell
git clone https://github.com/libsdl-org/SDL_mixer
cd SDL_mixer
./configure
make
sudo make install
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
