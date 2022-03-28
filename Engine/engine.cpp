#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define _USE_MATH_DEFINES
#include "engine.h"


using namespace std;

// Angulos da camera
float alpha_angle,beta_angle = 0.5;

// Distância à origem
float distance_Origin = 0;

//Modo de desenho
bool drawModeFill = false;

void Model::drawModel() const {
    int i = 0;
    float color = 0;
    for(Point point: points){
        string line;
        //Togle between wireframe and fill
        if(drawModeFill) glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        else glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        //Draw model
        glBegin(GL_TRIANGLES);
        //Define color if in fill mode or white if wireframe
        if(drawModeFill){
            if(i % 3 == 0) {
                color == 0? color = 1: color = 0;
            }
            i++;
            glColor3f(color, 1-color, 1-color);
        } else glColor3f(1, 1, 1);
        //Draw vertex
        glVertex3f(point.x,point.y,point.z);
    }
    glEnd();
}

void Transformation::applyTransformation() {
    switch (type) {
        case(0):
            glTranslatef(this->x,this->y,this->z);
            break;
        case(1):
            glRotatef(this->angle,this->x,this->y,this->z);
            break;
        case(2):
            glScalef(this->x,this->y,this->z);
            break;
        default:
            cout << "Unknown transformation type\n";
            break;
    }
}

//Modelos lidos do ficheiro XML
list<Model> modelsToDraw;

//Configuração da camera atual
CameraConfig cameraConfig;

//Abre um ficheiro .3d e carrega-o para memória
Model openFileAndLoadModel (const string& filename){
    fstream file;
    file.open(filename,ios::in);
    Model model;
    if(file.is_open()){
        string line;
        float point_x,point_y,point_z;
        int i = 0;
        float color = 0;
        while (getline(file,line)) {
            sscanf(line.c_str(),"%f %f %f",&point_x,&point_y,&point_z);
            Point point{};
            point.x = point_x;
            point.y = point_y;
            point.z = point_z;
            model.points.insert(model.points.end(),point);
        }
        cout << "File drawn: [" << filename << "]\n";
    } else cout << "File not found: [" << filename << "]\n";
    return model;
}

void readCameraXMLConfigurations(TiXmlElement* root){
    int i = 0;
    for (TiXmlElement* e = root->FirstChildElement("camera")->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        const char *x = e->Attribute("x");
        const char *y = e->Attribute("y");
        const char *z = e->Attribute("z");
        const char *fov = e->Attribute("fov");
        const char *near = e->Attribute("near");
        const char *far = e->Attribute("far");
        if (x && i == 0) {
            cout << "Position x: " << x << "\n";
            cameraConfig.cameraX = atof(x);
        }
        if (y && i == 0) {
            cout << "Position y: " << y << "\n";
            cameraConfig.cameraY = atof(y);
        }
        if (z && i == 0) {
            cout << "Position z: " << z << "\n";
            cameraConfig.cameraZ = atof(z);
        }
        if (x && i == 1) {
            cout << "LookAt x: " << x << "\n";
            cameraConfig.lookAtX = atof(x);
        }
        if (y && i == 1) {
            cout << "LookAt y: " << y << "\n";
            cameraConfig.lookAtY = atof(y);

        }
        if (z && i == 1) {
            cout << "LookAt z: " << z << "\n";
            cameraConfig.lookAtZ = atof(z);
        }
        if (x && i == 2) {
            cout << "Up x: " << x << "\n";
            cameraConfig.upX = atof(x);
        }
        if (y && i == 2) {
            cout << "Up y: " << y << "\n";
            cameraConfig.upY = atof(y);
        }
        if (z && i == 2) {
            cout << "Up z: " << z << "\n";
            cameraConfig.upZ = atof(z);
        }
        if (fov) {
            cout << "FOV: " << fov << "\n";
            cameraConfig.fov = atof(fov);

        }
        if (near) {
            cout << "Near: " << near << "\n";
            cameraConfig.near = atof(near);
        }
        if (far) {
            cout << "Far: " << far << "\n";
            cameraConfig.far = atof(far);
        }
        i++;
    }
}

void readGroupXMLConfigurationFile(TiXmlElement* root){
    int i = 0;
    list<Transformation> transformationList{};
       for (TiXmlElement* element = root->FirstChildElement("group"); element != nullptr; element = element->NextSiblingElement()){
           for (TiXmlElement* element2 = element -> FirstChildElement("transform"); element2 != nullptr ; element2 = element2->NextSiblingElement() ) {
               for(TiXmlElement* element3 = element2 -> FirstChildElement(); element3 != nullptr ; element3 = element3->NextSiblingElement()){
                   Transformation transformation{};
                   if(strcmp(element3->Value(),"translate") == 0){
                       transformation.type = 0;
                       transformation.angle = 0;
                       transformation.x = atof(element3->Attribute("x"));
                       transformation.y = atof(element3->Attribute("y"));
                       transformation.z = atof(element3->Attribute("z"));
                       transformationList.push_back(transformation);
                       cout << "Translate x: " << transformation.x;
                       cout << " y: " << transformation.y;
                       cout << " z: " << transformation.z << "\n";
                   }
                   if(strcmp(element3->Value(),"rotate") == 0){
                       transformation.type = 1;
                       transformation.angle = atof(element3->Attribute("angle"));
                       transformation.x = atof(element3->Attribute("x"));
                       transformation.y = atof(element3->Attribute("y"));
                       transformation.z = atof(element3->Attribute("z"));
                       transformationList.push_back(transformation);
                       cout << "Rotate angle: " << transformation.angle;
                       cout << " x: " << transformation.x;
                       cout << " y: " << transformation.y;
                       cout << " z: " << transformation.z << "\n";
                   }
                   if(strcmp(element3->Value(),"scale") == 0){
                       transformation.type = 2;
                       transformation.angle = 0;
                       transformation.x = atof(element3->Attribute("x"));
                       transformation.y = atof(element3->Attribute("y"));
                       transformation.z = atof(element3->Attribute("z"));
                       transformationList.push_back(transformation);
                       cout << "Scale x: " << transformation.x;
                       cout << " y: " << transformation.y;
                       cout << " z: " << transformation.z << "\n";
                   }
                   if(strcmp(element3->Value(),"model") == 0){
                       const char *modelFile = element3->Attribute("file");
                       Model model = openFileAndLoadModel(modelFile);
                       model.transformations = transformationList;
                       modelsToDraw.push_back(model);
                       cout << "Model file: " << modelFile << "\n";
                   }
               }
           }
           /*
           element->FirstChildElement("models")->FirstChildElement();
           const char *a1 = element->Attribute("file");
           if (a1)
               cout << "Model file: " << a1 << "\n";
           Model model = openFileAndLoadModel(a1);
           //modelsToDraw.insert(pair<int, Model>(i, model));
           i++;*/
       }
}

//Ler o ficheiro XML e carregar os modelos
void readXMLConfigurationFile(char* filename) {
    TiXmlDocument document;
    bool fileOpened = document.LoadFile(filename);
    int i = 0;
    if(fileOpened){
        TiXmlElement* root = document.RootElement();
        readCameraXMLConfigurations(root);
        readGroupXMLConfigurationFile(root);
    } else cout << "Error: Can't open XML File: " << filename << "\n";

}



//Redimensionar janela
void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you can't make a window with zero width).
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
    gluPerspective(cameraConfig.fov ,ratio, cameraConfig.near ,cameraConfig.far);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}


//Desenhar os eixos XYZ
void drawAxis(){
    glBegin(GL_LINES);
    //X Axis
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f( 100.0f, 0.0f, 0.0f);
    //Y Axis
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z Axis
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
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

    // For each pair model list<transformation> apply transformations and draw model
    for(Model model:  modelsToDraw) {
        model.drawModel();
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
        case GLUT_KEY_RIGHT:
            alpha_angle -= 0.1; break;
        case GLUT_KEY_LEFT:
            alpha_angle += 0.1; break;

        case GLUT_KEY_UP:
            beta_angle += 0.01f;
            if (beta_angle > 1.5f)
                beta_angle = 1.5f;
            break;

        case GLUT_KEY_DOWN:
            beta_angle -= 0.01f;
            if (beta_angle < -1.5f)
                beta_angle = -1.5f;
            break;

        case GLUT_KEY_PAGE_DOWN: distance_Origin -= 0.5f;
            if (distance_Origin < 1.0f)
                distance_Origin = 1.0f;
            break;

        case GLUT_KEY_PAGE_UP: distance_Origin += 0.5f; break;

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
    cameraConfig.cameraX = distance_Origin * cos(beta_angle) * sin(alpha_angle);
    cameraConfig.cameraY = distance_Origin * sin(beta_angle);
    cameraConfig.cameraZ = distance_Origin * cos(beta_angle) * cos(alpha_angle);
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    if(argc != 2){
        cout << "Syntax error: \n";
        cout << "   Usage: ./Engine [XML configuration file]\n";
        exit(-1);
    }
    string xmlFile = argv[1];
    printf("XML File: %s\n",argv[1]);
    readXMLConfigurationFile(argv[1]);
    /*
    //distância da camera à origem
    distance_Origin = sqrt((cameraConfig.cameraX)*(cameraConfig.cameraX) + (cameraConfig.cameraY)*(cameraConfig.cameraY) + (cameraConfig.cameraZ)*(cameraConfig.cameraZ));
    
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
    */
    return 1;
}

