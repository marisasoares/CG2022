#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "generator.h"
#include "fstream"
#include <string.h>

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

int main(int argc, char **argv) {
    /*
    if (argc != 3) {
        printf("Sintax error:\n");
        printf("   Usage: ./Engine [XML configuration file] [3d file to open]\n");
    }
    */

    fstream file3d;
    file3d.open("marisa.3d", ios::out);
    if(!file3d.is_open()){
        printf("Error opening file");
        exit(-1);
    }
    //filename = argv[4];
    if (strcmp(argv[1], "plane") == 0) {
        printf("Length: %f\n", atof(argv[2]));
        printf("Divisions: %f\n", atof(argv[3]));
        drawPlane(atof(argv[2]),atof(argv[3]));
    }
    else if (strcmp(argv[1], "sphere")) {

    }
    else if (strcmp(argv[1], "box")) {

    }
    else if (strcmp(argv[1], "box")) {

    }
    else printf("erro");

    return 1;
}