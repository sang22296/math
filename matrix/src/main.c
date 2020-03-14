///////////////////////////////////////
//       Author: Sang Nguyen         //
//                                   //
//    email: nqs.dn222@gmail.com     //
//                                   //
//       From Dota2vn with love      //
///////////////////////////////////////


#include "../inc/linear_regression.h"

int main(int argc, char const *argv[])
{
	char sample_input_file[]  = "./mat_files/sample_input.mat";
	char sample_output_file[] = "./mat_files/sample_output.mat";
	char input_file[]         = "./mat_files/input.mat";
	Vector *weight = linear_regression(sample_input_file,sample_output_file);
	apply_linear_rg(weight, input_file);
	return 0;
}