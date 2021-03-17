#include <iostream>
#include <vector>
#include <math.h>
#include <complex>
#include <fstream>
#include <sstream>
#include <string>
#include "functions.h"

using namespace std;

bool isDouble(string s, double& value)
{
  double temp; //sets a temp variable
  
  //checks if the content is a valid double ignoring whitespaces
  bool check = (istringstream(s) >> temp >> ws).eof();

  if(check == 0)
  {
    return false;
    //returns 0 without updating value
  }

  else
  {
    value = temp;
    return true;
    //returns 1 and updates value
  }
}

bool isInt(string s, int& value)
{
  int temp; //sets a temp variable

  //checks if the content is a valid int ignoring whitespaces
  bool check = (istringstream(s) >> temp >> ws).eof();

  if(check == 0)
  {
    return false;
    //returns 0 without updates value
  }

  else
  {
    value = temp;
    return true;
    //returns 1 and updating value
  }
}

bool datain(vector<double> &datain)
{
  string fname;
  cout << "File Name for input signal: ";
  getline(cin,fname); //take user input filename
  string ts; //string being read in file
  double tempv; //temp storage for valid doubles
  int tempi; //temp storage for valid start index

  fstream fin;
  fin.open(fname);
  if(!fin) //if file not found/invalid, throw error
  {
    cout<<"Error, file not detected. Try again.\n\n";
    return 0;
  }
  else //check for possible index on first line
  {
    fin >> ts; //check first string in file

    //if not int, either no specified index or invalid file
    if(!isInt(ts,tempi))
    {
      cout << "Index not specified, checking if valid double.\n";
      
      //if first entry is not double, invalid file
      if(!isDouble(ts,tempv))
      {
        cout<<"Error, not a valid signal file.\n\n";
        return 0;
      }
      else //if double, set index to 0
      {
        cout<<"Valid signal file found.\n\n";

        //returns to start of file so it may read signal value
        fin.seekg(0, fin.beg);
      }
    }
    else //if first entry is int
    {
      getline(fin,ts); //read the rest of the first line
  
      stringstream ss(ts);
      string ts2;
      ss >> ts2; //read string after the first int

      //if followed by double, first int is index
      if((isDouble(ts2,tempv)) && (!ts2.empty()))
      {
        cout<<"Valid signal file found.\n\n";
        fin.seekg(0, fin.beg);
        fin >> ts; //go to second string
      }
      else //if no double after, first int is signal value
      {
        cout<<"Valid signal file found.\n\n";
        fin.seekg(0, fin.beg);
      }
    }

    while(!fin.eof()) //reads until end of file
    {
      fin >> ts; //reads the first string in a line

      //if double and not blank
      if((isDouble(ts,tempv)) && (ts != ""))
      {
        datain.push_back(tempv); //add value to data vector
      }
      else
      {
        break; //ends when start of line is not valid signal value
      }
      
      getline(fin,ts); //skips the rest of the line
    }
  }
  return 1;
}

double getSampling()
{
  string testSampling;
  double sampling = 0;
  do
  {
    cout << "Input sampling frequency (Hz): ";
    getline(cin, testSampling);
  } while(!isDouble(testSampling, sampling) || (sampling <= 0));

  return sampling;
}

double getStart()
{
  string testStart;
  double start;
  do
  {
    cout << "Input start frequency (Hz): ";
    getline(cin, testStart);
  } while (!isDouble(testStart, start));
  
  return start;
}

double getEnd(double start)
{
  string testEnd;
  double end;
  do
  {
    cout << "Input end frequency (Hz): ";
    getline(cin, testEnd);
  } while(!isDouble(testEnd, end) || (end <= start));

  return end;
}

int getSteps()
{
  string testSteps;
  int steps = 0;
  do
  {
    cout << "Input number of steps: ";
    getline(cin, testSteps);
  } while(!isInt(testSteps, steps) || steps <= 0);

  return steps;
}

double getSSize(double start, double end, int steps)
{
  return (end - start) / steps;
}

vector<double> getDigital(double startFreq, int steps, double stepSize, double sampling)
{
  vector<double> digital;
  const double pi = 2 * asin(1); //define pi
  double currentFreq = 0;

  for(int i = 0; i <= steps; i++)
  {
    currentFreq = startFreq + stepSize*i;
    digital.push_back(2*pi*currentFreq/sampling);
  }
  return digital;
}

vector <complex<double>> DFT(vector<double> data, int steps, vector<double> omega)
{
  const complex<double> j(0.0,1.0); //define imaginary j
  complex<double> sum; //temp var
  vector<complex<double>> fourier;

  for (int m = 0; m <= steps; m++)
  {
    sum = 0;

    for (int n = 0; n < data.size(); n++)
    {
      sum = sum + data[n] * exp(-1 * omega[m] * n * j);
    }
    fourier.push_back(sum);
  }
  return fourier;
}

void outputRect(vector<complex<double>> fourier, int steps, double startFreq, double stepSize)
{
  ofstream outfile;
  string ofn;
  double currentFreq = 0;

  cout<<"Enter output file name for rectangular form: ";
  cin>>ofn;

  outfile.open(ofn);
  outfile << "Analog Frequency (Hz)\tReal Part\tImaginary Part" << endl;
  cout << "Analog Frequency (Hz)\tReal Part\tImaginary Part" << endl;
  for(int i = 0; i <= steps ; i++)
  {
    currentFreq = startFreq + stepSize*i;
    outfile << currentFreq << "\t\t\t" << fourier[i].real() << "\t\t" << fourier[i].imag() << endl;

    cout << currentFreq << "\t\t\t" << fourier[i].real() << "\t\t" << fourier[i].imag() << endl;
  }
  cout << endl;
}

void outputPol(vector<complex<double>> fourier, int steps, double startFreq, double stepSize)
{
  ofstream outfile;
  string ofn;
  double currentFreq = 0;
  const double pi = 2 * asin(1);
  
  cout<<"Enter output file name for polar form: ";
  cin>>ofn;
  outfile.open(ofn);
  outfile << "Analog Frequency (Hz)\tMagnitude\tPhase" << endl;
  cout << "Analog Frequency (Hz)\tMagnitude\tPhase" << endl;
  for(int i = 0; i <= steps ; i++)
  {
    currentFreq = startFreq + stepSize*i;
    outfile << currentFreq << "\t\t\t" << std::abs(fourier[i]) << "\t\t" << atan2(fourier[i].imag(), fourier[i].real())*180/pi << endl;

    cout << currentFreq << "\t\t\t" << std::abs(fourier[i]) << "\t\t" << atan2(fourier[i].imag(), fourier[i].real())*180/pi << endl;
  }
  cout << endl;

}

bool showoutput(vector<complex<double>> fourier, int steps, double startFreq, double stepSize)
{
  ofstream outfile;
  string ofn;
  char choice = 'n';
  cout<<"\nSelect form/s to export to file/s.\n";
  cout<<"1: Rectangular Form\n2: Polar Form\n3: Both forms\n0: Exit\n";
  cout<<"Selection: ";
  cin>>choice;
  cout<<endl;

  switch(choice)
  {
    case '1':
      outputRect(fourier, steps, startFreq, stepSize);
      break;
    case '2':
      outputPol(fourier, steps, startFreq, stepSize);
      break;
    case '3':
      outputRect(fourier, steps, startFreq, stepSize);
      outputPol(fourier, steps, startFreq, stepSize);
      break;
    case '0':
      cout << "Write to file cancelled.";
      return 1;
    default:
      cout << "Invalid input. Please try again." << endl;
      return 0;
  }
  outfile.close();
  return 1;
}