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

#ifndef AMA_TENSOR_MUL_MUL_CALCULATOR_HPP
#define AMA_TENSOR_MUL_MUL_CALCULATOR_HPP 1

#include <ama/tensor/iexp/iexp_calculator.hpp>
#include <ama/common/size_t.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/size.hpp>

namespace ama
{

  /* forward declaration */
  template <typename S, size_t D, size_t CT, size_t CO> class tensor;

  namespace tensor_
  {

    /* forward declaration*/
    template <typename LEFT, typename RIGHT> class mul_outer;

    namespace mpl = ::boost::mpl;

    /* append two list */
    template <typename I1, typename I2>
    struct list_append:
          mpl::fold<
                I2
              , I1
              , mpl::push_back<mpl::_1, mpl::_2>
              >::type { };

    /* get the covariant and the controvariant part of product */
    template <typename LEFT, typename RIGHT>
    struct mul_outer_index
    {
      /* reconstruct tensor type */
      typedef typename LEFT::value_type value_type;
      typedef typename LEFT::dimension_type dimension_type;

      typedef typename LEFT::controvariant_type left_controvariant_type;
      typedef typename LEFT::covariant_type left_covariant_type;

      typedef typename RIGHT::controvariant_type right_controvariant_type;
      typedef typename RIGHT::covariant_type right_covariant_type;

      typedef tensor<value_type, dimension_type::value, left_controvariant_type::value, left_covariant_type::value> left_tensor;
      typedef tensor<value_type, dimension_type::value, right_controvariant_type::value, right_covariant_type::value> right_tensor;

      /* indices list */
      typedef typename LEFT::index_list left_index_list;
      typedef typename RIGHT::index_list right_index_list;

      /* left controvariant and covariant indices */
      typedef iexp_controvariant<left_tensor, left_index_list> left_controvariant;
      typedef iexp_covariant<left_tensor, left_index_list> left_covariant;

      /* right controvariant and covariant indices */
      typedef iexp_controvariant<right_tensor, right_index_list> right_controvariant;
      typedef iexp_covariant<right_tensor, right_index_list> right_covariant;

      /* the controvariant and covariant indices */
      typedef list_append<left_controvariant, right_controvariant> controvariant;
      typedef list_append<left_covariant, right_covariant> covariant;

      /* the dimension of controvariant and covariant components */
      typedef mpl::size<controvariant> controvariant_type;
      typedef mpl::size<covariant> covariant_type;

      /* the full index list */
      typedef list_append<controvariant, covariant> index_list;

      /* tensor type */
      typedef tensor<value_type, dimension_type::value, controvariant_type::value, covariant_type::value> tensor_type;
    };

    template <typename LEFT, typename RIGHT>
    struct mul_calculator:
          mpl::if_<
                has_repeated_indices<typename mul_outer_index<LEFT, RIGHT>::index_list>
              , mpl::if_<
                      all_repeated_indices<typename mul_outer_index<LEFT, RIGHT>::index_list>
                    , typename LEFT::value_type
                    , iexp_temporary<
                            typename iexp_reduced_tensor<
                                  typename mul_outer_index<LEFT, RIGHT>::tensor_type
                                , typename mul_outer_index<LEFT, RIGHT>::index_list
                                >::type
                          , typename not_repeated_indices<typename mul_outer_index<LEFT, RIGHT>::index_list>::type
                          >
                    >
              , mul_outer<LEFT, RIGHT>
              >
    {
      /* TODO check indices */
    };

  }
}

#endif /* AMA_TENSOR_MUL_MUL_CALCULATOR_HPP */
