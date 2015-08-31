/* Very Fast Wavelet encoding/decoding library V.01 alpha
 * LGPL - By Eloi Du Bois (2008)
 * eloi.du.bois[AT]gmail.com.toremove
 *
 * Lifting scheme used: Le Gall 5/3, that means you can use it for lossless 
 *                      or lossy compression.
 *
 * Bibliography: Image and Video Compression for Multimedia Engineering.
 *               Yun Q. Shi Huifang Sun.
 *
 * PLEASE PUT MY NAME IN YOUR SPECIAL THANKS IF YOU USE THIS LIB
 * (That lib was not a piece of cake to be made...)
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
#include "include/vfwl_codec.h"
#include "include/vfwl_image.h"

#define usage_str "Usage: %s <input pnm file> <output pnm file>\n"

int
main(int argc, char *argv[]) {
    CLOCK_T start, stop;
    double t1, t2 = 0.0;
    wavparams_t params;
    wav_t *out = NULL;
    image_t img;
    unsigned char header[WAVELET_CODEC_HEADER_SIZE];

    printf("******************* Very Fast Wavelet Codec ****************\n");
    printf("* IMAGE ENCODING TEST                  v0.02a              *\n");
    printf("************************************************************\n");
    if (argc != 3) {
        fprintf(stderr, usage_str, argv[0]);
        return -1;
    }
    /* Wavelet codec initializations */
    params.nb_levels = 5;
    params.q_max = 1.0f;

    printf("\nLoading & encoding image\n");
    CLOCK(start);
    vfwl_encode_image(&out, argv[1], header, &params);
    CLOCK(stop);
    t1 = CLOCK_DIFF(stop, start);
    printf("Image reading & encoding took: %.03f\n", t1);
    t2 += t1;

    img.w = params.w;
    img.h = params.h;
    img.nb_channels = params.nb_channels;
    img.channels = (pix_t*)out;
    printf("\nWriting wavelets subband pyramid to wc.ppm\n");
    CLOCK(start);
    vfwl_export_pnm("wc.ppm", &img, 1);
    CLOCK(stop);
    t1 = CLOCK_DIFF(stop, start);
    printf("Image writing took: %.03f\n", t1);
    t2 += t1;

    printf("\nDecoding & writing image");
    CLOCK(start);
    vfwl_decode_image(argv[2], out, header);
    CLOCK(stop);
    t1 = CLOCK_DIFF(stop, start);
    printf("Image decoding & writing took: %.03f\n", t1);
    t2 += t1;

    printf("Total time: %.03f\n", t2);
    printf("\nFreeing data structures...\n");
    _mm_free(out);
    printf("\n");
    return 0;
}
