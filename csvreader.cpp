#include "csvreader.h"

CSVReader::CSVReader(const string& filename) : filename(filename) {}

vector<vector<double>> CSVReader::getData() const {
    return data;
}

bool CSVReader::readCSV() {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    data.clear(); // Clear existing data

    while (getline(file, line)) {
        stringstream ss(line);
        vector<double> row;
        string cell;

        while (getline(ss, cell, ',')) {
            // Convert the cell value to double
            double value = stod(cell);
            row.push_back(value);
        }

        data.push_back(row);
    }

    file.close();
    return true;
}
