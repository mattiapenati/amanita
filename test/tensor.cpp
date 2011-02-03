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

#include <ama/tensor.hpp>
#include <boost/mpl/vector.hpp>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ama_tensor

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(constructor)
{
  ama::tensor<float, 2, 1, 1> a1;

  ama::get<0,0>(a1) = 0.0;
  ama::get<0,1>(a1) = 0.1;
  ama::get<1,0>(a1) = 1.0;
  ama::get<1,1>(a1) = 1.1;

  ama::tensor<float, 2, 1, 1> a2(a1);

  BOOST_CHECK_EQUAL((ama::get<0,0>(a1)), (ama::get<0,0>(a2)));
  BOOST_CHECK_EQUAL((ama::get<0,1>(a1)), (ama::get<0,1>(a2)));
  BOOST_CHECK_EQUAL((ama::get<1,0>(a1)), (ama::get<1,0>(a2)));
  BOOST_CHECK_EQUAL((ama::get<1,1>(a1)), (ama::get<1,1>(a2)));

  ama::tensor<float, 2, 1, 1> a3; a3 = a1;

  BOOST_CHECK_EQUAL((ama::get<0,0>(a1)), (ama::get<0,0>(a3)));
  BOOST_CHECK_EQUAL((ama::get<0,1>(a1)), (ama::get<0,1>(a3)));
  BOOST_CHECK_EQUAL((ama::get<1,0>(a1)), (ama::get<1,0>(a3)));
  BOOST_CHECK_EQUAL((ama::get<1,1>(a1)), (ama::get<1,1>(a3)));
}

BOOST_AUTO_TEST_CASE(unary_operator)
{
  ama::tensor<float, 2, 1, 1> a1;

  ama::get<0,0>(a1) = 0.0;
  ama::get<0,1>(a1) = 0.1;
  ama::get<1,0>(a1) = 1.0;
  ama::get<1,1>(a1) = 1.1;

  ama::tensor<float, 2, 1, 1> a2;

  a2 = +a1;

  BOOST_CHECK_EQUAL((ama::get<0,0>(a2)), 0.0f);
  BOOST_CHECK_EQUAL((ama::get<0,1>(a2)), 0.1f);
  BOOST_CHECK_EQUAL((ama::get<1,0>(a2)), 1.0f);
  BOOST_CHECK_EQUAL((ama::get<1,1>(a2)), 1.1f);

  a2 = -a1;

  BOOST_CHECK_EQUAL((ama::get<0,0>(a2)), -0.0f);
  BOOST_CHECK_EQUAL((ama::get<0,1>(a2)), -0.1f);
  BOOST_CHECK_EQUAL((ama::get<1,0>(a2)), -1.0f);
  BOOST_CHECK_EQUAL((ama::get<1,1>(a2)), -1.1f);

  a2 = 2 * a1;

  BOOST_CHECK_EQUAL((ama::get<0,0>(a2)), 2 * 0.0f);
  BOOST_CHECK_EQUAL((ama::get<0,1>(a2)), 2 * 0.1f);
  BOOST_CHECK_EQUAL((ama::get<1,0>(a2)), 2 * 1.0f);
  BOOST_CHECK_EQUAL((ama::get<1,1>(a2)), 2 * 1.1f);
}

BOOST_AUTO_TEST_CASE(binary_operator)
{
  ama::tensor<float, 2, 1, 1> a1, a2;

  ama::get<0,0>(a1) = 0.0;
  ama::get<0,1>(a1) = 0.1;
  ama::get<1,0>(a1) = 1.0;
  ama::get<1,1>(a1) = 1.1;

  ama::get<0,0>(a2) = 0.0;
  ama::get<0,1>(a2) = 0.2;
  ama::get<1,0>(a2) = 2.0;
  ama::get<1,1>(a2) = 2.2;

  ama::tensor<float, 2, 1, 1> a3;

  a3 = a1 + a2;

  BOOST_CHECK_EQUAL((ama::get<0,0>(a3)), 0.0f + 0.0f);
  BOOST_CHECK_EQUAL((ama::get<0,1>(a3)), 0.1f + 0.2f);
  BOOST_CHECK_EQUAL((ama::get<1,0>(a3)), 1.0f + 2.0f);
  BOOST_CHECK_EQUAL((ama::get<1,1>(a3)), 1.1f + 2.2f);

  a3 = a1 - a2;

  BOOST_CHECK_EQUAL((ama::get<0,0>(a3)), 0.0f - 0.0f);
  BOOST_CHECK_EQUAL((ama::get<0,1>(a3)), 0.1f - 0.2f);
  BOOST_CHECK_EQUAL((ama::get<1,0>(a3)), 1.0f - 2.0f);
  BOOST_CHECK_EQUAL((ama::get<1,1>(a3)), 1.1f - 2.2f);
}

BOOST_AUTO_TEST_CASE(complex_operation)
{
  ama::tensor<float, 2, 1, 1> a1, a2, a3;

  ama::get<0,0>(a1) = 0.0;
  ama::get<0,1>(a1) = 0.1;
  ama::get<1,0>(a1) = 1.0;
  ama::get<1,1>(a1) = 1.1;

  ama::get<0,0>(a2) = 0.0;
  ama::get<0,1>(a2) = 0.2;
  ama::get<1,0>(a2) = 2.0;
  ama::get<1,1>(a2) = 2.2;

  ama::get<0,0>(a3) = 0.0;
  ama::get<0,1>(a3) = 0.3;
  ama::get<1,0>(a3) = 3.0;
  ama::get<1,1>(a3) = 3.3;

  ama::tensor<float, 2, 1, 1> a4;

  a4 = a1 + a2 + a3;

  BOOST_CHECK_EQUAL((ama::get<0,0>(a4)), 0.0f + 0.0f + 0.0f);
  BOOST_CHECK_EQUAL((ama::get<0,1>(a4)), 0.1f + 0.2f + 0.3f);
  BOOST_CHECK_EQUAL((ama::get<1,0>(a4)), 1.0f + 2.0f + 3.0f);
  BOOST_CHECK_EQUAL((ama::get<1,1>(a4)), 1.1f + 2.2f + 3.3f);

  a4 = a1 + a2 - a3;

  BOOST_CHECK_EQUAL((ama::get<0,0>(a4)), 0.0f + 0.0f - 0.0f);
  BOOST_CHECK_EQUAL((ama::get<0,1>(a4)), 0.1f + 0.2f - 0.3f);
  BOOST_CHECK_EQUAL((ama::get<1,0>(a4)), 1.0f + 2.0f - 3.0f);
  BOOST_CHECK_EQUAL((ama::get<1,1>(a4)), 1.1f + 2.2f - 3.3f);

  a4 = a1 - a2 + a3;

  BOOST_CHECK_EQUAL((ama::get<0,0>(a4)), 0.0f - 0.0f + 0.0f);
  BOOST_CHECK_EQUAL((ama::get<0,1>(a4)), 0.1f - 0.2f + 0.3f);
  BOOST_CHECK_EQUAL((ama::get<1,0>(a4)), 1.0f - 2.0f + 3.0f);
  BOOST_CHECK_EQUAL((ama::get<1,1>(a4)), 1.1f - 2.2f + 3.3f);

  a4 = a1 - a2 - a3;

  BOOST_CHECK_EQUAL((ama::get<0,0>(a4)), 0.0f - 0.0f - 0.0f);
  BOOST_CHECK_EQUAL((ama::get<0,1>(a4)), 0.1f - 0.2f - 0.3f);
  BOOST_CHECK_EQUAL((ama::get<1,0>(a4)), 1.0f - 2.0f - 3.0f);
  BOOST_CHECK_EQUAL((ama::get<1,1>(a4)), 1.1f - 2.2f - 3.3f);

  a4 = 0.5 * (a1 + a2);

  BOOST_CHECK_EQUAL((ama::get<0,0>(a4)), 0.5f * (0.0f + 0.0f));
  BOOST_CHECK_EQUAL((ama::get<0,1>(a4)), 0.5f * (0.1f + 0.2f));
  BOOST_CHECK_EQUAL((ama::get<1,0>(a4)), 0.5f * (1.0f + 2.0f));
  BOOST_CHECK_EQUAL((ama::get<1,1>(a4)), 0.5f * (1.1f + 2.2f));

  a4 = 0.5 * (a1 - a2);

  BOOST_CHECK_EQUAL((ama::get<0,0>(a4)), 0.5f * (0.0f - 0.0f));
  BOOST_CHECK_EQUAL((ama::get<0,1>(a4)), 0.5f * (0.1f - 0.2f));
  BOOST_CHECK_EQUAL((ama::get<1,0>(a4)), 0.5f * (1.0f - 2.0f));
  BOOST_CHECK_EQUAL((ama::get<1,1>(a4)), 0.5f * (1.1f - 2.2f));

  a4 = 0.5 * (a1 + a2) + a3;

  BOOST_CHECK_EQUAL((ama::get<0,0>(a4)), 0.5f * (0.0f + 0.0f) + 0.0f);
  BOOST_CHECK_EQUAL((ama::get<0,1>(a4)), 0.5f * (0.1f + 0.2f) + 0.3f);
  BOOST_CHECK_EQUAL((ama::get<1,0>(a4)), 0.5f * (1.0f + 2.0f) + 3.0f);
  BOOST_CHECK_EQUAL((ama::get<1,1>(a4)), 0.5f * (1.1f + 2.2f) + 3.3f);

  a4 = 0.5 * (a1 - a2) - a3;

  BOOST_CHECK_EQUAL((ama::get<0,0>(a4)), 0.5f * (0.0f - 0.0f) - 0.0f);
  BOOST_CHECK_EQUAL((ama::get<0,1>(a4)), 0.5f * (0.1f - 0.2f) - 0.3f);
  BOOST_CHECK_EQUAL((ama::get<1,0>(a4)), 0.5f * (1.0f - 2.0f) - 3.0f);
  BOOST_CHECK_EQUAL((ama::get<1,1>(a4)), 0.5f * (1.1f - 2.2f) - 3.3f);
}

BOOST_AUTO_TEST_CASE(outer)
{
  ama::tensor<float, 2, 1, 1> a1,a2,a3;
  ama::tensor<float, 2, 0, 1> v;
  ama::tensor<float, 2, 1, 0> w;

  ama::get<0>(v) = 1.1;
  ama::get<1>(v) = 2.1;

  ama::get<0>(w) = 1.2;
  ama::get<1>(w) = 2.2;

  ama::get<0,0>(a2) = 0.0;
  ama::get<0,1>(a2) = 0.1;
  ama::get<1,0>(a2) = 1.0;
  ama::get<1,1>(a2) = 1.1;

  a1 = ama::outer(w,v);

  BOOST_CHECK_EQUAL((ama::get<0,0>(a1)), (ama::get<0>(w) * ama::get<0>(v)));
  BOOST_CHECK_EQUAL((ama::get<0,1>(a1)), (ama::get<0>(w) * ama::get<1>(v)));
  BOOST_CHECK_EQUAL((ama::get<1,0>(a1)), (ama::get<1>(w) * ama::get<0>(v)));
  BOOST_CHECK_EQUAL((ama::get<1,1>(a1)), (ama::get<1>(w) * ama::get<1>(v)));

  a3 = a2 + ama::outer(w,v);

  BOOST_CHECK_EQUAL((ama::get<0,0>(a3)), (ama::get<0,0>(a2) + (ama::get<0>(w) * ama::get<0>(v))));
  BOOST_CHECK_EQUAL((ama::get<0,1>(a3)), (ama::get<0,1>(a2) + (ama::get<0>(w) * ama::get<1>(v))));
  BOOST_CHECK_EQUAL((ama::get<1,0>(a3)), (ama::get<1,0>(a2) + (ama::get<1>(w) * ama::get<0>(v))));
  BOOST_CHECK_EQUAL((ama::get<1,1>(a3)), (ama::get<1,1>(a2) + (ama::get<1>(w) * ama::get<1>(v))));
}

BOOST_AUTO_TEST_CASE(basic_index)
{
  typedef ama::index<'i'> i;
  typedef ama::index<'j'> j;
  typedef ama::index<'k'> k;

  typedef boost::mpl::vector<i> i_;
  typedef boost::mpl::vector<j> j_;

  typedef boost::mpl::vector<i,i> ii;
  typedef boost::mpl::vector<i,j> ij;
  typedef boost::mpl::vector<i,k> ik;
  typedef boost::mpl::vector<j,i> ji;
  typedef boost::mpl::vector<j,k> jk;

  typedef boost::mpl::vector<i,j,j,k> ijjk;

  ama::tensor<float, 2, 1, 1> a1;
  ama::tensor<float, 2, 1, 1> a2;
  ama::tensor<float, 2, 2, 2> a3;

  ama::get<0,0>(a1) = 2.2;
  ama::get<0,1>(a1) = 2.1;
  ama::get<1,0>(a1) = 1.2;
  ama::get<1,1>(a1) = 1.1;

  ama::get<0,0,0,0>(a3) = 1.0000;
  ama::get<0,0,0,1>(a3) = 1.0001;
  ama::get<0,0,1,0>(a3) = 1.0010;
  ama::get<0,0,1,1>(a3) = 1.0011;
  ama::get<0,1,0,0>(a3) = 1.0100;
  ama::get<0,1,0,1>(a3) = 1.0101;
  ama::get<0,1,1,0>(a3) = 1.0110;
  ama::get<0,1,1,1>(a3) = 1.0111;
  ama::get<1,0,0,0>(a3) = 1.1000;
  ama::get<1,0,0,1>(a3) = 1.1001;
  ama::get<1,0,1,0>(a3) = 1.1010;
  ama::get<1,0,1,1>(a3) = 1.1011;
  ama::get<1,1,0,0>(a3) = 1.1100;
  ama::get<1,1,0,1>(a3) = 1.1101;
  ama::get<1,1,1,0>(a3) = 1.1110;
  ama::get<1,1,1,1>(a3) = 1.1111;

  a2.idx<ij>() = a1.idx<ji>();

  BOOST_CHECK_EQUAL((ama::get<0,0>(a2)), (ama::get<0,0>(a1)));
  BOOST_CHECK_EQUAL((ama::get<0,1>(a2)), (ama::get<1,0>(a1)));
  BOOST_CHECK_EQUAL((ama::get<1,0>(a2)), (ama::get<0,1>(a1)));
  BOOST_CHECK_EQUAL((ama::get<1,1>(a2)), (ama::get<1,1>(a1)));

  a2.idx<ij>() = a1.idx<ij>() + a1.idx<ji>();

  BOOST_CHECK_EQUAL((ama::get<0,0>(a2)), (ama::get<0,0>(a1) + ama::get<0,0>(a1)));
  BOOST_CHECK_EQUAL((ama::get<0,1>(a2)), (ama::get<0,1>(a1) + ama::get<1,0>(a1)));
  BOOST_CHECK_EQUAL((ama::get<1,0>(a2)), (ama::get<1,0>(a1) + ama::get<0,1>(a1)));
  BOOST_CHECK_EQUAL((ama::get<1,1>(a2)), (ama::get<1,1>(a1) + ama::get<1,1>(a1)));

  a2.idx<ij>() = a1.idx<ij>() - a1.idx<ji>();

  BOOST_CHECK_EQUAL((ama::get<0,0>(a2)), (ama::get<0,0>(a1) - ama::get<0,0>(a1)));
  BOOST_CHECK_EQUAL((ama::get<0,1>(a2)), (ama::get<0,1>(a1) - ama::get<1,0>(a1)));
  BOOST_CHECK_EQUAL((ama::get<1,0>(a2)), (ama::get<1,0>(a1) - ama::get<0,1>(a1)));
  BOOST_CHECK_EQUAL((ama::get<1,1>(a2)), (ama::get<1,1>(a1) - ama::get<1,1>(a1)));

  a2.idx<ij>() = 0.5 * (a1.idx<ij>() + a1.idx<ji>());

  BOOST_CHECK_EQUAL((ama::get<0,0>(a2)), 0.5f * (ama::get<0,0>(a1) + ama::get<0,0>(a1)));
  BOOST_CHECK_EQUAL((ama::get<0,1>(a2)), 0.5f * (ama::get<0,1>(a1) + ama::get<1,0>(a1)));
  BOOST_CHECK_EQUAL((ama::get<1,0>(a2)), 0.5f * (ama::get<1,0>(a1) + ama::get<0,1>(a1)));
  BOOST_CHECK_EQUAL((ama::get<1,1>(a2)), 0.5f * (ama::get<1,1>(a1) + ama::get<1,1>(a1)));

  a2.idx<ij>() = 0.5 * (a1.idx<ij>() - a1.idx<ji>());

  BOOST_CHECK_EQUAL((ama::get<0,0>(a2)), 0.5f * (ama::get<0,0>(a1) - ama::get<0,0>(a1)));
  BOOST_CHECK_EQUAL((ama::get<0,1>(a2)), 0.5f * (ama::get<0,1>(a1) - ama::get<1,0>(a1)));
  BOOST_CHECK_EQUAL((ama::get<1,0>(a2)), 0.5f * (ama::get<1,0>(a1) - ama::get<0,1>(a1)));
  BOOST_CHECK_EQUAL((ama::get<1,1>(a2)), 0.5f * (ama::get<1,1>(a1) - ama::get<1,1>(a1)));

  float v = a1.idx<ii>();

  BOOST_CHECK_EQUAL(v, (ama::get<0,0>(a1) + ama::get<1,1>(a1)));

  a2.idx<ik>() = a3.idx<ijjk>();

  BOOST_CHECK_EQUAL((ama::get<0,0>(a2)), (ama::get<0,0,0,0>(a3) + ama::get<0,1,1,0>(a3)));
  BOOST_CHECK_EQUAL((ama::get<0,1>(a2)), (ama::get<0,0,0,1>(a3) + ama::get<0,1,1,1>(a3)));
  BOOST_CHECK_EQUAL((ama::get<1,0>(a2)), (ama::get<1,0,0,0>(a3) + ama::get<1,1,1,0>(a3)));
  BOOST_CHECK_EQUAL((ama::get<1,1>(a2)), (ama::get<1,0,0,1>(a3) + ama::get<1,1,1,1>(a3)));
}

BOOST_AUTO_TEST_CASE(basic_index_linear)
{
  ama::index<'i'> i;
  ama::index<'j'> j;
  ama::index<'k'> k;

  ama::tensor<float, 2, 1, 1> a1;
  ama::tensor<float, 2, 1, 1> a2;
  ama::tensor<float, 2, 2, 2> a3;

  a1(0,0) = 2.2;
  a1(0,1) = 2.1;
  a1(1,0) = 1.2;
  a1(1,0) = 1.1;

  a3(0,0,0,0) = 1.0000;
  a3(0,0,0,1) = 1.0001;
  a3(0,0,1,0) = 1.0010;
  a3(0,0,1,1) = 1.0011;
  a3(0,1,0,0) = 1.0100;
  a3(0,1,0,1) = 1.0101;
  a3(0,1,1,0) = 1.0110;
  a3(0,1,1,1) = 1.0111;
  a3(1,0,0,0) = 1.1000;
  a3(1,0,0,1) = 1.1001;
  a3(1,0,1,0) = 1.1010;
  a3(1,0,1,1) = 1.1011;
  a3(1,1,0,0) = 1.1100;
  a3(1,1,0,1) = 1.1101;
  a3(1,1,1,0) = 1.1110;
  a3(1,1,1,1) = 1.1111;

  a2(i,j) = a1(j,i);

  BOOST_CHECK_EQUAL(a2(0,0), a1(0,0));
  BOOST_CHECK_EQUAL(a2(0,1), a1(1,0));
  BOOST_CHECK_EQUAL(a2(1,0), a1(0,1));
  BOOST_CHECK_EQUAL(a2(1,1), a1(1,1));

  a2(i,j) = a1(i,j) + a1(j,i);

  BOOST_CHECK_EQUAL(a2(0,0), (a1(0,0) + a1(0,0)));
  BOOST_CHECK_EQUAL(a2(0,1), (a1(0,1) + a1(1,0)));
  BOOST_CHECK_EQUAL(a2(1,0), (a1(1,0) + a1(0,1)));
  BOOST_CHECK_EQUAL(a2(1,1), (a1(1,1) + a1(1,1)));

  a2(i,j) = a1(i,j) - a1(j,i);

  BOOST_CHECK_EQUAL(a2(0,0), (a1(0,0) - a1(0,0)));
  BOOST_CHECK_EQUAL(a2(0,1), (a1(0,1) - a1(1,0)));
  BOOST_CHECK_EQUAL(a2(1,0), (a1(1,0) - a1(0,1)));
  BOOST_CHECK_EQUAL(a2(1,1), (a1(1,1) - a1(1,1)));

  a2(i,j) = 0.5 * (a1(i,j) + a1(j,i));

  BOOST_CHECK_EQUAL(a2(0,0), 0.5f * (a1(0,0) + a1(0,0)));
  BOOST_CHECK_EQUAL(a2(0,1), 0.5f * (a1(0,1) + a1(1,0)));
  BOOST_CHECK_EQUAL(a2(1,0), 0.5f * (a1(1,0) + a1(0,1)));
  BOOST_CHECK_EQUAL(a2(1,1), 0.5f * (a1(1,1) + a1(1,1)));

  a2(i,j) = 0.5 * (a1(i,j) - a1(j,i));

  BOOST_CHECK_EQUAL(a2(0,0), 0.5f * (a1(0,0) - a1(0,0)));
  BOOST_CHECK_EQUAL(a2(0,1), 0.5f * (a1(0,1) - a1(1,0)));
  BOOST_CHECK_EQUAL(a2(1,0), 0.5f * (a1(1,0) - a1(0,1)));
  BOOST_CHECK_EQUAL(a2(1,1), 0.5f * (a1(1,1) - a1(1,1)));

  float v = a1(i,i);

  BOOST_CHECK_EQUAL(v, (a1(0,0) + a1(1,1)));

  a2(i,k) = a3(i,j,j,k);

  BOOST_CHECK_EQUAL(a2(0,0), (a3(0,0,0,0) + a3(0,1,1,0)));
  BOOST_CHECK_EQUAL(a2(0,1), (a3(0,0,0,1) + a3(0,1,1,1)));
  BOOST_CHECK_EQUAL(a2(1,0), (a3(1,0,0,0) + a3(1,1,1,0)));
  BOOST_CHECK_EQUAL(a2(1,1), (a3(1,0,0,1) + a3(1,1,1,1)));
}
