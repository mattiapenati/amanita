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

#ifndef AMA_COMMON_POINTER_WRAPPER_HPP
#define AMA_COMMON_POINTER_WRAPPER_HPP 1

namespace ama
{

  /* This class store a pointer, but is not designed for memory managment purpose */
  template <typename T>
  class pointer_wrapper
  {
  public:
    typedef T element_type;

    /* costructor */
    pointer_wrapper(T * ptr = 0): m_ptr(ptr) { }

    /* copy constructor */
    pointer_wrapper(pointer_wrapper const & ptrw): m_ptr(ptrw.m_ptr) { }

    /* copy operator */
    pointer_wrapper & operator=(T * ptr)
    {
      m_ptr = ptr;
      return *this;
    }

    /* copy operator */
    pointer_wrapper & operator=(pointer_wrapper const & ptrw)
    {
      m_ptr = ptrw.m_ptr;
      return *this;
    }

    /* access operators */
    T & operator*() const { return *m_ptr; }
    T * operator->() const { return m_ptr; }

    /* check if null */
    bool null() const { return (m_ptr == 0); }

    /* get the pointer */
    T * get() const { return m_ptr; }

    /* comparison operator */
    bool operator==(T * ptr) { return m_ptr == ptr; }
    bool operator==(pointer_wrapper const & ptrw) { return m_ptr == ptrw.m_ptr; }

  protected:
    T * m_ptr;
  };

}

#endif /* AMA_COMMON_POINTER_WRAPPER_HPP */
