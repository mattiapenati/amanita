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

#ifndef AMA_TENSOR_IEXP_SUM_HPP
#define AMA_TENSOR_IEXP_SUM_HPP 1

#include <ama/tensor/iexp/iexp_copy.hpp>
#include <ama/tensor/detail/copy.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/size.hpp>

namespace ama
{
  namespace tensor_
  {

    namespace mpl = ::boost::mpl;

    /* apply the sum: a trick to remove the last operation */
    template <typename T> T sum_op(T const & a, T const & b) { return a + b; }
    template <typename T> T sum_op(T const & a, mpl::na const &) { return a; }

    /* this struct implement the sum */
    template <
          typename D               /* the dimensione of tensor */
        , typename O               /* the order of tensor */
        , typename I = first<O>    /* the first multi-index */
        , typename R = mpl::false_ /* this type is true for the last multi-index */
        >
    struct sum
    {
      template <typename IMAP, typename ISUM, typename IEXP>
      static
      typename IEXP::value_type
      apply(IEXP const & iexp)
      {
        BOOST_MPL_ASSERT_MSG(
              (mpl::equal_to< mpl::size<I> , mpl::size<ISUM> >::value)
            , YOU_GIVE_A_INCORRECT_LIST_OF_INDICES
            , (I, ISUM));

        /* append to map */
        typedef typename mpl::fold<
              IMAP
            , typename make_imap<ISUM, I>::type
            , mpl::insert<mpl::_1, mpl::_2>
            >::type imap;

        /* increment the multi-index */
        typedef typename increment<D,I>::type increment_type;

        /* the first is the multi-index incremented */
        typedef typename mpl::first<increment_type>::type i;
        /* the second is a boolean flag toidentify the last multi-index */
        typedef typename mpl::second<increment_type>::type r;

        /* return */
        return sum_op(iexp.template at<imap>(),
                      sum<D,O,i,r>::template apply<IMAP, ISUM>(iexp));
      }
    };




    /* partial specialization, end the iterative call */
    template <typename D, typename O, typename I>
    struct sum<D,O,I,mpl::true_>
    {
      template <typename IMAP, typename ISUM, typename IEXP>
      static mpl::na apply(IEXP const &) { return mpl::na(); }
    };

  }
}

#endif /* AMA_TENSOR_IEXP_SUM_HPP */
