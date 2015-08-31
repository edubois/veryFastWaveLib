/* Very Fast Wavelet encoding/decoding library V.01 alpha
 * LGPL - by Eloi Du Bois 2008
 * eloi.du.bois[AT]gmail.com
 *
 * Bibliography: Image and Video Compression for Multimedia Engineering.
 *               Yun Q. Shi Huifang Sun.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for  more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * ===========================================================================
 * WARNING
 * THIS VERSION DOESN'T SUPPORT IMAGE SIZE THAT ARE LESSER THAN 32x32 AND NOT
 * POWER OF 2.
 */

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>

#include "include/timings.h"
#include "include/vfwl_globals.h"
#include "include/vfwl_codec.h"

#define N            4096

int
main() {
   CLOCK_T start, stop;
   double t1, t2;
   wavparams_t params;
   wav_t* img = (wav_t*)_mm_malloc(sizeof(wav_t) * N*N, 16);
   wav_t* out = (wav_t*)_mm_malloc(sizeof(wav_t) * N*N, 16);
   wav_t* reco = (wav_t*)_mm_malloc(sizeof(wav_t) * N*N, 16);
   wav_t* orig_copy = (wav_t*)_mm_malloc(sizeof(wav_t) * N*N, 16);
   wav_t* p_reco;
   wav_t* p_orig_copy;
   int i, j, error = 0;

   srand(0);
   for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
         img[i*N+j] = rand()*pow(2.0f, sizeof(wav_t)*8 - 1)/RAND_MAX - 1;
         orig_copy[i*N+j] = img[i*N+j];
         out[i*N+j] = 0.0f;
         reco[i*N+j] = 0.0f;
      }
   }

   /* Initializations */
   params.nb_levels = 4;
   params.w = N;
   params.h = N;
   params.nb_channels = 1;
   printf("******************* Very Fast Wavelet Codec ****************\n");
   printf("* BENCHMARK ON SIMD VECTORIZATION                          *\n");
   printf("************************************************************\n");

   /* Proceed for ward integer wavelet transform */
   printf(">Encoding...\n");
   CLOCK(start);
   fiwt1D_5_3(out, img, N*N, &params);
   CLOCK(stop);
   t1 = CLOCK_DIFF(stop, start);
   printf("Benchmark encoding: %.03f (ms)\n", t1 * 1000.0f);
/*   p_reco = out;
   for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
         printf("%d ", *p_reco++);
      }
      printf("\n");
   }
*/
   /* Inverse integer wavelet transfor m */
   printf(">Decoding...\n");
   CLOCK(start);
   iiwt1D_5_3(reco, out, N*N, &params);
   CLOCK(stop);
   t2 = CLOCK_DIFF(stop, start);
   printf("Benchmark decoding: %.03f (ms)\n", t2 * 1000.0f);
   printf("Benchmark total: %.03f (ms)\n", (t1+t2) * 1000.0f );
   p_reco = reco;
   p_orig_copy = orig_copy;
   for (i = 0; i < N*N && !error; i++) {
      if (*p_reco != *p_orig_copy) {
         fprintf(stderr, "[BREAKING] Error in reconstruction "
                         "at offset (%d):%d!=%d\n", 
                         i, *p_reco, *p_orig_copy);
      }
      p_reco++;
      p_orig_copy++;
   }

   if (!error)
      printf(">Reconstruction ok\n");

   /* Cleaning */
   _mm_free(img);
   _mm_free(out);
   _mm_free(reco);
   _mm_free(orig_copy);
   return 0;
}
