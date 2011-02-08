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

#ifndef AMA_TENSOR_MUL_MUL_REDUCER_HPP
#define AMA_TENSOR_MUL_MUL_REDUCER_HPP 1

#include <ama/tensor/detail/tensor_base.hpp>
#include <ama/tensor/mul/mul_calculator.hpp>
#include <ama/tensor/mul/mul_temporary.hpp>
#include <ama/tensor/iexp/iexp_copy.hpp>
#include <ama/tensor/iexp/indices.hpp>
#include <ama/tensor/iexp/sum.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/size.hpp>

namespace ama
{
  namespace tensor_
  {

    /* forward declaration */
    template <typename LEFT, typename RIGHT> class mul_reducer;


    /* specialization of traits */
    template <typename LEFT, typename RIGHT>
    struct tensor_traits< mul_reducer<LEFT, RIGHT> >
    {
      typedef typename LEFT::value_type value_type;

      typedef typename LEFT::dimension_type dimension_type;

      typedef mpl::size<typename iexp_reduce<
            typename mul_index<LEFT, RIGHT>::tensor_type
          , typename mul_index<LEFT, RIGHT>::index_list
          >::controvariant> controvariant_type;
      typedef mpl::size<typename iexp_reduce<
            typename mul_index<LEFT, RIGHT>::tensor_type
          , typename mul_index<LEFT, RIGHT>::index_list
          >::covariant> covariant_type;

      typedef ::boost::mpl::false_ is_assignable;
      typedef ::boost::mpl::true_ is_temporary;
    };


    /* class declaration */
    template <typename LEFT, typename RIGHT>
    class mul_reducer:
          public tensor_base< mul_reducer<LEFT, RIGHT> >
    {
    protected:
      typedef tensor_base< mul_reducer<LEFT, RIGHT> > base_type;
      typedef mul_reducer<LEFT, RIGHT> derived_type;

      typedef LEFT left_operand;
      typedef RIGHT right_operand;

      typedef mul_temporary<left_operand, right_operand> iexp_type;

    public:
      /* constructor */
      mul_reducer(left_operand const & left,
                  right_operand const & right)
          : m_iexp(left, right) { }

    public:
      typedef typename base_type::value_type value_type;
      typedef typename base_type::dimension_type dimension_type;

      template <typename ILIST>
      value_type at() const
      {
        namespace mpl = ::boost::mpl;

        typedef typename iexp_reduce<
              typename mul_index<LEFT, RIGHT>::tensor_type
            , typename mul_index<LEFT, RIGHT>::index_list
            >::index_list index_list; /* other indices */
        typedef typename iexp_reduce<
              typename mul_index<LEFT, RIGHT>::tensor_type
            , typename mul_index<LEFT, RIGHT>::index_list
            >::reduce_list sum_indices; /* index of sum */

        BOOST_MPL_ASSERT_MSG(
              (mpl::equal_to< mpl::size<ILIST> , mpl::size<index_list> >::value)
            , THE_INDICES_LIST_MUST_HAVE_THE_SAME_SIZE
            , (ILIST));

        /* indeces (not for sum) */
        typedef typename make_imap<index_list, ILIST>::type imap;
        typedef typename mpl::size<sum_indices>::type order;

        return sum<dimension_type, order>::template apply<imap, sum_indices>(m_iexp);
      }

    protected:
      iexp_type const m_iexp;
    };

  }
}

#endif /* AMA_TENSOR_MUL_MUL_REDUCER_HPP */
