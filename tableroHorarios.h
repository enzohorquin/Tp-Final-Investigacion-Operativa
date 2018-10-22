#ifndef TABLEROHORARIOS_H
#define TABLEROHORARIOS_H

#include <QList>
#include <QString>
#include "materia.h"
#include "QString"

class tableroHorarios
{
public:
    tableroHorarios();
    void insertarCurso(Materia materia);
    int getValor(int i, int j);
    QString getNombre(int i);
    Aula getAula(int i);
    int getAnio(int i);
    void inicializar();
    void getMateriasDia(QList<QString> & materiasDia, QString dia);
    void getMateriasDiaCompleta(QList<Materia> & materiasDia, QString dia);
    void getMaterias(QList<Materia> &materias);
    void addMateria(Materia mat);
    void setMateria(Materia materia);


private:
    int convertirDia(QString dia);
    int matriz[29][7];
    QList<Materia> materias;

};

#endif // TABLEROHORARIOS_H
