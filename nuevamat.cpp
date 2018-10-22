#include "nuevamat.h"
#include "ui_nuevamat.h"

NuevaMat::NuevaMat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevaMat)
{
    ui->setupUi(this);
}

NuevaMat::~NuevaMat()
{
    delete ui;
}

/*void NuevaMat::setPrincipal(ui_MainWindow *w)
{
    principal=w;
}*/

void NuevaMat::mostrarInsMat(){
    setWindowTitle("Nueva Materia");
    ui->lineNombre->setPlaceholderText("Ejemplo: Investigacion Operativa");
    ui->timeFin->setVisible(false);
    ui->timeInicio->setVisible(false);
    ui->lAula->setVisible(true);
    ui->boxAulas->setVisible(true);
    ui->ldesde->setVisible(false);
    ui->lhasta->setVisible(false);
    QList<QString> aulas;
    materias.getAulas(aulas);
    ui->boxAulas->addItems(aulas);
}

void NuevaMat::mostrarInsAula()
{
    setWindowTitle("Nueva Aula");
    ui->lineNombre->setPlaceholderText("Ejemplo: Aula 1");
    ui->timeFin->setVisible(false);
    ui->timeInicio->setVisible(false);
    ui->lAula->setVisible(false);
    ui->boxAulas->setVisible(false);
    ui->ldesde->setVisible(false);
    ui->lhasta->setVisible(false);
    ui->lDia->setVisible(false);
    ui->b
}
