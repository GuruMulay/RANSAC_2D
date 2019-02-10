#ifndef RANSAC_H_INCLUDED
#define RANSAC_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <math.h>
// #include <stdlib.h> // srand, rand
// srand (1);  // random seed


// #include "vector2d.h"

using point2d = std::array<double, 2>;

class Ransac{
public:
  int n = 2;  // (always 2 for 2D line fitting) minimum number of data points required to estimate model parameters
  double threshold;
  double confidence;  // probablity of choosing set of 2 points that are not outliers
  // so that the the chosen inlier points will be able to fit a line with max number of inliers
  double outlierFraction;

  std::vector<point2d> data;  // totalNx2 data
  unsigned totalN;  // ttal number of points
  std::vector<bool> inliers;  // stores bool if current inlier or not
  std::vector<bool> finalInliers;  // if the model is best fit then update this vector

  unsigned k = log(1 - confidence) / log(1 - pow(1 - outlierFraction, n));  // maximum number of iterations allowed in the algorithm

  // model and global parameters
  unsigned nInliersGlobalMax = 0;
  unsigned nInliersCurr = 0;
  std::array<double, 2> bestFitPointA, bestFitPointB;

  // Ransac();
  Ransac(int, double, double, double);
  bool readInfile(std::string const&);
  bool isWithinThreshold();
  void findBestFit();
  void printRansacParameters(bool);
  ~Ransac();

private:

};  // class

Ransac::Ransac(int n, double threshold, double confidence, double outlierFraction): n(n), threshold(threshold), confidence(confidence), outlierFraction(outlierFraction){}


bool Ransac::isWithinThreshold(const std::array<double, 2> &a, const std::array<double, 2> &b, const std::array<double, 2> &p){
  // line from a to b
  // check if p is within threshold distance of line ab
  // https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
  if (){
    return true;
  }
  else return false;

}  // isWithinThreshold


void Ransac::findBestFit(){
  std::array<double, 2> maybeInlierA, maybeInlierB, currPoint;
  for(unsigned i = 0; i <= k; i++){
    // randomly select n values from data
    unsigned n0 = rand() % totalN;
    unsigned n1 = rand() % totalN;
    maybeInlierA = {data[n0][0], data[n0][1]};
    maybeInlierB = {data[n1][0], data[n1][1]};
    /*
    std::cout << "random: " << n0 << " " << n1 << std::endl;
    std::cout << "point maybeInlierA: " << maybeInlierA[0] << " " << maybeInlierA[1] << std::endl;
    std::cout << "point maybeInlierB: " << maybeInlierB[0] << " " << maybeInlierB[1] << std::endl;
    */
    nInliersCurr = 0;
    inliers.clear();
    // iterate over the data points to find the number of points that are within threshold epsilon distance of the line fit for maybeInlierA and maybeInlierB
    for(unsigned p = 0; p <= totalN; p++){
      currPoint = {data[p][0], data[p][1]};
      if isWithinThreshold(maybeInlierA, maybeInlierB, currPoint){
        // increase curr inliers count and set true in the inliers vector
        nInliersCurr += 1;
        inliers.push_back(true);
      }
      else
      {
        inliers.push_back(false);
      }

      if (nInliersGlobalMax < nInliersCurr){
          nInliersGlobalMax = nInliersCurr;
          // update best fit points A and B
          bestFitPointA = {data[n0][0], data[n0][1]};
          bestFitPointB = {data[n1][0], data[n1][1]};
          finalInliers = inliers;
      }  // if


    }  // for data points
  }  // for k iterations
  std::cout << "Completed " << k << " iterations of RANSAC!"<< std::endl;
}  // findBestFit


bool Ransac::readInfile(std::string const& infile){
  std::ifstream file(infile.c_str());
  if (file.is_open())
  {
    std::cout << "Reading ... " << infile << std::endl;
    double x, y;
    char separator;

    while(true){
      file >> x >> separator >> y;
      data.push_back({x, y});
      if (file.eof()) break;
    }  // while

    totalN = data.size();
    return true;
  } // if
  else
  {
    std::cout << "Unable to open " << infile << std::endl;
    return false;
  } // else
} // readInfile


// void Ransac::printInliers(){
//   for (size_t i = 0; i != data.size(); i++){
//     std::cout << data[i][0] << ", " << data[i][1] << "" << std::endl;
//   }
// }  // printInliers

void Ransac::printRansacParameters(bool printData){
  std::cout << '\n' << "Ransac Parameters -------------------------------------------------->" << std::endl;
  std::cout << "n: " << n << std::endl;
  std::cout << "number of trials (iterations): " << k << std::endl;
  std::cout << "threshold: " << threshold << std::endl;
  std::cout << "confidence: " << confidence << std::endl;
  std::cout << "outlierFraction: " << outlierFraction << std::endl;
  if (printData){
    for (size_t i = 0; i != data.size(); i++){
      std::cout << data[i][0] << ", " << data[i][1] << ", isInlier? " << finalInliers[i] << std::endl;
    }
  }  // if

  std::cout << "Best fitting line is parameterized by points" << << std::endl;
  std::cout << "-------------------------------------------------->" << std::endl;

}  // printRansacParameters


Ransac::~Ransac(){}

#endif  // RANSAC_H_INCLUDED

abs(
  (
    (LP1[1] - LP0[1]) * Point[0] - (LP1[0] - LP0[0]) * Point[1] + LP1[0]*LP0[1] - LP1[1]*LP0[0]
  )

  / sqrt(pow((LP1[1]-LP0[1]),2) + pow(LP1[0]-LP0[0],2))
);
