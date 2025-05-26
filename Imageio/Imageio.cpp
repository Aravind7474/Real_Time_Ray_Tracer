#include <string.h>
#include "imageio.h"

/* Reads in a binary .ppm file. Allocates an array of necessary size
   for the image. Returns image size in X and Y
*/
void ReadPPM(const char *fn, int &X, int &Y, pixelvalue * &inimage, int &numchannel)
{
	int tmpint;
	char str[100];
	FILE *in_file = fopen(fn,"rb");

	if(in_file == NULL){
		printf("Can't open input file %s. Exiting.\n",fn);
		exit(1);
	}
	fscanf(in_file,"P%d\n", &tmpint);
	if(tmpint != 6){
		printf("Input file is not ppm. Exiting.\n");
		exit(1);
	}

	// skip comments embedded in header
	fgets(str,100,in_file);  
	while(str[0]=='#')
		fgets(str,100,in_file);

	// read image dimensions 
	sscanf(str,"%d %d",&X,&Y);
	fgets(str,100,in_file);  
	sscanf(str,"%d",&tmpint);

	if(tmpint != 255) printf("Warning: maxvalue is not 255 in ppm file\n");
	numchannel = 3;
	inimage = new unsigned char [numchannel*X*Y];
	if(inimage == NULL){
		printf("Can't allocate image of size %dx%d. Exiting\n",X,Y);
		exit(1);
	}else{
		printf("Reading image %s of size %dx%d\n",fn,X,Y);
	}
 
	fread(inimage,sizeof(unsigned char),numchannel*X*Y,in_file);
	FlipImage(X, Y, inimage);

	fclose(in_file);
}

void ReadImage(const char *fn, int &X, int &Y, pixelvalue * &inimage,int &numchannel)
{
	if(strstr(fn,".ppm"))
		ReadPPM(fn,X,Y,inimage,numchannel);
	

}


// flips an image upside down
void FlipImage(int nx, int ny, unsigned char *img)
{
    int i,j,k,rowOffsetSrc,rowOffsetDest,columnOffset;
    unsigned char ctmp;

	for(i=0;i<ny/2;i++)
	{
	   rowOffsetSrc=i*nx*3;
	   rowOffsetDest=(ny-1-i)*nx*3;
       for(j=0;j<nx;j++)
	   {
		   columnOffset=j*3;
		   for(k=0;k<3;k++)
		   {
			   ctmp=img[rowOffsetSrc+columnOffset+k];
               img[rowOffsetSrc+columnOffset+k]=img[rowOffsetDest+columnOffset+k];
               img[rowOffsetDest+columnOffset+k]=ctmp;
		   }
	   }
	}
}

/* Writes output image of size XxY to a raw ppm file with name out_fn.
   Assumes row-major order for result. result is 3*X*Y array of
   pixel values to be written out. It  calls function
   convert_pixel on each value befor writing it to a file.
*/
void WritePPM(int X, int Y, char *out_fn, pixelvalue *outimage)
{
	FILE *out_file;
	int i;

	printf("Write Out Image %s: %d*%d\n",out_fn,X,Y);

	out_file = fopen(out_fn,"wb");
	if(out_file == NULL){
		printf("Can't open output file. Exiting.\n");
		exit(1);
	}
 
	// write image dimensions 
	fprintf(out_file,"P6\n%d %d\n255\n",X,Y);

	// since we flipped the image upside-down when we read it
 	// we have to write it upside-down so it's stored the right way
    for(i=Y-1;i>=0;i--)
  	  fwrite(&outimage[i*X*3],sizeof(unsigned char),X*3,out_file);

	fclose(out_file);
}


void WritePGM(int X, int Y, char *out_fn, pixelvalue *outimage)
{
	FILE *out_file;
	int i;

	printf("Write Out Image %s: %d*%d\n",out_fn,X,Y);

	out_file = fopen(out_fn,"wb");
	if(out_file == NULL){
		printf("Can't open output file. Exiting.\n");
		exit(1);
	}
 
	// write image dimensions 
	fprintf(out_file,"P5\n%d %d\n255\n",X,Y);

	// since we flipped the image upside-down when we read it
 	// we have to write it upside-down so it's stored the right way
    for(i=Y-1;i>=0;i--)
  	  fwrite(&outimage[i*X],sizeof(unsigned char),X,out_file);

	fclose(out_file);
}
