//-----------------------------------------------------------------------------
// Name ------- Zara Malik
// Course ----- CS3233-01
// Project ---- Lighted Scene
// Due date --- October 23, 2024
// This program is an architectural city-like scene that includes several 
// buildings and a road. Some have open doors that show a plant inside. Also, 
// there is a very special surprise in this scene. 
//-----------------------------------------------------------------------------

#ifdef _WIN32
    #include <GL/glut.h>
#elif __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#endif

#include <iostream>
using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cmath>
#include "camera.h"


//--------------------------------------------------
// Creates the right and left sides of the building 
//--------------------------------------------------
void drawRightLeft(float normal, float width, float height, float front, float back){
    glBegin(GL_TRIANGLE_FAN);
        glNormal3i(normal, 0, 0);      
        glVertex3f(width, -2.0f, front);
        glVertex3f(width, -2.0f, back);  
        glVertex3f(width, height, back);  
        glVertex3f(width, height, front);  
    glEnd();
}

//--------------------------------------------------
// Creates the front and back sides of the building 
//--------------------------------------------------
void drawFrontBack(float normal, float width, float height, float z){
    glBegin(GL_TRIANGLE_FAN);
		glNormal3i(0, 0, normal); 
        glVertex3f(0.0f, -2.0f, z);
        glVertex3f(0.0f, height, z);  
        glVertex3f(width, height, z);  
        glVertex3f(width, -2.0f, z);  
	glEnd();
}

//------------------------------------------------
// Creates the top and bottom of the building 
//------------------------------------------------
void drawTopBottom(float normal, float width, float height, float front, float back){
    glBegin(GL_TRIANGLE_FAN);
		glNormal3i(0, normal, 0);     
        glVertex3f(0.0f, height, front);
        glVertex3f(width, height, front);
        glVertex3f(width, height, back);
        glVertex3f(0.0f, height, back);
   glEnd();
}

//--------------------------------------------------
// Creates all faces of the building
//--------------------------------------------------
void building(float xorigin, float width, float height, float front, float back) {
    //The color of the building
    glPushMatrix();
    glTranslatef(xorigin, 0.0f, height / 2);

    drawFrontBack(1.0f, width, height, front);         // Front face
    drawFrontBack(-1.0f, width, height, back);         // Back face
    drawRightLeft(-1.0f, 0.0f, height, front, back);   // Left Side
    drawRightLeft(1.0f, width, height, front, back);   // Right Side
    drawTopBottom(1.0f, width, height, front, back);   // Top face
    drawTopBottom(-1.0f, width, -2.0f, front, back);   // Bottom face

    glPopMatrix();
}

//-----------------------------------------------------------------
// Creates all faces of the building including a gap for the door
//-----------------------------------------------------------------
void buildingwithdoor(float xorigin, float width, float height, float front, float back){
    glPushMatrix();
    glTranslatef(xorigin, 0.0f, height / 2);

    //Front face with opening for door in the middle
    glBegin(GL_TRIANGLE_FAN);
		glNormal3i(0, 0, 1); 
        glVertex3f(0.0f, -2.0f, front);
        glVertex3f(0.0f, height, front);  
        glVertex3f(width/3, height, front);  
        glVertex3f(width/3, -2.0f, front);  
	glEnd();
    glBegin(GL_TRIANGLE_FAN);
		glNormal3i(0, 0, 1); 
        glVertex3f(2*width/3, -2.0f, front);
        glVertex3f(2*width/3, height, front);  
        glVertex3f(width, height, front);  
        glVertex3f(width, -2.0f, front);  
	glEnd();
    glBegin(GL_TRIANGLE_FAN);
		glNormal3i(0, 0, 1); 
        glVertex3f(0.0f, (height/2)-2, front);
        glVertex3f(0.0f, height, front);  
        glVertex3f(width, height, front);  
        glVertex3f(width, (height/2)-2, front);  
	glEnd();

    //Draws protruding door
    glBegin(GL_TRIANGLE_FAN);
        glNormal3i(0, 0, 1); 
        glVertex3f(width/3, -2.0f, front);
        glVertex3f(width/3, -2.0f, front+0.5f);
        glVertex3f(width/3, (height/2)-2, front+0.5f);
        glVertex3f(width/3, (height/2)-2, front);
    glEnd();

    drawFrontBack(-1.0f, width, height, back);         // Back face
    drawRightLeft(-1.0f, 0.0f, height, front, back);   // Left Side
    drawRightLeft(1.0f, width, height, front, back);   // Right Side
    drawTopBottom(1.0f, width, height, front, back);   // Top face
    drawTopBottom(-1.0f, width, -2.0f, front, back);   // Bottom face

    glPopMatrix();
}

//--------------------------
// Creates the road layout
//--------------------------
void road(float width, float length){
    glBegin(GL_TRIANGLE_FAN);
        glNormal3i(0, 1, 0);
        glVertex3f(-width/2, -2.0f, -length/2);
        glVertex3f(width/2, -2.0f, -length/2);
        glVertex3f(width/2, -2.0f, length/2);
        glVertex3f(-width/2, -2.0f, length/2);
    glEnd();
    
}

//--------------------------
// Creates the plant shapes
//--------------------------
void plant(float x, float y, float z){
    //Draws stem of the plant
    glPushMatrix();
    glTranslatef(x, y+2.0f, z); 
    glScalef(0.35f, 0.5f, 0.1f);
    glutSolidCube(0.25f); 
    glPopMatrix();

    //Draws the plant
    glPushMatrix();
    glTranslatef(x, y + 2.0f, z);
    glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.25f, 0.5f, 20.0f, 20.0f); 
    glPopMatrix();
}

//-----------------------
// Creates the sun shape
//-----------------------
void sun(float x, float y, float z){
    glPushMatrix();
    glTranslatef(x, y, z); 
    glutSolidSphere(0.5f, 20.0f, 20.0f); 
    glPopMatrix();
}

//------------------------------
// Creates the special surprise
//------------------------------
void surprise(float x, float y, float z, float radius){
    glLineWidth(6.0f);         // Makes the line arch bigger
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 32; i++){
        float angle = (2.0f * M_PI) * i / 64;  
        float xArc = x + radius * cos(angle);    
        float yArc = y + radius * sin(angle);  
        glVertex3f(xArc, yArc, z);
    }
    glEnd();
}

//--------------------------------------------------------------------------
// display()
//--------------------------------------------------------------------------
void display() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f);
    glMatrixMode(GL_MODELVIEW);

    cameraSetLimits(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
	cameraApply();

    //The color of the building
    float cube_color[] = { 0.5f, 0.4f, 0.3f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);

    //Creates buildings giving xorigin, width, height, front and back size, and whether is has a door opening or not
    building(-3.0f, 1.0f, 2.0f, 0.0f, -1.0f);
    buildingwithdoor(-1.8f, 1.5f, 2.33f, -2.5f, -3.5f);
    building(0.0f, 1.0f, 1.0f, 1.0f, 0.0f);
    buildingwithdoor(2.0f, 1.0f, 3.0f, 1.0f, -1.0f);
    building(1.5f, 1.0f, 4.0f, -3.5f, -4.5f);

    //Plant color is green
    float plant_color[] = { 0.0f, 0.85f, 0.1f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, plant_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, plant_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, plant_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);
    //Creates the plant inside the buildings with door openings given (x, y, z) coordinates
    plant(-1.0f, -3.85f, -2.0f);
    plant(2.5f, -3.85f, 1.15f);

    //Creates the road
    float road_color[] = { 0.33f, 0.33f, 0.33f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, road_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, road_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, road_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);
    //Given width and length of the road
    road(6.75f, 14.0f);

    //Creates the sun
    float sun_color[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sun_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 150.0F);
    //Given (x, y, z) coordinates
    sun(-3.0f, 4.0f, -2.0f);

    float colors[7][3] = {
        {1.0f, 0.0f, 0.0f}, // Red
        {1.0f, 0.5f, 0.0f}, // Orange
        {1.0f, 1.0f, 0.0f}, // Yellow
        {0.0f, 1.0f, 0.0f}, // Green
        {0.0f, 0.0f, 1.0f}, // Blue
        {0.5f, 0.0f, 0.5f}, // Indigo
        {0.5f, 0.0f, 1.0f}  // Violet
    };
    float arcWidth = 0.2f;
    //Creates archs for each rainbow color from the float list
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colors[0]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[0]);
    glMaterialf(GL_FRONT, GL_SHININESS, 180.0F);
    surprise(1.2f, -2.0f, -4.0f, 1.0f+6*arcWidth);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[1]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colors[1]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[1]);
    glMaterialf(GL_FRONT, GL_SHININESS, 180.0F);
    surprise(1.2f, -2.0f, -3.9f, 1.0f+5*arcWidth);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[2]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colors[2]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[2]);
    glMaterialf(GL_FRONT, GL_SHININESS, 180.0F);
    surprise(1.2f, -2.0f, -3.8f, 1.0f+4*arcWidth);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[3]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colors[3]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[3]);
    glMaterialf(GL_FRONT, GL_SHININESS, 180.0F);
    surprise(1.2f, -2.0f, -3.7f, 1.0f+3*arcWidth);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[4]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colors[4]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[4]);
    glMaterialf(GL_FRONT, GL_SHININESS, 180.0F);
    surprise(1.2f, -2.0f, -3.6f, 1.0f+2*arcWidth);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[5]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colors[5]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[5]);
    glMaterialf(GL_FRONT, GL_SHININESS, 180.0F);
    surprise(1.2f, -2.0f, -3.5f, 1.0f+1*arcWidth);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[6]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colors[6]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[6]);
    glMaterialf(GL_FRONT, GL_SHININESS, 180.0F);
    surprise(1.2f, -2.0f, -3.4f, 1.0f);

    glFlush();
}

//--------------------------------
// init()
//--------------------------------
void init(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_pos[] = { 5.0f, 10.0f, 5.0f, 1.0f };    // Light position other than default location
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    // Set light properties
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // White diffuse light
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // White specular highlights
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };  // Soft ambient light
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    // Normalize the normals
    glEnable(GL_NORMALIZE);

    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);

    return;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Lighted Scene");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
