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

#ifndef AMA_BINARY_TREE_DETAIL_BINARY_SEARCH_TREE_NODE_HPP
#define AMA_BINARY_TREE_DETAIL_BINARY_SEARCH_TREE_NODE_HPP 1

#include <ama/binary_tree/detail/binary_tree_node.hpp>

namespace ama
{
  namespace binary_tree_
  {

    template <typename VALUE>
    class binary_search_tree_node:
        public binary_tree_node< binary_search_tree_node<VALUE> >
    {
    public:
      typedef VALUE value_type;

    protected:
      typedef binary_tree_node< binary_search_tree_node<VALUE> > base_type;

    public:
      typedef typename base_type::node_handle node_handle;

    public:
      binary_search_tree_node(value_type const & val = value_type()):
          base_type()
        , m_val(val) { }

      binary_search_tree_node(binary_search_tree_node * parent,
                              value_type const & val = value_type()):
          base_type(parent)
        , m_val(val) { }

      binary_search_tree_node(node_handle const & parent,
                              value_type const & val = value_type()):
          base_type(parent.get())
        , m_val(val) { }

    public:
      value_type & value() { return m_val; }
      value_type const & value() const { return m_val; }

    protected:
      value_type m_val;
    };

  }
}

#endif /* AMA_BINARY_TREE_DETAIL_BINARY_SEARCH_TREE_NODE_HPP */
