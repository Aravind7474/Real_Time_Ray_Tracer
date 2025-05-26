#pragma once

typedef struct{
	unsigned char *data;  // an image of bytes
	int *intData;         // an image of integers
	float *fdata;         // an image of floats
	int nx,ny,n;          // image dimensions
	int ncolorChannels;   // number of color channels in the image (1 or 3)
} Image;

typedef struct{
	unsigned char *data;  // a volume of bytes
	int nx,ny,nz,n;       // image dimensions (nz is for a volume, a "3D image")
} Volume;
