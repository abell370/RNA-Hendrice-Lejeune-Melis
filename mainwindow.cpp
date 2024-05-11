#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maincontroller.h"

#include <QtGlobal>
#include <QVector>
#include <qlineseries.h>
#include <qchartview.h>
#include <qscatterseries.h>
#include <qlayout.h>
#include <QStringListModel>
#include <unordered_set>

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

    disbaleMultilayer(true);
    connect(ui->monolayerCheckButton, &QRadioButton::toggled, this, &MainWindow::disbaleMultilayer);
    connect(ui->minErrorInput, &QLineEdit::textChanged, this, &MainWindow::disableClassification);
    connect(ui->maxClassificationErrorInput, &QLineEdit::textChanged, this, &MainWindow::disableEMoy);

    /*
    ui->iterationSteps->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model->setHorizontalHeaderLabels({ "k","w0","w1","w2","x0","x1","x2","y","d","e" });
    
    ui->iterationSteps->setModel(model);
    */
    //this->updateDataSetPlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::disableClassification(const QString& text)
{
    ui->maxClassificationErrorInput->setEnabled(text.isEmpty());

}

void MainWindow::disableEMoy(const QString& text)
{
    ui->minErrorInput->setEnabled(text.isEmpty());

}

void MainWindow::disbaleMultilayer(bool checked)
{
    ui->activationFctHLayer->setEnabled(!checked);
    ui->activationFctOLayer->setEnabled(!checked);
    ui->hiddenLayerSizeInput->setEnabled(!checked);

    ui->activationFctGlobal->setEnabled(checked);
    ui->learningModelComboBox->setEnabled(checked);
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
    DataSet* dataSet = mainController->getDataSet();
    vector<QString> colors = {"blue","red","yellow","green","cyan","magenta","gray"};
    vector<int> dataClasses;
    vector<vector<double>> entries;

    for (auto dataSerie : dataSeries) {
        chart->removeSeries(dataSerie.second);
    }
    dataSeries.clear();

    dataClasses = dataSet->getDataClasses();
    entries = dataSet->getEntries();

    // For each data entry, add a point to corresponding data class scatter
    for (int i = 0; i < entries.size(); ++i) {
        int dataClass = dataSet->getDataClasses()[i];

        if (dataSeries[dataClass] == NULL) {
            QScatterSeries* classSerie = new QScatterSeries();
            classSerie->setName(QString("%1").arg(dataClass));
            classSerie->setColor(colors[dataClass % colors.size()]);
            //dataSeries.emplace(dataClass, classSerie);
            dataSeries[dataClass] = classSerie;
            chart->addSeries(classSerie);
        }

        QPointF point(entries[i][0], entries[i][1]);

        dataSeries.at(dataClass)->append(point);
    }
    
    chart->createDefaultAxes();
    chart->axisX()->setRange(dataSet->findMin(0) - 0.5, dataSet->findMax(0) + 0.5);
    chart->axisY()->setRange(dataSet->findMin(1) - 0.5, dataSet->findMax(1) + 0.5);
    chart->update();
}

void MainWindow::updateLMGraph() {
    vector<vector<double>> decisionWeights = mainController->getDecisionWeights(selectedIteration);
    DataSet* dataSet = mainController->getDataSet();
    vector<double> x1 = { dataSet->findMin(0) - 0.5, dataSet->findMax( 0) + 0.5 };
    vector<vector<double>> decisionLines;

    for (auto modelSerie : this->modelSeries) {
        chart->removeSeries(modelSerie);
    }
    modelSeries.clear();

    if (decisionWeights.size() > 0) {

        for (vector<double> weights : decisionWeights) {
            vector<double> x2 = this->calcDecisionLine(weights, x1);
            QLineSeries* modelSerie = new QLineSeries();

            for (int i = 0; i < x2.size(); ++i) {
                modelSerie->append(QPointF(x1[i], x2[i]));
            }

            chart->addSeries(modelSerie);
            modelSeries.push_back(modelSerie);
        }

        chart->update();
    }
}

vector<double> MainWindow::calcDecisionLine(vector<double> weights, vector<double> x1) {
    vector<double> line;
    for (double x1_i : x1) {
        switch (weights.size()) {
            case 2://regression
                line.push_back(-(weights[0] * x1_i) / weights[1]);
                break;
            case 3://classification
                line.push_back(-(weights[0] + weights[1] * x1_i) / weights[2]);
                break;
            default:
                break;
        }
    }
    return line;
}


void MainWindow::updateIteration() {
    unsigned iterCount = mainController->getIterationCount();
    if(0 < iterCount && (0 <= selectedIteration && selectedIteration < iterCount)){
        ui->iterationInput->setText(QString::number(selectedIteration));
        this->updateLMGraph();
        this->updateIterationValues();
    }
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
            QTableWidgetItem* valueItem = new QTableWidgetItem(QString::number(pair.second, 'g', 10));
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
        int hiddenLayerSize = ui->hiddenLayerSizeInput->text().toInt();

        ui->learningModelStatus->setText("Learning...");
        ui->learningModelStatus->setStyleSheet("QLabel {color: orange;}");
        vector<int> aFunctions = {};
        if (this->ui->multiLayerCheckButton->isChecked() )
        {
            aFunctions.push_back(ui->activationFctHLayer->currentIndex());
            aFunctions.push_back(ui->activationFctOLayer->currentIndex());
        }
        else
        {
            aFunctions.push_back(ui->activationFctGlobal->currentIndex());
        }
        mainController->setupModel(modelIndex, dataset.toStdString(), learningRate, nbClass, this->ui->multiLayerCheckButton->isChecked(), hiddenLayerSize, aFunctions, this->ui->randomWeights->isChecked());
        History* history = mainController->startTraining(maxIter, errorThreshold, minClassificationErrorAccepted);

        int numRows = history->size();
        int numCols = 2;
        ui->resultTable->reset();
        ui->resultTable->setRowCount(numRows);
        ui->resultTable->setColumnCount(numCols);

        string label = "";
        QColor color;
        for (int row = 0; row < numRows; ++row) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(history->getMSE(row), 'g', 10)); // Adjust precision as needed
            ui->resultTable->setItem(row, 0, item); // Corrected column index
            QTableWidgetItem* item2 = new QTableWidgetItem(QString::number(history->getClassification(row), 'g', 10)); // Adjust precision as needed
            ui->resultTable->setItem(row, 1, item2); // Corrected column index
            if (label != history->getLabel(row))
            {
                label = history->getLabel(row);
                color = QColor(rand() % 256, rand() % 256, rand() % 256);
            }
            item->setBackground(color);
            item2->setBackground(color);
        }

        if (numRows > 15) {
            ui->resultTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        }

        ui->resultTable->setHorizontalHeaderLabels({ "eMoy evolution","classification error"});
        
        ui->learningModelStatus->setText("Ready");
        ui->learningModelStatus->setStyleSheet("QLabel {color: green;}");


        ui->iterationMaxLabel->setText(QString("of %1").arg(mainController->getIterationCount() - 1));
        // TODO wait until end learning
        ui->startValidationBtn->setEnabled(true);
        selectedIteration = 0;

        updateDataSetPlot();
        updateLMGraph();
        //updateIteration();
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
    if(selectedIteration < mainController->getIterationCount() - 1) {
        selectedIteration++;
    }
    updateIteration();
}


void MainWindow::on_lastIterBtn_clicked()
{
    unsigned iterCount = mainController->getIterationCount();
    if(iterCount > 0){
        selectedIteration = iterCount - 1;
    }
    updateIteration();

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

