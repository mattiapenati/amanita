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

#ifndef AMA_TENSOR_IEXP_IEXP_TEMPORARY_HPP
#define AMA_TENSOR_IEXP_IEXP_TEMPORARY_HPP 1

#include <ama/tensor/detail/tensor_base.hpp>
#include <ama/tensor/iexp/index_reorder.hpp>
#include <ama/tensor/iexp/iexp_base.hpp>
#include <ama/tensor/iexp/is_same_iexp.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

namespace ama
{
  namespace tensor_
  {

    /* forward declaration */
    template <
          typename TENSOR /* the tensor indixed */
        , typename CTLIST /* the controvariant list */
        , typename COLIST /* the covariant list */
        > class iexp_temporary;


    /* specialization of iexp_traits */
    template <typename TENSOR, typename CTLIST, typename COLIST>
    struct iexp_traits < iexp_temporary<TENSOR, CTLIST, COLIST> >
    {
      typedef typename TENSOR::value_type value_type;

      typedef typename TENSOR::dimension_type dimension_type;

      typedef CTLIST controvariant_list;
      typedef COLIST covariant_list;

      typedef ::boost::mpl::false_ is_assignable;
    };


    /* class declaration */
    template <
          typename TENSOR
        , typename CTLIST
        , typename COLIST
        >
    class iexp_temporary:
      public iexp_base< iexp_temporary<TENSOR, CTLIST, COLIST> >
    {
    protected:
      typedef iexp_base< iexp_temporary<TENSOR, CTLIST, COLIST> > base_type;
      typedef iexp_temporary<TENSOR, CTLIST, COLIST> derived_type;

    public:
      typedef typename base_type::value_type value_type;
      typedef typename base_type::index_list index_list;

      typedef typename base_type::controvariant_type controvariant_type;
      typedef typename base_type::covariant_type covariant_type;

    protected:
      typedef TENSOR tensor_type;

    public:
      /* constructor */
      explicit
      iexp_temporary(tensor_type const & t)
          : m_t(t)
      {
        BOOST_MPL_ASSERT_MSG(
              (mpl::and_<
                     mpl::equal_to<controvariant_type, typename tensor_type::controvariant_type>
                   , mpl::equal_to<covariant_type, typename tensor_type::covariant_type>
                   >::value)
            , THE_TENSOR_MUST_HAVE_THE_SAME_INDICES_LIST_OF_EXPRESSION
            , (CTLIST, COLIST));
      }

      template <typename DERIVED>
      explicit
      iexp_temporary(tensor_base<DERIVED> const & t)
          : m_t(t)
      {
        BOOST_MPL_ASSERT_MSG(
              (mpl::and_<
                     mpl::equal_to<controvariant_type, typename DERIVED::controvariant_type>
                   , mpl::equal_to<covariant_type, typename DERIVED::covariant_type>
                   >::value)
            , THE_TENSOR_MUST_HAVE_THE_SAME_INDICES_LIST_OF_EXPRESSION
            , (CTLIST, COLIST));
      }

    public:
      /* retrieve the value */
      template <typename IMAP>
      value_type at() const
      {
        typedef typename index_reorder<IMAP, index_list>::type ilist;

        return m_t.template at<ilist>();
      }

    protected:
      tensor_type const m_t;
    };

  }
}

#endif /* AMA_TENSOR_IEXP_IEXP_TEMPORARY_HPP */
