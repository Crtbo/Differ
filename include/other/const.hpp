#pragma once
#include <SDL3/SDL.h>

const int kScreenWidth = 384;
const int kScreenHeight = 216;
const int kScreenFps = 60;
const int kScale = 4;

const int kTileSize = 16;
const int kTotalTileSprites = 12;

const int kTilePlacehold = 0;
const int kTileAir = 1;
const int kTileSpecial = 2;
const int kTileUpLeft = 3;
const int kTileUpMid = 4;
const int kTileUpRight = 5;
const int kTileMidLeft = 6;
const int kTileMidMid = 7;
const int kTileMidRight = 8;
const int kTileDownleft = 9;
const int kTileDownMid = 10;
const int kTileDownRight = 11;