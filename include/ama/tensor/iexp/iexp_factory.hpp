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

#ifndef AMA_TENSOR_IEXP_IEXP_FACTORY_HPP
#define AMA_TENSOR_IEXP_IEXP_FACTORY_HPP 1

#include <ama/tensor/iexp/iexp_mutable.hpp>
#include <ama/tensor/iexp/iexp_constant.hpp>

namespace ama
{
  namespace tensor_
  {

    /* forward declaration */
    template <typename WHAT> struct iexp_factory;


    /* specialization for mutable index expression */
    template <typename DERIVED, typename ILIST>
    struct iexp_factory< iexp_mutable<DERIVED, ILIST> >
    {
      static
      iexp_mutable<DERIVED,ILIST>
      apply(DERIVED & t)
      {
        return iexp_mutable<DERIVED,ILIST>(t);
      }
    };

    /* specialization for constant index expression */
    template <typename DERIVED, typename ILIST>
    struct iexp_factory< iexp_constant<DERIVED, ILIST> >
    {
      static
      iexp_constant<DERIVED,ILIST>
      apply(DERIVED & t)
      {
        return iexp_constant<DERIVED,ILIST>(t);
      }
    };

  }
}

#endif /* AMA_TENSOR_IEXP_IEXP_FACTORY_HPP */