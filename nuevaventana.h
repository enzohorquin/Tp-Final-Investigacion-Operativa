#ifndef NUEVAVENTANA_H
#define NUEVAVENTANA_H
#include "aula.h"

#include <QDialog>
#include "conjuntomat.h"
#include "materia.h"
#include "tablerohorarios.h"
#include "solucion.h"
#include "ui_nuevaventana.h"



namespace Ui {
    class NuevaVentana;
}
class MainWindow;
class NuevaVentana : public QDialog
{
    Q_OBJECT

public:
    explicit NuevaVentana(QWidget *parent = 0);
    ~NuevaVentana();
    //getters
    void getMaterias(QList<Materia>& materias);
    bool getManual() const;
    //setters
    void setSol(const Solucion &value);
    void setManual(bool value);
    void setInsAula(bool ins);
    void setMainWindow(MainWindow *m);
    //metodos publicos
    void addAula(Aula & a);
    void mostrarInsMat();
    void mostrarInsAula();
    void mostrarManual();
    void mostrarInsMatManual();
    void mostrarInsAulaManual();


private slots:
    void on_ok_clicked();
    void on_cancelar_clicked();
    void on_limitarFranja_clicked();

private:
    Ui::NuevaVentana *ui;
    Materia actual;
    bool insAula;
    bool manual;
    QList<Aula> listaAulas;
    QList<QString> aulas;
    MainWindow *principal;
    void getAula(QString nombre, Aula & aux);

    bool hayError();
    void franjaHorariaAula(bool valor);

};

#endif // NUEVAVENTANA_H
