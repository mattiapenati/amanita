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

#ifndef AMA_TENSOR_MUL_IEXP_OUTER_HPP
#define AMA_TENSOR_MUL_IEXP_OUTER_HPP 1

#include <ama/tensor/iexp/index_reorder.hpp>
#include <ama/tensor/iexp/iexp_base.hpp>
#include <ama/tensor/mul/mul_calculator.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/plus.hpp>

namespace ama
{
  namespace tensor_
  {

    /* forward declaration*/
    template <typename LEFT, typename RIGHT> class mul_outer;


    /* traits definition */
    template <typename LEFT, typename RIGHT>
    struct iexp_traits< mul_outer<LEFT, RIGHT> >
    {
      typedef typename LEFT::value_type value_type;

      typedef typename LEFT::dimension_type dimension_type;

      typedef typename mul_index<LEFT, RIGHT>::controvariant_list controvariant_list;
      typedef typename mul_index<LEFT, RIGHT>::covariant_list covariant_list;

      typedef ::boost::mpl::false_ is_assignable;
    };


    /* class declaration */
    template <typename LEFT, typename RIGHT>
    class mul_outer:
        public iexp_base< mul_outer<LEFT, RIGHT> >
    {
    protected:
      typedef iexp_base< mul_outer<LEFT, RIGHT> > base_type;
      typedef mul_outer<LEFT, RIGHT> derived_type;

    protected:
      typedef LEFT left_operand_type;
      typedef RIGHT right_operand_type;

    public:
      typedef typename base_type::value_type value_type;

    public:
      /* costructor */
      mul_outer(left_operand_type const & left,
                 right_operand_type const & right)
          : m_left(left),
            m_right(right) { }

    public:
      /* retrieve the value */
      template <typename IMAP>
      value_type at() const
      {
        return (m_left.template at<IMAP>()) * (m_right.template at<IMAP>());
      }

    protected:
      /* members */
      left_operand_type const m_left;
      right_operand_type const m_right;
    };

  }
}

#endif /* AMA_TENSOR_MUL_IEXP_OUTER_HPP */
