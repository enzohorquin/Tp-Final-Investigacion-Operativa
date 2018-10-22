#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tableroHorarios.h"
#include "solucion.h"
#include <QMainWindow>
#include "nuevaventana.h"
#include <QDialog>
#include <QFileDialog>
#include <QStandardPaths>
#include "aula.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addMateria(Materia mat);
    bool perteneceAula(QString aula);
    void addAnio(QString anio);
    void getAnios(QList<QString> &anios);
    void addAula(Aula &a);
    void getMaterias(QList<Materia> &materias);
    Solucion getSolucion();
    void setMateria(Materia materia);
    void mostrarHorarios();
    void mostrarAulas();
    int getCantidadAulas();
    QList<QString> getNombreAulas();

private slots:
    void on_modoManual_clicked();
    void on_insertarMateria_clicked();
    void on_insertarAula_clicked();
    void on_mostrarHorarios_clicked();
    void on_modoAuto_clicked();
    void on_borrar_clicked();
    void on_actionAutom_tico_triggered();
    void on_actionManual_triggered();
    void on_insertarAnio_clicked();
    void on_borrar_anio_clicked();

    void on_actionNuevo_triggered();
    void on_borrar_aula_clicked();
    void on_mostrarAulas_clicked();
    void on_tabWidget_tabCloseRequested(int index);
    void on_actionGuardar_triggered();
    void on_actionAbrir_triggered();



    void on_botonResolver_clicked();
    void on_actionCargar_Aulas_triggered();
    void on_actionGuardar_Aulas_triggered();

private:
    Ui::MainWindow *ui;
    Solucion sol;
    bool manual;
    NuevaVentana *nuevaVentana;

    void mostrarVentanas(bool valor);
    void resolver();
    void mostrarInicio(bool valor);
    void mostrarMateria(Materia materia);
    void separarDatos(QString line);
    void separarAulas(QString line);
};

#endif // MAINWINDOW_H
