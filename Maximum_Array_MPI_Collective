#include<iostream>
#include<mpi.h>
#include<cstdlib>
#include<ctime>

using namespace std;

int ArrayMaximum(int*, int);
void PrintArray(int*, int);

int main(int argc, char* argv[])
{
	srand(time(0));

	int size,
		myRank,
		diziBoyutu,
		globalMax,
		lokalMax,
		kismiBoyut;
		

	int* diziPtr,
		* parcaDiziler;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);


	if (myRank == 0)
	{
		cout << "Dinamik Dizi Boyutnu Girin: "; cin >> diziBoyutu; cout << endl;

		if (diziBoyutu % size == 0)
		{
			diziPtr = new int[diziBoyutu];
			for (int i = 0; i < diziBoyutu; i++)
				diziPtr[i] = rand() % 2023;
			PrintArray(diziPtr, diziBoyutu);
		}
		else
		{
			cout << "Veriler Eşit Olarak Paylaştırılamıyor\n";
			MPI_Abort(MPI_COMM_WORLD, 99);
		}
	}

	MPI_Bcast(&diziBoyutu, 1, MPI_INT, 0, MPI_COMM_WORLD);

	kismiBoyut = diziBoyutu / size;

	parcaDiziler = new int[kismiBoyut];

	MPI_Scatter(diziPtr, kismiBoyut, MPI_INT, parcaDiziler, kismiBoyut, MPI_INT, 0, MPI_COMM_WORLD);

	if (myRank == 2)
		for (int i = 0; i < kismiBoyut; i++)
			cout << parcaDiziler[i] << " ";
	cout << endl;

	lokalMax = ArrayMaximum(parcaDiziler, kismiBoyut);

	MPI_Reduce(&lokalMax, &globalMax, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (myRank == 0)
	{
		cout << "Dinamik dizinin en Buyuk elemani: " << globalMax << endl;
		delete[] diziPtr;
	}

	delete[]parcaDiziler;

	MPI_Finalize();

	return 0;
}

int ArrayMaximum(int* dizi, int boyut)
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
