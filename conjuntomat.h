#ifndef CONJUNTOMAT_H
#define CONJUNTOMAT_H

#include "QList"
#include "QString"
#include "materia.h"
#include "QSet"
#include "aula.h"
#define cte_inicio_dia 8


class ConjuntoMat
{
public:
    ConjuntoMat();
    void addAula(Aula &aula);
    void addMateria(Materia & materia);
    void addAnio();

    void getAulas(QList<Aula>& aulas);
    void getMaterias(QList<Materia> &materias);
    void getAnios(QList<QString> &listAnios);
    int getCargaHoraria(int anio);

    void borrarMateria(int i);
    void borrarAula(QString i);
    void borrarAnio();

    int posAula(Aula aula);
    int getCantAnios();
    void reiniciar();
    bool estaAula(QString aula);
    bool estaAulaUsada(QString aula);
    void borrarMateriaAula(QString aula);
    void actualizarMateria(int pos, int horas, QString dia, int horaInicio);

    int getAnioDeMat(int materia); //recupero el aula de la materia en la posicion i
    Aula getAulaDeMat(int materia);//recupero el aula de la materia en la posicion i
    int getInicio(QString dia, Aula aula, int anio, int cantHoras);
    void imprimir();
    void ocuparAula(QString nombreAula,HorarioDia franja);
    void setMateria(Materia materia);


private:
    QList<Aula> aulas;
    QList<Materia> materias;
    QList<int> anios;
};

#endif // CONJUNTOMAT_H
