#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionEditar_triggered();

    void on_cmdEditarModel_clicked();

    void on_actionAdicionar_Fluxo_triggered();

    void on_cmdAddFlowModel_clicked();

    void on_cmdRemFlowModel_clicked();

    void on_actionSair_triggered();

    void on_actionCriar_triggered();

    void on_actionEditar_2_triggered();

    void on_lstAllSystens_clicked(const QModelIndex &index);

    void on_txtSysValue_textChanged(const QString &arg1);

    void on_actionDestruir_triggered();

    void on_cmdDestruirSistema_clicked();

    void on_cmdCreateSystem_clicked();

    void on_actionLogistico_triggered();

    void on_actionExponencial_triggered();

    void on_cmdCreateFlow_clicked();

    void on_cmdCreateFlow_2_clicked();

    //void on_actionExecutar_triggered();

    void on_lstAllSystens_activated(const QModelIndex &index);

    void on_cmdEditSystem_clicked();

    void on_lstAllSystens_itemActivated(QListWidgetItem *item);

    void on_actionImprimir_triggered();

    //void on_actionAdicionar_Sistema_de_Entrada_triggered();

    void on_lstAllFlows_2_clicked(const QModelIndex &index);

    void on_actionAdicionar_Sistema_triggered();

    //void on_actionSistema_triggered();

    void on_actionDestruir_2_triggered();

    void on_cmdSalvarFluxos_clicked();

    void on_pushButton_clicked();

    void on_cmdResultado_clicked();

    void on_actionAbrir_triggered();

    void on_cmdSaveModel_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
