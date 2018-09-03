//Leandro Egea Julio 2016
//Realizado y probado en Microsoft Visual C++ 2010 Express (Windows 10)

//LIBRERIAS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define let 100     //Define el numero maximo de caracteres en una linea
#define Words 146   //Define el numero maximo de palabras de la base de datos

//ESTRUCTURA

typedef struct{
	char cad[let];
}str;

//PROTOTIPOS PRINCIPALES

//Funciones que estan directamente en el main como pequeños programas distintos elegidos mediante un menu
char Encriptar(void);
char Desencriptar(void);
char Fuerza_bruta(void);
char N_posibles(void);
void Historial(void);

//PROTOTIPOS AUXILIARES
//Funciones que ayudan a las principales a desarrollar su funcion
int ENC(char *pprimo, int i, int *pn, int e_d); //Como si fuese el main de la funcion ENCRIPT
int KEY(int e_d); //Pide la N al usuario
int TAKECADDIM(char *fprimo); //Recoge la cadena y dimension
void COPYCAD(int dim, char *fprimo, char *fcad); //Copia la cadena y la redimensiona para optimizarla
void ENCRIPT(int n, int dim, char *fcad, char *fenc); //Encripta
int SAVEFILE(char *penc); //Guarda la encriptacion en un fichero
float FRECUENCIA(int dim, char *fenc); //Da la suma de las frecuencias de las letras mas comunes en español de una cadena de caracteres
void DATABASE(float *frec, char *fenc, char *faux, str data[Words]); //Proporciona una base de datos de palabras comunes

//MAIN
void main(void)
{
	FILE *His;
	His = fopen("historial.txt", "a");
	fclose(His);
	char choose, chooseprima[3], r1, r2, r3, r4;
	printf(" ***PROGRAMA DE ENCRIPTACION*** \n");
	do
	{
		printf("\n Seleccione la tarea que desea realizar:\n");
		printf("a-Encriptar a partir de una clave \n");
		printf("b-Desencriptar a partir de una clave \n");
		printf("c-Desencriptar sin poseer la clave \n");
		printf("d-Obtener todas las posibles combinaciones \n");
		printf("e-Mostrar el historial de operaciones realizadas anteriormente \n");
		do
		{
			fflush(stdin);
			scanf("%c", &choose);
			switch (choose)
			{
			case 'a':
				choose = Encriptar();
				break;
			case 'b':
				choose = Desencriptar();
				break;
			case 'c':
				choose = Fuerza_bruta();
				break;
			case 'd':
				choose = N_posibles();
				break;
			case 'e':
				Historial();
				break;
			default:
				printf("Caracter incorrecto, por favor seleccione una opcion correcta\n");
				choose = 'z';
			}
		} while (choose == 'z'); //Mientras que la opcion que elija el usuario haga que choose sea z, se repetira el bucle

		//Algoritmo de repeticion del programa
		printf("Desea continuar con el programa? Si o No \n");
		char respuesta1[] = "Si", respuesta2[] = "No", respuesta3[] = "si", respuesta4[] = "no";
		do
		{
			fflush(stdin);
			gets(chooseprima); //la cadena de caracteres chooseprima sera valida si es si, Si, no o No
			//Comparacion entre lo introducido por el usuario y lo que hay en el codigo gracias a la funcion strcmp (string)
			r1 = strcmp(chooseprima, respuesta1);
			r2 = strcmp(chooseprima, respuesta2);
			r3 = strcmp(chooseprima, respuesta3);
			r4 = strcmp(chooseprima, respuesta4);
			if (r1 != 0 && r2 != 0 && r3 != 0 && r4 != 0) //Si no hay ninguna que coincida, la respuesta es invalida
			{
				printf("Respuesta invalida\n");
				printf("Responda si o no por favor \n");
			}
		} while (r1 != 0 && r2 != 0 && r3 != 0 && r4 != 0); //Mientras que la respuesta sea invalida, se repetira el bucle
	} while (r1 == 0 || r3 == 0); //Si la respuesta es si o Si el bucle repetira todo el programa, si no, finalizara el programa
	printf("FIN DEL PROGRAMA \n");
	system("pause");
}//FIN MAIN

//FUNCIONES PRINCIPALES
char Encriptar(void)
{
	fflush(stdin);
	int dim = 1000, n, i, e_d = 1;
	char *pprimo, *pcad, *penc, opcion;
	FILE *pf;
	//El usuario escribe lo que desea encriptar
	do
	{
		fflush(stdin);
		printf("Elige la opcion que desee:\n a-Pasar mensaje desde fichero (mifichero.txt)\n b-Escribir mensaje directamente en consola\n");
		scanf("%c", &opcion);
		switch (opcion)
		{
		case 'a':
			fflush(stdin);
			pf = fopen("mifichero.txt", "r"); //Solo permite leer el fichero
			//Condicion de existencia
			if (pf == NULL) //Si nos da error, no seguimos con el codigo
			{
				printf("No se encuentra el fichero\n");
				return 'z';  //Retorna una 'z' reiniciando el switch-case del main
			}
			else
			{
				pprimo = (char*)calloc(let, sizeof(char)); //Creacion del primer puntero
				fgets(pprimo, let, pf);
				i = 0;
				dim = ENC(pprimo, i, &n, e_d);
				fclose(pf);
			}
			if (dim == 0)
			{
				printf("ERROR: Fichero vacio \n");
			}
			break;
		case 'b':
			do
			{
				fflush(stdin);
				pprimo = (char*)calloc(let, sizeof(char)); //Creacion del primer puntero
				printf("Por favor, introduzca el mensaje que desea encriptar:\n");
				gets(pprimo);
				i = 0;
				dim = ENC(pprimo, i, &n, e_d);
			} while (dim == 0);
			break;
		default:
			printf("Opcion invalida\n");
			dim = 0;
		}
	} while (dim == 0); //Mientras que el valor de retorno de la funcion sea 0, se repetira el bucle
}
char Desencriptar(void)
{
	fflush(stdin);
	int dim = 1000, n, i, e_d = 2;
	char *pprimo, *pcad, *penc, opcion;
	FILE *pf;
	//El usuario escribe lo que desea encriptar
	do
	{
		fflush(stdin);
		printf("Elige la opcion que desee:\n a-Pasar mensaje desde fichero (mifichero.txt)\n b-Escribir mensaje directamente en consola\n");
		scanf("%c", &opcion);
		switch (opcion)
		{
		case 'a':
			fflush(stdin);
			pf = fopen("mifichero.txt", "r"); //Solo permite leer el fichero
			//Condicion de existencia
			if (pf == NULL) //Si nos da error, no seguimos con el codigo
			{
				printf("No se encuentra el fichero\n");
				return 'z';  //Retorna una 'z' reiniciando el switch-case del main
			}
			else
			{
				pprimo = (char*)calloc(let, sizeof(char)); //Creacion del primer puntero
				fgets(pprimo, let, pf);
				i = 0;
				dim = ENC(pprimo, i, &n, e_d);
				fclose(pf);
			}
			if (dim == 0)
			{
				printf("ERROR: Fichero vacio \n");
			}
			break;
		case 'b':
			do
			{
				fflush(stdin);
				pprimo = (char*)calloc(let, sizeof(char)); //Creacion del primer puntero
				printf("Por favor, introduzca el mensaje que desea encriptar:\n");
				gets(pprimo);
				i = 0;
				dim = ENC(pprimo, i, &n, e_d);
			} while (dim == 0);
			break;
		default:
			printf("Opcion invalida\n");
			dim = 0;
		}
	} while (dim == 0); //Mientras que el valor de retorno de la funcion sea 0, se repetira el bucle
}
char Fuerza_bruta(void)
{
	fflush(stdin);
	int dim = 1000, n, i = 0;
	char *pprimo, *pcad, *penc, opcion,z;
	float frec, flag = 0;
	FILE *pf, *His;
	His = fopen("historial.txt", "a");
	str vstr[26], *pvstr;
	pvstr = &vstr[0];
	//El usuario escribe lo que desea encriptar
	do
	{
		fflush(stdin);
		printf("Elige la opcion que desee:\na-Pasar mensaje desde fichero(mifichero.txt)\nb-Escribir mensaje directamente en consola\n");
		scanf("%c", &opcion);
		switch (opcion)
		{
		case 'a':
			fflush(stdin);
			pf = fopen("mifichero.txt", "r"); //Solo permite leer el fichero
			if (pf == NULL) //Si nos da error, no seguimos con el codigo
			{
				printf("No se encuentra el fichero\n");
				return 'z';
			}
			//Condicion de existencia
			else
			{
				penc = (char*)calloc(let, sizeof(char));
				fgets(vstr[0].cad, let, pf);
				fprintf(His, "%s->", pvstr->cad);
				for (n = 1; n <= 25; n++)
				{
					pvstr = &vstr[0];
					ENCRIPT(n, let, pvstr->cad, penc);
					pvstr = &vstr[n];
					COPYCAD(let - 1, penc, pvstr->cad);
					frec = FRECUENCIA(let, penc);
					if (frec>flag)
					{
						flag = frec;
						i = n;
					}
				}
				fclose(pf);
				pvstr = &vstr[i];
				puts(pvstr->cad);
				fprintf(His, "%s\n", pvstr->cad);
				printf("Es esa la opcion correcta? si o no\n");
				scanf("%c",&z);
				if (z == 'n' || z == 'N')
				{
					fflush(stdin);
					pf = fopen("mifichero.txt", "r"); //Solo permite leer el fichero
					if (pf == NULL) //Si nos da error, no seguimos con el codigo
					{
						printf("No se encuentra el fichero\n");
						return 'z';
					}
					//Condicion de existencia
					else
					{
						penc = (char*)calloc(let, sizeof(char));
						//pvstr = &vstr[0];
						fgets(vstr[0].cad, let, pf);
						fprintf(His, "%s->", pvstr->cad);
						for (n = 1; n <= 25; n++)
						{
							pvstr = &vstr[0];
							//fgets(vstr[n-1].cad, let, pf);
							ENCRIPT(n, let, pvstr->cad, penc);
							pvstr = &vstr[n];
							COPYCAD(let - 1, penc, pvstr->cad);
							printf("N=%d: ", n);
							puts(penc);
						}
						fclose(pf);
						printf("Indica la N correcta\n");
						scanf("%d", &n);
						pvstr = &vstr[n];
						fprintf(His, "%s\n", pvstr->cad);
						i = SAVEFILE(pvstr->cad);
					}
					break;
				}
				else
				{
					i = SAVEFILE(pvstr->cad);
				}
				break;
			}
		case 'b':
			do
			{
				fflush(stdin);
				pprimo = (char*)calloc(let, sizeof(char)); //Creacion del primer puntero
				printf("Por favor, introduzca el mensaje que desea encriptar:\n");
				gets(pprimo);
				dim = TAKECADDIM(pprimo);
				pcad = (char*)calloc(dim + 1, sizeof(char));
				penc = (char*)calloc(dim + 1, sizeof(char));
				COPYCAD(dim, pprimo, pcad);
				fprintf(His, "%s->", pcad);
			} while (dim == 0);
			free(pprimo);
			for (n = 1; n <= 25; n++)
			{
				pvstr = &vstr[n - 1];
				ENCRIPT(n, dim, pcad, penc);
				COPYCAD(dim, penc, pvstr->cad);
				frec = FRECUENCIA(dim, penc);
				if (frec>flag)
				{
					flag = frec;
					i = n - 1;
				}
			}
			pvstr = &vstr[i];
			puts(pvstr->cad);
			fprintf(His, "%s\n", pvstr->cad);
			printf("Es esa la opcion correcta?\n");
			scanf("%c", &z);
			if (z == 'n' || z == 'N')
			{
				do
				{
					fflush(stdin);
					pprimo = (char*)calloc(let, sizeof(char)); //Creacion del primer puntero
					printf("Por favor, introduzca  de nuevo el mensaje que desea encriptar:\n");
					gets(pprimo);
					dim = TAKECADDIM(pprimo);
					pcad = (char*)calloc(dim + 1, sizeof(char));
					penc = (char*)calloc(dim + 1, sizeof(char));
					COPYCAD(dim, pprimo, pcad);
					fprintf(His, "%s->", pcad);
				} while (dim == 0);
				free(pprimo);
				for (n = 1; n <= 25; n++)
				{
					pvstr = &vstr[n - 1];
					ENCRIPT(n, dim, pcad, penc);
					COPYCAD(dim, penc, pvstr->cad);
					printf("N=%d: ", n);
					puts(penc);
				}
				printf("Cual es la N correcta? \n");
				scanf("%d", &n);
				pvstr = &vstr[n - 1];
				fprintf(His, "%s\n", pvstr->cad);
				i = SAVEFILE(pvstr->cad);
				break;
			}
			else
			{
				i = SAVEFILE(pvstr->cad);
			}
			break;
		default:
			printf("Opcion invalida");
			dim = 0;
		}
	} while (dim == 0); //Mientras que el valor de retorno de la funcion sea 0, se repetira el bucle
	fclose(His);
}
char N_posibles(void)
{
	fflush(stdin);
	int dim = 1000, n, i;
	char *pprimo, *pcad, *penc, opcion;
	FILE *pf, *His;
	His = fopen("historial.txt", "a");
	str vstr[26], *pvstr;
	pvstr = &vstr[0];
	//El usuario escribe lo que desea encriptar
	do
	{
		fflush(stdin);
		printf("Elige la opcion que desee:\na-Pasar mensaje desde fichero(mifichero.txt)\nb-Escribir mensaje directamente en consola\n");
		scanf("%c", &opcion);
		switch (opcion)
		{
		case 'a':
			fflush(stdin);
			pf = fopen("mifichero.txt", "r"); //Solo permite leer el fichero
			if (pf == NULL) //Si nos da error, no seguimos con el codigo
			{
				printf("No se encuentra el fichero\n");
				return 'z';
			}
			//Condicion de existencia
			else
			{
				penc = (char*)calloc(let, sizeof(char));
				//pvstr = &vstr[0];
				fgets(vstr[0].cad, let, pf);
				fprintf(His, "%s->", pvstr->cad);
				for (n = 1; n <= 25; n++)
				{
					pvstr = &vstr[0];
					//fgets(vstr[n-1].cad, let, pf);
					ENCRIPT(n, let, pvstr->cad, penc);
					pvstr = &vstr[n];
					COPYCAD(let - 1, penc, pvstr->cad);
					printf("N=%d: ", n);
					puts(penc);
				}
				fclose(pf);
				printf("Indica la N correcta\n");
				scanf("%d", &n);
				pvstr = &vstr[n];
				fprintf(His, "%s\n", pvstr->cad);
				i = SAVEFILE(pvstr->cad);
			}
			break;
		case 'b':
			do
			{
				fflush(stdin);
				pprimo = (char*)calloc(let, sizeof(char)); //Creacion del primer puntero
				printf("Por favor, introduzca el mensaje que desea encriptar:\n");
				gets(pprimo);
				dim = TAKECADDIM(pprimo);
				pcad = (char*)calloc(dim + 1, sizeof(char));
				penc = (char*)calloc(dim + 1, sizeof(char));
				COPYCAD(dim, pprimo, pcad);
				fprintf(His, "%s->", pcad);
			} while (dim == 0);
			free(pprimo);
			for (n = 1; n <= 25; n++)
			{
				pvstr = &vstr[n - 1];
				ENCRIPT(n, dim, pcad, penc);
				COPYCAD(dim, penc, pvstr->cad);
				printf("N=%d: ", n);
				puts(penc);
			}
			printf("¿Cual es la N correcta? \n");
			scanf("%d", &n);
			pvstr = &vstr[n - 1];
			fprintf(His, "%s\n", pvstr->cad);
			i = SAVEFILE(pvstr->cad);
			break;
		default:
			printf("Opcion invalida\n");
			dim = 0;
		}
	} while (dim == 0); //Mientras que el valor de retorno de la funcion sea 0, se repetira el bucle
	fclose(His);
}
void Historial(void)
{
	FILE *His;
	His = fopen("historial.txt", "r");
	char a[let], r1, r2, r3, r4, chooseprima[3];
	while (feof(His) == NULL) //Imprime el historial
	{
		fgets(a, let, His);
		puts(a);
	}
	printf("Desea borrar el historial?\n");
	char respuesta1[] = "Si", respuesta2[] = "No", respuesta3[] = "si", respuesta4[] = "no";
	do
	{
		fflush(stdin);
		gets(chooseprima); //la cadena de caracteres chooseprima sera valida si es si, Si, no o No
		//Comparacion entre lo introducido por el usuario y lo que hay en el codigo gracias a la funcion strcmp (string)
		r1 = strcmp(chooseprima, respuesta1);
		r2 = strcmp(chooseprima, respuesta2);
		r3 = strcmp(chooseprima, respuesta3);
		r4 = strcmp(chooseprima, respuesta4);
		if (r1 != 0 && r2 != 0 && r3 != 0 && r4 != 0) //Si no hay ninguna que coincida, la respuesta es invalida
		{
			printf("Respuesta invalida\n");
			printf("Responda si o no por favor \n");
		}
		else if (r1 == 0 || r3 == 0)
		{
			His = fopen("historial.txt", "w");
			printf("\nEl historial ha sido borrado\n");
		}
		else
		{
			printf("\nEl historial no sera borrado\n");
		}
	} while (r1 != 0 && r2 != 0 && r3 != 0 && r4 != 0); //Mientras que la respuesta sea invalida, se repetira el bucle
	fclose(His);
}

//FUNCIONES Auxiliares
int ENC(char *pprimo, int i, int*pn, int e_d)
{
	int dim, n;
	char *pcad, *penc;
	FILE *His;
	dim = TAKECADDIM(pprimo); //Llamada a la funcion auxiliar que recoge la frase y la dimension
	if (dim == 0)
		return 0;
	His = fopen("historial.txt", "a");
	pcad = (char*)calloc(dim + 1, sizeof(char)); //Creacion del segundo puntero, ya optimizado
	COPYCAD(dim, pprimo, pcad); //Llamada a la funcion auxiliar que copia la cadena optimizada
	fprintf(His, "%s-->", pcad); //Guarda el mensaje sin pasar por el encriptador en el historial
	free(pprimo); //Liberacion de la primera cadena que no esta optimizada
	*pn = KEY(e_d); //El usuario escribe la clave
	penc = (char*)calloc(dim + 1, sizeof(char)); //Creacion del puntero de la cadena encriptada
	ENCRIPT(*pn, dim, pcad, penc); //Llamada de la funcion auxiliar de encriptacion
	puts(penc); //Escribe la encriptacion en pantalla
	n = SAVEFILE(penc); //Guarda el mensaje en un fichero (o no)
	fprintf(His, "%s\n", penc); //Guarda el mensaje encriptado en el historial
	fclose(His);
	free(pcad);
	free(penc);
	return dim;
}
int TAKECADDIM(char *fprimo) //Averigua si todo son letras y espacios y ademas actua como contador
{
	int dim = 0;
	while (*fprimo != '\0') //Mientras que a lo que apunta fprimo no sea final de caracteres, se repetira el bucle
	{
		if ((*fprimo == 32) || (*fprimo >= 65 && *fprimo <= 90) || (*fprimo >= 97 && *fprimo <= 122) || *fprimo == '\n') //Si es espacio, mayuscula o minuscula
		{
			if (*fprimo == 32 && *(fprimo + 1) == 32)
			{
				printf(" No se admiten dos espacios consecutivos\n");
				return(0); //Retornamos 0 para que el usuario vuelva a introducir la cadena correctamente
			}
			dim++; //dim se incrementa en uno
			fprimo++; //el puntero se mueve una posicion hacia delante
		}
		else //Si el caracter no es espacio ni mayuscula ni minuscula
		{
			printf(" No se adimite %c\n", *fprimo);
			printf(" Mensaje invalido. Solo se adimiten mayusculas, minusculas y espacios\n");
			return(0); //Retornamos 0 para que el usuario vuelva a introducir la cadena correctamente
		}
	}
	return(dim); //Una vez fprimo apunte al final de caracter, retornaremos el numero de caracteres introducidos
}
int KEY(int e_d) //El usuario escribe la clave de encriptacion
{
	int n = 0;
	fflush(stdin);
	do
	{
		printf("Ahora introduzca la clave de encriptacion: \n");
		scanf("%d", &n);
		if (n<1 || n>26)
		{
			printf("La clave de encriptacion debe ser una cifra comprendida entre 1 y 26 \n");
		}
	} while (n<1 || n>26);
	if (e_d == 1)
	{
		printf("El mensaje encriptado con la clave %d es el siguiente: \n", n);
		return (n);
	}
	else if (e_d == 2)
	{
		printf("El mensaje encriptado con la clave %d es el siguiente: \n", 26 - n);
		return (26 - n);
	}
}
void COPYCAD(int dim, char *fprimo, char *fcad) //Copia el mensaje en la cadena optimizada
{
	int i;
	for (i = 0; i<dim; i++)
	{
		*fcad = *fprimo;
		fcad++;
		fprimo++;
	}
	*fcad = '\0';
}
void ENCRIPT(int n, int dim, char *fcad, char *fenc)
{
	//Aplica el algoritmo de encriptacion a la cadena
	int i;
	for (i = 0; i<dim; i++) //Bucle hasta que se acabe la cadena de caracteres
	{
		if (*fcad == 32) //Los espacios se quedan en espacios
		{
			*fenc = 32;
		}
		else if (*fcad >= 97 && *fcad <= 122) //Referido a las minusculas
		{
			*fenc = *fcad + n - 90;  //Se resta 90 para evitar fallos referidos a la tabla ASCII (luego se vuelven a sumar)
			if (*fenc>32) //Sirve por si se pasa de la z en el alfabeto, vuelva a la a
			{
				*fenc -= 26;
			}
			*fenc += 90;
		}
		else if (*fcad >= 65 && *fcad <= 90) //Referido a las mayusculas
		{
			*fenc = *fcad + n;
			if (*fenc>90)
			{
				*fenc -= 26;
			}
		}
		fenc++;
		fcad++;
	}
	*fenc = '\0';
}
float FRECUENCIA(int dim, char *fenc)
{
	int i = 0;
	char *faux;
	faux = fenc;
	float frec = 0;
	FILE *pdata;
	str vdata[Words], *pvdata; //Para coger todas las palabras de la database
	pdata = fopen("database.txt", "r");    //Abre un fichero con palabras comunes del español
	if (pdata == NULL) //Si nos da error, no seguimos con el codigo
	{
		printf("No se encuentra el fichero de la base de datos\n");
		return 0;
	}
	else
	{
		while (feof(pdata) == NULL)
		{
			pvdata = &vdata[i];
			fscanf(pdata, "%s", pvdata->cad);  //Copia la base de datos en un vector de estructuras
			i++;
		}
	}
	fclose(pdata);
	for (i = 0; i<dim; i++) //Sirve para sumar la frecuencia absoluta de cada letra
	{
		if (*fenc == 32 && *(fenc + 2) == 32)
		{
			if (*(fenc + 1) != 'a'&& *(fenc + 1) != 'e'&&*(fenc + 1) != 'y'&&*(fenc + 1) != 'o'&&*(fenc + 1) != 'u'&&*(fenc + 1) != 'A'&&*(fenc + 1) != 'E'&&*(fenc + 1) != 'Y'&&*(fenc + 1) != 'O'&&*(fenc + 1) != 'U')
				return(0);
		}
		if (*fenc == 32)
			DATABASE(&frec, fenc, faux, vdata);
		else if (*fenc == 'a' || *fenc == 'A')
			frec += 12.53;
		else if (*fenc == 'b' || *fenc == 'B')
			frec += 1.42;
		else if (*fenc == 'c' || *fenc == 'C')
			frec += 4.68;
		else if (*fenc == 'd' || *fenc == 'D')
			frec += 5.86;
		else if (*fenc == 'e' || *fenc == 'E')
			frec += 13.68;
		else if (*fenc == 'f' || *fenc == 'F')
			frec += 0.69;
		else if (*fenc == 'g' || *fenc == 'G')
			frec += 1.01;
		else if (*fenc == 'h' || *fenc == 'H')
			frec += 0.70;
		else if (*fenc == 'i' || *fenc == 'I')
			frec += 6.25;
		else if (*fenc == 'j' || *fenc == 'J')
			frec += 0.44;
		else if (*fenc == 'k' || *fenc == 'K')
			frec += 0.01;
		else if (*fenc == 'l' || *fenc == 'L')
			frec += 4.97;
		else if (*fenc == 'm' || *fenc == 'M')
			frec += 3.15;
		else if (*fenc == 'n' || *fenc == 'N')
			frec += 6.71;
		else if (*fenc == 'o' || *fenc == 'O')
			frec += 8.68;
		else if (*fenc == 'p' || *fenc == 'P')
			frec += 2.51;
		else if (*fenc == 'q' || *fenc == 'Q')
			frec += 0.88;
		else if (*fenc == 'r' || *fenc == 'R')
			frec += 6.87;
		else if (*fenc == 's' || *fenc == 'S')
			frec += 7.98;
		else if (*fenc == 't' || *fenc == 'T')
			frec += 4.63;
		else if (*fenc == 'u' || *fenc == 'U')
			frec += 3.93;
		else if (*fenc == 'v' || *fenc == 'V')
			frec += 0.90;
		else if (*fenc == 'w' || *fenc == 'W')
			frec += 0.02;
		else if (*fenc == 'x' || *fenc == 'X')
			frec += 0.22;
		else if (*fenc == 'y' || *fenc == 'Y')
			frec += 0.90;
		else
			frec += 0.52;
		fenc++;
		if (frec == 10000)
			return (frec);
	}
	return (frec);
}
int SAVEFILE(char *penc)
{
	/*Guardar el mensaje en un fichero.
	El usuario elige si guardarlo o no, si elige que si, entonces se guarda en el fichero mifichero2.txt*/
	printf("\nDesea guardar en un fichero el mensaje? Si o No\n");
	char respuesta1[] = "Si", respuesta2[] = "No", respuesta3[] = "si", respuesta4[] = "no", resp[3], res1, res2, res3, res4;
	FILE *pf2;
	do
	{
		fflush(stdin);
		gets(resp);
		res1 = strcmp(resp, respuesta1);
		res2 = strcmp(resp, respuesta2);
		res3 = strcmp(resp, respuesta3);
		res4 = strcmp(resp, respuesta4);
		if (res1 == 0 || res3 == 0)
		{
			pf2 = fopen("mifichero2.txt", "w");
			if (pf2 == NULL)
			{
				printf("ERROR");
				return 1;
			}
			fprintf(pf2, "%s", penc);
			printf("\nSu archivo ha sido guardado\n");
			fclose(pf2);
		}
		else if (res2 == 0 || res4 == 0)
		{
			printf("\nSu archivo no sera guardado\n");
		}
		else
		{
			printf("\nOpcion invalida, introduzca si o no\n");
		}
	} while (res1 != 0 && res2 != 0 && res3 != 0 && res4 != 0);
}
void DATABASE(float *frec, char *fenc, char *faux, str data[Words])
{
	char *pword;
	int dim, i, j;
	dim = 0;
	do
	{
		fenc--;
		dim++;
	} while (*fenc != ' ' && *fenc != *faux);
	pword = (char*)calloc(dim + 1, sizeof(char));
	if (*fenc == 32)
	{
		fenc++;
		dim--;
	}
	COPYCAD(dim, fenc, pword);
	for (i = 0; i<Words; i++)
	{
		j = strcmp(pword, data[i].cad);
		if (j == 0)
			*frec = 10000;
	}
}