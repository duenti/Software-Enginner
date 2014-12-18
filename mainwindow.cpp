#include "mainwindow.h"
#include <vector>
#include "ui_mainwindow.h"
#include "UserFlows.h"
#include "System.h"
#include "Model.h"
#include "Flow.h"
#include "Factory.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QStandardItemModel>
#include <QSqlDatabase>
#include <QSqlQuery>


Factory* factory = Factory::getInstance();
int Factory::sysID_ = 0;
int Factory::flowID_ = 0;
Model* model;
QList<System*> systens;
QList<Flow*> flows;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    model = factory->modelCreator();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionEditar_triggered()
{
    ui->txtEditT0->setText(QString::number(model->getInitialTime()));
    ui->txtEditTF->setText(QString::number(model->getFinalTime()));
    ui->txtEditTS->setText(QString::number(model->getTimeStep()));
    ui->stkPrincipal->setCurrentIndex(1);
}

void MainWindow::on_cmdEditarModel_clicked()
{
    QMessageBox msg;
    model->setInitialTime(ui->txtEditT0->text().toInt());
    model->setFinalTime(ui->txtEditTF->text().toInt());
    model->setTimeStep(ui->txtEditTS->text().toInt());

    msg.setText("Modelo editado com sucesso.");
    msg.exec();
    //QMessageBox::Information(this, "Modelo", "Modelo editado com sucesso.");

    ui->stkPrincipal->setCurrentIndex(0);
}

void MainWindow::on_actionAdicionar_Fluxo_triggered()
{
    QList<Flow*> flows2;

    for(int i = 0; i < model->getFlows().size(); i++){
        flows2.push_back(model->getFlows().at(i));
    }

    ui->lstAllFlows->clear();
    ui->lstFlowsModel->clear();

    for(int i = 0; i < flows.size(); i++){
        if(flows2.contains(flows.at(i)))
            ui->lstFlowsModel->addItem(QString::fromStdString(flows2.at(i)->getName()));
        else
            ui->lstAllFlows->addItem(QString::fromStdString(flows.at(i)->getName()));
    }

    ui->stkPrincipal->setCurrentIndex(2);
}

void MainWindow::on_cmdAddFlowModel_clicked()
{
    //ADICIONA
    for(int i = 0; i < flows.size(); i++){
        if(flows.at(i)->getName() == ui->lstAllFlows->currentItem()->text().toStdString()){
            model->addFlow(flows.at(i));
        }
    }

    //ATUALIZA OS BOXES
    QList<Flow*> flows2;

    for(int i = 0; i < model->getFlows().size(); i++){
        flows2.push_back(model->getFlows().at(i));
    }

    ui->lstAllFlows->clear();
    ui->lstFlowsModel->clear();

    for(int i = 0; i < flows.size(); i++){
        if(flows2.contains(flows.at(i)))
            ui->lstFlowsModel->addItem(QString::fromStdString(flows2.at(i)->getName()));
        else
            ui->lstAllFlows->addItem(QString::fromStdString(flows.at(i)->getName()));
    }

    //ui->lstFlowsModel->addItem(ui->lstAllFlows->currentItem()->text());
}

void MainWindow::on_cmdRemFlowModel_clicked()
{
    //REMOVE
    for(int i = 0; i < flows.size(); i++){
        if(flows.at(i)->getName() == ui->lstFlowsModel->currentItem()->text().toStdString()){
            model->deleteFlow(flows.at(i));
        }
    }

    //ATUALIZA OS BOXES
    QList<Flow*> flows2;

    for(int i = 0; i < model->getFlows().size(); i++){
        flows2.push_back(model->getFlows().at(i));
    }

    ui->lstAllFlows->clear();
    ui->lstFlowsModel->clear();

    for(int i = 0; i < flows.size(); i++){
        if(flows2.contains(flows.at(i)))
            ui->lstFlowsModel->addItem(QString::fromStdString(flows2.at(i)->getName()));
        else
            ui->lstAllFlows->addItem(QString::fromStdString(flows.at(i)->getName()));
    }

}

void MainWindow::on_actionSair_triggered()
{
   ui->stkPrincipal->setCurrentIndex(0);
   QMainWindow::close();
}

void MainWindow::on_actionCriar_triggered()
{
    ui->txtNameSystem->setText("");
    ui->txtValueSystem->setText("");

    ui->stkPrincipal->setCurrentIndex(5);
}

void MainWindow::on_actionEditar_2_triggered()
{
    ui->lstAllSystens->clear();

    for(int i = 0; i < systens.size(); i++){
        ui->lstAllSystens->addItem(QString::fromStdString(systens.at(i)->getName()));
    }

    ui->stkPrincipal->setCurrentIndex(3);
}

void MainWindow::on_lstAllSystens_clicked(const QModelIndex &index)
{
    ui->lstAllSystens->currentItem();

    for(int i = 0; i < systens.size(); i++){
        if(systens.at(i)->getName() == ui->lstAllSystens->currentItem()->text().toStdString()){
            ui->txtSysValue->setText(QString::number(systens.at(i)->getValue()));
        }
    }
}

void MainWindow::on_txtSysValue_textChanged(const QString &arg1)
{

}

void MainWindow::on_actionDestruir_triggered()
{
    ui->lstAllSystens_2->clear();

    for(int i = 0; i < systens.size(); i++){
        ui->lstAllSystens_2->addItem(QString::fromStdString(systens.at(i)->getName()));
    }

    ui->stkPrincipal->setCurrentIndex(4);
}

void MainWindow::on_cmdDestruirSistema_clicked()
{
    QMessageBox msg;
    for(int i = 0; i < systens.size(); i++){
        if(systens.at(i)->getName() == ui->lstAllSystens_2->currentItem()->text().toStdString()){
            systens.erase(systens.begin() + i);
        }
    }

    msg.setText("Sistema editado com sucesso.");
    msg.exec();

    ui->lstAllSystens_2->clear();

    for(int i = 0; i < systens.size(); i++){
        ui->lstAllSystens_2->addItem(QString::fromStdString(systens.at(i)->getName()));
    }
}

void MainWindow::on_cmdCreateSystem_clicked()
{
    QMessageBox msg;
    string nome = ui->txtNameSystem->text().toStdString();
    double value = ui->txtValueSystem->text().toDouble();

    for(int i = 0; i < systens.size(); i++){
        if(systens.at(i)->getName() == nome){
            msg.setText("Este nome ja esta cadastrado, escolha outro e tente novamente.");
            return;
        }
    }

    System* s = factory->systemCreator(value);
    s->setName(nome);
    systens.push_back(s);


    msg.setText("Sistema criado com sucesso.");
    msg.exec();

    ui->stkPrincipal->setCurrentIndex(0);
}

void MainWindow::on_actionLogistico_triggered()
{
    ui->txtNameFlow->setText("");
    ui->txtVarFlow->setText("");
    ui->txtLimitFlow->setText("");

    ui->stkPrincipal->setCurrentIndex(6);
}

void MainWindow::on_actionExponencial_triggered()
{
    ui->txtNameFlow_2->setText("");
    ui->txtVarFlow_2->setText("");

    ui->stkPrincipal->setCurrentIndex(7);
}

void MainWindow::on_cmdCreateFlow_clicked()
{
    string nome = ui->txtNameFlow->text().toStdString();
    double val = ui->txtVarFlow->text().toDouble();
    double limit = ui->txtLimitFlow->text().toDouble();
    QMessageBox msg;

    for(int i = 0; i < flows.size(); i++){
        if(flows.at(i)->getName() == nome){
            msg.setText("Nome escolhido ja existe. Escolha outro e tente novamente.");
            return;
        }
    }

    Flow* f = factory->flowCreator<Flow1>();
    f->setName(nome);
    f->setLimit(limit);
    f->setVal(val);

    msg.setText("Fluxo criado com sucesso.");
    msg.exec();

    flows.push_back(f);

    ui->stkPrincipal->setCurrentIndex(0);
}

void MainWindow::on_cmdCreateFlow_2_clicked()
{
    string nome = ui->txtNameFlow_2->text().toStdString();
    double val = ui->txtVarFlow_2->text().toDouble();
    QMessageBox msg;

    for(int i = 0; i < flows.size(); i++){
        if(flows.at(i)->getName() == nome){
            msg.setText("Nome escolhido ja existe. Escolha outro e tente novamente.");
            return;
        }
    }

    Flow* f = factory->flowCreator<Flow2>();
    f->setName(nome);
    f->setVal(val);

    msg.setText("Fluxo criado com sucesso.");
    msg.exec();

    flows.push_back(f);

    ui->stkPrincipal->setCurrentIndex(0);
}

void MainWindow::on_lstAllSystens_activated(const QModelIndex &index)
{

}

void MainWindow::on_cmdEditSystem_clicked()
{
    QMessageBox msg;
    for(int i = 0; i < systens.size(); i++){
        if(systens.at(i)->getName() == ui->lstAllSystens->currentItem()->text().toStdString()){
            systens.at(i)->setValue(ui->txtSysValue->text().toDouble());
        }
    }

    msg.setText("Sistema editado com sucesso.");
    msg.exec();
}

void MainWindow::on_lstAllSystens_itemActivated(QListWidgetItem *item)
{

}

void MainWindow::on_actionImprimir_triggered()
{
    ui->lstAllSystens_3->clear();

    for(int i = 0; i < systens.size(); i++){
        ui->lstAllSystens_3->addItem(QString::fromStdString(systens.at(i)->getName()));
    }

    ui->stkPrincipal->setCurrentIndex(8);
}

void MainWindow::on_actionAdicionar_Sistema_triggered()
{
    /**/

    ui->stkPrincipal->setCurrentIndex(8);
}

void MainWindow::on_actionDestruir_2_triggered()
{
    ui->lstAllFlows_2->clear();
    ui->cmbEntrada->clear();
    ui->cmbSaida->clear();

    for(int i =0; i < flows.size(); i++){
        ui->lstAllFlows_2->addItem(QString::fromStdString(flows.at(i)->getName()));
    }

    ui->cmbEntrada->addItem(" ");
    ui->cmbSaida->addItem(" ");
    for(int i = 0; i < systens.size(); i++){
        ui->cmbEntrada->addItem(QString::fromStdString(systens.at(i)->getName()));
        ui->cmbSaida->addItem(QString::fromStdString(systens.at(i)->getName()));
    }

    ui->cmbEntrada->setCurrentText(" ");
    ui->cmbSaida->setCurrentText(" ");

    ui->stkPrincipal->setCurrentIndex(9);
}

void MainWindow::on_lstAllFlows_2_clicked(const QModelIndex &index)
{
    /*for(int i = 0; i < flows.size(); i++){
        if(flows.at(i)->getName() == ui->lstAllFlows_2->currentItem()->text().toStdString()){
            if(flows.at(i)->getInSystem() != NULL)
                ui->cmbEntrada->setCurrentText(QString::fromStdString(flows.at(i)->getInSystem()->getName()));
            if(flows.at(i)->getOutSystem() != NULL)
                ui->cmbSaida->setCurrentText(QString::fromStdString(flows.at(i)->getOutSystem()->getName()));
        }
    }*/
}

void MainWindow::on_cmdSalvarFluxos_clicked()
{

}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox msg;
    for(int i = 0; i < flows.size(); i++){
        for(int j = 0; j < systens.size(); j++){
            if(ui->lstAllFlows_2->currentItem()->text().toStdString() == flows.at(i)->getName()){
                if(ui->cmbEntrada->currentText().toStdString() == systens.at(j)->getName()){
                    flows.at(i)->setInSystem(systens.at(j));
                }
            }
            if(ui->lstAllFlows_2->currentItem()->text().toStdString() == flows.at(i)->getName()){
                if(ui->cmbSaida->currentText().toStdString() == systens.at(j)->getName()){
                    flows.at(i)->setOutSystem(systens.at(j));
                }
            }
        }
    }

    msg.setText("Sistemas adicionados com sucesso");
    msg.exec();

    ui->stkPrincipal->setCurrentIndex(0);
}

void MainWindow::on_cmdResultado_clicked()
{
    QMessageBox msg;
    System *sys;
    QList<double> list, antigo;
    list.clear();
    for(int i = 0; i < systens.size(); i++){
        if(systens.at(i)->getName() == ui->lstAllSystens_3->currentItem()->text().toStdString())
            sys = systens.at(i);
    }


    for(int i = 0; i < systens.size(); i++){
        antigo.push_back(systens.at(i)->getValue());
    }

    sys->clearResult();
    model->execute(sys);

    for(int i = 0; i < sys->impress().size();i++){
        list.push_back(sys->impress().at(i));
    }

    for(int i = 0; i < antigo.size(); i++){
        systens[i]->setValue(antigo[i]);
    }

    QStandardItemModel *qmodel = new QStandardItemModel(list.size(),2,this);
    qmodel->setHorizontalHeaderItem(0, new QStandardItem(QString("Tempo")));
    qmodel->setHorizontalHeaderItem(1, new QStandardItem(QString("Valor")));
    ui->tblResult->setModel(qmodel);


    int i;
    for(i = 0; i < list.size(); i++){
        qmodel->setItem(i,0,new QStandardItem(QString::number(i)));
        qmodel->setItem(i,1,new QStandardItem(QString::number(list.at(i))));
    }
}

void MainWindow::on_actionAbrir_triggered()
{
    ui->txtSaveModel->setText("");

    ui->stkPrincipal->setCurrentIndex(10);
}

void MainWindow::on_cmdSaveModel_clicked()
{
   /* QMessageBox msg;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=database.mdb");
    if(!db.open()){
        msg.setText("Erro: Banco não encontrado");
        msg.exec();
    }

    if(db.isOpen()){
        QSqlQuery query;

        for(int i = 0; i < model->getFlows().size(); i++){
            query.exec(QString("insert into Model(Nome,Flows) values('%1','%2')").arg(ui->txtSaveModel->text()).arg());
        }

        msg.setText("OK");
        msg.exec();
    }
    db.close();*/
}
