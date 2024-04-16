#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maincontroller.h"
#include "utils.h"

#include <QtGlobal>
#include <QVector>
#include <qlineseries.h>
#include <qchartview.h>
#include <qscatterseries.h>
#include <qlayout.h>
#include <QStringListModel>

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

    QList<QString> dsValidationNames;
    vector<string> datasetValidation = mainController->getValidationDatasets();
    dsValidationNames.reserve(datasetValidation.size());
    for (uint i = 0; i < datasetValidation.size(); i++) {
        dsValidationNames.push_back(QString::fromStdString(datasetValidation[i]));
    }
    ui->validationDatasetCB->addItems(dsValidationNames);

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
    this->chart = new QChart();
    chart->setTitle("Model Decision Line(s)");
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QWidget* chartWidget = ui->chartBox;

    if (chartWidget) {
        QVBoxLayout* chartLayout = new QVBoxLayout();
        chartLayout->addWidget(chartView);
        chartWidget->setLayout(chartLayout);
    }

}

void MainWindow::updateDataSetPlot() {
    vector<vector<double>> data = mainController->getData();

    dataSeries.clear();
    
    for (int i = 0; i < data.size(); ++i) {
        QPoint point(data[i][0], data[i][1]);
        dataSeries.append(point);
    }
    dataSeries.setName("Data Set");

    chart->addSeries(&dataSeries);
    chart->createDefaultAxes();
    chart->axisX()->setRange(Utils::findMin(data,0) - 0.5, Utils::findMax(data,0) + 0.5 );
    chart->axisY()->setRange(Utils::findMin(data, 1) - 0.5, Utils::findMax(data, 1) + 0.5);
    chart->update();
}

void MainWindow::updateLMGraph() {
    /*QLineSeries* identitySeries = new QLineSeries();
    for (int x = 0; x <= 10; ++x) {
        identitySeries->append(x, x);
    }
    identitySeries->setName("Decision Line");
    chart->addSeries(identitySeries);
    chart->createDefaultAxes();
    chart->update();*/
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

void MainWindow::on_startValidationBtn_clicked()
{
    try
    {
        QString dataset = ui->validationDatasetCB->property("currentText").toString();
        map<string,double> result = mainController->checkModelAccuracy(dataset.toStdString());

        int numRows = result.size();
        int numCols = 2; // 2 columns for string key and double value
        ui->validationResult->setRowCount(numRows);
        ui->validationResult->setColumnCount(numCols);

        QStringList headers;
        headers << "Label" << "Value";
        ui->validationResult->setHorizontalHeaderLabels(headers);

        int row = 0;
        for (const auto& pair : result) {
            // Set key
            QTableWidgetItem* keyItem = new QTableWidgetItem(QString::fromStdString(pair.first));
            ui->validationResult->setItem(row, 0, keyItem);

            // Set value
            QTableWidgetItem* valueItem = new QTableWidgetItem(QString::number(pair.second));
            /*
            if (pair.second == 0)
            {
                QColor color(0, 128, 0); // Yellow background color
                valueItem->setBackground(color);
            } else
            {
                QColor color(255, 165, 0); // Orange background color
                valueItem->setBackground(color);
            }
            */
            ui->validationResult->setItem(row, 1, valueItem);

            ++row;
        }

        ui->validationResult->resizeColumnsToContents();
        ui->validationResult->horizontalHeader()->setStretchLastSection(true);
        ui->validationResult->show();

    }
    catch (...) {
        ui->learningModelStatus->setText("Error");
        ui->learningModelStatus->setStyleSheet("QLabel {color: red;}");
    }
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
        int hiddenLayerSize = ui->hiddenLayerSizeInput->text().toInt();

        ui->learningModelStatus->setText("Learning...");
        ui->learningModelStatus->setStyleSheet("QLabel {color: orange;}");

        mainController->setupModel(modelIndex, dataset.toStdString(), learningRate, nbClass, this->ui->multiLayerCheckButton->isChecked(), hiddenLayerSize, activationFct);
        mainController->startTraining(maxIter, errorThreshold, minClassificationErrorAccepted);

        ui->learningModelStatus->setText("Ready");
        ui->learningModelStatus->setStyleSheet("QLabel {color: green;}");


        //ui->iterationMaxLabel->setText(QString("of %1").arg(mainController->iterationsSize(selectedLM) - 1));
        // TODO wait until end learning
        ui->startValidationBtn->setEnabled(true);
        selectedIteration = 0;

        updateDataSetPlot();
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

