#include "materia.h"
#include "qdebug.h"

Materia::Materia()
{

}

Materia::Materia(QString nombre,Aula &a){
    this->nombre=nombre;
    this->aula=a;
}

Materia::Materia(QString nombre, Aula &aula, int anio, int cargaHoraria){
    this->nombre=nombre;
    this->aula=aula;
    this->anio=anio;
    this->cantHoras=cargaHoraria;
}

Materia::Materia(QString nombre, Aula  & aula, int horaInicio, int minutoInicio, int horaFin, int minutoFin, QString dia){
    this->nombre=nombre;
    this->aula=aula;
    HorarioDia nuevo;
    dias.insert(dia,nuevo);
    dias.find(dia)->setHoraIncio(horaInicio,minutoInicio);
    dias.find(dia)->setHoraFin(horaFin,minutoFin);
    float horas;
       if(minutoInicio != 0)
           horas-=0.50;
       if(minutoFin != 0)
           horas+=0.50;


       horas = horas + (horaFin - horaInicio);
     cantHoras=horas;

}

Materia::Materia(QString nombre, Aula &aula, int horaInicio, int minutoInicio, int horaFin, int minutoFin, QString dia, int anio){
    this->nombre=nombre;
    this->aula=aula;
    HorarioDia nuevo;
    dias.insert(dia,nuevo);
    dias.find(dia)->setHoraIncio(horaInicio,minutoInicio);
    dias.find(dia)->setHoraFin(horaFin,minutoFin);
    this->anio=anio;
    float horas;
       if(minutoInicio != 0)
           horas-=0.50;
       if(minutoFin != 0)
           horas+=0.50;


     horas = horas + (horaFin - horaInicio);
     cantHoras=horas;
}


void Materia::setDia(QString d){
    HorarioDia nuevo;
    dias.insert(d,nuevo);
}
void Materia ::setAula(Aula &a){
    this->aula=a;
}

void Materia::setHoraFin(int hora, int min, QString dia){
    if (dias.find(dia) == dias.end()){
        HorarioDia nuevo;
        dias.insert(dia,nuevo);
    }
    else
        dias.find(dia)->setHoraFin(hora,min);

}

void Materia::setNombre(QString nombre)
{
    this->nombre = nombre;
}

void Materia::setHoraInicio(int hora, int min, QString dia){
    if (dias.find(dia) == dias.end()){
        HorarioDia nuevo;
        dias.insert(dia,nuevo);
    }
    else
    dias.find(dia)->setHoraIncio(hora,min);
}

Aula Materia::getAula() const {
    return aula;
}

QString Materia::getNombre() const{
    return nombre;
}

void Materia::getHoraFin(int &hora, int &min, QString dia) const{
    if (dias.find(dia) == dias.end()){
        hora=0;
        min=0;
    }
    else
        dias.find(dia)->getHoraFin(hora,min);
}

void Materia::getHoraInicio(int &hora, int &min, QString dia) const{
    if (dias.find(dia) == dias.end()){
        hora=0;
        min=0;
    }
    else
        dias.find(dia)->getHoraInicio(hora,min);

}

QList<QString> Materia::getDias()
{
    return dias.keys();
}


int Materia::getAnio() const
{
    return anio;
}

void Materia::setAnio(int value)
{
    anio = value;
}

int Materia::getCantHoras() const
{
    return cantHoras;
}

void Materia::borrarFranja(int inicio, int fin, QString dia)
{
    HorarioDia h= *dias.find(dia);
    int inicioMat,min, finMat;
    h.getHoraInicio(inicioMat,min);
    h.getHoraFin(finMat,min);
    if ( (inicio == inicioMat) && (fin == finMat) ){
        //mueve toda la materia
        dias.remove(dia);
    }
    else
        //muevo parte
        if ( (inicio > inicioMat) && (fin ==finMat) ){
            h.setHoraFin(inicio,0);
            dias.insert(dia,h);
        }
        else
            //muevo parte
            if ( (inicio == inicioMat) && (fin < finMat) ){
                h.setHoraIncio(fin,0);
                dias.insert(dia,h);
            }

}

void Materia::setCantHoras(int value)
{
    cantHoras = value;
}

void Materia::modificarCantHoras(int horas)
{
    this->cantHoras=cantHoras - horas;
}
