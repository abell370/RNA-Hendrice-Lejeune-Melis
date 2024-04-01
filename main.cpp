#include "mainwindow.h"
#include <vector>
#include <iostream>
#include <QApplication>
#include <qlayout.h>
#include <fstream>

#include <filesystem>
#include "deeplearning.h"
#include "stochastiqueactivation.h"

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
    vector<vector<double>> dataset = {
      {1.,0.9,0.1,0.9, 0.1, 0.9, 0.9}
    };

    DeepLearning model(dataset, { {0.,0.1,0.15,0.05},{0., 0.12,0.18,0.08} }, { {0.,0.1,0.14},{0.,0.125,0.21},{0.,0.13,0.07} }, 1.);
    model.learn(2, 3, 0.184, 3, new StochastiqueActivation());
    return 0;

}

