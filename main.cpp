#include <iostream>
#include<ctime>
#include "mpi.h"
#include "omp.h"


int main(int argc, char* argv[]){
	int numThreads=1;
	int pRank, total;

	for (int i = 0; i < argc; i++){
		if (strncmp(argv[i], "--threads", 9) == 0){
			numThreads = atoi(argv[i + 1]);
			break;
		}
	}

	omp_set_num_threads(numThreads);
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &total);
	MPI_Comm_rank(MPI_COMM_WORLD, &pRank);
	//std::cout << "Total processes=" << total << std::endl;
#pragma omp parallel for private(i)
	for (int i = 0; i < omp_get_max_threads(); ++i) {
		int tRank = omp_get_thread_num();
		srand((i+ 1) * (pRank + 1) * time(NULL));
		int num = rand() % 1000;
		std::cout << "I am " << i << " thread from " << pRank << " process, my random number = " << num << std::endl;
	}
	MPI_Finalize();
}


