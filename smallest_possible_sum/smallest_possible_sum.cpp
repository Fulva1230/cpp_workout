//
// Created by fulva on 11/6/2021.
//
#include <vector>
#include <numeric>

unsigned long long solution(const std::vector<unsigned long long>& arr){
  auto cur_iter = std::begin(arr);
  auto end_iter = std::end(arr);
  auto first = *cur_iter;
  ++cur_iter;
  if(cur_iter == end_iter){
    return first;
  }
  auto greatest_common_divisor = std::gcd(first, *cur_iter);
  ++cur_iter;
  for(;cur_iter != end_iter;++cur_iter){
    greatest_common_divisor = std::gcd(greatest_common_divisor, *cur_iter);
  }
  return greatest_common_divisor * std::size(arr);
}