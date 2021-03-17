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