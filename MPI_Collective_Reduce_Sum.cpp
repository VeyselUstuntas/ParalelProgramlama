#include<iostream>
#include<cstdio>
#include"mpi.h"
using namespace std;
//MPI_Collective_Reduce

#define SIZE 3
int main(int argc, char* argv[])
{
        int size,
                myRank,
                root;

        int* bufferPtr,
                * sumPtr;

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
        sumPtr = new int[SIZE];

        for (int i = 0; i < SIZE; i++)
                bufferPtr[i] = myRank * i;

        for (int i = 0; i < SIZE; i++)
                sumPtr[i] = 0;

        printf("myRank = %d Reduce ONCESİ sumPtr icerigi %d %d %d\n",myRank,sumPtr[0], sumPtr[1], sumPtr[2]);

        MPI_Reduce(bufferPtr, sumPtr,SIZE, MPI_INT, MPI_SUM,root, MPI_COMM_WORLD);

        printf("\n");

        printf("myRank = %d Reduce SONRASI sumPtr icerigi %d %d %d\n", myRank, sumPtr[0], sumPtr[1], sumPtr[2]);

        delete[]sumPtr;
        delete[]bufferPtr;

        MPI_Finalize();

        return 0;
}
