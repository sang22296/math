from ctypes import *

so_file = "./share_obj/mathlib.so"
matlib  = CDLL(so_file)

VER = False
HOR = True


data_info = matlib.get_file("./mat_files/data.mat")
total_input = matlib.init_matrix(data_info)

expect_input = matlib.sub_matrix(total_input,1,matlib.file_getrow(data_info),4,6)
data = matlib.transpose_matrix(expect_input)
line = matlib.get_line(total_input,7,VER)
output_data = matlib.transpose_matrix(line)
matlib.free_mat(total_input)

data_t = matlib.transpose_matrix(data)
output_data_t = matlib.transpose_matrix(output_data)
one_bar = matlib.ones(matlib.mat_getrow(data_t),VER)
Xbar = matlib.concatenate_mat(one_bar,data_t,HOR)

Xbar_t = matlib.transpose_matrix(Xbar)
A = matlib.mul_matrix(Xbar_t,Xbar)
b = matlib.mul_matrix(Xbar_t,output_data_t)

w = matlib.mul_matrix(matlib.inv_mat(A),b)

print("A = ")
matlib.display_matrix(A)
print("b = ")
matlib.display_matrix(b)

print("w = inv(A).b =")
matlib.display_matrix(w)

f = matlib.get_file("./mat_files/input.mat")
i = matlib.init_matrix(f)
input = matlib.transpose_matrix(i)
matlib.free_mat(i)
one = matlib.ones(matlib.mat_getrow(input),VER)
output_mat1 = matlib.concatenate_mat(one,input,HOR)
matlib.free_mat(one)
output_mat2 = matlib.mul_matrix(output_mat1,w)
output_mat = matlib.transpose_matrix(output_mat2)
matlib.free_mat(output_mat1)
matlib.free_mat(output_mat2)
print("Output data:")
matlib.display_matrix(output_mat)

matlib.free_mat(output_data)
matlib.free_mat(data)
matlib.free_mat(A)
matlib.free(b)
matlib.free_mat(w)
matlib.free_mat(output_mat)
matlib.free_mat(output_data_t)
matlib.free_mat(input)
matlib.free_mat(Xbar)
matlib.free(f)