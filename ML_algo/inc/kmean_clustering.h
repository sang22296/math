///////////////////////////////////////
//       Author: Sang Nguyen         //
//                                   //
//    email: nqs.dn222@gmail.com     //
//                                   //
//       From Dota2vn with love      //
///////////////////////////////////////

#ifndef KMEAN
#define KMEAN

#include "../../math_lib/inc/matrix.h"
#include "../../math_lib/inc/vector.h"
#include "../../common/inc/file_handle.h"

Matrix *Kmean_clustering(char *sample_input_file, uint32_t n_clusters);

Matrix *Kmean_clustering_img(img_info *i_info, uint32_t n_clusters);

#endif