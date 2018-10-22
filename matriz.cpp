#include "matriz.h"
#include "qdebug.h"

Matriz::Matriz(int fila, int col)
{
    this->fila=fila;
    this->col=col;

    matriz = new float  * [fila];
    for (int f = 0; f < fila; f++)
          matriz[f] = new float[this->col];

    inicializarMatriz();

}

void Matriz::put(int i, int j, float valor)
{
    matriz[i][j]= valor;
}

float Matriz::get(int i, int j)
{
    return matriz[i][j];
}



Matriz::~Matriz()
{
    for (int f = 0; f < fila; f++)
         delete [] matriz[f];

    delete [] matriz;

    matriz = 0;
}

int Matriz::getFila()
{
    return fila;
}

int Matriz::getCol()
{
    return col;
}

void Matriz::imprimir()
{   QString valor ="";

    for(int i=0;i<fila;i++){
        valor="";
        for(int j =0; j <col;j++)
            valor= valor + " " + QString::number(matriz[i][j]);
        qDebug()<<valor;
    }

}

void Matriz::inicializarMatriz()
{
    for(int i=0;i<fila;i++){
        for(int j =0; j <col;j++)
            matriz[i][j]=0;
    }
}


