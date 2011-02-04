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

#ifndef AMA_TENSOR_MUL_MUL_FACTORY_HPP
#define AMA_TENSOR_MUL_MUL_FACTORY_HPP 1

#include <ama/tensor/mul/mul_outer.hpp>

namespace ama
{
  namespace tensor_
  {

    /* forward declaration*/
    template <typename LEFT, typename RIGHT> class mul_outer;

    /* reduction over all indices */
    template <typename WHAT>
    struct mul_factory
    {
      template <typename LEFT, typename RIGHT>
      static
      WHAT apply(LEFT const & left, RIGHT const & right);
    };


    /* specialization for outer product */
    template <typename LEFT, typename RIGHT>
    struct mul_factory< mul_outer<LEFT, RIGHT> >
    {
      template <typename VOID>
      static
      mul_outer<LEFT, RIGHT> apply(LEFT const & left,
                                   RIGHT const & right)
      {
        return mul_outer<LEFT, RIGHT>(left,right);
      }
    };

  }
}

#endif /* AMA_TENSOR_MUL_MUL_FACTORY_HPP */
