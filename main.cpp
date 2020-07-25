/*
//  main.cpp
//  Assignment
//
//  Created by Mohammed Afroze on 23.02.20.
*/

#include <complex>
#include <iostream>
#include <initializer_list>

#include "matrix.hpp"
#include "matrix_helpers.hpp"
#include "vector_helpers.hpp"

int main(int argc, const char * argv[]) {
    
    // By default all are NonParallel operations
    assignment::matrix<std::complex<int>, assignment::NonParallel> m1_c(3,4,{{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11},{12}});
    assignment::matrix<std::complex<int>> m2_c(4,3,{{1,-1},{2,-2},{3,-3},{4,-4},{5,-5},{6,-6},{7,-7},{8,-8},{9,-9},{10,-10},{11,-11},{12,-12}});
    assignment::matrix<std::complex<int>> m3_c(4,3,{{1,-1},{2,-2},{3,-3},{4,-4},{5,-5},{6,-6},{7,-7},{8,-8},{9,-9},{10,-10},{11,-11},{12,-12}});
    assignment::matrix<std::complex<int>> sq(3,3,{{1},{2},{3},{4},{5},{6},{7},{8},{9}});
    
    assignment::matrix<int> m1(4,3,{1,2,3,4,5,6,7,8,9,10,11,12});
    assignment::matrix<int> m2(4,3,{1,2,3,4,5,6,7,8,9,10,11,12});
    assignment::matrix<int> m3(3,3,{1,2,3,4,5,6,7,8,9});
    assignment::matrix<int> m4(3,3,{1,2,3,4,5,6,7,8,9});
    assignment::matrix<int> m5(3,3,{1,2,3,4,5,6,7,8,9});
    
    assignment::vector<int> v1({10,12,18,14,27});
    assignment::vector<int> v2({10,12,18,14,27});
    assignment::vector<int> v3({10,12,18});
    
    // vector
    std::cout << "Addition: " << v1+v2 << std::endl;
    std::cout << "Subtraction: " << v1-v2 << std::endl;
    std::cout << "Multiplication: " << v1*v2 << std::endl;
    std::cout << "scalar_multiply: " << v1*v2*3 << std::endl;
    
    // vector complex
    std::cout << "Addition: " << v1+v2+v3 << std::endl;
    std::cout << "Subtraction: " << v1-v2-v3 << std::endl;
    std::cout << "Multiplication: " << v1*v2*-v3 << std::endl;
    std::cout << "scalar_multiply: " << v1*v2*3 << std::endl;
    
    // matrix
    std::cout << "Addition : " << m1 + m2 << std::endl;
    std::cout << "Subtraction: " << m1-m2 << std::endl;
    std::cout << "Multiplication: " << m1*m3 << std::endl;
    std::cout << "scalar_multiply: " << m1*m3*3 << std::endl;
    
    // matrix complex
    std::cout << "Addition: " << m1_c + m1_c << std::endl;
    std::cout << "Subtraction: " << m2_c - m3_c << std::endl;
    std::cout << "Multiplication: " << m1_c * m2_c << std::endl;
    std::cout << "scalar_multiply: " << m1_c * m2_c * 3 << std::endl;
    
    // casting
    auto casted_v3 =  assignment::cast_V2M<int, assignment::NonParallel>(v3, 1, 3);
    std::cout << "Cast vector2Matrix: " << casted_v3 << std::endl;

    return 0;
}
