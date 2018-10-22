#include "form.h"
#include "ui_form.h"
#include "qdebug.h"


Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    QList<QString> aux;
    aux<<"Lunes"<< "Martes"<<"Miercoles"<<"Jueves"<<"Viernes"<< "Sabado";
    ui->box_dia_anterior->addItems(aux);
    ui->box_dia_elegido->addItems(aux);
}

Form::~Form()
{
    delete ui;
}

void Form::mostrarHorarios(QList<Materia> materias)
{

    QList<Materia>::iterator it=materias.begin();
    int i=0;
    horariosActuales.inicializar();
    while (it!=materias.end()){
        if (it->getAnio()==anio){
            horariosActuales.insertarCurso(*it);
        }
        it++;
        i++;
    }
    MostrarTablero();
    ui->box_materia->clear();
//    on_box_dia_anterior_activated("Lunes");
//    ui->box_dia_anterior->setCurrentIndex(0);

}

void Form::mostrarHorariosAula(QList<Materia> materias, QString aula)
{
    QList<Materia>::iterator it=materias.begin();
    int i=0;
    horariosActuales.inicializar();
    while (it!=materias.end()){
        if (it->getAula().getNombre()==aula)
            horariosActuales.insertarCurso(*it);
        it++;
        i++;
    }
    MostrarTablero();
}

void Form::setMainWindow(MainWindow * mainW)
{
    this->mainW = mainW;
}


void Form::MostrarDias(int i, int j){
    QLabel*l = new QLabel();
    l->setStyleSheet("border-image: url(:/Imagenes/dia.png);");
    l->setScaledContents(true);
    switch (j){
    case 1:{
        l->setText("<CENTER><b>Lunes</b></CENTER>");
    }break;
    case 2:{
        l->setText("<CENTER><b>Martes</b></CENTER>");
    }break;
    case 3:{
        l->setText("<CENTER><b>Miércoles</b></CENTER>");
    }break;
    case 4:{
        l->setText("<CENTER><b>Jueves</b></CENTER>");
    }break;
    case 5:{
        l->setText("<CENTER><b>Viernes</b></CENTER>");
    }break;
    case 6:{
        l->setText("<CENTER><b>Sábado</b></CENTER>");
    }break;
    }
    ui->matriz->addWidget(l,i,j);

}

void Form::MostrarHoras(int i,int j){
    QLabel*l = new QLabel();
    l->setStyleSheet("border-image: url(:/Imagenes/dia.png);");
    l->setScaledContents(true);
    switch (i){
    case 1:{
        l->setText("<CENTER><b>08:00‐08:30</b></CENTER>");
    }break;
    case 2:{
        l->setText("<CENTER><b>08:30‐09:00</b></CENTER>");
    }break;
    case 3:{
        l->setText("<CENTER><b>09:00‐09:30</b></CENTER>");
    }break;
    case 4:{
        l->setText("<CENTER><b>09:30‐10:00</b></CENTER>");
    }break;
    case 5:{
        l->setText("<CENTER><b>10:00‐10:30</b></CENTER>");
    }break;
    case 6:{
        l->setText("<CENTER><b>10:30‐11:00</b></CENTER>");
    }break;
    case 7:{
        l->setText("<CENTER><b>11:00‐11:30</b></CENTER>");
    }break;
    case 8:{
        l->setText("<CENTER><b>11:30‐12:00</b></CENTER>");
    }break;
    case 9:{
        l->setText("<CENTER><b>12:00‐12:30</b></CENTER>");
    }break;
    case 10:{
        l->setText("<CENTER><b>12:30‐13:00</b></CENTER>");
    }break;
    case 11:{
        l->setText("<CENTER><b>13:00‐13:30</b></CENTER>");
    }break;
    case 12:{
        l->setText("<CENTER><b>13:30‐14:00</b></CENTER>");
    }break;
    case 13:{
        l->setText("<CENTER><b>14:00‐14:30</b></CENTER>");
    }break;
    case 14:{
        l->setText("<CENTER><b>14:30‐15:00</b></CENTER>");
    }break;
    case 15:{
        l->setText("<CENTER><b>15:00‐15:30</b></CENTER>");
    }break;
    case 16:{
        l->setText("<CENTER><b>15:30‐16:00</b></CENTER>");
    }break;
    case 17:{
        l->setText("<CENTER><b>16:00‐16:30</b></CENTER>");
    }break;
    case 18:{
        l->setText("<CENTER><b>16:30‐17:00</b></CENTER>");
    }break;
    case 19:{
        l->setText("<CENTER><b>17:00‐17:30</b></CENTER>");
    }break;
    case 20:{
        l->setText("<CENTER><b>17:30‐18:00</b></CENTER>");
    }break;
    case 21:{
        l->setText("<CENTER><b>18:00‐18:30</b></CENTER>");
    }break;
    case 22:{
        l->setText("<CENTER><b>18:30‐19:00</b></CENTER>");
    }break;
    case 23:{
        l->setText("<CENTER><b>19:00‐19:30</b></CENTER>");
    }break;
    case 24:{
        l->setText("<CENTER><b>19:30‐20:00</b></CENTER>");
    }break;
    case 25:{
        l->setText("<CENTER><b>20:00‐20:30</b></CENTER>");
    }break;
    case 26:{
        l->setText("<CENTER><b>20:30‐21:00</b></CENTER>");
    }break;
    case 27:{
        l->setText("<CENTER><b>21:00‐21:30</b></CENTER>");
    }break;
    case 28:{
        l->setText("<CENTER><b>21:30‐22:00</b></CENTER>");
    }break;
    }
    ui->matriz->addWidget(l,i,j);
}

void Form::MostrarTablero()
{
      for (int i=0;i<29;i++)
        for (int j=0;j<7;j++)
        {
            if (i==0)
                MostrarDias(i,j);
            else
                if (j==0){
                    MostrarHoras(i,j);
                }
            else {
                int valor1=horariosActuales.getValor(i-1,j);
                int valor2=horariosActuales.getValor(i,j);
                int valor3=0;
                if (i!=28)
                    valor3=horariosActuales.getValor(i+1,j);
                if (valor2==0){
                    QLabel*l = new QLabel();
                    if (i==28)
                        l->setStyleSheet("border-image: url(:/Imagenes/fin.png);");
                    else
                        l->setStyleSheet("border-image: url(:/Imagenes/vacio.png);");
                    l->setScaledContents(true);
                    ui->matriz->addWidget(l,i,j);
                }
                else{
                    QLabel*l = new QLabel();
                    if (valor2!=valor3 ){
                        if (horariosActuales.getValor(i-2,j)!=valor2){
                            //es el segundo, pongo el aula
                            l->setStyleSheet("border-image: url(:/Imagenes/finOcupado.png);");
                            QString text="<b><CENTER>";
                            text.append(horariosActuales.getAula(valor2).getNombre());
                            text.append(" - Año ");
                            text.append(QString::number(horariosActuales.getAnio(valor2) ) );
                            text.append("</b></CENTER>");
                            l->setText(text);
                            l->setScaledContents(true);
                            ui->matriz->addWidget(l,i,j);
                        }
                        else{
                        QLabel*l = new QLabel();
                        l->setStyleSheet("border-image: url(:/Imagenes/finOcupado.png);");
                        l->setScaledContents(true);
                        ui->matriz->addWidget(l,i,j);
                        }
                    }
                    else{
                        if (valor1!=valor2 && i!=28){
                            if (valor1==0)
                                l->setStyleSheet("border-image: url(:/Imagenes/inicio.png);");
                            else
                                l->setStyleSheet("border-image: url(:/Imagenes/medio.png);");
                            QString text="<b><CENTER>";
                            text.append(horariosActuales.getNombre(valor2));
                            text.append("</b></CENTER>");
                            l->setText(text);
                        l->setScaledContents(true);
                        ui->matriz->addWidget(l,i,j);
                        }
                        else
                        if (valor1==valor2){
                            if (horariosActuales.getValor(i-2,j)!=valor2){
                                //es el segundo, pongo el aula
                                l->setStyleSheet("border-image: url(:/Imagenes/medio.png);");
                                QString text="<b><CENTER>";
                                text.append("<b><CENTER>");
                                text.append(horariosActuales.getAula(valor2).getNombre());
                                text.append(" - Año ");
                                text.append(QString::number(horariosActuales.getAnio(valor2) ) );
                                text.append("</b></CENTER>");
                                l->setText(text);
                                l->setScaledContents(true);
                                ui->matriz->addWidget(l,i,j);
                            }
                            else{
                            QLabel*l = new QLabel();
                            l->setStyleSheet("border-image: url(:/Imagenes/medio.png);");
                            l->setScaledContents(true);
                            ui->matriz->addWidget(l,i,j);
                            }
                        }
                    }
                }
            }
        }

}

void Form::imprimirHorarios(QList<Materia> listMat)
{
    horariosActuales.inicializar();
    QList<Materia>::iterator i=listMat.begin();
    while (i!=listMat.end()){
           horariosActuales.insertarCurso(*i);
        i++;
    }
    MostrarTablero();
}

bool Form::diaOcupado(Materia mat, QString dia)
{
    int inicio, fin =0;
    mat.getHoraInicio(inicio,fin,dia);
    return (inicio != 0);
}


void Form::on_pushButton_clicked()
{
    QString horaNueva = ui->comboBox->currentText();
    int horaInicio, horaFin, j;
    QString aux ="";
    for (int i=0; horaNueva.at(i)!=':'; i++)
        aux.append(horaNueva.at(i));
    horaInicio = aux.toInt();
    aux.clear();
    j=horaNueva.size()-1;
    for (int i=horaNueva.size()-1; horaNueva.at(i)!=':'; i--){
        j--;
    }
    if (!horaNueva.at(j-2).isDigit())
        aux.append(horaNueva.at(j-1) );
    else{
        aux.append(horaNueva.at(j-2) );
        aux.append(horaNueva.at(j-1) );
    }
    horaFin = aux.toInt();

    QList<Materia> materiasH;
    mainW->getMaterias(materiasH);
    QList<Materia>::iterator it=materiasH.begin();
    while ( it != materiasH.end() ){

        if (it->getNombre() == ui->box_materia->currentText() ){

            int inicio,min, fin = 0;
            it->getHoraInicio(inicio,min,ui->box_dia_anterior->currentText());
            it->getHoraFin(fin,min,ui->box_dia_anterior->currentText());
            Aula aux = it->getAula();
            Materia nueva("nombre",aux,inicio, 0, ui->hora_inicio_anterior->time().hour(), 0, ui->box_dia_elegido->currentText(),it->getAnio() );
            if (fin>ui->hora_fin_anterior->time().hour()){
                nueva.setHoraInicio(ui->hora_fin_anterior->time().hour(),0,ui->box_dia_elegido->currentText());
                nueva.setHoraFin(fin,0,ui->box_dia_elegido->currentText());
            }

            it->borrarFranja(ui->hora_inicio_anterior->time().hour(),ui->hora_fin_anterior->time().hour(),ui->box_dia_anterior->currentText());

            if ( diaOcupado(*it, ui->box_dia_elegido->currentText()) ){
                //si en ese dia ya esta la materia creo una nueva
                QString espacio = " ";
                QString nombre = espacio + it->getNombre();
                QList<Materia>::iterator otroIt = it;
                while ( otroIt != materiasH.end() ){
                    //recorro por si no cree otra ya
                    if (otroIt->getNombre() == nombre)
                        nombre = espacio + nombre;
                    otroIt++;
                }
                qDebug()<<"llega hasta aca"<<nombre;
                nueva.setNombre(nombre);
                qDebug()<<"sale de aca";
                mainW->addMateria(nueva);
                materiasH.push_back(nueva);
            }
            //sino modifico esa
            it->setDia(ui->box_dia_elegido->currentText());
            it->setHoraInicio(horaInicio,0,ui->box_dia_elegido->currentText());
            it->setHoraFin(horaFin,0,ui->box_dia_elegido->currentText());
            mainW->setMateria(*it);
            horariosActuales.setMateria(*it);

        }
        it++;
    }
    qDebug()<<"pasa el add";
    mostrarHorarios(materiasH);
    ui->comboBox->clear();
}


void Form::on_box_dia_anterior_activated(const QString &arg1)
{
    ui->box_materia->clear();
    QList<QString> materias;
    horariosActuales.getMateriasDia(materias,arg1);
    ui->box_materia->addItems(materias);
    if (!materias.empty())
        on_box_materia_activated(ui->box_materia->currentIndex());
    else
        ui->comboBox->clear();
}



void Form::on_box_materia_activated(int index)
{
    QList<Materia> materias;
    this->horariosActuales.getMateriasDiaCompleta(materias,ui->box_dia_anterior->currentText());
    int hora, minutos, segundos, ms = 0;
    materias.at(index).getHoraInicio(hora,minutos, ui->box_dia_anterior->currentText());
    QTime time( hora,minutos,segundos,ms);
    ui->hora_inicio_anterior->setMinimumTime(time);
    ui->hora_fin_anterior->setMinimumTime(time);
    materias.at(index).getHoraFin(hora,minutos, ui->box_dia_anterior->currentText());
    QTime time2(hora,minutos,segundos,ms);
    ui->hora_fin_anterior->setMaximumTime(time2);
    ui->hora_inicio_anterior->setMaximumTime(time2);
    ui->hora_inicio_anterior->setTime(time);
    ui->hora_fin_anterior->setTime(time2);

}



void Form::on_box_dia_elegido_activated(const QString &arg1)
{
    ui->comboBox->clear();
    if (ui->box_materia->count()!=0){

        QList<Materia> materias;
        horariosActuales.getMateriasDiaCompleta(materias,ui->box_dia_anterior->currentText());
        Aula aula = materias.at(ui->box_materia->currentIndex()).getAula();
        Solucion s = mainW->getSolucion();
        aula = s.getAula(aula);

        QList<HorarioDia> franja;
        aula.getFranja(ui->box_dia_elegido->currentIndex(),franja);
        int cantHoras = ui->hora_fin_anterior->time().hour() - ui->hora_inicio_anterior->time().hour();

        foreach (HorarioDia horario, franja){
            int horaI,min,horaF = 0;
            horario.getHoraInicio(horaI,min);
            horario.getHoraFin(horaF,min);
            for (int i=horaI; i<horaF; i++){
                if ( (horaF-i >= cantHoras) && (!hayOtraMateria(i,cantHoras, ui->box_dia_elegido->currentIndex()) )
                     && (!estaOcupadaAula(i,cantHoras, ui->box_dia_elegido->currentText(), aula )) ){
                    QString nuevo = QString::number(i) + ":00 a " + QString::number(i+ cantHoras) + ":00";
                    ui->comboBox->addItem(nuevo);
                }
            }
        }
    }
}

bool Form::hayOtraMateria(int horaI, int cantHoras, int dia){
    dia++;
    horaI = ( (horaI-8)*2 +1) ;
    int horaF = horaI+ cantHoras *2;
    for (int i=horaI; i<horaF; i++)
        if (horariosActuales.getValor(i,dia) != 0)
            return true;
    return false;
}

bool Form::estaOcupadaAula(int horaInicio, int cantHoras, QString dia, Aula aula){
   QList<Materia> materias;
   mainW->getMaterias(materias);
   int horaI, min, horaF = 0;

   QVector<bool> horasLibres(14);
   for (int i=0; i<horasLibres.size(); i++)
       horasLibres[i]=true;//todos libres

   foreach (Materia m, materias){
       if (m.getAula().getNombre() == aula.getNombre()){
           m.getHoraInicio(horaI,min,dia);
           m.getHoraFin(horaF, min, dia);
           for (int i=horaI-8; i>=0 && i<horaF-8; i++)
               horasLibres[i]=false;
       }
   }

   for (int i=horaInicio-8; i<horaInicio-8+cantHoras; i++)
       if (!horasLibres[i])
           return true;
   return false;
}

void Form::setAnio(int anio)
{
    this->anio = anio;
}


void Form::on_mostrarAulas_clicked()
{
    if (ui->mostrarAulas->text() == "Mostrar Aulas"){
        ui->mostrarAulas->setText("Mostrar Horarios");
        cambiarEstado(false);
        mainW->mostrarAulas();
    }
    else{
        ui->mostrarAulas->setText("Mostrar Aulas");
        mainW->mostrarHorarios();
        cambiarEstado(true);
    }
}

void Form::cambiarEstado(bool estado){
    if (!estado)
        ui->mostrarAulas->setText("Mostrar Horarios");
    else
        ui->mostrarAulas->setText("Mostrar Aulas");
    ui->box_dia_anterior->setVisible(estado);
    ui->box_dia_elegido->setVisible(estado);
    ui->box_materia->setVisible(estado);
    ui->comboBox->setVisible(estado);
    ui->hora_fin_anterior->setVisible(estado);
    ui->hora_inicio_anterior->setVisible(estado);
    ui->label_2->setVisible(estado);
    ui->label_3->setVisible(estado);
    ui->label_4->setVisible(estado);
    ui->label_dia_anterior->setVisible(estado);
    ui->label_dia_elegido->setVisible(estado);
    ui->line->setVisible(estado);
    ui->line_2->setVisible(estado);
    ui->pushButton->setVisible(estado);
}
