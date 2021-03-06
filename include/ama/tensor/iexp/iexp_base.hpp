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

#ifndef AMA_TENSOR_IEXP_IEXP_BASE_HPP
#define AMA_TENSOR_IEXP_IEXP_BASE_HPP 1

#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/size.hpp>

namespace ama
{
  namespace tensor_
  {

    namespace mpl = ::boost::mpl;

    /* this class is needed to retrieve the information of DERIVED type */
    template <typename T> struct iexp_traits;

    /*
     * This class is the base for every class that represent a tensor, it uses
     * the CRTP to implement the static polymorphism. The previous traits need
     * to access to the property of tensor:
     *   - value_type, the scalar type used to represent the numbers
     *   - dimension, the dimension of tensor
     *   - order, the order (or rank) of tensor
     *
     * Moreover this class is only for internal purpose, the developers can use
     * that class to implement new tensors. The end user can ignore this class.
     */
    template <typename DERIVED>
    class iexp_base
    {
    protected:
      /* the foundamental types for CRTP */
      typedef iexp_base<DERIVED> base_type;
      typedef DERIVED derived_type;

    public:
      /* the type retrieved through the tensor_traits */
      typedef typename iexp_traits<DERIVED>::value_type value_type;

      typedef typename iexp_traits<DERIVED>::dimension_type dimension_type;

      typedef typename iexp_traits<DERIVED>::controvariant_list controvariant_list;
      typedef typename iexp_traits<DERIVED>::covariant_list covariant_list;

      typedef typename mpl::fold< covariant_list, controvariant_list, mpl::push_back<mpl::_1, mpl::_2> >::type index_list;

      typedef mpl::size<controvariant_list> controvariant_type;
      typedef mpl::size<covariant_list> covariant_type;

      typedef typename ::boost::mpl::plus<controvariant_type,covariant_type>::type order_type;

      typedef typename iexp_traits<DERIVED>::is_assignable is_assignable;

    public:
      /* cast the object to the base class */
      base_type & base() { return *static_cast<base_type *>(this); }
      base_type const & base() const { return *static_cast<base_type const *>(this); }

    public:
      /* cast the object to the derived class */
      derived_type & derived() { return *static_cast<derived_type *>(this); }
      derived_type const & derived() const { return *static_cast<derived_type const *>(this); }
    };

  }
}

#endif /* AMA_TENSOR_IEXP_IEXP_BASE_HPP */
