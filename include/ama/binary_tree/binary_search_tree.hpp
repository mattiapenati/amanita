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

#ifndef AMA_BINARY_TREE_BINARY_SEARCH_TREE_HPP
#define AMA_BINARY_TREE_BINARY_SEARCH_TREE_HPP 1

#include <boost/assert.hpp>
#include <ama/binary_tree/detail/binary_tree.hpp>
#include <ama/binary_tree/detail/binary_search_tree_node.hpp>

namespace ama
{

  template <typename VALUE>
  class binary_search_tree:
      public binary_tree_::binary_tree< binary_tree_::binary_search_tree_node<VALUE> >
  {
  public:
    typedef binary_tree_::binary_search_tree_node<VALUE> node_type;
    typedef typename node_type::node_handle node_handle;

    typedef VALUE value_type;

  protected:
    typedef node_type * node_pointer;
    typedef binary_tree_::binary_tree<node_type> base_type;

  public:
    /* insert a new value */
    node_handle insert(value_type const & val)
    {
      node_handle r;

      if(this->root().null())
      {
        this->reset(new node_type(val));
        r = this->root();
      }
      else
        r = this->insert(val, this->root());

      return r;
    }

    /* search for a value and return the relative node handler */
    node_handle search(value_type const & val)
    {
      BOOST_ASSERT(!this->root().null());
      return this->search(val, this->root());
    }

    /* retrieve the node that store the minimum */
    node_handle minimum()
    {
      BOOST_ASSERT(!this->root().null());
      return this->minimum(this->root());
    }

    /* retrieve the node that store the maximum */
    node_handle maximum()
    {
      BOOST_ASSERT(!this->root().null());
      return this->maximum(this->root());
    }

  public:
    /* insert a new value in the tree with root node */
    static node_handle insert(value_type const & val,
                              node_handle const & node)
    {
      node_handle x(node), y;

      while(!x.null())
      {
        y = x;
        x = (val < x->value()) ? x->left() : x->right();
      }

      node_pointer p = new node_type(y, val);
      (val < y->value()) ? y->reset_left(p) : y->reset_right(p);
      return node_handle(p);
    }

    /* search a value in the tree with root node */
    static node_handle search(value_type const & val,
                              node_handle const & node)
    {
      node_handle x = node;

      while(!x.null() and (val != x->value()))
        x = (val < x->value()) ? x->left() : x->right() ;

      return x;
    }

    /* retrieve the minimum of tree */
    static node_handle minimum(node_handle const & node)
    {
      node_handle x(node);
      while(!x->left().null())
        x = x->left();
      return x;
    }

    /* retrieve the maximum of tree */
    static node_handle maximum(node_handle const & node)
    {
      node_handle x(node);
      while(!x->right().null())
        x = x->right();
      return x;
    }

    /* retrieve the successor of tree */
    static node_handle successor(node_handle const & node)
    {
      node_handle x(node), y(node->parent());

      if(!x->right().null())
        return minimum(x->right());

      while(!y.null() and (x == y->right()))
      {
        x = y;
        y = y->parent();
      }

      return y;
    }

    /* retrieve the predecessor of tree */
    static node_handle predecessor(node_handle const & node)
    {
      node_handle x(node), y(node->parent());

      if(!x->left().null())
        return minimum(x->left());

      while(!y.null() and (x == y->left()))
      {
        x = y;
        y = y->parent();
      }

      return y;
    }

  };

}

#endif /* AMA_BINARY_TREE_BINARY_SEARCH_TREE_HPP */
