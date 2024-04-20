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
        string path = entry.path().filename().u8string();
        if (path.find(".csv"))
            pathToData.push_back(path);
    }

    path directorypathValidation = "data/validation/";
    vector<string> pathToValidationData = {};
    for (const auto& entry : directory_iterator(directorypathValidation))
    {
        string path = entry.path().filename().u8string();
        pathToValidationData.push_back(path);
    }

    DataSetReader* dataSetReader = new DataSetReader();
    QApplication a(argc, argv);

    MainController* mainController = new MainController(pathToData, pathToValidationData,{"Adaline", "Gradient", "Simple"}, dataSetReader);
    MainWindow w(mainController);


    w.show();
    return a.exec();
   
    
    /*
    vector<vector<double>> dataset = {
      {0.9,0.1,0.9, 0.1, 0.9, 0.9}
    };

    DeepLearning model(dataset);
    model.setup(2, 3, 1.);
    model.learn(0.184, 1, new SigmoidActivation());
    */
  
    return 0;

}

