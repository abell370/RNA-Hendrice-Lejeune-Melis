#pragma once

#include <vector>
#include <unordered_set>

using namespace std;

class Utils
{
public:
	static vector<double> generateRandom(int size);
	static vector<double> calcDecisionLine(vector<double> weights, vector<double> x);
};