#include<iostream>
#include"mpi.h"

using namespace std;

int main(int argc, char* argv[])
{
	int size,
		myRank,
		n,
		faktoriyel = 1,
		kismiCarpim = 1;

	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

	if (myRank == 0)
	{
		cout << "Faktoriyeli Alinacak Sayi: "; cin >> n; cout << endl;

		for (int i = myRank + 1; i <= n; i+=size)
			faktoriyel *= i;

		for (int i = 1; i < size; i++)
			MPI_Send(&n, 1, MPI_INT, i, 06, MPI_COMM_WORLD);

		for (int i = 1; i < size; i++)
		{
			MPI_Recv(&kismiCarpim, 1, MPI_INT, i, 07, MPI_COMM_WORLD, &status);
			faktoriyel *= kismiCarpim;
		}
		cout << "Girilen sayının faktoriyeli: " << faktoriyel << endl;
	}
	else
	{
		MPI_Recv(&n, 1, MPI_INT, 0, 06, MPI_COMM_WORLD, &status);

		for (int i = myRank + 1; i <= n; i += size)
			kismiCarpim *= i;

		MPI_Send(&kismiCarpim, 1, MPI_INT, 0, 07, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
