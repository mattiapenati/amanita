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

#ifndef AMA_TENSOR_IEXP_IEXP_MUTABLE_HPP
#define AMA_TENSOR_IEXP_IEXP_MUTABLE_HPP 1

#include <ama/tensor/iexp/index_reorder.hpp>
#include <ama/tensor/iexp/iexp_base.hpp>
#include <ama/tensor/iexp/iexp_copy.hpp>
#include <boost/mpl/bool.hpp>

namespace ama
{
  namespace tensor_
  {

    /* forward declaration */
    template <typename TENSOR, typename ILIST> class iexp_mutable;


    /* specialization of iexp_traits */
    template <typename TENSOR, typename ILIST>
    struct iexp_traits < iexp_mutable<TENSOR, ILIST> >
    {
      typedef typename TENSOR::value_type value_type;

      typedef typename TENSOR::dimension_type dimension_type;

      typedef typename TENSOR::controvariant_type controvariant_type;
      typedef typename TENSOR::covariant_type covariant_type;

      typedef ILIST index_list;

      typedef ::boost::mpl::true_ is_assignable;
    };


    /* class declaration */
    template <typename TENSOR, typename ILIST>
    class iexp_mutable:
      public iexp_base< iexp_mutable<TENSOR, ILIST> >
    {
    protected:
      typedef iexp_base< iexp_mutable<TENSOR, ILIST> > base_type;
      typedef iexp_mutable<TENSOR, ILIST> derived_type;

    public:
      typedef typename base_type::value_type value_type;

      typedef typename base_type::dimension_type dimension_type;
      typedef typename base_type::order_type order_type;

    protected:
      typedef TENSOR tensor_type;

    public:
      /* constructor */
      explicit iexp_mutable(tensor_type & t): m_t(t) { }

    public:
      /* retrieve the value */
      template <typename IMAP>
      value_type & at()
      {
        typedef typename index_reorder<IMAP, ILIST>::type ilist;
        return m_t.template at<ilist>();
      }

      template <typename IMAP>
      value_type at() const
      {
        typedef typename index_reorder<IMAP, ILIST>::type ilist;
        return m_t.template at<ilist>();
      }

    public:
      /* copy an expression */
      iexp_mutable &
      operator=(iexp_mutable const & ie)
      {
        iexp_copy<dimension_type,order_type>::apply(ie, *this);
        return *this;
      }

      /* copy an expression */
      template <typename DERIVED>
      iexp_mutable &
      operator=(iexp_base<DERIVED> const & ie)
      {
        /* TODO implement is_same_iexp */

        iexp_copy<dimension_type,order_type>::apply(ie.derived(), *this);
        return *this;
      }

    protected:
      tensor_type & m_t;
    };

  }
}

#endif /* AMA_TENSOR_IEXP_IEXP_MUTABLE_HPP */
