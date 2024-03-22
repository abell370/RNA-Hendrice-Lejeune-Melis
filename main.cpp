#include "mainwindow.h"
#include <vector>
#include <iostream>
#include <QApplication>
#include <qlineseries.h>
#include <qchartview.h>
#include <qscatterseries.h>

using namespace std;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    vector<DataSet> data = {};
    MainController* mainController = new MainController(data);
    MainWindow w(mainController);
    w.show();

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
    // Create a chart and add the series
    QChart* chart = new QChart();
    chart->addSeries(identitySeries);
    chart->addSeries(randomSeries);
    chart->setTitle("Simple Line Chart");
    chart->createDefaultAxes(); // Create default axes

    // Create a chart view and set the chart
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    w.setCentralWidget(chartView);
    w.show();
    return a.exec();
}

