## If you wanna compile this bad boy:
`g++ src/*.cpp src/engine/*.cpp src/other/*.cpp src/scene/*.cpp -o "Differ" -I "C:\SDL3-3.4.0\x86_64-w64-mingw32\include" -I "C:\SDL3_image-3.4.0\x86_64-w64-mingw32\include" -I "C:\SDL3_ttf-3.2.2\x86_64-w64-mingw32\include" -L "C:\SDL3-3.4.0\x86_64-w64-mingw32\lib" -L "C:\SDL3_image-3.4.0\x86_64-w64-mingw32\lib" -L "C:\SDL3_ttf-3.2.2\x86_64-w64-mingw32\lib" -lSDL3 -lSDL3_image -lSDL3_ttf -mwindows`
<br>but you will need these libraries: `SDL3` `SDL3_image` `SDL3_ttf`
and they will also have to be in aspecific place (although you could just change the stuff above)
## then run with:
`.\Differ.exe`
or just open it normally if you wanna
