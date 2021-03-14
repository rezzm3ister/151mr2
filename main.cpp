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
  vector<double> data; //vectors containing signal values
  int sampleSize = 0;

 
  while(!datain(data))
  {
    //loops until valid file is provided
  }
  
  //GETSIZE FUNCTION ==========================================================
  for(int i = 0; i < data.size(); i++)
  {
    sampleSize++;
  }
  //===========================================================================

  //shows signal values from file
  showdata(data,"Data");

  double sampleFreq, startFreq, endFreq, stepSize;
  int steps, form;

  cout << "\nInput sampling rate (Hz): ";
  cin >> sampleFreq;
  cout << "Input start frequency (Hz): ";
  cin >> startFreq;
  cout << "Input end frequency (Hz): ";
  cin >> endFreq;
  cout << "Input number of steps from start to end: ";
  cin >> steps;

  /* -----------NOT YET IMPLEMENTED------------  
  cout << "Specify output form: "
       << "\n1 - real and imaginary parts"
       << "\n2 - magnitude and phase"
       << "\n3 - both" << endl;
  cin >> form;
  --------------------------------------------*/
  stepSize = (endFreq - startFreq) / steps;

  //DFT COMPUTATION FUNCTION ==================================================
  //complex<double> fourier[steps] = {};
  vector<complex<double>> fourier;
  DFT(data, fourier, steps, startFreq, stepSize, sampleSize);
  /*
  const complex<double> j(0.0,1.0); //define imaginary j
  double pi = 2 * asin(1); //define pi
  double k; //the current frequency

  //temporary computational variables
  double exponent;
  complex<double> sum;
  int index;

  for (int m = 0; m < steps; m++)
  {
    sum = 0;
    index = 0;
    k = startFreq + stepSize*m;
    for (int n = 0; n < sampleSize; n++)
    {
      //exponent in DFT formula
      exponent = (2 * pi * k * n) / sampleSize;

      //applying euler's formula: e^(jx) = cos(x) + j*sin(x)
      sum = sum + data[index]*(cos(-exponent) + j*sin(-exponent));
      index++;
    }
    //fourier[m] = sum;
    fourier.push_back(sum);
  }
  */
  //===========================================================================

  // SHOW OUTPUT FUNCTION ===================================================== 
  double currentFreq;
  cout << "Fourier Transform: \n\n";

  cout << "Analog Frequency (Hz)\tReal Part\tImaginary Part" << endl;
  for(int i = 0; i < steps ; i++)
  {
      currentFreq = startFreq + stepSize*i; //analog frequency for current DFT value
      cout << currentFreq << "\t\t\t" << fourier[i].real() << "\t\t" << fourier[i].imag() << endl;
  }
  cout << endl;
  //===========================================================================
}