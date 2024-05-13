#include "mainwindow.h"
#include <vector>
#include <iostream>
#include <QApplication>
#include <qlayout.h>
#include <fstream>

#include <filesystem>
#include "multilayer.h"
#include "sigmoidactivation.h"
#include "csvreader.h"
#include "DataSetReader.h"

using namespace std::filesystem;
using namespace std;

int main(int argc, char* argv[])
{
    
    // TODO à sortir de la fonction
    path directorypath = "data/";
    vector<string> pathToData = {};
    for (const auto& entry : directory_iterator(directorypath)) 
    {
        if (entry.is_regular_file() && entry.path().extension() == ".csv") {
            string filename = entry.path().filename().u8string();
            pathToData.push_back(filename);
        }
    }

    path directorypathValidation = "data/validation/";
    vector<string> pathToValidationData = {};
    for (const auto& entry : directory_iterator(directorypathValidation))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".csv") {
            string path = entry.path().filename().u8string();
            pathToValidationData.push_back(path);
        }
    }

    DataSetReader* dataSetReader = new DataSetReader();
    QApplication a(argc, argv);

    MainController* mainController = new MainController(pathToData, pathToValidationData,{"Adaline", "Gradient", "Simple"}, dataSetReader);
    MainWindow w(mainController);


    w.show();
    return a.exec();
   
    return 0;

}

