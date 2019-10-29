#include "matrix.h"

int main(int argc, char const *argv[])
{
	File_mat *data_info = get_file("data.mat");

	Matrix *total_input = init_matrix(data_info);
	Matrix *expect_input = sub_matrix(total_input,1,data_info->row,4,6);

	Matrix *data = transpose_matrix(expect_input);

	display_matrix(data);
	Matrix *line = get_line(total_input,7,VER);
	Matrix *output_data = transpose_matrix(line);
	display_matrix(output_data);

	free_mat(total_input);
	free(line);

	Matrix *data_t = transpose_matrix(data);
	Matrix *output_data_t = transpose_matrix(output_data);

	Matrix *one_bar = ones(data_t->row,VER);
	Matrix *Xbar = concatenate_mat(one_bar,data_t,HOR);
	free(one_bar);

	Matrix *Xbar_t = transpose_matrix(Xbar);
	Matrix *A = mul_matrix(Xbar_t,Xbar);
	Matrix *b = mul_matrix(Xbar_t,output_data_t);

	free(Xbar_t);

	free_mat(data_t);

	Matrix *w = mul_matrix(inv_mat(A),b);

	printf("A = \n");
	display_matrix(A);
	printf("b = \n");
	display_matrix(b);

	printf("w = inv(A).b =\n");
	display_matrix(w);

	File_mat *f = get_file("input.mat");
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

	return 0;
}