// #include <bits/stdc++.h>  // includes every header from stl

// #include <string>
#include <iostream>
#include <iterator>
// #include <stdlib.h>  // srand, rand

#include <array>
#include <algorithm>


// std::cout << << << "\n";

void print_array(auto &arr){
  for(auto i : arr){
    std::cout << i << " ";
  }
  std::cout << "\n";
}


bool customGreaterFunction(int i, int j) {
  return i > j ;
}


int binSearch(auto &arr, int target) {
    int l = 0;
    int r = arr.size() - 1;
    int mid = 0;
    while (l <= r){
        mid = l + (r - l)/ 2;
        if (arr[mid] == target){
            return mid;
        }
        else if (arr[mid] < target){
            l = mid + 1;
        }
        else r = mid - 1;
    }  // while
    return -1;
}


int main(int argc, char *argv[]){
  // srand (1);  // random seed

  // array c-style
  // int arr[5] = {0,1,2};
  // std::cout << sizeof(arr) << "\n";
  // for (int i = 0; i != (sizeof(arr)/sizeof(*arr)); i++){
  //   std::cout << "i = " << i << " a[i] = " << arr[i] << "\n";
  // }

  // strings
  // std::string str1("first string");
  // std::cout << str1 << "\n";

  // array #include <array>
  // sort #include <algorithm>
  std::array<int, 10> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
  std::cout << "arr size " << s.size() << "\n";
  print_array(s);

  std::sort(s.begin(), s.end());
  print_array(s);

  std::sort(s.begin(), s.end(), std::greater<int>());
  print_array(s);

  std::sort(s.begin(), s.end(), std::less<int>());
  print_array(s);

  struct {
    bool operator()(int a, int b) const
    {
      return a > b;
    }
  } customGreater;

  std::sort(s.begin(), s.end(), customGreater);
  std::sort(s.begin(), s.end(), customGreaterFunction);
  print_array(s);

  // binary search stl
  if (std::binary_search(s.begin(), s.end(), 5, customGreaterFunction)){
    std::cout << "Found! " << "\n";
  }
  else{
    std::cout << "Not Found!" << "\n";
  }

  std::sort(s.begin(), s.end());
  print_array(s);

  // binary search mine
  std::cout << "Found? " << binSearch(s, 50) << "\n";


  // binary_search using lower_bound
  // does not always work!!!!!!!!!!
  // std::array<int, 9> s = {7, 4, 2, 8, 6, 1, 9, 0, 3};
  // std::cout << "lower_bound " << std::lower_bound(s.begin(), s.end(), 5) - s.begin() << "\n";



  //
  // uint32_t data[] = {10, 20, 30, 40};
  // auto dataSize = std::size(data);







  // input and output files are csv files
  // std::string infile(argv[1]);
  // std::string outfile = infile.substr(0, infile.find(".")) + "_out.txt";
  // std::cout << "infile: " << infile << "; outfile: " << outfile << std::endl;

} // main
