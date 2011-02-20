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

#ifndef AMA_BINARY_TREE_DETAIL_BINARY_TREE_NODE_HPP
#define AMA_BINARY_TREE_DETAIL_BINARY_TREE_NODE_HPP 1

#include <boost/scoped_ptr.hpp>
#include <ama/common/pointer_wrapper.hpp>

namespace ama
{
  namespace binary_tree_
  {

    /* This is a basic type for a binary tree's node, it use the CRTP to store
     * the child nodes and the parent node. */
    template <typename DERIVED>
    class binary_tree_node
    {
    protected:
      typedef DERIVED * pointer;
      typedef DERIVED const * const_pointer;

      typedef boost::scoped_ptr<DERIVED> smart_pointer;

    public:
      typedef ::ama::pointer_wrapper<DERIVED> node_handle;

    protected:
      binary_tree_node(pointer parent = 0):
          m_parent(parent)
        , m_left()
        , m_right() { }

      binary_tree_node(pointer parent,
                       pointer left,
                       pointer right):
          m_parent(parent)
        , m_left(left)
        , m_right(right) { }

    public:
      node_handle parent() const { return node_handle(m_parent); }
      node_handle left() const { return node_handle(m_left.get()); }
      node_handle right() const { return node_handle(m_right.get()); }

    public:
      void set_parent(pointer parent) { m_parent = parent; }

      void reset_left(pointer left) { m_left.reset(left); }
      void reset_right(pointer right) { m_right.reset(right); }

      void swap_left(smart_pointer & left) { m_left.swap(left); }
      void swap_right(smart_pointer & right) { right.swap(right); }

    private:
      /* The parent node */
      pointer m_parent; /* is a pointer and not a smart pointer becuase it must
                         * be destructed by its own parent, it's used as a
                         * reference to the parent */

      /* The two child nodes */
      smart_pointer m_left;
      smart_pointer m_right;
    };

  }
}

#endif /* AMA_BINARY_TREE_DETAIL_BINARY_TREE_NODE_HPP */
