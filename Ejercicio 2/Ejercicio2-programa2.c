/**********************+++++++++++++++++***
 * Ingenieria en Computación - UNRN Andina
 * Programación 1
 * minombredeusuario de GitHub: BrunoMayo
****+++++++++++++++++*********************/


#include <stdio.h>
#include <stdlib.h>


void juego(char **copiar_tablero, char **revelar_tablero, int filas, int columnas, int *contador_minas); //Acá se guarda la estructura del buscaminas, hecha a partir de otras funciones



int main()
{
    FILE *ptr_tablero = fopen("Buscaminas.txt", "r"); //Abro el archivo en donde esta guardado el tablero
    FILE *ptr_tamaño = fopen("dimensiones.txt", "r"); //Abro el archivo con las dimensiones del tablero
    
    int filas = 0; //Aca se va a guardar la cantidad de filas que tiene el tablero
    int columnas = 0; //Aca se va a guardar la cantidad de columnas que tiene el tablero
    char **copiar_tablero;
    char **revelar_tablero;
    int contador_minas[3] = {0, 0, 0};
    

 
    if (ptr_tamaño == NULL) //chequea que el archivo exista
    {
        printf("Error: no se pudo leer el archivo dimensiones.txt");
    }
    else //Copia las dimensiones del tablero a las variables filas y columnas  
    {
        
        fscanf(ptr_tamaño, "%d", &filas);
        fscanf(ptr_tamaño, "%d", &columnas);
    
        fclose(ptr_tamaño); //cierra el archivo
    }

    
    copiar_tablero = malloc(sizeof(char*) * filas); //Crea la matriz donde se copìara el tablero. Primero crea un array de tamaño igual a filas
    for (int i = 0; i < filas; i++)
    {
        copiar_tablero[i] = malloc(sizeof(char) * columnas); //crea un array dentro de cada array filas de tamaño igual a columnas
    }

    revelar_tablero = malloc(sizeof(char*) * filas); //Crea la matriz donde se iran revelando los casilleros en el tablero. Es de igual tamaño que copiar_tablero
    for (int i = 0; i < filas; i++)
    {
        revelar_tablero[i] = malloc(sizeof(char) * columnas);
    }
    


    if (ptr_tablero == NULL) //chequea que el archivo exista
    {
        printf("Error: no se pudo leer el archivo Buscaminas.txt");
    }
    else  //Copia el tablero a la matriz copiar_tablero
    {
        int i = 0;
        while (!feof(ptr_tablero)) //copia los strings a texto
        {
            fscanf(ptr_tablero, "%s", &copiar_tablero[i][0]);
            i = i + 1;
        }

        fclose(ptr_tablero); //cierra el archivo
    }

    
    juego(copiar_tablero, revelar_tablero, filas, columnas, contador_minas); //LLamo a la funcion en donde esta la estructura del buscaminas
    
    free(copiar_tablero);
    copiar_tablero = NULL;
    free(revelar_tablero);
    revelar_tablero = NULL;


    return 0;

}



void llenar_revelar_tablero(char **revelar_tablero, int filas, int columnas) //Esta funcion completa la matriz revelar tablero de espacios vacios
{
        for (int i = 0; i < filas; i++)
        {
            for (int j = 0; j < columnas; j++)
            {
                revelar_tablero[i][j] = ' ';
            }
            
        }    
}






void imprimir_tablero(char **copiar_tablero, char **revelar_tablero, int filas, int columnas) //Esta funcion crea la versión grafica del tablero que se muestra en la consola.
{
    //Se explican las acciones posibles
    printf("\n\nPresione [ M ] y luego enter si desea marcar una mina.\n");
    printf("Presione [ D ] y luego enter si desea descubrir una mina.\n");
    printf("Presione [ E ] y luego enter si desea salir.\n\n\n");
    
    
    
    for (int m = -1; m < columnas; m++) //Esta primera parte genera el indice superior del tablero
    {
        printf("+-----");
    }
    printf("+\n");
    for (int n = -1; n < columnas; n++) 
    {   
        if ( n >= 0 && n < 10)
        {
            printf("| C %d ", n);
        }
        else if (n > 9)
        {
            printf("| C%d ", n);
        }
        else
        {
            printf("|  X  ");
        }
    }
    printf("|\n");


    
    for (int i = 0; i < filas; i++) //Esta parte genera el tablero
    {
        
        for (int k = -1; k < columnas; k++)
        {
            printf("+-----");
        }
        printf("+\n");

        for (int j = -1; j < columnas; j++)
        {   
            if ( j == -1 && i < 10)         //
            {                               //
                printf("| F %d ", i);       //
            }                               // Esta parte va a generar el indice izuierdo
            else if (j == -1 && i > 9 )     //
            {                               //
                printf("| F%d ", i);        //
            }                               //
            else
            {
                printf("|  %c  ", revelar_tablero[i][j]);
            }
        }
        printf("|\n");
    }

    for (int m = -1; m < columnas; m++)
    {
        printf("+-----");
    }
    printf("+\n");
    
    
}







void descubrir_celda(char **copiar_tablero, char **revelar_tablero, int filas, int columnas) //Esta función descubre las celdas elegidas por el usuario
{
    //Aca se guardan las coordenadas ingresadas por el jugador
    int f = 0; 
    int c = 0; 

    printf("Inserte las coordenadas de la celda\nFila: "); //Pide y guarda el input del usuario
    scanf("%d", &f);

    while (f > filas-1)
    {
        printf("El numero no puede ser mayor a %d\nIngrese un nuevo numero: ", filas-1);
        scanf("%d", &f);
    }
    
    printf("Columna: "); //Pide y guarda el input del usuario
    scanf("%d", &c);
    
    while (c > columnas-1)
    {
        printf("El numero no puede ser mayor a %d\nIngrese un nuevo numero: ", columnas-1);
        scanf("%d", &c);
    }

    if(copiar_tablero[f][c] == '*' && revelar_tablero[f][c] != 'M') //Si el casillero tiene una mina, la muestra y termina el programa 
    {
        revelar_tablero[f][c] = copiar_tablero[f][c];
        imprimir_tablero(copiar_tablero, revelar_tablero, filas, columnas);
        printf("\n*************************\n* ¡OH NO, ERA UNA MINA! *\n*************************\n");
        exit(1);
    }
    else if(copiar_tablero[f][c] != '0' && revelar_tablero[f][c] != 'M') //Si el jugador descubre un numero se muestra ese casillero solo.
    {
        revelar_tablero[f][c] = copiar_tablero[f][c];
    }
    else if (revelar_tablero[f][c] != 'M') //Si el jugador descubre un 0 se muestran los casillero vacios adyacentes
    { 

        
        if(copiar_tablero[f][c] == '0') //Chequea que el casillero este en 0;
        {
                    
            if(f > 0 && c > 0 && f < filas-1 && c < columnas-1) //Si no esta en un borde, desbloquea el casillero y  todos los casilleros de al rededor
            {
                for(int i = -1; i < 2; i++) 
                {
                    for(int j = -1; j < 2; j++)
                    {
                        revelar_tablero[f+i][c+j] = copiar_tablero[f+i][c+j];
                    }
                }    
            }
            if(f == 0 && c == 0) //Si esta en la esquina superior izquierda, se desbloquea el casillero, el  de la derecha, el de abajo y el de abajo a la derecha
            {
                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        revelar_tablero[f+i][c+j] = copiar_tablero[f+i][c+j];       
                    }
                }
            }
            else if (f == 0 && c == columnas-1) //Si esta en la esquina superior derecha, se desbloquea el casillero, el de la izquierda, el de abajo y el de abajo a la izquierda
            {
                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        revelar_tablero[f+i][c-j] = copiar_tablero[f+i][c-j];       
                    }
                }
            } 
            else if (f == filas - 1 && c == 0) //Si esta en la esquina inferior izquierda, se desbloquea el casillero, el de la derecha, el de arriba y el de arriba a la derecha
            {
                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        revelar_tablero[f-i][c+j] = copiar_tablero[f-i][c+j];       
                    }
                }
            }
            else if (f == filas - 1 && c == columnas - 1) //Si esta en la esquina inferior derecha, se desbloquea el casillero, el de la izquierda, el de arriba y el de arriba a la izquierda
            {
                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        revelar_tablero[f-i][c-j] = copiar_tablero[f-i][c-j];       
                    }
                }
            }
            else if (f == 0) //Si se encuentra en el borde superior se desbloquea el casillero, los de los costados y los de abajo
            {
                for (int i = 0; i < 2; i++)
                {
                    for (int j = -1; j < 2; j++)
                    {
                        revelar_tablero[f+i][c+j] = copiar_tablero[f+i][c+j];       
                    }
                }
            }
            else if (f == filas - 1) //Si se encuentra en el borde inferior se desbloquea el casillero, los de los costados y los de arriba
            {
                for (int i = 0; i < 2; i++)
                {
                    for (int j = -1; j < 2; j++)
                    {
                        revelar_tablero[f-i][c+j] = copiar_tablero[f-i][c+j];       
                    }
                }
            }
            else if (c == 0) //Si se encuentra en el borde izquierdo se desbloquea el casillero, el de arriba, el de abajo y los de la derecha
            {
                for (int i = -1; i < 2; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        revelar_tablero[f+i][c+j] = copiar_tablero[f+i][c+j];       
                    }
                }
            }
            else if (c == columnas-1) //Si se encuenra en el borde derecho se desbloquea el casillero, el de arriba, el de abajo i los de la izquierda
            {
                for (int i = -1; i < 2; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        revelar_tablero[f+i][c-j] = copiar_tablero[f+i][c-j];       
                    }
                }
            }
                    
        }






        int t = 0;

        //Se itera por todo el casillero y cuando se encuentra un casillero desbloqueado en 0, se desbloquean los de al rededor
        while (t < columnas * filas) //Esto se hace filas * columnas veces, de esta manera me aseguro que si o si se desbloqueen todos los 0 que se deben desbloquear
        {
            for (int ii = 0; ii < filas; ii++)
            {
                for (int jj = 0; jj < columnas; jj++)
                {                
                    if(revelar_tablero[ii][jj] == '0')
                    {
                        if(ii > 0 && jj > 0 && ii < filas-1 && jj < columnas-1) //Caso en el que no esta en el borde
                        {    
                            for (int i = -1; i < 2; i++)
                            {
                                for (int j = -1; j < 2; j++)
                                {                                                                    
                                    revelar_tablero[ii+i][jj+j] = copiar_tablero[ii+i][jj+j];                                    
                                }
                            }
                        }
                        else if(ii == 0 && jj == 0) //Caso en el que este en la esquina superior izquierda
                        {
                            for (int i = 0; i < 2; i++)
                            {
                                for (int j = 0; j < 2; j++)
                                {                                                                    
                                    revelar_tablero[ii+i][jj+j] = copiar_tablero[ii+i][jj+j];                                    
                                }
                            }
                        }
                        else if(ii == 0 && jj == columnas-1) //Caso en el que esta en la esquina superior derecha
                        {
                            for (int i = 0; i < 2; i++)
                            {
                                for (int j = 0; j < 2; j++)
                                {                                                                    
                                    revelar_tablero[ii+i][jj-j] = copiar_tablero[ii+i][jj-j];                                    
                                }
                            }
                        }
                        else if(ii == filas-1 && jj == 0) //Caso en el que esta en la esquina inferior izquierda
                        {
                            for (int i = 0; i < 2; i++)
                            {
                                for (int j = 0; j < 2; j++)
                                {                                                                    
                                    revelar_tablero[ii-i][jj+j] = copiar_tablero[ii-i][jj+j];                                    
                                }
                            }
                        }
                        else if(ii == filas-1 && jj == columnas-1) //Caso en el que esta en la esquina inferior derecha
                        {
                            for (int i = 0; i < 2; i++)
                            {
                                for (int j = 0; j < 2; j++)
                                {                                                                    
                                    revelar_tablero[ii-i][jj-j] = copiar_tablero[ii-i][jj-j];                                    
                                }
                            }
                        }
                        else if(ii == 0) //Caso en el que esta en el borde superior
                        {
                            for (int i = 0; i < 2; i++)
                            {
                                for (int j = -1; j < 2; j++)
                                {                                                                    
                                    revelar_tablero[ii+i][jj+j] = copiar_tablero[ii+i][jj+j];                                    
                                }
                            }
                        }
                        else if(ii == filas-1) //Caso en el que esta en el borde inferior
                        {
                            for (int i = 0; i < 2; i++)
                            {
                                for (int j = -1; j < 2; j++)
                                {                                                                    
                                    revelar_tablero[ii-i][jj+j] = copiar_tablero[ii-i][jj+j];                                    
                                }
                            }
                        }
                        else if(jj == 0) //Caso en el que esta en el borde izquierdo
                        {
                            for (int i = -1; i < 2; i++)
                            {
                                for (int j = 0; j < 2; j++)
                                {                                                                    
                                    revelar_tablero[ii+i][jj+j] = copiar_tablero[ii+i][jj+j];                                    
                                }
                            }
                        }
                        else if(jj == columnas-1) //Caso en el que esta en el borde derecho
                        {
                            for (int i = -1; i < 2; i++)
                            {
                                for (int j = 0; j < 2; j++)
                                {                                                                    
                                    revelar_tablero[ii+i][jj-j] = copiar_tablero[ii+i][jj-j];                                    
                                }
                            }
                        }    
                    }
                }           
            }
            t = t + 1;
        }
        

    } 
}
 











void marcar_mina(char **copiar_tablero, char **revelar_tablero, int filas, int columnas, int *contador_minas) //Esta funcion se encarga del marcado de minas
{
    int contar_minas = 0; 
    

    for (int i = 0; i < filas; i++) //Cuenta la cantidad de minas
    {
        for (int j = 0; j < columnas; j++)
        {
            if(copiar_tablero[i][j] == '*')
            {
                contar_minas = contar_minas + 1;
            }
        }    
    }

    contador_minas[0] = contar_minas;  //Se almacena la cantidad de minas
    

    int marcar_filas; //Se almacena la fila a marcar
    int marcar_columnas; //Se almacena la columna a amrcar

    
    printf("Inserte las coordenadas de la celda\nFila: "); //Pide y guarda el input del usuario
    scanf("%d", &marcar_filas);

    while (marcar_filas > filas-1)
    {
        printf("El numero no puede ser mayor a %d\nIngrese un nuevo numero: ", filas-1);
        scanf("%d", &marcar_filas);
    }
    
    printf("Columna: "); //Pide y guarda el input del usuario
    scanf("%d", &marcar_columnas);
    
    while (marcar_columnas > columnas-1)
    {
        printf("El numero no puede ser mayor a %d\nIngrese un nuevo numero: ", columnas-1);
        scanf("%d", &marcar_columnas);
    }


    
    
    if(copiar_tablero[marcar_filas][marcar_columnas] == '*') //Si se marca una mina
    {
        contador_minas[2] = contador_minas[2] + 1;//Se almacena en el contador de minas marcadas    
        contador_minas[1] = contador_minas[1] + 1;//Se almacena en el contador de minas usadas
    }
    else
    {   
        contador_minas[1] = contador_minas[1] + 1;//Se almacena en el contador de minas usadas
    }

    
    
    revelar_tablero[marcar_filas][marcar_columnas] = 'M';//Donde se marco la mina se muestra una M     
    
}
















void juego(char **copiar_tablero, char **revelar_tablero, int filas, int columnas, int *contador_minas) //Esta variable almacena la estructura del juego
{

    llenar_revelar_tablero(revelar_tablero, filas, columnas); 

    printf("\n\n********************************************\n* BUSCAMINAS - PROGRAMACIÓN I - BRUNO MAYO *\n********************************************\n\n"); //Titulo
    imprimir_tablero(copiar_tablero, revelar_tablero,filas, columnas); //Se imprime el tablero con guiones para que el usuario lo vea

    
    char input; //Se almacena la accion a realizar
    int i = 0;
        
    while (i < filas * columnas)//El juego se ejecuta como máximo filas*columnas veces
    {
        
        scanf("%c", &input);
     
        
        

        if(input == 'e' || input == 'E') //Si el usuario selecicona 'E' se sale del juego
        {
            exit(1);
        }
        else if(input == 'd' || input == 'D') //Si se presiona 'D' se desbloquea una casilla
        {
            descubrir_celda(copiar_tablero, revelar_tablero, filas, columnas);
            imprimir_tablero(copiar_tablero, revelar_tablero, filas, columnas);
        }
        else if(input == 'm' || input == 'M') //Si se presiona 'M' se marca una mina
        {
       
            marcar_mina(copiar_tablero, revelar_tablero, filas, columnas, contador_minas);
            imprimir_tablero(copiar_tablero, revelar_tablero, filas, columnas);
            
            if(contador_minas[0] == contador_minas[2]) //Si la cantidad de minas marcadas es igual a la cantidad total de minas, se gana la partida
            {
                printf("\n\n******************************\n* FELICITACIONES, HAS GANADO *\n******************************\n\n");
                exit(1);
            }
            else if (contador_minas[1] == contador_minas[0]) //Si el usuario usa todas las minas, se le notifica que perdio
            {
                printf("\nHA PERDIDO, HA UTILIZADO TODAS LAS MINAS Y LO HA HECHO INCORRECTAMENTE\n\n\n");
                exit(1);
            }
 
        }    

        i = i + 1;

    }    
}