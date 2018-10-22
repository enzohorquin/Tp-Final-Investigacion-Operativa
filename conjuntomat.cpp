#include "conjuntomat.h"
#include "QDebug"
#include <string>


ConjuntoMat::ConjuntoMat()
{
}

void ConjuntoMat::addAula(Aula & aula){
    aulas.push_back(aula);
}

void ConjuntoMat::getAulas(QList<Aula> &aulas){
    aulas=this->aulas;
}

 void ConjuntoMat::addMateria(Materia & materia){
    materias.push_back(materia);
 }

 void ConjuntoMat::getMaterias(QList<Materia>&materias){
     materias=this->materias;
 }

 void ConjuntoMat::getAnios(QList<QString> &listAnios)
 {
     for (int i=0;i<anios.size();i++){
            listAnios.push_back(QString::number(anios.at(i)));
     }
 }

 int ConjuntoMat::getCargaHoraria(int anio)
 {
     int suma=0;
     QList<Materia>::iterator it=materias.begin();
     while (it!=materias.end()){
         if (it->getAnio()==anio)
             suma=suma+it->getCantHoras();
         it++;
     }
     return suma;
 }

 void ConjuntoMat::borrarMateria(int i){
    materias.removeAt(i);
 }

 void ConjuntoMat::borrarAula(QString i)
  {
      for(int j = 0; j<aulas.size();j++){
          if(aulas.at(j).getNombre()==i)
              aulas.removeAt(j);
      }
  }
 void ConjuntoMat::borrarAnio()
 {
     anios.pop_back();
 }

 void ConjuntoMat::addAnio()
 {
     anios.push_back(anios.size()+1);
 }

 int ConjuntoMat::posAula(Aula aula)
 {
     for (int i=0;i<aulas.size();i++)
         if (aulas.at(i).getNombre()==aula.getNombre())
             return i;
     return aulas.size();
 }

 int ConjuntoMat::getCantAnios()
 {
     return anios.size();
 }

 void ConjuntoMat::reiniciar()
 {
     materias.clear();
     aulas.clear();
     anios.clear();
 }

 bool ConjuntoMat::estaAula(QString aula)
 {
     for (int i=0; i<aulas.size(); i++)
         if (aulas.at(i).getNombre()==aula)
             return true;
     return false;
 }

 bool ConjuntoMat::estaAulaUsada(QString aula)
 {
     QList<Materia>::iterator it=materias.begin();
     while (it!=materias.end()){
         if (it->getAula().getNombre()==aula)
             return true;
         it++;
     }
     return false;
 }

 void ConjuntoMat::borrarMateriaAula(QString aula)
 {
     QList<Materia>::iterator it=materias.begin();
     QList<Materia>::iterator borrar;
     while (it!=materias.end()){
         borrar=it;
         it++;
         if (borrar->getAula().getNombre()==aula)
             materias.erase(borrar);
     }
 }

 void ConjuntoMat::actualizarMateria(int pos, int horas, QString dia, int horaInicio)
 {
     QList<Materia>::iterator it=materias.begin();
     int i=0;
     while (i<pos){
         i++;
         it++;
     }

     HorarioDia franja ;
     franja.setDia(dia);
     franja.setHoraIncio(horaInicio,00);
     franja.setHoraFin(horaInicio+horas,00);
     Aula aux = it->getAula();
     Aula aux2;

     for(int i =0 ; i<aulas.size();i++){
         Aula auxiliar = aulas.at(i);
         if(auxiliar.getNombre()==aux.getNombre()){
            aux2 = auxiliar;
         }



     }



     while (!aux2.perteneceFranja(franja)){
         horaInicio=horaInicio + 1;
         franja.setHoraIncio(horaInicio,00);
         franja.setHoraFin(horaInicio+horas,00);


     }

    aux2.ocuparAula(franja);
    it->setAula(aux2);

     for(int i =0 ; i<aulas.size();i++){
         Aula auxiliar = aulas.at(i);
         if(auxiliar.getNombre()==aux2.getNombre()){
             aulas.removeAt(i);
             aulas.insert(i,aux2);
         }



     }

      //au.imprimir();

     //ocuparAula(it->getAula().getNombre(), franja);
     it->modificarCantHoras(horas);
     it->setDia(dia);
     it->setHoraInicio(horaInicio,0,dia);
     it->setHoraFin(horaInicio+horas,0,dia);
 }

 int ConjuntoMat::getAnioDeMat(int materia)
 {
     return materias.at(materia).getAnio();
 }


 Aula ConjuntoMat::getAulaDeMat(int materia)
 {
     return materias.at(materia).getAula();
 }

 int ConjuntoMat::getInicio(QString dia, Aula aula, int anio, int cantHoras)
 {
     QVector<bool> horarios(16);
     for (int i=0; i<horarios.size(); i++)
         horarios[i] = 0;

     for (int i=0; i< materias.size(); i++){
         if ( (materias.at(i).getAula().getNombre()==aula.getNombre()) || ( materias.at(i).getAnio()==anio )){
             int horaI;
             int horaF;
             int minutos;
             materias.at(i).getHoraInicio(horaI,minutos,dia);
             materias.at(i).getHoraFin(horaF,minutos,dia);
             if ( (horaI !=0) && ( horaF != 0 ) && (cantHoras!=0) )
                for (int j=horaI; j<horaF; j++)
                    horarios[j-cte_inicio_dia]=true;
        }
     }

     int libresSeguidas= 0;
    qDebug()<<horarios;
     for (int i=0; i<horarios.size(); i++){
         if ( horarios[i] == true )
             libresSeguidas = 0;
         else
             libresSeguidas++;
         if (libresSeguidas == cantHoras){
             qDebug()<<"arranca en:"<<i+cte_inicio_dia;
             return i-cantHoras+cte_inicio_dia+1;
         }

     }
     return 17;//no tendria que llegar aca porque siempre hay solucion
 }

 void ConjuntoMat::imprimir()
 {
     qDebug()<<"MOSTRANDO  AULAS";
     for(int i = 0; i < aulas.size();i++){
         Aula A = aulas.at(i);
        qDebug()<< A.getNombre();
        A.imprimir();
     }

     for(int i = 0; i< materias.size();i++){
         Aula A = materias.at(i).getAula();
         qDebug()<<A.getNombre();
         A.imprimir();

     }
 }

 void ConjuntoMat::ocuparAula(QString nombreAula, HorarioDia franja)
 {
    foreach (Aula aula, aulas){
        if (aula.getNombre() == nombreAula){
            aula.ocuparAula(franja);
        }
    }
 }

 void ConjuntoMat::setMateria(Materia materia)
 {
//     QList<Materia>::iterator it = materias.begin();
//     QList<Materia>::iterator itBorrado = materias.begin();
//     while (it != materias.end()){
//         if ( it->getNombre() == materia.getNombre() ){
//            itBorrado = materias.erase(it);
//            materias.insert(itBorrado, materia);
//         }
//     }
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
