
# First half of makefile is meant for the host PC

# Second half of make is for Zedboard
INC_PATH=/usr/include/vivado_hls
CFLAGS = -I${INC_PATH}

mvecApp: host.cpp
	@echo "Compiling host program & running digitrec accelerator ..."
	g++ ${CFLAGS} host.cpp -o $@

# Clean up the directory before submission
clean:
	@echo "Clean up output files"
	rm -rf mvecApp