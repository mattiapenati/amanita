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

#ifndef AMA_TENSOR_DETAIL_TENSOR_OUTER_HPP
#define AMA_TENSOR_DETAIL_TENSOR_OUTER_HPP 1

#include <ama/tensor/detail/tensor_base.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/vector/vector0_c.hpp>

namespace ama
{
  namespace tensor_
  {

    /* forward declaration*/
    template <typename LEFT, typename RIGHT> class tensor_outer;


    /* traits definition */
    template <typename LEFT, typename RIGHT>
    struct tensor_traits< tensor_outer<LEFT, RIGHT> >
    {
      typedef typename LEFT::value_type value_type;

      typedef typename LEFT::dimension_type dimension_type;

      typedef typename ::boost::mpl::plus<
                             typename LEFT::controvariant_type
                           , typename RIGHT::controvariant_type
                           >::type controvariant_type;
      typedef typename ::boost::mpl::plus<
                             typename LEFT::covariant_type
                           , typename RIGHT::covariant_type
                           >::type covariant_type;

      typedef ::boost::mpl::false_ is_assignable;
      typedef ::boost::mpl::true_ is_temporary;
    };


    /* class declaration */
    template <typename LEFT, typename RIGHT>
    class tensor_outer:
        public tensor_base< tensor_outer<LEFT, RIGHT> >
    {
    protected:
      typedef tensor_base< tensor_outer<LEFT, RIGHT> > base_type;
      typedef tensor_outer<LEFT, RIGHT> derived_type;

    protected:
      typedef LEFT left_operand_type;
      typedef RIGHT right_operand_type;

    public:
      typedef typename base_type::value_type value_type;

    public:
      /* costructor */
      tensor_outer(left_operand_type const & left,
                   right_operand_type const & right)
          : m_left(left),
            m_right(right) { }

    public:
      /* retrieve the value */
      template <typename ILIST>
      value_type at() const
      {
        namespace mpl = ::boost::mpl;

        /* iterator */
        typedef typename mpl::begin<ILIST>::type begin1;
        typedef typename mpl::advance<begin1, typename LEFT::controvariant_type>::type begin2;
        typedef typename mpl::advance<begin2, typename RIGHT::controvariant_type>::type begin3;
        typedef typename mpl::advance<begin3, typename LEFT::covariant_type>::type begin4;
        typedef typename mpl::advance<begin4, typename RIGHT::covariant_type>::type begin5;
        typedef typename mpl::end<ILIST>::type end;

        /* check for no errors in the code */
        BOOST_MPL_ASSERT((mpl::equal_to<mpl::distance<end,begin5>,mpl::size_t<0> >));

        /* split multi-index */
        typedef typename mpl::fold<
              mpl::iterator_range<begin1, begin2>
            , mpl::vector0_c<size_t>
            , mpl::push_back<mpl::_1, mpl::_2>
            >::type controvariant_left;

        typedef typename mpl::fold<
              mpl::iterator_range<begin2, begin3>
            , mpl::vector0_c<size_t>
            , mpl::push_back<mpl::_1, mpl::_2>
            >::type controvariant_right;

        typedef typename mpl::fold<
              mpl::iterator_range<begin3, begin4>
            , mpl::vector0_c<size_t>
            , mpl::push_back<mpl::_1, mpl::_2>
            >::type covariant_left;

        typedef typename mpl::fold<
              mpl::iterator_range<begin4, begin5>
            , mpl::vector0_c<size_t>
            , mpl::push_back<mpl::_1, mpl::_2>
            >::type covariant_right;

        /* append the splittend multi-index */
        typedef typename mpl::fold<
              covariant_left
            , controvariant_left
            , mpl::push_back<mpl::_1, mpl::_2>
            >::type left_ilist;

        typedef typename mpl::fold<
              covariant_right
            , controvariant_right
            , mpl::push_back<mpl::_1, mpl::_2>
            >::type right_ilist;

        return (m_left.template at<left_ilist>()) *
            (m_right.template at<right_ilist>());
      }

    protected:
      /* if the operand is temporary we save a copy, otherwise a reference */
      typedef typename LEFT::is_temporary left_operand_is_temporary;
      typedef typename ::boost::mpl::if_<
            left_operand_is_temporary
          , left_operand_type const
          , left_operand_type const &
          >::type const_left_operand_type;

      /* if the operand is temporary we save a copy, otherwise a reference */
      typedef typename RIGHT::is_temporary right_operand_is_temporary;
      typedef typename ::boost::mpl::if_<
            right_operand_is_temporary
          , right_operand_type const
          , right_operand_type const &
          >::type const_right_operand_type;

      /* members */
      const_left_operand_type m_left;
      const_right_operand_type m_right;
    };

  }
}

#endif /* AMA_TENSOR_DETAIL_TENSOR_OUTER_HPP */
