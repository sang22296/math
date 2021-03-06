///////////////////////////////////////
//       Author: Sang Nguyen         //
//                                   //
//    email: nqs.dn222@gmail.com     //
//                                   //
//       From Dota2vn with love      //
///////////////////////////////////////


#ifndef COMMON
#define COMMON

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct File_mat {
	uint32_t row;
	uint32_t col;
	char *file_name;
} File_mat;

typedef File_mat File_vec;

typedef struct image_info {
	uint32_t height;
	uint32_t width;
	uint32_t bpp; // bytes per pixel
	unsigned char *img_data;
} img_info;

#endif