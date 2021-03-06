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

#ifndef AMA_MULTI_ARRAY_CONFIG_HPP
#define AMA_MULTI_ARRAY_CONFIG_HPP 1

#ifdef AMA_MULTI_ARRAY_DISABLE_LINEAR_ACCESS
#define AMA_MULTI_ARRAY_MAX_LINEAR_ACCESS -1
#endif /* AMA_MULTI_ARRAY_DISABLE_LINEAR_ACCESS */

#ifndef AMA_MULTI_ARRAY_MAX_LINEAR_ACCESS
#define AMA_MULTI_ARRAY_MAX_LINEAR_ACCESS 4
#endif /* AMA_MULTI_ARRAY_MAX_RUNTINE_ACCESS */

#if AMA_MULTI_ARRAY_MAX_LINEAR_ACCESS >= 0
#define AMA_MULTI_ARRAY_USE_LINEAR_ACCESS 1
#endif /* AMA_MULTI_ARRAY_MAX_LINEAR_ACCESS */

#endif /* AMA_MULTI_ARRAY_CONFIG_HPP */
