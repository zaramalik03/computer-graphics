//----------------------------------------------------------------------------
// Name ------- Zara Malik
// Course ----- CS323-01
// Project ---- Exam #1- Part II
// This is the second part of the first exam, creating a colorful 3D image of
// an octagonal bipyramid using OpenGL in C++ that can move with the trackball
// feature. 
//----------------------------------------------------------------------------

#ifdef _WIN32
    #include <GL/glut.h>
#elif __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#endif

#include <cmath>
#include "camera.h" // Eck's camera API.

// Define colors for each side
float colors[8][4] = {
    {0.5f, 1.0f, 0.8f, 0.85f},  // Aquamarine
    {0.6f, 0.4f, 0.8f, 0.85f},  // Amethyst
    {0.0f, 0.8f, 0.4f, 0.85f},  // Emerald
    {1.0f, 1.0f, 0.4f, 0.85f},  // Yellow
    {0.9f, 0.9f, 1.0f, 0.85f},  // White
    {1.0f, 0.7f, 0.8f, 0.85f},  // Rose Quartz
    {0.0f, 0.3f, 0.7f, 0.85f},  // Sapphire
    {1.0f, 0.55f, 0.2f, 0.85f}  // Topaz
};

// Define vertices for top and bottom pyramids
float topVertices[8][3] = {
    {0.0f, -1.0f, 0.0f}, {0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.0f},
    {0.0f, 1.0f, 0.0f}, {-0.5f, 0.5f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-0.5f, -0.5f, 0.0f}
};

float bottomVertices[8][3] = {
    {0.0f, 1.0f, 0.0f}, {-0.5f, 0.5f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-0.5f, -0.5f, 0.0f},
    {0.0f, -1.0f, 0.0f}, {0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.0f}
};

// Draw the bipyramid
void drawBipyramid() {
    // Draw the top pyramid
    float angle = 2.0f * M_PI / 8; 
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 8; i++) {
        glColor4fv(colors[i]);  // Set the color for the side
        glVertex3fv(topVertices[i]);  // First vertex of the triangle
        glVertex3f(0.0f, 0.0f, 1.0f);  // The apex of the top pyramid
        glVertex3fv(topVertices[(i + 1) % 8]);  // Next vertex, looping around
    }
    glEnd();

    // Draw the bottom pyramid
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 8; i++) {
        glColor4fv(colors[i]);  // Set the color for the side
        glVertex3fv(bottomVertices[i]);  // First vertex of the triangle
        glVertex3f(0.0f, 0.0f, -1.0f);  // The apex of the bottom pyramid
        glVertex3fv(bottomVertices[(i + 1) % 8]);  // Next vertex, looping around
    }
    glEnd();
}



//------------------------------------------------------------------------------------
// display() to render the octagonal bipyramid (8 triangles top and bottom)
//------------------------------------------------------------------------------------
void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   cameraSetLimits(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0); 
   cameraApply();  

   glRotatef(50.0f, 1.0f, 1.0f, 1.0f);

   drawBipyramid();
   glFlush();
}

//------------------------------------------------------------------------------------
// init()
// 
// The intializations pertain to using Eck's camera API with the trackball feature.
//------------------------------------------------------------------------------------
void init() {
    glutMouseFunc(trackballMouseFunction);   
    glutMotionFunc(trackballMotionFunction);  
    return;
}

//------------------------------------------------------------------------------------
// main()
//
// Main function. GLUT initalizations and the main event loop.
//------------------------------------------------------------------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Octagonal Bipyramid");
    glutDisplayFunc(display);
	init(); 
    glutMainLoop();
    return 0;
}
