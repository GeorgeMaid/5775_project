#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/gpm58/5775_project/mvecmult_xil_prj/solution1/.autopilot/db/a.g.bc ${1+"$@"}
