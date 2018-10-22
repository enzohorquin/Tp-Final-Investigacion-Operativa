#ifndef SOLUCION_H
#define SOLUCION_H

#include "tablerohorarios.h"
#include "restriccion.h"
#include "materia.h"
#include "qlist.h"
#include "matriz.h"
#include "conjuntomat.h"
#define CERO 0
#define UNO 1
#define cte_horas_aulas 16
class Solucion
{
public:
    Solucion();
    Solucion(QString dia);
    void resolver();
    void addRestriccion(Materia m);
    void addMateria(Materia &mat);
    void addAula(Aula &aula);
    void addAnio();
    void getAnios(QList<QString> &lisAnios);
    void getMaterias(QList<Materia> &materias);
    void borrarAnio();
    void borrarMateria(int mat);
    void borrarAula(QString aula);
    int getCantAnios();
    void reiniciar();
    QString getDia();
    void setDia(QString dia);
    void addDia(QString dia);
    bool estaAula(QString aula);
    bool estaAulaUsada(QString aula);
    void borrarMateriaAula(QString aula);
    void getAulas(QList<Aula> &aulas);
    Aula getAula(Aula &aula);
    void mostrarConjunto();
    void setMateria(Materia materia);

private:
    QList<Restriccion*> restricciones;
    QList<Materia> materias;
    Matriz * M;
    ConjuntoMat conjunto;
    QList<QString> dias;
    QString dia;
    int cantVar;
    int cantRest;
    int cantDias;

    //metodos privados
    bool infinitasSoluciones();
    void GenerarMatriz();
    void cargarFuncionObjetivo();
    void cargarMatrizIdentidad();
    void cargarRestriccionesEnMatriz();
    void imprimir();//despues borrar
    void addRestricciones();
    bool cumpleParada();
    float getValorPivot();
    int getFilaPivot();
    int getVariableEntraALaBase();
    void actualizarTabla();
    void solucion();
    void actualizarRestricciones(QVector<QPair<int, int> > resultado, QString dia);
    QVector<QPair<int, int> > obtenerResultados();
    bool restantesCero(int ubicacionUno, int col);


};

#endif // SOLUCION_H
