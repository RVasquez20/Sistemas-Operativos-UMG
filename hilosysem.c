	struct Rangos *rango = (struct Rangos *)arg;
	printf("Hilo: %d\n", rango->numero);
	int indice=rango->numero;
	fseek(the_file, numeros[indice], SEEK_SET);
	char lines[500];
	int contador = 0;
	long cursoen;
	long nuevo;
	while (fgets(lines, sizeof(lines), the_file))
	{
		printf("Bytes Inicio= %d hilo=%d ->%s\n", numeros[indice], indice, lines);
		/*char *token;
		char *tokensalto;
		token = strtok(lines, "|");

		strcpy(p.nombre, token);
		printf("Nombre %s\n", p.nombre);
		token = strtok(NULL, "|");
		strcpy(p.apellido, token);
		printf("Apellido %s\n", p.apellido);
		token = strtok(NULL, "|");
		strcpy(p.fecha, token);
		printf("fecha %s\n", p.fecha);
		token = strtok(NULL, "|");
		strcpy(p.direccion, token);
		printf("direccion %s\n", p.direccion);
		token = strtok(NULL, "|");
		strcpy(p.phone, token);
		printf("phone %s\n", p.phone);
		token = strtok(NULL, "|");
		strcpy(p.DPI, token);
		printf("DPI %s\n", p.DPI);
		token = strtok(NULL, "|");
		strcpy(p.Departamento, token);
		printf("Departamento %s\n", p.Departamento);
		token = strtok(NULL, "|");
		tokensalto = strtok(token, "\n");
		printf("tokensalto..%s\n", tokensalto);
		strcpy(p.Municipio, tokensalto);
		printf("Esperando Hilo:%d\n", indice);
		sem_wait(&sem1);
		printf("Escribiendo Hilo:%d\n", indice);*/
		//printf("Registro:\n%s,%s,%s,%s,%s,%s,%s,%s\n", p.Departamento, p.Municipio, p.DPI, p.nombre, p.apellido, p.direccion, p.phone, p.fecha);
		printf("Esperando Hilo:%d\n", indice);
		sem_wait(&sem1);
		printf("Escribiendo Hilo:%d\n", indice);
		fputs(lines,nuevo_file);
		//nuevos[indice]++;
		//fprintf(nuevo_file, "%s,%s,%s,%s,%s,%s,%s,%s\n", p.Departamento, p.Municipio, p.DPI, p.nombre, p.apellido, p.direccion, p.phone, p.fecha);
		//fprintf(nuevo_file,"%s,%s,%s,%s,%s,%s,%s,%s\n",p.Departamento,p.Municipio,p.DPI,p.nombre,p.apellido,p.direccion,p.phone,p.fecha);
		nuevo = ftell(the_file);
		nuevos[indice] = nuevo;
		printf("nuevo byte de inicio=%ld\n",nuevo);
		sem_post(&sem1);
		
		printf("Escribio Hilo:%d\n", indice);
		//cursoen=ftell(the_file);

		
		
		//if(indice<hilos-1 && cursoen>=numeros[indice+1])break;
		if((indice+1)!=hilos){
					printf("if(%ld>=%d) hilo actual=%d, hilo siguiente=%d\n", nuevos[indice],numeros[indice+1],rango->numero,rango->numero+1);
			if(nuevos[indice]>=numeros[indice+1]){
				break;
			}
		}else{
					printf("if(%ld>=%d) hilo actual=%d\n", nuevos[indice],total,rango->numero);
			if(nuevos[indice]>=total){
				break;
			}
		}
	}

	
		pthread_exit(NULL);