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

#ifndef AMA_TENSOR_COPY_HPP
#define AMA_TENSOR_COPY_HPP 1

#include <ama/tensor/detail/copy.hpp>
#include <ama/tensor/detail/is_same_tensor.hpp>
#include <ama/tensor/detail/tensor_base.hpp>
#include <ama/tensor/iexp/iexp_base.hpp>
#include <ama/tensor/iexp/iexp_copy.hpp>

namespace ama
{

  template <typename SRC, typename DST>
  void copy(tensor_::tensor_base<SRC> const & src,
            tensor_::tensor_base<DST> & dst)
  {
    BOOST_MPL_ASSERT_MSG(
          (tensor_::is_same_tensor<SRC, DST>::value)
        , COMPONENT_WISE_BINARY_OPERATION_BETWEEN_DIFFERENT_TENSORS_ARE_NOT_ALLOWED
        , (SRC, DST));

    BOOST_MPL_ASSERT_MSG(
          (DST::is_assignable::value)
        , THE_DESTINATION_MUST_BE_ASSIGNABLE
        , (DST));

    typedef typename SRC::dimension_type dimension_type;
    typedef typename SRC::order_type order_type;

    tensor_::copy<dimension_type,order_type>::template apply(src.derived(), dst.derived());
  }

}

#endif /* AMA_TENSOR_COPY_HPP */
