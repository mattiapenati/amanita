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

#ifndef AMA_MULTI_ARRAY_DETAIL_INDEX_COMPILETIME_HPP
#define AMA_MULTI_ARRAY_DETAIL_INDEX_COMPILETIME_HPP 1

#include <ama/common/size_t.hpp>
#include <ama/multi_array/config.hpp>

#ifdef AMA_MULTI_ARRAY_USE_LINEAR_ACCESS

#include <boost/assert.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/repeat.hpp>

#define AMA_MA_IC_CONCAT_COMMA(z, n, data) \
  BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(data, n)

#define AMA_MA_IC_ARGUMENT(n) \
  BOOST_PP_REPEAT(n, AMA_MA_IC_CONCAT_COMMA, size_t const & I)

#define AMA_MA_IC_INDEX(n) \
  BOOST_PP_CAT(I, BOOST_PP_DEC(n))

#define AMA_MA_IC_CHECK(D, n) \
  BOOST_ASSERT((AMA_MA_IC_INDEX(n) < D))

#define AMA_MA_IC_PREV(D, n) \
  index_compiletime<D>( BOOST_PP_REPEAT(BOOST_PP_DEC(n), AMA_MA_IC_CONCAT_COMMA, I) )

#define AMA_MA_IC_RETURN(D, n) \
  AMA_MA_IC_CHECK(D, n); \
  return (D * AMA_MA_IC_PREV(D, n)) + AMA_MA_IC_INDEX(n)

#define AMA_MA_IC_INDEX_COMPILE(n) \
  template <size_t D> \
  size_t index_compiletime( AMA_MA_IC_ARGUMENT(n) ) \
  { \
    BOOST_PP_IF(n, AMA_MA_IC_RETURN(D, n), return 0); \
  }

#define AMA_MA_IC_MACRO(z, n, data) \
  AMA_MA_IC_INDEX_COMPILE(n)

namespace ama
{
  namespace multi_array_
  {

    BOOST_PP_REPEAT(
        BOOST_PP_INC(4), AMA_MA_IC_MACRO, )

  }
}

#undef AMA_MA_IC_CONCAT_COMMA
#undef AMA_MA_IC_ARGUMENT
#undef AMA_MA_IC_INDEX
#undef AMA_MA_IC_CHECK
#undef AMA_MA_IC_PREV
#undef AMA_MA_IC_RETURN
#undef AMA_MA_IC_INDEX_COMPILE
#undef AMA_MA_IC_MACRO

#endif /* AMA_MULTI_ARRAY_USE_LINEAR_ACCESS */

#endif /* AMA_MULTI_ARRAY_DETAIL_INDEX_COMPILETIME_HPP */
