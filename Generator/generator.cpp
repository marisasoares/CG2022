#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "generator.h"
#include "fstream"
#include <string.h>

using namespace std;

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

    if (strcmp(argv[1], "plane") == 0) {
        file3d << "0 0 0\n";
        file3d << "1 0 1\n";
        file3d << "1 0 0\n";
        file3d << "0 0 0\n";
        file3d << "0 0 1\n";
        file3d << "1 0 1\n";
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