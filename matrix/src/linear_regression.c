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

	// free_mat(input);
	// free_vector(output);
	// free_mat(one_bar);
	// free_mat(Xbar);
	// free_mat(Xbar_t);
	// free_mat(A);
	// free_mat(b);
	// free_mat(A_invert);

	return weight;
#if 0
	free_mat(total_input);
	free_mat(line);

	Matrix *data_t = transpose_matrix(data);
	Matrix *output_data_t = transpose_matrix(output_data);

	Matrix *one_bar = ones(mat_getrow(data_t),VER);
	Matrix *Xbar = concatenate_mat(one_bar,data_t,HOR);
	free(one_bar);

	Matrix *Xbar_t = transpose_matrix(Xbar);
	Matrix *A = mul_matrix(Xbar_t,Xbar);
	Matrix *b = mul_matrix(Xbar_t,output_data_t);

	free_mat(Xbar_t);

	free_mat(data_t);

	Matrix *w = mul_matrix(inv_mat(A),b);

	printf("A = \n");
	display_matrix(A);
	printf("b = \n");
	display_matrix(b);

	printf("w = inv(A).b =\n");
	display_matrix(w);

	File_mat *f = get_file("./mat_files/input.mat");
	Matrix *i = init_matrix(f);
	Matrix *input = transpose_matrix(i);
	free_mat(i);
	//Matrix *output_mat = transpose_matrix(mul_matrix(concatenate_mat(ones(input->row,VER),input,HOR),w));
	Matrix *one = ones(input->row,VER);
	Matrix *output_mat1 = concatenate_mat(one,input,HOR);
	free_mat(one);
	Matrix *output_mat2 = mul_matrix(output_mat1,w);
	Matrix *output_mat = transpose_matrix(output_mat2);
	free_mat(output_mat1);
	free_mat(output_mat2);
	printf("Output data:\n");
	display_matrix(output_mat);
	//display_matrix(transpose_matrix(mul_matrix(Xbar,w)));
	//display_matrix(weight);


	free_mat(output_data);
	free_mat(data);
	free_mat(A);
	free(b);
	free_mat(w);
	free_mat(output_mat);
	free_mat(output_data_t);
	free_mat(input);
	free_mat(Xbar);
	free(data_info);
	free(f);

#endif

	return 0;
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
	display_vector(output);
	return output;

}