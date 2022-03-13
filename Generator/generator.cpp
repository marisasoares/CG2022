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

void drawBox(float x, float y, float z, int slices) {
    float x1 = x / 2;
    float z1 = z / 2;
    float slicesX = x / slices;
    float slicesY = y / slices;
    float slicesZ = z / slices;

	fstream file;
	file.open(filename, ios::out);

    // Base
    float auxX = -x1;
    float auxZ = -z1;
    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < slices; j++) {
            //1ºtriangulo 
			file << auxX<< " ";
			file << 0<< " ";
			file << auxZ<< " ";
            file << "\n";

			file << auxX + slicesX<< " ";
			file << 0<< " ";
			file << auxZ<< " ";
            file << "\n";

			file << auxX + slicesX<< " ";
			file << 0<< " ";
			file << auxZ + slicesZ<< " ";
            file << "\n";

			//2ºtriangulo 
			file << auxX + slicesX<< " ";
			file << 0<< " ";
			file << auxZ + slicesZ<< " ";
            file << "\n";

			file << auxX << " ";
			file << 0<< " ";
			file << auxZ + slicesZ<< " ";
            file << "\n";

			file << auxX<< " ";
			file << 0<< " ";
			file << auxZ<< " ";
            file << "\n";

            auxZ += slicesZ;
        }
        auxZ = -z1;
        auxX += slicesX;
    }
    // Cima
    auxX = -x1;
    auxZ = -z1;
    float auxY = y;
    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < slices; j++) {


            file << auxX + slicesX << " ";
            file << auxY << " ";
            file << auxZ + slicesZ << " ";
            file << "\n";

            file << auxX + slicesX << " ";
            file << auxY << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX << " ";
            file << auxY << " ";
            file << auxZ << " ";
            file << "\n";


            file << auxX << " ";
            file << auxY << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX << " ";
            file << auxY << " ";
            file << auxZ + slicesZ << " ";
            file << "\n";

            file << auxX + slicesX << " ";
            file << auxY << " ";
            file << auxZ + slicesZ << " ";
            file << "\n";

            auxZ += slicesZ;
        }
        auxZ = -z1;
        auxX += slicesX;
    }

    // Lado direito
    auxX = x1;
    auxZ = z1;
    auxY = y;
    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < slices; j++) {


            file << auxX << " ";
            file << auxY << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX << " ";
            file << auxY - slicesY << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX << " ";
            file << auxY - slicesY << " ";
            file << auxZ - slicesZ << " ";
            file << "\n";


            file << auxX << " ";
            file << auxY - slicesY << " ";
            file << auxZ - slicesZ << " ";
            file << "\n";

            file << auxX << " ";
            file << auxY << " ";
            file << auxZ - slicesZ << " ";
            file << "\n";

            file << auxX << " ";
            file << auxY << " ";
            file << auxZ << " ";
            file << "\n";

            auxZ -= slicesZ;
        }
        auxZ = z1;
        auxY -= slicesY;
    }

    // Lado Esquerdo
    auxX = -x1;
    auxZ = -z1;
    auxY = y;
    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < slices; j++) {

            file << auxX << " ";
            file << auxY << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX << " ";
            file << auxY - slicesY << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX << " ";
            file << auxY - slicesY << " ";
            file << auxZ + slicesZ;
            file << "\n";

            file << auxX<< " ";
            file << auxY - slicesY<< " ";
            file << auxZ + slicesZ<< " ";
            file << "\n";

            file << auxX<< " ";
            file << auxY<< " ";
            file << auxZ + slicesZ<< " ";
            file << "\n";

            file << auxX<< " ";
            file << auxY<< " ";
            file << auxZ<< " ";
            file << "\n";

            auxZ += slicesZ;
        }
        auxZ = -z1;
        auxY -= slicesY;
    }

    // Frente
    auxX = -x1;
    auxZ = z1;
    auxY = y;
    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < slices; j++) {

            file << auxX << " ";
            file << auxY<< " ";
            file << auxZ<< " ";
            file << "\n";

            file << auxX<< " ";
            file << auxY - slicesY<< " ";
            file << auxZ<< " ";
            file << "\n";

            file << auxX + slicesX<< " ";
            file << auxY - slicesY<< " ";
            file << auxZ<< " ";
            file << "\n";


            file << auxX + slicesX<< " ";
            file << auxY - slicesY<< " ";
            file << auxZ<< " ";
            file << "\n";

            file << auxX + slicesX<< " ";
            file << auxY<< " ";
            file << auxZ<< " ";
            file << "\n";

            file << auxX<< " ";
            file << auxY<< " ";
            file << auxZ<< " ";
            file << "\n";

            auxX += slicesX;
        }
        auxX = -x1;
        auxY -= slicesY;
    }

    // Trás
    auxX = x1;
    auxZ = -z1;
    auxY = y;
    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < slices; j++) {

            file << auxX<< " ";
            file << auxY<< " ";
            file << auxZ<< " ";
            file << "\n";

            file << auxX<< " ";
            file << auxY - slicesY<< " ";
            file << auxZ<< " ";
            file << "\n";

            file << auxX - slicesX<< " ";
            file << auxY - slicesY<< " ";
            file << auxZ<< " ";
            file << "\n";

            file << auxX - slicesX<< " ";
            file << auxY - slicesY<< " ";
            file << auxZ<< " ";
            file << "\n";

            file << auxX - slicesX<< " ";
            file << auxY<< " ";
            file << auxZ<< " ";
            file << "\n";

            file << auxX<< " ";
            file << auxY<< " ";
            file << auxZ<< " ";
            file << "\n";

            auxX -= slicesX;
        }
        auxX = x1;
        auxY -= slicesY;
    }

}

void drawPlane(float length, int divisions) {

    float x1 = length / 2;
    float z1 = length / 2;
    float div = length / divisions;

    int i, j;

    float x = -x1;
    float z = -z1;

    fstream file;
    file.open(filename,ios::out);
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

void createSphere(float raio, int stacks, int slices) {

        float delta1 = 2 * M_PI / stacks;
        float delta2 = M_PI / slices;

        fstream file;
        file.open(filename);
        float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
        float a, aux = 0;

        for (int i = 0 ; i < slices ; i ++) {

            a = 0;

            for (int j = 0 ; j < stacks ; j++){

            x1 = raio * sin(aux) * sin(a);
            y1 = raio * cos(aux);
            z1 = raio * sin(aux) * cos(a);

            x2 = raio * sin(aux + delta2) * sin(a + delta1);
            y2 = raio * cos(aux + delta2);
            z2 = raio * sin(aux + delta2) * cos(a + delta1);

            x3 = raio * sin(aux + delta2) * sin(a);
            y3 = raio * cos(aux + delta2);
            z3 = raio * sin(aux + delta2) * cos(a);

            x4 = raio * sin(aux) * sin(a + delta1);
            y4 = raio * cos(aux);
            z4 = raio * sin(aux) * cos(a + delta1);


            file << x1 << " " << y1 << " " << z1 << endl;
            file << x3 << " " << y3 << " " << z3 << endl;
            file << x2 << " " << y2 << " " << z2 << endl;

            file << x1 << " " << y1 << " " << z1 << endl;
            file << x2 << " " << y2 << " " << z2 << endl;
            file << x4 << " " << y4 << " " << z4 << endl;


            a += delta1;

            }

            aux += delta2;
        }
}


void createCone(float radius, float height, int slices, int stacks) {
    fstream file;
    file.open(filename,ios::out);

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
    printf("    Sphere: [radious] [slices] [height]\n");
    printf("    Cone: [radious] [heigth] [Slices] [stacks]\n");
    exit(-1);
}

int main(int argc, char **argv) {
    if(argc == 1) showSintaxError();

    if (strcmp(argv[1], "plane") == 0) {
        filename = argv[4];
        if(argc != 5) showSintaxError();
        drawPlane(atof(argv[2]),atof(argv[3]));
    }
    else if (strcmp(argv[1], "sphere") == 0) {
        if(argc != 6) showSintaxError();
        filename = argv[5];
        createSphere(atof(argv[2]),atof(argv[3]),atof(argv[4]));
    }
    else if ((strcmp(argv[1], "cone") == 0)) {
        if(argc != 7) showSintaxError();
        filename = argv[6];
        createCone(atof(argv[2]),atof(argv[3]),atoi(argv[4]),atoi(argv[5]));
    }
    else if (strcmp(argv[1], "box") == 0) {
        if(argc != 5) showSintaxError();
        filename = argv[4];
        drawBox(atof(argv[2]),atof(argv[2]),atof(argv[2]),atoi(argv[3]));

    }
    else showSintaxError();
    return 1;
}