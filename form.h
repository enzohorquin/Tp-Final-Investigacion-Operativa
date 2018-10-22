#ifndef FORM_H
#define FORM_H

#include "tableroHorarios.h"

#include <QWidget>
#include <ui_nuevaventana.h>
#include "QTime"
#include "solucion.h"
#include "mainwindow.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    void mostrarHorarios(QList<Materia> materias);
    void mostrarHorariosAula(QList<Materia> materias, QString aula);
    void setMainWindow(MainWindow *mainW);
    bool hayOtraMateria(int horaI, int cantHoras, int dia);
    bool estaOcupadaAula(int horaInicio, int cantHoras, QString dia, Aula aula);
    void setAnio(int anio);
    void cambiarEstado(bool estado);


private slots:
    void on_pushButton_clicked();
    void on_box_dia_anterior_activated(const QString &arg1);
    void on_box_materia_activated(int index);
    void on_box_dia_elegido_activated(const QString &arg1);

    void on_mostrarAulas_clicked();

private:
    Ui::Form *ui;

    Solucion *sol;
    int anio;
    tableroHorarios horariosActuales;
    MainWindow * mainW;
    void MostrarTablero();
    void MostrarDias(int i,int j);
    void MostrarHoras(int i, int j);
    void mostrarVentanas(bool valor);
    void imprimirHorarios(QList<Materia> listMat);
    bool diaOcupado(Materia mat, QString dia);

};

#endif // FORM_H
