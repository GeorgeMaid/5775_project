open_project -reset mvecmult_xil_prj
set_top mvecmult
add_files mvecmult.cpp
add_files -tb mvecmult_tb.cpp
open_solution "solution1"
set_part xc7z020clg484-1
create_clock -period 10 
csim_design
csynth_design
cosim_design
export_design
exit