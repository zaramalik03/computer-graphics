//-----------------------------------------------------------------------------
// Name ------- Zara Malik
// Course ----- CS3233-01
// Project ---- Awesome Sauce
// Due date --- November 1, 2024
// This program is a lighted 3D scene of a table with a big, unopened box of
// Tabasco Sauce and a solid teapot on it.
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

#include "camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//------------------------------------
// Draws the box of the Tabasco Sauce
//------------------------------------
void drawBox(){
    glEnable(GL_TEXTURE_2D);
    float box[8][3]{
        {-1.0f, -2.0f, 0.75f}, {-1.0f, 1.0f, 0.75f}, {-0.25f, 1.0f, 0.75f}, {-0.25f, -2.0f, 0.75f}, 
        {-1.0f, -2.0f, 0.0f}, {-1.0f, 1.0f, 0.0f}, {-0.25f, 1.0f, 0.0f}, {-0.25f, -2.0f, 0.0f},       
    };

    // Front face   
    glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2d(0.0f, 1.0f); 
        glVertex3fv(box[0]);
        glTexCoord2d(0.0f, 0.0f); 
        glVertex3fv(box[1]);  
        glTexCoord2d(0.1442f, 0.0f); 
        glVertex3fv(box[2]);  
        glTexCoord2d(0.1442f, 1.0f); 
        glVertex3fv(box[3]);  
	glEnd();

    // Back face 
    glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord2d(0.4333f, 1.0f); 
        glVertex3fv(box[4]);
        glTexCoord2d(0.4333f, 0.0f); 
        glVertex3fv(box[5]);  
        glTexCoord2d(0.2888f, 0.0f); 
        glVertex3fv(box[6]);  
        glTexCoord2d(0.2888f, 1.0f); 
        glVertex3fv(box[7]);  
	glEnd();

    // Left Side
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(-1.0f, 0.0f, 0.0f);    
        glTexCoord2d(0.2888f, 1.0f); 
        glVertex3fv(box[0]);
        glTexCoord2d(0.1445f, 1.0f);
        glVertex3fv(box[4]);
        glTexCoord2d(0.1445f, 0.0f);
        glVertex3fv(box[5]);
        glTexCoord2d(0.2888f, 0.0f);
        glVertex3fv(box[1]);  
    glEnd();

    // Right Side
     glBegin(GL_TRIANGLE_FAN);
        glNormal3f(1.0f, 0.0f, 0.0f);    
        glTexCoord2d(0.4336f, 1.0f); 
        glVertex3fv(box[3]);
        glTexCoord2d(0.5779f, 1.0f);
        glVertex3fv(box[7]);
        glTexCoord2d(0.5779f, 0.0f);
        glVertex3fv(box[6]);
        glTexCoord2d(0.4336f, 0.0f);
        glVertex3fv(box[2]);  
    glEnd();

    // Top face
    glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0.0f, 1.0f, 0.0f);     
		glTexCoord2d(0.5781f, 0.2889f);     
        glVertex3fv(box[1]);  
		glTexCoord2d(0.7224f, 0.2889f);  
        glVertex3fv(box[2]); 
		glTexCoord2d(0.7224f, 0.0f);
        glVertex3fv(box[6]);
		glTexCoord2d(0.5781f, 0.0f);   
        glVertex3fv(box[5]);
   glEnd();

    // Bottom face
    glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0.0f, -1.0f, 0.0f);     
		glTexCoord2d(0.5781f, 0.5776f);
        glVertex3fv(box[0]);  
		glTexCoord2d(0.7224f, 0.5776f);   
        glVertex3fv(box[3]); 
		glTexCoord2d(0.7224f, 0.2899f);
        glVertex3fv(box[7]);
		glTexCoord2d(0.5781f, 0.2899f);   
        glVertex3fv(box[4]);
   glEnd();


}

//-------------------------------------------------
// Draws each leg of the table
//-------------------------------------------------
void drawLeg(float x, float y, float z){
    float legVertices[8][3]{
        {x, y, z}, {x+0.5f, y, z}, {x+0.5f, y+2.0f, z}, {x, y+2.0f, z}, 
        {x, y, z-0.5f}, {x+0.5f, y, z-0.5f}, {x+0.5f, y+2.0f, z-0.5f}, {x, y+2.0f, z-0.5f},

    };
    //Front face
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3fv(legVertices[0]);
        glVertex3fv(legVertices[1]);
        glVertex3fv(legVertices[2]);
        glVertex3fv(legVertices[3]);
    glEnd();
    //Back face 
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3fv(legVertices[4]);
        glVertex3fv(legVertices[5]);
        glVertex3fv(legVertices[6]);
        glVertex3fv(legVertices[7]);
    glEnd();
    //Left face
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3fv(legVertices[4]);
        glVertex3fv(legVertices[0]);
        glVertex3fv(legVertices[3]);
        glVertex3fv(legVertices[7]);
    glEnd();
    //Right face
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3fv(legVertices[5]);
        glVertex3fv(legVertices[1]);
        glVertex3fv(legVertices[2]);
        glVertex3fv(legVertices[6]);
    glEnd();
}

//-----------------
// Table function
//-----------------
void drawTable(){
    //Table platform
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-2.5f, -2.0f, 3.0f);
        glVertex3f(-2.5f, -2.0f, -3.0f);
        glVertex3f(4.0f, -2.0f, -3.0f);
        glVertex3f(4.0f, -2.0f, 3.0f);
    glEnd();

    drawLeg(-2.4f, -4.0f, 3.0f);    //Front left leg
    drawLeg(-2.4f, -4.0f, -2.5f);   //Back left leg
    drawLeg(3.5f, -4.0f, 3.0f);     //Front right leg
    drawLeg(3.5f, -4.0f, -2.5f);    //Back right leg
}


//--------------------------------------------------------------------------
// display()
//--------------------------------------------------------------------------
void display() {
    glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f);
    glMatrixMode(GL_MODELVIEW);

    cameraSetLimits(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
	cameraApply();


    //Calls function to create box
    drawBox();
    glDisable(GL_TEXTURE_2D);       

    //Teapot color
    float teapot_color[] = { 1.0f, 0.25f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, teapot_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, teapot_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, teapot_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);
    //Creates teapot
    glPushMatrix();
        glTranslatef(2.0f, -1.6f, 0.0f);
        glutSolidTeapot(0.5);
	glPopMatrix();

    //Table color
    float table_color[] = { 0.5f, 0.35f, 0.25f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, table_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, table_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, table_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 80.0F);
    //Calls function to create table
    drawTable();

    glFlush();
}

//--------------------------------------------------------------------------
// init() - Various initializations
//--------------------------------------------------------------------------
void init(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);    
    glEnable(GL_NORMALIZE);   

    // Set light properties
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
    GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f }; 
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    GLuint textureID;
    //Load Tabasco Sauce Texture
    int imgWidth, imgHeight, bytesPerPixel;
    unsigned char* data = stbi_load("TabascoSauceTexture.jpg", &imgWidth, &imgHeight, &bytesPerPixel, 0);
    glGenTextures(1, &textureID);             
    glBindTexture(GL_TEXTURE_2D, textureID);   
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);
    return;
}

//--------------------------------------------------------------------------
// main
//--------------------------------------------------------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Tabasco Sauce");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
