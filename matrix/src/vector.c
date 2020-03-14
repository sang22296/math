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
		return ERROR_TYPE;
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