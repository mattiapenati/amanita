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

#ifndef AMA_TENSOR_TENSOR_HPP
#define AMA_TENSOR_TENSOR_HPP 1

#include <ama/tensor/config.hpp>
#include <ama/tensor/detail/tensor_base.hpp>
#include <ama/common/size_t.hpp>
#include <ama/multi_array/multi_array.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>

namespace ama
{

  template <typename S, /* scalar value used to represent scalar value */
            size_t D,   /* the dimension of vector space               */
            size_t CT,  /* the dimension of controvariant part         */
            size_t CO>  /* the dimension of covariant part             */
  class tensor;


  /* tensor traits specialization */
  namespace tensor_
  {

    template <typename S, size_t D, size_t CT, size_t CO>
    struct tensor_traits< tensor<S,D,CT,CO> >
    {
      typedef S value_type;

      typedef ::boost::mpl::size_t<D> dimension_type;

      typedef ::boost::mpl::size_t<CT> controvariant_type;
      typedef ::boost::mpl::size_t<CO> covariant_type;

      typedef ::boost::mpl::bool_<true> is_assignable;
      typedef ::boost::mpl::bool_<false> is_temporary;
    };

  }


  /* class declaration */
  template <typename S, size_t D, size_t CT, size_t CO>
  class tensor:
        public tensor_::tensor_base< tensor<S,D,CT,CO> >,
        public multi_array<S,D,CT+CO>
  {
  public:
    /* resolv the ambiguity */
    typedef typename tensor_::tensor_base< tensor<S,D,CT,CO> >::value_type value_type;
    typedef typename tensor_::tensor_base< tensor<S,D,CT,CO> >::dimension_type dimension_type;

  public:
    /* default constructor */
    tensor():
        tensor_::tensor_base< tensor<S,D,CT,CO> >(),
        multi_array<S,D,CT+CO>() { }

    /* copy constructor */
    tensor(tensor const & t):
        tensor_::tensor_base< tensor<S,D,CT,CO> >(),
        multi_array<S,D,CT+CO>(t) { }

    template <typename DERIVED>
    tensor(tensor_::tensor_base<DERIVED> const & t):
        tensor_::tensor_base< tensor<S,D,CT,CO> >(),
        multi_array<S,D,CT+CO>()
    {
      /* TODO use copy */
    }

  public:
    /* copy operator */
    template <typename DERIVED>
    tensor & operator=(tensor_::tensor_base<DERIVED> const & t)
    {
      /* TODO use copy */
      return *this;
    }
  };


  /* TODO same partial specialization of multi_array<...> */

}

#endif /* AMA_TENSOR_TENSOR_HPP */
