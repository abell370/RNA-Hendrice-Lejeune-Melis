#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/*
    Classe permettant de charger les données d'un fichier csv
*/
class CSVReader {
public:
    CSVReader(const string& filename);
    ~CSVReader() {};

    vector<vector<double>> getData() const;
    bool readCSV();

private:
    string filename;
    vector<vector<double>> data;
};

