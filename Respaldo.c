#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>



int pot( int base, int exp)
{
	if(exp == 0)
	{
		return 1;
	} else
	{
		return base*pot(base, exp-1);
  }
}

int main(int argc, char **argv)
{
	int potencia;

  if (argc < 2)
  {
		printf("por favor especifique el numero\n");
		exit(1);
	}
  sscanf(argv[1], "%i", &potencia);
  int poten = pot(2,potencia);

  printf("El valor de poten: %i\n", poten);

  //int * A = (int*) malloc ((poten/2)*sizeof(int));
  //int * B = (int*) malloc ((poten/2)*sizeof(int));
  //int * C = (int*) malloc ((poten/2)*sizeof(int));
  //int * D = (int*) malloc ((poten/2)*sizeof(int));
	int tam = poten/2;
  printf("Tam: %i\n", tam);
  int An[tam];
  int Bn[tam];
  int Cn[tam];
  int Dn[tam + 1];
  
  srand(time(NULL));

  for (int i=0 ;i < poten; i++)
  {
    An[i] = 0 + rand() % (2);
    Bn[i] = 0 + rand() % (2);
    //printf("%i\n",A[i]);
  }


  for (int i=0 ;i <poten; i++)
  {
    Cn[i] = 0;
    Dn[i] = 0;
  }
//void suma_acarreo(){
  int idHilo;
  omp_set_num_threads(poten);
  #pragma omp parallel shared(idHilo)
  {
    idHilo = omp_get_thread_num();

    if ((An[idHilo] == 1 )&&(Bn[idHilo]==1)){
      Cn[idHilo]=0;
      Dn[idHilo-1] =1;
    }else{
      Cn[idHilo] = An[idHilo] + Bn[idHilo];
    }
  }
	/* revisar esta idea les explico por aqui por que no se quien vera primero esto y lo intentara
	* pense en este caso con la idea que teniamos en el lab que es si la suma es A[1111] + B[1001] = 11000
	*Pero con nuestra idea daria 10010
	*A demas estoy viendo que estamos haciendo mal algo mas al momento de sumar C con D lo saque para ver si la hacia directa y no la hace.
	*aparte deberia siempre imprimirnos el arreglo D en 0 siempre ya que es nuestra clausula de salida sin embargo sale diferente de cero
	*Por lo que veo a lo mucho solo entra una vez al rato le sigo xD
	if ((An[0] == 1 )&&(Bn[0]==1)){
		Cn[0]=1;
		Dn[idHilo-1] =1;
	}else if((An[idHilo] == 1 )&&(Bn[idHilo]==1)){
		Cn[idHilo]=0;
		Dn[idHilo-1] =1;
	}else{
	 Cn[idHilo] = An[idHilo] + Bn[idHilo];
	}
	*/

	//int idHilo;
  /*omp_set_num_threads(poten);
  #pragma omp parallel shared(idHilo)
  {
    idHilo = omp_get_thread_num();

    if ((Cn[idHilo] == 1 )&&(Dn[idHilo]==1)){
      Dn[idHilo] = 0;
			Dn[idHilo] = 1;
      Cn[idHilo]=0;
    }else{
      Cn[idHilo]  += Dn[idHilo];
    }
  }*/

//}


void recursion(){
  int idHilo;
  omp_set_num_threads(poten);
  #pragma omp parallel shared(idHilo)
  {
    idHilo = omp_get_thread_num();

    if ((Cn[idHilo] == 1 )&&(Dn[idHilo]==1)){
			Dn[idHilo] = 0;
			Dn[idHilo-1] = 1;
      Cn[idHilo]=0;
			printf("%i\n",Dn[idHilo]);
			printf("%i\n",Dn[idHilo-1]);
			printf("%i\n",Cn[idHilo]);
    }else{
      Cn[idHilo] += Dn[idHilo];
    }
  }
}

void suma_acarreo(){
  int aux = 0;
  for(int i = 0; i < poten/2; i++){
    if(Dn[i] == 1){
      aux = 1;
    }
  }
  if(aux == 1){
    	recursion();
  }
}

suma_acarreo();

for (int i=0 ;i <poten; i++)
{
  //A[i] = 0 + rand() % (2);
  //B[i] = 0 + rand() % (2);
  printf("%i",An[i]);
}
printf("\n");
for (int i=0 ;i <poten; i++)
{
  //A[i] = 0 + rand() % (2);
  //B[i] = 0 + rand() % (2);
  printf("%i",Bn[i]);
}
printf("\n");
printf("Arrgeglo Resultado: \n");
for (int i=0 ;i < poten; i++)
{
  //A[i] = 0 + rand() % (2);
  //B[i] = 0 + rand() % (2);
  printf("%i",Cn[i]);
}
printf("\n");
printf("Arrgeglo Aux: \n");
for (int i=0 ;i <poten; i++)
{
  //A[i] = 0 + rand() % (2);
  //B[i] = 0 + rand() % (2);
  printf("%i",Dn[i]);
}
printf("\n");
	return 0;
}
