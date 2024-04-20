#include "DataSetReader.h"

DataSetReader::DataSetReader() {

}

DataSet* DataSetReader::read(string& filename, unsigned int classNb) {
	CSVReader* csvReader = new CSVReader(filename);
    
    if (!csvReader->readCSV()) {
        return NULL;
    }

	vector<vector<double>> data = csvReader->getData();
	vector<int> classes = vector<int>(data.size());

    if (classNb < 2) {
        if (data[0].size() < 3) { // si régression (0 ou 1 classe), pas de classe spécifiée
            for (int i = 0; i < data.size(); i++) {
                classes[i] = 1;
            }
        }
        else if (classNb == 2) {// si seulement 2 classes, colonne de classe binaire => 0,1 pour x,y et 2 pour classe binaire
            for (int i = 0; i < data.size(); i++) {
                classes[i] = data[i].back() > 0 ? 1 : 2;
            }
        }
        else {// si + de 2 classes, alors une colonne par classe
            for (int i = 0; i < data.size(); i++) {
                for (int j = data[i].size() - classNb, indivClass = 1; j < data[i].size(); j++, indivClass++) { // parcourt les classNb dernières colonnes (colonnes spécifiant la classe de l'individu)
                    if (data[i][j] > 0) {
                        classes[i] = indivClass;
                    }
                }
            }
        }
    }

    delete csvReader;

	return new DataSet(filename, data, classes);
}