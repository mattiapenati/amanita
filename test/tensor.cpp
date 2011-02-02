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
  ama::tensor<float, 2, 1, 1> a1;
  ama::tensor<float, 2, 0, 1> v;
  ama::tensor<float, 2, 1, 0> w;

  ama::get<0>(v) = 1.1;
  ama::get<1>(v) = 2.1;

  ama::get<0>(w) = 1.2;
  ama::get<1>(w) = 2.2;

  a1 = ama::outer(w,v);

  BOOST_CHECK_EQUAL((ama::get<0,0>(a1)), (ama::get<0>(w) * ama::get<0>(v)));
  BOOST_CHECK_EQUAL((ama::get<0,1>(a1)), (ama::get<0>(w) * ama::get<1>(v)));
  BOOST_CHECK_EQUAL((ama::get<1,0>(a1)), (ama::get<1>(w) * ama::get<0>(v)));
  BOOST_CHECK_EQUAL((ama::get<1,1>(a1)), (ama::get<1>(w) * ama::get<1>(v)));
}
