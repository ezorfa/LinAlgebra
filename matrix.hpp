/*
 //  matrix.hpp
 //  Assignment
 //
 //  Created by Mohammed Afroze on 23.02.20.
 */

/*! This files contains the template for a mathematical matrix
 */
#ifndef matrix_h
#define matrix_h

#include <algorithm>
#include <cstdlib>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <type_traits>

#include "vector.hpp"

namespace assignment {

/*! struct containing matrix data and convienience indexing functions.
 \tparam tpDataType matrix type
 */
template<typename tpDataType>
struct MData {

    std::size_t m_dimR;
    std::size_t m_dimC;
    std::unique_ptr<tpDataType[]> m_data;

    MData(std::size_t dimR, std::size_t dimC) :
                    m_dimR(dimR),
                    m_dimC(dimC),
                    m_data(new tpDataType[dimR * dimC])
    {
    }

    tpDataType const & operator()(std::size_t R, std::size_t C) const
    {
        return m_data[R * m_dimC + C];
    }
    tpDataType & operator()(std::size_t R, std::size_t C)
    {
        return m_data[R * m_dimC + C];
    }
};

/*! worker class, which is just used to process data !
 \tparam tpMatrixType matrix type
 */
template<typename tpMatrixType>
struct NonParallel {
    /*! worker class, which is just used to process data !
     \param xx_matrix_result matrix to hold result
     \param xx_left_matrix left matrix
     \param xx_right_matrix right matrix
     */
    static void matrix_multiply(tpMatrixType * xx_matrix_result, tpMatrixType const * xx_left_matrix, tpMatrixType const * xx_right_matrix)
    {

        for (typename tpMatrixType::size_type R = 0; R < xx_left_matrix->dimR(); ++R) {
            for (typename tpMatrixType::size_type C = 0; C < xx_right_matrix->dimC(); ++C) {
                (*xx_matrix_result)(R, C) = static_cast<typename tpMatrixType::value_type>(0.0);
                for (typename tpMatrixType::size_type i = 0; i < xx_left_matrix->dimC(); ++i) {
                    (*xx_matrix_result)(R, C) += (*xx_left_matrix)(R, i) * ((*xx_right_matrix)(i, C));
                }
            }
        }
    }
};

/*! worker class, which is just used to process data !
 \tparam tpMatrixType matrix type
 \note Not implemented yet. Can implement parallel matrix operation.
 */
template<typename tpMatrixType>
struct Parallel {
    /*! worker class, which is just used to process data !
     \param xx_matrix_result matrix to hold result
     \param xx_left_matrix left matrix
     \param xx_right_matrix right matrix
     */
    static void matrix_multiply(tpMatrixType * xx_matrix_result, tpMatrixType const * xx_left_matrix, tpMatrixType const * xx_right_matrix)
    {
        std::domain_error("Not Yet Implemented");
    }
};

template<typename tpDataType, template<typename > class tpPolicyType = NonParallel>
class matrix {
public:

    /*! type for the elements of the matrix
     */
    using value_type = tpDataType;

    /*! type for the size of the matrix
     */
    using size_type = std::size_t;

    /* ==== c  o  n  s  t  r  u  c  t  o  r  s ==== */

    /*! constructor
     \param xx_dim x dimension of the matrix
     */
    explicit matrix(size_type xx_dim);

    /*! constructor
     \param xx_dimR row dimension of the matrix
     \param xx_dimC column dimension of the matrix
     */
    explicit matrix(size_type xx_dimR, size_type xx_dimC);

    /*! constructor
     \param xx_dimR row dimension of the matrix
     \param xx_dimC column dimension of the matrix
     \param xx_value Value to be filled in the matrix
     */
    explicit matrix(size_type const xx_dimR, size_type const xx_dimC, tpDataType const xx_value);

    /*! constructor
     \param xx_dimR row dimension of the matrix
     \param xx_dimC column dimension of the matrix
     \param xx_ptr_array pointer to the array containing (xx_dimR * xx_dimC) elements.
     */
    explicit matrix(size_type const xx_dimR, size_type const xx_dimC, tpDataType const* xx_ptr_array);

    /*! constructor
     \param xx_dimR  Dimension of the matrix; treated as xx_dim X xx_dim
     \param xx_dimC  Dimension of the matrix; treated as xx_dim X xx_dim
     \param xx_list  Value to be filled in the matrix
     \note If enough number of elements not given in the list, then the rest are filled up with zeros. If exceeded, then ignored.
     */
    explicit matrix(size_type const xx_dimR, size_type const xx_dimC, std::initializer_list<tpDataType>&& xx_list);

    /*! copy constructor
     */
    matrix(matrix const & xx_matrix);

    /*! move constructor
     \param xx_matrix  Dimension of the matrix; treated as xx_dim X xx_dim
     */
    matrix(matrix && xx_matrix);

    /* ==== a  s  s  i  g  n  m  e  n  t     o  p  e  r  a  t  o  r  s ==== */

    /*! copy assignment operator
     */
    matrix & operator=(matrix const & xx_matrix);

    /*! move assignment operator
     */
    matrix & operator=(matrix && xx_matrix);

    /* ==== d  e  s  t  r  u  c  t  o  r ==== */

    /*! destructor
     */
    ~matrix() = default;

    /* ==== o  p  e  r  a  t  o  r     o  v  e  r  l  o  a  d  i  n  g ====*/

    /*! + operator overload
     \throw std::domain_error; if dimensions are not equal as (*this) matrix
     */
    matrix operator+(matrix const & xx_matrix) const;

    /*! + operator overload for the vector on the RHS.
     * \param xx_col_vector can be of any dimension but should have the meaning of a matrix having one coloumn
     * \note If xx_col_vector is greater than (*this) matrix_dimC then values are clipped accordingly and if contains less then vector is appended with zeros
     */
    matrix operator+(assignment::vector<tpDataType> const & xx_col_vector) const;

    /*! -operator overload
     * \param xx_matrix is the same dimension as (*this) matrix
     * \throw std::domain_error; if dimensions are not equal as (*this) matrix
     */
    matrix operator-(matrix const & xx_matrix) const;

    /*! *operator overload => Policy Matrix multiplication
     * \param xx_matrix is the same dimension as (*this) matrix
     * \throw std::domain_error; if dimensions are not equal as (*this) matrix
     * \note uses the policy with which the matrix class is instantiated.
     */
    matrix operator*(matrix const & xx_matrix) const;

    /*! *operator overload => Element-wise multiplication
     * \param xx_col_vector is similar to coloumn matrix
     * \throw std::domain_error if coloumn dimension of (*this) matrix not equal to vector dimension
     */
    assignment::vector<tpDataType> operator*(assignment::vector<tpDataType> const & xx_col_vector) const;

    /*! +operator overload with a scalar value
     */
    matrix operator+(tpDataType const & xx_scalar) const;

    /*! -operator overload with a scalar value.
     */
    matrix operator-(tpDataType const & xx_scalar) const;

    /*! *operator overload with a scalar value => element-wise multiplication
     */
    matrix operator*(tpDataType const xx_scalar) const;

    /*! *operator overload with a scalar value
     * \note enabled only when Non-integral data-type is used.
     */
    template<typename TDummy = tpDataType, typename std::enable_if<!std::is_integral<TDummy>::value>::type* = nullptr>
    matrix<tpDataType, tpPolicyType> operator *(size_type const xx_scalar) const;

    /*! +=operator overload with matrix
     * \param xx_matrix same dimension as (*this) matrix
     * \throw std::domain_error if coloumn dimension of (*this) matrix not equal to vector dimension
     */
    matrix & operator+=(matrix const & xx_matrix);

    /*! -=operator overload with matrix
     * \throw std::domain_error if coloumn dimension of (*this) matrix not equal to vector dimension
     */
    matrix & operator-=(matrix const & xx_matrix);

    /*! *=operator overload with matrix => Policy Matrix Multiplication (only for square matrices)
     * \throw std::domain_error if coloumn dimension of (*this) matrix not equal to vector dimension
     */
    matrix & operator*=(matrix const & xx_matrix);

    /*! ()operator overload for indexing
     * \note No error checking is done; upto the used to use proper indexing
     */
    tpDataType const & operator()(size_type dimR, size_type dimC) const;

    /*! ()operator overload for indexing
     */
    tpDataType & operator()(size_type dimR, size_type dimC);

    /* ==== h  e  l  p  e  r     f  u  n  c  t  i  o  n  s ==== */

    /*! Get the row dimension of the matrix
     */
    size_type const & dimR() const;

    /*! Get the coloumn dimension of the matrix
     */
    size_type const & dimC() const;

    /*!
     * \xx_value set the elements in the matrix with this value
     */
    void set(tpDataType const & xx_value);

private:

    /*! number of rows and columns
     */
    size_type m_dimR, m_dimC;

    /*! pointer to the matrix data
     */
    MData<tpDataType> m_data;

};

/* ==== c  o  n  s  t  r  u  c  t  o  r  s ==== */

template<typename tpDataType, template<typename > class tpPolicyType>
assignment::matrix<tpDataType, tpPolicyType>::matrix(size_type const xx_dim) :
                m_dimR(xx_dim),
                m_dimC(xx_dim),
                m_data(xx_dim, xx_dim)
{
}

template<typename tpDataType, template<typename > class tpPolicyType>
assignment::matrix<tpDataType, tpPolicyType>::matrix(size_type const xx_dimR, size_type const xx_dimC) :
                m_dimR(xx_dimR),
                m_dimC(xx_dimC),
                m_data(xx_dimR, xx_dimC)
{
}

template<typename tpDataType, template<typename > class tpPolicyType>
assignment::matrix<tpDataType, tpPolicyType>::matrix(size_type const xx_dimR, size_type const xx_dimC, tpDataType const xx_value) :
                m_dimR(xx_dimR),
                m_dimC(xx_dimC),
                m_data(m_dimR, m_dimC)
{
    for (size_type R = 0; R < m_dimR; ++R) {
        for (size_type C = 0; C < m_dimC; ++C) {
            m_data(R, C) = xx_value;
        }
    }
}

template<typename tpDataType, template<typename > class tpPolicyType>
assignment::matrix<tpDataType, tpPolicyType>::matrix(size_type const xx_dimR, size_type const xx_dimC, tpDataType const* xx_ptr_array) :
                m_dimR(xx_dimR),
                m_dimC(xx_dimC),
                m_data(m_dimR, m_dimC)
{
    for (size_type R = 0; R < m_dimR; ++R) {
        for (size_type C = 0; C < m_dimC; ++C) {
            m_data(R, C) = xx_ptr_array(R, C);
        }
    }
}

template<typename tpDataType, template<typename > class tpPolicyType>
assignment::matrix<tpDataType, tpPolicyType>::matrix(size_type const xx_dimR, size_type const xx_dimC, std::initializer_list<tpDataType>&& xx_list) :
                m_dimR(xx_dimR),
                m_dimC(xx_dimC),
                m_data(m_dimR, m_dimC)
{
    auto first = xx_list.begin();

    for (size_type R = 0; R < m_dimR; ++R) {
        for (size_type C = 0; C < m_dimC; ++C) {
            if (first != xx_list.end())
                m_data(R, C) = *(first++);
            else
                m_data(R, C) = 0;
        }
    }
}

template<typename tpDataType, template<typename > class tpPolicyType>
assignment::matrix<tpDataType, tpPolicyType>::matrix(matrix const & xx_matrix) :
                m_dimR(xx_matrix.m_dimR),
                m_dimC(xx_matrix.m_dimC),
                m_data(m_dimR, m_dimC)
{
    for (size_type R = 0; R < m_dimR; ++R) {
        for (size_type C = 0; C < m_dimC; ++C) {
            m_data(R, C) = xx_matrix.m_data(R, C);
        }
    }

}

template<typename tpDataType, template<typename > class tpPolicyType>
assignment::matrix<tpDataType, tpPolicyType>::matrix(matrix && xx_matrix) :
                m_dimR(std::move(xx_matrix.m_dimR)),
                m_dimC(std::move(xx_matrix.m_dimC)),
                m_data(m_dimR, m_dimC)
{
    m_data = std::move(xx_matrix.m_data);
}

/*  a  s  s  i  g  n  m  e  n  t     o  p  e  r  a  t  o  r  s  */

template<typename tpDataType, template<typename > class tpPolicyType>
matrix<tpDataType, tpPolicyType> &
assignment::matrix<tpDataType, tpPolicyType>::operator=(matrix const & xx_matrix)
{
    if (this == &xx_matrix)
        return *this;

    m_dimR = xx_matrix.m_dimR;
    m_dimC = xx_matrix.m_dimC;
    m_data(m_dimR, m_dimC);

    for (size_type R = 0; R < m_dimR; ++R) {
        for (size_type C = 0; C < m_dimR; ++C) {
            m_data(R, C) = xx_matrix.m_data(R, C);
        }
    }
}

template<typename tpDataType, template<typename > class tpPolicyType>
matrix<tpDataType, tpPolicyType> &
assignment::matrix<tpDataType, tpPolicyType>::operator=(matrix && xx_matrix)
{
    if (this == &xx_matrix)
        return *this;
    if ((m_dimC != xx_matrix.m_dimC) && (m_dimR != xx_matrix.m_dimR)) {
        m_dimR = xx_matrix.m_dimR;
        m_dimC = xx_matrix.m_dimC;
    }
    m_data = std::move(xx_matrix.m_data);
    return *this;
}

/* ==== o  p  e  r  a  t  o  r     o  v  e  r  l  o  a  d  i  n  g ==== */

template<typename tpDataType, template<typename > class tpPolicyType>
matrix<tpDataType, tpPolicyType> assignment::matrix<tpDataType, tpPolicyType>::operator+(matrix const & xx_matrix) const
{
    if (m_dimC != xx_matrix.m_dimC && m_dimR != xx_matrix.m_dimR)
        throw std::domain_error("Matrices should have same dimension");

    auto result = *this;
    for (size_type R = 0; R < m_dimR; ++R) {
        for (size_type C = 0; C < m_dimC; ++C) {
            result.m_data(R, C) += xx_matrix.m_data(R, C);
        }
    }
    return result;
}

template<typename tpDataType, template<typename > class tpPolicyType>
matrix<tpDataType, tpPolicyType> assignment::matrix<tpDataType, tpPolicyType>::operator+(assignment::vector<tpDataType> const & xx_vector) const
{
    auto result = *this;
    tpDataType temp;
    for (size_type R = 0; R < m_dimR; ++R) {
        for (size_type C = 0; C < m_dimC; ++C) {
            if (R > xx_vector.dim())
                temp = static_cast<tpDataType>(0.0);
            else
                temp = xx_vector[R];
            result.m_data(R, C) += temp;
        }
    }
    return result;
}

template<typename tpDataType, template<typename > class tpPolicyType>
matrix<tpDataType, tpPolicyType> assignment::matrix<tpDataType, tpPolicyType>::operator-(matrix const & xx_matrix) const
{
    if (m_dimC != xx_matrix.m_dimC && m_dimR != xx_matrix.m_dimR)
        throw std::domain_error("Matrices should have same dimension");

    auto result = *this;
    for (size_type R = 0; R < m_dimR; ++R) {
        for (size_type C = 0; C < m_dimC; ++C) {
            result.m_data(R, C) -= xx_matrix.m_data(R, C);
        }
    }
    return result;
}

template<typename tpDataType, template<typename > class tpPolicyType>
matrix<tpDataType, tpPolicyType> assignment::matrix<tpDataType, tpPolicyType>::operator*(matrix const & xx_matrix) const
{
    if (m_dimC != xx_matrix.m_dimR)
        throw std::domain_error("Number of columns_A != Number of rows_B");

    matrix<tpDataType, tpPolicyType> result(m_dimR, xx_matrix.m_dimC);
    tpPolicyType<matrix>::matrix_multiply(&result, this, &xx_matrix);

    return result;
}

template<typename tpDataType, template<typename > class tpPolicyType>
matrix<tpDataType, tpPolicyType> assignment::matrix<tpDataType, tpPolicyType>::operator+(tpDataType const & xx_scalar) const
{
    auto result = *this;
    for (size_type R = 0; R < m_dimR; ++R) {
        for (size_type C = 0; C < m_dimC; ++C) {
            result.m_data(R, C) += xx_scalar;
        }
    }
    return result;
}

template<typename tpDataType, template<typename > class tpPolicyType>
matrix<tpDataType, tpPolicyType> assignment::matrix<tpDataType, tpPolicyType>::operator-(tpDataType const & xx_scalar) const
{
    auto result = *this;
    for (size_type R = 0; R < m_dimR; ++R) {
        for (size_type C = 0; C < m_dimC; ++C) {
            result.m_data(R, C) -= xx_scalar;
        }
    }
    return result;
}

template<typename tpDataType, template<typename > class tpPolicyType>
matrix<tpDataType, tpPolicyType> assignment::matrix<tpDataType, tpPolicyType>::operator*(tpDataType const xx_scalar) const
{
    auto result = *this;
    for (size_type R = 0; R < m_dimR; ++R) {
        for (size_type C = 0; C < m_dimC; ++C) {
            result.m_data(R, C) *= xx_scalar;
        }
    }
    return result;
}

template<typename tpDataType, template<typename > class tpPolicyType>
matrix<tpDataType, tpPolicyType> &
assignment::matrix<tpDataType, tpPolicyType>::operator+=(matrix const & xx_matrix)
{
    if (m_dimC != xx_matrix.dimR())
        throw std::domain_error("Number of columns_A != Number of rows_B");

    for (size_type R = 0; R < m_dimR; ++R) {
        for (size_type C = 0; C < m_dimC; ++C) {
            m_data(R, C) += xx_matrix.m_data(R, C);
        }
    }
    return (*this);
}

template<typename tpDataType, template<typename > class tpPolicyType>
matrix<tpDataType, tpPolicyType> &
assignment::matrix<tpDataType, tpPolicyType>::operator-=(matrix const & xx_matrix)
{
    if (m_dimC != xx_matrix.dimR())
        throw std::domain_error("Number of columns_A != Number of rows_B");

    for (size_type R = 0; R < m_dimR; ++R) {
        for (size_type C = 0; C < m_dimC; ++C) {
            m_data(R, C) -= xx_matrix.m_data(R, C);
        }
    }
    return (*this);
}

template<typename tpDataType, template<typename > class tpPolicyType>
matrix<tpDataType, tpPolicyType> &
assignment::matrix<tpDataType, tpPolicyType>::operator*=(matrix const & xx_matrix)
{
    if (m_dimC != m_dimR || xx_matrix.m_dimC != xx_matrix.m_dimR)
        throw std::domain_error("matrix_B should be the same size as matrix_A");
    auto temp = (*this);

    if (this == &xx_matrix) {
        tpPolicyType<matrix>::matrix_multiply(this, &temp, &temp);
    } else {
        tpPolicyType<matrix>::matrix_multiply(this, &temp, &xx_matrix);
    }

    return (*this);
}

template<typename tpDataType, template<typename > class tpPolicyType>
template<typename TDummy, typename std::enable_if<!std::is_integral<TDummy>::value>::type*>
matrix<tpDataType, tpPolicyType> assignment::matrix<tpDataType, tpPolicyType>::operator *(size_type const xx_scalar) const
{
    auto result = *this;
    for (size_type R = 0; R < m_dimR; ++R) {
        for (size_type C = 0; C < m_dimC; ++C) {
            result.m_data(R, C) *= static_cast<tpDataType>(xx_scalar);
        }
    }
    return result;
}

template<typename tpDataType, template<typename > class tpPolicyType>
assignment::vector<tpDataType> assignment::matrix<tpDataType, tpPolicyType>::operator*(assignment::vector<tpDataType> const & xx_col_vector) const
{
    auto result = assignment::vector<tpDataType>(m_dimR);
    for (size_type R = 0; R < m_dimR; ++R) {
        result[R] = static_cast<tpDataType>(0);
        for (size_type C = 0; C < m_dimC; ++C) {
            result[R] += (*this)(R, C) * xx_col_vector[C];
        }
    }
    return result;
}

template<typename tpDataType, template<typename > class tpPolicyType>
tpDataType const &
assignment::matrix<tpDataType, tpPolicyType>::operator()(size_type dimR, size_type dimC) const
{
    return m_data(dimR, dimC);
}

template<typename tpDataType, template<typename > class tpPolicyType>
tpDataType &
assignment::matrix<tpDataType, tpPolicyType>::operator()(size_type dimR, size_type dimC)
{
    return m_data(dimR, dimC);
}

/* ==== h  e  l  p  e  r     f  u  n  c  t  i  o  n  s  ==== */

template<typename tpDataType, template<typename > class tpPolicyType>
std::size_t const &
assignment::matrix<tpDataType, tpPolicyType>::dimR() const
{
    return m_dimR;
}

template<typename tpDataType, template<typename > class tpPolicyType>
std::size_t const &
assignment::matrix<tpDataType, tpPolicyType>::dimC() const
{
    return m_dimC;
}

template<typename tpDataType, template<typename > class tpPolicyType>
void assignment::matrix<tpDataType, tpPolicyType>::set(tpDataType const & xx_value)
{
    for (size_type R = 0; R < m_dimR; ++R) {
        for (size_type C = 0; C < m_dimC; ++C) {
            (*this)(R, C) = xx_value;
        }
    }
}

}

#endif /* matrix_h */
