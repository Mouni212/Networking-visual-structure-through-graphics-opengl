#include <IL/il.h>
#include<IL/ilu.h>
#include <GL/glut.h>
#include<math.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

#define DEFAULT_WIDTH  1000
#define DEFAULT_HEIGHT 1000

using namespace std;

float p,p1,p2;
int width  = 1000;
int height = 1000;
int depth = 1000.0;
GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
static int spin = 0;
float red=1.0f, blue=1.0f, green=1.0f;
float angle = 0.0f;
float lx=0.1f,lz=-1.0f,ly = 0.1f;
float x=2.0f,z=200.0f,y=5.0f;
static char theStringBuffer[10]; 
static long font = (long)  GLUT_BITMAP_TIMES_ROMAN_24  ; 
static float h1 = 0.5;

void host()
{
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_COLOR_MATERIAL);
   glColor3f(1.0f, 0.0f, 0.0f);
   glutSolidSphere(3, 20, 16);
   glDisable(GL_LIGHTING);
   glDisable(GL_LIGHT0);
   glDisable(GL_COLOR_MATERIAL);
   glFlush ();
}


void router()
{
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_COLOR_MATERIAL);
   glColor3f(1.0f, 1.0f, 0.0f);
   glutSolidSphere(3, 20, 16);
   glDisable(GL_LIGHTING);
   glDisable(GL_LIGHT0);
   glDisable(GL_COLOR_MATERIAL);
   glFlush ();
}


int LoadImage(char *filename)
{
    ILboolean success; 
     ILuint image; 
    ilGenImages(1, &image); 
     ilBindImage(image); 
     success = ilLoadImage(filename);
    if (success) 
    {
           success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE); 
        if (!success){
                 return -1;}
    }
    else
        return -1;

    return image;
}

// Routine to draw a bitmap character string.
void writeBitmapString(void *font, char *string)
{  
   char *c;

   for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Routine to onvert floating point to char string.
void floatToString(char * destStr, int precision, float val) 
{
   sprintf(destStr,"%f",val);
   destStr[precision] = '\0';
}

// Write data.
void writeData(void)
{
   glColor3f(0.0, 1.0, 0.0);
   
   floatToString(theStringBuffer, 4, h1);
   glRasterPos3f(0.06*width, 0.03*height, -0.4*depth);
   writeBitmapString((void*)font, "SWITCHING FABRIC");
}


void display() 
{
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	    glLoadIdentity ();
	gluLookAt(	x, y, z,
			x+lx, y+ly, z+lz,
			0.0f, 1.0f,  0.0f);

int iTimeElapsed = glutGet(GLUT_ELAPSED_TIME);
p2 = iTimeElapsed*0.00001;

int flag=0;
	if(z>-200){
	//before image
		glPushMatrix();
			p1=p2;
		    GLuint texid;
		    ILuint    image;
			image = LoadImage("/home/mounika/Desktop/sem6/computergraphics/project1/network.jpg");
		    if ( image == -1 )
		    {
			printf("Can't load picture file  by DevIL ");
			return ;
		    }
			iluFlipImage();
		       glGenTextures(1, &texid); 
		       glBindTexture(GL_TEXTURE_2D, texid); 
		       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
		       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		       glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
			0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());

			//center
			glBegin(GL_QUADS);
			   glTexCoord2i(0, 0); glVertex3f(-0.2*width,   -0.2075*height, -0.2*depth);
			   glTexCoord2i(1, 0); glVertex3f(0.25*width,   -0.2075*height, -0.2*depth);
			   glTexCoord2i(1, 1); glVertex3f(0.25*width, 0.2575*height, -0.2*depth);
			   glTexCoord2i(0, 1); glVertex3f(-0.2*width, 0.2575*height, -0.2*depth);
		       glEnd();	
			//left
			glBegin(GL_QUADS);
			   glTexCoord2i(0, 0); glVertex3f(-0.2*width,   -0.2075*height, -0.2*depth);
			   glTexCoord2i(1, 0); glVertex3f(-0.4*width,   -0.2075*height, 0.25*depth);
			   glTexCoord2i(1, 1); glVertex3f(-0.4*width, 0.2575*height, 0.25*depth);
			   glTexCoord2i(0, 1); glVertex3f(-0.2*width, 0.2575*height, -0.2*depth);
		       glEnd();				

			//right
			glBegin(GL_QUADS);
			   glTexCoord2i(0, 0); glVertex3f(0.25*width,   -0.2075*height, -0.2*depth);
			   glTexCoord2i(1, 0); glVertex3f(0.45*width,   -0.2075*height, 0.25*depth);
			   glTexCoord2i(1, 1); glVertex3f(0.45*width, 0.2575*height, 0.25*depth);
			   glTexCoord2i(0, 1); glVertex3f(0.25*width, 0.2575*height, -0.2*depth);
		       glEnd();	

			ilDeleteImages(1, &image); 
			glDeleteTextures(1, &texid);

			
			glTranslatef(-75,0.0,-200);
			 host();
			glTranslatef(75.0,0.0,200);

			glTranslatef(100,0.0,-200.0);
			 host();
			glTranslatef(-100.0,0.0,200.0);

	
			glTranslatef(-25,50.0,-200);
			 router();
			glTranslatef(25.0,-50.0,200);

			glTranslatef(50.0,50.0,-200.0);
			 router();
			glTranslatef(-50.0,-50.0,200.0);
			
			glTranslatef(50.0,0.0,-200.0);
			 router();
			glTranslatef(-50.0,0.0,200.0);
		//glColor3f(1.0,1.0,1.0);

		//packet
			glColor3f(1.0,1.0,1.0);
			image = LoadImage("/home/mounika/Desktop/sem6/computergraphics/project1/postcard.jpg");
		    if ( image == -1 )
		    {
			printf("Can't load picture file  by DevIL ");
			return ;
		    }

			iluFlipImage();
		       glGenTextures(1, &texid); 
		       glBindTexture(GL_TEXTURE_2D, texid); 
		       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
		       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		       glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
			0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
			
			glColor3f(0.5,0.0,0.0);
			/*glBegin(GL_QUADS);
				   glTexCoord2i(0, 0); glVertex3f(-0.079*width,   0.0, -0.1*depth);
				   glTexCoord2i(1, 0); glVertex3f(-0.06*width, 0.0, -0.1*depth);
				   glTexCoord2i(1, 1); glVertex3f(-0.06*width, 0.05*height, -0.1*depth);
				   glTexCoord2i(0, 1); glVertex3f(-0.079*width,   0.05*height, -0.1*depth);
			glEnd();*/

			for(int i=0;i<9;i++){
				if(p2<0.05 + 0.17*i){
				glTranslatef((p2-0.17*i)*width,(p2-0.17*i)*height,0.0);
				 glBegin(GL_QUADS);
					   glTexCoord2i(0, 0); glVertex3f(-0.079*width,   0.0, -0.2*depth);
					   glTexCoord2i(1, 0); glVertex3f(-0.074*width, 0.0, -0.2*depth);
					   glTexCoord2i(1, 1); glVertex3f(-0.072*width, 0.005*height, -0.2*depth);
					   glTexCoord2i(0, 1); glVertex3f(-0.077*width,   0.005*height, -0.2*depth);
					glEnd();
					glTranslatef(-(p2-0.17*i)*width,-(p2-0.17*i)*height,0.0);
				}
				else if(p2<0.125 + 0.17*i){
				glTranslatef(0.0,50,0.0);
				glTranslatef((p2-0.17*i)*width,0.0,0.0);
				 glBegin(GL_QUADS);
					   glTexCoord2i(0, 0); glVertex3f(-0.079*width,   0.0, -0.2*depth);
					   glTexCoord2i(1, 0); glVertex3f(-0.074*width, 0.0, -0.2*depth);
					   glTexCoord2i(1, 1); glVertex3f(-0.072*width, 0.005*height, -0.2*depth);
					   glTexCoord2i(0, 1); glVertex3f(-0.077*width,   0.005*height, -0.2*depth);
					glEnd();
					glTranslatef(-(p2-0.17*i)*width,0.0,0.0);
				
				}
				else if(p2<0.17 + 0.17*i){
				glTranslatef(0.0,(p2-0.17*i)*height,0.0);
				glColor3f(1.0,1.0,1.0);
				glTranslatef((p2-0.17*i)*width,-(p2-0.17*i)*height,0.0);
				 glBegin(GL_QUADS);
					   glTexCoord2i(0, 0); glVertex3f(-0.079*width,   0.0, -0.2*depth);
					   glTexCoord2i(1, 0); glVertex3f(-0.074*width, 0.0, -0.2*depth);
					   glTexCoord2i(1, 1); glVertex3f(-0.072*width, 0.005*height, -0.2*depth);
					   glTexCoord2i(0, 1); glVertex3f(-0.077*width,   0.005*height, -0.2*depth);
					glEnd();
					glTranslatef(-(p2-0.17*i)*width,(p2-0.17*i)*height,0.0);
				}
				printf("%f\n",p2);
			}
			glColor3f(1.0,1.0,1.0);

			ilDeleteImages(1, &image); 
			glDeleteTextures(1, &texid);
			glPopMatrix();
		}

		else if((x > -0.09*width && x < -0.06*width) || (x > 0.09*width && x < 0.11*width)){
			p=p2-p1;
			
			glClearColor (0.0, 0.0, 0.0, 0.0);
			glPushMatrix();

			    GLuint texid;
			    ILuint    image;


			//Front face
			    image = LoadImage("/home/mounika/Desktop/sem6/computergraphics/project1/box.jpg");
			    if ( image == -1 )
			    {
				printf("Can't load picture file  by DevIL ");
				return ;
			    }
			       glGenTextures(1, &texid); 
			       glBindTexture(GL_TEXTURE_2D, texid); 
			       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
			       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			       glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
				0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());

			       
				glTranslatef(0.0,-100.0,-700.0);
				if(p>0.2)
					glTranslatef((p-0.2)*width,0.0,0.0);
				glBegin(GL_QUADS);
				   glTexCoord2i(0, 0); glVertex3f(0.0375*width,   0.0375*height, 0.0*depth);
				   glTexCoord2i(0, 1); glVertex3f(0.0375*width,   0.0625*height, 0.0*depth);
				   glTexCoord2i(1, 1); glVertex3f(0.0625*width, 0.0625*height, 0.0*depth);
				   glTexCoord2i(1, 0); glVertex3f(0.0625*width, 0.0375*height, 0.0*depth);
			       glEnd();
				ilDeleteImages(1, &image); 
				glDeleteTextures(1, &texid);


			//back face
				image = LoadImage("/home/mounika/Desktop/sem6/computergraphics/project1/box.jpg");
			    if ( image == -1 )
			    {
				printf("Can't load picture file  by DevIL ");
				return ;
			    }
			       glGenTextures(1, &texid); 
			       glBindTexture(GL_TEXTURE_2D, texid); 
			       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
			       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			       glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
				0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());

			       glBegin(GL_QUADS);
				   glTexCoord2i(0, 0); glVertex3f(0.0375*width,   0.0375*height, 0.2*depth);
				   glTexCoord2i(0, 1); glVertex3f(0.0375*width,   0.0625*height, 0.2*depth);
				   glTexCoord2i(1, 1); glVertex3f(0.0625*width, 0.0625*height, 0.2*depth);
				   glTexCoord2i(1, 0); glVertex3f(0.0625*width, 0.0375*height, 0.2*depth);
			       glEnd();
				ilDeleteImages(1, &image); 
				glDeleteTextures(1, &texid);

				

			//bottom face
				image = LoadImage("/home/mounika/Desktop/sem6/computergraphics/project1/box.jpg");
			    if ( image == -1 )
			    {
				printf("Can't load picture file  by DevIL ");
				return ;
			    }
			       glGenTextures(1, &texid); 
			       glBindTexture(GL_TEXTURE_2D, texid); 
			       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
			       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			       glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
				0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());

			       glBegin(GL_QUADS);
				   glTexCoord2i(0, 0); glVertex3f(0.0375*width,   0.0375*height, 0.0);
				   glTexCoord2i(0, 1); glVertex3f(0.0625*width,   0.0375*height, 0.0);
				   glTexCoord2i(1, 1); glVertex3f(0.0625*width, 0.0375*height, 0.2*depth);
				   glTexCoord2i(1, 0); glVertex3f(0.0375*width, 0.0375*height, 0.2*depth);
			       glEnd();
				ilDeleteImages(1, &image); 
				glDeleteTextures(1, &texid);


			//left face
				image = LoadImage("/home/mounika/Desktop/sem6/computergraphics/project1/box.jpg");
			    if ( image == -1 )
			    {
				printf("Can't load picture file  by DevIL ");
				return ;
			    }
			       glGenTextures(1, &texid); 
			       glBindTexture(GL_TEXTURE_2D, texid); 
			       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
			       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			       glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
				0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());

			       glBegin(GL_QUADS);
				   glTexCoord2i(0, 0); glVertex3f(0.0375*width,   0.0375*height, 0.2*depth);
				   glTexCoord2i(0, 1); glVertex3f(0.0375*width,   0.0375*height, 0.0);
				   glTexCoord2i(1, 1); glVertex3f(0.0375*width, 0.0625*height, 0.0);
				   glTexCoord2i(1, 0); glVertex3f(0.0375*width, 0.0625*height, 0.2*depth);
			       glEnd();
				ilDeleteImages(1, &image); 
				glDeleteTextures(1, &texid);




			//right face
				image = LoadImage("/home/mounika/Desktop/sem6/computergraphics/project1/box.jpg");
			    if ( image == -1 )
			    {
				printf("Can't load picture file  by DevIL ");
				return ;
			    }
			       glGenTextures(1, &texid); 
			       glBindTexture(GL_TEXTURE_2D, texid); 
			       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
			       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			       glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
				0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());

			       glBegin(GL_QUADS);
				   glTexCoord2i(0, 0); glVertex3f(0.0625*width,   0.0375*height, 0.2*depth);
				   glTexCoord2i(0, 1); glVertex3f(0.0625*width,   0.0375*height, 0.0);
				   glTexCoord2i(1, 1); glVertex3f(0.0625*width, 0.0625*height, 0.0);
				   glTexCoord2i(1, 0); glVertex3f(0.0625*width, 0.0625*height, 0.2*depth);
			       glEnd();
				if(p>0.2)
					glTranslatef(-(p-0.2)*width,0.0,0.0);
				ilDeleteImages(1, &image); 
				glDeleteTextures(1, &texid);


			//letter 


			image = LoadImage("/home/mounika/Desktop/sem6/computergraphics/project1/postcard.jpg");
			    if ( image == -1 )
			    {
				printf("Can't load picture file  by DevIL ");
				return ;
			    }
				iluFlipImage();
			       glGenTextures(1, &texid); 
			       glBindTexture(GL_TEXTURE_2D, texid); 
			       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
			       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			       glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
				0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());

			glTranslatef(0,-30,0);
			float t = 0.01;


				
				if(p<0.0325)
				{
				glTranslatef(0.0015*width, -iTimeElapsed*0.00001*width, 0.2*depth); 
				//glColor3f(1.0f, 0.0f, 0.0f);
				glBegin(GL_QUADS);
				   glTexCoord2i(0, 0); glVertex3f(0.0715*width,   0.2555*height, -0.2*depth);
				   glTexCoord2i(1, 0); glVertex3f(0.083*width, 0.2555*height, -0.2*depth);
				   glTexCoord2i(1, 1); glVertex3f(0.089*width, 0.2675*height, -0.2*depth);
				   glTexCoord2i(0, 1); glVertex3f(0.0765*width,   0.2675*height, -0.2*depth);
				glEnd();	
				glTranslatef(-0.0015*width, iTimeElapsed*0.00001*width, -0.2*depth); 
				p = iTimeElapsed*0.0001;
				}
				else if(p>0.0425 && p<0.0625)
				{
					glTranslatef(0.0015*width, -(p-0.01)*width, 0.2*depth); 
					glBegin(GL_QUADS);
					   glTexCoord2i(0, 0); glVertex3f(0.0715*width,   0.2555*height, -0.2*depth);
					   glTexCoord2i(1, 0); glVertex3f(0.083*width, 0.2555*height, -0.2*depth);
					   glTexCoord2i(1, 1); glVertex3f(0.089*width, 0.2675*height, -0.2*depth);
					   glTexCoord2i(0, 1); glVertex3f(0.0765*width,   0.2675*height, -0.2*depth);
					glEnd();
					glTranslatef(-0.0015*width, (p-0.01)*width, -0.2*depth); 
				}
				//stopping code
				else if(p>=0.0325 && p<=0.0425){
					glTranslatef(0.0015*width, -0.0325*width, 0.2*depth); 
					glBegin(GL_QUADS);
					   glTexCoord2i(0, 0); glVertex3f(0.0715*width,   0.2555*height, -0.2*depth);
					   glTexCoord2i(1, 0); glVertex3f(0.083*width, 0.2555*height, -0.2*depth);
					   glTexCoord2i(1, 1); glVertex3f(0.089*width, 0.2675*height, -0.2*depth);
					   glTexCoord2i(0, 1); glVertex3f(0.0765*width,   0.2675*height, -0.2*depth);
					glEnd();
					glTranslatef(-0.0015*width, 0.0325*width, -0.2*depth); 
				}
				
			//printf("%f ",p);
			//came till 0.0625 now has to stop for 0.01 move for 0.02
			float a = 0.0625;
			for(int i=0;i<5;i++)
			{
				if(p>=a && p<(a+t))
				{
					//stop
					glTranslatef(0.0015*width, -(a-0.01)*width, 0.2*depth); 
					glBegin(GL_QUADS);
					   glTexCoord2i(0, 0); glVertex3f(0.0715*width,   0.2555*height, -0.2*depth);
					   glTexCoord2i(1, 0); glVertex3f(0.083*width, 0.2555*height, -0.2*depth);
					   glTexCoord2i(1, 1); glVertex3f(0.089*width, 0.2675*height, -0.2*depth);
					   glTexCoord2i(0, 1); glVertex3f(0.0765*width,   0.2675*height, -0.2*depth);
					glEnd();
					glTranslatef(-0.0015*width, (a-0.01)*width, -0.2*depth); 
					p=a+t;
				}
				else if(p>=(a+t) && p<(a+3*t))
				{
					//move
					glTranslatef(0.0015*width, -(p-0.02)*width, 0.2*depth); 
					glBegin(GL_QUADS);
					   glTexCoord2i(0, 0); glVertex3f(0.0715*width,   0.2555*height, -0.2*depth);
					   glTexCoord2i(1, 0); glVertex3f(0.083*width, 0.2555*height, -0.2*depth);
					   glTexCoord2i(1, 1); glVertex3f(0.089*width, 0.2675*height, -0.2*depth);
					   glTexCoord2i(0, 1); glVertex3f(0.0765*width,   0.2675*height, -0.2*depth);
					glEnd();
					glTranslatef(-0.0015*width, (p-0.02)*width, -0.2*depth); 
				}
				a = a+0.025;
			}
			glTranslatef(0,30,0);
				ilDeleteImages(1, &image); 
				glDeleteTextures(1, &texid);

			//letter

				image = LoadImage("/home/mounika/Desktop/sem6/computergraphics/project1/postcard.jpg");
			    if ( image == -1 )
			    {
				printf("Can't load picture file  by DevIL ");
				return ;
			    }
				iluFlipImage();
			       glGenTextures(1, &texid); 
			       glBindTexture(GL_TEXTURE_2D, texid); 
			       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
			       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			       glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
				0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
				if(p>0.2){
				glTranslatef((p-0.21+0.0015)*width,-0.2*height,0.0);
				 glBegin(GL_QUADS);
					   glTexCoord2i(0, 0); glVertex3f(0.0715*width,   0.2555*height, 0.1*depth);
					   glTexCoord2i(1, 0); glVertex3f(0.083*width, 0.2555*height, 0.1*depth);
					   glTexCoord2i(1, 1); glVertex3f(0.089*width, 0.2675*height, 0.1*depth);
					   glTexCoord2i(0, 1); glVertex3f(0.0765*width,   0.2675*height, 0.1*depth);
					glEnd();
					glTranslatef(-(p-0.21+0.0015)*width,0.2*height,0.0);
				}
				ilDeleteImages(1, &image); 
				glDeleteTextures(1, &texid);

			//osi 
				image = LoadImage("/home/mounika/Desktop/sem6/computergraphics/project1/osi.jpg");
			    if ( image == -1 )
			    {
				printf("Can't load picture file  by DevIL ");
				return ;
			    }
				iluFlipImage();
			       glGenTextures(1, &texid); 
			       glBindTexture(GL_TEXTURE_2D, texid); 
			       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
			       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			       glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
				0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());


			       glBegin(GL_QUADS);
				   glTexCoord2i(0, 0); glVertex3f(-0.07*width,   0.0675*height, -0.2*depth);
				   glTexCoord2i(1, 0); glVertex3f(0.07*width,   0.0675*height, -0.2*depth);
				   glTexCoord2i(1, 1); glVertex3f(0.07*width, 0.2675*height, -0.2*depth);
				   glTexCoord2i(0, 1); glVertex3f(-0.07*width, 0.2675*height, -0.2*depth);
			       glEnd();	




				ilDeleteImages(1, &image); 
				glDeleteTextures(1, &texid);
				glPopMatrix();
		
		}

		else if((x > -0.04*width && x < -0.02*width) || (x < 0.06*width && x > 0.04*width)){
			glClearColor (0.0, 0.0, 0.0, 0.0);
			glPushMatrix();
				p=p2-p1;
				glTranslatef(175,10,-500);
				// host();
				//glTranslatef(75.0,0.0,200);
			    glTranslatef(0.5f, 0.5f, 0.0); 
			    //glTranslatef(0.5f, 0.5f, 0.0);
			    int size=0.070f;
				int w=width/10;
				int h = height/10;
				int d = depth/10;
				glTranslatef(-0.325*w,0.0f,-0.1*d);
				//float p = iTimeElapsed*0.0001;
			glTranslatef(-75,0,0);
			p=p*10;
			//packet
				if(p<0.325f)
				{
				glTranslatef(p*w, 0.0f, -0.1*d); 
				glColor3f(0.0f, 0.0f, 1.0f);
				glBegin(GL_POLYGON);
				   glVertex3f(-0.14*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.13*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.135*w, 0.115*h, -0.1*d);
				   glVertex3f(-0.145*w, 0.115*h, -0.1*d);
				glEnd();
				glTranslatef(-p*w, 0.0f, -0.1*d); 
				glColor3f(1.0f, 1.0f, 1.0f);

				}

				else if(p<0.575f){
				glTranslatef(p*w, -(p-0.325)*0.5*h, -0.1*d); 
				glColor3f(0.0f, 0.0f, 1.0f);
				glBegin(GL_POLYGON);
				   glVertex3f(-0.14*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.13*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.135*w, 0.115*h, -0.1*d);
				   glVertex3f(-0.145*w, 0.115*h, -0.1*d);
				glEnd();
					glTranslatef(-p*w, (p-0.325)*0.5*h, -0.1*d); 
				glColor3f(1.0f, 1.0f, 1.0f);
				}
				else {
				glTranslatef(p*w, -0.125*h, -0.1*d); 
				glColor3f(0.0f, 0.0f, 1.0f);
				glBegin(GL_POLYGON);
				   glVertex3f(-0.14*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.13*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.135*w, 0.115*h, -0.1*d);
				   glVertex3f(-0.145*w, 0.115*h, -0.1*d);
				glEnd();
				glTranslatef(-p*w, 0.125*h, -0.1*d); 	
				}
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(0.325*w,0.0*h,0.1*d);

			//packet2

				glTranslatef(-0.4*w,0.0*h,0.1*d);
				
				if(p<0.4f)
				{
				glTranslatef(p*w, 0.0*h, -0.1*d); 
				glColor3f(0.0f, 1.0f, 1.0f);
				glBegin(GL_POLYGON);
				   glVertex3f(-0.14*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.13*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.135*w, 0.115*h, -0.1*d);
				   glVertex3f(-0.145*w, 0.115*h, -0.1*d);
				glEnd();
				glTranslatef(-p*w, 0.0*h, -0.1*d); 

				}

				else if(p<0.65f){
				glTranslatef(p*w, -(p-0.4)*0.5*h, -0.1*d); 
				glColor3f(0.0f, 1.0f, 1.0f);
				glBegin(GL_POLYGON);
				   glVertex3f(-0.14*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.13*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.135*w, 0.115*h, -0.1*d);
				   glVertex3f(-0.145*w, 0.115*h, -0.1*d);
				glEnd();
					glTranslatef(-p*w, (p-0.4)*0.5*h, -0.1*d); 
				}
				else {
				glTranslatef(p*w, -0.125*h, -0.1*d); 
				glColor3f(0.0f, 1.0f, 1.0f);
				glBegin(GL_POLYGON);
				   glVertex3f(-0.14*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.13*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.135*w, 0.115*h, -0.1*d);
				   glVertex3f(-0.145*w, 0.115*h, -0.1*d);
				glEnd();
				glTranslatef(-p*w, 0.125*h, -0.1*d); 	
				}
			glTranslatef(0.4*w,0.0f,0.1*d);
			glColor3f(1.0f, 1.0f, 1.0f);
			//packet3

				glTranslatef(-0.325*w,-0.125*h,0.1*d);
				
				if(p<0.325f)
				{
				glTranslatef(p*w, 0.0*h, -0.1*d); 
				glColor3f(1.0f, 0.0f, 1.0f);
				glBegin(GL_POLYGON);
				   glVertex3f(-0.14*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.13*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.135*w, 0.115*h, -0.1*d);
				   glVertex3f(-0.145*w, 0.115*h, -0.1*d);
				glEnd();
				glTranslatef(-p*w, 0.0*h, -0.1*d); 

				}

				else if(p<0.575f){
				glTranslatef(p*w, -(p-0.325)*0.5*h, -0.1*d); 
				glColor3f(1.0f, 0.0f, 1.0f);
				glBegin(GL_POLYGON);
				   glVertex3f(-0.14*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.13*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.135*w, 0.115*h, -0.1*d);
				   glVertex3f(-0.145*w, 0.115*h, -0.1*d);
				glEnd();
					glTranslatef(-p*w, (p-0.325)*0.5*h, -0.1*d); 
				}
				else {
				glTranslatef(p*w, -0.125*h, -0.1*d); 
				glColor3f(1.0f, 0.0f, 1.0f);
				glBegin(GL_POLYGON);
				   glVertex3f(-0.14*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.13*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.135*w, 0.115*h, -0.1*d);
				   glVertex3f(-0.145*w, 0.115*h, -0.1*d);
				glEnd();
				glTranslatef(-p*w, 0.125*h, -0.1*d); 	
				}
			glTranslatef(0.325*w,0.125*h,0.1*d);
			glColor3f(1.0f, 1.0f, 1.0f);
			//packet4

				glTranslatef(-0.325*w,-0.25*h,0.1*d);
				if(p<0.325f)
				{
				glTranslatef(p*w, 0.0*h, -0.1*d); 
				glColor3f(1.0f, 0.0f, 1.0f);
				glBegin(GL_POLYGON);
				   glVertex3f(-0.14*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.13*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.135*w, 0.115*h, -0.1*d);
				   glVertex3f(-0.145*w, 0.115*h, -0.1*d);
				glEnd();
				glTranslatef(-p*w, 0.0*h, -0.1*d); 

				}

				else if(p<0.575f){
				glTranslatef(p*w, (p-0.325)*h, -0.1*d); 
				glColor3f(1.0f, 0.0f, 1.0f);
				glBegin(GL_POLYGON);
				   glVertex3f(-0.14*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.13*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.135*w, 0.115*h, -0.1*d);
				   glVertex3f(-0.145*w, 0.115*h, -0.1*d);
				glEnd();
					glTranslatef(-p*w, -(p-0.325)*h, -0.1*d); 
				}
				else {
				glTranslatef(p*w, 0.25*h, -0.1*d); 
				glColor3f(1.0f, 0.0f, 1.0f);
				glBegin(GL_POLYGON);
				   glVertex3f(-0.14*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.13*w, 0.125*h, -0.1*d);
				   glVertex3f(-0.135*w, 0.115*h, -0.1*d);
				   glVertex3f(-0.145*w, 0.115*h, -0.1*d);
				glEnd();
				glTranslatef(-p*w, -0.25*h, -0.1*d); 	
				}
				p=p/10;
			glTranslatef(0.325*w,0.25*h,0.1*d);
			//glTranslatef(35,25,0);
			glColor3f(1.0f, 1.0f, 1.0f);
			//switching fabric
				glTranslatef(0.125*w,-0.175*h,0.0*d);
			    for(int i=0;i<70;i++)
			    {
				glTranslatef(0.0*w,0.0050*h,0.0*d);
				glColor3f(0.396*w, 0.263*h, 0.129*d);
				glutSolidCube(0.0050*w);
				//glTranslatef(-(0.025f+i*size),-0.025f,0.0);
			    } 

			    for(int i=0;i<50;i++)
			    {
				glTranslatef(-0.0050*w,0.0,0.0);
				glColor3f(0.396*w, 0.263*h, 0.129*d);
				glutSolidCube(0.0050*w);
				//glTranslatef(-(0.025f+i*size),-0.025f,0.0);
			    }

			    for(int i=0;i<70;i++)
			    {
				glTranslatef(0.0,-0.0050*h,0.0);
				glColor3f(0.396*w, 0.263*h, 0.129*d);
				glutSolidCube(0.0050*w);
				//glTranslatef(-(0.025f+i*size),-0.025f,0.0);
			    }

			    for(int i=0;i<50;i++)
			    {
				glTranslatef(0.0050*w,0.0,0.0);
				glColor3f(0.396*w, 0.263*h, 0.129*d);
				glutSolidCube(0.0050*w);
				//glTranslatef(-(0.025f+i*size),-0.025f,0.0);
			    }

				glTranslatef(-0.125*w,0.175*h,0.0);

			//left side
				glTranslatef(-0.225*w,0.125*h,0.0);
				glColor3f(0.396*w, 0.0f, 0.09*d);
				glutSolidCube(0.050*w);
					
				glTranslatef(-0.10*w,0.0f,0.0);
				glColor3f(0.396*w, 0.0f, 0.09*d);
				glutSolidCube(0.050*w);	

				glTranslatef(-0.10*w,0.0f,0.0);
				glColor3f(0.396*w, 0.0f, 0.09*d);
				glutSolidCube(0.050*w);

				glTranslatef(+0.425*w,-0.125*h,0.0);

				glTranslatef(-0.225*w,0.0f,0.0);
				glColor3f(0.396*w, 0.0f, 0.09*d);
				glutSolidCube(0.050*w);
					
				glTranslatef(-0.10*w,0.0f,0.0);
				glColor3f(0.396*w, 0.0f, 0.09*d);
				glutSolidCube(0.050*w);	

				glTranslatef(-0.10*w,0.0f,0.0);
				glColor3f(0.396*w, 0.0f, 0.09*d);
				glutSolidCube(0.050*w);

				glTranslatef(+0.425*w,-0.0*h,0.0);

				glTranslatef(-0.225*w,-0.125*h,0.0);
				glColor3f(0.396*w, 0.0f, 0.09*d);
				glutSolidCube(0.050*w);
					
				glTranslatef(-0.10*w,0.0f,0.0);
				glColor3f(0.396*w, 0.0f, 0.09*d);
				glutSolidCube(0.050*w);	

				glTranslatef(-0.10*w,0.0f,0.0);
				glColor3f(0.396*w, 0.0f, 0.09*d);
				glutSolidCube(0.050*w);

				glTranslatef(+0.425*w,0.125*h,0.0);

				//right side
				glTranslatef(0.225*w,0.125*h,0.0);
				glColor3f(0.396*w, 0.0f, 0.09*d);
				glutSolidCube(0.050*w);
					
				glTranslatef(0.10*w,0.0f,0.0);
				glutSolidCube(0.050*w);	

				glTranslatef(0.10*w,0.0f,0.0);
				glutSolidCube(0.050*w);

				glTranslatef(-0.425*w,-0.125*h,0.0);

				glTranslatef(0.225*w,0.0f,0.0);
				glutSolidCube(0.050*w);
					
				glTranslatef(0.10*w,0.0f,0.0);
				glColor3f(0.396*w, 0.0f, 0.09*d);
				glutSolidCube(0.050*w);	

				glTranslatef(0.10*w,0.0f,0.0);
				glutSolidCube(0.050*w);

				glTranslatef(-0.425*w,-0.0*h,0.0);

				glTranslatef(0.225*w,-0.125*h,0.0);
				glutSolidCube(0.050*w);
					
				glTranslatef(0.10*w,0.0*h,0.0);
				glutSolidCube(0.050*w);	

				glTranslatef(0.10*w,0.0f,0.0);
				glutSolidCube(0.050*w);

				glTranslatef(-0.425*w,0.125*h,0.0);
			    
						glTranslatef(75,0,0);
			    glPopMatrix();
				writeData();
				//glOrtho(0.0, width, height, 0.0, -depth, depth);
			}
			    glutSwapBuffers();
} 



void reshape(GLsizei w, GLsizei h) 
{
    if (h == 0)  h = 1;      // prevent divide by zero
	float ratio =  w * 1.0 / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
    glViewport     (0, 0, w, h);
       // glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	gluPerspective(45.0f, ratio, 0.1f, 10000.0f);
    glMatrixMode   (GL_MODELVIEW);
//  gluLookAt      (0, 3, 5, 0, 0, 0,	0.0f, 1.0f, 0.0f);
glutPostRedisplay();
}

/* Initialize OpenGL Graphics */
void init(void) 
{
	glEnable(GL_TEXTURE_2D);     // Enable 2D texturing
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//   glEnable(GL_LIGHTING);
   //glEnable(GL_LIGHT0);
   glColorMaterial(GL_FRONT, GL_DIFFUSE);
   //glEnable(GL_COLOR_MATERIAL);
}



void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 5.0f;

	switch (key) {
		case GLUT_KEY_F1 :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_F2 :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_F3 :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_F4 :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
		case GLUT_KEY_F5 :
			angle += 0.01f;
			ly = sin(angle);
			break;
		case GLUT_KEY_F6 :
			angle -= 0.01f;
			ly = sin(angle);
			break;
	}
}


int main(int argc, char **argv) 
{
    glutInit(&argc, argv);        
    glutInitDisplayMode    (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize     (1000, 1000);
       glutCreateWindow("DF"); 
		init();    
       glutDisplayFunc(display);    
       glutReshapeFunc(reshape);
		glutIdleFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys); 
	glEnable(GL_DEPTH_TEST);

     if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
     {
           printf("wrong DevIL version ");
           return -1;
     }
     ilInit(); 
    glutMainLoop();

     return 0;
} 


