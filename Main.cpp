#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <stdlib.h>
#include "Application.h"
Application application;
GLuint texture_id;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
	glClearColor(1.0, 1.0, 1.0,0.0);	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0);
		glVertex2f(0.0, 0.0);

		glTexCoord2f(0.0, 1.0);
		glVertex2f(0.0, 1.0);

		glTexCoord2f(1.0, 1.0);
		glVertex2f(1.0, 1.0);

		glTexCoord2f(1.0, 0.0);
		glVertex2f(1.0, 0.0);
	glEnd();
	
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	if(h == 0) h = 1;
	glViewport(0, 0, w, h ); 
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	gluOrtho2D(-0.1, 1.1, -0.1, 1.1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void create_texture()
{
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	const Image & view_result = application.get_image();
	glTexImage2D(GL_TEXTURE_2D, 0, 3, view_result.nx, view_result.ny, 0, GL_RGB, GL_UNSIGNED_BYTE, view_result.data);
	glEnable(GL_TEXTURE_2D);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Ray Tracing");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	create_texture();
	glutMainLoop();
	glDeleteTextures( 1, &texture_id);
	return 0;
}
