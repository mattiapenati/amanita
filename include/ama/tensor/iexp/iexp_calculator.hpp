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

#ifndef AMA_TENSOR_IEXP_IEXP_CALCULATOR_HPP
#define AMA_TENSOR_IEXP_IEXP_CALCULATOR_HPP 1

#include <ama/tensor/iexp/iexp_constant.hpp>
#include <ama/tensor/iexp/iexp_mutable.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/vector/vector0.hpp>

namespace ama
{
  namespace tensor_
  {

    namespace mpl = ::boost::mpl;

    /* check if the list contains repeated indices */
    template <typename ILIST>
    struct has_repeated_indices:
        mpl::fold<
              ILIST
            , mpl::false_
            , mpl::or_<
                  mpl::_1
                , mpl::greater<
                        mpl::count<ILIST, mpl::_2>
                      , mpl::size_t<1>
                      >
                >
            >::type { };

    /* from a indices list compute the list of not-repeated */
    template <typename ILIST>
    struct not_repeated_indices:
        mpl::fold<
              ILIST
            , mpl::vector0<>
            , mpl::if_<
                    mpl::equal_to<
                          mpl::count<ILIST, mpl::_2>
                        , mpl::size_t<1>
                        >
                  , mpl::push_back<mpl::_1, mpl::_2>
                  , mpl::_2
                  >
            > { };

    /* from a indices list compute the list of repeated */
    template <typename ILIST>
    struct repeated_indices:
        mpl::fold<
              ILIST
            , mpl::vector0<>
            , mpl::if_<
                    mpl::greater<
                          mpl::count<ILIST, mpl::_2>
                        , mpl::size_t<1>
                        >
                  , mpl::push_back<mpl::_1, mpl::_2>
                  , mpl::_2
                  >
            > { };

    /* check if all indices are repeated */
    template <typename ILIST>
    struct all_repeated_indices:
        mpl::empty< not_repeated_indices<ILIST> > { };

    /* compute the return type of an iexp expression */
    template <typename TENSOR, typename ILIST, typename CONST>
    struct iexp_calculator:
        mpl::if_<
              has_repeated_indices<ILIST>
            , mpl::if_<
                    all_repeated_indices<ILIST>
                  , typename TENSOR::value_type
                  , iexp_temporary<TENSOR, typename not_repeated_indices<ILIST>::type>
                  >
            , mpl::if_<
                    CONST
                  , iexp_constant<TENSOR, ILIST>
                  , iexp_mutable<TENSOR, ILIST>
                  >
            >::type { };

  }
}

#endif /* AMA_TENSOR_IEXP_IEXP_CALCULATOR_HPP */
