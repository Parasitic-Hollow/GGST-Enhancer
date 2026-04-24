# GGST-Enhancer
GGST ENHANCER

This is a fork intended to make the mod work on Linux.

Color Unlocker (only others with the tool will see it!)

Improved Fishing (no duplicates and secret items)

No censorship in the Museum!

Reward Unlocker (Auras)

Custom R-Code Avatar

Linux:

1. Download x64 `winmm.dll` from [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases).

2. Build this project or download a [built copy of the mod](https://github.com/Parasitic-Hollow/GGST-Enhancer/releases).

3. If you built the project yourself, rename `build/UMPDC.dll` to `GGSTEnhancer.asi`.

4. Put `winmm.dll` next to `GGST-Win64-Shipping.exe` in `RED/Binaries/Win64`.

5. Put the mod in that same `Win64` folder as `GGSTEnhancer.asi`.

6. In Steam launch options, use:

```bash
WINEDLLOVERRIDES="winmm=n,b" %command%
```

7. Launch the game.

8. `GGSTEnhancer.ini` is created the first time you launch the game. Put `Avatar.png` and `Thumbnail.jpg` in that same `Win64` folder if you want to use them.

Building on Linux:

1. Install a MinGW-w64 toolchain and CMake

2. Configure with a Windows target, for example:

```bash
cmake -S . -B build \
  -DCMAKE_SYSTEM_NAME=Windows \
  -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++
```

3. Build:

```bash
cmake --build build
```

4. The build output is `build/UMPDC.dll`

Optional:

Edit GGSTEnhancer.ini for custom settings (it is created when opening the game for the first time)

Place an image called "Avatar.png" in the same folder, maximum file size is 262400 bytes, the alpha channel must be inverted for it to be visible ingame

Place a jpg called "Thumbnail.jpg" in the same folder, maximum file size is 290816 bytes.
