#include "matrix.h"

bool is_square(Matrix *A){
	return (A->row == A->col != 0)?true:false;
}

void free_mat(Matrix *A){
	if(A == NULL){
		return;
	}
	for(int i=0; i<A->row; i++){
		free(A->data[i]);
	}
	free(A->data);
	free(A);

}

Matrix *sub_matrix(Matrix *A, uint32_t r_from, uint32_t r_to, uint32_t c_from, uint32_t c_to){
	if(A == NULL){
		printf("Invalid input matrix!\n");
		exit(1);
	}
	if(r_from > r_to){
		printf("Invalid input, r_from: %d must be less than r_to: %d!\n",r_from,r_to);
		exit(1);
	}
	if(c_from > c_to){
		printf("Invalid input, c_from: %d must be less than c_to: %d!\n",c_from,c_to);
		exit(1);
	}
	if(r_to <=0 || r_from <= 0 || c_to <= 0 || c_from <= 0 || r_to > A->row || c_to > A->col){
		printf("Invalid index compare with input matrix\n");
		exit(1);
	}
	Matrix *sub = (Matrix *)calloc(1,sizeof(Matrix));
	sub->row = r_to - r_from+1;
	sub->col = c_to - c_from+1;
	double **data = (double **)calloc(sub->row,sizeof(double *));
	for(int i=0; i<sub->row; i++){
		data[i] = (double *)calloc(sub->col,sizeof(double));
	}
	for(int i=0; i<sub->row; i++){
		for(int j=0; j<sub->col; j++){
			data[i][j] = A->data[r_from+i-1][c_from+j-1];
		}
	}
	sub->data = data;
	return sub;
}

Matrix *get_line(Matrix *A, uint32_t line, bool dir){
	Matrix *line_mat = (Matrix *)calloc(1,sizeof(Matrix));
	if(dir){
		if(line > A->row){
			printf("Invalid index for getting line!\n");
			exit(1);
		}
		double **data = (double **)calloc(1,sizeof(double *));
		data[0] = (double *)calloc(A->col,sizeof(double));
		for(int i=0; i<A->col; i++){
			data[0][i] = A->data[line-1][i];
		}
		line_mat->row = 1;
		line_mat->col = A->col;
		line_mat->data = data;
	}
	else{
		if(line > A->col){
			printf("Invalid index for getting line!\n");
			exit(1);
		}
		double **data = (double **)calloc(A->row,sizeof(double *));
		for(int i=0; i<A->row; i++){
			data[i] = (double *)calloc(1,sizeof(double));
		}
		for(int i=0; i<A->row; i++){
			data[i][0] = A->data[i][line-1];
		}
		line_mat->row = A->row;
		line_mat->col = 1;
		line_mat->data = data;
	}
	return line_mat;
}

Matrix *one_hot(uint32_t num, uint32_t pos){
	if(pos == 0 || pos > num){
		printf("Cannot initialize one-hot, Invalid position!\n");
		exit(1);
	}
	double **data = (double **)calloc(1,sizeof(double*));
	data[0] = (double *)calloc(num,sizeof(double));
	for(int i=0; i<num; i++){
		data[0][i] = 0;
	}
	data[0][pos-1] = 1;
	Matrix *one_hot = (Matrix *)calloc(1,sizeof(Matrix));
	one_hot->row = 1;
	one_hot->col = num;
	one_hot->data = data;
	return one_hot;
}

Matrix *ones(uint32_t num, bool axis){
	Matrix *one = (Matrix *)calloc(1,sizeof(Matrix));
	if(axis){
		double **data = (double **)calloc(1,sizeof(double*));
		data[0] = (double *)calloc(num,sizeof(double));
		for(int i=0; i<num; i++){
			data[0][i] = 1;
		}
		one->row = 1;
		one->col = num;
		one->data = data;
	}
	else {
		double **data = (double **)calloc(num,sizeof(double*));
		for(int i=0; i<num; i++){
			data[i] = (double *)calloc(1,sizeof(double));
		}
		for(int i=0; i<num; i++){
			data[i][0] = 1;
		}
		one->row = num;
		one->col = 1;
		one->data = data;
	}
	return one;
}

Matrix *concatenate_mat(Matrix *A, Matrix *B, bool axis){
	Matrix *concat_mat = (Matrix *)calloc(1,sizeof(Matrix));
	if(axis){
		if(A->row != B->row){
			printf("Cannot concatinate 2 matrixes!\n");
			exit(1);
		}
		double **data = (double **)calloc(A->row,sizeof(double*));
		for(int i=0; i<A->row; i++){
			data[i] = (double *)calloc(A->col+B->col,sizeof(double));
		}
		concat_mat->row = A->row;
		concat_mat->col = A->col + B->col;
		
		for(int i=0; i<concat_mat->row; i++){
			for(int j=0; j<concat_mat->col; j++){
				bool exceed = (j >= A->col)?true:false;
				if(!exceed){
					data[i][j] = A->data[i][j];
				}
				else{
					data[i][j] = B->data[i][j-A->col];
				}
			}
		}
		concat_mat->data = data;
	}

	else{
		if(A->col != B->col){
			printf("Cannot concatinate 2 matrixes!\n");
			exit(1);
		}
		double **data = (double **)calloc(A->row+B->row,sizeof(double*));
		for(int i=0; i<(A->row+B->row); i++){
			data[i] = (double *)calloc(A->col,sizeof(double));
		}
		concat_mat->row = A->row+B->row;
		concat_mat->col = A->col;
		concat_mat->data = data;
		for(int i=0; i<concat_mat->row; i++){
			for(int j=0; j<concat_mat->col; j++){
				bool exceed = (i >= A->row)?true:false;
				if(!exceed){
					data[i][j] = A->data[i][j];
				}
				else{
					data[i][j] = B->data[i-A->row][j];
				}
			}
		}
	}

	return concat_mat;
}

Matrix *minors_mat(Matrix *A){
	double det = 0;
	if(!is_square(A)){
		printf("The Matrix is not a square matrix!\n");
		exit(1);
	}
	if(A->row == 2){
		double temp;

		temp = A->data[0][0];
		A->data[0][0] = A->data[1][1];
		A->data[1][1] = temp;

		temp = A->data[0][1];
		A->data[0][1] = A->data[1][0];
		A->data[1][0] = temp;

		return A;
	}
	double **data = (double **)calloc(A->row,sizeof(double*));
	for(int i=0; i<A->col; i++){
		data[i] = (double *)calloc(A->col,sizeof(double));
	}
	Matrix *minors = (Matrix *)calloc(1,sizeof(Matrix));
	minors->row = minors->col = A->row;
	for(int i=0; i<A->row; i++){
		for(int j=0; j<A->col; j++){
			Matrix *sub_mat = (Matrix *)calloc(1,sizeof(Matrix));
			double **sub_data = (double **)calloc(A->row-1,sizeof(double*));
			for(int k=0; k<A->row-1; k++){
				sub_data[k] = (double *)calloc(A->col-1,sizeof(double));
			}
			bool exceed_col = false;
			for(int m=0; m<A->row-1; m++){
				bool exceed_row = false;
				exceed_row = (m >= i);
				for(int n=0; n<A->col-1; n++){
					exceed_col = (n >= j);
					if(!exceed_row && !exceed_col)
						sub_data[m][n] = A->data[m][n];
					else if(!exceed_row && exceed_col)
						sub_data[m][n] = A->data[m][n+1];
					else if(exceed_row && !exceed_col)
						sub_data[m][n] = A->data[m+1][n];
					else
						sub_data[m][n] = A->data[m+1][n+1];
				}
			}
			sub_mat->row = A->row-1;
			sub_mat->col = A->col-1;
			sub_mat->data = sub_data;
			data[i][j] = det_mat(sub_mat);
			free_mat(sub_mat);
		}
	}
	minors->data = data;
	return minors;

}

Matrix *sign_chart(uint32_t n){
	Matrix *sign = (Matrix *)calloc(1,sizeof(Matrix));
	double **data = (double **)calloc(n,sizeof(double*));
	for(int i=0; i<n; i++){
		data[i] = (double *)calloc(n,sizeof(double));
	}
	sign->row = sign->col = n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if((i+j)%2 == 0)
				data[i][j] = 1;
			else
				data[i][j] = -1;
		}
	}
	sign->data = data;
	return sign;
}

double det_mat(Matrix *A){
	double det = 0;
	if(!is_square(A)){
		printf("The Matrix is not a square matrix!\n");
		exit(1);
	}
	if(A->row == 1){
		return A->data[0][0];
	}
	else if(A->row == 2){
		return A->data[0][0]*A->data[1][1]-A->data[0][1]*A->data[1][0];
	}
	else {
		for(int i=0; i<A->col; i++){
			Matrix *B = (Matrix *)calloc(1,sizeof(Matrix));
			double **data = (double **)calloc(A->row-1,sizeof(double*));
			for(int k=0; k<A->row-1; k++){
				data[k] = (double *)calloc(A->col-1,sizeof(double));
			}
			for(int m=0; m<A->row-1; m++){
				bool exceed = false;
				for(int n=0; n<A->col-1; n++){
					exceed = (n >= i);
					if(!exceed)
						data[m][n] = A->data[m+1][n];
					else
						data[m][n] = A->data[m+1][n+1];
				}
			}
		B->row = A->row-1;
		B->col = A->col-1;
		B->data = data;
		double sign = (i%2 == 0)?1:-1;
		det += sign*A->data[0][i]*det_mat(B);
		free_mat(B);
		}
	}
	return det;
}

Matrix *transpose_matrix(Matrix *A){
	Matrix* Trans = (Matrix *)calloc(1,sizeof(Matrix));
	double **data = (double **)calloc(A->col,sizeof(double*));
	for(int i=0; i<A->col; i++){
		data[i] = (double *)calloc(A->row,sizeof(double));
	}
	Trans->row = A->col;
	Trans->col = A->row;
	for(int i=0; i<Trans->row; i++)
		for(int j=0; j<Trans->col; j++)
			data[i][j] = A->data[j][i];

	Trans->data = data;
	return Trans;
}

Matrix* unit_mat(uint32_t n){
	Matrix *unit = (Matrix *)calloc(1,sizeof(Matrix));

	double **data = (double **)calloc(n,sizeof(double*));
	for(int i=0; i<n; i++){
		data[i] = (double *)calloc(n,sizeof(double));
	}
	unit->row = unit->col = n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i == j)
				data[i][j] = 1;
			else
				data[i][j] = 0;
		}
	}
	unit->data = data;
	return unit;
}

Matrix *factor_matrix(Matrix *A, double n){
	double **data = (double **)calloc(A->row,sizeof(double*));
	for(int i=0; i<A->row; i++){
		data[i] = (double *)calloc(A->col,sizeof(double));
	}
	Matrix* RET = (Matrix *)calloc(1,sizeof(Matrix));
	RET->row = A->row;
	RET->col = A->col;
	RET->data = data;
	for(int i=0; i<RET->row; i++){
		for(int j=0; j<RET->col; j++){
			data[i][j] = A->data[i][j]*n;
		}
	}
	return RET;
}

Matrix *time_matrix(Matrix *A,Matrix *B){
	if(A->row != B->row || A->col != B->col){
		printf("Two matrix must be equal!\n" );
		exit(1);
	}
	double **data = (double **)calloc(A->row,sizeof(double*));
	for(int i=0; i<A->row; i++){
		data[i] = (double *)calloc(B->col,sizeof(double));
	}
	Matrix* RET = (Matrix *)calloc(1,sizeof(Matrix));
	RET->row = A->row;
	RET->col = B->col;
	RET->data = data;
	for(int i=0; i<RET->row; i++){
		for(int j=0; j<RET->col; j++){
			data[i][j] = A->data[i][j]*B->data[i][j];
		}
	}
	return RET;
}

Matrix* mul_matrix(Matrix* A, Matrix* B) {
	double **data = (double **)calloc(A->row,sizeof(double*));
	for(int i=0; i<A->row; i++){
		data[i] = (double *)calloc(B->col,sizeof(double));
	}
	Matrix* RET = (Matrix *)calloc(1,sizeof(Matrix));
	RET->row = A->row;
	RET->col = B->col;
	RET->data = data;
	
	for(int i = 0; i < A->row; i++){
		for(int m=0; m < B->col; m++){
			for(int j = 0; j < B->row; j++) {
				data[i][m] += A->data[i][j] * B->data[j][m];
			}	
		}
	}

	return RET;
}

Matrix *inv_mat(Matrix *A){
	if(!is_square(A)){
		printf("The Matrix is not a square matrix!\n");
		exit(1);
	}
	double det = det_mat(A);
	if(det == 0){
		printf("Matrix is singular! (Determinant = 0)\n");
		exit(1);
	}
	Matrix *minor = minors_mat(A);
	Matrix *sign = sign_chart(A->row);
	Matrix *minor_sign = time_matrix(sign,(minor));
	Matrix *fact_mat = factor_matrix(minor_sign,1/det);
	Matrix *invert = transpose_matrix(fact_mat);
	free_mat(minor);
	free_mat(sign);
	free_mat(minor_sign);
	free_mat(fact_mat);
	return invert;
}

Matrix* init_matrix(File_mat *mat_file){
	uint32_t r = mat_file->row;
	uint32_t c = mat_file->col;
	char *file_name = mat_file->file_name;
	double **data = (double **)calloc(r,sizeof(double*));
	for(int i=0; i<r; i++){
		data[i] = (double *)calloc(c,sizeof(double));
	}
	Matrix *Mat = (Matrix *)calloc(1,sizeof(Matrix));
	Mat->row = r;
	Mat->col = c;
	FILE *file;
	file=fopen(file_name, "r");
	if(file == NULL){
		printf("File of matrix does not exist!\n");
		return 0;
	}

	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			if (!fscanf(file, "%lf", &data[i][j])) 
				break;
		}
	}
	fclose(file);
	Mat->data = data;
	return Mat;
}

void write_matrix(Matrix *A,char *file_name){
	FILE *file = fopen(file_name,"w");
	for(int i=0; i < A->row; i++){
		for(int j=0; j < A->col; j++){
			fprintf(file, "%.2lf ", A->data[i][j]);
		}
		fprintf(file, "\n");
	}
	fclose(file);
}

void display_matrix(Matrix *A) {
	printf("(%d;%d)\n", A->row, A->col);

	for(int i = 0; i < A->row; i++) {
		for(int j = 0; j < A->col; j++){
			printf("%.2lf\t", A->data[i][j]);
		}
		printf("\n");
	}
}

File_mat *get_file(char *file_name){
	File_mat *mat_file = (File_mat *)calloc(1,sizeof(File_mat));
	mat_file->file_name = file_name;
	FILE *file = fopen(mat_file->file_name,"r");
	if(file == NULL){
		printf("File of matrix name: %s does not exist!\n",file_name);
		exit(1);
	}
	mat_file->row = 0;
	mat_file->col = 1;
	char current;
	char last ='0';
	bool endline = false;
	bool start = false;
	uint32_t sub_col = 1;
	int line = 0;
	while((current = fgetc(file)) !=  EOF){
		if(current == '\n')
			line++;
		bool sub_endline = false;
		if(!isdigit(current) && !isspace(current) && current != '.'){
			printf("Invalid character in Matrix file!\n");
			printf("In %s, line %d\n", file_name,line);
			exit(1);
		}
		if(isdigit(current)){
			start = true;
		}
		if(current == '\n' && last != '\n' && start){
			mat_file->row++;
			if(!endline && last == ' '){
				mat_file->col--;
			}
			if(endline){
				sub_endline = true;
			}
			endline = true;
			start =false;
		}
		if(current == ' ' && !endline && last != ' ' && start){
			mat_file->col++;
		}
		if(endline && current == ' ' && !sub_endline && start && last != ' '){
			sub_col++;
		}
		if(sub_endline && last == ' '){
			sub_col--;
		}
		if(sub_endline){
			if(sub_col != mat_file->col){
				printf("Invalid matrix file!\n");
				printf("In %s, line %d\n", file_name,line);
				exit(1);
			}
			sub_col = 1;
		}
		last = current;
	}
	if(mat_file->row == 0 || mat_file->col == 0){
		printf("Warning!!! There is problem in the matrix file: %s!!!\n",file_name);
	}
	return mat_file;
}
