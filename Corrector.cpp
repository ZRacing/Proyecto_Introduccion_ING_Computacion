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

	// Abrir el archivo en modo lectura
	errno_t err = fopen_s(&fp, szNombre, "r");
	if (err != 0 || fp == nullptr) {
		return;
	}

	// Leer el archivo línea por línea
	while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
		// Procesar cada palabra en la línea
		char* token = strtok(buffer, " \n\r"); // Separar palabras por espacios o saltos de línea
		while (token != nullptr) {
			// Verificar que no exceda el tamaño máximo de elementos
			if (iNumElementos >= TAMTOKEN) {
				break;
			}

			// Copiar la palabra al arreglo de palabras
			strcpy_s(szPalabras[iNumElementos], TAMTOKEN, token);

			// Inicializar la estadística de aparición
			iEstadisticas[iNumElementos] = 1;

			// Incrementar el contador de palabras
			iNumElementos++;

			// Obtener el siguiente token
			token = strtok(nullptr, " \n\r");
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

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
// Función ClonaPalabras
void ClonaPalabras(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas) {
	iNumSugeridas = 0;
	for (int i = 0; i < strlen(szPalabraLeida); i++) {
		char palabraModificada[TAMTOKEN];
		strcpy_s(palabraModificada, TAMTOKEN, szPalabraLeida);
		memmove(&palabraModificada[i], &palabraModificada[i + 1], strlen(szPalabraLeida) - i);
		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], TAMTOKEN, palabraModificada);
	}
}
