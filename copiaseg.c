#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

FILE *the_file;
FILE *nuevo_file;
int Grupos, Resultado,hilos,total;

char *Entrada;

struct Persona
{
	char nombre[50];
	char apellido[50];
	char fecha[50];
	char direccion[50];
	char phone[50];
	char DPI[50];
	char Departamento[50];
	char Municipio[50];
};
struct Persona p;

struct Rangos
{
	int numero;
	long comienzo;
};

sem_t sem1;


int CantidadDeLineas(char *);
long numeros[5];
int lineasporhilo[5];
void *Procesar(void *arg)
{
	sem_wait(&sem1);
struct Rangos *rango = (struct Rangos *)arg;
int indice=rango->numero;
//getchar();
printf("Hilo: %d\n", indice);
fseek(the_file, numeros[indice], SEEK_SET);
printf("byte inicio: %ld\n", numeros[indice]);
char lines[500];
while (fgets(lines, sizeof(lines), the_file) && lineasporhilo[indice]<Resultado)
	{
		
		//printf(" hilo=%d ->%s\n", indice, lines);
		//printf("Esperando Hilo:%d\n", indice);
	//sem_wait(&sem1);
		//printf("Escribiendo Hilo:%d\n", indice);
		printf("%s", lines);
		fputs(lines,nuevo_file);
		long nuevo = ftell(the_file);
		numeros[indice]=nuevo;
		lineasporhilo[indice]++;
		
printf("lineado por hilo=: %d hilo=%d\n",lineasporhilo[indice],indice);
//getchar();
		
		printf("if(%d>=%d)\n",lineasporhilo[indice],Resultado);
		if(lineasporhilo[indice]>=Resultado)
		{
			printf("\n\n");
			pthread_exit(NULL);
			break;}
			sem_post(&sem1);
		//printf("Escribio Hilo:%d\n", indice);

		/*if((indice+1)!=hilos){
					printf("if(%ld>=%ld) hilo actual=%d\n", numeros[indice],numeros[indice+1],indice);
			if(numeros[indice]>=numeros[indice+1]  ){
				break;
			}
		}else{
					printf("if(%ld>=%d) hilo actual=%d\n", numeros[indice],total,indice);
			if(numeros[indice]>=total){
				break;
			}
		}*/
	
	}


}

int CantidadDeLineas(char *nombre)
{

	FILE *a = fopen(nombre, "r");
	char line[500];
	int cantidad = 0;
	while (fgets(line, sizeof(line), a))
	{
		cantidad++;
	}
	return cantidad;
}

int main(int argc, char *argv[])
{

	int cantidadTotalLineas = CantidadDeLineas(argv[3]); //M=100


	int hilosC = atoi(argv[2]); //T=5
	hilos=hilosC;
	Grupos = atoi(argv[1]);					  //G=?
	Resultado = cantidadTotalLineas / hilosC; //R=20
	printf("Lineas por hilo:%d",Resultado);
	sem_init(&sem1, 0, 1);
	pthread_t hilos[hilosC];
	struct Rangos r[hilosC];

	Entrada=argv[3];	

	FILE *a = fopen(argv[3], "r");
	fseek(a, 0, SEEK_END);
	long size, start, start2;
	size = ftell(a);//8661 bytes
	printf("total %ld\n",size);
	total=size;
	char line[500];
	r[0].comienzo = 0;
	r[0].numero = 0;
	numeros[0]=0;
	for (int i = 1; i < hilosC; i++)
	{
		r[i].numero = i;
		start = (size / hilosC * i);

		fseek(a, start, SEEK_SET);
		fgets(line, sizeof(line), a);

		start2 = ftell(a);
		fgets(line, sizeof(line), a);
		r[i].comienzo = start2;
		numeros[i]=start2;
		printf("i=%d num=%ld\n",i,start2);
	}
	fclose(a);


/*the_file= fopen(Entrada,"r");
nuevo_file= fopen("Salida.csv","a+");	
int rc;
for (int i = 0; i < hilosC; i++)
	{
		rc=pthread_create(&hilos[i], NULL, Procesar, (void *)&r[i]);
		if (rc) {
	        printf("Error: No se puede crear el hilo,%d", rc );
	        exit(-1);
        }
	}
   
	for (int i = 0; i < hilosC; i++)
	{
		pthread_join(hilos[i], NULL);
	}

	sem_destroy(&sem1);


fclose(the_file);
fclose(nuevo_file);*/
for (int i =0;i<5;i++){
	printf("i=%d l=%d\n",i,lineasporhilo[i]);
}
}
