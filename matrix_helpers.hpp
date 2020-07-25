//
//  matrix_helpers.hpp
//  Assignment
//
//  Created by Mohammed Afroze on 24.02.20.
//

#ifndef matrix_helpers_h
#define matrix_helpers_h

namespace assignment {
/* ==== f  r  e  e     o  p  e  r  a  t  o  r  s ==== */

/*! left scalar multiply operator
*/
template<typename tpDataType, template<typename > class tpPolicyType>
assignment::matrix<tpDataType, tpPolicyType> operator *(tpDataType const xx_scalar, matrix<tpDataType, tpPolicyType> const & xx_matrix)
{
    auto result = xx_matrix;
    for (std::size_t R = 0; R < xx_matrix.dimR(); ++R) {
        for (std::size_t C = 0; C < xx_matrix.dimC(); ++C) {
            result(R, C) *= xx_scalar;
        }
    }
    return result;
}

/*! left scalar multiply operator  => disabled for integrals
*/
template<typename tpDataType, template<typename > class tpPolicyType, typename std::enable_if<!std::is_integral<tpDataType>::value>::type* = nullptr>
matrix<tpDataType, tpPolicyType> operator *(std::size_t const xx_scalar, matrix<tpDataType, tpPolicyType> const & xx_matrix)
{
    auto result = xx_matrix;
    for (std::size_t R = 0; R < xx_matrix.dimR(); ++R) {
        for (std::size_t C = 0; C < xx_matrix.dimC(); ++C) {
            result(R, C) *= xx_scalar;
        }
    }
    return result;
}

/*!  negation operator
*/
template<typename tpDataType, template<typename > class tpPolicyType>
matrix<tpDataType, tpPolicyType> operator -(matrix<tpDataType, tpPolicyType> const & xx_matrix)
{
    auto result = xx_matrix;
    for (std::size_t R = 0; R < xx_matrix.dimR(); ++R) {
        for (std::size_t C = 0; C < xx_matrix.dimC(); ++C) {
            result(R, C) = -xx_matrix(R, C);
        }
    }
    return result;
}

/*! casting vector to matrix
 \note either one of dimR or dimC should be 1
 \throw std::domain error
*/
template<typename tpDataType, template<typename > class tpPolicyType = assignment::NonParallel>
matrix<tpDataType, tpPolicyType> cast_V2M(assignment::vector<tpDataType> const & xx_vector, int dimR, int dimC)
{
    if (dimR > 1 && dimC > 1)
        throw std::domain_error("Either dimR or dimC should be 1");
    auto temp_mat = assignment::matrix<tpDataType, tpPolicyType>(dimR, dimC);
    
    for (std::size_t R = 0; R < temp_mat.dimR(); ++R) {
        for (std::size_t C = 0; C < temp_mat.dimC(); ++C) {
            temp_mat(R, C) = xx_vector[std::max(R, C)];
        }
    }
    return temp_mat;
}

/*! casting matrix to vector
 \throw std::domain error if matrix is neither row or coloumn matrix
*/
template<typename tpDataType, template<typename > class tpPolicyType = assignment::NonParallel>
assignment::vector<tpDataType> cast_M2V(matrix<tpDataType, tpPolicyType> const & xx_matrix)
{
    if (xx_matrix.dimR() > 1 && xx_matrix.dimC() > 1)
        throw std::domain_error("Either dimR or dimC should be 1");

    auto temp_mat = assignment::vector < tpDataType > (std::max(xx_matrix.dimC(), xx_matrix.dimR()));
    for (std::size_t R = 0; R < xx_matrix.dimR(); ++R) {
        for (std::size_t C = 0; C < xx_matrix.dimC(); ++C) {
            temp_mat[std::max(R, C)] = xx_matrix(R, C);
        }
    }
    return temp_mat;
}

/*! output matrix to std::cout
 \throw std::domain error
*/
template<typename tpDataType, template<typename > class tpPolicyType>
std::ostream& operator<<(std::ostream& os, assignment::matrix<tpDataType, tpPolicyType> const & xx_matrix)
{   
    os << '[';
    for (int R = 0; R < xx_matrix.dimR(); ++R) {
        if (R > 0)
            os << ',' << std::endl << " ";

        for (int C = 0; C < xx_matrix.dimC(); ++C)
            os << xx_matrix(R, C) << " ";
    }
    os << ']';
    return os;
}
}
#endif /* matrix_helpers_h */
