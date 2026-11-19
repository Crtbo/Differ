# Differ
## What is this?
A platformer game made with C++ and SDL3

## How to play?
### Menu
- Moving: `UP`/`W` and `DOWN`/`S` keys
- Confirm: `RETURN`/`Y`/`Z` key
- Go back: `BACKSPACE`/`X` key

### Gameplay
- Moving: `A`/`LEFT` and `D`/`RIGHT` keys
- Jumping: `SPACE` bar
- Running: `LEFT SHIFT` key
- You can slide on and jump off a wall

### Level editing
- Moving: `W`/`UP`, `A`/`LEFT`, `S`/`DOWN` and `D`/`RIGHT` keys
- Placing tiles: `LEFT` mouse click
- Changing tiles: `SCROLL` mouse wheel

## How to open game?
Since the game is already compiled, all you need to do is click on the .exe file. You can also type `.\Differ.exe` in the terminal if you are in the root of the project

## How to compile?
use the following g++ line:

`g++ src/*.cpp src/engine/*.cpp src/other/*.cpp src/scene/*.cpp -o "Differ" -I "C:\SDL3-3.4.0\x86_64-w64-mingw32\include" -I "C:\SDL3_image-3.4.0\x86_64-w64-mingw32\include" -I "C:\SDL3_ttf-3.2.2\x86_64-w64-mingw32\include" -L "C:\SDL3-3.4.0\x86_64-w64-mingw32\lib" -L "C:\SDL3_image-3.4.0\x86_64-w64-mingw32\lib" -L "C:\SDL3_ttf-3.2.2\x86_64-w64-mingw32\lib" -lSDL3 -lSDL3_image -lSDL3_ttf -mwindows`

but you will need these libraries: `SDL3` `SDL3_image` `SDL3_ttf`
and they will also have to be in aspecific place (although you could just change the stuff above)
