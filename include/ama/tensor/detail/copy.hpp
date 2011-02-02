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

#ifndef AMA_TENSOR_DETAIL_COPY_HPP
#define AMA_TENSOR_DETAIL_COPY_HPP 1

#include <boost/mpl/bool.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/modulus.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/vector/vector0_c.hpp>

namespace ama
{
  namespace tensor_
  {

    namespace mpl = ::boost::mpl;


    /* given the order this struct create the first index */
    template <typename O>
    struct first:
        mpl::fold<
              mpl::range_c<size_t, 0, O::value>
            , mpl::vector0_c<size_t>
            , mpl::push_back< mpl::_1 , mpl::size_t<0> >
            >::type { };

     /* increment the multi-index */
     template <
           typename D /* the dimension */
         , typename I /* the multi-index */
         >
     struct increment:
         mpl::fold<
               I
             , mpl::pair<                  /* a pair with:           */
                   mpl::vector0_c<size_t>  /*  - the multi-index     */
                 , mpl::true_              /*  - an the carry of sum */
                 >
             , mpl::pair<
                   mpl::push_back<
                       mpl::first<mpl::_1>
                     , mpl::modulus<
                           mpl::if_<
                               mpl::second<mpl::_1>
                             , mpl::next<mpl::_2>
                             , mpl::_2
                             >
                         , D
                         >
                     >
                 , mpl::equal_to<
                       mpl::if_<
                           mpl::second<mpl::_1>
                         , mpl::next<mpl::_2>
                         , mpl::_2
                         >
                     , D
                     >
                 >
             > { };


     /* this struct implement the copy */
     template <
           typename D               /* the dimensione of tensor */
         , typename O               /* the order of tensor */
         , typename I = first<O>    /* the first multi-index */
         , typename R = mpl::false_ /* this type is true for the last multi-index */
         >
     struct copy
     {
       template <typename SRC, typename DST>
       static void apply(SRC const & src, DST & dst)
       {
         dst.template at<I>() = src.template at<I>();

         /* increment the multi-index */
         typedef typename increment<D,I>::type increment_type;

         /* the first is the multi-index incremented */
         typedef typename mpl::first<increment_type>::type i;
         /* the second is a boolean flag toidentify the last multi-index */
         typedef typename mpl::second<increment_type>::type r;

         /* iterative call */
         copy<D,O,i,r>::apply(src,dst);
       }
     };


     /* partial specialization, end the iterative call */
     template <typename D, typename O, typename I>
     struct copy<D,O,I,mpl::true_>
     {
       template <typename SRC, typename DST>
       static void apply(SRC const &, DST &) { }
     };

  }
}

#endif /* AMA_TENSOR_DETAIL_COPY_HPP */
