from ctypes import *

so_file = "share_obj/ML_algo.so"
ML_lib  = CDLL(so_file)

sample_input_file  = "./data/sample_linear_input.mat"
sample_output_file = "./data/sample_linear_output.mat"
input_file         = "./data/input.mat"
weight = ML_lib.linear_regression(sample_input_file,sample_output_file)
ML_lib.display_matrix(ML_lib.apply_linear_rg(weight, input_file))