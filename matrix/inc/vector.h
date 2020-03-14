///////////////////////////////////////
//       Author: Sang Nguyen         //
//                                   //
//    email: nqs.dn222@gmail.com     //
//                                   //
//       From Dota2vn with love      //
///////////////////////////////////////


#ifndef __VECLIB__
#define __VECLIB__

#include "matrix.h"

/* Vecotr basically is a matrix with 1 row or 1 collum*/
typedef Matrix Vector;
typedef File_mat File_vec;

typedef enum {
	COL = 0,
	ROW,
	MATRIX,
	ERROR_TYPE
} Vector_type;

// Check if Vector is a row or a collum of data
Vector_type check_vector(Vector *A);

// return the length of Vector
// return NULL if the input is invalid
uint32_t vector_length(Vector *A);

// get the element base on the passing index
// return length 0 for any error
double get_element(Vector *A, uint32_t idx);

// Check if the Vector is a unit Vector
// return true if input Vector is a unit vector
// vice versa, return false
bool is_unit_vetor(Vector *A);

// free the input Vector
void free_vector(Vector *A);

// return a tranpose vector of the input vector
Vector *transpose_vector(Vector *A);

// take a subset of the input Vector
Vector *sub_vector(Vector *A, uint32_t from, uint32_t to);

// init a Vector from a File_vec object
Vector *init_vector(File_vec *A);

// write the Vector to a file
void write_vector(Vector *A, char *file_name);

// print the input Vector to stdout
void display_vector(Vector *A);

#endif