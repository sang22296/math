///////////////////////////////////////
//       Author: Sang Nguyen         //
//                                   //
//    email: nqs.dn222@gmail.com     //
//                                   //
//       From Dota2vn with love      //
///////////////////////////////////////

#ifndef LINEAR_RG
#define LINEAR_RG

#include "matrix.h"
#include "vector.h"

Vector *linear_regression(char *sample_input_file, char *sample_output_file);
Vector *apply_linear_rg(Vector *weight, char *file);

#endif