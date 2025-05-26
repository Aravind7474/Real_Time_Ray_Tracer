#include "Application.h"

Application::Application()
{
	_ray_tracer.run(view_result);
	WriteFile();
}

Application::~Application()
{
	if (view_result.data != NULL)
	{
		delete [] view_result.data;
	}

	if (view_result.fdata != NULL)
	{
		delete [] view_result.fdata;
	}

	if (view_result.intData != NULL)
	{
		delete [] view_result.intData;
	}
}

void Application::ReadFile(char * file)
{
   FILE *fp;
   char imageType[3],str[100];
   int dummy;
   int i,j;

   if(file == NULL)
		return;

   // Read PGM image file with filename "file"

   // The PGM file format for a GREYLEVEL image is:
   // P5 (2 ASCII characters) <CR>
   // two ASCII numbers for nx ny (number of rows and columns <CR>
   // 255 (ASCII number) <CR>
   // binary pixel data with one byte per pixel

   // The PGM file format for a COLOR image is:
   // P6 (2 ASCII characters) <CR>
   // two ASCII numbers for nx ny (number of rows and columns <CR>
   // 255 (ASCII number) <CR>
	//binary pixel data with three bytes per pixel (one byte for each RGB)

    fp=fopen(file,"rb");

    //free memory from old image, if any
    if(view_result.n>0)
    {
	  delete[] view_result.data;
	}

    //read the first ASCII line to find out if we read a color image or
	// a greylevel image

    fgets(str,100,fp);
	sscanf(str,"%s",imageType);

    if(!strncmp(imageType,"P5",2)) // greylevel image 
    {
       view_result.ncolorChannels=1;
	} 
	else if(!strncmp(imageType,"P6",2)) // color image 
    {
	   view_result.ncolorChannels=3;
	}
	// skip comments embedded in header
    fgets(str,100,fp);  
	while(str[0]=='#')
		fgets(str,100,fp);

    // read image dimensions 
    sscanf(str,"%d %d",&view_result.nx,&view_result.ny);

	// read the next line into dummy variable
    fgets(str,100,fp);  
	 
   	// allocate the memory
	view_result.n=view_result.nx*view_result.ny;

    // read the image data 
	view_result.data = new unsigned char [view_result.n*view_result.ncolorChannels];
	fread(view_result.data,sizeof(unsigned char),view_result.n*view_result.ncolorChannels,fp);

  	//unfortunately OpenGL displays the image upside-down we have to flip it at read time.
    FlipImage(&view_result);

	fclose(fp);

}

void Application::WriteFile()
{
   FILE *fp;
   char imageType[3],str[100];
   int dummy,i;
   char *file = "results_ray_tracing.ppm";
   if(file == NULL)
		return;

   // Write PGM image file with filename "file"

   // The PGM file format for a GREYLEVEL image is:
   // P5 (2 ASCII characters) <CR>
   // two ASCII numbers for nx ny (number of rows and columns <CR>
   // 255 (ASCII number) <CR>
   // binary pixel data with one byte per pixel

   // The PGM file format for a COLOR image is:
   // P6 (2 ASCII characters) <CR>
   // two ASCII numbers for nx ny (number of rows and columns <CR>
   // 255 (ASCII number) <CR>
   // binary pixel data with three bytes per pixel (one byte for each R,G,B)

    fp=fopen(file,"wb");

    // write the first ASCII line with the file type
	if(view_result.ncolorChannels==1)
   	  fprintf(fp,"P5\n"); //greylevel image
    else if(view_result.ncolorChannels==3)
      fprintf(fp,"P6\n");  // color image

    // write image dimensions 
    fprintf(fp,"%d %d\n",view_result.nx,view_result.ny);

	// write '255' to the next line 
    fprintf(fp,"255\n");

	// since we flipped the image upside-down when we read it
 	// we have to write it upside-down so it's stored the right way
    for(i=view_result.ny-1;i>=0;i--)
  	  fwrite(&view_result.data[i*view_result.nx*view_result.ncolorChannels],sizeof(unsigned char),view_result.nx*view_result.ncolorChannels,fp);

	fclose(fp);
}

// flips an image upside down
// you will not have to change anything here

void Application::FlipImage(Image *img)
{
    int i,j,k,rowOffsetSrc,rowOffsetDest,columnOffset;
    unsigned char ctmp;

	for(i=0;i<img->ny/2;i++)
	{
	   rowOffsetSrc=i*img->nx*img->ncolorChannels;
	   rowOffsetDest=(img->ny-1-i)*img->nx*img->ncolorChannels;
       for(j=0;j<img->nx;j++)
	   {
		   columnOffset=j*img->ncolorChannels;
		   for(k=0;k<img->ncolorChannels;k++)
		   {
			   ctmp=img->data[rowOffsetSrc+columnOffset+k];
               img->data[rowOffsetSrc+columnOffset+k]=img->data[rowOffsetDest+columnOffset+k];
               img->data[rowOffsetDest+columnOffset+k]=ctmp;
		   }
	   }
	}
}
// put your application routines here:
