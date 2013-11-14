#include "mpi.h"
#include <stdio.h>

int main(argc,argv) 
int argc;
char *argv[];  {
int numtasks, rank, dest, source, rc, count, tag=1;  
char inmsg, outmsg='x';
MPI_Status Stat;
int x[4] = {-1,0,1,2};
int ind[5] = {1,1,1,1,1};
int rez[4];
int i;

MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

if (rank == 0) {
  dest = 1;
  for (i = 0; i < 4; i++)
  {
	rez[i] = ind[0] * x[i];
	rc = MPI_Send(&rez[i], 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
	}
 } 

else if (rank == numtasks - 1) {
  source = rank - 1;
  printf("Final result: \n");
  for (i = 0; i < 4; i++)
  {
	rc = MPI_Recv(&rez[i], 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	printf("%d \n", rez[i] + ind[rank]);
}
  } else {
	  dest = rank + 1;
	  source = rank - 1;
	  for (i = 0; i < 4; i++)
	  {
		  rc = MPI_Recv(&rez[i], 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
		rez[i] = (rez[i] + ind[rank]) * x[i];
		rc = MPI_Send(&rez[i], 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
	}
  }

MPI_Finalize();
}
