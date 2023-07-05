#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<sys/time.h> // timeval
using namespace std;

int ArrayMax(int *, int);
void ArrayPrint(int[], int);

int main(int argc, char* argv[])
{
        srand(time(0));

        struct timeval currentTime;

        int diziBoyutu,
            globalMax,
            ustLimit;

        int *diziPtr;

        bool durumArgv1 = true;
        bool durumArgv2 = true;

        double startTime,endTime,elapsedTime;

        if(argc != 3)
        {
                cout<<"Hata... Arguman Sayısı Geçersiz."<<endl;
                exit(1);
        }

        else
        {
          for(int i=0; i<strlen(argv[1]);i++)
                  if(isdigit(argv[1][i])==0)
                  {       durumArgv1 = false;
                          break;
                  }

          for(int i=0;i<strlen(argv[2]);i++)
                  if(isdigit(argv[2][i])==0)
                  {
                          durumArgv2 = false;
                          break;
                  }

          if(durumArgv1==true and durumArgv2==true)
          {

            diziBoyutu = atoi(argv[1]);
            ustLimit = atoi(argv[2]);

            diziPtr = new int[diziBoyutu];

            for(int i=0; i<diziBoyutu; i++)
                    diziPtr[i] = rand()%ustLimit;

            ArrayPrint(diziPtr,diziBoyutu);

            gettimeofday(&currentTime,NULL);
            startTime = currentTime.tv_sec+(currentTime.tv_usec/1000000.0);

            globalMax = ArrayMax(diziPtr,diziBoyutu);

            gettimeofday(&currentTime,NULL);
            endTime = currentTime.tv_sec+(currentTime.tv_usec/1000000.0);

            elapsedTime = endTime - startTime;

            cout<<"Dizinin En buyuk Elemanini Bulmak Icin Gecen Sure: "<<elapsedTime<<endl;

            cout<<"Dizinin En Buyuk Elemani: "<<globalMax;

            delete[] diziPtr;
          }
          else
                  cout<<"Argumanlar Tam sayi olmalıdır"<<endl;
      }
}

int ArrayMax(int *dizi, int boyut)
{
        int enBuyuk = dizi[0];
        for(int i=0;i<boyut;i++)
                if(dizi[i]>enBuyuk)
                        enBuyuk = dizi[i];
        return enBuyuk;
}

void ArrayPrint(int dizi[],int boyut)
{
        for(int i=0; i<boyut; i++)
                cout<<dizi[i]<<" ";
        cout<<endl;
}
