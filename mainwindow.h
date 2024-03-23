#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "maincontroller.h"
#include "dataset.h"
#include <qstandarditemmodel.h>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MainController* mainController, QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_startBtn_clicked();
    void updateIteration();
    void on_firstStepBtn_clicked();
    void on_previousIterBtn_clicked();

    void on_nextIterBtn_clicked();

    void on_lastIterBtn_clicked();

    void on_iterationInput_textChanged(const QString& arg1);

    void on_dataSetComboBox_currentIndexChanged(int index);

    void on_learningModelComboBox_currentIndexChanged(int index);

    void on_resetBtn_clicked();

private:
    Ui::MainWindow* ui;
    MainController* mainController;
    QStandardItemModel* model;
    uint selectedIteration;
    uint selectedDataSet;
    uint selectedLM;

    void insertChart();
    void updateDataSetPlot();
    void updateLMGraph();
    void updateIterationValues();
    void resetWindow();
    QVector<double> calcLinePoints(Iteration iteration);
};
#endif // MAINWINDOW_H
