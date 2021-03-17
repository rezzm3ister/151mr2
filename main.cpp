#include <iostream>
#include <vector>
#include <math.h>
#include <complex>
#include <fstream>
#include <sstream>
#include <string>
#include "functions.h"

using namespace std;

int main()
{
  vector<double> data; //vector containing signal values
 
  while(!datain(data));

  double sampleFreq = getSampling();
  double startFreq = getStart();
  double endFreq = getEnd(startFreq);
  int steps = getSteps();

  double stepSize = getSSize(startFreq, endFreq, steps);

  vector<double> digital = getDigital(startFreq, steps, stepSize, sampleFreq);
  vector<complex<double>> fourier = DFT(data, steps, digital);

  while(!showoutput(fourier, steps, startFreq, stepSize));
}