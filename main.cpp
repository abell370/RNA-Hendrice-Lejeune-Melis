#include "mainwindow.h"
#include <vector>
#include <iostream>
#include <QApplication>
#include <qlayout.h>
#include <fstream>

#include <filesystem>

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
        pathToData.push_back(path);
    }

    QApplication a(argc, argv);

    MainController* mainController = new MainController(pathToData, {"Adaline", "Gradient", "Simple"});
    MainWindow w(mainController);


    w.show();
    return a.exec();
   
    
}

