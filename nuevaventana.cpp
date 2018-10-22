#include "nuevaventana.h"
#include "ui_nuevaventana.h"
#include "mainwindow.h"
#include "qmessagebox.h"
#include "qdebug.h"
#include "aula.h"
#define OCHO 8
#define VEINTIDOS 22

NuevaVentana::NuevaVentana(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevaVentana)
{
    ui->setupUi(this);
    manual=false;
    this->setModal(true);
    QList<QString> aux;
    aux<<"Lunes"<< "Martes"<<"Miercoles"<<"Jueves"<<"Viernes"<< "Sabado";
    ui->boxDIa->addItems(aux);
    aux.clear();
    aux<<"Teórica"<<"Práctica"<<"Teórico-Práctico"<<"Práctica Especial";
    ui->boxModal->addItems(aux);
    franjaHorariaAula(false);
}

NuevaVentana::~NuevaVentana()
{
    delete ui;
}

void NuevaVentana::mostrarInsMat(){

    setWindowTitle("Nueva Materia");
    ui->label->setVisible(false);
    ui->lineNombre->clear();
    ui->lineNombre->setPlaceholderText("Ejemplo: Investigacion Operativa");
    ui->timeFin->setVisible(false);
    ui->timeInicio->setVisible(false);
    ui->lAula->setVisible(true);
    ui->boxAulas->setVisible(true);
    ui->ldesde->setVisible(false);
    ui->lhasta->setVisible(false);
    ui->lDia->setVisible(false);
    ui->lAnio->setVisible(true);
    ui->boxDIa->setVisible(false);
    ui->cargaHoraria->setVisible(true);
    ui->lcargaHora->setVisible(true);
    ui->boxAnio->setVisible(true);
    ui->lModal->setVisible(true);
    ui->boxModal->setVisible(true);
    QList<QString> anios;
    principal->getAnios(anios);
    ui->boxAnio->clear();
    ui->boxAnio->addItems(anios);
    ui->boxAulas->clear();
    if(aulas.isEmpty()){
        aulas = principal->getNombreAulas();
        ui->boxAulas->addItems(aulas);
    }
    else{   QList<QString> out2;
            QList<QString> lisAulas = principal->getNombreAulas();
            QSet<QString> out ;
            for(int i =0;i<lisAulas.size();i++){
                out.insert(lisAulas.at(i));
            }
            for(int i = 0;i<aulas.size();i++){
                out.insert(aulas.at(i));
            }

            out2=out.toList();
            ui->boxAulas->addItems(out2);






    }
    franjaHorariaAula(false);
    ui->limitarFranja->setVisible(false);
}

void NuevaVentana::mostrarInsAula()

{   ui->label->setVisible(true);
    ui->limitarFranja->setVisible(true);
    ui->lineNombre->clear();
    setWindowTitle("Nueva Aula");
    ui->lineNombre->setPlaceholderText("Ejemplo: Aula 1");
    ui->timeFin->setVisible(false);
    ui->timeInicio->setVisible(false);
    ui->lAula->setVisible(false);
    ui->boxAulas->setVisible(false);
    ui->ldesde->setVisible(false);
    ui->lhasta->setVisible(false);
    ui->lDia->setVisible(false);
    ui->boxDIa->setVisible(false);
    ui->cargaHoraria->setVisible(false);
    ui->lcargaHora->setVisible(false);
    ui->boxAnio->setVisible(false);
    ui->lAnio->setVisible(false);
    ui->lModal->setVisible(false);
    ui->boxModal->setVisible(false);

    franjaHorariaAula(false);

}

void NuevaVentana::franjaHorariaAula(bool valor){
    // label dias
    ui->lLunes->setVisible(valor);
    ui->lMartes->setVisible(valor);
    ui->lMiercoles->setVisible(valor);
    ui->lJueves->setVisible(valor);
    ui->lViernes->setVisible(valor);
    ui->lSabado->setVisible(valor);
    // label desde
    ui->ldesde->setVisible(valor);
    ui->ldesde_martes->setVisible(valor);
    ui->ldesde_miercoles->setVisible(valor);
    ui->ldesde_jueves->setVisible(valor);
    ui->ldesde_viernes->setVisible(valor);
    ui->ldesde_sabado->setVisible(valor);
    // time inicio
    ui->timeInicio->setVisible(valor);
    ui->timeInicio_martes->setVisible(valor);
    ui->timeInicio_miercoles->setVisible(valor);
    ui->timeInicio_jueves->setVisible(valor);
    ui->timeInicio_viernes->setVisible(valor);
    ui->timeInicio_sabado->setVisible(valor);
    // label hasta
    ui->lhasta->setVisible(valor);
    ui->lhasta_martes->setVisible(valor);
    ui->lhasta_miercoles->setVisible(valor);
    ui->lhasta_jueves->setVisible(valor);
    ui->lhasta_viernes->setVisible(valor);
    ui->lhasta_sabado->setVisible(valor);
    //time fin
    ui->timeFin->setVisible(valor);
    ui->timeFin_martes->setVisible(valor);
    ui->timeFin_miercoles->setVisible(valor);
    ui->timeFin_jueves->setVisible(valor);
    ui->timeFin_viernes->setVisible(valor);
    ui->timeFin_sabado->setVisible(valor);


}


void NuevaVentana::on_ok_clicked()
{
    QString aula=ui->lineNombre->text();
    Aula nuevaAula(aula.toLower());
    if (insAula==true){

        if ( principal->perteneceAula(aula.toLower()) ){
             ui->boxAulas->addItem(aula.toLower());
             aulas.push_back(ui->lineNombre->text().toLower());

            HorarioDia lunes;


            lunes.setDia("Lunes");

          if(ui->timeInicio->time().hour() >= OCHO && ui->timeFin->time().hour()<= VEINTIDOS){
            lunes.setHoraIncio(ui->timeInicio->time().hour(),ui->timeInicio->time().minute());
            lunes.setHoraFin(ui->timeFin->time().hour(),ui->timeFin->time().minute());
            nuevaAula.setFranja(lunes);


          }

           HorarioDia martes;

           martes.setDia("Martes");

         if(ui->timeInicio_martes->time().hour() >= OCHO && ui->timeFin_martes->time().hour() <= VEINTIDOS){
           martes.setHoraIncio(ui->timeInicio_martes->time().hour(),ui->timeInicio_martes->time().minute());
           martes.setHoraFin(ui->timeFin_martes->time().hour(),ui->timeFin_martes->time().minute());
           nuevaAula.setFranja(martes);

        }

           HorarioDia miercoles;
           miercoles.setDia("Miercoles");

         if(ui->timeInicio_miercoles->time().hour()>=OCHO && ui->timeFin_miercoles->time().hour() <= VEINTIDOS){
           miercoles.setHoraIncio(ui->timeInicio_miercoles->time().hour(),ui->timeInicio_miercoles->time().minute());
           miercoles.setHoraFin(ui->timeFin_miercoles->time().hour(),ui->timeFin_miercoles->time().minute());
           nuevaAula.setFranja(miercoles);

        }

           HorarioDia jueves;
           jueves.setDia("Jueves");
          if(ui->timeInicio_jueves->time().hour() >=  OCHO && ui->timeFin_jueves->time().hour() <= VEINTIDOS) {
           jueves.setHoraIncio(ui->timeInicio_jueves->time().hour(),ui->timeInicio_jueves->time().minute());
           jueves.setHoraFin(ui->timeFin_jueves->time().hour(),ui->timeFin_jueves->time().minute());
           nuevaAula.setFranja(jueves);

          }

           HorarioDia viernes;
           viernes.setDia("Viernes");

           if(ui->timeInicio_viernes->time().hour() >=  OCHO && ui->timeFin_viernes->time().hour() <= VEINTIDOS) {
           viernes.setHoraIncio(ui->timeInicio_viernes->time().hour(),ui->timeInicio_viernes->time().minute());
           viernes.setHoraFin(ui->timeFin_viernes->time().hour(),ui->timeFin_viernes->time().minute());
           nuevaAula.setFranja(viernes);

           }

           HorarioDia sabado;
           sabado.setDia("Sabado");

           if(ui->timeInicio_sabado->time().hour() >=  OCHO && ui->timeFin_viernes->time().hour() <= VEINTIDOS) {
           sabado.setHoraIncio(ui->timeInicio_sabado->time().hour(),ui->timeInicio_sabado->time().minute());
           sabado.setHoraFin(ui->timeFin_sabado->time().hour(),ui->timeFin_sabado->time().minute());
           nuevaAula.setFranja(sabado);

           }

            listaAulas.push_back(nuevaAula);
            principal->addAula(nuevaAula);
            ui->limitarFranja->setText("Si");





        }
        else
            QMessageBox::warning(this,"Error al guardar.","Ya existe un aula con dicho nombre.");
    }
    else{
        QString nombreMat=ui->lineNombre->text().toUpper();
        nombreMat.append(" (");
        if (ui->boxModal->currentText()=="Teórica")
            nombreMat.append("T");
        else
            if (ui->boxModal->currentText()=="Teórico-Práctico")
                nombreMat.append("T/P");
            else
                if (ui->boxModal->currentText()=="Práctica Especial")
                    nombreMat.append("PE");
                else
                    nombreMat.append("P");
        nombreMat.append(")");
        //version manual
        if (manual==true){
            if ( hayError() )
                QMessageBox::warning(this,"Franja horaria no valida.","No se permite ingresar dicha materia en ese horario.");
            else{
                Aula aula_correspondiente ;
                this->getAula(ui->boxAulas->currentText(),aula_correspondiente);
                Materia materia( nombreMat,aula_correspondiente,ui->timeInicio->time().hour(),
                                 ui->timeInicio->time().minute(), ui->timeFin->time().hour(),ui->timeFin->time().minute(),
                                 ui->boxDIa->currentText(),ui->boxAnio->currentText().toInt() );
                principal->addMateria(materia); //mostrar en la ventana la nueva materia y agregar a conjunto
            }
        }
        else{
            //version con programacion lineal
            Aula aula_correspondiente ;
            this->getAula(ui->boxAulas->currentText(),aula_correspondiente);

            Materia nueva(nombreMat,aula_correspondiente,ui->boxAnio->currentText().toInt(),ui->cargaHoraria->value());
            principal->addMateria(nueva);
        }
    }
    this->close();
}

void NuevaVentana::setInsAula(bool ins){
    insAula=ins;


}

void NuevaVentana::setMainWindow(MainWindow *m)
{
    principal=m;
}

void NuevaVentana::addAula(Aula &a)
{
    listaAulas.push_back(a);
}

void NuevaVentana::on_cancelar_clicked()
{
    this->close();
}

bool NuevaVentana::hayError()
{
    int horaInicio=ui->timeInicio->time().hour();
    int horaFin = ui->timeFin->time().hour();
    if (horaFin<=horaInicio)
        return true;
    if ( (horaFin<8) || (horaFin>22) || (horaInicio<8) || (horaInicio>22) )
        return true;
    int minInicio = ui->timeInicio->time().minute();
    int minFin = ui->timeFin->time().minute();
    if (  ( (minFin != 0) && (minFin != 30) ) || ( (minInicio != 0)  && (minInicio != 30) ) )
        return true;
    return false;
}

bool NuevaVentana::getManual() const
{
    return manual;
}

void NuevaVentana::setManual(bool value)
{
    manual = value;
}


void NuevaVentana::mostrarInsMatManual(){
    setWindowTitle("Nueva Materia");
    ui->lineNombre->clear();
    ui->lineNombre->setPlaceholderText("Ejemplo: Investigacion Operativa");
    ui->timeFin->setVisible(true);
    ui->timeInicio->setVisible(true);
    ui->lAula->setVisible(true);
    ui->boxAulas->setVisible(true);
    ui->ldesde->setVisible(true);
    ui->lhasta->setVisible(true);
    ui->lDia->setVisible(true);
    ui->boxDIa->setVisible(true);
    ui->boxAnio->setVisible(true);
    ui->lAnio->setVisible(true);
    ui->cargaHoraria->setVisible(false);
    ui->lcargaHora->setVisible(false);
    ui->lModal->setVisible(true);
    ui->boxModal->setVisible(true);
    QList<QString> anios;
    principal->getAnios(anios);
    ui->boxAnio->clear();
    ui->boxAnio->addItems(anios);
    ui->boxAulas->clear();
    ui->boxAulas->addItems(aulas);
    ui->limitarFranja->hide();
}




void NuevaVentana::on_limitarFranja_clicked()
{
    franjaHorariaAula(ui->limitarFranja->text() == "Si");
    if (ui->limitarFranja->text() == "Si")
        ui->limitarFranja->setText("No");
    else
        ui->limitarFranja->setText("Si");
}

void NuevaVentana::getAula(QString nombre, Aula & aux)
{   qDebug()<<nombre;
    for(int i = 0; i< this->listaAulas.size();i++){
        qDebug()<<listaAulas.at(i).getNombre();
        if(listaAulas.at(i).getNombre()==nombre){
             qDebug()<<"ENTRO GET AULA "<<nombre;
            aux=listaAulas.at(i) ;
}
    }
}
