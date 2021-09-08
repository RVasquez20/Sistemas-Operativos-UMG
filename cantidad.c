#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

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
//Total de bytes a leer es de 120
int main(int argc,char * argv[]){

FILE *a=fopen(argv[1],"r");
char line[500];

while (!feof(a))
	{
		fgets(line, sizeof(line), a);

char *token="";
		token = strtok(line, "|");
		p.nombre=token;
		printf("Nombre %s\n", p.nombre);
		token = strtok(NULL, "|");
		p.apellido=token;
		printf("Apellido %s\n", p.apellido);
		token = strtok(NULL, "|");
		p.fecha=token;
		printf("fecha %s\n", p.fecha);
		token = strtok(NULL, "|");
		p.direccion=token;
		printf("direccion %s\n", p.direccion);
		token = strtok(NULL, "|");
		p.phone=token;
		printf("phone %s\n", p.phone);
		token = strtok(NULL, "|");
		p.DPI=token;
		printf("DPI %s\n", p.DPI);
		token = strtok(NULL, "|");
		p.Departamento=token;
		printf("Departamento %s\n", p.Departamento);
		token = strtok(NULL, "\n");

		//tokensalto = strtok(token, "\n");
		//printf("tokensalto..%s\n", tokensalto);
		p.Municipio=token;
		//token = strtok(NULL, "\n");
		//sem_wait(&sem1);
printf("%s,%s,%s,%s,%s,%s,%s,%s\n", p.Departamento, p.Municipio, p.DPI, p.nombre, p.apellido, p.direccion, p.phone, p.fecha);

	}

//for(int i=0;i<=100;i+=20){
/*fseek(a,sizeof(p),SEEK_SET);
fgets(line,sizeof(line),a);
printf("est %s\n",line);
//}
fclose(a);*/




/*

FILE *a=fopen(argv[1],"r");
FILE *b=fopen("prueba2.txt","a+");
fseek(a,0,SEEK_END);
long size,start,start2;
size=ftell(a);
char line[500];
printf("%ld\n",size);
for (int i = 1; i<5;i++) {
		start = (long)(size/5*i); //position of reading input csv file by the i th thread
		//inFile.seekg(searchStart[i]); //start of getting the exact position of i th thread
		//getline(inFile, tmpData);
		//searchStart[i] = inFile.tellg(); //end of getting the exact position of i th thread
		printf("%d->%ld\n",i,start);
		fseek(a,start,SEEK_SET);
		fgets(line,sizeof(line),a);
		printf("%s\n",line);
		start2=ftell(a);
		printf("start 2->%ld\n",start2);
		fgets(line,sizeof(line),a);
		printf("%s\n",line);
	}
fclose(a);
*/
/*int lineas=*((int*)arg);
	int cantidad=0;
	//wait
char line[500];
//while(fgets(line,sizeof(line),a)&& cantidad!=lineas){
	for (int i = 1; i <= lineas; i++){
		fgets(line,sizeof(line),a);
	printf("->%s\n",line);
char *token;
token=strtok(line,"|");
	while(token!=NULL ){
	p.nombre=token;
		
		token=strtok(NULL,"|");
		p.apellido=token;
		printf("Esperando..\n");
		sem_wait(&sem1);
		printf("Escribiendo..\n");
		printf("Nombre %s\n",p.nombre);
		printf("Apellido %s\n",p.apellido);
		sem_post(&sem1);
		printf("Escribio..\n");
		token=strtok(NULL,"|");
	}
printf("\n");*/
	//cantidad++;
	//}

	//printf("cantidad : %d\n",cantidad);

	//'p' 'r' 'u' 'e' 'b' 'a' '\0'
	// ./h2=0  prueba=1 prro/x=2 total=3
	// printf("%d\n",argc);
	//printf("0->%s\n",argv[0]);
	//printf("1->%s\n",argv[1]);
	//    printf("2->%s\n",argv[2]);
	//    printf("%s\n",argv[argc]);
	//
	//
	/*int fd;
char c;
int contador=0;
fd=open(argv[1],O_RDONLY);

if(fd!=-1)
{
//LEER EL ARCHIVO
//El archivo se lee caracter por caracter
while(read(fd,&c,sizeof(c)!=0)){
	if(c!='|'){
		if(contador==0){
		strcat(p.nombre,c);
		//printf("%c",c);
		
		}else if(contador==1){
		strcat(p.apellido,c);
		//printf("%c",c);
		
		}
	}
	if(c=='|'){
		contador++;
		//printf("contador++ %d %c\n",contador,c);
	}
	if(c == '\n'){
		contador=0;
		//printf("contador0 %d",contador);
		printf("Nombre %s\n",p.nombre);
		printf("Apellido %s\n",p.apellido);
		p.nombre="";
		p.apellido="";
		
		printf("\n");
	}
	//printf("%c",c);
}
//CERRAR ARCHIVO
close(fd);
/*printf("Nombre %s\n",p.nombre);
printf("Apellido %s\n",p.apellido);*/
	/*
}
 
else{
printf("\nEl archivo no existe");
}
*/
/*FILE *b=fopen("prueba2.txt","a+");
char line[500];
int cantidad=0,total=0;
while (fgets(line, sizeof(line), a) )
	{
 char *token;
  char *tokensalto;
 token=strtok(line,"|");
while (token != NULL)
{
			
			strcpy(p.nombre,token);
			printf("Nombre %s\n",p.nombre);
			token = strtok(NULL, "|");
			strcpy(p.apellido,token);
			printf("Apellido %s\n",p.apellido);
			token = strtok(NULL, "|");
			strcpy(p.fecha,token);
			printf("fecha %s\n",p.fecha);
			token = strtok(NULL, "|");
			strcpy(p.direccion,token);
			printf("direccion %s\n",p.direccion);
			token = strtok(NULL, "|");
			strcpy(p.phone,token);
			printf("phone %s\n",p.phone);
			token = strtok(NULL, "|");
			strcpy(p.DPI,token);
			printf("DPI %s\n",p.DPI);
			token = strtok(NULL, "|");
			strcpy(p.Departamento,token);
			printf("Departamento %s\n",p.Departamento);
			token = strtok(NULL, "|");
			tokensalto=strtok(token,"\n");
			strcpy(p.Municipio,tokensalto);
			token = strtok(NULL, "|");
fprintf(b,"%s,%s,%s,%s,%s,%s,%s,%s\n",p.Departamento,p.Municipio,p.DPI,p.nombre,p.apellido,p.direccion,p.phone,p.fecha);
//fprintf(b,"%s,%s,%s,%s,%s\n",p.Departamento,p.Municipio,p.DPI,p.nombre,p.apellido);

	}
	}
fclose(b);
fclose(a);*/


}