/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion.
	(c) Ponga su nombre y numero de cuenta aqui.
 Oscar Gabriel Hernández Luna 
 322328071

	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.

******************************************************************************************************************/
#include "stdafx.h"
#include <string.h>
#include "corrector.h"
//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
	FILE* fp = nullptr; // Puntero al archivo
	char buffer[300];   // Buffer temporal para leer líneas del archivo
	iNumElementos = 0;  // Inicializamos el contador de elementos


	errno_t err = fopen_s(&fp, szNombre, "r");
	if (err != 0 || fp == nullptr) {
		return;
	}
	
// Lee archivo línea a línea con el buffer
	while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
		char* start = buffer;
		while (*start != '\0') {

			while (*start == ' ' || *start == '\n' || *start == '\r')
				start++;

			if (*start == '\0') // Cuando es fin de linea
				break;

			// Condiciones para encontrar fin
			char* end = start;
			while (*end != ' ' && *end != '\n' && *end != '\r' && *end != '\0')
				end++;


			size_t length = end - start;
			if (length > 0 && length < TAMTOKEN) {
				if (iNumElementos >= TAMTOKEN)
					break;

				//Copiar
				strcpy_s(szPalabras[iNumElementos], TAMTOKEN, start, length);
				szPalabras[iNumElementos][length] = '\0';

				//Se pone en 1 la cantidad de veces que aparece
				iEstadisticas[iNumElementos] = 1;
				iNumElementos++;
			}
			start = end;
		}
	}

	// Cerrar el archivo
	fclose(fp);

}

/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void ListaCandidatas(
	char szPalabrasSugeridas[][TAMTOKEN],
	int iNumSugeridas,
	char szPalabras[][TAMTOKEN],
	int iEstadisticas[],
	int iNumElementos,
	char szListaFinal[][TAMTOKEN],
	int iPeso[],
	int& iNumLista)
{
	iNumLista = 0; // Inicializamos el contador de la lista final

	for (int i = 0; i < iNumSugeridas; i++) {
		for (int j = 0; j < iNumElementos; j++) {
			if (strcmp(szPalabrasSugeridas[i], szPalabras[j]) == 0) {
				// Palabra encontrada en el diccionario
				strcpy_s(szListaFinal[iNumLista], szPalabras[j]);
				iPeso[iNumLista] = iEstadisticas[j];
				iNumLista++;
			}
		}
	}

	// Ordenar szListaFinal por peso (burbuja por simplicidad)
	for (int i = 0; i < iNumLista - 1; i++) {
		for (int j = i + 1; j < iNumLista; j++) {
			if (iPeso[i] < iPeso[j]) {
				// Intercambiar palabras
				char tempPalabra[TAMTOKEN];
				strcpy_s(tempPalabra, szListaFinal[i]);
				strcpy_s(szListaFinal[i], szListaFinal[j]);
				strcpy_s(szListaFinal[j], tempPalabra);

				// Intercambiar pesos
				int tempPeso = iPeso[i];
				iPeso[i] = iPeso[j];
				iPeso[j] = tempPeso;
			}
		}
	}
}
//Da inicio a una función revertir
int revertir(int posicion, char szPalabraLeidaCopia2[TAMTOKEN], char szPalabrasSugeridas[][TAMTOKEN], int newPal, int longitud);
int revertir(int posicion, char szPalabraLeidaCopia2[TAMTOKEN], char szPalabrasSugeridas[][TAMTOKEN], int newPal, int longitud)
{
    strcpy_s(szPalabrasSugeridas[newPal], szPalabraLeidaCopia2);
    return newPal + 1;
}
// Función clonapalabra
void ClonaPalabras(
    char *szPalabraLeida,                     // Palabra a clonar
    char szPalabrasSugeridas[][TAMTOKEN],    // Lista de palabras clonadas
    int &iNumSugeridas)                      // Número de elementos en la lista
{
    int longitud, posicion = 0;
    int i, conta, newPal = 0, apuntador;
    char letras[] = {"abcdefghijklmnopqrstuvwxyzáéíóú"};  // Abecedario
    //char letras2[] = {"áéíóú"};            // Caracteres especiales
    char szPalabraLeidaCopia[TAMTOKEN], auxilPalab[TAMTOKEN], auxilPalab2[TAMTOKEN];

    longitud = strlen(szPalabraLeida);


    for (i = 0; i < longitud; i++) {
        apuntador = 0;
        memset(auxilPalab, 0, TAMTOKEN);

        for (conta = 0; conta < longitud; conta++) {
            if (i != conta) {  // Pone las letras menos la eliminada
                auxilPalab[apuntador++] = szPalabraLeida[conta];
            }
        }
        newPal = revertir(posicion, auxilPalab, szPalabrasSugeridas, newPal, longitud - 1);
    }


    for (i = 0; i < longitud - 1; i++) {
        strcpy_s(szPalabraLeidaCopia, szPalabraLeida);
        char temp = szPalabraLeidaCopia[i];
        szPalabraLeidaCopia[i] = szPalabraLeidaCopia[i + 1];
        szPalabraLeidaCopia[i + 1] = temp;

        newPal = revertir(posicion, szPalabraLeidaCopia, szPalabrasSugeridas, newPal, longitud);
    }


    for (i = 0; i < longitud; i++) {
        strcpy_s(szPalabraLeidaCopia, szPalabraLeida);

        for (conta = 0; conta < strlen(letras); conta++) {
            szPalabraLeidaCopia[i] = letras[conta];  // Sustituye cada letra en la posición actual

            newPal = revertir(posicion, szPalabraLeidaCopia, szPalabrasSugeridas, newPal, longitud);

						/*szPalabraLeidaCopia[i] = letras2[j]; //Sustituye cada letra con las especiales

						newPal = revertir(posicion, szPalabraLeidaCopia, szPalabrasSugeridas, newPal, longitud);*/
        }
    }


    for (i = 0; i <= longitud; i++) {
        for (conta = 0; conta < strlen(letras); conta++) {
            memset(auxilPalab, 0, TAMTOKEN);
            memset(auxilPalab2, 0, TAMTOKEN);

            // Copia las letras antes de la posición de inserción
            strcpy_s(auxilPalab, szPalabraLeida, i);

            // Inserta el carácter del alfabeto
            auxilPalab[i] = letras[conta];

            // Copia las letras después de la posición de inserción
            strcpy_s(auxilPalab2, &szPalabraLeida[i]);

            strcat_s(auxilPalab, auxilPalab2);  // Combina las dos partes
            newPal = revertir(posicion, auxilPalab, szPalabrasSugeridas, newPal, longitud + 1);
        }
    }

    iNumSugeridas = newPal;
}

