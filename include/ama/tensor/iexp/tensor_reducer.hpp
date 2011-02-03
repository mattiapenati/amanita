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

#ifndef AMA_TENSOR_IEXP_TENSOR_REDUCER_HPP
#define AMA_TENSOR_IEXP_TENSOR_REDUCER_HPP 1

#include <ama/tensor/detail/tensor_base.hpp>
#include <ama/tensor/iexp/iexp_calculator.hpp>
#include <ama/tensor/iexp/iexp_constant.hpp>
#include <ama/tensor/iexp/sum.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size.hpp>

namespace ama
{
  namespace tensor_
  {

    /* forward declaration */
    template <typename TENSOR, typename ILIST> class tensor_reducer;


    /* specialization of trait */
    template <typename TENSOR, typename ILIST>
    struct tensor_traits< tensor_reducer<TENSOR, ILIST> >
    {
      typedef typename TENSOR::value_type value_type;

      typedef typename repeated_indices<ILIST>::type sum_indeces; /* index of sum */

      typedef typename TENSOR::dimension_type dimension_type;
      typedef ::boost::mpl::size< iexp_controvariant_unique<TENSOR,ILIST> > controvariant_type;
      typedef ::boost::mpl::size< iexp_covariant_unique<TENSOR,ILIST> > covariant_type;

      typedef ::boost::mpl::false_ is_assignable;
      typedef ::boost::mpl::true_ is_temporary;
    };


    /* class definition */
    template <
          typename TENSOR
        , typename ILIST /* the list of all indeces */
        >
    class tensor_reducer:
        public tensor_base< tensor_reducer<TENSOR,ILIST> >
    {
    protected:
      typedef tensor_base< tensor_reducer<TENSOR,ILIST> > base_type;
      typedef tensor_reducer<TENSOR,ILIST> derived_type;

      typedef TENSOR tensor_type;
      typedef iexp_constant<TENSOR, ILIST> iexp_type;

    public:
      typedef typename base_type::value_type value_type;

    public:
      explicit
      tensor_reducer(tensor_type const & t)
          : m_iexp(t) { }

    public:
      template <typename IND>
      value_type at() const
      {
        namespace mpl = ::boost::mpl;

        typedef typename not_repeated_indices<ILIST>::type indeces; /* other indices */
        typedef typename repeated_indices<ILIST>::type sum_indeces; /* index of sum */

        /* TODO check size<IND> == size<indices> */

        /* indeces (not for sum) */
        typedef typename make_imap<indeces, IND>::type imap;

        /* others */
        typedef typename TENSOR::dimension_type dimension;
        typedef typename mpl::size<sum_indeces>::type order;

        return sum<dimension, order>::template apply<imap, sum_indeces>(m_iexp);
      }

    protected:
      iexp_type const m_iexp;
    };

  }
}

#endif /* AMA_TENSOR_IEXP_TENSOR_REDUCER_HPP */
