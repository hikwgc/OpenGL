/*  c7-3.c   Copyright (c) 2003 by T. HAYASHI and K. KATO  */
/*                                    All rights reserved  */
#include <stdlib.h>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include <math.h>
#define KEY_ESC 27
/*
#define imageWidth 8
#define imageHeight 8

void polarview( void );
void resetview( void );
unsigned char image[imageHeight][imageWidth][4];
float xOrigin = 0.0, yOrigin = 0.0;
int xBegin = 0, yBegin = 0;
int mButton;
float distance, twist, elevation, azimuth;
float znear = 1.0, zfar = 80.0, fovy = 40.0;


unsigned char bitmap1[imageHeight][imageWidth]=
{
	{0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00},
	{0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00},
	{0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00},
	{0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff}
};
unsigned char bitmap2[imageHeight][imageWidth]=
{
	{0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00},
	{0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00},
	{0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00},
	{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
	{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
	{0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00},
	{0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00},
	{0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00}
};

void display(void)
{
	float diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	float texcolor[] = { 1.0, 0.0, 0.0, 1.0 };
    
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, texcolor);
	glEnable(GL_TEXTURE_2D);
    
	glPushMatrix ();
	polarview();
    
	glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );
	glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
	glMaterialfv( GL_FRONT, GL_AMBIENT, ambient );
	glMaterialf( GL_FRONT, GL_SHININESS, 128.0 );
    
    glEnable( GL_LIGHTING );
	glEnable( GL_DEPTH_TEST );
    
	glNormal3f(0.0,1.0,0.0);
	glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0); glVertex3f(1.0,0.0,1.0);
    glTexCoord2f(0.0,5.0); glVertex3f(1.0,0.0,-1.0);
    glTexCoord2f(5.0,5.0); glVertex3f(-1.0,0.0,-1.0);
    glTexCoord2f(5.0,0.0); glVertex3f(-1.0,0.0,1.0);
	glEnd();
	glPopMatrix();
    
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

void myKbd( unsigned char key, int x, int y )
{
	switch(key) {
        case 'R':
            resetview();
            break;
        case 's':
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            break;
        case 'S':
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            break;
        case 't':
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            break;
        case 'T':
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        case 'b':
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
            break;
        case 'd':
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            break;
        case 'm':
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            break;
        case 'p':
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            break;
        case KEY_ESC:
            exit( 0 );
        default :
            break;
    }
	glutPostRedisplay();
}


void myMouse( int button, int state, int x, int y )
{
    if (state == GLUT_DOWN) {
        xBegin = x;
        yBegin = y;
		mButton = button;
    }
}


void myMotion(int x, int y)
{
    int xDisp, yDisp;
    
    xDisp = x - xBegin;
    yDisp = y - yBegin;
    switch(mButton){
        case GLUT_LEFT_BUTTON:
            azimuth += (float) xDisp/2.0;
            elevation -= (float) yDisp/2.0;
            break;
        case GLUT_MIDDLE_BUTTON:
            twist = fmod (twist + xDisp/3.0, 360.0);
            break;
        case GLUT_RIGHT_BUTTON:
            distance -= (float) yDisp/60.0;
            break;
    }
    xBegin = x;
    yBegin = y;
    glutPostRedisplay();
}

void makeImage(void)
{
	int i,j;
	for (i = 0; i < imageHeight; i++) {
   		for (j = 0; j < imageWidth; j++) {
        	image[i][j][0] = (unsigned char) bitmap2[i][j];			// bitmap2§À —§®§ø§Í
        	image[i][j][1] = (unsigned char) bitmap2[i][j];			// bitmap1§Œ∆‚Õ∆§Ú —§®§∆§ﬂ§Î
        	image[i][j][2] = (unsigned char) bitmap2[i][j];
        	image[i][j][3] = (unsigned char) 50;
     	}
	}
}


void initTexture(void)
{
	makeImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageWidth, imageHeight, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, imageWidth, imageHeight,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
}


void myInit (char *progname)
{
    int width = 400, height = 400;
    
    glutInitWindowPosition(0, 0); glutInitWindowSize( width, height);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(progname);
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glutKeyboardFunc( myKbd );
    glutMouseFunc( myMouse );
    glutMotionFunc( myMotion );
	initTexture();
	resetview();
	glEnable( GL_LIGHT0 );
}


void myReshape(int width, int height)
{
    float aspect;
    
    aspect = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspect, znear, zfar);
    glMatrixMode(GL_MODELVIEW);
}


void polarview( void )
{
    glTranslatef( 0.0, 0.0, -distance);
    glRotatef( -twist, 0.0, 0.0, 1.0);
    glRotatef( -elevation, 1.0, 0.0, 0.0);
    glRotatef( -azimuth, 0.0, 1.0, 0.0);
}


void resetview( void )
{
	distance = 6.0;
	twist = 0.0;
	elevation = -45.0;
	azimuth = 30.0;
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutReshapeFunc (myReshape);
	glutDisplayFunc(display);
	glutMainLoop();
	return(0);
}
 */
/*

#define imageWidth 512
#define imageHeight 512

void polarview( void );
void resetview( void );
unsigned char image[imageHeight][imageWidth][4];
float distance, twist, elevation, azimuth;
float nearw = 1.0, farw = 20.0, fovy = 60.0;
int mflag=1;
float dist=0.0;

void display(void)
{
    float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glPushMatrix();
	polarview();
    glEnable( GL_DEPTH_TEST );
    
	glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );
	glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
	glMaterialfv( GL_FRONT, GL_AMBIENT, ambient );
	glMaterialf( GL_FRONT, GL_SHININESS, 128.0 );
    glEnable( GL_LIGHTING );
	glTranslatef(0.0,0.0,dist);
	glutSolidSphere( 1.0 ,60 , 60);
	glPopMatrix();
	glDisable( GL_LIGHTING );
    glDisable( GL_DEPTH_TEST );
	glutSwapBuffers();
}

void idle( void )
{
	if (mflag==1) {
		if (dist<-farw) {
			mflag=0;
			dist=-farw;
		}
		else dist-=1.0;
	}
	else {
		if (dist>0.0) {
			mflag=1;
			dist=0.0;
		}
		else dist+=0.05;
	}
	glutPostRedisplay();
}


void myKbd(unsigned char key, int x, int y)
{
	switch(key) {
        case KEY_ESC:
            exit( 0 );
        default:
            break;
	}
}

void makeImage(void)
{
	int i, j, c,d;
    
    for (i = 0; i < imageHeight; i++) {
        for (j = 0; j < imageWidth; j++) {
			d=150.0*(rand()/(float)RAND_MAX);
			c=d+50;
            image[i][j][0] = (unsigned char) c;
            image[i][j][1] = (unsigned char) 0;
            image[i][j][2] = (unsigned char) 0;
            image[i][j][3] = (unsigned char) 200;
        }
    }
    for (i = 0; i < imageHeight; i+=32) {
        for (j = 0; j < imageWidth; j++) {
			image[i][j][0] = (unsigned char) 0;
			image[i][j][1] = (unsigned char) 255;
			image[i][j][2] = (unsigned char) 255;
			image[i][j][3] = (unsigned char) 255;
        }
    }
}

//void initTexture(void)
//{
//	makeImage();
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexImage2D(GL_TEXTURE_2D, 0, 4, imageWidth, imageHeight,
  //               0, GL_RGBA, GL_UNSIGNED_BYTE, image);
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//    glEnable(GL_TEXTURE_GEN_S);
//    glEnable(GL_TEXTURE_GEN_T);
//    glEnable(GL_TEXTURE_2D);
//}


 void initTexture(void)
 {
 makeImage();
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
 gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageWidth, imageHeight,
 GL_RGBA, GL_UNSIGNED_BYTE, image);
 glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
 glEnable(GL_TEXTURE_GEN_S);
 glEnable(GL_TEXTURE_GEN_T);
 glEnable(GL_TEXTURE_2D);
 }


void myInit (char *progname)
{
    int width = 400, height = 400;
    
    glutInitWindowPosition(0, 0);
	glutInitWindowSize( width, height);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(progname);
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glutKeyboardFunc(myKbd);
	resetview();
	initTexture();
	glShadeModel( GL_SMOOTH );
	glEnable( GL_LIGHT0 );
}


void myReshape(int width, int height)
{
    float aspect = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspect, nearw, farw);
    glMatrixMode(GL_MODELVIEW);
}


void polarview( void )
{
    glTranslatef( 0.0, 0.0, -distance);
    glRotatef( -twist, 0.0, 0.0, 1.0);
    glRotatef( -elevation, 1.0, 0.0, 0.0);
    glRotatef( -azimuth, 0.0, 1.0, 0.0);
}


void resetview( void )
{
	distance = 3.0;
    twist = 0.0;
    elevation = 0.0;
    azimuth = 0.0;
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutReshapeFunc (myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	return(0);
}
*/

/*
#define IMAGE_HEIGHT	64
#define IMAGE_WIDTH		64

void polarview( void );
void resetview( void );

float xOrigin = 0.0, yOrigin = 0.0;
int xBegin = 0, yBegin = 0;
float distance, twist, elevation, azimuth;
float nearw = 1.0, farw = 30.0, fovy = 60.0;
int mButton;
float tval=0.0;
unsigned int texname=1;

unsigned char image1[IMAGE_HEIGHT][IMAGE_WIDTH][4];
void MakeImage1(void)
{
	int i, j, color;
	glBindTexture(GL_TEXTURE_2D, texname);
    for (i = 0; i < IMAGE_HEIGHT; i++) {
        for (j = 0; j < IMAGE_WIDTH; j++) {
            color = ((((i&0x8)==0)^((j&0x8)==0)))*255;
            image1[i][j][0] = (unsigned char)color;
            image1[i][j][1] = (unsigned char)color;
            image1[i][j][2] = (unsigned char)0;
            image1[i][j][3] = (unsigned char)100;
        }
    }
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4,IMAGE_WIDTH ,IMAGE_HEIGHT,0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
}

void display(void)
{
	float diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glPushMatrix();
	polarview();
    glEnable( GL_DEPTH_TEST );
    
	glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );
	glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
	glMaterialfv( GL_FRONT, GL_AMBIENT, ambient );
	glMaterialf( GL_FRONT, GL_SHININESS, 128.0 );
    glEnable( GL_LIGHTING );
    //	glTranslatef(0.0,tval,0.0);
    //
	glTranslatef(0.0,0.6,0.0);
	glutSolidTeapot(1.0);
    //	glutSolidCube(1.0);
    //	glutSolidSphere(1.0,20,20);
    //
	glPopMatrix();
	glDisable( GL_LIGHTING );
    glDisable( GL_DEPTH_TEST );
	glutSwapBuffers();
}


void SetupTextures(void)
{
    
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //
	MakeImage1();
	//glTexGenf(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
	//glTexGenf(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
    //	glTexGenf(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
    //	glTexGenf(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
    //	glTexGenf(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
    //	glTexGenf(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_2D);
}

void DeleteTextures(void)
{
	glDeleteTextures(1,&texname);
}

void myKbd(unsigned char key, int x, int y)
{
	switch(key) {
        case KEY_ESC:
            DeleteTextures();
            exit( 0 );
        default:
            break;
	}
}

void myMouse( int button, int state, int x, int y )
{
    if (state == GLUT_DOWN) {
        xBegin = x;
        yBegin = y;
		mButton=button;
    }
}


void myMotion(int x, int y)
{
    int xDisp, yDisp;
    
    xDisp = x - xBegin;
    yDisp = y - yBegin;
    switch(mButton){
        case GLUT_LEFT_BUTTON:
            azimuth += (float) xDisp/2.0;
            elevation -= (float) yDisp/2.0;
            break;
        case GLUT_MIDDLE_BUTTON:
            twist = fmod (twist + xDisp, 360.0);
            break;
        case GLUT_RIGHT_BUTTON:
            distance -= (float) yDisp/40.0;
            break;
    }
    xBegin = x;
    yBegin = y;
    glutPostRedisplay();
}


void myInit(char *progname)
{
    glutInitWindowPosition(0, 0);
	glutInitWindowSize( 400, 400);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(progname);
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glutKeyboardFunc(myKbd);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);
	resetview();
	SetupTextures();
	glShadeModel( GL_SMOOTH );
	glEnable( GL_LIGHT0 );
}


void myReshape(int width, int height)
{
    float aspect = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspect, nearw, farw);
    glMatrixMode(GL_MODELVIEW);
}


void polarview( void )
{
    glTranslatef( 0.0, 0.0, -distance);
    glRotatef( -twist, 0.0, 0.0, 1.0);
    glRotatef( -elevation, 1.0, 0.0, 0.0);
    glRotatef( -azimuth, 0.0, 1.0, 0.0);
}


void resetview( void )
{
	distance = 5.0;
    twist = 0.0;
    elevation = -45.0;
    azimuth = 30.0;
}

int tflag=0;
void idle( void )
{
	if (tflag) {
		tval-=0.05;
		if (tval<0.0) tflag=0;
	}
	else {
		tval+=0.05;
		if (tval> 2.0) tflag=1;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutReshapeFunc (myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	return(0);
}


*/

#define imageWidth 8
#define imageHeight 8

void polarview( void );
void resetview( void );
unsigned char image1[imageHeight][imageWidth][4];
unsigned char image2[imageHeight][imageWidth][4];
int xBegin = 0, yBegin = 0;
int mButton;
float distance, twist, elevation, azimuth;
float nearw = 1.0, farw = 30.0, fovy = 60.0;


void initTexture(void);

void display(void)
{
    float diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
	glPushMatrix();
	polarview();
    glEnable( GL_DEPTH_TEST );
	glEnable(GL_TEXTURE_2D);
    
	glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );
	glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
	glMaterialfv( GL_FRONT, GL_AMBIENT, ambient );
	glMaterialf( GL_FRONT, GL_SHININESS, 128.0 );
    glEnable( GL_LIGHTING );
    
	glBindTexture(GL_TEXTURE_2D,1);
	glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.5,-0.5,0.5);
    glTexCoord2f(0.0,5.0); glVertex3f(-0.5,0.5,0.5);
    glTexCoord2f(5.0,5.0); glVertex3f(0.5,0.5,0.5);
    glTexCoord2f(5.0,0.0); glVertex3f(0.5,-0.5,0.5);
	glEnd();
    
	glBindTexture(GL_TEXTURE_2D,2);
	glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0); glVertex3f(0.5,-0.5,0.5);
    glTexCoord2f(0.0,5.0); glVertex3f(0.5,-0.5,-0.5);
    glTexCoord2f(5.0,5.0); glVertex3f(0.5,0.5,-0.5);
    glTexCoord2f(5.0,0.0); glVertex3f(0.5,0.5,0.5);
	glEnd();

    glBindTexture(GL_TEXTURE_2D,2);
	glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0); glVertex3f(0.5,0.5,-0.5);
    glTexCoord2f(0.0,5.0); glVertex3f(0.5,-0.5,-0.5);
    glTexCoord2f(5.0,5.0); glVertex3f(-0.5,-0.5,-0.5);
    glTexCoord2f(5.0,0.0); glVertex3f(-0.5,0.5,-0.5);
	glEnd();
    
    glBindTexture(GL_TEXTURE_2D,1);
	glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0); glVertex3f(-0.5,0.5,-0.5);
    glTexCoord2f(0.0,5.0); glVertex3f(-0.5,0.5,0.5);
    glTexCoord2f(5.0,5.0); glVertex3f(-0.5,-0.5,0.5);
    glTexCoord2f(5.0,0.0); glVertex3f(-0.5,-0.5,-0.5);
	glEnd();
    
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glDisable( GL_LIGHTING );
    glDisable( GL_DEPTH_TEST );
	glutSwapBuffers();
}

void myKbd(unsigned char key, int x, int y)
{
	switch(key) {
        case KEY_ESC:
            exit( 0 );
        default:
            break;
	}
}

unsigned char bitmap1[imageHeight][imageWidth]=
{
	{0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00},
	{0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00},
	{0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00},
	{0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff}
};
unsigned char bitmap2[imageHeight][imageWidth]=
{
	{0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00},
	{0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00},
	{0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00},
	{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
	{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
	{0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00},
	{0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00},
	{0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00}
};


void makeImage1(void)
{
	int i, j, c;
    
    for (i = 0; i < imageHeight; i++) {
        for (j = 0; j < imageWidth; j++) {
			c = bitmap1[i][j];
            image1[i][j][0] = (unsigned char) c;
            image1[i][j][1] = (unsigned char) c;
            image1[i][j][2] = (unsigned char) c;
            image1[i][j][3] = (unsigned char) 128;
        }
    }
}
void makeImage2(void)
{
	int i, j, c;
    
    for (i = 0; i < imageHeight; i++) {
        for (j = 0; j < imageWidth; j++) {
			c = bitmap2[i][j];
            image2[i][j][0] = (unsigned char) c;
            image2[i][j][1] = (unsigned char) 0;
            image2[i][j][2] = (unsigned char) 0;
            image2[i][j][3] = (unsigned char) 128;
        }
    }
}

void initTexture1(void)
{
	makeImage1();
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D,1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4,imageWidth ,imageHeight,0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
}

void initTexture2(void)
{
	makeImage2();
	
    //	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D,2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4,imageWidth ,imageHeight,0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image2);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
}

void myInit (char *progname)
{
    glutInitWindowPosition(0, 0);
	glutInitWindowSize( 400, 400);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(progname);
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glutKeyboardFunc(myKbd);
    
	resetview();
	initTexture1();
	initTexture2();
	glShadeModel( GL_SMOOTH );
	glEnable( GL_LIGHT0 );
}


void myReshape(int width, int height)
{
    float aspect = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspect, nearw, farw);
    glMatrixMode(GL_MODELVIEW);
}


void polarview( void )
{
    glTranslatef( 0.0, 0.0, -distance);
    glRotatef( -twist, 0.0, 0.0, 1.0);
    glRotatef( -elevation, 1.0, 0.0, 0.0);
    glRotatef( -azimuth, 0.0, 1.0, 0.0);
}


void resetview( void )
{
	distance = 3.0;
    twist = 0.0;
    elevation = -30.0;
    azimuth = 30.0;
}

void myMouse( int button, int state, int x, int y )
{
	if( state == GLUT_DOWN) {
		mButton = button;
        xBegin = x;
        yBegin = y;
	}
}


void myMotion(int x, int y)
{
    int xDisp, yDisp;
    
    xDisp = x - xBegin;
    yDisp = y - yBegin;
    switch(mButton){
        case GLUT_LEFT_BUTTON:
            azimuth += (float) xDisp/2.0;
            elevation -= (float) yDisp/2.0;
            break;
        case GLUT_MIDDLE_BUTTON:
            twist = fmod (twist + xDisp, 360.0);
            break;
        case GLUT_RIGHT_BUTTON:
            distance -= (float) yDisp/40.0;
            break;
    }
    xBegin = x;
    yBegin = y;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutReshapeFunc (myReshape);
	glutDisplayFunc(display);
	glutMouseFunc(myMouse);
	glutMotionFunc( myMotion );
	glutMainLoop();
	return(0);
}







