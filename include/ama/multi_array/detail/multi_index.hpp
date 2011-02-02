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

#ifndef AMA_MULTI_ARRAY_DETAIL_MULTI_INDEX_HPP
#define AMA_MULTI_ARRAY_DETAIL_MULTI_INDEX_HPP 1

#include <ama/common/size_t.hpp>
#include <ama/multi_array/config.hpp>

#ifdef AMA_MULTI_ARRAY_USE_LINEAR_ACCESS

#include <ama/multi_array/detail/index_runtime.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/repeat.hpp>

#define AMA_MA_MI_CONCAT_COMMA(z, n, data) \
  BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(data, n)

#define AMA_MA_MI_ARGUMENT(n) \
  BOOST_PP_REPEAT(n, AMA_MA_MI_CONCAT_COMMA, size_t const & I)

#define AMA_MA_MI_CALL(n) \
  BOOST_PP_REPEAT(n, AMA_MA_MI_CONCAT_COMMA, I)

#define AMA_MA_MI_SPECIALIZATION(n) \
  template <typename DERIVED, typename T, size_t D> \
  class multi_index<DERIVED, T, D, n> \
  { \
  public: \
    typedef T value_type; \
    \
    typedef T & reference; \
    typedef T & const_reference; \
    \
  protected: \
    typedef multi_index<DERIVED, T, D, n> base_type; \
    typedef DERIVED derived_type; \
    \
  public: \
    derived_type & derived() { return *static_cast<derived_type *>(this); } \
    derived_type const & derived() const { return *static_cast<derived_type const *>(this); } \
    \
  public: \
    reference operator()( AMA_MA_MI_ARGUMENT(n) ) \
    { \
      size_t const i = ::ama::multi_array_::index_runtime<D>( AMA_MA_MI_CALL(n) ); \
      return derived().m_data.at(i); \
    } \
    \
    const_reference operator()( AMA_MA_MI_ARGUMENT(n) ) const \
    { \
      size_t const i = ::ama::multi_array_::index_runtime<D>( AMA_MA_MI_CALL(n) ); \
      return derived().m_data.at(i); \
    } \
  };

#define AMA_MA_MI_MACRO(z, n, data) \
  AMA_MA_MI_SPECIALIZATION(n)

namespace ama
{
  namespace multi_array_
  {

    template <typename DERIVED, typename T, size_t D, size_t O>
    class multi_index
    {
    public:
      typedef T value_type;

      typedef T & reference;
      typedef T & const_reference;

    protected:
      typedef multi_index<DERIVED, T, D, O> base_type;
      typedef DERIVED derived_type;

    public:
      reference operator()();
      const_reference operator()() const;
    };

    BOOST_PP_REPEAT(
        BOOST_PP_INC(AMA_MULTI_ARRAY_MAX_LINEAR_ACCESS), AMA_MA_MI_MACRO, )

  }
}

#undef AMA_MA_MI_CONCAT_COMMA
#undef AMA_MA_MI_ARGUMENT
#undef AMA_MA_MI_CALL
#undef AMA_MA_MI_SPECIALIZATION
#undef AMA_MA_MI_MACRO

#endif /* AMA_MULTI_ARRAY_USE_LINEAR_ACCESS */

#endif /* AMA_MULTI_ARRAY_DETAIL_MULTI_INDEX_HPP */
