//============================================================================
// Name        : ransac.cpp
// Created on  :
// Author      : @guru
// Version     :
// Description : RANSAC for 2D points
//============================================================================

#include <string>
#include <iostream>

#include "ransac.h"

// std::cout << "" << << std::endl;
// using point2d = std::array<double, 2>;
// std::vector<poin/t2d> data;


int main(int argc, char *argv[]){
  // input and output files are csv files
  std::string infile(argv[1]);
  std::string outfile = infile.substr(0, infile.find(".")) + "_out.txt";
  std::cout << "infile:" << infile << "; outfile:" << outfile << std::endl;

  // Ransac
  Ransac* R = new Ransac(2, 0.1, 0.99, 0.3333);
  R->printRansacParameters();
  

  if (!R->readInfile(infile)){
    std::cerr << "Cannot open input file " << infile << std::endl;
    return 1;
  }

} // main
