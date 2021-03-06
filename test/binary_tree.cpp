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

#include <ama/binary_tree.hpp>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ama_array

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(bst_constructor)
{
  ama::binary_search_tree<int> tree;
}

BOOST_AUTO_TEST_CASE(bst_inserter)
{
  typedef ama::binary_search_tree<int> tree_t;

  tree_t tree;

  tree_t::node_handle n1 = tree.insert(5);
  tree_t::node_handle n2 = tree.insert(2);
  tree_t::node_handle n3 = tree.insert(7);

  BOOST_CHECK_EQUAL(n1->value(), 5);
  BOOST_CHECK_EQUAL(n1->left()->value(), 2);
  BOOST_CHECK_EQUAL(n1->right()->value(), 7);

  BOOST_CHECK_EQUAL(n2->value(), 2);
  BOOST_CHECK_EQUAL(n3->value(), 7);
}

BOOST_AUTO_TEST_CASE(bst_search)
{
  typedef ama::binary_search_tree<int> tree_t;

  tree_t tree;

  tree_t::node_handle n1 = tree.insert(5);
  tree_t::node_handle n2 = tree.insert(2);
  tree_t::node_handle n3 = tree.insert(7);

  BOOST_CHECK_EQUAL(n1->value(), 5);
  BOOST_CHECK_EQUAL(n1->left()->value(), 2);
  BOOST_CHECK_EQUAL(n1->right()->value(), 7);

  BOOST_CHECK_EQUAL(n2->value(), 2);
  BOOST_CHECK_EQUAL(n3->value(), 7);

  tree_t::node_handle s1 = tree.search(2);
  tree_t::node_handle s2 = tree.search(3);

  BOOST_CHECK_EQUAL(s1->value(), 2);
  BOOST_CHECK(s2.null());
}
