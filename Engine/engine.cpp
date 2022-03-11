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

using namespace std;

float cameraAngle = 0;
float scale = 1;
string file3D = "NaN";
fstream openedFile;

//Abre um ficheiro .3d e desenha
void openFileAndDrawPoints (string filename){
    fstream file;
    file.open(filename,ios::in);
    if(file.is_open()){
        string line;
        glBegin(GL_TRIANGLES);
        float point_x,point_y,point_z;
        int i = 0;
        float color = 0;
        while (getline(file,line)) {
            sscanf(line.c_str(),"%f %f %f",&point_x,&point_y,&point_z);
            //cout << "Desenhado: ";
            //cout << line;
            //cout << "\n";
            if(i % 3 == 0) {
                color == 0? color = 1: color = 0;
            }
            i++;
            glColor3f(color, 1-color, 1-color);
            glVertex3f(point_x,point_y,point_z);

        }
        glEnd();
    }
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

    gluLookAt(5.0,5.0,5.0,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);
    glRotatef(cameraAngle,0,1,0);
    glTranslatef(scale,scale,scale);
    openFileAndDrawPoints(file3D);
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
    }
    glutPostRedisplay();

}

int main(int argc, char **argv) {
    if(argc != 3){
        //TO DO open xml
        cout << "Sintax error:\n";
        cout << "   Usage: ./Engine [XML configuration file] [3d file to open]\n";
        exit(-1);
    }
    string xmlFile = argv[1];
    file3D = argv[2];
    printf("XML File: %s\n",argv[1]);
    openedFile.open(file3D);
    if(openedFile.is_open()){
        printf("3D file: %s\n",argv[2]);
    }else{
        printf("[Error] Can't open file: %s\n",argv[2]);
        exit(-1);
    }
    /*
    TiXmlDocument document(argv[1]);
    document.LoadFile();
    document.FirstChildElement("World");
    */
// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    char* windowName = static_cast<char *>(malloc(sizeof(char) * 100));
    sprintf(windowName,"#File: [%s]",argv[2]);
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
/*
void readXMLConfigurationFile(char* filename){
    TiXmlDocument doc(filename);
    TiXmlHandle hdocument(&doc);
    doc.RootElement()
}
*/
