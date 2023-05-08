#include<iostream>
#include"mpi.h"
#include<ctime>
#include<cstdio>
#include<cstdlib>
using namespace std;

int FindMaximum(int*, int);
void PrintArray(int*, int);


int main(int argc, char* argv[])
{
    srand((time(0)));

    int sizee,
        myRank,
        diziBoyutu,
        kismiBoyut,
        lokalMaksimum,
        globalMaksimum;

    int* diziPtr,
        * kismiDiziPtr,
        * lokalMaksimumlarPtr;


    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &sizee);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    MPI_Status status;

    if (myRank == 0)
    {
        cout << "Dizi Boyutunu Girin: "; cin >> diziBoyutu; cout << endl;

        if (diziBoyutu % (sizee - 1) == 0)
        {
            diziPtr = new int[diziBoyutu];

            for (int i = 0; i < diziBoyutu; i++)
                diziPtr[i] = rand() % 2023;

            PrintArray(diziPtr, diziBoyutu);

            kismiBoyut = diziBoyutu / (sizee - 1);

            for (int i = 1; i < sizee; i++)
                MPI_Send(&kismiBoyut, 1, MPI_INT, i, 25, MPI_COMM_WORLD);

            for (int i = 1; i < sizee; i++)
                MPI_Send(&diziPtr[(i - 1) * kismiBoyut], kismiBoyut, MPI_INT, i, 33, MPI_COMM_WORLD);

            lokalMaksimumlarPtr = new int[sizee - 1];

            for (int i = 1; i < sizee; i++)
            {
                MPI_Recv(&lokalMaksimum, 1, MPI_INT, i, 06, MPI_COMM_WORLD, &status);

                lokalMaksimumlarPtr[i - 1] = lokalMaksimum;

            }
            globalMaksimum = FindMaximum(lokalMaksimumlarPtr, sizee - 1);

            cout << "En Buyuk Dizi Elemani: " << globalMaksimum << endl;

            delete[] lokalMaksimumlarPtr;
            delete[] diziPtr;
        }
        else
        {
            cout << "Veriler Ýþlemcilere Tam Paylaþtýrýlamaýyor" << endl;
            MPI_Abort(MPI_COMM_WORLD, 99);
        }
    }
    else
    {
        MPI_Recv(&kismiBoyut, 1, MPI_INT, 0, 25, MPI_COMM_WORLD, &status);

        kismiDiziPtr = new int[kismiBoyut];

        MPI_Recv(kismiDiziPtr, kismiBoyut, MPI_INT, 0, 33, MPI_COMM_WORLD, &status);

        printf("My rank is %d ve kismiDizimin 0 indisli Elemani %d\n", myRank, kismiDiziPtr[0]);

        lokalMaksimum = FindMaximum(kismiDiziPtr, kismiBoyut);

        MPI_Send(&lokalMaksimum, 1, MPI_INT, 0, 06, MPI_COMM_WORLD);

        delete[] kismiDiziPtr;
    }

    MPI_Finalize();
    return 0;
}

int FindMaximum(int* dizi, int boyut)
{
    int enBuyuk = dizi[0];
    for (int i = 1; i < boyut; i++)
        if (enBuyuk < dizi[i])
            enBuyuk = dizi[i];
    return enBuyuk;
}

void PrintArray(int* dizi, int boyut)
{
    for (int i = 0; i < boyut; i++)
        cout << dizi[i] << " ";
    cout << endl << endl;
}