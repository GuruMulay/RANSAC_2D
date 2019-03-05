// #include <bits/stdc++.h>  // includes every header from stl

// #include <string>
#include <iostream>
#include <iterator>
// #include <stdlib.h>  // srand, rand

#include <array>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <iterator>


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

  // multimap keys are ordered not the values
  // std::multimap <int, int> mm;
  // std::multimap <int, int>::iterator itr;
  // typedef std::multimap <int, int>::iterator UMMIterator;

  // unordered multimap is equivalent to dict from python! uses hashing
  std::unordered_multimap <int, int> mm;
  std::unordered_multimap <int, int>::iterator itr;
  typedef std::unordered_multimap <int, int>::iterator UMMIterator;

  mm.insert(std::pair<int, int>(1, 10));
  mm.insert(std::pair<int, int>(2, 20));
  mm.insert(std::pair<int, int>(3, 30));
  mm.insert(std::pair<int, int>(4, 40));
  mm.insert(std::pair<int, int>(5, 53));
  mm.insert(std::pair<int, int>(5, 51));
  mm.insert(std::pair<int, int>(5, 52));
  mm.insert(std::pair<int, int>(1, 11));
  mm.insert(std::pair<int, int>(1, 12));
  mm.insert(std::pair<int, int>(1, 15));
  // mm[1] = 16;
  // mm[5] = 55;
  // mm.insert(std::pair<int, int>());

  for (itr = mm.begin(); itr != mm.end(); itr++){
    std::cout << "key: " << itr->first << " val: " << itr->second << "\n";
    // std::cout << "key: " << (*itr).first << " val: " << (*itr).second << "\n";
  }

  int key = 5;

  if (mm.find(key) == mm.end()) std::cout << key << " not found\n";
  else std::cout << "Found key " << key << std::endl;


  // all the values of a key
  std::cout << "all the values for key = " << key << "\n";
  std::pair<UMMIterator, UMMIterator> vrange = mm.equal_range(key);

  for (UMMIterator it = vrange.first; it != vrange.second; it++)
		std::cout << it->second << std::endl;

  int count_range_ele = std::distance(vrange.first, vrange.second);
  std::cout << "count of values with key " << count_range_ele << std::endl;

} // main
