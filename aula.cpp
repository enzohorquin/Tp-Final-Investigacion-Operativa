#include "aula.h"
#include "qdebug.h"
#define OCHO 8
#define VEINTIDOS 22
Aula::Aula(QString nombre)
{
this->nombre=nombre;
for(int i=0; i<6;i++){

    QList<HorarioDia> dias;
    HorarioDia defaul;
    defaul.setHoraIncio(OCHO,00);
    defaul.setHoraFin(VEINTIDOS,00);
    dias.append(defaul);
    this->franjaDisponible.append(dias);

}
}

Aula::Aula()
{

}

void Aula::getFranja(int id,QList<HorarioDia> & h){
    h= franjaDisponible.at(id);

}

QString Aula::getNombre() const
{
    return nombre;
}

float Aula::getCantHorasDisponibles(int dia) const
{
    QList<HorarioDia> franjasDia = franjaDisponible.at(dia);
    int horas =0;
    for(int i=0; i < franjasDia.size();i++){
        horas+=franjasDia.at(i).getCantidadHoras();
    }
    qDebug()<<horas;
    return horas;
}

bool Aula::perteneceFranja(HorarioDia hora)
{
    int id = this->convertirDia(hora.getDia());

    QList<HorarioDia> franjasDia = franjaDisponible.at(id);

    for(int i=0;i<franjasDia.size();i++){
        HorarioDia aux = franjasDia.at(i);

        if(aux.perteneceFranja(hora))
            return true;
}
    return false;
}

bool Aula::ocuparAula(HorarioDia hora)
{
    int id = convertirDia(hora.getDia());
    QList<HorarioDia> franjasDia = franjaDisponible.at(id);

    franjaDisponible.removeAt(id);

    for(int i=0;i<franjasDia.size();i++){
        HorarioDia aux = franjasDia.at(i);

        if(aux.perteneceFranja(hora)){

            QList<HorarioDia> auxiliar = generarFranja(aux,hora);
            franjasDia.removeAt(i);
            for(int j= 0; j<auxiliar.size();j++){
                    franjasDia.insert(i+j,auxiliar.at(j));

            }
            franjaDisponible.insert(id,franjasDia);
            qDebug()<<"cantidad de horas adentro:"<<getCantHorasDisponibles(id);
            this->imprimir();qDebug()<<"IMPRIMIENDO AULA DESDE OCUPAR ";
            return true;
        }
    }
    return false;
}
int Aula::convertirDia(QString dia)
{
    if(dia=="LUNES")
        return 0;
    else
        if(dia=="MARTES")
            return 1;
        else
            if(dia=="MIERCOLES")
               return 2;
            else
                if(dia=="JUEVES")
                    return 3;
                   else
                    if(dia=="VIERNES")
                            return 4;
                        else
                            return 5;



}

void Aula::imprimir()
{
    for(int i = 0; i<franjaDisponible.size();i++){
        QList<HorarioDia> auxiliar = franjaDisponible.at(i);
        qDebug()<< "DIA "<< i;
        for(int j =0; j<auxiliar.size();j++){
            HorarioDia a = auxiliar.at(j);
            qDebug()<<a.toString();
        }



    }

}



bool Aula::desocuparAula(HorarioDia hora,HorarioDia horaReemplazada)
{
    if(this->perteneceFranja(hora)){

        QList<HorarioDia> horas_disponibles ;
        this->getFranja(this->convertirDia(horaReemplazada.getDia()),horas_disponibles);
          bool inserto = false;

          for(int i =0; i<horas_disponibles.size() && !inserto;i++){
                  HorarioDia disp = horas_disponibles.at(i);
                  int hi,mi,hf,mf;
                  int hf1,mf1;
                  int hi1,mi1;
                  disp.getHoraInicio(hi,mi);
                  disp.getHoraFin(hf,mf);
                  horaReemplazada.getHoraFin(hf1,mf1);
                  horaReemplazada.getHoraInicio(hi1,mi1);

                  if((horaReemplazada < disp) && (hi == hf1 && mi==mf1) ){ // Busco que sea la posicion correcta que tenga que juntar
                       qDebug()<<"ENTRO PAPEL";

                        HorarioDia nuevo;
                        nuevo.setDia(horaReemplazada.getDia());
                        nuevo.setHoraIncio(hi1,mi1);
                        nuevo.setHoraFin(hf,mf);
                        qDebug()<<nuevo.toString();
                        qDebug()<<disp.toString();
                        horas_disponibles.removeAt(i);
                        horas_disponibles.insert(i,nuevo);

                        inserto = true ;

                  }
                  else
                      if(horaReemplazada < disp ){

                          HorarioDia nuevo;
                          nuevo.setDia(horaReemplazada.getDia());
                          nuevo.setHoraIncio(hi1,mi1);
                          nuevo.setHoraFin(hf1,mf1);
                          qDebug()<<nuevo.toString();
                          qDebug()<<disp.toString();
                          horas_disponibles.insert(i,nuevo);

                          inserto = true ;

                      }

          }
          franjaDisponible.removeAt(this->convertirDia(horaReemplazada.getDia()));
          franjaDisponible.insert(this->convertirDia(horaReemplazada.getDia()),horas_disponibles);
          this->ocuparAula(hora);
          return true;
 }
    else return false;
}

QList<HorarioDia> Aula::generarFranja(HorarioDia h1, HorarioDia h2) /*h1 corresponde al horario que tengo disponible y h2 el horario que quiero ocupar.*/
{                                                                   //Unicamente se va a entrar en este metodo si h2 esta incluido en h1

    QList<HorarioDia> resultado ;

    HorarioDia horario1,horario2;
    int horaInicio1,horaInicio2,minI1,minI2,horaFin1,horaFin2,minF1,minF2;


    int horaResultadoI1,horaResultadoI2,horaResultadoF1,horaResultadoF2,minResultadoI1,minResultadoI2,minResultadoF1,minResultadoF2;

    h1.getHoraInicio(horaInicio1,minI1);
    h1.getHoraFin(horaFin1,minF1);
    h2.getHoraInicio(horaInicio2,minI2);
    h2.getHoraFin(horaFin2,minF2);

    if(horaInicio1==horaInicio2 && horaFin1==horaFin2 && minI1==minI2 && minF1==minF2)
        return resultado; // El caso que tenga disponible por ejemplo de 8:00 a 12:00 y lo quiero ocupar de 8:00 a 12:00, retornaria la lista vacia por que
                          // No queda ninguna franja horaria disponible.
    else
        if(horaInicio1==horaInicio2 && minI1==minI2)  {
            horaResultadoI2 = horaFin2;
            minResultadoI2= minF2;                  // Caso que tenga disponible por ejemplo de 8:00 a 12:00 y quiera ocuparlo desde la misma hora de inicio 8:00 a xx:xx.
            horaResultadoF2=horaFin1;
            minResultadoF2=minF1;

           horario2.setDia(h1.getDia());
           horario2.setHoraIncio(horaResultadoI2,minResultadoI2);
           horario2.setHoraFin(horaResultadoF2,minResultadoF2);
           resultado.push_back(horario2);
           return resultado;



        }
    else
          if(horaFin2==horaFin1 && minF2==minF1){   // caso que tenga disponible por ejemplo de  8:00 a 12:00 y quiera ocuparlo de xx:xx a 12:00, tendria que generar una franja sola disponible
            horaResultadoF1 = horaInicio2;
            minResultadoF1  =  minI2;

            horaResultadoI1 = horaInicio1;
            minResultadoI1= minI1;

            horario1.setDia(h1.getDia());
            horario1.setHoraIncio(horaResultadoI1,minResultadoI1);
            horario1.setHoraFin(horaResultadoF1,minResultadoF1);
            resultado.push_back(horario1);
            return resultado;
          }

       else
             if( (horaInicio2 > horaInicio1 && horaFin2 < horaFin1) || (horaInicio1==horaInicio2 && minI1 < minI2) ){ // Tenga disponible de 8:00 a 13:00 y quiera ocupar de 9:00 a 12:00. tengo que generar dos franjas disponibles 8:00 a 9:00 y 12:00 a 13:00

                 horaResultadoI1= horaInicio1;
                 minResultadoI1=minI1;

                 horaResultadoF1=horaInicio2;
                 minResultadoF1=minI2;


                 horario1.setDia(h1.getDia());
                 horario1.setHoraIncio(horaResultadoI1,minResultadoI1);
                 horario1.setHoraFin(horaResultadoF1,minResultadoF1);

                 resultado.push_back(horario1);

                 horaResultadoI2=horaFin2;
                 minResultadoI2=minF2;

                 horaResultadoF2=horaFin1;
                 minResultadoF2=minF1;

                 horario2.setDia(h1.getDia());
                 horario2.setHoraIncio(horaResultadoI2,minResultadoI2);
                 horario2.setHoraFin(horaResultadoF2,minResultadoF2);
                 resultado.push_back(horario2);
                 return resultado;

             }


}

void Aula::setFranja(HorarioDia &hora)
{
    int id = this->convertirDia(hora.getDia());

    QList<HorarioDia> aux = franjaDisponible.at(id);

    aux.clear();      // Elimina cualquier franja horaria que haya anterior.
    aux.append(hora); // Agrega a ese dia una nueva franja horaria.
    franjaDisponible.removeAt(id);
    franjaDisponible.insert(id,aux);

    qDebug()<< "CAMBIANDO HORA DE AULA"<< hora.toString() << " EN EL DIA "<< hora.getDia();
}
