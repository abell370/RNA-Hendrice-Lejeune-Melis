#include "mainwindow.h"
#include <vector>
#include <iostream>
#include <QApplication>
#include <qlineseries.h>
#include <qchartview.h>
#include <qscatterseries.h>
#include <qlayout.h>

using namespace std;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    vector<DataSet> data = {};
    MainController* mainController = new MainController(data);
    MainWindow w(mainController);


    QLineSeries* identitySeries = new QLineSeries();
    for (int x = 0; x <= 10; ++x) {
        identitySeries->append(x, x);
    }
    identitySeries->setName("Identity Function");

    QScatterSeries* randomSeries = new QScatterSeries();
    for (int i = 0; i < 10; ++i) {
        QPoint point(i, rand() % 10); // Generate random points
        randomSeries->append(point);
    }
    randomSeries->setName("Random Points");

    QChart* chart = new QChart();
    chart->addSeries(identitySeries);
    chart->addSeries(randomSeries);
    chart->setTitle("Simple Line Chart");
    chart->createDefaultAxes(); 
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QWidget* chartWidget = w.findChild<QWidget*>("chart");

    if (chartWidget) {
        QVBoxLayout* chartLayout = new QVBoxLayout();
        chartLayout->addWidget(chartView);
        chartWidget->setLayout(chartLayout);
    }
    else {
        cerr << "Error: Could not find widget named 'chart'." << endl;
        return 1;
    }

    w.show();
    return a.exec();
}

