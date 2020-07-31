///////////////////////////////////////
//       Author: Sang Nguyen         //
//                                   //
//    email: nqs.dn222@gmail.com     //
//                                   //
//       From Dota2vn with love      //
///////////////////////////////////////


#ifndef FILE_HANDLE
#define FILE_HANDLE

#include "common.h"

//Read a file and return the information of that file as type File_mat
File_mat *get_file(char *file_name);
void image_to_raw_data(img_info *i_info, const char *file_name);

#endif // FILE_HANDLE