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

#include <ama/common/size_t.hpp>
#include <ama/tensor/iexp/indices.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/max.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/vector/vector0.hpp>

/* forward declaration */
namespace ama
{
  template <typename T, size_t D, size_t CT, size_t CO> class tensor;

  namespace tensor_
  {
    template <typename TENSOR, typename CTLIST, typename COLIST> class iexp_constant;
    template <typename TENSOR, typename CTLIST, typename COLIST> class iexp_mutable;
    template <typename TENSOR, typename CTLIST, typename COLIST> class iexp_temporary;
  }
}




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
                  , mpl::_1
                  >
            >::type { };

    /* from a indices list compute the list of repeated */
    template <typename ILIST>
    struct repeated_indices:
        mpl::fold<
              ILIST
            , mpl::vector0<>
            , mpl::if_<
                    mpl::and_<
                          mpl::greater<
                                mpl::count<ILIST, mpl::_2>
                              , mpl::size_t<1>
                              >
                        , mpl::not_<
                                mpl::contains<
                                mpl::_1
                              , mpl::_2
                              >
                              >
                        >
                  , mpl::push_back<mpl::_1, mpl::_2>
                  , mpl::_1
                  >
            >::type { };

    /* check if all indices are repeated */
    template <typename ILIST>
    struct all_repeated_indices:
        mpl::fold<
              ILIST
            , mpl::true_
            , mpl::and_<
                  mpl::_1
                , mpl::greater<
                        mpl::count<ILIST, mpl::_2>
                      , mpl::size_t<1>
                      >
                >
            >::type { };

    /* compute the return type of an iexp expression */
    template <typename TENSOR, typename ILIST, typename CONST>
    struct iexp_calculator:
        mpl::if_<
              has_repeated_indices<ILIST>
            , typename mpl::if_<
                    all_repeated_indices<ILIST>
                  , typename TENSOR::value_type
                  , iexp_temporary<
                          typename iexp_reduce<TENSOR, ILIST>::tensor_type
                        , typename iexp_reduce<TENSOR, ILIST>::controvariant
                        , typename iexp_reduce<TENSOR, ILIST>::covariant
                        >
                  >::type
            , typename mpl::if_<
                    CONST
                  , iexp_constant<
                          TENSOR
                        , typename controvariant<TENSOR,ILIST>::type
                        , typename covariant<TENSOR,ILIST>::type
                        >
                  , iexp_mutable<
                          TENSOR
                        , typename controvariant<TENSOR,ILIST>::type
                        , typename covariant<TENSOR,ILIST>::type
                        >
                  >::type
            >
    {
      typedef typename mpl::fold<
            ILIST
          , mpl::size_t<0>
          , mpl::max<
                  mpl::_1
                , mpl::count<ILIST, mpl::_1>
                >
          >::type max_;

      /* check if the indeces are repeated at most twice */
      BOOST_MPL_ASSERT_MSG(
            (mpl::less_equal< max_, mpl::size_t<2> >::type::value)
          , AN_INDEX_COULD_BE_REPEATED_AT_MOST_TWICE
          , (TENSOR, ILIST));

      typedef typename controvariant<TENSOR,ILIST>::type controvariant_;
      typedef typename covariant<TENSOR,ILIST>::type covariant_;

      typedef typename mpl::not_< has_repeated_indices<controvariant_> >::type bct_;
      typedef typename mpl::not_< has_repeated_indices<covariant_> > bco_;

      /* check for reduced indeces */
      BOOST_MPL_ASSERT_MSG(
            (mpl::and_<bct_,bco_>::type::value)
          , YOU_CANNOT_REDUCE_TWO_INDICES_OF_SAME_TYPE
          , (TENSOR, ILIST));
    };

  }
}

#endif /* AMA_TENSOR_IEXP_IEXP_CALCULATOR_HPP */
