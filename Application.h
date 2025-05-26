#ifndef __Application_H
#define __Application_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "Ray_Tracer.h"
#include "common/image_volume.h"

class Application {
public:
  Application();
	~Application();	
  
public:
	const Image & get_image() const {	return view_result; }
private:
	void ReadFile(char * file);
	void WriteFile();
	void FlipImage(Image *img);
private:
	Ray_Tracer	_ray_tracer;
	Image view_result; 
	Volume vol;
};

#endif
