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
  cin >> form;
  --------------------------------------------*/
  stepSize = (endFreq - startFreq) / steps;

  //DFT COMPUTATION FUNCTION ==================================================
  //complex<double> fourier[steps] = {};
  vector<complex<double>> fourier;
  DFT(data, fourier, steps, startFreq, stepSize, sampleSize);

  while(!showoutput(fourier, steps, startFreq, stepSize));

}