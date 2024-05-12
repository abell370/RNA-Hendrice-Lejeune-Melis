#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qchart.h>
#include <qscatterseries.h>
#include <qlineseries.h>
#include "maincontroller.h"
#include "dataset.h"
#include <qstandarditemmodel.h>
#include <map>

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
    void on_startValidationBtn_clicked();

    void on_nextIterBtn_clicked();

    void on_lastIterBtn_clicked();

    void on_iterationInput_textChanged(const QString& arg1);

private:
    Ui::MainWindow* ui;
    MainController* mainController;
    QStandardItemModel* model;
    QChart* chart;
    map<int, QScatterSeries*> dataSeries;
    vector<QLineSeries*> modelSeries;
    uint selectedIteration;
    uint selectedDataSet;
    uint selectedLM;

    void insertChart();
    void disbaleMultilayer(bool checked);
    void disableClassification(const QString& text);
    void disableEMoy(const QString& text);
    void updateDataSetPlot();
    void updateLMGraph();
    void resetWindow();
    vector<double> calcDecisionLine(vector<double> weights, vector<double> x);
};
#endif // MAINWINDOW_H
