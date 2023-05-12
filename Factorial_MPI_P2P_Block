#include<iostream>
#include"mpi.h"
using namespace std;
#define TAG 06
int main(int argc, char* argv[])
{
        int size,
                myRank,
                n,
                altLimit,
                ustLimit,
                blokBoyutu,
                faktoriyel=1,
                kismiCarpim=1;

        MPI_Status status;

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

        if (myRank == 0)
        {
                cout << "Faktoriyeli Alinacak Sayiyi Girin: "; cin >> n; cout << endl;

                if (n % size != 0) {
                        cout << "İşlemcilere Eşit veri paylaştırılamıyor" << endl;
                        MPI_Abort(MPI_COMM_WORLD, 06);
                }

                blokBoyutu = n / size;

                altLimit = (myRank * blokBoyutu) + 1;
                ustLimit = (myRank + 1) * blokBoyutu;

                for (int i = 1; i < size; i++)
                        MPI_Send(&n, 1, MPI_INT, i, TAG, MPI_COMM_WORLD);

                for (int i = 1; i < size; i++)
                {
                        MPI_Recv(&kismiCarpim, 1, MPI_INT, i, TAG, MPI_COMM_WORLD, &status);
                        faktoriyel *= kismiCarpim;
                }

                for (int i = altLimit; i <= ustLimit; i++)
                        faktoriyel *= i;

                cout << "Girilen Sayının Faktoriyeli " << faktoriyel << endl;
        }

        else
        {
                MPI_Recv(&n, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD, &status);

                blokBoyutu = n / size;

                altLimit = (myRank * blokBoyutu) + 1;
                ustLimit = (myRank + 1) * blokBoyutu;

                for (int i = altLimit; i <= ustLimit; i++)
                        kismiCarpim *= i;

                MPI_Send(&kismiCarpim, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);

        }

        MPI_Finalize();
        return 0;
}
