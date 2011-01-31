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

#ifndef AMA_COMMON_ARRAY_HPP
#define AMA_COMMON_ARRAY_HPP 1

#include <ama/common/size_t.hpp>
#include <boost/array.hpp>
#include <boost/static_assert.hpp>
#include <algorithm>

namespace ama
{

  /*
   * This class extends the current boost array. Some useful constructor are
   * defined.
   */
  template <typename T, size_t N>
  class array:
    public ::boost::array<T,N>
  {
  public:
    explicit
    array(T const & value = T())
        : ::boost::array<T,N>()
    {
      this->fill(value);
    }


    template <typename T2>
    explicit
    array(array<T2, N> const & rhs)
        : ::boost::array<T,N>()
    {
      *static_cast< ::boost::array<T,N>* >(this) = rhs;
    }


    template <typename _InputIterator>
    array(_InputIterator begin, _InputIterator end)
        : ::boost::array<T,N>()
    {
      std::copy(begin, end, this->begin());
    }
  };


  /* the get function for static access to array */
  template <size_t I, typename T, size_t N>
  typename array<T, N>::reference
  get(array<T,N> & a)
  {
    BOOST_STATIC_ASSERT((I < N));
    return a.elems[I];
  }

  template <size_t I, typename T, size_t N>
  typename array<T, N>::const_reference
  get(array<T,N> const & a)
  {
    BOOST_STATIC_ASSERT((I < N));
    return a.elems[I];
  }

}

#endif /* AMA_COMMON_ARRAY_HPP */
