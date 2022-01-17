/*************************
 * Ingenieria en Computación - UNRN Andina
 * Programación 1
 * minombredeusuario de GitHub: BrunoMayo
*************************/



#include <stdio.h>
#include <stdlib.h>


void minas(int **tablero, int filas, int columnas); //Permite ubicar donde se desee las minas
void llenar_interior(int **tablero, int filas, int columnas); //Completa el tablero exceptuando los bordes
void llenar_bordes(int **tablero, int filas, int columnas); //Completa los bordes del tablero


int main()
{
    FILE* ptr_tablero = fopen("Buscaminas.txt", "w"); //Abre el archivo donde se guardará el tablero
    FILE* ptr_dimensiones = fopen("dimensiones.txt", "w"); //Abre el archivo donde se guardarán las dimensiones del tablero;

    if (ptr_tablero == NULL) //chequea que el archivo exista
    {
        printf("Error: no se pudo leer el archivo Buscaminas.txt");
    }
    if (ptr_dimensiones == NULL) //chequea que el archivo exista
    {
        printf("Error: no se pudo leer el archivo dimensiones.txt");
    }

    
    int columnas;
    int filas;
    int **tablero;


    //Obtiene la cantidad de columnas
    do
    {
        printf("\nIngrese la cantidad de columnas: ");
        scanf("%d", &columnas);
    }while(columnas < 1);

    
    //Obtiene la cantidad de filas
    do
    {
        printf("\nIngrese la cantidad de filas: ");
        scanf("%d", &filas);
    }while(filas < 1);


    fprintf(ptr_dimensiones, "%d\n%d", filas, columnas); //Imprimo las dimensiones del tablero (Es para usar en la segunda parte del programa)
    fclose(ptr_dimensiones);


    tablero = malloc(sizeof(int*) * filas); //Crea la matriz donde se almacenará el tablero. Primero crea un array de tamaño igual a filas
    for (int i = 0; i < filas; i++)
    {
        tablero[i] = malloc(sizeof(int) * columnas); //crea un array dentro de cada array filas de tamaño igual a columnas
    }

    //Ejecuto las 3 funciones que conforman el tablero
    minas( tablero, filas, columnas);
    llenar_interior(tablero, filas, columnas);    
    llenar_bordes(tablero, filas, columnas);
    
    
    
    for (int i = 0; i < filas; i++) //Donde hay un 9 o un numero mayo coloco una mina y lo imprimo en un archivo txt
    {
        for (int j = 0; j < columnas; j++)
        {
            if(tablero[i][j] > 8)
            {  
                fprintf(ptr_tablero, "*");
            }
            else
            {   
                fprintf(ptr_tablero, "%d", tablero[i][j]);
            }
        }
        fprintf(ptr_tablero, "\n");
        
    }

    
    fclose(ptr_tablero);
    free(tablero);
    tablero = NULL;

    return 0;
    


}




void minas(int **tablero, int filas, int columnas) //Permite disponer las minas en donde se desee
{
    int minas;
    int f;
    int c;    

    printf("\nIngrese cuantas minas habra en el juego: "); //Se pide al usuario cuantas mians desea usar
    scanf("%d", &minas);
    while(minas > columnas*filas || minas < 1)
    {
        if(minas > columnas*filas)
        {
            printf("No pueden haber mas minas que casilleros. Ingrese un nuevo numero: ");
            scanf("%d", &minas);
        }
        else 
        {
            printf("Debe haber por lo menos una mina. Ingrese un nuevo numero: ");
            scanf("%d", &minas);
        }
    } 
    
    for (int i = 0; i < minas; i++)
    {
        do
        {
            printf("\nIngrese donde desea colocar la mina numero %d\nFila: ", i + 1); //Se colocan las minas en el tablero
            scanf("%d", &f);
        } while (f >= filas || f < 0);

        do
        {
            printf("Columna: ");
            scanf("%d", &c);
        } while (c >= columnas || c < 0);    

        tablero[f][c] = 9;
    }

}



void llenar_interior(int **tablero, int filas, int columnas) //Se forma el tablero sin los bordes
{

    for (int i = 1; i < filas-1; i++)   //Inicializo el loop en 1 y lo finalizo en filas -1 para que no llegue a los límites
    {
        for (int j = 1; j < columnas-1; j++) //Inicializo el loop en 1 y lo finalizo en columnas -1 para que no llegue a los límites
        {   

            if (tablero[i][j] > 8)
            {
                tablero[i-1][j-1] = tablero[i-1][j-1] + 1;
                tablero[i-1][j] = tablero[i-1][j] + 1;
                tablero[i-1][j+1] = tablero[i-1][j+1] + 1;
                tablero[i][j-1] = tablero[i][j-1] + 1;
                tablero[i][j] = tablero[i][j] + 1;
                tablero[i][j+1] = tablero[i][j+1] + 1;
                tablero[i+1][j-1] = tablero[i+1][j-1] + 1;
                tablero[i+1][j] = tablero[i+1][j] + 1;
                tablero[i+1][j+1] = tablero[i+1][j+1] + 1;
            }
            
            
        }
        
    }


}




void llenar_bordes(int **tablero, int filas, int columnas) //Se completan los bordes del tablero
{
    for (int i = 0; i < filas; i++)   
    {
        for (int j = 0; j < columnas; j++)
        {
            if(tablero[i][j] > 8 && i == 0) //Completo en caso de que haya una mina en el borde superior incluyendo las esquinas superiores
            {
                tablero[i+1][j] = tablero[i+1][j] + 1;
                if(j == 0)
                {
                    tablero[i][j+1] = tablero[i][j+1] + 1;
                    tablero[i+1][j+1] = tablero[i+1][j+1] + 1; 
                }
                if(j == columnas - 1)
                {
                    tablero[i][j-1] = tablero[i][j-1] + 1;
                    tablero[i+1][j-1] = tablero[i+1][j-1] + 1;
                }
                if(j != 0 && j != columnas - 1)
                {
                    tablero[i][j-1] = tablero[i][j-1] + 1;
                    tablero[i][j+1] = tablero[i][j+1] + 1;
                    tablero[i+1][j-1] = tablero[i+1][j-1] + 1;
                    tablero[i+1][j+1] = tablero[i+1][j+1] + 1;
                }
            }
            if(tablero[i][j] > 8 && i == filas - 1) //Completo en caso de que haya una mina en el borde inferior incluyendo las esquinas inferiores
            {
                tablero[i-1][j] = tablero[i-1][j] + 1;
                if(j == 0)
                {
                    tablero[i-1][j+1] = tablero[i-1][j+1] + 1;
                    tablero[i][j+1] = tablero[i][j+1] + 1; 
                }
                if(j == columnas - 1)
                {
                    tablero[i-1][j-1] = tablero[i-1][j-1] + 1;
                    tablero[i][j-1] = tablero[i][j-1] + 1;
                }
                if(j != 0 && j != columnas - 1)
                {
                    tablero[i][j-1] = tablero[i][j-1] + 1;
                    tablero[i][j+1] = tablero[i][j+1] + 1;
                    tablero[i-1][j-1] = tablero[i-1][j-1] + 1;
                    tablero[i-1][j+1] = tablero[i-1][j+1] + 1;
                }
            }   
            if(tablero[i][j] > 8 && j == 0 && i != 0 && i != filas - 1) //Completo en caso de que haya una mina en el borde izquierdo sin incluir esquinas
            {
                tablero[i-1][j] = tablero[i-1][j] + 1;
                tablero[i+1][j] = tablero[i+1][j] + 1;
                tablero[i-1][j+1] = tablero[i-1][j+1] + 1;
                tablero[i][j+1] = tablero[i][j+1] + 1;
                tablero[i+1][j+1] = tablero[i+1][j+1] + 1;
            }
            if(tablero[i][j] > 8 && j == columnas - 1 && i != 0 && i != filas - 1) //Completo en caso de que haya una mina en el borde superior sin incluir esquinas
            {
                tablero[i-1][j] = tablero[i-1][j] + 1;
                tablero[i+1][j] = tablero[i+1][j] + 1;
                tablero[i-1][j-1] = tablero[i-1][j-1] + 1;
                tablero[i][j-1] = tablero[i][j-1] + 1;
                tablero[i+1][j-1] = tablero[i+1][j-1] + 1;
            }
        }
    }


}



