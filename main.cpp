#include "mainwindow.h"
#include <vector>
#include <iostream>
#include <QApplication>
#include <qlayout.h>
#include <fstream>

#include <filesystem>
#include "deeplearning.h"
#include "sigmoidactivation.h"
#include "csvreader.h"

using namespace std::filesystem;
using namespace std;

int main(int argc, char* argv[])
{
    /*
    // TODO à sortir de la fonction
    path directorypath = "data/";
    vector<string> pathToData = {};
    for (const auto& entry : directory_iterator(directorypath)) 
    {
        string path = entry.path().filename().u8string();
        pathToData.push_back(path);
    }

    QApplication a(argc, argv);

    MainController* mainController = new MainController(pathToData, {"Adaline", "Gradient", "Simple"});
    MainWindow w(mainController);


    w.show();
    return a.exec();
   
    */

    CSVReader reader("data/table_4_12.csv");
    if (reader.readCSV())
    {
        vector<vector<double>> dataset = reader.getData();
        // Sert à ajouter le x0 aux données => TODO aller modofier les algos pour ne pas devoir modifier les données de bases
        for (auto& point : dataset) {
            point.insert(point.begin(), 1.);
        }
        DeepLearning model(dataset);
        model.setup(2, 1, 1, 0.5);
        model.learn(0.001, 2000, new SigmoidActivation());
    }

  
    return 0;

}

