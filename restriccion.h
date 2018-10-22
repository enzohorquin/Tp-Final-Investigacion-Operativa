#ifndef RESTRICCION_H
#define RESTRICCION_H

#include "QString"
#include "materia.h"
#include "QDebug"

#include <QList>

class Restriccion
{
public:
    //constructores
    Restriccion();
    Restriccion(bool horas, bool porAula, Aula aula,QString anio);

    //getters
    bool getPorAula();
    QString getAnio() const;
    bool getPorCantHoras() const;
    int getValorInd() const;
    int getValor(int i)const;
    void setValorInd(int value);
    int size()const;
    //setters
    Aula getAula();
    void setAnio(const QString &value);
    void setAula(const QString &value);    
    void setPorCantHoras(bool value);
    //funcionalidad
    void addVar(int m);//hacer cuando tenga el otro codigo
    bool estaMateria(int m);

    void imprimir(QList<QString> &materias);//despues borrar

private:
    QList<int> variables;
    bool porCantHoras;//si es por horas
    bool porAula;// permite conocer si la restriccion es por compartir aula o por compartir año
    Aula aula;
    QString anio;
    int valorInd;


};

#endif // RESTRICCION_H
