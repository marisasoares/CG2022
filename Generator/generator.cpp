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
    else if (strcmp(argv[1], "box") == 0) {

    }
    else if (strcmp(argv[1], "box") == 0) {

    }
    else showSintaxError();
    return 1;
}