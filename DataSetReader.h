#pragma once
#include "csvreader.h"
#include "dataset.h"

class DataSetReader
{
public:
	DataSet* read(string& filename, unsigned int classNb);
};

