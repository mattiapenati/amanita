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

#ifndef AMA_TENSOR_DETAIL_IS_SAME_TENSOR_HPP
#define AMA_TENSOR_DETAIL_IS_SAME_TENSOR_HPP 1

#include <boost/mpl/and.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/equal_to.hpp>

namespace ama
{
  namespace tensor_
  {
    namespace mpl = ::boost::mpl;

    template <typename T1, typename T2>
    struct is_same_tensor:
        mpl::and_<
              mpl::equal<typename T1::value_type, typename T2::value_type>
            , mpl::equal_to<typename T1::dimension_type, typename T2::dimension_type>
            , mpl::equal_to<typename T1::controvariant_type, typename T2::controvariant_type>
            , mpl::equal_to<typename T1::covariant_type, typename T2::covariant_type>
            >{ };

  }
}

#endif /* AMA_TENSOR_DETAIL_IS_SAME_TENSOR_HPP */
