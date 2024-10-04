# command to generate all executables
all: vmsim_out vmgen_out vmstats_out

vmsim_out: vmsim.c sim_eng.c
	gcc vmsim.c sim_eng.c -o vmsim_out

vmgen_out: vmgen.c
	gcc vmgen.c -o vmgen_out

vmstats_out: vmstats.c sim_eng.c
	gcc vmstats.c sim_eng.c -o vmstats_out

# Command to delete all generated output files
clean:
	rm -f vmsim_out vmgen_out vmstats_out vmrates.dat vmrefs.dat