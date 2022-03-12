#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include "tinyxml.h"
#endif
#include "engine.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

float cameraAngle = 0;
float scale = 1;
fstream openedFile;

class CameraConfig{
public:
    float cameraX;
    float cameraY;
    float cameraZ;
    float lookAtX;
    float lookAtY;
    float lookAtZ;
    float upX;
    float upY;
    float upZ;
    float fov;
    float near;
    float far;
};

map<int,string> filesToDraw;

CameraConfig cameraConfig;

bool drawModeFill = false;

void readXMLConfigurationFile(char* filename) {
    TiXmlDocument document;
    bool fileOpened = document.LoadFile(filename);
    if(fileOpened){
        TiXmlElement* root = document.RootElement();
        int i = 0;
        for (TiXmlElement* e = root->FirstChildElement("camera")->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
        {
            if (e)
            {
                const char *a1 = e->Attribute("x");
                const char *a2 = e->Attribute("y");
                const char *a3 = e->Attribute("z");
                const char *a4 = e->Attribute("fov");
                const char *a5 = e->Attribute("near");
                const char *a6 = e->Attribute("far");

                //DEBUG
                if (a1 && i == 0) {
                    cout << "Position x: " << a1 << "\n";
                    cameraConfig.cameraX = atof(a1);
                }
                if (a2 && i == 0) {
                    cout << "Position y: " << a2 << "\n";
                    cameraConfig.cameraY = atof(a2);

                }
                if (a3 && i == 0) {
                    cout << "Position z: " << a3 << "\n";
                    cameraConfig.cameraZ = atof(a3);
                }
                if (a1 && i == 1) {
                    cout << "LookAt x: " << a1 << "\n";
                    cameraConfig.lookAtX = atof(a1);
                }
                if (a2 && i == 1) {
                    cout << "LookAt y: " << a2 << "\n";
                    cameraConfig.lookAtY = atof(a2);

                }
                if (a3 && i == 1) {
                    cout << "LookAt z: " << a3 << "\n";
                    cameraConfig.lookAtZ = atof(a3);
                }
                if (a1 && i == 2) {
                    cout << "Up x: " << a1 << "\n";
                    cameraConfig.upX = atof(a1);
                }
                if (a2 && i == 2) {
                    cout << "Up y: " << a2 << "\n";
                    cameraConfig.upY = atof(a2);
                }
                if (a3 && i == 2) {
                    cout << "Up z: " << a3 << "\n";
                    cameraConfig.upZ = atof(a3);
                }
                if (a4){
                    cout << "FOV: " << a4 << "\n";
                    cameraConfig.fov = atof(a4);

                }
                if (a5) {
                    cout << "Near: " << a5 << "\n";
                    cameraConfig.near = atof(a5);
                }
                if (a6) {
                    cout << "Far: " << a6 << "\n";
                    cameraConfig.far = atof(a6);
                }
            }
            i++;
        }
        i = 0;
        for (TiXmlElement* e = root->FirstChildElement("group")->FirstChildElement("models")->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
        {
            if (e)
            {
                const char *a1 = e->Attribute("file");

                if (a1)
                    cout << "Model file: " << a1 << "\n";
                filesToDraw.insert(pair<int,string>(i,a1));
            }
            i++;
        }
    } else cout << "Error: Can't open XML File: " << filename;

}


//Abre um ficheiro .3d e desenha
void openFileAndDrawPoints (string filename){
    fstream file;
    file.open(filename,ios::in);
    if(file.is_open()){
        string line;
        if(drawModeFill) glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        else glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glBegin(GL_TRIANGLES);
        float point_x,point_y,point_z;
        int i = 0;
        float color = 0;
        while (getline(file,line)) {
            sscanf(line.c_str(),"%f %f %f",&point_x,&point_y,&point_z);
            if(drawModeFill){
               if(i % 3 == 0) {
                color == 0? color = 1: color = 0;
                }
                i++;
                glColor3f(color, 1-color, 1-color); 
            } else glColor3f(1, 1, 1); 
            glVertex3f(point_x,point_y,point_z);

        }
        cout << "File drawn: [" << filename << "]\n";
        glEnd();
    } else cout << "File not found: [" << filename << "]\n";
}

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}


void drawAxis(){
    glBegin(GL_LINES);
    //X Axis
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-10.0f, 0.0f, 0.0f);
    glVertex3f( 10.0f, 0.0f, 0.0f);
    //Y Axis
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -10.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    // Z Axis
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();

}

void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
   
    gluLookAt(cameraConfig.cameraX,cameraConfig.cameraY,cameraConfig.cameraZ,
              cameraConfig.lookAtX,cameraConfig.lookAtY,cameraConfig.lookAtZ,
              cameraConfig.upX,cameraConfig.upY,cameraConfig.upZ);
    //gluPerspective(cameraConfig.fov,16/9,cameraConfig.near,cameraConfig.far);

    for(auto const &ent1 : filesToDraw) {
        openFileAndDrawPoints(ent1.second);
    }
    drawAxis();
    // End of frame
    glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}

void processSpecialKeys(int key, int xx, int yy) {

    switch (key) {
        case GLUT_KEY_UP:
            scale++;
            break;
        case GLUT_KEY_DOWN:
            scale--;
            break;
        case GLUT_KEY_RIGHT:
            cameraAngle += 5;
            break;
        case GLUT_KEY_LEFT:
            cameraAngle -= 5;
            break;
        case GLUT_KEY_F1:
            glCullFace(GL_FRONT);
            break;
        case GLUT_KEY_F2:
            glCullFace(GL_BACK);
            break;
        case GLUT_KEY_F3:
            drawModeFill = false;
            break;
        case GLUT_KEY_F4:
            drawModeFill = true;
            break;
    }
    glutPostRedisplay();

}

int main(int argc, char **argv) {
    if(argc != 2){
        cout << "Sintax error: \n";
        cout << "   Usage: ./Engine [XML configuration file]\n";
        exit(-1);
    }
    string xmlFile = argv[1];
    printf("XML File: %s\n",argv[1]);
    readXMLConfigurationFile(argv[1]);
// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    char* windowName = static_cast<char *>(malloc(sizeof(char) * 100));
    sprintf(windowName,"File: [%s]",argv[1]);
    glutCreateWindow(windowName);

// Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);

// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}

