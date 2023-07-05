#include<iostream>
#include<cstdio>
#include"mpi.h"
using namespace std;
//MPI_Collective_Broadcast

#define SIZE 5
int main(int argc, char* argv[])
{
	int size,
		myRank,
		root;

	int* bufferPtr;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (myRank == 0)
	{
		cout << "Lütfen bir Broadcast Yapılacak Rank Girin:"; cin >> root; cout << endl;

		if (root < 0 || root >= size)
		{
			cout << "Girilen Rank Geçersiz..." << endl;
			MPI_Abort(MPI_COMM_WORLD, 99);
		}
	}

	MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);

	bufferPtr = new int[SIZE];

	for (int i = 0; i < SIZE; i++)
		bufferPtr[i] = myRank * i;

	printf("myRank = %d Broadcast ÖNCESİ dizi İçeriği %d %d %d %d %d\n", myRank, bufferPtr[0], bufferPtr[1], bufferPtr[2], bufferPtr[3], bufferPtr[4]);

	MPI_Bcast(bufferPtr, SIZE, MPI_INT, root, MPI_COMM_WORLD);

	printf("myRank = %d Broadcast SONRASI dizi İçeriği %d %d %d %d %d\n", myRank, bufferPtr[0], bufferPtr[1], bufferPtr[2], bufferPtr[3], bufferPtr[4]);

	delete[] bufferPtr;

	MPI_Finalize();

	return 0;
}
