
#include <stdio.h>
#include <stdlib.h>


//COLORI NELLA MATRICE
#define BOLDRED      "\033[1m\033[41m"      /* Red */
#define BOLDGREEN    "\033[1m\033[42m"      /* Green */
#define BOLDWHITE    "\033[1m\033[47m"      /* White */
#define RESET   	 "\x1b[0m"


int mosse=0;


int** Crea_Matrice(int n,int m);                        //Crea la matrice in modo randomico
void Stampa_Matrice(int **A, int n, int m);             //Stampa la matrice
void Cambia(int** A,int i,int j,char x);                //Cambia, a seconda dei casi, la casella giusta modificandola con il giusto colore (quello diverso dalle due selezionate)
void Risoluzione2x2(int** A,int i,int j);                //Risolve la matrice in sottomatrici 2x2
void U_Orizzontale_4x4(int** A,int i,int j,int m);        //Unisce, e quindi risolve, due matrici 2x2 orizzontalmente
void U_Verticale_4x4(int** A,int i,int j,int m);          //Unisce verticalmente le matrici formate dalla funzione U_Orizzontale_4x4
int Check(int** A,int n,int m);                          //Controlla se l'intera matrice è risolta
void Risoluzione_Matrice(int** A,int n,int m);            //Gestisce l'algoritmo per la risoluzioni delle matrici




int **Crea_Matrice(int n, int m)
{
    srand(time(NULL));

	int i,j;
	int **A;
	A = (int **) malloc (n * (sizeof(int*)));
	for(i=0; i<n; i++)
    {
		A[i] = (int *) malloc (m * (sizeof(int)));
		for(j=0; j<m; j++)
		{
			A[i][j] = rand()%3;
		}
	}
	return A;
}



void Stampa_Matrice(int **A, int n, int m)
{
	int i,j;

	printf("  ");

	for(i=0; i<m;i++)
        printf(" %d",i);

    printf("\n");
	for(i=0; i<n; i++)
    {
		printf("%d ",i);
		for(j=0; j<m; j++)
        {
			switch(A[i][j])
			{
				case 0:
					printf(BOLDRED"  "RESET);
					break;
				case 1:
					printf(BOLDGREEN"  "RESET);
					break;
				case 2:
					printf(BOLDWHITE"  "RESET);
					break;
			}
		}
       printf("\n");
	}
}


//I cambi ovest e nord sono inutilizzati, dato che basta considerare i casi est e sud
void Cambia(int** A,int i,int j,char x)
{
    int mossa=0;

    switch(x)
    {
        //Modifico la casella corrente e quella ad EST
        case 'e':

          if(A[i][j]!=A[i][j+1])
          {
               mosse++;
                if(A[i][j]+A[i][j+1]==1)
                {
                    A[i][j]=2;
                    A[i][j+1]=2;
                }
                if(A[i][j]+A[i][j+1]==2)
                {
                    A[i][j]=1;
                    A[i][j+1]=1;
                }
                if(A[i][j]+A[i][j+1]==3)
                {
                    A[i][j]=0;
                    A[i][j+1]=0;
                }
          }
        break;
         //Modifico la casella corrente e quella a NORD
        case 'n':

              if(A[i][j]!=A[i-1][j])
              {

                    mosse++;
                    if(A[i][j]+A[i-1][j]==1)
                    {
                        A[i][j]=2;
                        A[i-1][j]=2;
                    }
                    if(A[i][j]+A[i-1][j]==2)
                    {
                        A[i][j]=1;
                        A[i-1][j]=1;
                    }
                    if(A[i][j]+A[i-1][j]==3)
                    {
                        A[i][j]=0;
                        A[i-1][j]=0;
                    }
              }
        break;
         //Modifico la casella corrente e quella ad OVEST
        case 'o':

              if(A[i][j]!=A[i][j-1])
              {
                 mosse++;
                    if(A[i][j]+A[i][j-1]==1)
                    {
                        A[i][j]=2;
                        A[i][j-1]=2;
                    }
                    if(A[i][j]+A[i][j-1]==2)
                    {
                        A[i][j]=1;
                        A[i][j-1]=1;
                    }
                    if(A[i][j]+A[i][j-1]==3)
                    {
                        A[i][j]=0;
                        A[i][j-1]=0;
                    }
               }
        break;
         //Modifico la casella corrente e quella a SUD
        case 's':

            if(A[i][j]!=A[i+1][j])
            {
                 mosse++;
                if(A[i][j]+A[i+1][j]==1)
                {
                    A[i][j]=2;
                    A[i+1][j]=2;
                }
                if(A[i][j]+A[i+1][j]==2)
                {
                    A[i][j]=1;
                    A[i+1][j]=1;
                }
                if(A[i][j]+A[i+1][j]==3)
                {
                    A[i][j]=0;
                    A[i+1][j]=0;
                }
            }
        break;
    }

}

//Data una matrice 2x2 questo algoritmo la risolve in massimo 4 passaggi
void Risoluzione2x2(int** A,int i,int j)
{

            Cambia(A,i,j,'e');
            Cambia(A,i+1,j,'e');
            Cambia(A,i,j,'s');
            Cambia(A,i,j+1,'s');

}

void U_Orizzontale_4x4(int** A,int i,int j,int m)
{
    int k;
//      printf("Inizio Unisci in orizzontale da i=%d j=%d\n",i,j);
      Cambia(A,i,j+1,'e');
      Cambia(A,i,j,'e');
      Cambia(A,i,j+2,'e');
      for(k=0;k<m;k++)
      {
         Cambia(A,i,k,'s');
      }

}


void U_Verticale_4x4(int** A,int i,int j,int m)
{
    int k,x=0;
 //    printf("Inizio Unisci in verticale, i=%d j=%d\n",i,j);


      Cambia(A,i+1,j,'s');
      Cambia(A,i,j,'s');
      Cambia(A,i+2,j,'s');

      for(k=0;k<m;k++)    //primo elemento prima colonna e spennello a destra poi scorro giu spennello a destra e cosi via
      {
          Cambia(A,k,j,'e');
      }


}

int Check(int** A,int n,int m)
{
    int num,i,j;
     num=A[0][0];

           for(i=0;i<n;i++)
           {
                for(j=0;j<m;j++)
                {
                   if(A[i][j]!=num)
                       return 0;

                }
            }

            return 1;
}






void Risoluzione_Matrice(int** A,int n,int m)
{
     int i,j,num,esci=0;

            for(i=0;i<n;i=i+2)
            {
                for(j=0;j<m;j=j+2)
                {
                   Risoluzione2x2(A,i,j);          //Risolvo la matrice in sottomatrici 2x2
                }
            }

//             Stampa_Matrice(A,n,m);


           int Risolta=Check(A,n,m);

      if(Risolta==1)
      printf("\n\nL'algoritmo ha risolto il gioco");
      else                            //Matrice 4x4 oppure 8x8
      {
                           for(i=0;i<n;i=i+2)
                           {
                                 for(j=0;j<m;j=j+(m/2))
                                 {
                                    U_Orizzontale_4x4(A,i,j,m);   //Unisco in modo orizzontale le matrici 2x2 per averne due 2x4 uguali
                                 }
                            }

 //                          Stampa_Matrice(A,n,m);


                                 for(i=0;i<n;i=i+4)
                                 {
                                   for(j=0;j<m;j=j+2)
                                          U_Verticale_4x4(A,i,j,m);  //Unisco le matrici 2x4 per formarne una 4x4
                                 }


//                                      Stampa_Matrice(A,n,m);

                                  Risolta=Check(A,n,m);

                                  if(Risolta==1)
                                      printf("\n\nL'algoritmo ha risolto il gioco");
                                  else                         //Matrice 8x8
                                  {
                                      for(i=0;i<n;i=i+2)
                                      {
                                            U_Orizzontale_4x4(A,i,2,m);
                                            U_Orizzontale_4x4(A,i,0,m);
                                            U_Orizzontale_4x4(A,i,2,m);
                                            U_Orizzontale_4x4(A,i,0,m);
                                            U_Orizzontale_4x4(A,i,4,m);
                                      }

                                       for(j=0;j<n;j=j+2)
                                       {
                                            U_Verticale_4x4(A,2,j,m);
                                            U_Verticale_4x4(A,0,j,m);
                                            U_Verticale_4x4(A,2,j,m);
                                            U_Verticale_4x4(A,0,j,m);
                                            U_Verticale_4x4(A,4,j,m);
                                       }

                                       printf("\n\nL'algoritmo ha risolto il gioco");

                                  }

      }

}



int main()
{
    int n,m;
	int **A;
    char risposta;

    do
    {

             printf("\t\t\t\t\t   Gioco Colori \n\n");
             printf("\t\t\t\tRisoluzione matrici 2x2,4x4,8x8\n\t\t\t\t\t Minieri Maurizio\n\n");
             printf("Scrivi n & m : ");
             scanf("%d",&n);
             m = n;
    }
    while((n!=2&&n!=4&&n!=8)&&printf("Errore,n & m non validi\n"));




    system("cls");
    printf("\t\t\t\t\t   Gioco Colori \n\n");
    printf("\t\t\t\tRisoluzione matrici 2x2,4x4,8x8\n\t\t\t\t\t Minieri Maurizio\n\n");
    printf(": Matrice %dx%d\n\n",n,m);
    A = Crea_Matrice(n,m);
    Stampa_Matrice(A,n,m);



          Risoluzione_Matrice(A,n,m);
          printf("\n\nStampa\n\n");
          Stampa_Matrice(A,n,m);
          printf("\n\nMOSSE = %d\n\n",mosse);

    system("PAUSE");
	return 0;
}
