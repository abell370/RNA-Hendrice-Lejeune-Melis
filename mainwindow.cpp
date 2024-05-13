#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maincontroller.h"

#include <QApplication>
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
    modelChart = this->insertChart("Model Decision Line(s)", ui->modelChart);
    lossChart = this->insertChart("Loss Diagram", ui->lossChart);

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

QChart* MainWindow::insertChart(QString title, QWidget* target)
{
    QChart* chart = new QChart();
    chart->setTitle(title);
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QWidget* chartWidget = target;

    if (chartWidget) {
        QVBoxLayout* chartLayout = new QVBoxLayout();
        chartLayout->addWidget(chartView);
        chartWidget->setLayout(chartLayout);
    }

    return chart;
}

void MainWindow::updateDataSetPlot() {
    DataSet* dataSet = mainController->getDataSet();
    vector<int> dataClasses;
    vector<vector<double>> entries;

    for (auto dataSerie : dataSeries) {
        modelChart->removeSeries(dataSerie.second);
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
            dataSeries[dataClass] = classSerie;
            modelChart->addSeries(classSerie);
        }

        QPointF point(entries[i][0], entries[i][1]);

        dataSeries.at(dataClass)->append(point);
    }
    
    modelChart->createDefaultAxes();
    modelChart->axisX()->setRange(dataSet->findMin(0) - 0.5, dataSet->findMax(0) + 0.5);
    modelChart->axisY()->setRange(dataSet->findMin(1) - 0.5, dataSet->findMax(1) + 0.5);
    modelChart->update();
}

void MainWindow::updateLMGraph() {
    vector<vector<double>> decisionWeights = mainController->getDecisionWeights(selectedIteration);
    DataSet* dataSet = mainController->getDataSet();
    int nbClass = ui->amountOfClassesInput->text().toInt();
    vector<double> x1 = { dataSet->findMin(0) - 0.5, dataSet->findMax( 0) + 0.5 };

    for (auto modelSerie : this->modelSeries) {
        modelChart->removeSeries(modelSerie);
    }
    modelSeries.clear();

    for (int i = 0; i < decisionWeights.size(); ++i) {
        vector<double> x2;
        if (ui->multiLayerCheckButton->isChecked() && nbClass == 1) {//Si régression non-linéaire
            x2 = this->predictPoints(x1);
        }
        else {
            x2 = this->calcDecisionLine(decisionWeights[i], x1);
        }
        QLineSeries* modelSerie = new QLineSeries();
        modelSerie->setName(QString("Neuron %1").arg(i + 1));

        for (int j = 0; j < x1.size(); ++j) {
            //QPoint point = QPoint(x1[j], x2[j]);
            modelSerie->append(x1[j],x2[j]);
        }
        modelChart->addSeries(modelSerie);
        modelSeries.push_back(modelSerie);
    }

    modelChart->createDefaultAxes();
    modelChart->axisX()->setRange(dataSet->findMin(0) - 0.5, dataSet->findMax(0) + 0.5);
    modelChart->axisY()->setRange(dataSet->findMin(1) - 0.5, dataSet->findMax(1) + 0.5);
    modelChart->update();
}

vector<double> MainWindow::calcDecisionLine(vector<double> weights, vector<double> x1) {
    int nbClass = ui->amountOfClassesInput->text().toInt();
    vector<double> line;
    double x2_i;
    for (double x1_i : x1) {
        switch (weights.size()) {
            case 2://regression => y = ax + b <=> y = w1 * x1 + w0
                x2_i = weights[1] * x1_i + weights[0];
                line.push_back(x2_i);
                break;
            case 3://classification
                x2_i = -(weights[0] + weights[1] * x1_i) / weights[2];
                line.push_back(x2_i);
                break;
            default:// + de 2 dimensions pas supporté
                break;
        }
    }
    return line;
}

vector<double> MainWindow::predictPoints(vector<double> &x1) {
    vector<double> x1Copy = vector<double>(x1);
    x1.clear();
    vector<double> x2;
    for (float i = x1Copy[0]; i < x1Copy[1]; i += 0.01) {
        vector<double> values = mainController->predict({ i });
        x1.push_back(i);
        x2.push_back(values[0]);
    }
    return x2;
}

void MainWindow::updateLossGraph(){
    vector<double> loss = mainController->getLoss();

    if(lossSeries != NULL){
        lossChart->removeSeries(lossSeries);
    }

    lossSeries = new QLineSeries();

    for (int i = 0; i < loss.size(); ++i) {
        lossSeries->append(i, loss[i]);
    }

    lossChart->addSeries(lossSeries);

    lossChart->createDefaultAxes();
    lossChart->update();
}


void MainWindow::updateSelectedIteration() {
    unsigned iterCount = mainController->getIterationCount();
    if(0 < iterCount && (0 <= selectedIteration && selectedIteration < iterCount)){
        ui->iterationInput->setText(QString::number(selectedIteration));
    }
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

        qApp->processEvents();

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

        updateDataSetPlot();
        updateLossGraph();
        on_firstStepBtn_clicked();
        updateLMGraph();
    }catch(...){
        ui->learningModelStatus->setText("Error");
        ui->learningModelStatus->setStyleSheet("QLabel {color: red;}");
    }

}

void MainWindow::on_firstStepBtn_clicked()
{
    selectedIteration = 0;
    updateSelectedIteration();
}


void MainWindow::on_previousIterBtn_clicked()
{
    if (selectedIteration > 0) {
        selectedIteration--;
    }
    updateSelectedIteration();
}


void MainWindow::on_nextIterBtn_clicked()
{
    if(selectedIteration < mainController->getIterationCount() - 1) {
        selectedIteration++;
    }
    updateSelectedIteration();
}


void MainWindow::on_lastIterBtn_clicked()
{
    unsigned iterCount = mainController->getIterationCount();
    if(iterCount > 0){
        selectedIteration = iterCount - 1;
    }
    updateSelectedIteration();

}


void MainWindow::on_iterationInput_textChanged(const QString& arg1)
{
    try {
        selectedIteration = arg1.toInt();
    }
    catch (...) {

    }
    this->updateLMGraph();
}
