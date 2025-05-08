//--------------------------------------------------------------------------
// Name-------Zara Malik
// Course-----CS3233-01
// Project----Draw Your House
// Due--------September 11, 2024
// This is a C++ program that uses OpenGL to draw a 2D picture of my house. 
// This includes 2 windows, a purple door, a roof, a sun, and a tree.
//--------------------------------------------------------------------------

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

//---------------------------------------------------------------------------
// The function display() draws all the components of the house.
//---------------------------------------------------------------------------

void display() {
    glClearColor(0.0f, 0.87f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); 

    //Enabling blending makes it possible to use the alpha component of the
    //color to control opacity.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //These functions set the world coordinates in the viewport.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0f, 2.0f, 2.0f, -2.0f); //Arguments: left, right, bottom, top

    //Create square base for house
    glBegin(GL_TRIANGLE_STRIP); 
        glColor3f(0.8f, 0.7f, 0.5f);  //Sand
        glVertex2f(-0.8f, 0.0f);
        glVertex2f(0.8f, 0.0f);
        glVertex2f(-0.8f, 1.2f);
        glVertex2f(0.8f, 1.2f);
    glEnd();

    //Create door
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.5f, 0.4f, 0.7f);  //Purple
        glVertex2f(-0.15f, 0.65f);
        glVertex2f(0.15f, 0.65f);
        glVertex2f(-0.15f, 1.2f);
        glVertex2f(0.15f, 1.2f);  
    glEnd();     

    //Create edge of door design
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.7f, 0.4f, 0.9f);  //Dark Purple
        glVertex2f(-0.075f, 0.65f);
        glVertex2f(0.075f, 0.65f);
        glVertex2f(-0.075f, 1.2f);
        glVertex2f(0.075f, 1.2f);  
    glEnd();    

    //Create first window
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1.0f, 1.0f, 1.0f);   //Window # 1
        glVertex2f(-0.25f, 0.4f);   
        glVertex2f(-0.25f, 0.1f);
        glVertex2f(-0.55f, 0.4f);
        glVertex2f(-0.55f, 0.1f);
    glEnd(); 

    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);   //Vertical Window Line # 1
        glVertex2f(-0.4f, 0.1f);
        glVertex2f(-0.4f, 0.4f);
    glEnd(); 

    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);   //Horizontal Window Line # 1
        glVertex2f(-0.25f, 0.25f);
        glVertex2f(-0.55f, 0.25f);
    glEnd(); 


    //Create second window
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1.0f, 1.0f, 1.0f);   //Window # 2
        glVertex2f(0.25f, 0.4f);
        glVertex2f(0.25f, 0.1f);
        glVertex2f(0.55f, 0.4f);
        glVertex2f(0.55f, 0.1f);  
    glEnd();

    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);   //Vertical Window Line # 2
        glVertex2f(0.4f, 0.1f);
        glVertex2f(0.4f, 0.4f);
    glEnd(); 

    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);   //Horizontal Window Line # 2
        glVertex2f(0.25f, 0.25f);
        glVertex2f(0.55f, 0.25f);
    glEnd(); 

    //Create ground
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.0f, 0.75f, 0.0f);  //Green
        glVertex2f(3.0f, 1.2f);
        glVertex2f(-3.0f, 1.2f);
        glVertex2f(3.0f, 4.0f);
        glVertex2f(-3.0f, 4.0f);  
    glEnd();  

    //Create roof
    glBegin(GL_TRIANGLES);           
       glColor3f(0.3f, 0.2f, 0.2f);   //Dark Brown
       glVertex2f(-0.8f, 0.0f);              
       glVertex2f(0.8f, 0.0f);      
       glVertex2f(0.0f, -0.8f);
    glEnd();

    //Create tree (3 dark green triangles)
    glBegin(GL_TRIANGLES); 
        glColor3f(0.0f, 0.4f, 0.0f);  //Triangle #1
        glVertex2f(0.7f, 0.2f);
        glVertex2f(0.9f, -0.2f);
        glVertex2f(1.1f, 0.2f);
        glColor3f(0.0f, 0.4f, 0.0f);  //Triangle #2
        glVertex2f(0.7f, 0.4f);
        glVertex2f(0.9f, 0.0f);
        glVertex2f(1.1f, 0.4f);
        glColor3f(0.0f, 0.4f, 0.0f);  //Triangle #3
        glVertex2f(0.7f, 0.6f);
        glVertex2f(0.9f, 0.2f);
        glVertex2f(1.1f, 0.6f);
    glEnd();

    //Create tree trunk
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.36f, 0.25f, 0.2f);  //Brown
        glVertex2f(0.8f, 1.2f);
        glVertex2f(1.0f, 1.2f);
        glVertex2f(0.8f, 0.6f);
        glVertex2f(1.0f, 0.6f);
    glEnd();

    //Create sun
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.0f);      //Yellow
    for (int i = 0; i < 64; i++) {
        float angle = 6.2832 * i / 64;         //6.2832 is 2π
        float x = 1.2f + 0.2f * cos(angle);    //center of x is 1.2 
        float y = -1.4f + 0.2f * sin(angle);   //center of y is 1.4
        glVertex2f(x, y);
    }
    glEnd();

    //Create sun ray
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(1.0f, 1.0f, 1.0f, 0.3f);        //White; a bit transparent
    for (int i = 0; i < 64; i++) {
        float angle = 6.2832 * i / 64;         
        float x = 1.2f + 0.4f * cos(angle);   //Radius is a bit larger to make ray visible
        float y = -1.4f + 0.4f * sin(angle);   
        glVertex2f(x, y);
    }
    glEnd();

    glFlush();  // Render now
}

//---------------------------------------------------------------------------
// This is the main function to run the program.
//---------------------------------------------------------------------------

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(720, 720);
    glutInitWindowPosition(800, 300);
    glutCreateWindow("Red/Blue/Green Squares");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
