/*
 * PCG Random Number Generation for C.
 *
 * Copyright 2014 Melissa O'Neill <oneill@pcg-random.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * For additional information about the PCG random number generation scheme,
 * including its license and other licensing options, visit
 *
 *       http://www.pcg-random.org
 */

/*
 * This code is derived from the official basic C PCG implementation (see:
 * https://github.com/imneme/pcg-c-basic). It has been slightly modified to
 * remove unnecessary functions and defines and to add two extra functions
 * srand_pcg and rand_pcg and the macro RAND_MAX_PCG to allow using it as
 * similarly as possible to the stdlib random functions.
 * -- Federico Cerisola
*/

#include "random.h"

/* state for global RNGs */

static pcg32_random_t pcg32_global = PCG32_INITIALIZER;

/* pcg32_srandom(initstate, initseq)
 * pcg32_srandom_r(rng, initstate, initseq):
 *     Seed the rng.  Specified in two parts, state initializer and a
 *     sequence selection constant (a.k.a. stream id) */

void pcg32_srandom_r(pcg32_random_t* rng, uint64_t initstate, uint64_t initseq)
{
    rng->state = 0U;
    rng->inc = (initseq << 1u) | 1u;
    pcg32_random_r(rng);
    rng->state += initstate;
    pcg32_random_r(rng);
}

void pcg32_srandom(uint64_t seed, uint64_t seq)
{
    pcg32_srandom_r(&pcg32_global, seed, seq);
}

/* pcg32_random()
 * pcg32_random_r(rng)
 *     Generate a uniformly distributed 32-bit random number */

uint32_t pcg32_random_r(pcg32_random_t* rng)
{
    uint64_t oldstate = rng->state;
    rng->state = oldstate * 6364136223846793005ULL + rng->inc;
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

uint32_t pcg32_random()
{
    return pcg32_random_r(&pcg32_global);
}

/* drop in replacement functions for stdlib */
void srand_pcg(uint64_t seed)
{
    pcg32_srandom(seed, 54u);
}

uint32_t rand_pcg()
{
    return pcg32_random();
}
