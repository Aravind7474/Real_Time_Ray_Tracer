#ifndef __IMAGEIO_H
#define __IMAGEIO_H

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char pixelvalue;	// an image of float

// functions of imageio.cpp
void ReadPPM(const char *fn, int &X, int &Y, pixelvalue * &inimage,int &numchannel);
void ReadImage(const char *fn, int &X, int &Y, pixelvalue * &inimage, int &numchannel);
void FlipImage(int nx, int ny, unsigned char *img);
void WritePPM(int X, int Y, char *out_fn, pixelvalue *outimage);
void WritePGM(int X, int Y, char *out_fn, pixelvalue *outimage);

#endif
