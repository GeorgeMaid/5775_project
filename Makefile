# How to use:
# 0. Include this file in a Makefile
# 1. Make sure XILINX_VITIS env variable is set.
# 2. Run 'make file.v', where 'file.cpp' exists and 'file' is the name of the top function
# 3. Inspect the result in file_xil_prj

# HW
XILINX_VITIS?=/opt/Xilinx/Vitis/2021.1
XILINX_SETTINGS=$(XILINX_VITIS)/settings64.sh
XILINX_HLS_RUN=source $(XILINX_SETTINGS); vitis_hls
PRJ_STEM=xil_prj

#Part
PART=xczu3eg-sbva484-1-i
#clk PERIOD
PERIOD=10

%_hls_script.tcl:
	@echo "open_project $*_$(PRJ_STEM)" > $@
	@echo "set_top $*" >> $@
	@echo "add_files \"$*.cpp\"" >> $@
	@echo "open_solution "solution1" -flow_target vivado" >> $@
	@echo "set_part {$(PART)}" >> $@
	@echo "create_clock -period $(PERIOD) -name default" >> $@
	@echo "config_export -format ip_catalog -output ./build/iprepo/$*.zip -rtl verilog" >> $@
	@echo "csynth_design" >> $@
	@echo "close_project" >> $@
	@echo "quit" >> $@

%_cosim_script.tcl: ./%_tb.cpp
	@echo "open_project $*_$(PRJ_STEM)" > $@
	@echo "set_top $*" >> $@
	@echo "add_files \"$*.cpp\"" >> $@
	@echo "add_files -tb -cflags \"-I$(shell pwd)/src -Wno-unknown-pragmas\" -csimflags \"-Wno-unknown-pragmas\" \"$<\"" >> $@
	@echo "open_solution "solution1" -flow_target vivado" >> $@
	@echo "set_part {$(PART)}" >> $@
	@echo "create_clock -period $(PERIOD) -name default" >> $@
	@echo "csynth_design" >> $@
	@echo "cosim_design -enable_fifo_sizing -enable_dataflow_profiling -rtl verilog -tool xsim" >> $@
	@echo "close_project" >> $@
	@echo "quit" >> $@


%.v: %_hls_script.tcl %.cpp
	test -f $(XILINX_SETTINGS)
	-rm -rf $*_$(PRJ_STEM)
	$(XILINX_HLS_RUN) -f $<
	-rm -f $@
	touch $@
	for fname in $*_$(PRJ_STEM)/solution1/syn/verilog/*.v; do \
		[ -e "$$fname" ] || continue; cat $$fname >> $@; \
	done
