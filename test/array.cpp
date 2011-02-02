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

#include <ama/common/array.hpp>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ama_array

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(constructor)
{
  ama::array<int,2> a1;
  ama::array<int,2> a2(3);
  ama::array<int,2> a3(a2);

  BOOST_CHECK_EQUAL(a1.at(0), 0);
  BOOST_CHECK_EQUAL(a1.at(1), 0);

  BOOST_CHECK_EQUAL(a2.at(0), 3);
  BOOST_CHECK_EQUAL(a2.at(1), 3);

  BOOST_CHECK_EQUAL(a3.at(0), 3);
  BOOST_CHECK_EQUAL(a3.at(1), 3);
}


BOOST_AUTO_TEST_CASE(copy)
{
  ama::array<int,2> a1(3);
  ama::array<int,2> a2;

  a2 = a1;

  BOOST_CHECK_EQUAL(a1.at(0), a2.at(0));
  BOOST_CHECK_EQUAL(a1.at(1), a2.at(0));
}


BOOST_AUTO_TEST_CASE(iterator_constructor)
{
  int v[] = {1, 2};
  ama::array<int,2> a1(v+0, v+2);

  BOOST_CHECK_EQUAL(a1.at(0), 1);
  BOOST_CHECK_EQUAL(a1.at(1), 2);
}

BOOST_AUTO_TEST_CASE(get_access)
{
  ama::array<int,3> a1;

  ama::get<0>(a1) = 0;
  ama::get<1>(a1) = 1;
  ama::get<2>(a1) = 2;

  BOOST_CHECK_EQUAL(a1.at(0), 0);
  BOOST_CHECK_EQUAL(a1.at(1), 1);
  BOOST_CHECK_EQUAL(a1.at(2), 2);
}
