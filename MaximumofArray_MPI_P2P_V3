#include<iostream>
#include<ctime>
#include<cstdlib>
#include"mpi.h"
using namespace std;

#define TAG 06

int MaximumArray(int*, int);
void PrintArray(int*, int);

int main(int argc, char* argv[])
{
        srand(time(0));

        int size,
                myRank,
                diziBoyutu,
                kismiBoyut,
                kismiBoyutSon,
                globalMax,
                lokalMax;

        int* diziPtr,
                * kismiDiziPtr;

        MPI_Status status;

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

        if (myRank == 0)
        {
                cout << "Dinamik Dizi Boyutunu Girin: "; cin >> diziBoyutu; cout << endl;

                diziPtr = new int[diziBoyutu];

                for (int i = 0; i < diziBoyutu; i++)
                        diziPtr[i] = rand() % 2023;

                PrintArray(diziPtr, diziBoyutu);

                kismiBoyut = diziBoyutu / size;
                kismiBoyutSon = (diziBoyutu / size) + (diziBoyutu % size);

                for (int i = 1; i < size - 1; i++)
                        MPI_Send(&kismiBoyut, 1, MPI_INT, i, TAG, MPI_COMM_WORLD);

                MPI_Send(&kismiBoyutSon, 1, MPI_INT, (size - 1), TAG, MPI_COMM_WORLD);

                for (int i = 1; i < size - 1; i++)
                        MPI_Send(&diziPtr[i * kismiBoyut], kismiBoyut, MPI_INT, i, TAG, MPI_COMM_WORLD);

                MPI_Send(&diziPtr[ (size-1)* kismiBoyut], kismiBoyutSon, MPI_INT, (size-1), TAG, MPI_COMM_WORLD);

                globalMax = MaximumArray(diziPtr, kismiBoyut);

                for (int i = 1; i < size; i++)
                {
                        MPI_Recv(&lokalMax, 1, MPI_INT, i, TAG, MPI_COMM_WORLD, &status);

                        if (lokalMax > globalMax)
                                globalMax = lokalMax;
                }
                cout << "Dizinin En Buyuk Elemani: " << globalMax << endl;
                delete[] diziPtr;
        }
        else
        {
                MPI_Recv(&kismiBoyut, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD, &status);

                kismiDiziPtr = new int[kismiBoyut];

                MPI_Recv(kismiDiziPtr, kismiBoyut, MPI_INT, 0, TAG, MPI_COMM_WORLD, &status);

                lokalMax = MaximumArray(kismiDiziPtr, kismiBoyut);

                if(myRank == 2)
                {
                        printf("myrank 2\t");
                        PrintArray(kismiDiziPtr,kismiBoyut);
                }


                if(myRank == size-1)
                {
                        printf("son bilgisayar\t");
                        PrintArray(kismiDiziPtr,kismiBoyut);
                }

                MPI_Send(&lokalMax, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);

                delete[] kismiDiziPtr;

        }
        MPI_Finalize();
        return 0;
}

int MaximumArray(int*dizi, int boyut)
{
        int enBuyuk = dizi[0];
        for (int i = 1; i < boyut; i++)
                if (dizi[i] > enBuyuk)
                        enBuyuk = dizi[i];
        return enBuyuk;
}

void PrintArray(int* dizi, int boyut)
{
        for (int i = 0; i < boyut; i++)
                cout << dizi[i] << " ";
        cout << endl;
}
