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
#include <ama/tensor/copy.hpp>
#include <ama/tensor/detail/tensor_base.hpp>
#include <ama/tensor/iexp/iexp.hpp>
#include <ama/tensor/iexp/iexp_calculator.hpp>
#include <ama/tensor/iexp/iexp_factory.hpp>
#include <ama/tensor/iexp/indices.hpp>
#include <ama/common/size_t.hpp>
#include <ama/multi_array/multi_array.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/size.hpp>
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

      typedef ::boost::mpl::true_ is_assignable;
      typedef ::boost::mpl::false_ is_temporary;
    };

  }


  /* class declaration */
  template <typename S, size_t D, size_t CT, size_t CO>
  class tensor:
        public tensor_::tensor_base< tensor<S,D,CT,CO> >
      , public multi_array<S,D,CT+CO>
#ifdef AMA_MULTI_ARRAY_USE_LINEAR_ACCESS
      , public tensor_::iexp< tensor<S,D,CT,CO>, CT+CO >
#endif /* AMA_MULTI_ARRAY_USE_LINEAR_ACCESS */
  {
  public:
    /* resolv the ambiguity */
    typedef typename tensor_::tensor_base< tensor<S,D,CT,CO> >::value_type value_type;
    typedef typename tensor_::tensor_base< tensor<S,D,CT,CO> >::dimension_type dimension_type;

    /* needed */
    typedef typename tensor_::tensor_base< tensor<S,D,CT,CO> >::controvariant_type controvariant_type;
    typedef typename tensor_::tensor_base< tensor<S,D,CT,CO> >::covariant_type covariant_type;

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
    explicit
    tensor(tensor_::tensor_base<DERIVED> const & t):
        tensor_::tensor_base< tensor<S,D,CT,CO> >(),
        multi_array<S,D,CT+CO>()
    {
      ama::copy(t.derived(), *this);
    }

  public:
    /* copy operator */
    template <typename DERIVED>
    tensor & operator=(tensor const & t)
    {
      ama::copy(t.derived(), *this);
      return *this;
    }

    template <typename DERIVED>
    tensor & operator=(tensor_::tensor_base<DERIVED> const & t)
    {
      ama::copy(t.derived(), *this);
      return *this;
    }


#ifdef AMA_MULTI_ARRAY_USE_LINEAR_ACCESS
  public:
    using multi_array<S,D,CT+CO>::operator();
    using tensor_::iexp< tensor<S,D,CT,CO> , CT+CO >::operator();
#endif /* AMA_MULTI_ARRAY_USE_LINEAR_ACCESS */

/* ============================ INDEX EXPRESSION ============================ */
  public:
    /* index expression contruction */
    template <typename ILIST>
    typename tensor_::iexp_calculator<tensor, ILIST, ::boost::mpl::false_>::type
    idx()
    {
      namespace mpl = ::boost::mpl;

      typedef mpl::equal_to<
            mpl::size<typename tensor_::controvariant<tensor<S,D,CT,CO>, ILIST>::type>
          , controvariant_type
          > ct;
      typedef mpl::equal_to<
            mpl::size<typename tensor_::covariant<tensor<S,D,CT,CO>, ILIST>::type>
          , covariant_type
          > co;

      BOOST_MPL_ASSERT_MSG(
            (ct::value && co::value)
          , THE_LENGTH_OF_LIST_OF_INDICES_MUST_BE_EQUAL_TO_THE_TENSOR_ORDER
          , (ILIST));

      typedef typename tensor_::iexp_calculator<tensor, ILIST, ::boost::mpl::false_>::type what;

      return tensor_::iexp_factory<what>::template apply<ILIST>(*this);
    }

    template <typename ILIST>
    typename tensor_::iexp_calculator<tensor, ILIST, ::boost::mpl::true_>::type
    idx() const
    {
      namespace mpl = ::boost::mpl;

      typedef mpl::equal_to<
            mpl::size<typename tensor_::controvariant<tensor<S,D,CT,CO>, ILIST>::type>
          , controvariant_type
          > ct;
      typedef mpl::equal_to<
            mpl::size<typename tensor_::covariant<tensor<S,D,CT,CO>, ILIST>::type>
          , covariant_type
          > co;

      BOOST_MPL_ASSERT_MSG(
            (ct::value && co::value)
          , THE_LENGTH_OF_LIST_OF_INDICES_MUST_BE_EQUAL_TO_THE_TENSOR_ORDER
          , (ILIST));

      typedef typename tensor_::iexp_calculator<tensor, ILIST, ::boost::mpl::true_>::type what;

      return tensor_::iexp_factory<what>::template apply<ILIST>(*this);
    }
/* ============================ INDEX EXPRESSION ============================ */
  };




  /* partial specialization for 0-order tensor */
  template <typename S, size_t D>
  class tensor<S,D,0,0>:
      public tensor_::tensor_base< tensor<S,D,0,0> >,
      public multi_array<S,D,0>
  {
  public:
    /* resolv the ambiguity */
    typedef typename tensor_::tensor_base< tensor<S,D,0,0> >::value_type value_type;
    typedef typename tensor_::tensor_base< tensor<S,D,0,0> >::dimension_type dimension_type;

  public:
    /* default constructor */
    explicit
    tensor(S const & value = S()):
        tensor_::tensor_base< tensor<S,D,0,0> >(),
        multi_array<S,D,0>(value) { }

    /* copy constructor */
    tensor(tensor const & t):
        tensor_::tensor_base< tensor<S,D,0,0> >(),
        multi_array<S,D,0>(t) { }

    template <typename DERIVED>
    explicit
    tensor(tensor_::tensor_base<DERIVED> const & t):
        tensor_::tensor_base< tensor<S,D,0,0> >(),
        multi_array<S,D,0>()
    {
      ama::copy(t.derived(), *this);
    }

  public:
    /* copy operator */
    template <typename DERIVED>
    tensor & operator=(tensor_::tensor_base<DERIVED> const & t)
    {
      ama::copy(t.derived(), *this);
      return *this;
    }

  public:
    /* cast operator */
    operator value_type() { return this->template at<void>(); }
    operator value_type() const { return this->template at<void>(); }
  };




  /* partial specialization for 0-dimension tensor */
  template <typename S, size_t CT, size_t CO>
  class tensor<S,0,CT,CO>:
      public tensor_::tensor_base< tensor<S,0,CT,CO> >,
      public multi_array<S,0,CT+CO>
  {
  public:
    /* resolv the ambiguity */
    typedef typename tensor_::tensor_base< tensor<S,0,CT,CO> >::value_type value_type;
    typedef typename tensor_::tensor_base< tensor<S,0,CT,CO> >::dimension_type dimension_type;
  };




  /* partial specialization for 0-dimension tensor */
  template <typename S>
  class tensor<S,0,0,0>:
      public tensor_::tensor_base< tensor<S,0,0,0> >,
      public multi_array<S,0,0>
  {
  public:
    /* resolv the ambiguity */
    typedef typename tensor_::tensor_base< tensor<S,0,0,0> >::value_type value_type;
    typedef typename tensor_::tensor_base< tensor<S,0,0,0> >::dimension_type dimension_type;
  };

}

#endif /* AMA_TENSOR_TENSOR_HPP */
