#include "horariodia.h"

HorarioDia::HorarioDia()
{
    horaInicio=0;
    horaFin=0;
    minutoFin=0;
    minutoInicio=0;
}

void HorarioDia::getHoraInicio(int &hora, int &min) const
{
    hora = horaInicio;
    min = minutoInicio;
}

void HorarioDia::getHoraFin(int &hora, int &min) const
{
    hora = horaFin;
    min = minutoFin;
}

QString HorarioDia::getDia() const
{
    return this->dia;
}



void HorarioDia::setHoraIncio(int hora, int min)
{
    horaInicio = hora;
    minutoInicio = min;
}

void HorarioDia::setHoraFin(int hora, int min)
{
    horaFin = hora;
    minutoFin = min;
}

void HorarioDia::setDia(QString d)
{
    dia = d.toUpper();
}

int HorarioDia::getCantidadHoras() const
{
    int horas = (horaFin - horaInicio);
    return horas;
}

bool HorarioDia::perteneceFranja(HorarioDia h)
{
    int horaI,horaF,minI,minF;
    h.getHoraInicio(horaI,minI);
    h.getHoraFin(horaF,minF);


    return ( ( (horaInicio==horaI && minutoInicio<=minI)||(horaInicio < horaI) )  && ( (horaFin > horaF ) || (horaFin == horaF && minutoFin >= minF) ) ) ;
}

bool HorarioDia::operator <(HorarioDia h)
{
    int horaI,horaF,minI,minF;
    h.getHoraInicio(horaI,minI);
    h.getHoraFin(horaF,minF);

    return (( this->horaInicio < horaI ) || (horaInicio==horaI && minutoInicio < minI));
}

bool HorarioDia::operator ==(HorarioDia h)
{
    int horaI,horaF,minI,minF;
    h.getHoraInicio(horaI,minI);
    h.getHoraFin(horaF,minF);

    return ((horaInicio==horaI  && minutoInicio==minI && horaFin == horaF && minutoFin==minF));
}

QString HorarioDia::toString()
{
    QString out =  QString::number(horaInicio)+":"+QString::number(minutoInicio) + " - "+ QString::number(horaFin)+":"+QString::number(minutoFin);
    return out;
}
