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

#ifndef AMA_TENSOR_IEXP_IEXP_CWISE_BINARY_HPP
#define AMA_TENSOR_IEXP_IEXP_CWISE_BINARY_HPP 1

#include <ama/tensor/iexp/iexp_base.hpp>
#include <ama/tensor/iexp/is_same_iexp.hpp>
#include <boost/mpl/assert.hpp>

namespace ama
{
  namespace tensor_
  {

    /* this class represent a unary component-wise operation */
    template <typename LEFT, typename RIGHT, typename OPERATOR> class iexp_cwise_binary;


    /* specialization of iexp_traits */
    template <typename LEFT, typename RIGHT, typename OPERATOR>
    struct iexp_traits< iexp_cwise_binary<LEFT, RIGHT, OPERATOR> >
    {
      typedef typename OPERATOR::result_type value_type;

      typedef typename LEFT::dimension_type dimension_type;

      typedef typename LEFT::controvariant_list controvariant_list;
      typedef typename LEFT::covariant_list covariant_list;

      typedef ::boost::mpl::false_ is_assignable;
    };


    /* class declaration */
    template <typename LEFT, typename RIGHT, typename OPERATOR>
    class iexp_cwise_binary:
        public iexp_base< iexp_cwise_binary<LEFT, RIGHT, OPERATOR> >
    {
      BOOST_MPL_ASSERT_MSG(
            (is_same_iexp<LEFT,RIGHT>::value)
          , COMPONENT_WISE_BINARY_OPERATION_BETWEEN_DIFFERENT_EXPRESSION_ARE_NOT_ALLOWED
          , (LEFT, RIGHT));

    protected:
      typedef iexp_base< iexp_cwise_binary<LEFT, RIGHT, OPERATOR> > base_type;
      typedef iexp_cwise_binary<LEFT, RIGHT, OPERATOR> derived_type;

    protected:
      typedef LEFT left_operand_type;
      typedef RIGHT right_operand_type;
      typedef OPERATOR operator_type;

    public:
      typedef typename base_type::value_type value_type;

    public:
      /* constructor */
      iexp_cwise_binary(left_operand_type const & left_operand,
                        right_operand_type const & right_operand,
                        operator_type const & op = operator_type())
          : m_left_operand(left_operand),
            m_right_operand(right_operand),
            m_operator(op) { }

    public:
      /* retrieve the value */
      template <typename IMAP>
      value_type at() const
      {
        return m_operator(
                 m_left_operand.template at<IMAP>(),
                 m_right_operand.template at<IMAP>());
      }

    protected:
      /* members */
      left_operand_type m_left_operand;
      right_operand_type m_right_operand;
      operator_type const m_operator;
    };

  }
}

#endif /* AMA_TENSOR_IEXP_IEXP_CWISE_BINARY_HPP */
