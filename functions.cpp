#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>
#include <complex>
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
    //returns 1 and updating value
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
    //returns 0 without updating value
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



//for showing necessary data
void showdata(vector<double> data, string ttype)
{
  cout << ttype << ": ";
  for(int i = 0; i < data.size(); i++)
  {
    if(i == data.size() - 1)
    {
      cout << data[i];
    }
    else
    {
      cout << data[i] << ", ";
    }
  }
  cout << endl;
}

void DFT(vector<double> data, vector<complex<double>> &fourier, 
        int steps, double startFreq, double stepSize, int sampleSize)
{
  const complex<double> j(0.0,1.0); //define imaginary j
  const double pi = 2 * asin(1); //define pi
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
}

bool showoutput(vector<complex<double>> fourier, int steps, 
                double startFreq, double stepSize)
{
  ofstream outfile;
  string ofn;
  double currentFreq=0;
  char choice = 'n', choice2 = 'm';
  const double pi = 2 * asin(1);
  cout<<"Select Output Form\n";
  cout<<"1: Rectangular Form\n2: Polar Form\n";
  cout<<"3: Both forms\n0: Exit\n";
  cout<<"Selection: ";
  cin>>choice;
  cout<<endl<<endl;

  switch(choice)
  {
    case '1':
      cout << "Fourier Transform: \n\n";
      cout << "Analog Frequency (Hz)\tReal Part\t\tImaginary Part" << endl;
      for(int i = 0; i < steps ; i++)
      {
          currentFreq = startFreq + stepSize*i; 
          //analog frequency for current DFT value
          cout << currentFreq << "\t\t\t" << fourier[i].real() 
               << "  \t\t" << fourier[i].imag() << endl;
      }
      cout << endl;
      break;
    case '2':
      cout << "Fourier Transform: \n\n";
      cout << "Analog Frequency (Hz)\tMagnitude\t\tAngle" << endl;
      for(int i = 0; i < steps ; i++)
      {
          currentFreq = startFreq + stepSize*i; 
          //analog frequency for current DFT value
          cout << currentFreq << "\t\t\t" << abs(fourier[i]) 
               << "  \t\t" << arg(fourier[i])*180/pi << endl;
      }
      cout << endl;
      break;
    case '3':
      cout << "Rectangular Form: \n\n";
      cout << "Analog Frequency (Hz)\tReal Part\t\tImaginary Part" << endl;
      for(int i = 0; i < steps ; i++)
      {
          currentFreq = startFreq + stepSize*i; 
          //analog frequency for current DFT value
          cout << currentFreq << "\t\t\t" << fourier[i].real() 
          << "  \t\t" << fourier[i].imag() << endl;
      }
      cout << endl << endl;
      cout << "Polar Form: \n\n";
      cout << "Analog Frequency (Hz)\tMagnitude\t\tAngle" << endl;
      for(int i = 0; i < steps ; i++)
      {
          currentFreq = startFreq + stepSize*i; 
          //analog frequency for current DFT value
          cout << currentFreq << "\t\t\t" << abs(fourier[i]) 
               << "  \t\t" << arg(fourier[i])*180/pi << endl;
      }
      cout << endl;
      break;
    case '0':
      return 1;
      break;
  }

  cout<<"Do you want to export this into a file?\n";
  cout<<"1: Yes, Rectangular form. \n2: Yes, Polar form. \n";
  cout<<"3: Yes, export both forms. \n4: No.\n";
  cout<<"Selection: ";
  cin>>choice2;
  
  switch(choice2)
  {
    case '1':
      cout<<"Enter output file name: ";
      cin>>ofn;
      outfile.open(ofn);
      outfile << "Analog Frequency (Hz)\tReal Part\t\tImaginary Part" << endl;
      for(int i = 0; i < steps ; i++)
        {
          currentFreq = startFreq + stepSize*i; 
          //analog frequency for current DFT value
          outfile << currentFreq << "\t\t\t" << fourier[i].real() 
          << "  \t\t" << fourier[i].imag() << endl;
        }
      break;
    case '2':
      cout<<"Enter output file name: ";
      cin>>ofn;
      outfile.open(ofn);
      outfile << "Analog Frequency (Hz)\tMagnitude\t\tAngle" << endl;
      for(int i = 0; i < steps ; i++)
      {
        currentFreq = startFreq + stepSize*i; 
        //analog frequency for current DFT value
        outfile << currentFreq << "\t\t\t" << abs(fourier[i]) 
                << "  \t\t" << arg(fourier[i])*180/pi << endl;
      }
      break;
    case '3':
      cout<<"Enter output file name for Rectangular form: ";
      cin>>ofn;
      outfile.open(ofn);
      outfile << "Analog Frequency (Hz)\tMagnitude\t\tAngle" << endl;
      for(int i = 0; i < steps ; i++)
      {
        currentFreq = startFreq + stepSize*i; 
        //analog frequency for current DFT value
        outfile << currentFreq << "\t\t\t" << fourier[i].real() 
                << "  \t\t" << fourier[i].imag() << endl;
      } 
      outfile.close();
      cout<<"Enter output file name for Polar form: ";
      cin>>ofn;
      outfile.open(ofn);
      outfile << "Analog Frequency (Hz)\tMagnitude\t\tAngle" << endl;
      for(int i = 0; i < steps ; i++)
      {
        currentFreq = startFreq + stepSize*i; 
        //analog frequency for current DFT value
        outfile << currentFreq << "\t\t\t" << abs(fourier[i]) 
                << "  \t\t" << arg(fourier[i])*180/pi << endl;
      }
      break;
  }
  outfile.close();
  return 0;
}