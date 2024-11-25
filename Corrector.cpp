
//Codigo sin comentarios
#include "stdafx.h"
#include <string.h>
#include "corrector.h"

void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
	FILE* fp = nullptr; 
	char buffer[300];  
	iNumElementos = 0;  


	errno_t err = fopen_s(&fp, szNombre, "r");
	if (err != 0 || fp == nullptr) {
		return;
	}
	
	while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
		char* start = buffer;
		while (*start != '\0') {

			while (*start == ' ' || *start == '\n' || *start == '\r')
				start++;

			if (*start == '\0') 
				break;

			
			char* end = start;
			while (*end != ' ' && *end != '\n' && *end != '\r' && *end != '\0')
				end++;


			size_t length = end - start;
			if (length > 0 && length < TAMTOKEN) {
				if (iNumElementos >= TAMTOKEN)
					break;

				strcpy_s(szPalabras[iNumElementos], TAMTOKEN, start, length);
				szPalabras[iNumElementos][length] = '\0';

				iEstadisticas[iNumElementos] = 1;
				iNumElementos++;
			}
			start = end;
		}
	}


	fclose(fp);

}


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
	iNumLista = 0; 

	for (int i = 0; i < iNumSugeridas; i++) {
		for (int j = 0; j < iNumElementos; j++) {
			if (strcmp(szPalabrasSugeridas[i], szPalabras[j]) == 0) {
				strcpy_s(szListaFinal[iNumLista], szPalabras[j]);
				iPeso[iNumLista] = iEstadisticas[j];
				iNumLista++;
			}
		}
	}

	for (int i = 0; i < iNumLista - 1; i++) {
		for (int j = i + 1; j < iNumLista; j++) {
			if (iPeso[i] < iPeso[j]) {
				char tempPalabra[TAMTOKEN];
				strcpy_s(tempPalabra, szListaFinal[i]);
				strcpy_s(szListaFinal[i], szListaFinal[j]);
				strcpy_s(szListaFinal[j], tempPalabra);
				int tempPeso = iPeso[i];
				iPeso[i] = iPeso[j];
				iPeso[j] = tempPeso;
			}
		}
	}
}

int revertir(int posicion, char szPalabraLeidaCopia2[TAMTOKEN], char szPalabrasSugeridas[][TAMTOKEN], int newPal, int longitud);
int revertir(int posicion, char szPalabraLeidaCopia2[TAMTOKEN], char szPalabrasSugeridas[][TAMTOKEN], int newPal, int longitud)
{
    strcpy_s(szPalabrasSugeridas[newPal], szPalabraLeidaCopia2);
    return newPal + 1;
}
// Función clonapalabra
void ClonaPalabras(
    char *szPalabraLeida,                  
    char szPalabrasSugeridas[][TAMTOKEN],  
    int &iNumSugeridas)                    
{
    int longitud, posicion = 0;
    int i, conta, newPal = 0, apuntador;
    char letras[] = {"abcdefghijklmnopqrstuvwxyzáéíóú"};     
    char szPalabraLeidaCopia[TAMTOKEN], auxilPalab[TAMTOKEN], auxilPalab2[TAMTOKEN];

    longitud = strlen(szPalabraLeida);


    for (i = 0; i < longitud; i++) {
        apuntador = 0;
        memset(auxilPalab, 0, TAMTOKEN);

        for (conta = 0; conta < longitud; conta++) {
            if (i != conta) {  
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
            szPalabraLeidaCopia[i] = letras[conta];  

            newPal = revertir(posicion, szPalabraLeidaCopia, szPalabrasSugeridas, newPal, longitud);

						
        }
    }


    for (i = 0; i <= longitud; i++) {
        for (conta = 0; conta < strlen(letras); conta++) {
            memset(auxilPalab, 0, TAMTOKEN);
            memset(auxilPalab2, 0, TAMTOKEN);

            
            strcpy_s(auxilPalab, szPalabraLeida, i);

            
            auxilPalab[i] = letras[conta];

            
            strcpy_s(auxilPalab2, &szPalabraLeida[i]);

            strcat_s(auxilPalab, auxilPalab2);  
            newPal = revertir(posicion, auxilPalab, szPalabrasSugeridas, newPal, longitud + 1);
        }
    }

    iNumSugeridas = newPal;
}
