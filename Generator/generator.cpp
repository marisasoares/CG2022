#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "generator.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "sstream"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

string filename;

void drawBox(float x, float y, float z, int slices)
{
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
    for (int i = 0; i < slices; i++)
    {
        for (int j = 0; j < slices; j++)
        {
            // 1ºtriangulo
            file << auxX << " ";
            file << 0 << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX + slicesX << " ";
            file << 0 << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX + slicesX << " ";
            file << 0 << " ";
            file << auxZ + slicesZ << " ";
            file << "\n";

            // 2ºtriangulo
            file << auxX + slicesX << " ";
            file << 0 << " ";
            file << auxZ + slicesZ << " ";
            file << "\n";

            file << auxX << " ";
            file << 0 << " ";
            file << auxZ + slicesZ << " ";
            file << "\n";

            file << auxX << " ";
            file << 0 << " ";
            file << auxZ << " ";
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
    for (int i = 0; i < slices; i++)
    {
        for (int j = 0; j < slices; j++)
        {

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
    for (int i = 0; i < slices; i++)
    {
        for (int j = 0; j < slices; j++)
        {

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
    for (int i = 0; i < slices; i++)
    {
        for (int j = 0; j < slices; j++)
        {

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

            file << auxX << " ";
            file << auxY - slicesY << " ";
            file << auxZ + slicesZ << " ";
            file << "\n";

            file << auxX << " ";
            file << auxY << " ";
            file << auxZ + slicesZ << " ";
            file << "\n";

            file << auxX << " ";
            file << auxY << " ";
            file << auxZ << " ";
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
    for (int i = 0; i < slices; i++)
    {
        for (int j = 0; j < slices; j++)
        {

            file << auxX << " ";
            file << auxY << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX << " ";
            file << auxY - slicesY << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX + slicesX << " ";
            file << auxY - slicesY << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX + slicesX << " ";
            file << auxY - slicesY << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX + slicesX << " ";
            file << auxY << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX << " ";
            file << auxY << " ";
            file << auxZ << " ";
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
    for (int i = 0; i < slices; i++)
    {
        for (int j = 0; j < slices; j++)
        {

            file << auxX << " ";
            file << auxY << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX << " ";
            file << auxY - slicesY << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX - slicesX << " ";
            file << auxY - slicesY << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX - slicesX << " ";
            file << auxY - slicesY << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX - slicesX << " ";
            file << auxY << " ";
            file << auxZ << " ";
            file << "\n";

            file << auxX << " ";
            file << auxY << " ";
            file << auxZ << " ";
            file << "\n";

            auxX -= slicesX;
        }
        auxX = x1;
        auxY -= slicesY;
    }
}

void drawPlane(float length, int divisions)
{

    float x1 = length / 2;
    float z1 = length / 2;
    float div = length / divisions;

    int i, j;

    float x = -x1;
    float z = -z1;

    fstream file;
    file.open(filename, ios::out);
    string coord;

    for (i = 0; i < divisions; i++)
    {
        for (j = 0; j < divisions; j++)
        {

            // 1º triangulo
            file << x;
            file << " 0 ";
            file << z;
            file << "\n";

            file << x + div;
            file << " 0 ";
            file << z + div;
            file << "\n";

            file << x + div;
            file << " 0 ";
            file << z;
            file << "\n";

            // 2 triangulo

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

void createSphere(float raio, int stacks, int slices)
{

    float delta1 = 2 * M_PI / stacks;
    float delta2 = M_PI / slices;

    fstream file;
    file.open(filename, ios::out);
    float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
    float a, aux = 0;

    for (int i = 0; i < slices; i++)
    {

        a = 0;

        for (int j = 0; j < stacks; j++)
        {

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

void createCone(float radius, float height, int slices, int stacks)
{
    fstream file;
    file.open(filename, ios::out);

    float theta = 0;
    float nextTheta = 0;
    float delta = (2 * M_PI) / slices;
    float raio = radius / stacks;
    float altura = height / stacks;
    int i, j;

    // fazer a circunferência da base
    for (i = 0; i < slices; i++)
    {
        nextTheta = theta + delta;

        file << "0 0 0\n";
        file << radius * sin(nextTheta) << " 0 " << radius * cos(nextTheta) << "\n";
        file << radius * sin(theta) << " 0 " << radius * cos(theta) << "\n";

        theta = nextTheta;
    } // Fazer as laterais
    float r1 = radius;
    float r2 = radius - raio;
    float alt1 = 0;
    float alt2 = altura;
    theta = 0;
    nextTheta = 0;

    for (i = 0; i < slices; i++)
    {
        nextTheta += delta;

        for (j = 0; j < stacks; j++)
        {
            file << r1 * sin(nextTheta) << " " << alt1 << " " << r1 * cos(nextTheta) << "\n";
            file << r2 * sin(nextTheta) << " " << alt2 << " " << r2 * cos(nextTheta) << "\n";
            file << r1 * sin(theta) << " " << alt1 << " " << r1 * cos(theta) << "\n";

            file << r2 * sin(nextTheta) << " " << alt2 << " " << r2 * cos(nextTheta) << "\n";
            file << r2 * sin(theta) << " " << alt2 << " " << r2 * cos(theta) << "\n";
            file << r1 * sin(theta) << " " << alt1 << " " << r1 * cos(theta) << "\n";

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

void showSintaxError()
{
    printf("Sintax error:\n");
    printf("   Usage: ./generator [Shape] [Args] [Output File]\n");
    printf(" Shapes available: \n");
    printf("    plane: [length] [divisions]\n");
    printf("    box: [size] [divisions]\n");
    printf("    sphere: [radious] [slices] [height]\n");
    printf("    cone: [radious] [heigth] [Slices] [stacks]\n");
    printf("    bezier: [.patch file] [Tesselation]\n");
    exit(-1);
}

float* formulaBezier( float tt, float *p1 , float *p2 , float *p3 , float *p4) {

    float ite = 1.0 - tt;
    float* ppt = new float[3];

    float x0 , x1 , x2 , x3;
    x0 = pow(ite,3);
    x1 = 3 * tt*pow(ite,2);
    x2 = 3 * tt * tt * ite;
    x3 = tt * tt * tt;

    ppt[0] = x0*p1[0] + x1*p2[0] + x2*p3[0] + x3*p4[0];
    ppt[1] = x0*p1[1] + x1*p2[1] + x2*p3[1] + x3*p4[1];
    ppt[2] = x0*p1[2] + x1*p2[2] + x2*p3[2] + x3*p4[2];


    return ppt;
}


float* bezier( float a , float b , int* indice , float** pontos , int ni , int np) {

    float* ponto = new float[3];
    float altp[4][3];
    float res[4][3];
    int i , j = 0 , x = 0;
    float *calculo;


    for( i = 0 ; i < 16 ; i++) {
        altp[j][0] = pontos[indice[i]][0];
        altp[j][0] = pontos[indice[i]][1];
        altp[j][0] = pontos[indice[i]][2];

        j++;

        if( j % 4 == 0 ) {
            ponto = formulaBezier(a,altp[0],altp[1],altp[2],altp[3]);
            res[x][0] = ponto[0];
            res[x][1] = ponto[1];
            res[x][2] = ponto[2];

            x++;

            j = 0;
        }

    }
    calculo = formulaBezier(b,res[0],res[1],res[2],res[3]);

    return calculo;
}


void patch( string file , int tess , string name) {

    //abrir ficheiros de input e output

    ofstream fileo(name);
    string line , aux;
    ifstream filei(file);
    int i;

    //get patch
    if(filei.is_open()) {
        getline(filei,line);
        int npatch = atoi(line.c_str());
        int** indices = new int*[npatch];
        cout << npatch << endl;

        for(int r = 0 ; r < npatch ; r++) {
            getline(filei,line);
            indices[r] = new int[16];

            for(int j = 0 ; j < 16 ; j++) {
                i = line.find(",");
                aux = line.substr(0,i);
                indices[r][j] = atoi(aux.c_str());
                line.erase(0, i + 1);
            }
        }

        getline(filei,line);
        int npontos = atoi(line.c_str());
        cout << npontos << endl;
        float** pontos = new float*[npontos];

        //get pontos
        for( int m = 0 ; m < npontos ; m++){
            getline(filei,line);
            pontos[m] = new float[3];
            for( int l = 0 ; l < 3 ; l++) {
                i = line.find(",");
                aux = line.substr(0,i);
                pontos[m][l] = atof(aux.c_str());
                line.erase(0 , i + 1);
            }
        }

        float incre = 1.0 / tess , u , v , u2 , v2;
        float *** pontoRes = new float**[npatch];

        for(int rr = 0 ; rr < npatch ; rr++) {
            pontoRes[rr] = new float*[4];
            //escrever pontos
            for( int jj = 0 ; jj < tess ; jj++) {

                for( int mn = 0 ; mn < tess ; mn++) {

                    u = jj*incre;
                    v = mn*incre;
                    u2 = (jj + 1)* incre;
                    v2 = (mn + 1)* incre;

                    pontoRes[rr][0] = bezier(u, v, indices[rr], pontos, npatch, npontos);
                    pontoRes[rr][1] = bezier(u, v2, indices[rr], pontos, npatch, npontos);
                    pontoRes[rr][2] = bezier(u2, v, indices[rr], pontos, npatch, npontos);
                    pontoRes[rr][3] = bezier(u2, v2, indices[rr], pontos, npatch, npontos);


                    fileo << pontoRes[rr][0][0] << "," << pontoRes[rr][0][1] << "," << pontoRes[rr][0][2] << endl;
                    fileo << pontoRes[rr][2][0] << "," << pontoRes[rr][2][1] << "," << pontoRes[rr][2][2] << endl;
                    fileo << pontoRes[rr][3][0] << "," << pontoRes[rr][3][1] << "," << pontoRes[rr][3][2] << endl;

                    fileo << pontoRes[rr][0][0] << "," << pontoRes[rr][0][1] << "," << pontoRes[rr][0][2] << endl;
                    fileo << pontoRes[rr][3][0] << "," << pontoRes[rr][3][1] << "," << pontoRes[rr][3][2] << endl;
                    fileo << pontoRes[rr][1][0] << "," << pontoRes[rr][1][1] << "," << pontoRes[rr][1][2] << endl;
                }
            }

        }
    }

    filei.close();
    fileo.close();
}




int main(int argc, char **argv)
{
    if (argc == 1)
        showSintaxError();

    if (strcmp(argv[1], "plane") == 0)
    {
        filename = argv[4];
        if (argc != 5)
            showSintaxError();
        drawPlane(atof(argv[2]), atof(argv[3]));
    }
    else if (strcmp(argv[1], "sphere") == 0)
    {
        if (argc != 6)
            showSintaxError();
        filename = argv[5];
        createSphere(atof(argv[2]), atof(argv[3]), atof(argv[4]));
    }
    else if ((strcmp(argv[1], "cone") == 0))
    {
        if (argc != 7)
            showSintaxError();
        filename = argv[6];
        createCone(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]));
    }
    else if (strcmp(argv[1], "box") == 0)
    {
        if (argc != 5)
            showSintaxError();
        filename = argv[4];
        drawBox(atof(argv[2]), atof(argv[2]), atof(argv[2]), atoi(argv[3]));
    }
    else if (strcmp(argv[1], "bezier") == 0)
    {
        if (argc != 5)
            showSintaxError();
        char *file = argv[2];
        filename = argv[4];
        patch(file,atoi(argv[3]),filename);
    }
    else
        showSintaxError();
    return 1;
}