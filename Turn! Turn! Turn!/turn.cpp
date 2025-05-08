//------------------------------------------------------------------------------
// Name ------- Zara Malik
// Course ----- CS3233-01
// Project ---- Turn! Turn! Turn!
// Due -------- November 22, 2024
// This project uses the indices of vertices, textures, normals, and faces to
// draw an object read from any OBJ file prompted by the user. The chosen object
// turns around the y-axis.
//------------------------------------------------------------------------------

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
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


//Initialize the vectors
std::vector<std::vector<float>> vertices;  
std::vector<std::vector<float>> textures;
std::vector<std::vector<float>> normals;
std::vector<std::vector<std::vector<float>>> faces;
int floatCount = 0;   
float rotationAngle = 0.0f;      

double min = -10.0, max = 10.0;   //Min and max values of cameraSetLimits and glOrtho
bool scale = false;               //Determines if a specific object needs to be scaled down

//-------------------------------------------------------------------------------
// loadOBJ() - reads the v, vt, vn, and f indices from the obj file
//-------------------------------------------------------------------------------
void loadOBJ(std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    std::string line;
    while(getline(file,line)) {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;
        if (prefix == "v"){
            std::vector<float> v;
            float x, y, z;
            ss >> x >> y >> z;
            //Condition if vertices exceed limits of the screen
            if (x < min || x > max || y < min || y > max || z < min || z > max){
                scale = true;
            }
            v.push_back(x); v.push_back(y); v.push_back(z);  //Add each coordinate to this set
            vertices.push_back(v);      //Add that set of coordinates to the vertices vector
        } else if (prefix == "vt"){
            std::vector<float> t;
            float u, v;
            ss >> u >> v;
            t.push_back(u); t.push_back(v);  //Add each coordinate to this set
            textures.push_back(t);        //Add that set of coordinates to the textures vector
        } else if (prefix == "vn"){
            std::vector<float> n;
            float x, y, z;
            ss >> x >> y >> z;
            //Condition if vertices exceed limits of the screen
            if (x < min || x > max || y < min || y > max || z < min || z > max){
                scale = true;
            }
            n.push_back(x); n.push_back(y); n.push_back(z);   //Add each coordinate to this set
            normals.push_back(n);        //Add that set of coordinates to the normals vector
        } else if(prefix == "f"){ 
            std::vector<std::vector<float>> f;
            floatCount++;    //Counts the total number of faces in the file
            while(ss >> prefix){
                std::stringstream faceStream(prefix);
                std::string faceStr;
                std::vector<float> faceIndices;
                while (std::getline(faceStream, faceStr, '/')) {
                    if (!faceStr.empty()) {
                        faceIndices.push_back(std::stof(faceStr));  //Adds the v/vt/vn that is read
                    } else {
                        faceIndices.push_back(0); 
                    }
                }
                f.push_back(faceIndices);   //Adds each v/vt/vn in the current face
            }
            faces.push_back(f);  //Adds each face read into the total set of faces
        }
    }
    file.close();
}

//-----------------------------------------------------------------------------------------------------------
// drawObject() - iterates over the face vectors to access the vertex, texture, and normal index positions
// and create the image of the object
//-----------------------------------------------------------------------------------------------------------
void drawObject() {
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    //Condition if we have to scale the object or not
    if (scale == true){
        glScalef(0.25f, 0.25f, 0.25f);
    }
    //Iterate through total number of faces
    for (int i = 0; i < floatCount; i++){
        glBegin(GL_TRIANGLE_FAN);
            float nIndex = faces[i][0][2]-1;
            glNormal3f(normals[nIndex][0], normals[nIndex][1], normals[nIndex][2]);
            //Iterate through each vertex in the current face
            for (int j = 0; j < faces[i].size(); j++){
                float vIndex = faces[i][j][0]-1;   
                float tIndex = faces[i][j][1]-1;
                glTexCoord2d(textures[tIndex][0], textures[tIndex][1]);
                glVertex3f(vertices[vIndex][0], vertices[vIndex][1], vertices[vIndex][2]);
            }
        glEnd();
    }
}

//--------------------------------------------------------------------------
// display() - sets up camera and all function calls/components
//--------------------------------------------------------------------------
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(min, max, min, max, min, max);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);

    cameraSetLimits(min, max, min, max, min, max);
	cameraApply();

    float color[] = { 1.0f, 1.0f, 1.0f }; 
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color);
    glMateriali(GL_FRONT, GL_SHININESS, 100.0F);
    glPushMatrix();
    drawObject();   //Calls function to draw object
    glPopMatrix();
    glutSwapBuffers(); 
}

//--------------------------------------------------------------------------
// timer() - to post redisplay events and rotaion
//--------------------------------------------------------------------------
void timer(int unused){
    rotationAngle += 1.0f;
    if (rotationAngle >= 360.0f) {
        rotationAngle -= 360.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(17, timer, 0);
}

//--------------------------------------------------------------------------
// init() - various initializations
//--------------------------------------------------------------------------
void init() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set light properties
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
    GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f }; 
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glutMouseFunc(trackballMouseFunction);   
    glutMotionFunc(trackballMotionFunction);  
    return;
}
//--------------------------------------------------------------------------
// main() - main function to run the program
//--------------------------------------------------------------------------
int main(int argc, char** argv) {
    std::string filename;
    std::cout << "Enter obj file name: ";  
    std::cin >> filename;
    loadOBJ(filename);                   

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1180, 900);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Turn! Turn! Turn!");
    init(); 
    timer(0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
