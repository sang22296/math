///////////////////////////////////////
//       Author: Sang Nguyen         //
//                                   //
//    email: nqs.dn222@gmail.com     //
//                                   //
//       From Dota2vn with love      //
///////////////////////////////////////


#include "../inc/linear_regression.h"

Vector *linear_regression(char *sample_input_file, char *sample_output_file)
{
	File_mat *input_info  = get_file(sample_input_file);
	File_vec *output_info = get_file(sample_output_file);

	Matrix *input         = init_matrix(input_info);
	Vector *output        = init_vector(output_info);
	if(input->row != vector_length(output)) {
		printf("The input data and out put data does not match\n");
		printf("Input file %s has %u rows\n",sample_input_file,input->row);
		printf("but output file %s has data length = %u\n", sample_output_file,vector_length(output));
		free_mat(input);
		free_vector(output);
		exit(1);
	}
	switch(check_vector(output))
	{
		case(COL):
			break;
		case(ROW):
			output = transpose_vector(output);
			break;
		default:
			printf("There is a problem with output vector!\n");
			exit(1);
	}

	Matrix *one_bar = ones(mat_getrow(input),VER);
	Matrix *Xbar    = concatenate_mat(one_bar,input,HOR);
	Matrix *Xbar_t  = transpose_matrix(Xbar);
	Matrix *A       = mul_matrix(Xbar_t,Xbar);
	// display_matrix(A);
	Matrix *b        = mul_matrix(Xbar_t,output);
	Matrix *A_invert = inv_matrix(A);
	Vector *weight        = mul_matrix(A_invert,b);
	// display_vector(weight);

	free_mat(input);
	free_vector(output);
	free_mat(one_bar);
	free_mat(Xbar);
	free_mat(Xbar_t);
	// free_mat(A);
	free_mat(b);
	free_mat(A_invert);

	return weight;
}

Vector *apply_linear_rg(Vector *weight, char *file) {
	switch(check_vector(weight))
	{
		case(COL):
			break;
		case(ROW):
			weight = transpose_vector(weight);
			break;
		default:
			printf("There is a problem with output vector!\n");
			exit(1);
	}
	File_mat *input_file = get_file(file);
	Matrix   *input      = init_matrix(input_file);
	if(input->col != vector_length(weight)-1) {
		printf("input->col != vector_length(weight)-1\n");
		printf("Input file %s has %u collums\n",file,input->col);
		printf("but weight has data length = %u\n", vector_length(weight));
		free_mat(input);
		exit(1);
	}
	Matrix *one    = ones(mat_getrow(input),VER);
	Matrix *Xbar   = concatenate_mat(one,input,HOR);
	Vector *output = mul_matrix(Xbar,weight);
	// display_vector(output);
	return output;

}