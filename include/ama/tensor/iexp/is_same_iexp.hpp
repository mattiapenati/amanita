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

#ifndef AMA_TENSOR_IEXP_IS_SAME_IEXP_HPP
#define AMA_TENSOR_IEXP_IS_SAME_IEXP_HPP 1

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/inserter.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform.hpp>

namespace ama
{
  namespace tensor_
  {

    namespace mpl = ::boost::mpl;

    template <
          typename ILIST1
        , typename ILIST2
        >
    struct is_same_ilist:
        mpl::transform<
              ILIST1
            , ILIST2
            , mpl::and_<
                    mpl::contains<ILIST2, mpl::_1>
                  , mpl::contains<ILIST1, mpl::_2>
                  >
            , mpl::inserter<
                    mpl::true_
                  , mpl::and_<
                          mpl::_1
                        , mpl::_2
                        >
                  >
            >::type { };

    template <typename LEFT, typename RIGHT>
    struct is_same_iexp:
        mpl::and_<
              mpl::equal<
                    typename LEFT::value_type
                  , typename RIGHT::value_type
                  >
            , mpl::equal<
                    typename LEFT::dimension_type
                  , typename RIGHT::dimension_type
                  >
            , mpl::equal<
                    typename LEFT::controvariant_type
                  , typename RIGHT::controvariant_type
                  >
            , mpl::equal<
                    typename LEFT::covariant_type
                  , typename RIGHT::covariant_type
                  >
            , typename mpl::and_<
                    is_same_ilist<
                          typename LEFT::controvariant_list
                        , typename RIGHT::controvariant_list
                        >
                  , is_same_ilist<
                          typename LEFT::covariant_list
                        , typename RIGHT::covariant_list
                        >
                  >::type
            > { };

  }
}

#endif /* AMA_TENSOR_IEXP_IS_SAME_IEXP_HPP */
