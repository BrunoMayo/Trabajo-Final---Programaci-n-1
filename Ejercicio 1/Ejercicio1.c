/*************************
 * Ingenieria en Computación - UNRN Andina
 * Programación 1
 * minombredeusuario de GitHub: BrunoMayo
*************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int diferentes_simbolos(int j, char texto[100][10]); //chequea que no haya simbolos distintos en un mismo string
int sumar(char texto[100][10], int j, int punto_anterior); //realiza las sumas
int restar(char texto[100][10], int iterador, int singo_previo); //realiza las restas
int hay_alfa(char texto[100][10], int i); //chequea que no exista un caracter alfabetico distinto de a
float promedio(char texto[100][10], int iterador); //calcula el promedio
int multuplicar(char texto[100][10], int iterador, int signo_previo); //realiza las multiplicaciónes

int main()
{
    FILE *ptr_archivo = fopen("prueba.txt", "r");
    
    char texto[100][10]; //aca se van a copiar los strings del archivo .txt
    int i = 0; //Va a contar cuantos string hay en texto

    if (ptr_archivo == NULL) //chequea que el archivo exista
    {
        printf("Error: no se pudo leer el archivo");
    }
    else
    {
        while (!feof(ptr_archivo)) //copia los strings a texto
        {
            fscanf(ptr_archivo, "%s", &texto[i][0]);
            i = i + 1;
        }

        fclose(ptr_archivo); //cierra el archivo
    }

    int iterador = 0; //sirve para iterar entre los strings
    int signo_previo = -1; //Sirve para representar la posición del singo anterior
    int resultado = 0;

    if (hay_alfa(texto, i) == 1) //chequeo que no haya caracteres alfanumericos
    {
        exit(1);
    } 

    
    while (iterador < i)
    {
        if (texto[iterador][0] == '+') //calcula las sumas
        {
            if (diferentes_simbolos(iterador, texto) == 1)
            {
                exit(1);
            } 
            else
            {
                resultado = resultado + sumar(texto, iterador, signo_previo);
                signo_previo = iterador;
            }
        }
        else if (texto[iterador][0] == '-' && !isdigit(texto[iterador][1]) ) //calcula las restas
        {
            if (diferentes_simbolos(iterador, texto) == 1)
            {
                exit(1);
            } 
            else
            {
                resultado = resultado + restar(texto, iterador, signo_previo);
                signo_previo = iterador;
            }
        }
        else if (texto[iterador][0] == 'a') //calcula el promedio;
        {
            if (diferentes_simbolos(iterador, texto) == 1)
            {
                exit(1);
            } 
            else
            {
                promedio(texto, iterador);
                //iterador = iterador + 1;
                resultado = 0;
                signo_previo = iterador;
            }
        }
        else if (texto[iterador][0] == '*') //calcula las multiplicaciones
        {
            if (diferentes_simbolos(iterador, texto) == 1)
            {
                exit(1);
            } 
            else if(signo_previo == -1 && resultado == 0)
            {
                resultado = 1;
                resultado = resultado * multuplicar(texto, iterador, signo_previo);
                signo_previo = iterador;
            }
            else
            {
                resultado = resultado * multuplicar(texto, iterador, signo_previo);
                signo_previo = iterador;
            }
        }
        else if (texto[iterador][0] == '=') //Imprime el resultado desde las operaciones desde un igual al siguiente 
        {
            if (diferentes_simbolos(iterador, texto) == 1)
            {
                exit(1);
            }
            else
            {
                printf("= %d\n", resultado);
                signo_previo = iterador;
                resultado = 0;
                
            }
        }
        
        iterador = iterador + 1;

    }
    

    
    return 0;

}





int diferentes_simbolos(int iterador, char texto[100][10]) //analiza que no haya simbolos matematicos distintos en un mismo string
{
    int no_coincide = 0;
    
    for (int m = 1; m < strlen(texto[iterador]); m++)
    {
        if (!isdigit(texto[iterador][m]) && texto[iterador][0] == '-')
        {
            printf("\nError: se han utilizado diferentes simbolos matematicos en la línea %d del archivo\n", iterador + 1);
            no_coincide = 1;   
            break;       
        }
      
    } 
      
    if (no_coincide == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}




int hay_alfa(char texto[100][10], int i) //analiza que no haya ningun caracter alfabetico que no sea 'a'
{
    int alfa = 0;
    for (int j = 0; j < i; j++)
    {
        for (int k = 0; k < strlen(texto[j]); k++)
        {   
            if (isalpha(texto[j][k]) && texto[j][0] != 'a')
            {
                alfa = 1;
            }
        }
        
    }
    
    if (alfa == 1)
    {
        printf("Error: el archivo contiene caracteres alfabeticos\n");
        return 1;
    }
    else
    {
        return 0;
    }
}






int sumar(char texto[100][10], int iterador, int signo_previo) //calcula las sumas
{
 
    int suma = 0;
    for (int i = (iterador - 1); i > signo_previo; i--)
    {
        if (isdigit(texto[i][0]))
        {
            printf("+ %s ", texto[i]);
            suma = suma + atoi(&texto[i][0]);
        }
        else if(texto[i][0] == '-' && isdigit(texto[i][1]))
        {
            printf("+ %s ", texto[i]);
            suma = suma - atoi(&texto[i][1]);
        }
        else
        {
            printf("\nError: se ha encontrado un caracter invalido\n");
            exit(1);
        }
        
        
    }

   

    return suma;

}





int restar(char texto[100][10], int iterador, int signo_previo) //calcula las restas
{
   
    int resta = 0;
    
    
    for (int i = (iterador - 1); i > signo_previo; i--)
    { 
        if (isdigit(texto[i][0]))
        {    
            printf("- %s ", texto[i]);
            resta = resta - atoi(&texto[i][0]);
        }  
        else if(texto[i][0] == '-' && isdigit(texto[i][1]))
        {
            printf("+ %s ", texto[i]);
            resta = resta - atoi(&texto[i][1]);
        }
        else
        {
            printf("\nError: se ha encontrado un caracter invalido\n");
            exit(1);
        }
    }
   
    return resta;

}


float promedio(char texto[100][10], int iterador) //calcula el promedio
{
    int j = iterador - 1;
    float contador = 0;
    float suma = 0;
    float resultado;
    printf("El promedio de ");
    while (texto[j][0] != '='  && j >= 0)
    {

        if (isdigit(texto[j][0] ))
        {   
            printf("%s, ", texto[j]);
            suma = suma + atof(&texto[j][0]);
            contador = contador + 1;
        }
        else if (texto[j][0] == '-' && isdigit(texto[j][1]))
        {   
            printf("%s, ", texto[j]);
            suma = suma - atof(&texto[j][1]);
            contador = contador + 1;
        }
        else if(texto[j][0] == '+' || (texto[j][0] == '-' && isdigit(texto[j][1])) || texto[j][0] == '*')
        {
            printf("\nError: el promedio no pude tener otras operaciones en el medio\n");
            exit(1);
        }
        j = j - 1;
    }

    resultado = suma / contador;
    printf(" es: %.2f\n", resultado);

    return 0;

}

int multuplicar(char texto[100][10], int iterador, int signo_previo) //calcula la multiplicacion
{
    int multiplicacion = 1;
    
    for (int i = (iterador - 1); i > signo_previo; i--)
    { 
        if (isdigit(texto[i][0]))
        {    
            printf("* %s ", texto[i]);
            multiplicacion = multiplicacion * atoi(&texto[i][0]);
        }
        else if(texto[i][0] == '-' && isdigit(texto[i][1]))
        {
            printf("* %s ", texto[i]);
            multiplicacion = multiplicacion * (atoi(&texto[i][1]) * -1) ;
        }  
        else
        {
            printf("\nError: se ha encontrado un caracter invalido\n");
            exit(1);
        }
    }
   
    return multiplicacion;
}

