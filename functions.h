#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "functions.cpp"

using namespace std;

bool isDouble(string s, double& value);
bool isInt(string s, int& value);
bool datain(vector<double> &datain);

double getSampling();
double getStart();
double getEnd(double start);
int getSteps();
double getSSize(double start, double end, int steps);

vector<double> getDigital(vector<double> analogFreq, double sampling);
vector<complex<double>> DFT(vector<double> data, int steps, vector<double> omega);

void outputRect(vector<complex<double>> fourier, int steps, double startFreq, double stepSize);
void outputPol(vector<complex<double>> fourier, int steps, double startFreq, double stepSize);
bool showoutput(vector<complex<double>> fourier, int steps, double startFreq, double stepSize);
#endif