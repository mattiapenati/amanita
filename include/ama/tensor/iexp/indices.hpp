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

#ifndef AMA_TENSOR_IEPX_INDICES_HPP
#define AMA_TENSOR_IEPX_INDICES_HPP 1

#include <boost/mpl/contains.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/vector/vector0.hpp>

namespace ama
{
  /* forward declaration */
  template <typename T, size_t D, size_t CT, size_t CO> class tensor;
}

namespace ama
{
  namespace tensor_
  {

    /* retrieve the controvariant indices */
    template <typename TENSOR, typename ILIST>
    struct controvariant:
        mpl::fold<
              mpl::iterator_range<
                    typename mpl::begin<ILIST>::type
                  , typename mpl::advance<
                          typename mpl::begin<ILIST>::type
                        , typename TENSOR::controvariant_type
                        >::type
                  >
            , mpl::vector0<>
            , mpl::push_back<mpl::_1, mpl::_2>
            > { };




    /* retrieve the covariant indices */
    template <typename TENSOR, typename ILIST>
    struct covariant:
        mpl::fold<
              mpl::iterator_range<
                    typename mpl::advance<
                          typename mpl::begin<ILIST>::type
                        , typename TENSOR::controvariant_type
                        >::type
                  , typename mpl::end<ILIST>::type
                  >
            , mpl::vector0<>
            , mpl::push_back<mpl::_1, mpl::_2>
            > { };




    /* reduce the indices */
    template <typename CTLIST, typename COLIST>
    struct reduce
    {
      typedef typename mpl::fold<
            CTLIST
          , mpl::vector0<>
          , mpl::if_<
                  mpl::contains<COLIST, mpl::_2>
                , mpl::_1
                , mpl::push_back<mpl::_1, mpl::_2>
                >
          >::type controvariant;

      typedef typename mpl::fold<
            COLIST
          , mpl::vector0<>
          , mpl::if_<
                  mpl::contains<CTLIST, mpl::_2>
                , mpl::_1
                , mpl::push_back<mpl::_1, mpl::_2>
                >
          >::type covariant;
    };




    /* given the tensor and the list compute the reduced */
    template <typename TENSOR, typename ILIST>
    struct iexp_reduce
    {
      typedef typename controvariant<TENSOR, ILIST>::type controvariant_;
      typedef typename covariant<TENSOR, ILIST>::type covariant_;

      typedef reduce<controvariant_, covariant_> reduce_type;

      typedef typename reduce_type::controvariant controvariant;
      typedef typename reduce_type::covariant covariant;

      typedef typename mpl::fold<covariant, controvariant, mpl::push_back<mpl::_1, mpl::_2> >::type index_list;

      typedef typename mpl::fold<
            controvariant_
          , mpl::vector0<>
          , mpl::if_<
                  mpl::contains<covariant_, mpl::_2>
                , mpl::push_back<mpl::_1, mpl::_2>
                , mpl::_1
                >
          >::type reduce_list;

      typedef typename TENSOR::value_type value_type;
      typedef typename TENSOR::dimension_type dimension_type;
      typedef typename mpl::size<controvariant>::type controvariant_type;
      typedef typename mpl::size<covariant>::type covariant_type;

      typedef tensor<
            value_type
          , dimension_type::value
          , controvariant_type::value
          , covariant_type::value
          > tensor_type;
    };

  }
}

#endif /* AMA_TENSOR_IEPX_INDICES_HPP */
