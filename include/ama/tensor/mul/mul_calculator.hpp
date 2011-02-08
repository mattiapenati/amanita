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

#ifndef AMA_TENSOR_MUL_MUL_CALCULATOR_HPP
#define AMA_TENSOR_MUL_MUL_CALCULATOR_HPP 1

#include <ama/tensor/iexp/iexp_calculator.hpp>
#include <ama/tensor/iexp/indices.hpp>
#include <ama/common/size_t.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/size.hpp>

/* forward declaration */
namespace ama
{
  template <typename S, size_t D, size_t CT, size_t CO> class tensor;
  namespace tensor_
  {
    template <typename LEFT, typename RIGHT> class mul_outer;
  }
}




namespace ama
{
  namespace tensor_
  {

    namespace mpl = ::boost::mpl;

    /* get the covariant and the controvariant part of product */
    template <typename LEFT, typename RIGHT>
    struct mul_index
    {
      /* the controvariant and covariant indices */
      typedef typename mpl::fold<
            typename RIGHT::controvariant_list
          , typename LEFT::controvariant_list
          , mpl::push_back<mpl::_1, mpl::_2>
          >::type controvariant_list;
      typedef typename mpl::fold<
            typename RIGHT::covariant_list
          , typename LEFT::covariant_list
          , mpl::push_back<mpl::_1, mpl::_2>
          >::type covariant_list;

      /* the dimension of controvariant and covariant components */
      typedef mpl::size<controvariant_list> controvariant_type;
      typedef mpl::size<covariant_list> covariant_type;

      /* the full index list */
      typedef typename mpl::fold<
            covariant_list
          , controvariant_list
          , mpl::push_back<mpl::_1, mpl::_2>
          >::type index_list;

      /* tensor type */
      typedef typename LEFT::value_type value_type;
      typedef typename LEFT::dimension_type dimension_type;
      typedef tensor<
            value_type
          , dimension_type::value
          , controvariant_type::value
          , covariant_type::value
          > tensor_type;
    };

    template <typename LEFT, typename RIGHT>
    struct mul_calculator:
          mpl::if_<
                has_repeated_indices<typename mul_index<LEFT, RIGHT>::index_list>
              , typename mpl::if_<
                      all_repeated_indices<typename mul_index<LEFT, RIGHT>::index_list>
                    , typename LEFT::value_type
                    , iexp_temporary<
                            typename iexp_reduce<
                                  typename mul_index<LEFT, RIGHT>::tensor_type
                                , typename mul_index<LEFT, RIGHT>::index_list
                                >::tensor_type
                          , typename iexp_reduce<
                                  typename mul_index<LEFT, RIGHT>::tensor_type
                                , typename mul_index<LEFT, RIGHT>::index_list
                                >::controvariant
                          , typename iexp_reduce<
                                  typename mul_index<LEFT, RIGHT>::tensor_type
                                , typename mul_index<LEFT, RIGHT>::index_list
                                >::covariant
                          >
                    >::type
              , mul_outer<LEFT, RIGHT>
              >
    {
      /* TODO check indices the repeated indices must be in different part */
    };

  }
}

#endif /* AMA_TENSOR_MUL_MUL_CALCULATOR_HPP */
