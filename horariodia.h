#ifndef HORARIODIA_H
#define HORARIODIA_H

#include "QString"

class HorarioDia
{
public:
    HorarioDia();
    //getters
    void getHoraInicio(int &hora, int &min) const;
    void getHoraFin(int &hora, int &min) const;
    QString getDia()const;

    //setters
    void setHoraIncio(int hora, int min);
    void setHoraFin (int hora, int min);
    void setDia(QString d);
    int getCantidadHoras()const;
    bool perteneceFranja(HorarioDia h) ;
    bool operator <(HorarioDia h);

    bool operator ==(HorarioDia h);

    QString toString();

private:
    int horaInicio;
    int minutoInicio;
    int horaFin;
    int minutoFin;
    QString dia;




};

#endif // HORARIODIA_H
