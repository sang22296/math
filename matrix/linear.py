from ctypes import *

so_file = "./share_obj/linear_rg.so"
lr_lib  = CDLL(so_file)

sample_input_file  = "./mat_files/sample_input.mat"
sample_output_file = "./mat_files/sample_output.mat"
input_file         = "./mat_files/input.mat"
weight = lr_lib.linear_regression(sample_input_file,sample_output_file)
lr_lib.apply_linear_rg(weight, input_file)