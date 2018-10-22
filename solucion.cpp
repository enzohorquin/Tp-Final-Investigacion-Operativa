#include "solucion.h"
#define cte_dias 5

Solucion::Solucion()
{
}

Solucion::Solucion(QString dia)
{
    this->dia=dia;
}

void Solucion::resolver()
{
    cantDias=dias.size();

    while (!dias.empty()){

        addRestricciones();
        materias.clear();
        conjunto.getMaterias(materias);
        cantVar=materias.size();
        cantRest=restricciones.size();
         M= new  Matriz(cantRest+1,cantVar+cantRest+2);
        this->cargarFuncionObjetivo();
        this->cargarMatrizIdentidad();
        this->cargarRestriccionesEnMatriz();
        QVector<QPair<int,int> > resultado= obtenerResultados();
        restricciones.clear();
        actualizarRestricciones(resultado,dias.front());//puedo unir con resolver desp ver
        dias.pop_front();


    }

 }

void Solucion::addMateria(Materia  & mat)
{

    conjunto.addMateria(mat);
}

void Solucion::addAula(Aula & aula)
{
    conjunto.addAula(aula);
}

void Solucion::addAnio()
{
    conjunto.addAnio();
}

void Solucion::getAnios(QList<QString> &lisAnios)
{
    conjunto.getAnios(lisAnios);
}

void Solucion::getMaterias(QList<Materia> &materias)
{
    conjunto.getMaterias(materias);
}

void Solucion::borrarAnio()
{
    conjunto.borrarAnio();
}

void Solucion::borrarMateria(int mat)
{
    conjunto.borrarMateria(mat);
}

void Solucion::borrarAula(QString aula){
    conjunto.borrarAula(aula);
}

int Solucion::getCantAnios()
{
    return conjunto.getCantAnios();
}

void Solucion::reiniciar()
{
    restricciones.clear();
    materias.clear();
    //puede haber problemas con la matriz
    conjunto.reiniciar();
}

void Solucion::addDia(QString dia)
{
    dias.push_back(dia);
}

bool Solucion::estaAula(QString aula)
{
    return ( conjunto.estaAula(aula) );
}

bool Solucion::estaAulaUsada(QString aula)
{
    return conjunto.estaAulaUsada(aula);
}

void Solucion::borrarMateriaAula(QString aula)
{
    conjunto.borrarMateriaAula(aula);
}

void Solucion::getAulas(QList<Aula> &aulas)
{
    conjunto.getAulas(aulas);
}

Aula Solucion::getAula(Aula &aula)
{
    QList<Aula> aulas;
    conjunto.getAulas(aulas);
    for (int i=0; i< aulas.size(); i++)
        if (aulas.at(i).getNombre()== aula.getNombre()){
            return aulas.at(i);}
    return aula;
}

void Solucion::mostrarConjunto()
{
    conjunto.imprimir();
}

void Solucion::setMateria(Materia materia)
{
    conjunto.setMateria(materia);
}
void Solucion::imprimir()
{

    QList<Materia> materias;
    QList<QString>nombres;
    conjunto.getMaterias(materias);
    QList<Materia>::iterator it=materias.begin();
    while (it!=materias.end()){
        nombres.push_back(it->getNombre());
        it++;
    }
    for (int i=0;i<restricciones.size();i++){
        qDebug()<<"restriccion: "<<i;
        restricciones.at(i)->imprimir(nombres);
    }
}

void Solucion::addRestricciones()
{
    //agrego las restricciones por misma aula
    QList<Aula> aulas;
    conjunto.getAulas(aulas);
    for (int i=0; i<aulas.size(); i++){
        Restriccion *r=new Restriccion(false,true,aulas.at(i),"0");// no interesa el año porque es por aula
        r->setValorInd(aulas.at(i).getCantHorasDisponibles(cantDias-dias.size())); //haciendo cantDias - dias.size me da el dia en que se encuentra
        restricciones.push_back(r);
    }

    //agrego las restricciones por mismo año
    QList<QString> anios;
    conjunto.getAnios(anios);
    for (int j=0; j<anios.size(); j++){
        Aula no_importa("no importa");
        Restriccion *r=new Restriccion( false, false,no_importa, anios.at(j) ); //no interesa el aula porque es por año
        r->setValorInd( conjunto.getCargaHoraria( j+1 )/dias.size() );
        restricciones.push_back(r);
    }

    //agrego las restricciones por hora
    QList<Materia> listMat;
    conjunto.getMaterias(listMat);
    QList<Materia>::iterator i=listMat.begin();
    int j=0;//pos en la lista
    while (i!=listMat.end()){
        Restriccion *r=new Restriccion( true, false, i->getAula(), QString::number(i->getAnio()) );//no interesa el aula porque es por año
        r->addVar(j);
        r->setValorInd(i->getCantHoras());
        restricciones.push_back(r);

        //modifico la restriccion de aula
        int pos=conjunto.posAula(i->getAula());
        Restriccion *restAula=restricciones.at(pos);
        restAula->addVar(j);

        //modifico la restriccion de año
        Aula noEsta("No existe");
        pos=conjunto.posAula(noEsta);//como no esta me devuelve el size
        Restriccion *restAnio=restricciones.at(pos+i->getAnio()-1);
        restAnio->addVar(j);

        i++;j++;
    }
    imprimir();//mostrar restricciones


}



//--------------------

void Solucion::actualizarTabla()
{

    int filaPivot = this->getFilaPivot();
    float valorPivot = this->getValorPivot();
    int varEntrante= this->getVariableEntraALaBase();

    for(int j=0;j<M->getCol();j++){
         float valor = M->get(filaPivot,j)/valorPivot;
         M->put(filaPivot,j,valor);

    }
    for(int i=0; i<M->getFila();i++){
        float AntElementoFilaEnColumnaPivote = M->get(i,varEntrante);
        for(int j=0; j<M->getCol();j++){
            if(i!=filaPivot){
                 float valor = M->get(i,j)- (AntElementoFilaEnColumnaPivote * M->get(filaPivot,j));
                 M->put(i,j,valor);
            }
        }
    }

}


int Solucion::getVariableEntraALaBase()
{
     float menorValor=10000;
     float filaFuncObjetivo = M->getFila()-1;
     int columnaSolucion=-99;
     for(int j=0; j<M->getCol()-2;j++){
         float valorActual=M->get(filaFuncObjetivo,j);
         if(valorActual<menorValor){
             menorValor=valorActual;
             columnaSolucion=j;
         }

     }

     return columnaSolucion;

}

int Solucion::getFilaPivot()
{
    int columnaPivot= this->getVariableEntraALaBase();
    int ultimaColumna= M->getCol()-1;
    float valorMinimo = 1000;
    int filaSolucion= -1;

    for(int i=0;i<cantRest;i++){
        float valorActual=M->get(i,ultimaColumna);
        if (M->get(i,columnaPivot)>0) //agregue el if porque encontre que no se divide si es neg
            valorActual  =  M->get(i,ultimaColumna)/M->get(i,columnaPivot);
        if(M->get(i,columnaPivot)!=0)
        if(valorActual>=CERO)
            if(valorActual<=valorMinimo){
                valorMinimo= valorActual;
                filaSolucion=i;
        }
    }

   return filaSolucion;

}
float Solucion::getValorPivot()
{
    return M->get(this->getFilaPivot(),this->getVariableEntraALaBase());

}

bool Solucion::cumpleParada()
{
  int maxFil = M->getFila()-1;

  for(int i=0; i<M->getCol()-1;i++){
      if(M->get(maxFil,i)< CERO )
          return false;
  }
  return true;

}
void Solucion::cargarRestriccionesEnMatriz()
{
  int ultimaCol= M->getCol()-1;


  for(int i= 0; i<restricciones.size(); i++){

    Restriccion * r = restricciones.at(i);

    for(int j=0; j<r->size();j++){
        int valor= r->getValor(j);
        M->put(i,valor,UNO);

    }
    M->put(i,ultimaCol,r->getValorInd());
    }
}
void Solucion::cargarFuncionObjetivo()
{
    int ultimaCol= M->getCol()-1;
    int ultimaFil= M->getFila()-1;


    for(int i=0; i<cantVar;i++){

        M->put(ultimaFil,i,-UNO);
    }
    for(int i=cantVar;i<ultimaCol-2;i++){
        M->put(ultimaFil,i,0);
    }
    M->put(ultimaFil,ultimaCol-1,0);
    M->put(ultimaFil,ultimaCol,0);
}

void Solucion::cargarMatrizIdentidad()
{
    for(int i=0; i < M->getFila()-1;i++) // Tiene que recorrer hasta la ante ultima Restriccion por que la ultima es la funcion Objetivo
        for(int j= cantVar; j<cantVar+cantRest+1;j++){
            if(j-cantVar==i)
                    M->put(i,j,1);
            else
                M->put(i,j,0);
        }
}

QVector<QPair<int, int> > Solucion::obtenerResultados()
{

    QVector<QPair<int,int> > lista_nueva;

    solucion();

    //verifico si hay infinitas soluciones
    int ultimaFil= M->getFila()-1;
    int ultimaCol= M->getCol()-1;
    bool infinitas =false;
    for (int i=0; i<cantVar; i++ )
        if (M->get(ultimaFil,i) == 0 )
            infinitas = true;
    int maxHoras = M->get(ultimaFil,ultimaCol);

    bool tuvo_resultado;
    int columnaSolucion = M->getCol()-1;
    for(int j=0;j<cantVar;j++){
        tuvo_resultado=false;
        for(int i=0;i<cantRest ;i++){
            if (M->get(i,j)== UNO) {
                if (infinitas && (restantesCero(i,j)) ){
                    QPair<int,int> Aux;
                    Aux.first= j;
                    if (M->get(i,columnaSolucion)<=maxHoras)
                        Aux.second=M->get(i,columnaSolucion);
                    else
                        Aux.second=maxHoras;
                    maxHoras= maxHoras - M->get(i,columnaSolucion);
                    lista_nueva.push_back(Aux);
                    tuvo_resultado=true;
                }
                else
                    if (restantesCero(i,j)){
                            QPair<int,int> Aux;
                            Aux.first= j;
                            Aux.second=M->get(i,columnaSolucion);
                            lista_nueva.push_back(Aux);
                            tuvo_resultado=true;
                    }
            }
        }

        if(!tuvo_resultado){
            QPair<int,int> Auxiliar;
            Auxiliar.first=j;
            Auxiliar.second=CERO;
            lista_nueva.push_back(Auxiliar);
        }

    }

    return lista_nueva;
}

void Solucion::solucion()
{
    while(!this->cumpleParada()){

        this->actualizarTabla();


    }

}

void Solucion::actualizarRestricciones(QVector<QPair<int,int> > resultado, QString dia)
{
    QList<QString> anios;
    conjunto.getAnios(anios);
    for (int a=1; a<=anios.size(); a++){
        for (int i=0; i<resultado.size(); i++){
            //solamente actualizo si es el aula y es de ese dia
            if ( (resultado.at(i).second != 0) && (conjunto.getAnioDeMat(resultado.at(i).first) == a  ) ){
                int horaInicio = conjunto.getInicio(dia, conjunto.getAulaDeMat(resultado.at(i).first) , conjunto.getAnioDeMat(resultado.at(i).first), resultado.at(i).second );
                conjunto.actualizarMateria(resultado.at(i).first,resultado.at(i).second, dia, horaInicio );
            }
        }
    }
}

bool Solucion::restantesCero(int ubicacionUno, int col){
    //me fijo si tiene ceros arriba y abajo
    for (int i=0; i< M->getFila()-2; i++ ){
        if (i!=ubicacionUno)
            if (M->get(i,col)!=0)
                return false;
    }
    return true;
}


