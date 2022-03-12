#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "generator.h"
#include "fstream"
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

string filename;

void drawPlane(float length, int divisions) {

    float x1 = length / 2;
    float z1 = length / 2;
    float div = length / divisions;

    int i, j;

    float x = -x1;
    float z = -z1;

    fstream file;
    file.open("plane.3d",ios::out);
    //char* string = malloc(sizeof(char) * 20);
    string coord;


    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {

            //1º triangulo
            file << x;
            file << " 0 ";
            file << z;
            file << "\n";

            file << x+div;
            file << " 0 ";
            file << z+div;
            file << "\n";

            file << x+div;
            file << " 0 ";
            file << z;
            file << "\n";

            //2 triangulo

            file << x + div;
            file << " 0 ";
            file << z + div;
            file << "\n";

            file << x;
            file << " 0 ";
            file << z;
            file << "\n";

            file << x;
            file << " 0 ";
            file << z + div;
            file << "\n";

            z += div;
        }
        z = -z1;
        x += div;
    }
}

void createSphere(float radius, int slices, int stacks){
    
    float delta1 = M_PI / stacks;
    float delta2 = 2 * M_PI / slices;
    fstream file;
    file.open("sphere.3d",ios::out);

    for (float i = -M_PI / 2; i < M_PI / 2; i += delta1) {

        float aux1 = i + delta1;


        for (float j = 0; j < 2 * M_PI - delta2; j += delta2) {

            float aux2 = j + delta2;

            //Triângulo 1

            file << (cos(aux1) * sin(j) * radius) << " " << sin(aux1) * radius << "" << cos(aux1)* cos(j)* radius << "\n";
            file << cos(i) * sin(j) * radius << " " << sin(i) * radius << " " << cos(i) * cos(j) * radius << "\n";
            file << cos(i) * sin(aux2) * radius << " " << sin(i) * radius << " " << cos(i) * cos(aux2) * radius << "\n";

            //Triângulo 2
            file << cos(aux1) * sin(j) * radius << " " << sin(aux1) * radius << " " << cos(aux1)* cos(j)* radius << "\n";
            file << cos(i) * sin(aux2) * radius << " " << sin(i) * radius << " " << cos(i)* cos(aux2)* radius << "\n";
            file << cos(aux1) * sin(aux2) * radius << " " << sin(aux1) * radius << " " << cos(aux1)* cos(aux2)* radius << "\n";

        }
    }
}


void createCone(float radius, float height, int slices, int stacks, string name) {
    fstream file;
    file.open(name,ios::out);

    float theta = 0;
    float nextTheta = 0;
    float delta = (2 * M_PI) / slices;
    float raio = radius / stacks;
    float altura = height / stacks;
    int i, j;

    //fazer a circunferência da base
    for (i = 0; i < slices; i++) {
        nextTheta = theta + delta;

        file << "0 0 0\n";
        file << radius * sin(nextTheta) << " 0 " << radius * cos(nextTheta) << "\n";
        file << radius * sin(theta) << " 0 " << radius * cos(theta) << "\n";

        theta = nextTheta;
    }// Fazer as laterais
    float r1 = radius;
    float r2 = radius - raio;
    float alt1 = 0;
    float alt2 = altura;
    theta = 0;
    nextTheta = 0;

    for (i = 0; i < slices; i++) {
        nextTheta += delta;

        for (j = 0; j < stacks; j++) {
            file << r1 * sin(nextTheta) <<" "<< alt1 <<" " << r1 * cos(nextTheta) << "\n";
            file << r2 * sin(nextTheta) << " "<< alt2 << " " << r2 * cos(nextTheta) << "\n";
            file << r1 * sin(theta) << " "<< alt1 << " " << r1 * cos(theta) << "\n";

            file << r2 * sin(nextTheta) << " "<< alt2 << " " << r2 * cos(nextTheta) << "\n";
            file << r2 * sin(theta) << " "<< alt2 << " " << r2 * cos(theta) << "\n";
            file << r1 * sin(theta) << " "<< alt1 << " " << r1 * cos(theta) << "\n";

            r1 -= raio;
            r2 -= raio;
            alt1 += altura;
            alt2 += altura;
        }
        r1 = radius;
        r2 = radius - raio;
        alt1 = 0;
        alt2 = altura;
        theta = nextTheta;
    }
}


void showSintaxError(){
    printf("Sintax error:\n");
    printf("   Usage: ./generator [Shape] [Args] [Output File]\n");
    printf(" Shapes available: \n");
    printf("    Plane: [length] [divisions]\n");
    printf("    Box: [size] [divisions]\n");
    printf("    Sphere: [radious] [height]\n");
    printf("    Cone: [radious] [heigth] [Slices] [stacks]\n");
    exit(-1);
}

int main(int argc, char **argv) {
    printf("argc: %d\n" , argc);
    if(argc == 1) showSintaxError();

    if (strcmp(argv[1], "plane") == 0) {
        if(argc != 5) showSintaxError();
        printf("Length: %f\n", atof(argv[2]));
        printf("Divisions: %f\n", atof(argv[3]));
        drawPlane(atof(argv[2]),atof(argv[3]));
    }
    else if (strcmp(argv[1], "sphere") == 0) {
        printf("esfera");
        if(argc != 6) showSintaxError();
        createSphere(atof(argv[2]),atof(argv[3]),atof(argv[4]));
    }
    else if ((strcmp(argv[1], "cone") == 0) && (argc == 7)) {
        createCone(atof(argv[2]),atof(argv[3]),stoi(argv[4]),stoi(argv[5]), argv[6]);
    }
    else if (strcmp(argv[1], "box") == 0) {

    }
    else showSintaxError();
    return 1;
}