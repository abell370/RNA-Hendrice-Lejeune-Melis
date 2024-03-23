#pragma once

#include <QChartView>

class GraphWidget  : public QChartView
{
	Q_OBJECT

public:
	GraphWidget(QChartView*parent);
	~GraphWidget();
};
