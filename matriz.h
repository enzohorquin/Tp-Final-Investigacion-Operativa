#ifndef MATRIZ_H
#define MATRIZ_H

#include <QMainWindow>
#include <QWidget>

class Matriz
{
public:
    Matriz();
    Matriz(int fila, int col);
   void  put(int i, int j, float valor);
   float get(int i, int j);
    ~Matriz();
   int getFila();
   int getCol();
   void imprimir();
    void inicializarMatriz();


private:
    int fila;
    int col;
    float ** matriz;

};

#endif // MATRIZ_H
