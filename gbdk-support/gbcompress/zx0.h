/*
 * (c) Copyright 2021 by Einar Saukas. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * The name of its author may not be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define INITIAL_OFFSET 1

#define FALSE 0
#define TRUE 1

#define ZX0_SKIP_NONE 0
#define ZX0_BACKWARD_OFF     FALSE
#define ZX0_INVERT_MODE_ON   TRUE
#define ZX0_CLASSIC_MODE_OFF FALSE

#define ZX0_MAX_OFFSET    32640
#define ZX7_MAX_OFFSET     2176


typedef struct block_t {
    struct block_t *chain;
    struct block_t *ghost_chain;
    int bits;
    int index;
    int offset;
    int references;
} BLOCK;

BLOCK *allocate(int bits, int index, int offset, BLOCK *chain);

void assign(BLOCK **ptr, BLOCK *chain);

BLOCK *zx0optimize(unsigned char *input_data, int input_size, int skip, int offset_limit);

// Decompression
unsigned char *zx0compress(BLOCK *optimal, unsigned char *input_data, int input_size, int skip, int backwards_mode, int invert_mode, int *output_size, int *delta);
int zx0decompress(char * filename_in, char * filename_out);
