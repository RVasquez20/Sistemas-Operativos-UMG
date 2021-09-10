#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

FILE *the_file;
FILE *nuevo_file;
int Grupos, Resultado, hilos, total;
long outPos[30];
long outPos2[30];
char *Entrada;

struct Persona
{
	char *nombre;
	char *apellido;
	char *fecha;
	char *direccion;
	char *phone;
	char *DPI;
	char *Departamento;
	char *Municipio;
};
struct Persona p;

struct Rangos
{
	int numero;
	long comienzo;
};

sem_t sem1;

int CantidadDeLineas(char *);
long *numeros;
int *lineasporhilo;
void *Procesar(void *arg)
{
	sem_wait(&sem1);
	struct Rangos *rango = (struct Rangos *)arg;
	int indice = rango->numero;
	//getchar();
	printf("Hilo: %d\n", indice);
	fseek(the_file, numeros[indice], SEEK_SET);
	printf("byte inicio: %ld\n", numeros[indice]);
	char lines[500];
	while (lineasporhilo[indice] < Resultado)
	{
		fgets(lines, sizeof(lines), the_file);
		int largo = (int)strlen(lines);
		char *token = "";
		token = strtok(lines, "|");
		p.nombre = token;
		printf("Nombre %s\n", p.nombre);
		token = strtok(NULL, "|");
		p.apellido = token;
		printf("Apellido %s\n", p.apellido);
		token = strtok(NULL, "|");
		p.fecha = token;
		printf("fecha %s\n", p.fecha);
		token = strtok(NULL, "|");
		p.direccion = token;
		printf("direccion %s\n", p.direccion);
		token = strtok(NULL, "|");
		p.phone = token;
		printf("phone %s\n", p.phone);
		token = strtok(NULL, "|");
		p.DPI = token;
		printf("DPI %s\n", p.DPI);
		token = strtok(NULL, "|");
		p.Departamento = token;
		printf("Departamento %s\n", p.Departamento);
		token = strtok(NULL, "\n");
		p.Municipio = token;
		token = "";

		int primeraletra = p.Departamento[0];
		int letterId = (int)(primeraletra - 65);	
		fseek(nuevo_file, outPos[letterId], SEEK_SET);

		fprintf(nuevo_file, "%s,%s,%s,%s,%s,%s,%s,%s", p.Departamento, p.Municipio, p.DPI, p.nombre, p.apellido, p.direccion, p.phone, p.fecha);
		outPos[letterId] = ftell(nuevo_file);
		if (largo < 110)
		{
			fseek(nuevo_file, outPos[letterId], SEEK_SET);
			for (int i = 0; i < 110 - largo; i++)
			{

				fprintf(nuevo_file, " ");
				printf(" ");
			}
			fprintf(nuevo_file, "\n");
			printf("\n");
		}
		outPos[letterId] = ftell(nuevo_file);

		//sem_wait(&sem1);
		//fprintf(nuevo_file, "%s,%s,%s,%s,%s,%s,%s,%s\n", p.Departamento, p.Municipio, p.DPI, p.nombre, p.apellido, p.direccion, p.phone, p.fecha);

		//printf(" hilo=%d ->%s\n", indice, lines);
		//printf("Esperando Hilo:%d\n", indice);
		//sem_wait(&sem1);
		//printf("Escribiendo Hilo:%d\n", indice);
		//printf("%s", lines);
		//fputs(lines,nuevo_file);
		long nuevo = ftell(the_file);
		numeros[indice] = nuevo;
		lineasporhilo[indice]++;

		if (lineasporhilo[indice] == Resultado)
		{
			printf("\n\n");

			break;
		}
	}

	sem_post(&sem1);
	pthread_exit(NULL);
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
	hilos = hilosC;
	numeros = (long *)calloc(hilosC, sizeof(long *));
	lineasporhilo = (int *)calloc(hilosC, sizeof(int *));
	Grupos = atoi(argv[1]);					  //G=?
	Resultado = cantidadTotalLineas / hilosC; //R=20
	printf("Lineas por hilo:%d\n", Resultado);
	sem_init(&sem1, 0, 1);
	pthread_t hilos[hilosC];
	struct Rangos r[hilosC];

	Entrada = argv[3];
	FILE *a = fopen(argv[3], "r");
	fseek(a, 0, SEEK_END);
	long size, start, start2;
	size = ftell(a); //8661 bytes
	//printf("total %ld\n",size);
	total = size;
	char line[500];
	r[0].comienzo = 0;
	r[0].numero = 0;
	numeros[0] = 0;
	for (int i = 1; i < hilosC; i++)
	{
		r[i].numero = i;
		//printf("id=%d\n",i);
		start = (long)(size / hilosC * i);

		fseek(a, start, SEEK_SET);
		fgets(line, sizeof(line), a);
		//printf("line->%s\n",line);
		start2 = ftell(a);
		//recordatorio quitar linea abajo
		//fgets(line, sizeof(line), a);
		//printf("line->%s\n",line);
		r[i].comienzo = start2;
		numeros[i] = start2;
		//printf("i=%d num=%ld\n",i,start2);
	}
	fclose(a);

	for (int i = 0; i < 27; i++)
    {
        outPos[i] = (long)((110 * Grupos) * i); //position of output with the letter 'B C ... Z'
        printf("%d=%ld\n", i, outPos[i]);
    }
    for (int i = 0; i < 27; i++)
    {
        outPos2[i] = (long)((110 * Grupos) * i); //position of output with the letter 'B C ... Z'
        printf("%d=%ld\n", i, outPos2[i]);
    }
	getchar();
	the_file = fopen(Entrada, "r");
	nuevo_file = fopen("Salida.csv", "w+");
	int rc;
	for (int i = 0; i < hilosC; i++)
	{
		rc = pthread_create(&hilos[i], NULL, Procesar, (void *)&r[i]);
		if (rc)
		{
			printf("Error: No se puede crear el hilo,%d", rc);
			exit(-1);
		}
	}

	for (int i = 0; i < hilosC; i++)
	{
		pthread_join(hilos[i], NULL);
	}
for (int i = 0; i < 26; i++)
    {
        rewind(nuevo_file);        
        if ( outPos[i] < outPos2[i + 1])
        {
            int lineas = ((outPos2[i + 1] / 110) - (outPos[i] / 110));
            for (int p = lineas; p >= 1; p--)
            {
                rewind(nuevo_file);
                fseek(nuevo_file, outPos[i], SEEK_SET);
                    for (int j = 0; j < 109; j++)
                    {

                        fprintf(nuevo_file, " ");
                        printf(" ");
                    }
                    fprintf(nuevo_file, "\n");
                    outPos[i] = ftell(nuevo_file);   
            }
        }
    }
	sem_destroy(&sem1);
	
	fclose(the_file);
	fclose(nuevo_file);
	for (int i = 0; i < hilosC; i++)
	{
		printf("i=%d l=%d\n", i, lineasporhilo[i]);
	}
}
