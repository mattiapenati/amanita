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

#ifndef AMA_TENSOR_IEXP_HPP
#define AMA_TENSOR_IEXP_HPP 1

#include <ama/tensor/index.hpp>

#include <ama/tensor/iexp/iexp_cwise_unary.hpp>
#include <ama/tensor/iexp/iexp_cwise_binary.hpp>
#include <ama/tensor/operator.hpp>

namespace ama
{

  /* plus */
  template <typename DERIVED>
  DERIVED const &
  operator+(tensor_::iexp_base<DERIVED> const & ie) { return ie.derived(); }

  /* minus */
  template <typename DERIVED>
  tensor_::iexp_cwise_unary<
        DERIVED
      , std::negate<typename DERIVED::value_type>
      >
  operator-(tensor_::iexp_base<DERIVED> const & ie)
  {
    typedef typename DERIVED::value_type value_type;
    typedef std::negate<value_type> operator_type;

    typedef tensor_::iexp_cwise_unary<DERIVED,operator_type> return_type;

    return return_type(ie.derived());
  }

  /* multiplication by scalar value */
  template <typename DERIVED>
  tensor_::iexp_cwise_unary<
        DERIVED
      , tensor_::scalar_mul<typename DERIVED::value_type>
      >
  operator*(typename DERIVED::value_type const & a,
            tensor_::iexp_base<DERIVED> const & ie)
  {
    typedef typename DERIVED::value_type value_type;
    typedef tensor_::scalar_mul<value_type> operator_type;

    typedef tensor_::iexp_cwise_unary<DERIVED,operator_type> return_type;

    return return_type(ie.derived(), operator_type(a));
  }




  /* plus */
  template <typename LEFT, typename RIGHT>
  tensor_::iexp_cwise_binary<
        LEFT
      , RIGHT
      , std::plus<typename LEFT::value_type>
      >
  operator+(tensor_::iexp_base<LEFT> const & left,
            tensor_::iexp_base<RIGHT> const & right)
  {
    typedef typename LEFT::value_type value_type;
    typedef std::plus<value_type> operator_type;
    typedef tensor_::iexp_cwise_binary<LEFT, RIGHT, operator_type> return_type;

    return return_type(left.derived(), right.derived());
  }

  /* minus */
  template <typename LEFT, typename RIGHT>
  tensor_::iexp_cwise_binary<
        LEFT
      , RIGHT
      , std::minus<typename LEFT::value_type>
      >
  operator-(tensor_::iexp_base<LEFT> const & left,
            tensor_::iexp_base<RIGHT> const & right)
  {
    typedef typename LEFT::value_type value_type;
    typedef std::minus<value_type> operator_type;
    typedef tensor_::iexp_cwise_binary<LEFT, RIGHT, operator_type> return_type;

    return return_type(left.derived(), right.derived());
  }


}


#endif /* AMA_TENSOR_IEXP_HPP */
