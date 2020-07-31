///////////////////////////////////////
//       Author: Sang Nguyen         //
//                                   //
//    email: nqs.dn222@gmail.com     //
//                                   //
//       From Dota2vn with love      //
///////////////////////////////////////

#ifdef __clang__
#define STBIWDEF static inline
#endif
#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../image_lib/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../image_lib/stb_image.h"

#include "../ML_algo/inc/linear_regression.h"
#include "../ML_algo/inc/kmean_clustering.h"

void v_half_cut(unsigned char *data, int w, int h, int n)
{
    for(int i=0; i < h/2; i++)
        for (int j = 0; j < w; j++)
        {
            data[i*w*n +j*n + 0] = 0;
            data[i*w*n +j*n + 1] = 0;
            data[i*w*n +j*n + 2] = 0;
        }
}

int main(int argc, char const *argv[])
{
#if 1
    img_info i_info;
    uint32_t *h = &(i_info.height);
    uint32_t *w = &(i_info.width);
    uint32_t *n = &(i_info.bpp);
    const char filename[] = "./data/butterfly.jpeg";
    i_info.img_data = stbi_load(filename, w, h, n, 0);
    printf("width: %d, height: %d, bpp: %d\n", *w, *h, *n);
    image_to_raw_data(&i_info, "buom_raw.txt");
    int n_cluster = 4;
    Matrix *A = Kmean_clustering_img(&i_info, n_cluster);
    unsigned char *data;
    data = matrix_to_image(A, *h, *w);
    stbi_write_png("buom.png", *w, *h, *n, data, (*w)*(*n));
    stbi_image_free(i_info.img_data);
#else
	char sample_linear_input_file[]  = "./data/sample_linear_input.mat";
	char sample_linear_output_file[] = "./data/sample_linear_output.mat";
	char input_file[]         = "./data/input.mat";

	char sample_kmean_input_file[]   = "./data/sample_kmean_input.mat";


	Vector *weight = linear_regression(sample_linear_input_file,
										sample_linear_output_file);
	Vector *output = apply_linear_rg(weight, input_file);
	display_vector(output);
	Kmean_clustering(sample_kmean_input_file,3);
#endif
	return 0;
}