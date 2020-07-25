/*
 //  vector.hpp
 //  Assignment
 //
 //  Created by Mohammed Afroze on 23.02.20.
 */

/*! This files contains the template for a mathematical vector
 */
#ifndef vector_h
#define vector_h

#include <algorithm>
#include <cstdlib>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <type_traits>

namespace assignment {
template<typename tpDataType>
class vector {
public:

    /*! type for the elements of the matrix
     */
    using value_type = tpDataType;

    /*! type for the size of the matrix
     */
    using size_type = std::size_t;

    /* ==== c  o  n  s  t  r  u  c  t  o  r  s ==== */

    /*! constructor
     \param xx_dim x dimension of the array
     */
    explicit vector(size_type const xx_dim);

    /*! constructor
     \param xx_dim x dimension of the array
     \param xx_value value to be filled in with
     */
    explicit vector(size_type const xx_dim, tpDataType const xx_value);

    /*! constructor
     \param xx_dim x dimension of the array
     \param xx_ptr_array pointer to the array of elements
     \note The array should have atleast xx_dim elements
     */
    explicit vector(size_type const xx_dim, tpDataType const* xx_ptr_array);

    /*! constructor
     \param XX_list initializer list of elements to be stored in the vector; for convienience
     \note The size of the initializer list is the size of the vector
     */
    explicit vector(std::initializer_list<tpDataType>&& XX_list);

    /*! copy constructor
     */
    vector(vector const & xx_vector);

    /*! move constructor
     */
    vector(vector && xx_vector);

    /* ==== a  s  s  i  g  n  m  e  n  t     o  p  e  r  a  t  o  r  s  ==== */

    /*! copy assignment operator
     */
    vector & operator=(vector const & xx_vector);

    /*! move assignment operator
     */
    vector & operator=(vector && xx_vector);

    /* ==== d  e  s  t  r  u  c  t  o  r ==== */

    /*! default destructor
     */
    ~vector() = default;

    /* ==== o  p  e  r  a  t  o  r     o  v  e  r  l  o  a  d  i  n  g ==== */

    /*! + operator overload
     */
    vector operator+(vector const & xx_vector);

    /*! - operator overload
     */
    vector operator-(vector const & xx_vector);

    /*!  *operator overload => element-wise multiplication
     \note xx_vector is clipped if its dim > (*this) vector's dim and appended with 1 otherwise
     */
    vector operator*(vector const & xx_vector);

    /*! + operator overload with scalar
     */
    vector operator+(tpDataType const & xx_scalar);

    /*! - operator overload with scalar
     */
    vector operator-(tpDataType const & xx_scalar);

    /*! * operator overload with scalar
     */
    vector operator*(tpDataType const xx_scalar);

    /*! * operator overload with scalar
     \note only enabled if the datatype is not integral (Ex: when std::complex)
     */
    template<typename TDummy = tpDataType, typename std::enable_if<!std::is_integral<TDummy>::value>::type* = nullptr>
    vector<tpDataType> operator *(size_type const xx_scalar);

    /*! +=operator overload
     */
    vector & operator+=(vector const & xx_vector);

    /*! -=operator overload
     */
    vector & operator-=(vector const & xx_vector);

    /*! * =operator overload
     */
    vector & operator*=(vector const & xx_vector);

    /*! [ ]operator overload for indexing
     */
    tpDataType const & operator[](size_type const xx_idx) const;

    /*! [ ]operator overload for indexing
     */
    tpDataType & operator[](size_type const xx_idx);

    /* ==== h  e  l  p  e  r     f  u  n  c  t  i  o  n  s ==== */

    /*! get dimension of the vector
     */
    size_type const dim() const;

    /*! set the value of each element with xx_value
     */
    void set(tpDataType const & xx_value);

private:
    /*! dimension of the matrix
     */
    size_type m_dim;

    /*! unique pointer to the data
     */
    std::unique_ptr<value_type[]> m_data;

};

/* ==== c  o  n  s  t  r  u  c  t  o  r  s ==== */

template<typename tpDataType>
assignment::vector<tpDataType>::vector(size_type const xx_dim) :
                m_dim(xx_dim),
                m_data(new tpDataType[m_dim])
{
}

template<typename tpDataType>
assignment::vector<tpDataType>::vector(size_type const xx_dim, tpDataType const xx_value) :
                m_dim(xx_dim),
                m_data(new tpDataType[m_dim])
{
    for (size_type i = 0; i < m_dim; ++i) {
        m_data[i] = xx_value;
    }
}

template<typename tpDataType>
assignment::vector<tpDataType>::vector(size_type xx_dim, tpDataType const* xx_ptr_array) :
                m_dim(xx_dim),
                m_data(new tpDataType[m_dim])
{
    for (size_type i = 0; i < xx_dim; ++i) {
        m_data[i] = *xx_ptr_array++;
    }
}

template<typename tpDataType>
assignment::vector<tpDataType>::vector(std::initializer_list<tpDataType>&& xx_list) :
                m_dim(0),
                m_data(new tpDataType[m_dim])
{
    m_dim = xx_list.size();
    int i = 0;
    for (auto&& x : xx_list) {
        m_data[i] = x;
        ++i;
    }
}

template<typename tpDataType>
assignment::vector<tpDataType>::vector(vector const & xx_vector) :
                m_dim(xx_vector.m_dim),
                m_data(new tpDataType[m_dim])
{
    for (size_type i = 0; i < m_dim; ++i) {
        m_data[i] = xx_vector[i];
    }
}

template<typename tpDataType>
assignment::vector<tpDataType>::vector(vector && xx_vector) :
                m_dim(std::move(xx_vector.m_dim)),
                m_data(new tpDataType[m_dim])
{
    m_data = std::move(xx_vector.m_data);
}

/* ==== a  s  s  i  g  n  m  e  n  t     o  p  e  r  a  t  o  r  s ==== */

template<typename tpDataType>
vector<tpDataType> &
assignment::vector<tpDataType>::operator=(vector const & xx_vector)
{
    if (this == &xx_vector)
        return *this;
    
    m_dim = xx_vector.m_dim;
    m_data(new tpDataType[m_dim]);
    std::copy(&xx_vector.m_data[0], &xx_vector.m_data[0] + m_dim, &m_data[0]);
}

template<typename tpDataType>
vector<tpDataType> &
assignment::vector<tpDataType>::operator=(vector && xx_vector)
{
    if (this == &xx_vector)
        return *this;
    
    m_dim = std::move(xx_vector.m_dim);
    m_data(new tpDataType[m_dim]);
    m_data = std::move(xx_vector.m_data);
}

/* ==== o  p  e  r  a  t  o  r     o  v  e  r  l  o  a  d  i  n  g ==== */

//variation
template<typename tpDataType>
vector<tpDataType> assignment::vector<tpDataType>::operator+(vector const & xx_vector)
{
    auto temp = *this;
    for (size_type i = 0; i < xx_vector.m_dim; ++i)
        temp.m_data[i] += xx_vector[i];

    return temp;
}

template<typename tpDataType>
vector<tpDataType> assignment::vector<tpDataType>::operator-(vector const & xx_vector)
{
    auto temp = *this;
    for (size_type i = 0; i < xx_vector.m_dim; ++i)
        temp.m_data[i] -= xx_vector[i];

    return temp;
}

template<typename tpDataType>
vector<tpDataType> assignment::vector<tpDataType>::operator*(vector const & xx_vector)
{
    auto temp = *this;
    for (size_type i = 0; i < xx_vector.m_dim; ++i)
        temp.m_data[i] *= xx_vector[i];
    return temp;
}

template<typename tpDataType>
vector<tpDataType> assignment::vector<tpDataType>::operator+(tpDataType const & xx_scalar)
{
    auto result = *this;
    for (size_type i = 0; i < this->m_dim; ++i)
        result.m_data[i] += xx_scalar;

    return result;
}

template<typename tpDataType>
vector<tpDataType> assignment::vector<tpDataType>::operator-(tpDataType const & xx_scalar)
{
    auto result = *this;
    for (size_type i = 0; i < this->m_dim; ++i)
        result.m_data[i] -= xx_scalar;

    return result;
}

template<typename tpDataType>
vector<tpDataType> assignment::vector<tpDataType>::operator*(tpDataType const xx_scalar)
{
    auto result = *this;
    for (size_type i = 0; i < this->m_dim; ++i)
        result.m_data[i] *= xx_scalar;
    return result;
}

template<typename tpDataType>
vector<tpDataType> &
assignment::vector<tpDataType>::operator+=(vector const & xx_vector)
{
    for (size_type i = 0; i < m_dim; ++i) {
        m_data[i] += xx_vector.m_data[i];
    }

    return (*this);
}

template<typename tpDataType>
vector<tpDataType> &
assignment::vector<tpDataType>::operator-=(vector const & xx_vector)
{
    for (size_type i = 0; i < m_dim; ++i) {
        m_data[i] -= xx_vector.m_data[i];
    }

    return (*this);
}

template<typename tpDataType>
vector<tpDataType> &
assignment::vector<tpDataType>::operator*=(vector const & xx_vector)
{
    for (size_type i = 0; i < m_dim; ++i) {
        m_data[i] *= xx_vector.m_data[i];
    }

    return (*this);
}

template<typename tpDataType>
template<typename T, typename std::enable_if<!std::is_integral<T>::value>::type*>
vector<tpDataType> assignment::vector<tpDataType>::operator *(size_type const xx_scalar)
{
    auto result = *this;
    for (size_type i = 0; i < m_dim; ++i) {
        result.m_data[i] *= xx_scalar;
    }

    return result;
}

template<typename tpDataType>
tpDataType const &
assignment::vector<tpDataType>::operator[](size_type const idx) const
{
    return m_data[idx];
}

template<typename tpDataType>
tpDataType &
assignment::vector<tpDataType>::operator[](size_type const idx)
{
    return m_data[idx];
}

/* ==== h  e  l  p  e  r     f  u  n  c  t  i  o  n  s==== */

template<typename tpDataType>
size_t const assignment::vector<tpDataType>::dim() const
{
    return m_dim;
}

template<typename tpDataType>
void assignment::vector<tpDataType>::set(tpDataType const & xx_scalar)
{
    for (size_t i = 0; i < m_dim; ++i) {
        (*this)[i] = xx_scalar;
    }
    return (*this);
}

}

#endif /* vector_h */
