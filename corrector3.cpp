#include <stdio.h>
#define LIMITE 2000
int main()
{

    int limcalificaciones;
    int contador, contador2, lis;
    int numcuenta[LIMITE];
    double calificacion[LIMITE];

    scanf ("%d", &limcalificaciones);

    for (contador=0;contador<limcalificaciones;contador++)
    {
    scanf ("%i", &numcuenta[contador]);
    scanf ("%lf", &calificacion[contador]);
    }

        //Acomodar numcuenta menor-mayor
        for (contador=0;contador<limcalificaciones-1;contador++)
            {
            for (contador2=0;contador2<(limcalificaciones-contador-1);contador2++)
            {
            if (numcuenta[contador2]>numcuenta[contador2+1])
            {
                int tempX = numcuenta[contador2];
                numcuenta[contador2] = numcuenta[contador2+1];
                numcuenta[contador2+1] = tempX;

                double tempY = calificacion[contador2];
                calificacion[contador2] = calificacion[contador2+1];
                calificacion[contador2+1] = tempY;
            }
            }

            /Eliminar numcuenta repetido
            for (contador=0;contador<limcalificaciones;contador++)
            {/
                if (numcuenta[contador] == numcuenta[contador+1] && calificacion[contador] > calificacion[contador+1]) {
            calificacion[contador+1] = 0;
            numcuenta[contador+1] = 0;
        }
                if (numcuenta[contador] == numcuenta[contador+1] && calificacion[contador] < calificacion[contador+1]) {
            calificacion[contador] = 0;
            numcuenta[contador] = 0;
        }}
        //Revisión final
        for (contador=0;contador<=limcalificaciones;contador++) {
    if (numcuenta[contador] == numcuenta[contador+1] && calificacion[contador] > calificacion[contador+1]) {
            calificacion[contador+1] = 0;
            numcuenta[contador+1] = 0;
        }
                if (numcuenta[contador] == numcuenta[contador+1] && calificacion[contador] < calificacion[contador+1]) {
            calificacion[contador] = 0;
            numcuenta[contador] = 0;
        }}
    //Imprimir valores

    lis = 0;
for (contador = 0; contador < limcalificaciones; contador++) {
    if (numcuenta[contador] > 0) {
        lis++;
    }
}
        printf("%i\n", lis);
        //printf("%i\n", limcalificaciones);
    for (contador=0;contador<limcalificaciones;contador++)
    {

        if (numcuenta[contador] > 0) 
        printf("%i %.2lf\n", numcuenta[contador], calificacion[contador]);}
}
