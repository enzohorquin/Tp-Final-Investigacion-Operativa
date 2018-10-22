#include "restriccion.h"

Restriccion::Restriccion()
{

}

Restriccion::Restriccion(bool horas, bool porAula, Aula aula, QString anio)
{
    this->anio=anio;
    this->aula=aula;
    this->porAula=porAula;
    this->porCantHoras=horas;
}


QString Restriccion::getAnio() const
{
    return anio;
}

void Restriccion::setAnio(const QString &value)
{
    anio = value;
}

Aula Restriccion::getAula()
{
    return aula;
}

void Restriccion::setAula(const QString &value)
{
    aula = value;
}

void Restriccion::addVar(int m)
{
    variables.push_back(m);//borar el parametro mat desp
}

int Restriccion::getValorInd() const
{
    return valorInd;
}

int Restriccion::size()const
{
    return variables.size();
}

int Restriccion::getValor(int i) const
{
    return variables.at(i);
}

void Restriccion::setValorInd(int value)
{
    valorInd = value;
}

bool Restriccion::getPorCantHoras() const
{
    return porCantHoras;
}

void Restriccion::setPorCantHoras(bool value)
{
    porCantHoras = value;
}

bool Restriccion::getPorAula()
{
    return porAula;
}
bool Restriccion::estaMateria(int m)
{
    for (int i=0;i<variables.size();i++)
        if (variables.at(i)==m)
            return true;
    return false;
}

void Restriccion::imprimir(QList<QString> &materias)
{

    QString text=" ";
    for (int i=0;i<variables.size();i++){
        text.append(materias.at(variables.at(i)));
        text.append("<= ");
        text.append(QString::number(valorInd));
        if (i<variables.size()-1)
        text.append(" + ");
    }
    if (porAula){
        text.append("    - ");
        text.append(aula.getNombre());
    }
    else
        if (porCantHoras)
            text.append("    - por hora");
        else{
            text.append("    - por año");
            text.append(anio);}
    qDebug()<<text;

}
