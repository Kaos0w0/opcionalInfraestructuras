secuencial: compile_sec
	./secuencial/func

compile_sec:
	gcc -o ./secuencial/func ./secuencial/func.c

pthreads_2: compile_pthreads
	./pthreads/hilos 2

pthreads_4: compile_pthreads
	./pthreads/hilos 4

pthreads_8: compile_pthreads
	./pthreads/hilos 8

compile_pthreads:
	gcc -o ./pthreads/hilos ./pthreads/hilos.c -pthread

openmp_static_2: compile_openMP
	./openmp/openmp 1 2

openmp_static_4: compile_openMP
	./openmp/openmp 1 4

openmp_static_8: compile_openMP
	./openmp/openmp 1 8

openmp_dinamic_2: compile_openMP
	./openmp/openmp 2 2

openmp_dinamic_4: compile_openMP
	./openmp/openmp 2 4

openmp_dinamic_8: compile_openMP
	./openmp/openmp 2 8

compile_openMP:
	gcc -o ./openmp/openmp ./openmp/openmp.c -fopenmp