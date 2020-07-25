//
//  vector_helpers.hpp
//  Assignment
//
//  Created by Mohammed Afroze on 24.02.20.
//

#ifndef vector_helpers_h
#define vector_helpers_h

namespace assignment {

/* ==== f  r  e  e     f  u  n  c  t  i  o  n  s==== */

/*! left scalar multiply operator
*/
template<typename tpDataType>
vector<tpDataType> operator *(tpDataType const xx_scalar, vector<tpDataType> const & xx_vector)
{
    auto result = xx_vector;
    for (size_t i = 0; i < xx_vector.dim(); ++i) {
        result[i] *= xx_scalar;
    }
    return result;
}

/*! left scalar multiply operator => disabled for integral-types
*/
template<typename tpDataType, typename std::enable_if<!std::is_integral<tpDataType>::value>::type* = nullptr>
vector<tpDataType> operator *(size_t const xx_scalar, vector<tpDataType> const & xx_vector)
{
    auto result = xx_vector;
    for (size_t i = 0; i < xx_vector.dim(); ++i) {
        result[i] *= xx_scalar;
    }
    return result;
}

/*! negation operator
*/
template<typename tpDataType>
vector<tpDataType> operator -(vector<tpDataType> const & xx_vector)
{
    auto result = xx_vector;
    for (size_t i = 0; i < result.dim(); ++i) {
        result[i] = -xx_vector[i];
    }

    return result;
}

/*! output vector to std::cout
*/
template<typename tpDataType>
std::ostream& operator<<(std::ostream& os, assignment::vector<tpDataType> const & xx_vector)
{
    os << '[';
    for (int i = 0; i < xx_vector.dim(); ++i) {
        if (i > 0)
            os << " ,";
        os << xx_vector[i];
    }
    os << ']';
    return os;
}
    
    };
#endif /* vector_helpers_h */
