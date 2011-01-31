/*
 * Copyright (c) 2011, Mattia Penati <mattia.penati@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice,
 *       this list of conditions and the following disclaimer in the documentation
 *       and/or other materials provided with the distribution.
 *     * Neither the name of the Mattia Penati nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef AMA_MULTI_ARRAY_MULTI_ARRAY_HPP
#define AMA_MULTI_ARRAY_MULTI_ARRAY_HPP 1

#include <ama/common/size_t.hpp>
#include <ama/common/array.hpp>

#include <ama/multi_array/detail/index_runtime.hpp>
#include <ama/multi_array/detail/size.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/size_t.hpp>

namespace ama
{

  template <typename T, size_t D, size_t O>
  class multi_array
  {
  public:
    typedef T value_type;

    typedef T & reference;
    typedef T const & const_reference;

  public:
    typedef ::boost::mpl::size_t<D> dimension_type;
    typedef ::boost::mpl::size_t<O> order_type;

  public:
    /* default constructor */
    multi_array()
        : m_data()
    { }

    /* copy constructor */
    template <typename T2>
    explicit
    multi_array(multi_array<T2, D, O> const & rhs)
        : m_data(rhs.m_data)
    { }

  public:
    /* copy operator */
    template <typename T2>
    multi_array & operator=(multi_array<T2, D, O> const & rhs)
    {
      m_data = rhs.m_data;
      return *this;
    }

  public:
    /* get a component from a index list (Boost.MPL - Forward Sequence) */
    template <typename ILIST>
    reference at()
    {
      rangecheck<ILIST>();
      typedef typename multi_array_::index_runtime<dimension_type,ILIST>::type index;

      return m_data.at(index::value);
    }

    /* get a component from a index list (Boost.MPL - Forward Sequence) */
    template <typename ILIST>
    const_reference at() const
    {
      rangecheck<ILIST>();
      typedef typename multi_array_::index_runtime<dimension_type,ILIST>::type index;

      return m_data.at(index::value);
    }

  public:
    /* the size of storage */
    size_t size() const { return m_size; }

    /* check if the storage is empty */
    bool empty() const { return false; }

  public:
    /* dimension and order of storage */
    size_t dimension() const { return D; }
    size_t order() const { return O; }

  protected:
    /* the size of array */
    BOOST_STATIC_CONSTANT(size_t, m_size = (::ama::multi_array_::size<D, O>::value));

    /* the array to store the values */
    ::ama::array<T, m_size> m_data;

  protected:
    /* check a indeces list (Boost.MPL - Forward Sequence) */
    template <typename ILIST>
    void rangecheck()
    {
      namespace mpl = ::boost::mpl;

      /* some alias */
      typedef mpl::bool_<true> true_;

      typedef mpl::size_t<0> zero_;

      /* check each indeces */
      typedef typename mpl::fold<
            ILIST
          , true_
          , mpl::and_<
                  mpl::_1
                , mpl::less<mpl::_2,dimension_type>
                , mpl::greater_equal<mpl::_2,zero_>
                >
          >::type range_;

      /* check the number of indeces */
      typedef typename mpl::equal_to<mpl::size<ILIST>,order_type> size_;

      /* check */
      BOOST_MPL_ASSERT((mpl::and_<range_,size_>));
    }
  };


  template <typename T, size_t O>
  class multi_array<T, 0, O>
  {
  public:
    typedef T value_type;

    typedef T & reference;
    typedef T const & const_reference;

  public:
    /* the size of storage */
    size_t size() const { return 0; }

    /* check if the storage is empty */
    bool empty() const { return true; }

  public:
    /* dimension and order of storage */
    size_t dimension() const { return 0; }
    size_t order() const { return O; }
  };

}

#endif /* AMA_MULTI_ARRAY_MULTI_ARRAY_HPP */