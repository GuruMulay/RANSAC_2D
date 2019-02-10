#ifndef RANSAC_H_INCLUDED
#define RANSAC_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <math.h>
// Thanks to https://github.com/joekeo/RANSAC/blob/master/main.cpp

using point2d = std::array<double, 2>;

class Ransac{
public:
  int n = 2;  // (always 2 for 2D line fitting) minimum number of data points required to estimate model parameters
  double threshold;
  double confidence;  // probablity of choosing set of 2 points that are not outliers
  // so that the the chosen inlier points will be able to fit a line with max number of inliers
  double outlierFraction;

  std::vector<point2d> data;  // totalNx2 data
  unsigned totalN;  // total number of points
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
  bool isWithinThreshold(const std::array<double, 2> &, const std::array<double, 2> &, const std::array<double, 2> &);
  void findBestFit();
  void printRansacParameters(bool);
  ~Ransac();

private:

};  // class

Ransac::Ransac(int n, double threshold, double confidence, double outlierFraction): n(n), threshold(threshold), confidence(confidence), outlierFraction(outlierFraction){}


bool Ransac::readInfile(std::string const& infile){
  std::ifstream file(infile.c_str());
  if (file.is_open())
  {
    std::cout << "Reading ... " << infile << std::endl;
    double x, y;
    char separator;

    while(file >> x >> separator >> y){
      data.push_back({x, y});
      std::cout << x << " " << y << std::endl;
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


bool Ransac::isWithinThreshold(const std::array<double, 2> &a, const std::array<double, 2> &b, const std::array<double, 2> &p){
  // line from a to b; check if p is within threshold distance of line ab
  // https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
  double numerator = abs((b[1] - a[1])*p[0] - (b[0] - a[0])*p[1] + b[0]*a[1] - b[1]*a[0]);
  double denominator = sqrt(pow(b[1] - a[1], 2) + pow(b[0] - a[0], 2));
  if (numerator/denominator < threshold){
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
      if (isWithinThreshold(maybeInlierA, maybeInlierB, currPoint)){
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
  std::cout << "\nCompleted " << k << " iterations of RANSAC!"<< std::endl;
}  // findBestFit


void Ransac::printRansacParameters(bool printData){
  std::cout << '\n' << "Ransac Parameters -------------------------------------------------->" << std::endl;
  std::cout << "n: " << n << std::endl;
  std::cout << "number of trials (iterations): " << k << std::endl;
  std::cout << "threshold: " << threshold << std::endl;
  std::cout << "confidence: " << confidence << std::endl;
  std::cout << "outlierFraction: " << outlierFraction << std::endl;
  if (printData){
    for (size_t i = 0; i != data.size(); i++){
      std::cout << i << " " << data[i][0] << ", " << data[i][1] << ", isInlier? " << finalInliers[i] << std::endl;
    }
  }  // if
  std::cout << "Best fitting line is parameterized by points A: (" << bestFitPointA[0] << ", " << bestFitPointA[1] << ") B: (" << bestFitPointB[0] << ", " << bestFitPointB[1] << ")"<< std::endl;
  std::cout << "-------------------------------------------------->" << std::endl;

}  // printRansacParameters

Ransac::~Ransac(){}

#endif  // RANSAC_H_INCLUDED
