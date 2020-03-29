///////////////////////////////////////
//       Author: Sang Nguyen         //
//                                   //
//    email: nqs.dn222@gmail.com     //
//                                   //
//       From Dota2vn with love      //
///////////////////////////////////////


#include "../inc/linear_regression.h"
#include "../inc/kmean_clustering.h"

int main(int argc, char const *argv[])
{
#if 0
	char data[]                  = "./mat_files/data.mat";
	File_mat *data_info  = get_file(data);
	Matrix *data_matrix         = init_matrix(data_info);
	display_vector(get_line(data_matrix,1,VER));
#endif
	char sample_linear_input_file[]  = "./mat_files/sample_linear_input.mat";
	char sample_linear_output_file[] = "./mat_files/sample_linear_output.mat";
	char input_file[]         = "./mat_files/input.mat";

	char sample_kmean_input_file[]   = "./mat_files/sample_kmean_input.mat";


	Vector *weight = linear_regression(sample_linear_input_file,
										sample_linear_output_file);
	Vector *output = apply_linear_rg(weight, input_file);
	display_vector(output);
	Kmean_clustering(sample_kmean_input_file,3);
	return 0;
}