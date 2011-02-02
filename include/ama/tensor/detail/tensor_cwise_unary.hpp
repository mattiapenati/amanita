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

#ifndef AMA_TENSOR_DETAIL_TENSOR_CWISE_UNARY_HPP
#define AMA_TENSOR_DETAIL_TENSOR_CWISE_UNARY_HPP 1

#include <ama/tensor/detail/tensor_base.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

namespace ama
{
  namespace tensor_
  {

    /* this class representa a unary component-wise operation */
    template <typename OPERAND, typename OPERATOR> class tensor_cwise_unary;


    /* specialization of tensor_traits */
    template <typename OPERAND, typename OPERATOR>
    struct tensor_traits< tensor_cwise_unary<OPERAND, OPERATOR> >
    {
      typedef typename OPERATOR::result_type value_type;

      typedef typename OPERAND::dimension_type dimension_type;

      typedef typename OPERAND::controvariant_type controvariant_type;
      typedef typename OPERAND::covariant_type covariant_type;

      typedef ::boost::mpl::false_ is_assignable;
      typedef ::boost::mpl::true_ is_temporary;
    };


    /* class declaration */
    template <typename OPERAND, typename OPERATOR>
    class tensor_cwise_unary:
        public tensor_base< tensor_cwise_unary<OPERAND, OPERATOR> >
    {
    protected:
      typedef tensor_base< tensor_cwise_unary<OPERAND, OPERATOR> > base_type;
      typedef tensor_cwise_unary<OPERAND, OPERATOR> derived_type;

    protected:
      typedef OPERAND operand_type;
      typedef OPERATOR operator_type;

    public:
      typedef typename base_type::value_type value_type;

    public:
      /* constructor */
      explicit
      tensor_cwise_unary(operand_type const & operand,
                         operator_type const & op = operator_type())
          : m_operand(operand),
            m_operator(op) { }

    public:
      /* retrieve the value */
      template <typename ILIST>
      value_type at() const { return m_operator(m_operand.template at<ILIST>()); }

    protected:
      /* if the operand is temporary we save a copy, otherwise a reference */
      typedef typename OPERAND::is_temporary operand_is_temporary;
      typedef typename ::boost::mpl::if_<
            operand_is_temporary
          , operand_type const
          , operand_type const &
          >::type const_operand_type;

      /* members */
      const_operand_type m_operand;
      operator_type const m_operator;
    };

  }
}

#endif /* AMA_TENSOR_DETAIL_TENSOR_CWISE_UNARY_HPP */
