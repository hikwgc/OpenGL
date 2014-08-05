//
//  main.cpp
//  PracticeOpenGL
//
//  Created by 川口大志 on 2014/05/15.
//  Copyright (c) 2014年 川口大志. All rights reserved.
//

#include <iostream>
#include <GLUT/glut.h>
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#include "math.h"
#include "myShape.h"
#define KEY_ESC 27
#define PI 3.1415926536

float theta = 0.0;
float dist = 0.0;

void polarview(void);
void resetview(void);
void drawNormal(float, float, float, float, float, float);
void drawNormal( float*, float* );
int xBegin, yBegin;
int mButton;
float distance, twist, elevation, azimuth;

void initLighting(void);

int bWired    = 0;
int bRotating = 0;
int bShading  = 0;
float spin = 0;
int bLightRotating = 0;

// コールバック関数
void displayLight(void) {
    initLighting();
    float diffuse []  = {1.0, 1.0, 1.0, 1.0};
    float specular [] = {1.0, 1.0, 1.0, 1.0};
    float ambient []  = {0.1, 0.1, 0.1, 1.0};
    float shininess   = 128.0;

    
    float light0[] = {-3.0, 0, 0, 1};
    float light1[] = { 0.0, 1.0, 0, 0.0};
    float blueEmission[] = {0.3, 0.3, 1.0, 1.0};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    glPushMatrix();
    polarview();
    glLightfv(GL_LIGHT1, GL_POSITION, light1);
    glPushMatrix();
    glRotatef(spin, 0, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0);
    
    glTranslatef(-3, 0, 0);
    glPushAttrib(GL_LIGHTING_BIT);
    glMaterialfv(GL_FRONT, GL_EMISSION, blueEmission);
    glutSolidCube(0.1);
    glPopAttrib();
    glPopMatrix();
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glRotatef(90, 1, 0, 0);
    glutSolidSphere(1, 100, 100);
    
    glPopMatrix();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glutSwapBuffers();

}

void initLighting(void) {
    float diffuse [] = {1.0, 1.0, 1.0, 1.0};
    float specular[] = {1.0, 1.0, 1.0, 1.0};
    float ambient [] = {0.1, 0.1, 0.1, 1.0};
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
    
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);
    
    glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT4, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT4, GL_AMBIENT, ambient);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    //glEnable(GL_LIGHT4);
}


void displayRocket(void) {
    initLighting();

    float light0[] = {-2.0, 0, 0, 1.0};
    float light1[] = { 0.0, -4.0, 0, 1.0};
    float light2[] = { 3.0, 1.0, 0, 0.0};
    float light3[] = { 0.0, -3.0, 0, 0.0};
    //float light4[] = { 0.0, 3.0, 0, 0.0};
    float blueEmission[] = {0.3, 0.3, 1.0, 1.0};
    float redEmission[] = {1.0, 0.3, 0.3, 1.0};
    
    // for material
    float diffuse []  = {0.0, 0.2, 1.0, 1.0};
    float reddiff []  = {1.0, 0.2, 0.2, 1.0};
    float specular [] = {1.0, 1.0, 1.0, 1.0};
    float ambient []  = {0.1, 0.1, 0.1, 1.0};
    float shininess   = 128.0;
    
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    glPushMatrix();
    polarview();
    glLightfv(GL_LIGHT2, GL_POSITION, light2);
    
    glPushMatrix();
    glRotatef(spin, 1, 0, 0);
    glLightfv(GL_LIGHT1, GL_POSITION, light1);
    glTranslatef(0, -4, 0);
    glPushAttrib(GL_LIGHTING_BIT);
    glMaterialfv(GL_FRONT, GL_EMISSION, blueEmission);
    glutSolidCube(0.1);
    glPopAttrib();
    glPopMatrix();
     
    glPushMatrix();
    glRotatef(spin, 0, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0);
    glTranslatef(-2, 0, 0);
    glPushAttrib(GL_LIGHTING_BIT);
    glMaterialfv(GL_FRONT, GL_EMISSION, blueEmission);
    glutSolidCube(0.1);
    glPopAttrib();
    glPopMatrix();
    
    glPushMatrix();
    glLightfv(GL_LIGHT3, GL_POSITION, light3);
    glTranslatef(0, -2.5, 0);
    glPushAttrib(GL_LIGHTING_BIT);
    glMaterialfv(GL_FRONT, GL_EMISSION, redEmission);
    glutSolidCube(0.2);
    glPopAttrib();
    glPopMatrix();

    //if (bShading) {
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    //}
    glMaterialfv(GL_FRONT, GL_DIFFUSE, reddiff);
    glRotatef(theta, 0, 1, 0);
    
    glPushMatrix();
    glTranslatef(0.0, 1.0, 0.0);
    
    if (bWired) {
        myWireCylinder(1.0, 2.0, 12);
    }
    else {
        glColor3f(0.5, 0.5, 0.5);
        mySolidCylinder(1.0, 2.0, 12);
    
    }
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glTranslatef(0.0, 1.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    if (bWired) {
        glutWireCone(1.0, 2.0, 12, 3);
    }
    else {
        glColor3f(1.0, 0.1, 0.1);
        glutSolidCone(1.0, 2.0, 12, 3);
    }
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, reddiff);
    glTranslatef(0.0, -1.0, 0.0);
    
    glRotatef(-2*theta, 0, 1, 0);
    if (bWired) {
        myWireCylinder(1.0, 2.0, 12);
    }
    else {
        glColor3f(0.5, 0.5, 0.5);
        mySolidCylinder(1.0, 2.0, 12);
    }
    
    glEnable(GL_NORMALIZE);    
    glPushMatrix();
    glScalef( 0.1, 1.0, 1.5);
    if (bWired) {
        glutWireCube(2.0);
    }
    else {
        glColor3f(0.5, 0.1, 0.1);
        glutSolidCube(2.0);
    }
    glPopMatrix();
    
    glPushMatrix();
    glScalef(1.5, 1.0, 0.1);
    if (bWired) {
        glutWireCube(2.0);
    }
    else {
        glColor3f(0.5, 0.1, 0.1);
        glutSolidCube(2.0);
    }
    glPopMatrix();
    glDisable(GL_NORMALIZE);
    
    glTranslatef(0.0, -1.5, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    
/*    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    float Emission[] ={1.0, 0.3, 0.3, 1.0};
    float Emission2[] ={1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Emission2);
    glMaterialfv(GL_BACK, GL_DIFFUSE, Emission);
 */
    if (bWired) {
        glutWireCone(0.5, 1.0, 12, 3);
    }
    else {
        glColor3f(1.0, 0.1, 0.1);
        glutSolidCone(0.5, 1.0, 12, 3);
    }
    
    glDisable(GL_LIGHTING);
    
    glDisable(GL_DEPTH_TEST);
    glPopMatrix();
    glutSwapBuffers();
}





void displayMaterial(void) {
    float diffuse []  = {1.0, 1.0, 1.0, 1.0};
    float specular [] = {1.0, 1.0, 1.0, 1.0};
    float ambient []  = {0.1, 0.1, 0.1, 1.0};
    float shininess   = 128.0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    polarview();
    glEnable(GL_DEPTH_TEST);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    glEnable(GL_LIGHTING);
    
    glutSolidSphere(1, 100, 100);
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glPopMatrix();
    glFlush();
}

void displayShading(void) {
    float vertex_data[4][3] = {  1.0,  0.0,  1.0,
        1.0,  0.0, -1.0,
        -1.0,  0.0, -1.0,
        -1.0,  0.0,  1.0 };
    /*
	float normal_data[4][3] = { 0.447214,  0.774597,  0.447214,
        0.447214,  0.774597, -0.447214,
        -0.447214,  0.774597, -0.447214,
        -0.447214,  0.774597,  0.447214 };
    */
    float normal_data[4][3] = { -1.5,  1.0,  -1.5,
        0.447214,  0.774597, -0.447214,
        -0.447214,  0.774597, -0.447214,
        -0.447214,  0.774597,  0.447214 };
    
    
    int i;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    polarview();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    
    glBegin(GL_POLYGON);
    /*
    glNormal3f(0, 1, 0);
    glVertex3f(1, 0, 1);
    glVertex3f(1, 0, -1);
    glVertex3f(-1, 0, -1);
    glVertex3f(-1, 0, 1);
    */
    for( i = 0 ; i < 4; ++i ) {
        glNormal3fv( normal_data[i] );
        glVertex3fv( vertex_data[i] );
    }
    
    glEnd();
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    //drawNormal(0, 0, 0, 0, 1, 0);
    for( i = 0 ; i < 4; ++i )
        drawNormal( vertex_data[i], normal_data[i] );
    glPopMatrix();
    glDisable(GL_DEPTH_TEST);
    glutSwapBuffers();
    
}

void drawNormal(float x0, float y0, float z0, float x1, float y1, float z1) {
    glColor3f(1, 0, 0);
    glLineWidth(2);
    glPushMatrix();
    glTranslatef(x0, y0, z0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(x1, y1, z1);
    glEnd();
    glPopMatrix();
}

void drawNormal( float *v0, float *v1 )
{
    float x0, y0, z0;
    
    glColor3f( 1.0, 0.0, 0.0 );
	glLineWidth( 2.0 );
    x0= v0[0], y0= v0[1], z0= v0[2];
    glPushMatrix();
    glTranslatef( x0, y0, z0 );
    glBegin( GL_LINES );
    glVertex3f( 0.0, 0.0, 0.0 );
    glVertex3fv( v1 );
    glEnd();
    glPopMatrix();
}

void displayView(void) {
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    //gluLookAt(0.0, 1.0, dist, 0.0, 1.0, dist+1.0, 0.0, 1.0, 0.0);
    gluLookAt(0.0, 10.0, 10.0, 0.0, 0.0, 15.0, 0.0, 0.0, 1.0);
    
    glPushMatrix();
    glTranslatef(1.5, 2.0, 10.0);
    glRotatef(theta, 1.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glutWireTeapot(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.5, 2.0, 20.0);
    glRotatef(2.0*theta, 1.0, 0.0, 0.0);
    glutWireTorus(0.2, 1.0, 15, 30);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, 1.0, 30.0);
    glRotatef(3.0*theta, 0.2, -1.0, 0.0);
    glRotatef(-90, 1.0, 0.2, 0.0);
    glColor3f(1.0, 1.0, 0.0);
    glutWireSphere(1.0, 15, 15);
    glPopMatrix();
    
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for (i = -35; i < 36; i+=2) {
        glVertex3f((float)i, 0, -35.0);
        glVertex3f((float)i, 0, 35.0);
        glVertex3f(-50, 0, (float)i);
        glVertex3f(50, 0, (float)i);
    }
    glEnd();
    
    glPopMatrix();
    glutSwapBuffers();
    
    
}

void displayAnime(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    //glTranslatef(0.0, 0.0, -5.0);
    //gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    polarview();
    
    glTranslatef(0.0, 0.0, 2.0 * sin(PI * theta/180));
    glRotatef(theta, -1.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glRectf(-1.0, -1.0, 1.0, 1.0);
    
    glPopMatrix();
    glutSwapBuffers();
    
}

void idle(void) {
    
    if (bRotating) {
        dist = fmod(dist + 0.05, 32.0);
        theta = fmod(theta+3.0 + sin(2*PI*theta/360)*2, 360.0);
    }
    if( bRotating ) {
		spin = fmod( (spin + 1.0), 360.0 );
    }
    glutPostRedisplay();
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    glTranslatef(0.0, 0.0, -3.0);
    glTranslatef(0.2, 0.1, 0.2);
    glRotatef(30.0, 0.0, 1.0, 0.0);
    glScalef(1.0, 0.5, 0.0);
    
    // POLYGON
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.5, 0.5, 0.5);
    
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-0.5, 0.5, 0.5);
    
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.0);
    
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.75, 0.0, 0.5);
    
    glEnd();

    //line
    /*
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.75, 0.75, 0.0);
    glVertex3f(0.75, -0.75, 0.0);
    glEnd();
    
    glLineWidth(8.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-0.75, 0.75, 0.0);
    glVertex3f(-0.75, -0.75, 0.0);
    glEnd();
    */
    
    glPopMatrix();
    glFlush();
}

void displayCircle(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    
    float radius = 0.5;
    int split_num = 1000;
    for (int i = 0; i < split_num; i++) {
        glVertex3f(
                   radius * cos(2.0 * PI * (float)i/(float)split_num),
                   radius * sin(2.0 * PI * (float)i/(float)split_num),
                   0.0);
    }
    glEnd();
    glFlush();
}

void displaySphere() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_DEPTH_TEST);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -5.0);
    

    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(1.0, 20, 20);
    
    glRotatef(-60, 0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glRectf(-1.0, -1.5, 1.0, 1.5);
    
    glPopMatrix();
    glDisable(GL_DEPTH_TEST);
    glFlush();
}

void displayTeapot() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_DEPTH_TEST);
    glPushMatrix();

    glTranslatef(0.0, 0.0, -5.0);

    glColor3f(1.0, 1.0, 0.0);
    glutSolidTeapot(1.0);
 
    glTranslatef(0.5, 0.0, 0.5);
    glRotatef(-60, 0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glRectf(-1.0, -1.5, 1.0, 1.5);

    
    glPopMatrix();
    glDisable(GL_DEPTH_TEST);
    glFlush();
    
}

void myKbd(unsigned char key, int x, int y) {
    switch (key) {
        case 'R':
            resetview();
            glutPostRedisplay();
            break;
        case 's':
            bShading = 1 - bShading;
            break;
        case 'r':
            bRotating = 1 - bRotating;
            break;
        case 'w':
            bWired = 1 - bWired;
            break;
        case KEY_ESC:
            exit(0);
    }
}

void myMouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        xBegin = x;
        yBegin = y;
        mButton = button;
    }
}

void myMotion(int x, int y) {
    int xDisp, yDisp;
    
    xDisp = x - xBegin;
    yDisp = y - yBegin;
    switch (mButton) {
        case GLUT_LEFT_BUTTON:
            azimuth += (float)xDisp/5.0;
            elevation -= (float)yDisp/5.0;
            break;
        case GLUT_MIDDLE_BUTTON:
            twist = fmod(twist + xDisp/3.0, 360.0);
            break;
        case GLUT_RIGHT_BUTTON:
            distance -= (float)(xDisp + yDisp)/60.0;
            break;
    }
    xBegin = x;
    yBegin = y;
    glutPostRedisplay();
}

void myInit (char *progname) {
    int width = 500, height = 500;
    int disp_w = glutGet(GLUT_SCREEN_WIDTH)/2 - width/2;
    int disp_h = glutGet(GLUT_SCREEN_HEIGHT)/2 - height/2;
    
    glutInitWindowPosition(disp_w, disp_h);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(progname);
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutKeyboardFunc(myKbd);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);
    resetview();
    glShadeModel(GL_SMOOTH);
    //initLighting();
}

void myReshape(int width, int height) {
    float aspect = (float)width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, aspect, 1, 50);
    glMatrixMode(GL_MODELVIEW);
}

void polarview(void) {
    glTranslatef(0.0, 0.0, -distance);
    glRotatef(-twist, 0, 0, 1);
    glRotatef(-elevation, 1, 0, 0);
    glRotatef(-azimuth, 0, 1, 0);
}

void resetview(void) {
    distance = 15;
    twist = 0;
    elevation = 0;
    azimuth = 0;
}


// メイン関数
int main(int argc, char** argv)
{
    glutInit(&argc, argv); //GLUT, OpenGL環境を初期化
    myInit(argv[0]);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(displayRocket);
    glutIdleFunc(idle);
    glutMainLoop();
    
    return 0;
}