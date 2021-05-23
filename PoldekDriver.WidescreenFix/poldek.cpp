#include "pch.h"
#include "poldek.h"

screen_data TheScreen;

// rpm - 64x32
// kmh - 128x32
// speedo - 256x256

void __stdcall Draw2D(int ptr, texture_data* tex, int fontID, Vector2D * scale, int special, float rotation, Vector2D * pos, unsigned int color)
{
	if (tex)
	{

		if (TheScreen.aspectRatio > (4.0f / 3.0f))
		{
			if (TheScreen.aspectRatio >= (16.0f / 9.0f))
			{
				if ((tex->x == 256 && tex->y == 256))
				{
					pos->x += ((float)TheScreen.x - pos->x) / 6.0f;
				}
				if ((tex->x == 64 && tex->y == 32))
				{
					pos->x -= (((float)TheScreen.x - pos->x) / 4.0f) / 2.83f;
				}
				if ((tex->x == 128 && tex->y == 32))
				{
					pos->x += (((float)TheScreen.x - pos->x) / 6.0f) / 1.17f;
				}
			}

		}

	}

	((void(__stdcall*)(int, texture_data*, int, Vector2D*, int, float, Vector2D*, unsigned int))0x4418E5)(ptr,tex, fontID, scale, special, rotation, pos, color);

}
