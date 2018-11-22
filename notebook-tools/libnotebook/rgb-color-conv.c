/* 3 functions to convert between RGB colors and the corresponding xterm-256 values
 * Wolfgang Frisch, xororand@frexx.de */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// whole colortable, filled by maketable()
static int initialized=0;
static unsigned char colortable[254][3];

// the 6 value iterations in the xterm color cube
static const unsigned char valuerange[] = { 0x00, 0x5F, 0x87, 0xAF, 0xD7, 0xFF };

// 16 basic colors
static const unsigned char basic16[16][3] =
{
	{ 0x00, 0x00, 0x00 }, // 0
	{ 0xCD, 0x00, 0x00 }, // 1
	{ 0x00, 0xCD, 0x00 }, // 2
	{ 0xCD, 0xCD, 0x00 }, // 3
	{ 0x00, 0x00, 0xEE }, // 4
	{ 0xCD, 0x00, 0xCD }, // 5
	{ 0x00, 0xCD, 0xCD }, // 6
	{ 0xE5, 0xE5, 0xE5 }, // 7
	{ 0x7F, 0x7F, 0x7F }, // 8
	{ 0xFF, 0x00, 0x00 }, // 9
	{ 0x00, 0xFF, 0x00 }, // 10
	{ 0xFF, 0xFF, 0x00 }, // 11
	{ 0x5C, 0x5C, 0xFF }, // 12
	{ 0xFF, 0x00, 0xFF }, // 13
	{ 0x00, 0xFF, 0xFF }, // 14
	{ 0xFF, 0xFF, 0xFF }  // 15
};

// read a hex-rgb-color like "CCAABB"
// output are 3 unsigned chars
// returns 0 on failure and 1 on success
int readcolor(const char* rgb_string, unsigned char* output)
{
	char Xr[3], Xg[3], Xb[3];

	// string -> bytes
	if(strlen(rgb_string)!=6) return 0;
	strncpy(Xr,rgb_string+0,2);
	strncpy(Xg,rgb_string+2,2);
	strncpy(Xb,rgb_string+4,2);
	output[0] = (unsigned char) strtoll(Xr, NULL, 16);
	output[1] = (unsigned char) strtoll(Xg, NULL, 16);
	output[2] = (unsigned char) strtoll(Xb, NULL, 16);

	return 1;
}

// convert an xterm color value (0-253) to 3 unsigned chars rgb
void xterm2rgb(unsigned char color, unsigned char* rgb)
{
	// 16 basic colors
	if(color<16)
	{
		rgb[0] = basic16[color][0];
		rgb[1] = basic16[color][1];
		rgb[2] = basic16[color][2];
	}

	// color cube color
	if(color>=16 && color<=232)
	{
		color-=16;
		rgb[0] = valuerange[(color/36)%6];
		rgb[1] = valuerange[(color/6)%6];
		rgb[2] = valuerange[color%6];
	}

	// gray tone
	if(color>=233 && color<=253)
	{
		rgb[0]=rgb[1]=rgb[2] = 8+(color-232)*0x0a;
	}
}

// fill the colortable for use with rgb2xterm
void maketable()
{
	unsigned char c, rgb[3];
	for(c=0;c<=253;c++)
	{
		xterm2rgb(c,rgb);
		colortable[c][0] = rgb[0];
		colortable[c][1] = rgb[1];
		colortable[c][2] = rgb[2];
	}
}

// selects the nearest xterm color for a 3xBYTE rgb value
unsigned char rgb2xterm(unsigned char* rgb)
{
	unsigned char c, best_match=0;
	double d, smallest_distance;

	if(!initialized)
		maketable();

	smallest_distance = 10000000000.0;

	for(c=0;c<=253;c++)
	{
		d = pow(colortable[c][0]-rgb[0],2.0) +
			pow(colortable[c][1]-rgb[1],2.0) +
			pow(colortable[c][2]-rgb[2],2.0);
		if(d<smallest_distance)
		{
			smallest_distance = d;
			best_match=c;
		}
	}

	return best_match;
}
