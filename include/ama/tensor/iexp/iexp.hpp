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
 *     * Neither the name of the Politecnico di Milano nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
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

#ifndef AMA_TENSOR_IEXP_IEXP_HPP
#define AMA_TENSOR_IEXP_IEXP_HPP 1

#include <ama/tensor/config.hpp>

#ifdef AMA_MULTI_ARRAY_USE_LINEAR_ACCESS

#include <ama/tensor/index.hpp>
#include <ama/tensor/iexp/iexp_calculator.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/list/adt.hpp>


namespace ama
{
  namespace tensor_
  {

    template <typename DERIVED, size_t ORDER> struct iexp;

    namespace mpl = ::boost::mpl;




#define AMA_TENSOR_IEXP_CONCAT_COMMA(z, n, data) \
  BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(data, n)

#define AMA_TENSOR_IEXP_CONCAT_COMMA_INDEX(z, n, data) \
  BOOST_PP_COMMA_IF(n) ::ama::index< BOOST_PP_CAT(data, n) >

#define AMA_TENSOR_IEXP_CONCAT_COMMA_ARG(z, n, data) \
  BOOST_PP_COMMA_IF(n) ::ama::index< BOOST_PP_CAT(data, n) > const &

#define AMA_TENSOR_IEXP_TEMPLATE(n) \
  BOOST_PP_REPEAT(n, AMA_TENSOR_IEXP_CONCAT_COMMA, char I)

#define AMA_TENSOR_IEXP_LIST(n) \
  ::boost::mpl::vector< BOOST_PP_REPEAT(n, AMA_TENSOR_IEXP_CONCAT_COMMA_INDEX, I) >

#define AMA_TENSOR_IEXP_ARGOUMENTS(n) \
  BOOST_PP_REPEAT(n, AMA_TENSOR_IEXP_CONCAT_COMMA_ARG, I)

#define AMA_TENSOR_IEXP_SPECIALIZATION(n) \
    template <typename DERIVED> \
    struct iexp< DERIVED , n > \
    { \
      BOOST_PP_IF(n, template <, ) AMA_TENSOR_IEXP_TEMPLATE(n) BOOST_PP_IF(n, >, ) \
      typename iexp_calculator<DERIVED, AMA_TENSOR_IEXP_LIST(n) , mpl::false_>::type \
      operator()( AMA_TENSOR_IEXP_ARGOUMENTS(n) ) \
      { \
        return static_cast<DERIVED *>(this)->template idx< AMA_TENSOR_IEXP_LIST(n) >(); \
      } \
      \
      BOOST_PP_IF(n, template <, ) AMA_TENSOR_IEXP_TEMPLATE(n) BOOST_PP_IF(n, >, ) \
      typename iexp_calculator<DERIVED, AMA_TENSOR_IEXP_LIST(n) , mpl::true_>::type \
      operator()( AMA_TENSOR_IEXP_ARGOUMENTS(n) ) const \
      { \
        return static_cast<DERIVED const *>(this)->template idx< AMA_TENSOR_IEXP_LIST(n) >(); \
      } \
    };

#define AMA_TENSOR_IEPX_MACRO(z, n, data) \
    AMA_TENSOR_IEXP_SPECIALIZATION(n)


    BOOST_PP_REPEAT(
        BOOST_PP_INC(AMA_TENSOR_MAX_LINEAR_ACCESS), AMA_TENSOR_IEPX_MACRO, )


#undef AMA_TENSOR_IEXP_CONCAT_COMMA
#undef AMA_TENSOR_IEXP_CONCAT_COMMA_INDEX
#undef AMA_TENSOR_IEXP_CONCAT_COMMA_ARG
#undef AMA_TENSOR_IEXP_TEMPLATE
#undef AMA_TENSOR_IEXP_LIST
#undef AMA_TENSOR_IEXP_ARGOUMENTS
#undef AMA_TENSOR_IEXP_SPECIALIZATION
#undef AMA_TENSOR_IEPX_MACRO




  }
}

#endif /* AMA_MULTI_ARRAY_USE_LINEAR_ACCESS */

#endif /* AMA_TENSOR_IEXP_IEXP_HPP */
