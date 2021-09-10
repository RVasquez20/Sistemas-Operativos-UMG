#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int *a;
int main(int argc, char *argv[])
{

    /*char *cadena="Florida";
    printf("%c",(char)cadena[0]);
    return 0;*/
    /*int grupos=atoi(argv[1]);
    a=(int *)calloc(grupos,sizeof(int*));
    for (int i =0;i<grupos; i++){
        a[i]=i;
    }
    for(int i=0; i < grupos; i++){
        printf("%d",a[i]);
    }*/

    long x;
    FILE *c = fopen("Salidaenorden.csv", "w+");

    //fseek(a, 21, SEEK_SET);
    // fputs("New York,Albany,4151355697,Cassie,Uren,55804 Kennedy Hill,5189600511,11/08/2019",a);

    fclose(c);
    long size;
    FILE *entrada = fopen("datos2.psv", "r");
    fseek(entrada, 0, SEEK_END);
    size = ftell(entrada);
    rewind(entrada);
    int cantidad[26];

    printf("%ld\n", size);
    long outPos[30];
    long outPos2[30];
    for (int i = 0; i < 27; i++)
    {
        outPos[i] = (long)((110 * 15) * i); //position of output with the letter 'B C ... Z'
        printf("%d=%ld\n", i, outPos[i]);
    }
    for (int i = 0; i < 27; i++)
    {
        outPos2[i] = (long)((110 * 15) * i); //position of output with the letter 'B C ... Z'
        printf("%d=%ld\n", i, outPos2[i]);
    }
    char lines[500];
    int contador = 0;
    FILE *SALIDA = fopen("Salidaenorden.csv", "r+");
    fgets(lines, sizeof(lines), entrada);
    while (!feof(entrada))
    {
        int primeraletra = lines[0];
        printf("primer letra=%d \n", primeraletra);
        int letterId = (int)(primeraletra - 65);
        printf("primer pos=%ld id=%d\n", outPos[letterId], letterId);
        printf("primera letra:%c\n", primeraletra);
        fseek(SALIDA, outPos[letterId], SEEK_SET);
        int largo = (int)strlen(lines);
        for (int let = 0; let < largo - 1; let++)
        {
            fprintf(SALIDA, "%c", lines[let]);
            long tamanio = (long)strlen(lines);
            printf("%c", lines[let]);
        }
        outPos[letterId] = ftell(SALIDA);
        if (largo < 110)
        {
            fseek(SALIDA, outPos[letterId], SEEK_SET);
            for (int i = 0; i < 110 - largo; i++)
            {

                fprintf(SALIDA, " ");
                printf(" ");
            }
            fprintf(SALIDA, "\n");
            printf("\n");
        }
        outPos[letterId] = ftell(SALIDA);
        printf("nueva pos=%ld id=%d\n", outPos[letterId], letterId);
        
        fgets(lines, sizeof(lines), entrada);
    }

    char xy = (char)32;
    char salto = (char)10;
    for (int i = 0; i < 26; i++)
    {
        rewind(SALIDA);
        printf("if  %ld<%ld\n", outPos[i], outPos2[i + 1]);
        if ( outPos[i] < outPos2[i + 1])
        {
            int lineas = ((outPos2[i + 1] / 110) - (outPos[i] / 110));
            printf("lineas restantes=%d", lineas);
            for (int p = lineas; p >= 1; p--)
            {
                rewind(SALIDA);
                fseek(SALIDA, outPos[i], SEEK_SET);
                    for (int j = 0; j < 109; j++)
                    {

                        fprintf(SALIDA, " ");
                        printf(" ");
                    }
                    fprintf(SALIDA, "\n");
                    printf("\n");
                    outPos[i] = ftell(SALIDA);
                    printf("posrelleno=%ld", outPos[i]);

                     printf("lineas=%d", p);
                                       
                
            }
        }
    }

    fclose(SALIDA);
    fclose(entrada);

    /* FILE *b = fopen("Salidareoden.csv", "r+");
    rewind(b);
    
    fseek(b, 90, SEEK_SET);
    fprintf(b,"%s\n",cad);
    fseek(b, 0, SEEK_SET);
    fprintf(b,"%s\n",cad);
       fclose(b);*/
    /*for(int i =0; i < 20; i++){
        if(i%2==0){
    fseek(b, positionA, SEEK_SET);
    fprintf(b,"%d\n",i);
    printf("%d\n",i);
    getchar();
    positionA=ftell(b);
    positionB+=positionA;
    printf("position a:%ld\n",positionA);
    getchar();
    cantidad[0]++;
    printf("Cantidad0=%d\n",cantidad[0]);
       }else{
             printf("position b:%ld\n",positionB);
             getchar();
          fseek(b, positionB, SEEK_SET);
    fprintf(b,"%d\n",i);
    printf("%d\n",i);
    getchar();
    positionB=ftell(b);  
    printf("position b:%ld\n",positionB);
    getchar();
 cantidad[1]++;
 printf("Cantidad0=%d\n",cantidad[0]);
        }
        
    //fseek(a, 21, SEEK_SET);
   // fputs("New York,Albany,4151355697,Cassie,Uren,55804 Kennedy Hill,5189600511,11/08/2019",a);
   // fflush(b);
        
    }
    if(cantidad[0]<12){
            int dif=12-cantidad[0];
            printf("dif:%d\n",dif);
            fseek(b, positionA, SEEK_SET);
            for(int i=0;i<dif;i++){
                fprintf(b," \n");
            }
        }
       if(cantidad[1]<12){
            int dif=12-cantidad[1];
            printf("dif:%d\n",dif);
            fseek(b, positionB, SEEK_SET);
            for(int i=0;i<dif;i++){
                fprintf(b," \n");
            }
        }*/

    return 0;
}