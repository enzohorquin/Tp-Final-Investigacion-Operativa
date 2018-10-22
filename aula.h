#ifndef AULA_H
#define AULA_H
#include "QString"
#include "qlist.h"
#include "horariodia.h"

class Aula
{
public:
    Aula(QString nombre);
    Aula();
    bool perteneceFranja(HorarioDia hora);
    bool ocuparAula(HorarioDia hora);
    void setFranja(HorarioDia & hora);
    void getFranja(int id,QList<HorarioDia>  & h);
    QString getNombre() const;
    float getCantHorasDisponibles(int dia)const;
    int convertirDia(QString dia);
    void imprimir();
    void eliminar(HorarioDia horaReemplazada);
    bool desocuparAula(HorarioDia hora, HorarioDia horaReemplazada);

private:
    QString nombre;
    QList<QList<HorarioDia> > franjaDisponible;  /* La primer lista corresponde a los dias
                                                    La segunda lista corresponde a la franja disponible que tiene el aula en ese dia
                                                    Debido a que cuando se haga la primer asignacion de horario en el aula, pasaria a tener dos rangos de horarios disponibles
                                                    y asi sucesivamente. */


    QList<HorarioDia> generarFranja(HorarioDia h1, HorarioDia h2) ; //h1 corresponde al horario que tengo disponible y h2 el horario que quiero ocupar.





};

#endif // AULA_H
