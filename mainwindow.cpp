#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maincontroller.h"

#include <QtGlobal>
#include <QVector>
#include <qlineseries.h>
#include <qchartview.h>
#include <qscatterseries.h>
#include <qlayout.h>

MainWindow::MainWindow(MainController* mainController, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), mainController(mainController)
{
    model = new QStandardItemModel();

    ui->setupUi(this);
    this->setWindowTitle("RNA_Hendrice_Lejeune_Melis_Juin_2024");
    ui->scrollArea->setWidgetResizable(true);
    this->insertChart();

    this->selectedIteration = 0;
    this->selectedDataSet = 0;
    
    QList<QString> lmNames;
    vector<string> models = mainController->getLearningModels();
    lmNames.reserve(models.size());
    for (uint i = 0; i < models.size(); i++) {
        lmNames.push_back(QString::fromStdString(models[i]));
    }
    ui->learningModelComboBox->addItems(lmNames);

    QList<QString> dsNames;
    vector<string> dataSets = mainController->getDataSets();
    dsNames.reserve(dataSets.size());
    for (uint i = 0; i < dataSets.size(); i++) {
        dsNames.push_back(QString::fromStdString(dataSets[i]));
    }
    ui->dataSetComboBox->addItems(dsNames);

    /*
    ui->iterationSteps->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model->setHorizontalHeaderLabels({ "k","w0","w1","w2","x0","x1","x2","y","d","e" });
    
    ui->iterationSteps->setModel(model);
    */
    this->updateDataSetPlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertChart()
{
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
    QWidget* chartWidget = ui->chart;

    if (chartWidget) {
        QVBoxLayout* chartLayout = new QVBoxLayout();
        chartLayout->addWidget(chartView);
        chartWidget->setLayout(chartLayout);
    }

}

void MainWindow::updateDataSetPlot() {
    //DataSet dataSet = mainController->getDataSet(selectedDataSet);
    /*
    QCustomPlot *plot = ui->plot;

    double minX1 = dataSet.findMin(1), maxX1 = dataSet.findMax(1);
    double minX2 = dataSet.findMin(2), maxX2 = dataSet.findMax(2);
    plot->xAxis->setRange(minX1 - 0.5, maxX1 + 5.5);
    plot->yAxis->setRange(minX2 - 0.5, maxX2 + 5.5);
    plot->graph(0)->setData(dataSet.getXValues(1), dataSet.getXValues(2));
    plot->replot();
*/
}

void MainWindow::updateLMGraph() {
    /*
    if(ui->plot->graphCount() < 2){
        return;
    }
    QVector<double> x1 = {-20,20};
    QVector<double> x2 = mainController->calcGraph(selectedLM, selectedIteration, std::vector<double>(x1.begin(), x1.end()));
    QCustomPlot *plot = ui->plot;

    plot->graph(1)->setData(x1,x2);
    plot->replot();
*/
}

void MainWindow::updateIteration() {
    /*
    if(mainController->hasIterations(selectedLM)){
        ui->iterationInput->setText(QString::number(selectedIteration));
        this->updateLMGraph();
        this->updateIterationValues();
    }
*/
}

void MainWindow::updateIterationValues() {
    /*
    Iteration iteration = mainController->getIteration(this->selectedLM, this->selectedIteration);
    std::vector<Step> steps = iteration.getSteps();
    Step *step;

    if(steps.size() == 0){
        return;
    }

    step = &steps[0];

    this->model = new QStandardItemModel(0, 4 + (2 * steps[0].weights.size()));// 4 (k,y,d,e) + 2 * size of weight|entries (w0*x0, w1*x1,...)

    QStringList headerLabels = {"k"};
    for(unsigned int i = 0; i < step->weights.size(); ++i){
        headerLabels.append(QString("w%1").arg(i));
    }
    for(unsigned int i = 0; i < step->entries.size() - 1; ++i){//-1 as the expected output (d), is at the end of the entries and shouldn't be displayed twice
        headerLabels.append(QString("x%1").arg(i));
    }
    headerLabels.append({"y","d","e"});
    this->model->setHorizontalHeaderLabels(headerLabels);

    for(unsigned int i = 0; i < steps.size(); i++){
        step = &steps[i];
        QList<QStandardItem*> row;
        row.append(new QStandardItem(QString::number(step->k)));
        for(unsigned int w = 0; w < step->weights.size(); w++){
            QStandardItem* weight = new QStandardItem(QString::number(step->weights[w]));
            row.append(weight);
        }
        for(unsigned int x = 0; x < step->entries.size() - 1; x++){
            QStandardItem* entry = new QStandardItem(QString::number(step->entries[x]));
            row.append(entry);
        }
        row.append(new QStandardItem(QString::number(step->y)));
        row.append(new QStandardItem(QString::number(step->d)));
        row.append(new QStandardItem(QString::number(step->e)));
        this->model->insertRow(i, row);
    }

    ui->iterationErrorLabel->setText(QString("%1 errors").arg(iteration.getErrorNb()));
    ui->iterationSteps->setModel(this->model);
*/
}

void MainWindow::on_startBtn_clicked()
{
    
    try{
        int maxIter = ui->maxIterInput->text().toInt();
        double errorThreshold = ui->minErrorInput->text().toDouble();
        double learningRate = ui->learningRateInput->text().toDouble();
        int modelIndex = ui->learningModelComboBox->currentIndex();
        QString dataset = ui->dataSetComboBox->property("currentText").toString();
        int nbClass = ui->amountOfClassesInput->text().toInt();
        int minClassificationErrorAccepted = ui->maxClassificationErrorInput->text().toInt();
        int activationFct = ui->activationFctComboBox->currentIndex();

        ui->learningModelStatus->setText("Learning...");
        ui->learningModelStatus->setStyleSheet("QLabel {color: orange;}");

        mainController->setupModel(modelIndex, dataset.toStdString(), learningRate, nbClass, this->ui->multiLayerCheckButton->isChecked());
        mainController->startTraining(maxIter, errorThreshold, minClassificationErrorAccepted, activationFct);

        ui->learningModelStatus->setText("Ready");
        ui->learningModelStatus->setStyleSheet("QLabel {color: green;}");


        //ui->iterationMaxLabel->setText(QString("of %1").arg(mainController->iterationsSize(selectedLM) - 1));

        selectedIteration = 0;

        updateIteration();
    }catch(...){
        ui->learningModelStatus->setText("Error");
        ui->learningModelStatus->setStyleSheet("QLabel {color: red;}");
    }

}

void MainWindow::on_firstStepBtn_clicked()
{
    selectedIteration = 0;
    updateIteration();
}


void MainWindow::on_previousIterBtn_clicked()
{
    if (selectedIteration > 0) {
        selectedIteration--;
    }
    updateIteration();
}


void MainWindow::on_nextIterBtn_clicked()
{
    /*
    if(selectedIteration < mainController->iterationsSize(selectedLM) - 1){
        selectedIteration++;
    }
    updateIteration();
*/
}


void MainWindow::on_lastIterBtn_clicked()
{
    /*
    if(mainController->iterationsSize(selectedLM) > 0){
        selectedIteration = mainController->iterationsSize(selectedLM) - 1;
    }
    updateIteration();
*/
}


void MainWindow::on_iterationInput_textChanged(const QString& arg1)
{
    try {
        selectedIteration = arg1.toInt();
    }
    catch (...) {

    }
    updateIteration();
}


void MainWindow::on_dataSetComboBox_currentIndexChanged(int index)
{
    /*
    if(selectedDataSet != index){
        selectedDataSet = index;
        this->updateDataSetPlot();

        mainController->reset(selectedLM);
        this->resetWindow();
        this->updateLMGraph();
    }
*/
}


void MainWindow::on_learningModelComboBox_currentIndexChanged(int index)
{
    /*
    selectedLM = index;
    this->updateLMGraph();

    if(mainController->hasIterations(selectedLM)){
        ui->learningModelStatus->setText("Ready");
        ui->learningModelStatus->setStyleSheet("QLabel {color: green;}");
        this->updateIterationValues();
        ui->iterationMaxLabel->setText(QString("of %1").arg(mainController->iterationsSize(selectedLM) - 1));
    }else{
        this->resetWindow();
    }
*/
}


void MainWindow::on_resetBtn_clicked()
{
    /*
    mainController->reset(selectedLM);
    this->resetWindow();
*/
}

void MainWindow::resetWindow() {
    /*
    ui->learningModelStatus->setText("Not Ready");
    ui->learningModelStatus->setStyleSheet("QLabel {}");

    this->model->clear();
    ui->iterationErrorLabel->setText("0 errors");
    ui->iterationMaxLabel->setText("of 0");

    this->updateDataSetPlot();
    this->updateLMGraph();
*/
}

