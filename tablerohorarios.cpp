#include "tablerohorarios.h"
#include "qdebug.h"

tableroHorarios::tableroHorarios() {
    inicializar();
}

void tableroHorarios::inicializar(){
    for (int i=0;i<29;i++)
        for (int j=0;j<7;j++)
            matriz[i][j]=0;
}

void tableroHorarios::getMateriasDia(QList<QString> & materiasDia, QString dia)
{
    int j = convertirDia(dia);
    for (int i=1; i<29; i++){
        if ( (matriz[i][j]!=0) && (!materiasDia.contains( materias.at(matriz[i][j]-1).getNombre() ) ) )
            materiasDia.push_back( materias.at(matriz[i][j]-1).getNombre() );
    }
}

void tableroHorarios::getMateriasDiaCompleta(QList<Materia> &materiasDia, QString dia )
{
    int j = convertirDia(dia);
    QList<int> posMaterias;
    for (int i=1; i<29; i++){
        if ( (matriz[i][j]!=0) && (!posMaterias.contains( matriz[i][j] ) ) ){
            materiasDia.push_back( materias.at(matriz[i][j]-1) );
            posMaterias.push_back(matriz[i][j]);
        }
    }
}

void tableroHorarios::getMaterias(QList<Materia> &materias)
{
    materias = this->materias;
}

void tableroHorarios::addMateria(Materia mat)
{
    materias.push_back(mat);
}

void tableroHorarios::setMateria(Materia materia)
{
    bool inserto = false;
    for (int i=0;i<materias.size(); i++)
        if ( materias.at(i).getNombre() == materia.getNombre() ){
            materias.removeAt(i);
            materias.insert(i,materia);
            inserto = true;
        }
    if (!inserto)
        materias.push_back(materia);

}

int tableroHorarios::convertirDia(QString dia)
{
    if (dia=="Lunes")
        return 1;
    if (dia=="Martes")
        return 2;
    if (dia=="Miercoles")
        return 3;
    if (dia=="Jueves")
        return 4;
    if (dia=="Viernes")
        return 5;
    if (dia=="Sabado")
        return 6;
}

void tableroHorarios::insertarCurso(Materia materia){
    materias.push_back(materia);
    int horaInicio; int mInicio;
    int horaFin; int mFin;
    QList<QString> dias =materia.getDias();
    //por cada dia
    foreach (QString s, dias){
        int d=convertirDia(s);
        materia.getHoraInicio(horaInicio,mInicio,s);
        materia.getHoraFin(horaFin,mFin,s);
        int inicio=(horaInicio-8)*2+1;
        if (mInicio == 30)
            inicio++;
        int fin=(horaFin-8)*2+1;
        if (mFin == 30)
            fin++;
        for (int i=inicio;i<fin;i++)
            if (matriz[i][d]==0)
                matriz[i][d]=materias.size();
    }

}

int tableroHorarios::getValor(int i, int j){
    return matriz[i][j];
}

QString tableroHorarios::getNombre(int i){
    Materia res=materias.at(i-1);
    if (i!=0 && !materias.isEmpty())
        return ( res.getNombre() );
}

Aula tableroHorarios::getAula(int i)
{
    Materia res=materias.at(i-1);
    if (i!=0 && !materias.isEmpty())
        return ( res.getAula() );
}

int tableroHorarios::getAnio(int i)
{
    Materia res=materias.at(i-1);
    if (i!=0 && !materias.isEmpty())
        return ( res.getAnio() );
}
