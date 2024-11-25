#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define TAMTOKEN 50

void QuitarCaracteres(char* palabra) {
    char simbolos[] = ".,;()";
    int i, j, apuntador = 0;

    size_t longitud = strlen(palabra); // Calcula longitud una vez
    for (i = 0; i < longitud; i++) {
        int anadir = 1;
        for (j = 0; j < strlen(simbolos); j++) {
            if (palabra[i] == simbolos[j]) {
                anadir = 0;
                break; // Salir del bucle si se encuentra el símbolo
            }
        }
        if (anadir) {
            palabra[apuntador] = palabra[i];
            apuntador++;
        }
    }
    palabra[apuntador] = '\0';

    for (i = 0; palabra[i] != '\0'; i++) {
        palabra[i] = tolower(palabra[i]);
    }
}

void Eliminar(char szPalabras[][TAMTOKEN], int* elementos, int iEstadisticas[]) {
    int i, j, k;
    for (i = 0; i < *elementos; i++) {
        iEstadisticas[i]++;
    }

    for (i = 0; i < *elementos; i++) {
        for (j = i + 1; j < *elementos; j++) {
            if (strcmp(szPalabras[i], szPalabras[j]) == 0) {
                iEstadisticas[i]++;
                for (k = j; k < *elementos - 1; k++) {
                    strcpy_s(szPalabras[k], szPalabras[k + 1]);
                }
                (*elementos)--; // Decrementa el número de elementos
                j--; // Ajusta índice para comparar el siguiente
            }
        }
    }
}

void Ordenar(char szPalabras[][TAMTOKEN], int elementos, int iEstadisticas[], int opcion) {
    int i, j;
    char aux[TAMTOKEN];
    int auxNum;

    if (opcion == 0) { // Orden alfabético
        for (i = 0; i < elementos; i++) {
            for (j = 0; j < elementos - 1; j++) {
                if (strcmp(szPalabras[j], szPalabras[j + 1]) > 0) {
                    strcpy_s(aux, szPalabras[j]);
                    strcpy_s(szPalabras[j], szPalabras[j + 1]);
                    strcpy_s(szPalabras[j + 1], aux);

                    auxNum = iEstadisticas[j];
                    iEstadisticas[j] = iEstadisticas[j + 1];
                    iEstadisticas[j + 1] = auxNum;
                }
            }
        }
    }
    else if (opcion == 1) { // Orden por frecuencia
        for (i = 0; i < elementos; i++) {
            for (j = 0; j < elementos - 1; j++) {
                if (iEstadisticas[j] > iEstadisticas[j + 1]) {
                    auxNum = iEstadisticas[j];
                    iEstadisticas[j] = iEstadisticas[j + 1];
                    iEstadisticas[j + 1] = auxNum;

                    strcpy_s(aux, szPalabras[j]);
                    strcpy_s(szPalabras[j], szPalabras[j + 1]);
                    strcpy_s(szPalabras[j + 1], aux);
                }
            }
        }
    }
}

void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int* iNumElementos) {
    FILE* fp;
    char palabra[TAMTOKEN];
    *iNumElementos = 0;

    fp = NULL;
    if (fopen_s(&fp, szNombre, "r") != 0 || !fp) {
        perror("Error al abrir el archivo");
        return;
    }


    while (fscanf_s(fp, "%s", palabra, (unsigned int)TAMTOKEN) == 1) {
        QuitarCaracteres(palabra);
        strcpy_s(szPalabras[*iNumElementos], palabra);
        (*iNumElementos)++;
        if (*iNumElementos >= TAMTOKEN) {
            printf("Error: demasiadas palabras\n");
            break;
        }
    }

    fclose(fp);

    Eliminar(szPalabras, iNumElementos, iEstadisticas);
    Ordenar(szPalabras, *iNumElementos, iEstadisticas, 0);
}

void   ClonaPalabras(
    char* szPalabraLeida,                     // Palabra a clonar
    char    szPalabrasSugeridas[][TAMTOKEN],    //Lista de palabras clonadas
    int& iNumSugeridas)                      //Numero de elementos en la lista
{
    int longitud, posicion = 0;
    int i, j, m, jPalabra = 0, apuntador, jApuntador, contador;
    int posicion2 = 0;

    char letras[] = { "abcdefghijklmnopqrstuvwxyz" };
    char letras2[] = { "ñáéíóú" };

    //char szPalabraLeidaCopiaDef[TAMTOKEN];
    char szPalabraLeidaCopia[TAMTOKEN];
    char szPalabraLeidaCopia2[TAMTOKEN];
    char palabrafin[TAMTOKEN];
    char auxiliarPal[TAMTOKEN];
    char auxiliarPal2[TAMTOKEN];

    longitud = strlen(szPalabraLeida);

    for (i = 0; i < longitud; i++)
    {
        for (j = 0; j < strlen(letras); j++)
        {
            if (szPalabraLeida[i] == letras[j])
            {
                contador++;
            }
            else if (szPalabraLeida[i] == letras2[0])
            {
                posicion = i;
            }
        }
    }
    if (posicion != 0)
    {
        apuntador = 0;
        for (i = 0; i < longitud; i++)
        {
            if (szPalabraLeida[i] != letras2[1])
            {
                palabrafin[apuntador] = szPalabraLeida[i];
                apuntador++;
            }
        }
        strcpy(szPalabraLeida, palabrafin);
        longitud--;
    }

    //inicio eliminacion
    for (i = 0; i < longitud; i++)
    {
        apuntador = 0;
        memset(palabrafin, 0, 50);

        for (j = 0; j < longitud; j++)
        {
            if (i != j)
            {
                palabrafin[apuntador] = szPalabraLeida[j];
                apuntador++;
            }
        }
        //printf("\t%s\n",palabrafin);
        //printf("longitud: %i\n",longitud);
        jPalabra = revertir(posicion, palabrafin, szPalabrasSugeridas, jPalabra, longitud);
    }
    //fin eliminacion

    //inicio intercambio
    for (j = 1; j < longitud; j++)
    {
        strcpy(szPalabraLeidaCopia2, szPalabraLeida);
        strcpy(szPalabraLeidaCopia, szPalabraLeida);

        for (i = 0; i < longitud - j; i++)
        {
            szPalabraLeidaCopia2[i + j] = szPalabraLeidaCopia2[i + (j - 1)];
            szPalabraLeidaCopia2[i + (j - 1)] = szPalabraLeidaCopia[i + j];

            jPalabra = revertir(posicion, szPalabraLeidaCopia2, szPalabrasSugeridas, jPalabra, longitud);
        }
    }
    //fin intercambio

    //inicio cambio de caracteres
    for (i = 0; i < longitud; i++)
    {
        strcpy(szPalabraLeidaCopia, szPalabraLeida);

        for (j = 0; j < strlen(letras); j++)
        {
            szPalabraLeidaCopia[i] = letras[j];
            jPalabra = revertir(posicion, szPalabraLeidaCopia, szPalabrasSugeridas, jPalabra, longitud);
            //strcpy(szPalabrasSugeridas[jPalabra],szPalabraLeidaCopia);
        }
    }

    for (i = 0; i < longitud; i++)
    {
        strcpy(szPalabraLeidaCopia, szPalabraLeida);
        for (j = 0; j < 6; j++)
        {
            memset(auxiliarPal, 0, 50);
            memset(auxiliarPal2, 0, 50);

            apuntador = 0;
            for (m = 0; m < i; m++)
            {
                auxiliarPal[apuntador] = szPalabraLeidaCopia[m];
                apuntador++;
            }

            apuntador = 0;
            for (m = i + 1; m < longitud; m++)
            {
                auxiliarPal2[apuntador] = szPalabraLeidaCopia[m];
                apuntador++;
            }

            switch (j)
            {
            case 0:
                strcat(auxiliarPal, "ñ");
                strcat(auxiliarPal, auxiliarPal2);
                break;
            case 1:
                strcat(auxiliarPal, "á");
                strcat(auxiliarPal, auxiliarPal2);
                break;
            case 2:
                strcat(auxiliarPal, "é");
                strcat(auxiliarPal, auxiliarPal2);
                break;
            case 3:
                strcat(auxiliarPal, "í");
                strcat(auxiliarPal, auxiliarPal2);
                break;
            case 4:
                strcat(auxiliarPal, "ó");
                strcat(auxiliarPal, auxiliarPal2);
                break;
            case 5:
                strcat(auxiliarPal, "ú");
                strcat(auxiliarPal, auxiliarPal2);
                break;
            }
            jPalabra = revertir(posicion, auxiliarPal, szPalabrasSugeridas, jPalabra, longitud);
            //printf("aux: %s\n",auxiliarPal);
        }
    }
    //fin cambio de caracteres

    //inicio poner caracteres entre caracteres
    for (i = 0; i < longitud + 1; i++)
    {
        strcpy(szPalabraLeidaCopia, szPalabraLeida);
        for (j = 0; j < strlen(letras); j++)
        {
            memset(auxiliarPal, 0, 50);
            memset(auxiliarPal2, 0, 50);

            apuntador = 0;
            for (m = 0; m < i; m++)
            {
                auxiliarPal[apuntador] = szPalabraLeidaCopia[m];
                apuntador++;
            }
            auxiliarPal[apuntador] = letras[j];

            apuntador = 0;
            for (m = i; m < longitud; m++)
            {
                auxiliarPal2[apuntador] = szPalabraLeidaCopia[m];
                apuntador++;
            }

            strcat(auxiliarPal, auxiliarPal2);
            //printf("%s\n",auxiliar);
            jPalabra = revertir(posicion, auxiliarPal, szPalabrasSugeridas, jPalabra, longitud);
        }
    }
    //fin poner caracteres entre caracteres

    iNumSugeridas = jPalabra + 1;
}
