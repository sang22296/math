///////////////////////////////////////
//       Author: Sang Nguyen         //
//                                   //
//    email: nqs.dn222@gmail.com     //
//                                   //
//       From Dota2vn with love      //
///////////////////////////////////////


#ifndef __MATLIB__

#define __MATLIB__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#define HOR true
#define VER false

typedef struct Matrix {
	uint32_t row;
	uint32_t col;
	double **data;
} Matrix;

typedef struct File_mat {
	uint32_t row;
	uint32_t col;
	char *file_name;
} File_mat;

void free_mat(Matrix *A);

uint32_t mat_getrow(Matrix *A);
uint32_t mat_getcol(Matrix *A);
uint32_t file_getrow(File_mat *A);
uint32_t file_getcol(File_mat *A);

// Create a sub matrix from input matrix A, which coressponding number of rows and collum
Matrix *sub_matrix(Matrix *A, uint32_t r_from, uint32_t r_to, uint32_t c_from, uint32_t c_to);

// Return determinant of given matrix as a double number
double det_mat(Matrix *A);

// Get a row or a collum of Matrix A, line is the order of row or collum, 
//								"axis" decide to get row or collum (true of false)
Matrix *get_line(Matrix *A, uint32_t line, bool axis);

// Return a matrix which is concatenated  from two matrixes A and B, 
//"axis" decide to concatenate by horizontal or vertical direction (true or false)
Matrix *concatenate_mat(Matrix *A, Matrix *B, bool axis);

//Create a matrix with 1 row or 1 collum, 
//	the new 1D matrix contain "num" of elements which equal to 1.
//	"axis" decide if the new 1D matrix is horizontal or vertical (true or false)
Matrix *ones(uint32_t num, bool axis);

//The same as ones(), but only the element at pos equal 1, others equal 0
Matrix *one_hot(uint32_t num, uint32_t pos);

//Check if a matrix is a square matrix
bool is_square(Matrix *A);

//Create a matrix which is minors of given matrix
Matrix *minors_mat(Matrix *A);

//Create a square n*n matrix, all the elements equal +1 or -1
// follow the rule: if sum of row's and collum's index is even, the element equal 1
//				else, it equal -1
//For example a 3x3 matrix:
//	      1  -1   1
//	     -1   1  -1
//	      1  -1   1
Matrix *sign_chart(uint32_t n);

//Create a matrix which is tranpose of matrix A
// (collum (1..n) of A is row (1..n) of return matrix )
Matrix *transpose_matrix(Matrix *A);

//Create a n*n unit matrix
//For example n=3
//    1  0  0
//    0  1..0
//    0  0  1
Matrix* unit_mat(uint32_t n);

//Return a new matrix with all of element is 
//			element of matrix A multifly by factor "n"
Matrix *factor_matrix(Matrix *A, double n);

//Return a new matrix with all elements corresponding to
//		elements in matrix A multifly with element in matrix B
//		(A and B must have the same size)
Matrix *time_matrix(Matrix *A,Matrix *B);

//Multifly two matrixs
Matrix* mul_matrix(Matrix* A, Matrix* B);

//Return the matrix which is invert of the given matrix
Matrix *inv_matrix(Matrix *A);

//Initalize a matrix based on infomation read in a file as type File_mat
Matrix* init_matrix(File_mat *mat_file);

//Write a given matrix into a file as given file name
void write_matrix(Matrix *A,char *file_name);

//Print a matrix
void display_matrix(Matrix *A);

//Read a file and return the information of that file as type File_mat
File_mat *get_file(char *file_name);

#endif