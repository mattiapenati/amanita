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

#ifndef AMA_MULTI_ARRAY_GET_HPP
#define AMA_MULTI_ARRAY_GET_HPP 1

#include <ama/multi_array/config.hpp>
#include <ama/multi_array/multi_array.hpp>

#ifdef AMA_MULTI_ARRAY_USE_LINEAR_ACCESS

#include <boost/mpl/vector_c.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comma.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/repeat.hpp>

#define AMA_MA_GET_TYPE(S, D, O) \
  multi_array< S BOOST_PP_COMMA() D BOOST_PP_COMMA() O >

#define AMA_MA_GET_REFERENCE(S, D, O) \
  AMA_MA_GET_TYPE(S, D, O)::reference

#define AMA_MA_GET_CONST_REFERENCE(S, D, O) \
  AMA_MA_GET_TYPE(S, D, O)::const_reference

#define AMA_MA_GET_DEFAULT_TEMPLATE(S,D,O) \
  typename S BOOST_PP_COMMA() size_t D BOOST_PP_COMMA() size_t O

#define AMA_MA_CONCAT_COMMA(z, n, data) \
  BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(data, n)

#define AMA_MA_TEMPLATE(n) \
  BOOST_PP_REPEAT(n, AMA_MA_CONCAT_COMMA, size_t I)

#define AMA_MA_LIST(n) \
  BOOST_PP_REPEAT(n, AMA_MA_CONCAT_COMMA, I)

#define AMA_MA_GET(n) \
  template < AMA_MA_TEMPLATE(n) BOOST_PP_COMMA_IF(n) AMA_MA_GET_DEFAULT_TEMPLATE(S,D,O) > \
  typename AMA_MA_GET_REFERENCE(S,D,O) \
  get(AMA_MA_GET_TYPE(S,D,O) & ma) \
  { \
    typedef ::boost::mpl::vector_c<size_t BOOST_PP_COMMA_IF(n) AMA_MA_LIST(n) > ilist; \
    return ma.template at<ilist>(); \
  }

#define AMA_MA_GET_CONST(n) \
  template < AMA_MA_TEMPLATE(n) BOOST_PP_COMMA_IF(n) AMA_MA_GET_DEFAULT_TEMPLATE(S,D,O) > \
  typename AMA_MA_GET_CONST_REFERENCE(S,D,O) \
  get(AMA_MA_GET_TYPE(S,D,O) const & ma) \
  { \
    typedef ::boost::mpl::vector_c<size_t BOOST_PP_COMMA_IF(n) AMA_MA_LIST(n) > ilist; \
    return ma.template at<ilist>(); \
  }

#define AMA_MA_MACRO(z, n, data) \
  AMA_MA_GET(n) \
  AMA_MA_GET_CONST(n)

namespace ama
{
  BOOST_PP_REPEAT(
      BOOST_PP_INC(AMA_MULTI_ARRAY_MAX_LINEAR_ACCESS), AMA_MA_MACRO, )
}

#undef AMA_MA_GET_TYPE
#undef AMA_MA_GET_REFERENCE
#undef AMA_MA_GET_CONST_REFERENCE
#undef AMA_MA_GET_DEFAULT_TEMPLATE
#undef AMA_MA_CONCAT_COMMA
#undef AMA_MA_TEMPLATE
#undef AMA_MA_LIST
#undef AMA_MA_GET
#undef AMA_MA_GET_CONST
#undef AMA_MA_MACRO

#endif /* AMA_MULTI_ARRAY_USE_LINEAR_ACCESS */

#endif /* AMA_MULTI_ARRAY_GET_HPP */
