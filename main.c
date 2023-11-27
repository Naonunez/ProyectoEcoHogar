#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <string.h>
#include <assert.h>
#include <strings.h>

//Tdas
#include "list.h"
#include "heapMax.h"
#include "heapMin.h"


typedef struct{
    char Nombre[50];
    int ConsumoPromedio;
    char FechaAd[50];
    int HoraDiario;
    char Potencia[50];
    char Fabricante[50];
    char Modelo[50];

}Dispositivos;

typedef struct Categoria {
    char nombre[50];
    char descripcion[100];
    List* listasDeListas;  
} Categoria;

typedef struct{
    int Consumo;
    int Costo;
    int Mes;
    int Year;

}Factura;


void Inicializacion(){
    char Ingreso[50];
    printf("\033[0;32m");
    printf("\n");
    printf("\n");
    printf(" ----------   ----------   ----------   ---    ---   ---------   ---------    ------------   ------------     \n");
    printf("|          | |          | |          | |   |  |   | |         | |         |  |            | |            |    \n");
    printf("|  --------  |   -------  |    ---   | |   |  |   | |   ---   | |  -------   |     --     | |     ----   |    \n");
    printf("|  |         |  |         |   |   |  | |   |  |   | |  |   |  | |  |         |   |    |   | |    |    |  |    \n");
    printf("|  --------  |  |         |   |   |  | |   |  |   | |  |   |  | |  |         |   |    |   | |     ----   |    \n");
    printf("|          | |  |         |   |   |  | |    --    | |  |   |  | |  |         |     --     | |    --     --    \n");
    printf("|  --------  |  |         |   |   |  | |   |  |   | |  |   |  | |  |   ----- |     --     | |   |  |   |      \n");
    printf("|  |         |  |         |   |   |  | |   |  |   | |  |   |  | |  |    | |  |   |    |   | |   |   |   |     \n");
    printf("|  --------  |   -------  |    ---   | |   |  |   | |   ---   | |   ----  |  |   |    |   | |   |    |   |    \n");
    printf("|          | |          | |          | |   |  |   | |         | |         |  |   |    |   | |   |     |   |   \n");
    printf(" ----------   ----------   ----------   ---    ---   ---------   ---------    ---      ---   ---       ---    \n");
    printf("\n");
    printf("                                           1. Continuar\n");
    printf("\033[0m");
    printf("\033[0;31m");
    printf("                                           2. Salir\n");
    printf("\033[0m");
    scanf("%s",Ingreso);

    while(true){
        if (strcmp(Ingreso, "1") == 0) {
            break;
            } 
        else if (strcmp(Ingreso, "2") == 0) {
            printf("Cerrando aplicación\n");
            exit(0);
            }    
        else {
            printf("Por favor, ingrese una opción válida\n");
            scanf("%s", Ingreso);
            }
    }
    
}

void VolverMenu(){
    char menu[50];

    printf("Para volver al menu ingrese cualquier caracter\n");
    scanf("%s", menu);
}

void IngresoDatosDispositivos(List* ListaDispositivos){
    Dispositivos* Nuevo = (Dispositivos*) malloc (sizeof(Dispositivos));

    printf("Ingrese el nombre del dispositivo\n");
    getchar();
    fgets(Nuevo->Nombre, sizeof(Nuevo->Nombre), stdin);
    Nuevo->Nombre[strcspn(Nuevo->Nombre, "\n")] = '\0';

    printf("Ingrese en numeros el consumo promedio del dispositivo \n");
    scanf("%i", &Nuevo->ConsumoPromedio);

    printf("Ingrese la fecha de adquisicion del dispositivo (DD /MM / AAAA) \n");
    getchar();
    fgets(Nuevo->FechaAd, sizeof(Nuevo->FechaAd), stdin);
    Nuevo->FechaAd[strcspn(Nuevo->FechaAd, "\n")] = '\0';

    printf("Ingrese el tiempo de uso diario del dispositivo en numero de horas\n");
    scanf("%i", &Nuevo->HoraDiario);

    printf("Ingrese la potencia nominal del dispositivo \n");
    getchar();
    fgets(Nuevo->Potencia, sizeof(Nuevo->Potencia), stdin);
    Nuevo->Potencia[strcspn(Nuevo->Potencia, "\n")] = '\0';

    printf("Ingrese el nombre del fabricante del dispositivo \n");
    fgets(Nuevo->Fabricante, sizeof(Nuevo->Fabricante), stdin);
    Nuevo->Fabricante[strcspn(Nuevo->Fabricante, "\n")] = '\0';

    printf("Ingrese el numero de modelo del dispositivo \n");
    fgets(Nuevo->Modelo, sizeof(Nuevo->Modelo), stdin);
    Nuevo->Modelo[strcspn(Nuevo->Modelo, "\n")] = '\0';

    pushFront(ListaDispositivos, Nuevo);

    printf("Dispositivo ingresado correctamente\n");

}

Categoria* CrearCategoria() {
    Categoria* nuevaCategoria = (Categoria*) malloc (sizeof(Categoria));
    assert(nuevaCategoria != NULL);

    printf("Ingrese el nombre de la categoria: \n");
    getchar();
    fgets(nuevaCategoria->nombre, sizeof(nuevaCategoria->nombre), stdin);
    nuevaCategoria->nombre[strcspn(nuevaCategoria->nombre, "\n")] = '\0'; 

    printf("Ingrese la descripcion de la categoria: \n");
    fgets(nuevaCategoria->descripcion, sizeof(nuevaCategoria->descripcion), stdin);
    nuevaCategoria->descripcion[strcspn(nuevaCategoria->descripcion, "\n")] = '\0'; 

    nuevaCategoria->listasDeListas = createList();

    VolverMenu();
    return nuevaCategoria;
    
}
    


void AgregarACategoria(List* ListaCategorias, List* ListaDispositivos){
    char nombreDispositivo[50];
    char nombreCategoria[50];

    printf("Ingrese el nombre de la categoria existente: \n");
    getchar();
    fgets(nombreCategoria, sizeof(nombreCategoria), stdin);
    nombreCategoria[strcspn(nombreCategoria, "\n")] = '\0';

    printf("Ingrese el nombre del dispositivo: \n");
    fgets(nombreDispositivo, sizeof(nombreDispositivo), stdin);
    nombreDispositivo[strcspn(nombreDispositivo, "\n")] = '\0';

    Dispositivos* Disp = firstList(ListaDispositivos);

    while(Disp != NULL && strcasecmp(Disp->Nombre, nombreDispositivo) != 0){
        Disp = nextList(ListaDispositivos);
    }

    if(Disp == NULL) {
        printf("Dispositivo no encontrado.\n");
        return;
    }

    Categoria* Cat = firstList(ListaCategorias);

    while (Cat != NULL && strcasecmp(Cat->nombre, nombreCategoria) != 0) {
        Cat = nextList(ListaCategorias);
    }

    if(Cat == NULL) {
        printf("Categoria no encontrada.\n");
        return;
    }

    pushFront(Cat->listasDeListas,Disp);

    printf("Dispositivo %s agregado correctamente a la categoria %s\n", (char*)Disp,(char*)Cat);
    VolverMenu();

}


void VerTodosDispositivos(List *ListaDispositivos){
    
    Dispositivos *Datos = firstList(ListaDispositivos);
    
    if (Datos == NULL){
        printf("No se han registrado dispositivos\n");
        return;
    }

    printf("Dispositivos ingresados:\n");
    while (Datos != NULL){
        printf("Nombre: %s \n", Datos->Nombre);
        printf("Marca: %s \n", Datos->Fabricante);
        printf("Consumo promedio: %i \n\n", Datos->ConsumoPromedio);

        Datos = nextList(ListaDispositivos);

    }
}



int main(){
    char opcion[50];
    char opcion1[50];
    char opcion2[50];

    Inicializacion();

    List* ListaDispositivos = NULL;
    ListaDispositivos = createList();

    List* ListaCategorias = NULL;
    ListaCategorias = createList();

    while(true){
    
    printf("Menu\n");
    printf("1. Registro de datos de consumo de energia\n");
    printf("2. Recomendaciones de ahorro de energia\n");
    printf("3. Visualizacion de facturas y huella de carbono\n");
    printf("4. Funciones avanzadas\n");
    printf("5. Mis dispositivos\n");
    printf("6. Acerca de EcoHogar\n");
    printf("7. Salir\n");

    scanf("%s", opcion);

    if (strcmp(opcion, "1") == 0){
        

        while(true){
            printf("1.Ingresar datos de dispositivos\n");
            printf("2.Ingresar datos de categorias\n");
            printf("3.Ingresar datos de facturas\n");

            scanf("%s", opcion1);

            if (strcmp(opcion1, "1") == 0){
                IngresoDatosDispositivos(ListaDispositivos);
                VolverMenu();
                break;
                
            }
            else if (strcmp(opcion1, "2") == 0){
                while(true){
                    printf("1. Crear nuevo categoria\n");
                    printf("2. Agregar dispositivo a categoria ya existente\n");
                    scanf("%s", opcion2);

                    if (strcmp(opcion2, "1") == 0){
                        pushFront(ListaCategorias,CrearCategoria());
                        

                    }
                    else if (strcmp(opcion2, "2") == 0){
                        AgregarACategoria(ListaCategorias,ListaDispositivos);
                        
                        break;

                    }


               }
               VolverMenu();
               break;

            }
            else if(strcmp(opcion1, "3") == 0){
                //Ingreso Facturas
                VolverMenu();
                break;
            }
            else{
                printf("Por favor, ingrese una opcion valida\n");
                scanf("%s", opcion1);
            }
        }
    }
    
    else if (strcmp(opcion, "2") == 0){
        while(true){
            printf("1.Analisis de consumo\n");
            printf("2.Ver recomendaciones\n");

            scanf("%s", opcion1);

            if (strcmp(opcion1, "1") == 0){
                //AnalisisConsumo
                VolverMenu();
                break;
            }
            else if (strcmp(opcion1, "2") == 0){
                // VerRecomendaciones
                VolverMenu();
                break;

            }
            else{
                printf("Por favor, ingrese una opcion valida\n");
                scanf("%s", opcion1);
            }
        }
    }

    else if (strcmp(opcion, "3") == 0){
        while(true){
            printf("1.Ver facturas\n");
            printf("2.Calcular huella de carbono\n");

            scanf("%s", opcion1);

            if(strcmp(opcion1, "1") == 0){
                //Facturas
                VolverMenu();
                break;
            }
            else if(strcmp(opcion1, "2") == 0){
                //HuellaCarbono
                VolverMenu();
                break;

            }
            else{
                printf("Por favor, ingrese una opcion valida\n");
                scanf("%s", opcion1); 
            }
        }

    }

    else if (strcmp(opcion, "4") == 0){
        while(true){
            printf("1.Mostrar dispositivos por consumo bajo\n");
            printf("2.Mostrar mayores consumidores de energía\n");

            scanf("%s", opcion1);

            if(strcmp(opcion1, "1") == 0){
                //MenorConsumo
                VolverMenu();
                break;
            }
            else if(strcmp(opcion1, "2") == 0){
                //MayorConsumo
                VolverMenu();
                break;

            }
            else{
                printf("Por favor, ingrese una opcion valida\n");
                scanf("%s", opcion1); 
            }
        }

    }
    else if (strcmp(opcion, "5") == 0){
        while(true){
            printf("1. Ver todos mis dispositivos\n");
            printf("2. Ver dispositivos por categoria\n");
            printf("3. Buscar dispositivo\n");
            scanf("%s", opcion1);

            if(strcmp(opcion1, "1") == 0){
                VerTodosDispositivos(ListaDispositivos);
                VolverMenu();
                break;
            }
            else if(strcmp(opcion1, "2") == 0){
                //VerporCategoria
                VolverMenu();
                break;

            }
            else if(strcmp(opcion1, "3") == 0){
                //BuscarDispositivos
                VolverMenu();
                break;

            }
            else{
                printf("Por favor, ingrese una opcion valida\n");
                scanf("%s", opcion1); 
            }
        }

    }

    else if (strcmp(opcion, "6") == 0){
        while(true){
            printf("1. ¿Como usar nuestra aplicacion?\n");
            printf("2. Nuestro proposito\n");
            printf("3. Acerca de nuestros creadores\n");
            scanf("%s", opcion1);

            if(strcmp(opcion1, "1") == 0){
                //ComoUsar
                VolverMenu();
                break;
            }
            else if(strcmp(opcion1, "2") == 0){
                //proposito
                VolverMenu();
                break;

            }
            else if(strcmp(opcion1, "3") == 0){
                //AcercaNosotros
                VolverMenu();
                break;

            }
            else{
                printf("Por favor, ingrese una opcion valida\n");
                scanf("%s", opcion1); 
            }
        }

    }

    else if (strcmp(opcion, "7") == 0){
        while(true){
            printf("Usted esta saliendo de EcoHogar\n");
            printf("1. Confirmar\n");
            printf("2. Cancelar\n");

            scanf("%s", opcion1);

            if(strcmp(opcion1, "1") == 0){
                exit(0);
            }
            else if(strcmp(opcion1, "2") == 0){
                //cancelar
                VolverMenu();
                break;

            }
            else{
                printf("Por favor, ingrese una opcion valida\n");
                scanf("%s", opcion1); 
            }
        }

    }
    else{
        printf("Por favor, ingrese una opcion valida\n");
        scanf("%s", opcion); 
    }
  }

}