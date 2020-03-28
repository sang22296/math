///////////////////////////////////////
//       Author: Sang Nguyen         //
//                                   //
//    email: nqs.dn222@gmail.com     //
//                                   //
//       From Dota2vn with love      //
///////////////////////////////////////


#include "../inc/kmean_clustering.h"

void init_centers(Matrix *centers) {
/*TO DO*/
	centers->data[0][0] = 150;
	centers->data[0][1] = 0;

	centers->data[1][0] = 160;
	centers->data[1][1] = 0.7;

	centers->data[2][0] = 170;
	centers->data[2][1] = 0.5;
}

bool has_converged(Matrix *new_centers, Matrix *last_centers) {

	if(new_centers->row != last_centers->row ||
	      new_centers->col != last_centers->col ) {
		printf("The 2 input Matrix must be have the same size\n");
		exit(1);
	}

	for(int i=0; i < new_centers->row; i++) {
		for(int j=0; j < new_centers->col; j++) {
			if(new_centers->data[i][j] != last_centers->data[i][j]) {
				return false;
			}
		}
	}

	return true;
}

Matrix *update_label(Matrix *data, Matrix *centers) {

	if(data->col != centers->col) {
		printf("Data and Centers must have the same element size\n");
		exit(1);
	}
	Matrix *labels = construct_matrix(data->row,centers->row);
	long double min_distance = LDBL_MAX;
	long double distance;
	for(int i=0; i < data->row; i++) {
		uint32_t pos;
		Vector *data_ii = get_line(data,i+1,ROW);
		for(int j=0; j < centers->row; j++) {
			Vector *centers_jj = get_line(centers,j+1,ROW);
			distance = norm2(data_ii,centers_jj);
			if(min_distance > distance) {
				min_distance = distance;
				pos = j;
			}
			free_vector(centers_jj);
		}
		labels->data[i][pos] = 1;
		min_distance = LDBL_MAX;
	}

	return labels;

}

Matrix *update_center(Matrix *data, Matrix *labels) {
	Matrix *new_centers      = construct_matrix(labels->col,data->col);
	uint32_t *cluster_count  = (uint32_t *)calloc(labels->col,sizeof(uint32_t));
	uint32_t  pos;
	for(int i=0; i < data->row; i++) {
		Vector *line = get_line(labels,i+1,ROW);
		pos = find_onehot(line);
		for(int j=0; j<new_centers->col; j++) {
			new_centers->data[pos-1][j] += data->data[i][j];
		}
		free_vector(line);
		cluster_count[pos-1]++;
	}

	for(int i=0; i<new_centers->row; i++) {
		if(cluster_count[i] != 0) {
			for(int j=0; j<new_centers->col; j++) {
				new_centers->data[i][j] /= cluster_count[i];
			}
		}
	}
	free(cluster_count);

	return new_centers;
}

Matrix *Kmean_clustering(char *data_file, uint32_t n_clusters) {

	File_mat *data_info  = get_file(data_file);
	Matrix   *data       = init_matrix(data_info);

	Matrix *centers      = construct_matrix(n_clusters,data->col);
	Matrix *last_centers = construct_matrix(n_clusters,data->col);
	Matrix *labels       = construct_matrix(data->row, n_clusters);

	// init center
	printf("Init centers\n");
	init_centers(centers);
	display_vector(centers);

	do {
		// update label
		printf("Update labels\n");
		labels = update_label(data,centers);
		display_vector(labels);
		// update center
		// free_mat(last_centers);
		printf("Last centers\n");
		last_centers = centers;
		display_matrix(last_centers);
		printf("Update centers\n");
		centers = update_center(data,labels);
		display_matrix(centers);
		// has converged ? return:continue
	} while(!has_converged(last_centers,centers));
	return labels;
}