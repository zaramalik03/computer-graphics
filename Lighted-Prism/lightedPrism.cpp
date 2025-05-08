//--------------------------------------------------------------------------------
// Name ------- Zara Malik
// Course ----- CS3233-01
// Project ---- Lighted Prism
// This project draws an n-gonal prism in 3D that has size rectangle sides and
// two n-gon ends. This includes a default light source and the trackball feature.
//--------------------------------------------------------------------------------

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
#include "camera.h" // Eck's camera API.
#include <cmath>
using namespace std;

int n; //global variable n


//----------------------------------------------------
// Loop through n sides to draw the bottom-side n-gon 
//----------------------------------------------------
void drawBottomPolygon(int n){
    float radius = 1.0f;
    float angle = 2.0f * M_PI / n;           //Angle between each vertex in radians
    glBegin(GL_TRIANGLE_FAN);
    glNormal3i(0, 0, -1);
    for (int i = 0; i < n; i++){
        float currentAngle = i * angle;      //Current point angle for each iteration
        float x = radius * cos(currentAngle);
        float y = radius * sin(currentAngle);

        float point[3] = {x, y, 0.0f};
        glVertex3fv(point);
    }
    glEnd();
}

//--------------------------------------------------
// Loop through n sides to draw the top-side n-gon 
//--------------------------------------------------
void drawTopPolygon(int n){
    float radius = 1.0f;
    float angle = 2.0f * M_PI / n;           //Angle between each vertex in radians
    glBegin(GL_TRIANGLE_FAN);
    glNormal3i(0, 0, 1);
    for (int i = 0; i < n; i++){
        float currentAngle = i * angle;      //Current point angle for each iteration
        float x = radius * cos(currentAngle);    
        float y = radius * sin(currentAngle);

        float point[3] = {x, y, 2.0f};
        glVertex3fv(point);
    }
    glEnd();
}


//--------------------------------------------------------------------------------------
// Create rectangles for each side of the n-gon prism to match the top and bottom sides
//--------------------------------------------------------------------------------------
void drawPrism(int n){
    if (n < 3) return;
    float radius = 1.0f;
    float angle = 2.0f * M_PI / n;

    //Calls this function to draw the top side of n-gon
    drawTopPolygon(n);

    for (int i = 0; i < n; i++){
        glBegin(GL_TRIANGLE_FAN);  
            //Top and bottom coordinates of vertices
            float x1Bottom = radius * cos(i * angle);
            float y1Bottom = radius * sin(i * angle);
            float x1Top = x1Bottom;
            float y1Top = y1Bottom;

            float x2Bottom = radius * cos((i+1)%n * angle);
            float y2Bottom = radius * sin((i+1)%n * angle);
            float x2Top = x2Bottom;
            float y2Top = y2Bottom;

            //Vertex Positions
            float p0 [3] = {x1Bottom, y1Bottom, 0.0f};     //Bottom origin, P[0]
            float p1 [3] = {x2Top, y2Top, 0.0f};           //P[1]
            float p2 [3] = {x2Bottom, y2Bottom, 2.0f};     //P[2]

            //Coordinates for v
            float vx = p1[0] - p0[0];
            float vy = p1[1] - p0[1];
            float vz = 0.0f;

            //Coordinates for w
            float wx = p2[0] - p0[0];
            float wy = p2[1] - p0[1];
            float wz = 2.0f;

            //Cross product for normal vector coordinates (n = v * w)
            float nx = (vy*wz) - (vz*wy);
            float ny = (vz*wx) - (vx*wz);
            float nz = (vx*wy) - (vy*wx);
            float normal [3] = {nx, ny, nz};

            //Normal vector result
            glNormal3fv(normal);   
            glVertex3f(x1Bottom, y1Bottom, 0.0f);      // Bottom left
            glVertex3f(x2Bottom, y2Bottom, 0.0f);      // Bottom right
            glVertex3f(x2Top, y2Top, 2.0f);            // Top right
            glVertex3f(x1Top, y1Top, 2.0f);            // Top left
            
        glEnd();
    }

    //Calls this function to draw the bottom side of n-gon
    drawBottomPolygon(n);
}

//--------------------------------------------------------------------------
// display()
//--------------------------------------------------------------------------
void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    cameraSetLimits(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);
	cameraApply();

    //Sets the color for all vertices of the prism
    float prism_color[] = { 0.0f, 0.37f, 0.73f, 0.0f };  
    glMaterialfv(GL_FRONT, GL_DIFFUSE, prism_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, prism_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, prism_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0F);
    glRotatef(50.0f, 1.0f, 1.0f, 1.0f);

    //Calls this function to draw the n-gonal prism
    drawPrism(n);

    glFlush();
}

//--------------------------------------------------------------------------
// init()
//--------------------------------------------------------------------------
void init() {
    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0);     
    glEnable(GL_NORMALIZE);  
    glutMouseFunc(trackballMouseFunction);   
    glutMotionFunc(trackballMotionFunction);  
    return;
}


int main(int argc, char** argv) {
    std::cout << "Enter the number of vertices (n) ----- ";
    std::cin >> n;
    if (n < 3) {
        std::cout << "n must be greater than 2." << std::endl;
        return -1;
    }
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(600, 300);
    glutCreateWindow("Lighted Prism");

    glutDisplayFunc(display);
    init();        
    glutMainLoop();
    return 0;
}
