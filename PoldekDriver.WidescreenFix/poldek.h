#pragma once

struct Vector2D {
	float x, y;
};


struct screen_data {
	int  x;
	int  y;
	float aspectRatio;
};


struct texture_data {
	char unk[32];
	// these are allocated, not actual
	int  x;
	int  y;
};


extern screen_data TheScreen;


void __stdcall Draw2D(int ptr, texture_data* tex, int fontID, Vector2D* scale, int special, float rotation, Vector2D* pos, unsigned int color);