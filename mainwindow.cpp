#include "form.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QFile>
#include <QLabel>
#include <qpointer.h>
#include <QtXml/qdom.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manual=false;
    ui->modoAuto->setVisible(true);
    ui->modoManual->setVisible(false);
    mostrarVentanas(false);
    nuevaVentana = new NuevaVentana();
    ui->tabWidget->setTabText(0,"Solucion");
    mostrarInicio(true);
    ui->mostrarAulas->setVisible(false);
    ui->mostrarHorarios->setVisible(false);
    ui->botonResolver->setVisible(false);
    }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addMateria(Materia mat)
{
    //mostrar materia
    mostrarMateria(mat);

    //agregar a conjunto
    sol.addMateria(mat);
}

bool MainWindow::perteneceAula(QString aula)
{
    //devuelve true si la agrega
    if ( !sol.estaAula(aula) ){
        //mostrar aula
        ui->listAulas->addItem(aula);

        return true;
    }
    return false;
}

void MainWindow::addAnio(QString anio)
{
    int cantAnios = this->sol.getCantAnios();
    anio.remove(0,1);
    while (anio.at(0)!=' '){
        anio.remove(0,1);
    }
    anio.remove(0,1);
    int a = anio.toInt();
    qDebug()<<a<<anio;
    if (a>cantAnios){
        on_insertarAnio_clicked();
    }

}

void MainWindow::getAnios(QList<QString> &anios)
{
    sol.getAnios(anios);
}

void MainWindow::addAula(Aula & a)
{

    sol.addAula(a);
}

void MainWindow::getMaterias(QList<Materia> &materias)
{
    sol.getMaterias(materias);
}

Solucion MainWindow::getSolucion()
{
    return sol;
}

void MainWindow::setMateria(Materia materia)
{
    sol.setMateria(materia);
}

void MainWindow::mostrarHorarios()
{
    on_mostrarHorarios_clicked();
}

void MainWindow::mostrarAulas()
{
    on_mostrarAulas_clicked();
}


void MainWindow::on_modoManual_clicked()
{
    manual=true;
    mostrarVentanas(true);
    mostrarInicio(false);
    ui->modoAuto->setVisible(false);
    ui->modoManual->setVisible(false);
    nuevaVentana->setMainWindow(this);
    nuevaVentana->setManual(true);
}

void MainWindow::on_insertarMateria_clicked()
{
    //verificar que hayan ingresado aulas y años
    QList<QString> aux;
    sol.getAnios(aux);
    if ( sol.getCantAnios()==0 )
        QMessageBox::warning(this,"Error al ingresar.","Antes debe ingresar años.");
    else{
        if ( ui->listAulas->count()==0 )
            QMessageBox::warning(this,"Error al ingresar.","Antes debe ingresar aulas.");
        else{
            if (manual==true){
                nuevaVentana->setInsAula(false);
                nuevaVentana->mostrarInsMatManual();
                nuevaVentana->show();

            }
            else{
                nuevaVentana->setInsAula(false);
                nuevaVentana->mostrarInsMat();
                nuevaVentana->show();
            }
        }
    }
}

void MainWindow::on_insertarAula_clicked()
{
    nuevaVentana->setInsAula(true);
    nuevaVentana->mostrarInsAula();
    nuevaVentana->show();

}

void MainWindow::on_mostrarHorarios_clicked()
{
    //mostrar horarios
    //mostrarVentanas(false);
    int cant=sol.getCantAnios();
    QList<Materia> materias;
    sol.getMaterias(materias);
    //borrar tab viejos
    for (int i=0; i<=ui->tabWidget->count(); i++ )
        on_tabWidget_tabCloseRequested(1);
    for (int i=1; i<=cant; i++ ){
        QPointer<Form> nuevo = new Form;
        Form *aux=nuevo.data();
        aux->setMainWindow(this);
        aux->setAnio(i);
        aux->cambiarEstado(true);
        aux->mostrarHorarios(materias);
        QString nombre("Año ");
        QString pos = QString::number(i);
        nombre.append(pos);
        ui->tabWidget->addTab(nuevo,nombre);
        ui->tabWidget->setCurrentIndex(i);
    }
}

void MainWindow::on_modoAuto_clicked()
{
    //settear modo auto
    manual=false;
    nuevaVentana->setMainWindow(this);
    nuevaVentana->setManual(false);
    //parte grafica
    mostrarVentanas(true);
    mostrarInicio(false);
    ui->modoAuto->setVisible(false);
    ui->modoManual->setVisible(false);
    ui->mostrarAulas->setVisible(false);
    ui->mostrarHorarios->setVisible(false);
    ui->botonResolver->setVisible(true);
}

void MainWindow::on_borrar_clicked()
{
    sol.borrarMateria(ui->listMaterias->currentRow());
    ui->listMaterias->clear();
    QList<Materia> materias;
    sol.getMaterias(materias);
    QList<Materia>::iterator it=materias.begin();
    while (it!=materias.end()){
        mostrarMateria(*it);
        it++;
    }
}


void MainWindow::resolver(){
    sol.resolver();//creo que hay que sacar el parametro
}

void MainWindow::mostrarInicio(bool valor)
{
    ui->modoAuto->setVisible(valor);
    ui->ltitulo->setVisible(valor);
    ui->lIcono->setVisible(valor);
}

void MainWindow::mostrarMateria(Materia materia)
{   qDebug()<<materia.getNombre()<<"ENTRO MATERIA EN MOSTRAR MATERIA";
    QString text=materia.getNombre();
    text.append(" - ");
    text.append(QString::number(materia.getCantHoras() ) );
    text.append("H - ");
    qDebug()<<materia.getAula().getNombre()<<"NOMBRE MATEIRA";
    text.append( materia.getAula().getNombre() );
    text.append(" - Año ");
    text.append( QString::number( materia.getAnio() ) );
    ui->listMaterias->addItem(text);
}

void MainWindow::separarDatos(QString line)
{
    QString nombre ="";

    while(line.at(0)!= '-'){
        nombre.append(line.at(0));
        line.remove(0,1);
    }

    line.remove(0,1);
    line.remove(0,1);
    nombre.remove(nombre.size()-1,1);
    //Ya tenemos nombre materia



    QString horas="";
    int h=-1;
    while(line.at(0)!= 'H'){
        horas.append(line.at(0));
        line.remove(0,1);
    }

    h=horas.toInt();
    line.remove(0,1);
    line.remove(0,1);
    line.remove(0,1);
    line.remove(0,1);

    // Ya tenemos la cantidad de horas

    QString aula ="";
    while(line.at(0)!= '-') {
        aula.append(line.at(0));
        line.remove(0,1);
    }

    aula.remove(aula.size()-1,1);

    line.remove(0,1);
    line.remove(0,1);

    QString anio =line;

    while (line.at(0)!=' '){
        line.remove(0,1);
    }
    line.remove(0,1);
    int a = line.toInt();

    this->addAnio(anio);

    QList<Aula> lista_aulas ;
    sol.getAulas(lista_aulas);
    bool inserto = false;



    if(sol.estaAula(aula.toLower())){

         for(int i = 0 ; i < lista_aulas.size() && !inserto; i++){

                Aula au = lista_aulas.at(i);
                if(au.getNombre()==aula.toLower()){
                    Materia materia(nombre,au,a,h);
                    addMateria(materia);
                    inserto = true ;




                }
          }

    }
    else {

        Aula au = lista_aulas.at(0);
        Materia materia(nombre,au,a,h);
        this->addMateria(materia);
         QMessageBox::warning(this,"Error al ingresar materia : " + materia.getNombre(),"A la materia :" + materia.getNombre()+" se le asigno: " +au.getNombre());

    }



   }


void MainWindow::separarAulas(QString line)
{
    QString nombreAula;
    while(line.at(0)!='-'){
        nombreAula.append(line.at(0));
        line.remove(0,1);
    }
    nombreAula.remove(nombreAula.size()-1,1);

    line.remove(0,1);
    line.remove(0,1);

    QString hi;

    if(line.at(1)!=':'){
        hi = line.at(0);
        hi+= line.at(1);
        line.remove(0,1);
        line.remove(0,1);
        line.remove(0,1);

   }
   else
   {
       hi=line.at(0);
       line.remove(0,1);
       line.remove(0,1);
   }
    int horaI = hi.toInt();


    QString mi = line.at(0);
    int minI = mi.toInt();


    if(minI == 3)
        minI=30;

   while(line.at(0)!='-')
       line.remove(0,1);

   line.remove(0,1);
   line.remove(0,1);

   QString hf;
   if(line.at(1)!=':'){
       hf = line.at(0);
       hf+= line.at(1);
       line.remove(0,1);
       line.remove(0,1);
       line.remove(0,1);

  }
  else
  {
      hf=line.at(0);
      line.remove(0,1);
      line.remove(0,1);
  }
   int horaF = hf.toInt();



   QString mf = line.at(0);
   int minF = mf.toInt();

   if(minF == 3)
       minF=30;

   QString dia;

   while(line.at(0)!='-')
       line.remove(0,1);

    line.remove(0,1);
    line.remove(0,1);

     line.append(" ");
    while(line.at(0) !=' '){
        dia.append(line.at(0));
        line.remove(0,1);
    }
        HorarioDia franja_disp;
        franja_disp.setDia(dia);

        franja_disp.setHoraIncio(horaI,minI);
        franja_disp.setHoraFin(horaF,minF);

      if(sol.estaAula(nombreAula.toLower())) {

         QList<Aula> listaAulas;
         sol.getAulas(listaAulas);
         for(int i =0;i<listaAulas.size();i++){
             Aula au=  listaAulas.at(i);
            sol.borrarAula(au.getNombre());
             if(au.getNombre()==nombreAula.toLower()){

                au.setFranja(franja_disp);
             }

            sol.addAula(au);

         }

      }
      else
      {
          Aula nuevaAula(nombreAula.toLower());
          ui->listAulas->addItem(nombreAula.toLower());
          nuevaAula.setFranja(franja_disp);
          this->addAula(nuevaAula);
           nuevaVentana->addAula(nuevaAula);


      }


}

void MainWindow::on_actionAutom_tico_triggered()
{
    on_modoAuto_clicked();
}

void MainWindow::on_actionManual_triggered()
{
    on_modoManual_clicked();
}

void MainWindow::on_insertarAnio_clicked()
{
    sol.addAnio();
    QList<QString> lisAnios;
    sol.getAnios(lisAnios);
    ui->listAnios->addItem(lisAnios.back() );
}

void MainWindow::on_borrar_anio_clicked()
{
    //borrar de la parte grafica
    int aux=ui->listAnios->count();
    ui->listAnios->takeItem(aux-1);
    sol.borrarAnio();
}

void MainWindow::mostrarVentanas(bool valor)
{
    ui->insertarAula->setVisible(valor);
    ui->insertarMateria->setVisible(valor);
    ui->insertarAnio->setVisible(valor);
    ui->borrar_aula->setVisible(valor);
    ui->borrar->setVisible(valor);
    ui->borrar_anio->setVisible(valor);
    ui->listAnios->setVisible(valor);
    ui->listAulas->setVisible(valor);
    ui->listMaterias->setVisible(valor);
    ui->lList->setVisible(valor);
    ui->lList_anios->setVisible(valor);
    ui->lList_aulas->setVisible(valor);
    ui->mostrarHorarios->setVisible(valor);
    //check dias solo en automatico
    if (manual==false){
        ui->checkLunes->setVisible(valor);
        ui->checkMartes->setVisible(valor);
        ui->checkMiercoles->setVisible(valor);
        ui->checkJueves->setVisible(valor);
        ui->checkViernes->setVisible(valor);
        ui->checkSabado->setVisible(valor);
        ui->mostrarAulas->setVisible(valor);
    }
}

void MainWindow::on_actionNuevo_triggered()
{
    mostrarInicio(true);
    mostrarVentanas(false);
    delete nuevaVentana;
    sol.reiniciar();
    nuevaVentana = new NuevaVentana();
    ui->listAnios->clear();
    ui->listAulas->clear();
    ui->listMaterias->clear();
    ui->mostrarAulas->setVisible(false);
    ui->mostrarHorarios->setVisible(false);
    ui->botonResolver->setVisible(false);
    for (int i=0; i<=ui->tabWidget->count(); i++ )
        on_tabWidget_tabCloseRequested(1);

}


void MainWindow::on_borrar_aula_clicked()
{
    if ((ui->listAulas->currentItem()!=NULL)) {
        if ( sol.estaAulaUsada( ui->listAulas->currentItem()->text() ) ){
            QMessageBox::StandardButton resBtn = QMessageBox::question(this,"Aula asignada","El aula fue asignada a una materia.Se borraran las materias que utilicen dicha aula ¿Desea continuar ?",QMessageBox::Yes|QMessageBox::No);
            if (resBtn == QMessageBox::Yes){
                sol.borrarMateriaAula(ui->listAulas->currentItem()->text());
                ui->listMaterias->clear();
                QList<Materia> materias;
                sol.getMaterias(materias);
                QList<Materia>::iterator it=materias.begin();
                while (it!=materias.end()){
                    mostrarMateria(*it);
                    it++;
                }
            }
        }
        sol.borrarAula(ui->listAulas->currentItem()->text());
        ui->listAulas->takeItem(ui->listAulas->row(ui->listAulas->currentItem()));
    }

}


void MainWindow::on_mostrarAulas_clicked()
{
    QList<Aula> aulas;
    sol.getAulas(aulas);
    QList<Materia> materias;
    sol.getMaterias(materias);
    //borrar tab viejos
    for (int i=0; i<=ui->tabWidget->count(); i++ )
        on_tabWidget_tabCloseRequested(1);

    for (int i=1; i<=aulas.size(); i++ ){
        QPointer<Form> nuevo = new Form;
        Form *aux=nuevo.data();
        aux->setMainWindow(this);
        aux->cambiarEstado(false);
        aux->mostrarHorariosAula(materias,aulas.at(i-1).getNombre());
        ui->tabWidget->addTab(nuevo,aulas.at(i-1).getNombre());
        ui->tabWidget->setCurrentIndex(i);
    }

}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (index != 0)
        ui->tabWidget->removeTab(index);
}

void MainWindow::on_actionGuardar_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Guardar archivo",QStandardPaths::locate(QStandardPaths::DesktopLocation,""),"TXT (*.txt);;Todos los archivos (*.*)");

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    if(file.isOpen()){
        QTextStream text(&file);
       for (int i=0; i< ui->listMaterias->count(); i++){
            text << ui->listMaterias->item(i)->text()<< "\n";
        }
        file.close();
    }

}

void MainWindow::on_actionAbrir_triggered()
{
    if(this->getCantidadAulas()==0){
           QMessageBox::warning(0,"Error"," Debe cargar las aulas primero ");
        }
        else {

        this->on_modoAuto_clicked();
        //abrir archivo
        QString path1 = "C:\\Users\\enzo\\Documents\\InvestigacionOperativa\\Archivos";

        QString path = QFileDialog::getOpenFileName(this,"Cargar materias",path1,"*.txt");
        if(!path.isEmpty()){
            QFile file( path );
            if (!file.open(QIODevice::ReadOnly))
                QMessageBox::information(0,"error",file.errorString());
            QTextStream in (&file);

            while (!in.atEnd()){
                QString line = in.readLine();
                separarDatos(line); //a partir de los datos guardados genera la materia
            }
            file.close();
        }
    }


}

int MainWindow::getCantidadAulas()
{
    QList<Aula> aulas;
    sol.getAulas(aulas);
    return aulas.size();
}

QList<QString> MainWindow::getNombreAulas()
{   QList<QString> out ;
    QList<Aula> listaaulas ;
    sol.getAulas(listaaulas);
    for(int i =0; i<listaaulas.size();i++){
        out.push_back(listaaulas.at(i).getNombre());

    }
    return out;
}



void MainWindow::on_botonResolver_clicked()
{
    ui->mostrarAulas->setVisible(true);
    ui->mostrarHorarios->setVisible(true);
    ui->botonResolver->setVisible(false);

    if (manual==false){
        //agrego tantos dias como dias haya seleccionado
        if (ui->checkLunes->isChecked())
            sol.addDia("Lunes");
        if (ui->checkMartes->isChecked())
            sol.addDia("Martes");
        if (ui->checkMiercoles->isChecked())
            sol.addDia("Miercoles");
        if (ui->checkJueves->isChecked())
            sol.addDia("Jueves");
        if (ui->checkViernes->isChecked())
            sol.addDia("Viernes");
        if (ui->checkSabado->isChecked())
            sol.addDia("Sabado");
        sol.resolver();
    }

}

void MainWindow::on_actionCargar_Aulas_triggered()
{
    //borrar todos los datos que esten ingresados.
        on_actionNuevo_triggered();
        this->on_modoAuto_clicked();
        //abrir archivo
        QString path1 = "C:\\Users\\enzo\\Documents\\InvestigacionOperativa\\Archivos";

        QString path = QFileDialog::getOpenFileName(this,"Cargar Aulas",path1,"*.txt");
        if(!path.isEmpty()){
            QFile file( path );
            if (!file.open(QIODevice::ReadOnly))
                QMessageBox::information(0,"error",file.errorString());
            QTextStream in (&file);

            while (!in.atEnd()){

                QString line = in.readLine();
                separarAulas(line); //a partir de los datos guardados genero el Aula.
            }
            file.close();
        }

}

void MainWindow::on_actionGuardar_Aulas_triggered()
{
    QString lunes="Lunes";
    QString martes="Martes";
    QString miercoles="Miercoles";
    QString jueves="Jueves";
    QString viernes="Viernes";
    QString sabado="Sabado";
    QString fileName = QFileDialog::getSaveFileName(this,"Guardar Aulas",QStandardPaths::locate(QStandardPaths::DesktopLocation,""),"TXT (*.txt);;Todos los archivos (*.*)");

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    if(file.isOpen()){
        QTextStream text(&file);
        QList<Aula> lista_aulas ;
        sol.getAulas(lista_aulas);

       for (int i=0; i< lista_aulas.size(); i++){
            Aula aux = lista_aulas.at(i);


            for(int j=0;j<6;j++){
            QList<HorarioDia> franja;
            aux.getFranja(j,franja);
             for(int x=0;x<franja.size();x++){
               switch(j){

              case 0 :{ HorarioDia auxiliar = franja.at(x);
                         text <<aux.getNombre()+" - "+auxiliar.toString()+" - "+lunes << "\n";
                         break;
                    }
              case 1 : {HorarioDia auxiliar = franja.at(x);
                       text<< aux.getNombre()+" - "+auxiliar.toString()+" - "+martes << "\n";
                        break;
                        }
              case 2: {HorarioDia auxiliar = franja.at(x);
                  text<<aux.getNombre()+" - "+auxiliar.toString()+" - "+miercoles<<"\n";
                    break;
               }
              case 3:{HorarioDia auxiliar = franja.at(x);
                  text <<aux.getNombre()+" - "+auxiliar.toString()+" - "+jueves<<"\n";
                    break;
               }
              case 4:{HorarioDia auxiliar = franja.at(x);
                   text<<aux.getNombre()+" - "+auxiliar.toString()+" - "+viernes<<"\n";
                    break;
               }
              case 5: {HorarioDia auxiliar = franja.at(x);
                   text<< aux.getNombre()+" - "+auxiliar.toString()+" - "+sabado<<"\n";
                    break;
               }


            }


            }
        }

    }

      file.close();

}
}
