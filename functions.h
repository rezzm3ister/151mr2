#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "functions.cpp"

using namespace std;

bool isDouble(string s, double& value);
bool isInt(string s, int& value);
bool datain(vector<double> &datain);
void showdata(vector<double> data, string ttype);

void DFT(vector<double> data, vector<complex<double>> &fourier, int steps, double startFreq, double stepSize, int sampleSize);

bool showoutput(vector<complex<double>> fourier, int steps, double startFreq, double stepSize);

#endif