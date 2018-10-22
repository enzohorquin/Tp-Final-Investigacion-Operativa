#ifndef MATERIA_H
#define MATERIA_H

#include "QString"
#include "QHash"
#include "horariodia.h"
#include "aula.h"

class Materia
{
public:
    //constructores
    Materia();
    Materia(QString nombre, Aula &a);
    Materia(QString nombre, Aula &aula, int anio, int cargaHoraria);
    Materia(QString nombre, Aula &aula, int horaInicio, int minutoInicio, int horaFin, int minutoFin, QString dia);
    Materia(QString nombre, Aula &aula, int horaInicio,int minutoInicio,int horaFin, int minutoFin,QString dia,int anio);

    //getters
    void setAula (Aula & a );
    QString getNombre() const;
    Aula getAula() const;
    void getHoraInicio(int &hora, int &min, QString dia) const;
    void getHoraFin (int &hora, int &min, QString dia) const;
    QList<QString> getDias();
    int getAnio() const;
    int getCantHoras() const;
    void borrarFranja(int inicio,int fin, QString dia);

    //setters
    void setAnio(int value);
    void setCantHoras(int value);
    void setDia (QString d);
    void setHoraInicio(int hora, int min, QString dia);
    void setHoraFin(int hora, int min, QString dia);
    void setNombre(QString nombre);

//    void operator ==(const Materia &otraMateria);
   //Materia operator =(const Materia &otraMateria);
   void modificarCantHoras(int horas);

private:
    QString nombre;
    int anio;
    int cantHoras;
    Aula aula;
    QHash<QString,HorarioDia> dias;

};

#endif // MATERIA_H
