#include<iostream>
#include<mpi.h>
#include<ctime>
#include<cstdlib>
using namespace std;

#define TAG 06

void PrintArray(int*, int);
int MaximumArray(int *, int);

int main(int argc, char* argv[])
{
        srand(time(0));

        int size,
            myRank,
            diziBoyutu,
            kismiBoyut,
            lokalMax,
            globalMax;

        int *diziPtr,
            *kismiDiziPtr;

        MPI_Status status;

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD,&size);
        MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

        if(myRank == 0)
        {
                cout<<"Dinamik Dizi Boyutunu Girin: "; cin>> diziBoyutu; cout<<endl;

                if(diziBoyutu % size !=0)
                {
                        cout<<"Veriler Islemcilere Esit Olarak Paylastirilamiyor."<<endl;
                        MPI_Abort(MPI_COMM_WORLD,99);
                }

                diziPtr = new int[diziBoyutu];

                for(int i = 0; i<diziBoyutu;i++)
                        diziPtr[i] = rand()%2023;

                PrintArray(diziPtr,diziBoyutu);

                kismiBoyut = diziBoyutu/size;

                for(int i = 1; i<size; i++)
                        MPI_Send(&kismiBoyut,1,MPI_INT,i,TAG,MPI_COMM_WORLD);

                for(int i=1; i<size; i++)
                        MPI_Send(&diziPtr[i*kismiBoyut],kismiBoyut,MPI_INT,i,TAG,MPI_COMM_WORLD);

                globalMax = MaximumArray(diziPtr,kismiBoyut);

                for(int i = 1; i<size; i++)
                {
                        MPI_Recv(&lokalMax,1,MPI_INT,i,TAG,MPI_COMM_WORLD,&status);
                        if(lokalMax>globalMax)
                                globalMax = lokalMax;
                }
                cout<<"Dinamik Dizideki En Buyuk Eleman: "<<globalMax<<endl;

                delete [] diziPtr;

        }
        else
        {
                MPI_Recv(&kismiBoyut,1,MPI_INT,0,TAG,MPI_COMM_WORLD,&status);

                kismiDiziPtr = new int[kismiBoyut];

                MPI_Recv(kismiDiziPtr,kismiBoyut,MPI_INT,0,TAG,MPI_COMM_WORLD,&status);

                lokalMax = MaximumArray(kismiDiziPtr,kismiBoyut);

                MPI_Send(&lokalMax,1,MPI_INT,0,TAG,MPI_COMM_WORLD);

                delete [] kismiDiziPtr;
        }

        MPI_Finalize();

        return 0;
}

int MaximumArray(int *dizi, int boyut)
{
        int enBuyuk = dizi[0];
        for(int i=0; i<boyut; i++)
                if(dizi[i]>enBuyuk)
                        enBuyuk = dizi[i];
        return enBuyuk;
}

void PrintArray(int *dizi, int boyut)
{
        for(int i=0; i<boyut; i++)
                cout<<dizi[i]<<" ";
        cout<<"\n";
}
