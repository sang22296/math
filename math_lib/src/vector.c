///////////////////////////////////////
//       Author: Sang Nguyen         //
//                                   //
//    email: nqs.dn222@gmail.com     //
//                                   //
//       From Dota2vn with love      //
///////////////////////////////////////


#include "../inc/vector.h"

Vector_type check_vector(Vector *A) {
	if(A->row != 1 && A->col != 1 && A->row != 0 && A->col != 0) {
		return MATRIX;
	} else if(A->row == 1 && A->col != 0) {
		return ROW;
	} else if(A->row != 0 && A->col == 1) {
		return COL;
	} else {
		printf("The input is error! Not a vector!\n");
		exit(1);
	}
}

uint32_t vector_length(Vector *A) {
	switch(check_vector(A)) {
		case(ROW):
			return A->col;
			break;
		case(COL):
			return A->row;
			break;
		case(MATRIX):
			printf("The input is a Matrix\n");
			break;
		case(ERROR_TYPE):
			printf("The input is error type\n");
			break;
		default:
			return 0;
			break;
	}
	return 0;
}

double get_element(Vector *A, uint32_t idx) {
	if(idx >= A->row && idx >= A->col) {
		printf("Invalid index for getting element\n");
		exit(1);
	}
	switch(check_vector(A)) {
		case(ROW):
			return A->data[0][idx];
			break;
		case(COL):
			return A->data[idx][0];
			break;
		case(MATRIX):
			printf("The input is a Matrix\n");
			break;
		case(ERROR_TYPE):
			printf("The input is error type\n");
			exit(1);
			break;
		default:
			printf("Cannot recognize the input\n");
			exit(1);
			break;
	}
	printf("Exit get_element(Vector *A, uint32_t idx) function due to error\n");
	exit(1);
}

bool is_unit_vetor(Vector *A) {
	bool first = false;
	double ele;
	for (int i = 0; i < vector_length(A); ++i) {
		if((ele = get_element(A,i)) == 1) {
			if(!first) {
				first = true;
			}
		} else if(ele == 0) {
			continue;
		} else {
			return false;
		}
	}
	if(first) {
		return true;
	} else {
		return false;
	}
}

void free_vector(Vector *A) {
	free_mat(A);
}

Vector *construct_vector(uint32_t length, bool axis) {
	if(axis == ROW) {
		Vector *V = construct_matrix(1,length);
		return V;
	} else if (axis == COL) {
		Vector *V = construct_matrix(length,1);
		return V;
	} else {
		printf("Invalid input for @param: axis\n");
		exit(1);
	}
}

Vector *transpose_vector(Vector *A) {
	return transpose_matrix(A);
}
 
Vector *sub_vector(Vector *A, uint32_t from, uint32_t to) {
	switch(check_vector(A)) {
		case(ROW):
			return sub_matrix(A, 1, 1, from, to);
			break;
		case(COL):
			return sub_matrix(A, from, to, 1, 1);
			break;
		case(MATRIX):
			printf("The input is a Matrix\n");
			break;
		case(ERROR_TYPE):
			printf("The input is error type\n");
			break;
		default:
			return NULL;
			break;
	}
	return NULL;
}

Vector *init_vector(File_vec *A) {
	Vector *V = init_matrix(A);
	switch(check_vector(V)) {
		case(ROW):
			return V;
			break;
		case(COL):
			return V;
			break;
		case(MATRIX):
			printf("The input is a Matrix\n");
			break;
		case(ERROR_TYPE):
			printf("The input is error type\n");
			break;
		default:
			return NULL;
			break;
	}
	return NULL;
}

void write_vector(Vector *A, char *file_name) {
	write_matrix(A,file_name);
}

void display_vector(Vector *A) {
	display_matrix(A);
}

long double norm2(Vector *A, Vector *B) {
	if(vector_length(A) != vector_length(B)) {
		printf("Two Vectors must be have the same length!\n");
		exit(1);
	}
	int A_type = check_vector(A);
	int B_type = check_vector(B);
	long double sum = 0;

	switch(A_type) {
		case(MATRIX):
			printf("First Vector is a Matrix\n");
			exit(1);
		case(ERROR_TYPE):
			printf("The First Vector type is Error\n");
			exit(1);
		}
	switch(B_type){
		case(MATRIX):
			printf("Second Vector is a Matrix\n");
			exit(1);
		case(ERROR_TYPE):
			printf("The First Vector type is Error\n");
			exit(1);
		}

	if(A_type == ROW && B_type == COL) {
		Vector *A_trans = transpose_vector(A);
		for(int i = 0; i < A->row; i++) {
			sum += (B->data[i][0] - A_trans->data[i][0])*(B->data[i][0] - A_trans->data[i][0]);
		}
		free_vector(A_trans);
		return sum;
	}
	else if(A_type == COL && B_type == ROW) {
		Vector *B_trans = transpose_vector(B);
		for(int i = 0; i < A->row; i++) {
			sum += (B_trans->data[i][0] - A->data[i][0])*(B_trans->data[i][0] - A->data[i][0]);
		}
		free_vector(B_trans);
		return sum;
	}
	else if (A_type == ROW && B_type == ROW) {
		for(int i = 0; i < A->col; i++) {
			sum += (B->data[0][i] - A->data[0][i])*(B->data[0][i] - A->data[0][i]);
		}
		return sum;
	}
	else {
		for(int i = 0; i < A->row; i++) {
			sum += (B->data[i][0] - A->data[i][0])*(B->data[i][0] - A->data[i][0]);
		}
		return sum;
	}
	return sum;
}

uint32_t find_onehot(Vector *V) {
	uint32_t len =  vector_length(V);
	bool is_onehot = false;
	uint32_t pos;
	int type = check_vector(V);
	switch(type) {
		case(ROW):
			for(int i=0; i < len; i++) {
				if(V->data[0][i] != 1 && V->data[0][i] != 0) {
					printf("The input is not a one-hot Vector\n");
					display_vector(V);
					exit(1);
				}
				if(!is_onehot && V->data[0][i] == 1) {
					pos = i+1;
					is_onehot = true;
				} else if(is_onehot && V->data[0][i] == 1) {
					printf("The input is not a one-hot Vector\n");
					display_vector(V);
					exit(1);
				} else {
					continue;
				}
			}
			break;
		case(COL):
			for(int i=0; i < len; i++) {
				if(V->data[i][0] != 1 && V->data[i][0] != 0) {
					printf("The input is not a one-hot Vector\n");
					display_vector(V);
					exit(1);
				}
				if(!is_onehot && V->data[i][0] == 1) {
					pos = i+1;
					is_onehot = true;
				} else if(is_onehot && V->data[i][0] == 1) {
					printf("The input is not a one-hot Vector\n");
					display_vector(V);
					exit(1);
				} else {
					continue;
				}
			}
			break;
	}
	if(!is_onehot) {
		printf("The input is not a one-hot Vector\n");
		display_vector(V);
		exit(1);
	}
	return pos;
}

Vector *mid_point(Vector *A, Vector* B) {

	int type_A = check_vector(A);
	int type_B = check_vector(B);

	if(vector_length(A) != vector_length(B)) {
		printf("Two input vectors must be have the same length!\n");
		exit(1);
	}

	Vector *temp_A;
	Vector *temp_B;
	if(type_A == MATRIX || type_B == MATRIX) {
		printf("The input must be a Vector for calculating midpoint\n");
		exit(1);
	}

	if((type_A == type_B) == COL) {
		temp_A = transpose_vector(A);
		temp_B = transpose_vector(B);
	} else if(type_A != type_B) {
		if(type_A == COL) {
			temp_A = transpose_vector(A);
			temp_B = B;
		} else {
			temp_A = A;
			temp_B = transpose_vector(B);
		}
	} else {
		temp_A = A;
		temp_B = B;
	}
	Vector *Mid_point = construct_vector(temp_A->col,ROW);
	for(int i=0; i < temp_A->col; i++) {
		Mid_point->data[0][i] = (temp_A->data[0][i] + temp_B->data[0][i]) / 2;
	}
	free_vector(temp_A);
	free_vector(temp_B);
	return Mid_point;
}
