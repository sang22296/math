///////////////////////////////////////
//       Author: Sang Nguyen         //
//                                   //
//    email: nqs.dn222@gmail.com     //
//                                   //
//       From Dota2vn with love      //
///////////////////////////////////////


#include "../inc/file_handle.h"

File_mat *get_file(char *file_name){
	File_mat *mat_file = (File_mat *)calloc(1,sizeof(File_mat));
	mat_file->file_name = file_name;
	// These lines were added for fixing "last enter bug"
	FILE *file = fopen(mat_file->file_name,"a+r");
	if(file == NULL){
		printf("File of matrix name: %s does not exist!\n",file_name);
		exit(1);
	}
	fseek(file,0,SEEK_END);
	fseek(file,ftell(file)-1,SEEK_SET);
	if(fgetc(file) != '\n') {
		fprintf(file, "\n");
	}
	fclose(file);
	//
	file = fopen(mat_file->file_name,"r");
	
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
		if(!isdigit(current) && !isspace(current) && current != '.' && current != '-'){
			printf("Invalid character in file!\n");
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
				printf("Invalid file!\n");
				printf("In %s, line %d\n", file_name,line);
				exit(1);
			}
			sub_col = 1;
		}
		last = current;
	}
	if(mat_file->row == 0 || mat_file->col == 0){
		printf("Warning!!! There is problem in the file: %s!!!\n",file_name);
		exit(1);
	}
	return mat_file;
}

void image_to_raw_data(img_info *i_info, const char *file_name) {
	uint32_t h = i_info->height;
	uint32_t w = i_info->width;
	uint32_t n = i_info->bpp;
	unsigned char *data = i_info->img_data;

	FILE *file = fopen(file_name,"w");
	for(int i=0; i < h; i++){
		for(int j=0; j < w; j++){
			for(int k=0; k < n; k++) {
				fprintf(file, "%d", data[i*w*n + j*n + k]);
				fprintf(file, " ");
			}
			fprintf(file, "\n");
		}
	}
	fclose(file);
}
