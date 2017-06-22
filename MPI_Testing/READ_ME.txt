To compile:

mpicc -c -o  Hello_world_mpi.o Hello_world_mpi.cpp // mpicc can be replaced with "mpicxx" or "mpic++" for C++

Linking to an executable file:

mpicc -o Hello_world_mpi.exe Hello_world_mpi.o  

To run:

mpirun -n 4 Hello_world_mpi.exe

// Please write any updates if this does not work 
