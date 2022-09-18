# simple-audio-player
a lightweight audio player written in **C** and **SDL2**

### Features
  - supports mp3, wav, ogg
  - drag and drop support
  - support multimedia keys

## Building for Windows

To compile simple-audio-player
  - install [CMake](https://cmake.org/download/)
  - install [Visual Studio 2022](https://visualstudio.microsoft.com/) (MinGW not supported)

clone the repository and enter the cloned repository
```shell
git clone https://github.com/ThirulogeswarenVenkatraman/simple-audio-player.git
cd simple-audio-player
```
create a directory named ``build`` inside the source folder containing CMakeLists.txt
```shell
mkdir build
cd build 
```
from newly created ``build`` directory, run: ``cmake ..`` to generate platform specific build files

then run the following to build the project
```shell
cmake --build . --config Release
```

