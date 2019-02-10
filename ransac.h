#ifndef RANSAC_H_INCLUDED
#define RANSAC_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
// #include "vector2d.h"

using point2d = std::array<double, 2>;

class Ransac{
public:
  int n;  // minimum number of data points required to estimate model parameters
  double threshold;
  double confidence;
  double outlierFraction;

  std::vector<point2d> data;  // nx2 data
  int k;  // maximum number of iterations allowed in the algorithm

  // Ransac();
  Ransac(int, double, double, double);
  bool readInfile(std::string const&);
  void printRansacParameters();

  ~Ransac();

private:

};  // class

Ransac::Ransac(int n, double threshold, double confidence, double outlierFraction): n(n), threshold(threshold), confidence(confidence), outlierFraction(outlierFraction){}

bool Ransac::readInfile(std::string const& infile){
  std::ifstream file(infile.c_str());
  if (file.is_open())
  {
    std::cout << "Reading ... " << infile << std::endl;

  } // if
  else
  {
    std::cout << "Unable to open " << infile << std::endl;
    return false;
  } // else
} // readInfile


void Ransac::printRansacParameters(){
  std::cout << '\n' << "Ransac Parameters -------------------------------------------------->" << std::endl;
  std::cout << "n: " << n << std::endl;
  std::cout << "threshold: " << threshold << std::endl;
  std::cout << "confidence: " << confidence << std::endl;
  std::cout << "outlierFraction: " << outlierFraction << std::endl;
  std::cout << '\n' << "-------------------------------------------------->" << std::endl;

}  // printRansacParameters


Ransac::~Ransac(){}

#endif  // RANSAC_H_INCLUDED
