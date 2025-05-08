//----------------------------------------------------------------------------
// Name ------- Zara Malik
// Course ----- CS323-01
// Project ---- Exam #2- Take That!
// Due -------- November 13, 2024
// This assignment as the second exam is a 3D image of a round dartboard that
// is texture mapped with Dr. Bryan Crawley's face on it, and a dart that is
// animated to target the dartboard. 
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
#include "camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float dartPos = 5.0f;   //Position of dart
float speed = 0.06f;    //Speed of animation  

//--------------------------------------------------------------------------------
// dartboard() - draws the dartboard with texture mapping for Dr. Crawley's face
//--------------------------------------------------------------------------------
void dartboard(){
    float radius = 2.0f;
    float angle = 2.0f * M_PI / 32;
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, 1.0f);
    for (int i = 0; i < 32; i++) {
        float currentAngle = i * angle;     
        float x = -2.0f + radius * cos(currentAngle);    
        float y = 1.2f + radius * sin(currentAngle);
        float point[3] = {x, y, 0.0f};
        float s = 0.5f + 0.5f * cos(currentAngle);  
        float t = 0.5f - 0.5f * sin(currentAngle);
        glTexCoord2d(s, t);
        glVertex3fv(point);
    }
    glEnd();

}


//----------------------------------------------------------------------------------------------------
// normalvector() - to compute the normal vector coordinates, cross product, and normalize the vector
//----------------------------------------------------------------------------------------------------
void normalvector(float x2Bottom, float x1Bottom, float y2Bottom, float y1Bottom, float x1Top, float y1Top, float x2Top, float y2Top){
    //Coordinates for v
    float vx = x2Bottom - x1Bottom;
    float vy = y2Bottom - y1Bottom;
    float vz = 0.4f;                //0.0f - (-0.4f);

    //Coordinates for w
    float wx = x1Top - x1Bottom;
    float wy = y1Top - y1Bottom;
    float wz = 0.4f;                //0.0f - (-0.4f)

    //Cross product for normal vector coordinates
    float nx = (vy*wz) - (vz*wy);
    float ny = (vz*wx) - (vx*wz);
    float nz = (vx*wy) - (vy*wx); 
    float normal[3] = {nx, ny, nz};

    //Normalize vector
    float length = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    if (length != 0.0f) {
        nx /= length;
        ny /= length;
        nz /= length;
    }
    glNormal3fv(normal);   
    glVertex3f(x1Bottom, y1Bottom, -0.4f);      // Bottom left
    glVertex3f(x2Bottom, y2Bottom, -0.4f);      // Bottom right
    glVertex3f(x2Top, y2Top, 0.0f);             // Top right
    glVertex3f(x1Top, y1Top, 0.0f);             // Top left
}

//--------------------------------------------------------------------------
// dartboardBody() - draws the side walls and back of the dartboard
//--------------------------------------------------------------------------
void dartboardBody(){
    glPushMatrix();
    float radius = 2.0f;
    float angle = 2.0f * M_PI / 32;
    //Using prism drawing to draw side walls
    for (int i = 0; i < 32; i++){
        glBegin(GL_TRIANGLE_FAN);  
            //Top and bottom coordinates of vertices
            float x1Bottom = -2.0f+ radius * cos(i * angle);
            float y1Bottom = 1.2f+ radius * sin(i * angle);
            float x1Top = x1Bottom;
            float y1Top = y1Bottom;

            float x2Bottom = -2.0f+ radius * cos((i+1)%32 * angle);
            float y2Bottom = 1.2f+ radius * sin((i+1)%32 * angle);
            float x2Top = x2Bottom;
            float y2Top = y2Bottom;

            //Call normal vector function
            normalvector(x2Bottom, x1Bottom, y2Bottom, y1Bottom, x1Top, y1Top, x2Top, y2Top);
        glEnd();
    }
    //Creating the back of the dartboard
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, -1.0f);  
    for (int i = 0; i < 32; i++) {
        float currentAngle = i * angle;
        float x = -2.0f + radius * cos(currentAngle);
        float y = 1.2f + radius * sin(currentAngle);
        glVertex3f(x, y, -0.4f);
    }
    glEnd();
    glPopMatrix();
}

//--------------------------------------------------------------------------
// drawHalfCircle() - function to draw half circle for dart decoration
//--------------------------------------------------------------------------
void drawHalfCircle(float xArc, float yArc, float zArc){
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 32; i++){
        float angle = (2.0f * M_PI) * i / 64;  
        float x = xArc + 0.35f * cos(angle);    
        float y = yArc + 0.35f * sin(angle);  
        glVertex3f(x, y, zArc);
    }
    glEnd();
}
//--------------------------------------------------------------------------------------------
// dart() - main function for the dart, a thin cylinder body with half circle fins 
//--------------------------------------------------------------------------------------------
void dart(){
    const int faces = 50;
    float point[faces*2][3];
    glPushMatrix();
    //Creates a list of points for cylinder
    for (int i = 0; i < faces; i++) {
        float degrees, radians;
        degrees = i * 360.0/faces;
        radians = degrees * M_PI / 180;
        point[i][0] = point[i+faces][0] = cos(radians); 
        point[i][1] = point[i+faces][1] = sin(radians); 
        point[i][2] = 1;        
        point[i+faces][2] = -1; 
    }

    //Enable animation with dartPos for translation.
    glTranslatef(-2.0f, 1.2f, dartPos);

    //Scale & rotate cylinder to look like a small dart pointing horizontally.
    glScalef(0.085f, 0.085f, 1.2f);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);

    //Draw near end of the cylinder.
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
        glNormal3f(0.0f, 0.0f, 1.0f);
        for (int i = 0; i < faces; i++) {
            glVertex3fv(point[i%faces]);
        }
    glEnd();
    
    //Draw far end of the cylinder.
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
        glNormal3f(0.0f, 0.0f, -1.0f);
        for (int i = faces-1; i>=0; i--) {
            glVertex3fv(point[i+faces]);
        }
    glEnd();
    
    //Draw sides of the cylinder
    glBegin(GL_TRIANGLE_STRIP);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
        for (int i = 0; i <= faces; i++) {
            glVertex3fv(point[i%faces]);
            glVertex3fv(point[i%faces + faces]);   
        }
    glEnd();
    glPopMatrix();

    //Creates top half circle for the dart
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(-dartPos+5.0f, 0.0f, 0.0f);
    drawHalfCircle(-6.0f, 1.2f, -2.0f);        //Calls function
    glPopMatrix();

    //Creates bottom half circle for the dart
    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(dartPos-5.0f, 0.0f, 0.0f);
    drawHalfCircle(6.0f, -1.2f, -2.0f);        //Calls function
    glPopMatrix();

    //Creates left half circle for the dart
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(-dartPos+5.0f, 0.0f, 0.0f);
    drawHalfCircle(-6.0f, 2.0f, 1.2f);         //Calls function
    glPopMatrix();

    //Creates right half circle for the dart
    glPushMatrix();
    glRotatef(270.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(-dartPos+5.0f, 0.0f, 0.0f);
    drawHalfCircle(-6.0f, -2.0f, -1.2f);       //Calls function
    glPopMatrix();
}


//--------------------------------------------------------------------------
// display() - sets up camera and all function calls/components
//--------------------------------------------------------------------------
void display() {
    glClearColor(0.8f, 0.7f, 0.5f, 1.0f);   //Sand background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    cameraSetLimits(-6.0, 6.0, -6.0, 6.0, -6.0, 6.0);
	cameraApply();

    //Draws the body and back of dartboard
    float dartboard_color2[] = { 0.32f, 0.25f, 0.2f, 0.0f };  //Color is brown
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dartboard_color2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, dartboard_color2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, dartboard_color2);
    glMateriali(GL_FRONT, GL_SHININESS, 100.0F);
    dartboardBody();

    //Draws dartboard
    float dartboard_color[] = { 1.0f, 1.0f, 1.0f, 0.0f }; 
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dartboard_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, dartboard_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, dartboard_color);
    glMateriali(GL_FRONT, GL_SHININESS, 100.0F);
    glEnable(GL_TEXTURE_2D);
    dartboard();
    glDisable(GL_TEXTURE_2D);

    //Draws dart
    float dart_color[] = { 1.0f, 0.0f, 0.0f, 0.0f };  //Color is red
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dart_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, dart_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, dart_color);
    glMateriali(GL_FRONT, GL_SHININESS, 100.0F);
    dart();

    //Draws pointy cone tip of the dart
    float tip_color[] = { 1.0f, 0.91f, 0.0f, 0.0f };  //Color is gold
    glMaterialfv(GL_FRONT, GL_DIFFUSE, tip_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, tip_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, tip_color);
    glMateriali(GL_FRONT, GL_SHININESS, 100.0F);

    glPushMatrix();
    //Translate for the tip to move along the entire dart
    glTranslatef(-2.0f, 1.2f, dartPos-1.2f);    
    //Scale and rotate to make it small as the dart
    glScalef(0.45f, 0.45f, 1.5f);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glutSolidCone(0.18f, 0.49f, 20.0f, 20.0f);   //Cone shape
    glPopMatrix();

    glutSwapBuffers(); 
}

//--------------------------------------------------------------------------
// init() - various initializations
//--------------------------------------------------------------------------
void init() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    // Load Image texture of Dr. Crawley
    GLuint textureID;
    int imgWidth, imgHeight, bytesPerPixel;
    unsigned char* data = stbi_load("MyFace.jpg", &imgWidth, &imgHeight, &bytesPerPixel, STBI_rgb);
    glGenTextures(1, &textureID);             
    glBindTexture(GL_TEXTURE_2D, textureID);   
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glutMouseFunc(trackballMouseFunction);   
    glutMotionFunc(trackballMotionFunction);  
    return;
}

//--------------------------------------------------------------------------
// timer() - to post redisplay events and animations
//--------------------------------------------------------------------------
void timer(int unused) {
    dartPos -= speed;   
    if (dartPos <= 1.85f) {
        dartPos = 5.0f;     //Sets back to initial position
    }
    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

//--------------------------------------------------------------------------
// main() - main function to run the program
//--------------------------------------------------------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(950, 950);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Take That!");
    glutDisplayFunc(display);
	init(); 
    timer(0);
    glutMainLoop();
    return 0;
}
