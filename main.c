#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <string.h>
#include <assert.h>
#include <strings.h>
#include <ctype.h>

//Tdas
#include "list.h"
#include "heapMax.h"
#include "heapMin.h"


//En este struct almacenamos los datos de cada dispositivo a ingresar
typedef struct{
    char Nombre[50];
    int ConsumoPromedio;
    char FechaAd[50];
    int HoraDiario;
    char Potencia[50];
    char Fabricante[50];
    char Modelo[50];

}Dispositivos;

//En este struct guardamos una lista de listas que guarda categorias que crea el usuario con una brve descripcion
typedef struct Categoria {
    char nombre[50];
    char descripcion[100];
    List* listasDeListas;  
} Categoria;

//En este struct guardamos los datos de las facturas para analizar el consumo
typedef struct{
    double Consumo;
    int CostoTotal;
    int CargoFijo;
    int Mes;
    int Year;
    char NombreFac[50];

}Facturas;



//Esta funcion crea un inicio con el nombre de nuestra aplicacion en color verde
//Solo funciona si se corre en una terminal, en el ejecutable solo mostrara numeros
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
    printf("\033[0;31m");
    printf("                                           2. Salir\n");
    printf("\033[0m");
    scanf("%s",Ingreso);
    // en este ciclo comenzamos la aplicacion o directamente si cierra si gusta y se pide el ingreso de una opcion valida
    while(true){
        if (strcmp(Ingreso, "1") == 0) {
            break;
            } 
        else if (strcmp(Ingreso, "2") == 0) {
            printf("Cerrando aplicacion\n");
            exit(0);
            }    
        else {
            printf("Por favor, ingrese una opcion valida\n");
          
            }
    }

}
//Esta funcion es para no volver tan abruptamente al menu principal
//Asi se pueden leer los datos proporcionados por cada opcion antes de volver
void VolverMenu(){
    char menu[50];

    printf("Para volver al menu ingrese cualquier caracter\n");
    scanf("%s", menu);
}


//Esta funcion permite ingresar informacion detallada sobre un dispostivo(Se almacenara en la estructura de datos Dispositivo)
void IngresoDatosDispositivos(List* ListaDispositivos){
    //Asignamos memoria dinamicamente para ingresar los datos de los dispositivos
    Dispositivos* Nuevo = (Dispositivos*) malloc (sizeof(Dispositivos));

    printf("========== Ingreso de dispositivos ==========\n");
    printf("Ingrese el nombre del dispositivo\n");
    getchar();
    fgets(Nuevo->Nombre, sizeof(Nuevo->Nombre), stdin);
    Nuevo->Nombre[strcspn(Nuevo->Nombre, "\n")] = '\0';

    //Usamos este ciclo para asegurarnos que se entren datos numericos ya que esta variable es muy importante mas adelante
    int validInput = 0;
    char buffer[10];
    do {
        printf("Ingrese en kWh el consumo promedio del dispositivo \n");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        validInput = 1;
        for (int i = 0; i < strlen(buffer); i++) {
            if (!isdigit(buffer[i])) {
                validInput = 0;
                break;
            }
        }

        if (!validInput) {
            printf("Error: Ingrese un número válido.\n");
        } 
        else {
            Nuevo->ConsumoPromedio = atoi(buffer);
        }
    } while (!validInput);

    printf("Ingrese la fecha de adquisicion del dispositivo (DD / MM / AAAA) \n");
    getchar();
    fgets(Nuevo->FechaAd, sizeof(Nuevo->FechaAd), stdin);
    Nuevo->FechaAd[strcspn(Nuevo->FechaAd, "\n")] = '\0';

    printf("Ingrese el tiempo de uso diario del dispositivo en numero de horas\n");
    scanf("%i", &Nuevo->HoraDiario);
    while(true){
      if (Nuevo->HoraDiario > 24){
        printf("Por favor ingrese un numero valido\n");
        scanf("%i", &Nuevo->HoraDiario);
      }
      else{
        break;
      }
    }  

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

    printf("========================================\n");

}

//Esta funcion permite ingresar el nombre hacia una nueva Categoria a crear para luego poder organizar los diferentes dispositivos ingresado en la funcion anterior
Categoria* CrearCategoria() {

    printf("========== Crear Categorias ==========\n");
    //Asignamos memoria para crear cada categoria
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

    return nuevaCategoria;
    printf("========================================\n");

}


//Esta funcion permite añadir cualquier dispositivo ingresado a una categoria ya existente
void AgregarACategoria(List* ListaCategorias, List* ListaDispositivos){
    char nombreDispositivo[50];
    char nombreCategoria[50];
  
    printf("========== Añadir a Categoria ==========\n");
    printf("Ingrese el nombre de la categoria existente: \n");
    getchar();
    fgets(nombreCategoria, sizeof(nombreCategoria), stdin);
    nombreCategoria[strcspn(nombreCategoria, "\n")] = '\0';

    printf("Ingrese el nombre del dispositivo: \n");
    fgets(nombreDispositivo, sizeof(nombreDispositivo), stdin);
    nombreDispositivo[strcspn(nombreDispositivo, "\n")] = '\0';
    
    //Recorremos la lista de dispositivos para buscar el que fue ingresado haciendo comparaciones
    Dispositivos* Disp = firstList(ListaDispositivos);    

    //Usamos el strcasecmp para que no diferencie entre mayusculas y minusculas
    while(Disp != NULL && strcasecmp(Disp->Nombre, nombreDispositivo) != 0){
        Disp = nextList(ListaDispositivos);
    }
    //Con estos if hacemos control ya que si firstlist retorna nulo el programa se cierra
    if(Disp == NULL) {
        printf("Dispositivo no encontrado.\n");
        return;
    }
    //Y ahora recorremos la lista de categorias para encontrar una que coincida y añadir el dispositivo 
    Categoria* Cat = firstList(ListaCategorias);
  
    while (Cat != NULL && strcasecmp(Cat->nombre, nombreCategoria) != 0) {
        Cat = nextList(ListaCategorias);
    }

    if(Cat == NULL) {
        printf("Categoria no encontrada.\n");
        return;
    }
    //Y agregamos el dispoditivo a la categoria que se queria
    pushFront(Cat->listasDeListas,Disp);

    printf("Dispositivo %s agregado correctamente a la categoria %s\n", (char*)Disp,(char*)Cat);

    printf("========================================\n");

}
//Esta funcion obtiene los datos de la factura de electricidad para en un futuro poder calcular el consumo mediante los meses que se ingresen
void IngresarFacturas(List* ListaFacturas){
    //Asignamos memoria para guardar los datos de las facturas
    Facturas* Nueva = (Facturas*) malloc (sizeof(Facturas));
  
    printf("========== Ingreso de Factura ==========\n");
    printf("Ingrese el nombre con el cual guardar la factura\n");
    getchar();
    fgets(Nueva->NombreFac, sizeof(Nueva->NombreFac), stdin);
    Nueva->NombreFac[strcspn(Nueva->NombreFac, "\n")] = '\0';

    printf("Ingrese el consumo en la factura\n");
    scanf("%lf", &Nueva->Consumo);

    printf("Ingrese el costo total en la factura\n");
    scanf("%i", &Nueva->CostoTotal);

    printf("Ingrese el cargo fijo de la factura\n");
    scanf("%i", &Nueva->CargoFijo);

    printf("Ingrese el mes de la factura\n");
  
    //Nos aseguramos que se entre un mes valido
    scanf("%i", &Nueva->Mes);
    while(true){
      if (Nueva->Mes < 1 || Nueva->Mes >12){
        printf("Por favor ingrese un valor valido\n");
        scanf("%i", &Nueva->Mes);
      }
      else{
        break;
        }
    }
  

    printf("Ingrese el año en la factura\n");
    scanf("%i", &Nueva->Year);

    printf("Factura ingresada correctamente\n");
    //Y se añade al comienzo de la lista para que su busqueda sea mas rapida para las funciones de mas adelante
    pushFront(ListaFacturas,Nueva);

    printf("========================================\n");

}

//Esta funcion analiza los datos de consumo para poder identificar los diferentes dispositivos que consumen mas energia y compararlos
void AnalizarConsumo(List* ListaDispositivos, List* ListaFacturas, MaxHeap* HeapMax, MinHeap* HeapMin){
    double consumoTotal = 0.0;
    //Para evitar la repeticion de datos cuando se corre 2 o mas veces la funcion borramos si es que hay datos al inicio de la funcion
    if(HeapMax != NULL){
      liberarMaxHeap(HeapMax);
      liberarMinHeap(HeapMin);
    }
    //Buscamos la ultima factura ingresada, la cual se guardo en el comienzo de la lista
    Facturas* factura = firstList(ListaFacturas);

     printf("========== Analisis de Consumo ==========\n");
    //Hacemos un control para que el programa no se cierre cuando no hay facturas ingresadas
    if(factura == NULL){
        printf("Para hacer el analisis de consumo debes ingresar al menos una factura electrica\n");
        return;
    }
    
    consumoTotal = factura->Consumo;

    printf("El consumo total de la ultima factura ingresada es: %.2lf kWh\n", consumoTotal);
    //Incializamos los dispositivos para que segun su consumo entren a la posicion que les corresponden en los monticulos
    Dispositivos* dispositivo = firstList(ListaDispositivos);

    while (dispositivo != NULL) {
        double porcentajeContribucion = (dispositivo->ConsumoPromedio / consumoTotal) * 100.0;

        insertarMax(HeapMax, porcentajeContribucion, (char*) dispositivo);
        insertarMin(HeapMin, porcentajeContribucion, (char*) dispositivo);

        dispositivo = nextList(ListaDispositivos);

    }

    printf("========================================\n");
}

//Esta funcion permite mostrar todos los dispositivos ingresados
void VerTodosDispositivos(List *ListaDispositivos){
    //Recorremos cada dispositivo ingresado en la lista
    Dispositivos *Datos = firstList(ListaDispositivos);

     printf("========== Ver Todos los Dispositivos ==========\n");
    //si no hay registrados volvemos, ya que si no hay el programa se cierra
    if (Datos == NULL){
        printf("No se han registrado dispositivos\n");
        return;
    }
    //Y mostramos los datos mas relevantes de cada dispositivo
    printf("Dispositivos ingresados:\n");
    while (Datos != NULL){
        printf("Nombre: %s \n", Datos->Nombre);
        printf("Marca: %s \n", Datos->Fabricante);
        printf("Consumo promedio: %i \n\n", Datos->ConsumoPromedio);

        Datos = nextList(ListaDispositivos);

    }
    printf("========================================\n");
}



//Esta funcion permite mostrar los dispositivos que coincidan con la categoria de busqueda ingresada
void VerDispositivosCategoria(List *ListaCategorias) {
    char nombreCategoria[50];

    printf("========== Ver Dispositivos por Categoria ==========\n");
    //preguntamos por el nombre de la categoria
    printf("Ingrese el nombre de la categorIa para ver los dispositivos:\n");
    getchar();
    fgets(nombreCategoria, sizeof(nombreCategoria), stdin);
    nombreCategoria[strcspn(nombreCategoria, "\n")] = '\0';

    //Recorremos la lista de listas
    Categoria *categoria = firstList(ListaCategorias);
    while (categoria != NULL) {
        //Comparamos lo ingresado con lo que se busca
        if (strcasecmp(categoria->nombre, nombreCategoria) == 0) {
            List *listaDispositivos = categoria->listasDeListas;
            Dispositivos *dispositivo = firstList(listaDispositivos);

            if (dispositivo == NULL) {
                printf("No hay dispositivos en esta categoría.\n");
                return;
            }
            //Y si encuentra mostramos los datos principales
            printf("Dispositivos en la categoría %s:\n", nombreCategoria);
            while (dispositivo != NULL) {
                printf("Nombre: %s\n", dispositivo->Nombre);
                printf("Marca: %s\n", dispositivo->Fabricante);
                printf("Consumo promedio: %i\n", dispositivo->ConsumoPromedio);

                dispositivo = nextList(listaDispositivos);
            }
            printf("========================================\n");
            return;
        }
        categoria = nextList(ListaCategorias);
    }

    printf("Categoría no encontrada.\n");
    printf("========================================\n");
}

//Esta funcion permite ingresar el nombre de cualquier dispositivo y hacer una busqueda en la lista
void BuscarDispositivos(List *ListaDispositivos) {
    char nombreBusqueda[50];

     printf("========== Buscar Dispositivo ==========\n");
    //Ingresamos el nombre a buscar
    printf("Ingrese el nombre del dispositivo a buscar:\n");
    getchar();
    fgets(nombreBusqueda, sizeof(nombreBusqueda), stdin);
    nombreBusqueda[strcspn(nombreBusqueda, "\n")] = '\0';

    Dispositivos *dispositivo = firstList(ListaDispositivos);
    //Y recorremos la lista de dispositivos
    while (dispositivo != NULL) {
        if (strcasecmp(dispositivo->Nombre, nombreBusqueda) == 0) {
            //Y si se encuentra en la lista lo muestra
            printf("Dispositivo encontrado:\n");
            printf("Nombre: %s\n", dispositivo->Nombre);
            printf("Marca: %s\n", dispositivo->Fabricante);
            printf("Consumo promedio: %i\n", dispositivo->ConsumoPromedio);
            printf("========================================\n");
            return;
        }
        dispositivo = nextList(ListaDispositivos);
    }

    printf("Dispositivo no encontrado.\n");
    printf("========================================\n");
}


//Esta funcion permite ver las facturas de energia ingresadas a partir de los datos de consumo 
void verFacturas(List *ListaFacturas) {
    //Inicializamos en el primer dato de las facturas
    Facturas *factura = firstList(ListaFacturas);
     printf("========== Ver Facturas ==========\n");

    if (factura == NULL) {
        printf("No hay facturas registradas.\n");
        return;
    }

    printf("Facturas registradas:\n");
    //Y si hay registradas se muestran todas
    while (factura != NULL) {
        printf("Nombre de la factura: %s\n", factura->NombreFac);
        printf("Consumo: %.2lf kWh\n", factura->Consumo);
        printf("Costo total: %i\n", factura->CostoTotal);
        printf("Cargo fijo: %i\n", factura->CargoFijo);
        printf("Mes: %i\n", factura->Mes);
        printf("Año: %i\n", factura->Year);
        printf("\n");

        factura = nextList(ListaFacturas);
    }
    printf("========================================\n");
}

//Funcion para obtener el primer dispositivo de la lista con un consumo promedio superior a 50
Dispositivos* ObtenerDispositivoAltoConsumo(List* ListaDispositivos) {
  
  Dispositivos* dispositivo = firstList(ListaDispositivos);
  while (dispositivo != NULL) {
      if (dispositivo->ConsumoPromedio > 50) {
        //devuelve el primer dispositivo con el alto consumo
        return dispositivo;
      }
      dispositivo = nextList(ListaDispositivos);
    }
  //retorna NULL si no se encuentra ningun dispositivo con alto consumo
  return NULL;
}

//Funcion para obtener el año desde una cadena de fecha en formato  (DD/MM/AAAA)
int ObtenerAnioDesdeFecha(const char* fecha) {
  int anio;
  if (sscanf(fecha, "%*d / %*d / %d", &anio) == 1) {
      //Devuelve el año obtenido de la cadena de fecha
      return anio;
 }

  return -1;
}

//con esta funcion obtenemos los dispositivos que tienen varios años de uso en el hogar
Dispositivos* ObtenerDispositivoAntiguo(List* ListaDispositivos) {
    Dispositivos* dispositivo = firstList(ListaDispositivos);
    while (dispositivo != NULL) {
        int anioAdquisicion = ObtenerAnioDesdeFecha(dispositivo->FechaAd);
        if (anioAdquisicion < 2015) {
            return dispositivo;
        }
        dispositivo = nextList(ListaDispositivos);
    }
    //Retorna NULL si no se encuentra ningun dispistivo antiguo
    return NULL;
}

//Esta funcion obtiene la primera factura de la lista con un consumo superior a 200 kWh
Facturas* ObtenerFacturaAltoConsumo(List* ListaFacturas) {
    Facturas* factura = firstList(ListaFacturas);
    while (factura != NULL) {
        if (factura->Consumo > 200) {
            //Devuelve la primera factura con alto consumo
            return factura;
        }
    }
    //Returna NULL si no se encuentra ninguna factura con alto consumo
    return NULL;
}

//Esta funcion muestra recomendaciones especificas para el ahorro de energia en el hogar(como ajustar el uso de un dispositvo o reemplazar un dispositivo)
void VerRecomendaciones(List* ListaDispositivos, List* ListaFacturas){
  //Obenemos los dispositivos que cumplen con los criterios de estas funciones
  Dispositivos* dispositivoAltoConsumo = ObtenerDispositivoAltoConsumo(ListaDispositivos);
  Dispositivos* dispositivoAntiguo = ObtenerDispositivoAntiguo(ListaDispositivos);
  Facturas* facturaAltoConsumo = ObtenerFacturaAltoConsumo(ListaFacturas);

   printf("========== Recomendaciones ==========\n");
  //Si la funcion antes mencionada encuentra un dispositivo con alto consumo se muestra la recomendacion
  if (dispositivoAltoConsumo != NULL) {
      printf("Recomendaciones:\n");
      printf("El dispositivo %s tiene un alto consumo promedio. Considera reemplazarlo por uno mas eficiente.\n", dispositivoAltoConsumo->Nombre);
  }
  //Lo mismo con la antiguedad 
  if (dispositivoAntiguo != NULL) {
    printf("El dispositivo %s es antiguo. Puedes ahorrar energia reemplazandolo con un modelo mas reciente y eficiente.\n", dispositivoAntiguo->Nombre);
  }
  //Y si la ultima factura es de alto consumo lo muestra
  if (facturaAltoConsumo != NULL) {
      printf("Tu última factura (%s) tiene un consumo alto. Analiza los detalles y considera ajustar el uso de los dispositivos.\n", facturaAltoConsumo->NombreFac);
  }
  printf("========================================\n");
  
}


//Esta funcion utiliza los datos de consumo para poder calcular la huella de carbono asociada y muestra el resultado al usuario
void CalcularHuellaDeCarbono(List* ListaFacturas) {
    //El factor de emision electrica es una constante
    double factorEmision = 0.5;
    double consumoEnergia;
    Facturas* factura = firstList(ListaFacturas);

    consumoEnergia = factura->Consumo;
    //con esta formula calculamos la huella de carbono segun el consumo electrico mensual de la persona y el factor de emision electrica del pais
    double huellaCarbono = consumoEnergia * factorEmision;

    printf("\n========== Huella de Carbono ==========\n");
    printf("Tu consumo de energia ha generado una huella de carbono de %.2lf kg CO2e.\n", huellaCarbono);
    //Si el calculo es menor o igual a 100 es bueno
    if (huellaCarbono <= 100){
       printf(" ¡Felicidades! Tu consumo electrico de este mes es bajo, contribuyendo positivamente al medio ambiente\n");
    }
    //Si esta sobre 100 y menor 250 es regular 
    else if (huellaCarbono > 100 && huellaCarbono <= 250){
       printf("Estas en el rango de consumo moderado. Hay espacio para mejorar y reducir tu huella de carbono. Considera adoptar medidas de eficiencia energetica, como usar electrodomesticos con certificacion energética y apagar luces cuando no las necesitas\n");
    }
    //Y si no entra en las anteriores es malo
    else{
      printf("Tu consumo electrico de este mes es alto, lo que contribuye significativamente a las emisiones de carbono. Te recomendamos visitar nuestra seccion de recomendaciones para disminuir tu huella de carbono\n");
    }
  
    printf("Recuerda que cada pequeña accion para reducir tu consumo puede marcar la diferencia.\n");
    printf("========================================\n\n");
}

//Esta funcion proporciona detalles sobre como usar la aplicacion
void ComoUsar() {
    printf("\n========== Como usar EcoHogar ==========\n");
    printf("1. Ingresa los datos de tus dispositivos para realizar un seguimiento del consumo.\n");
    printf("2. Puedes agrupar tus dispositivos en categorias para un mejor análisis.\n");
    printf("3. Registra tus facturas electricas para un calculo preciso de costos y consumo.\n");
    printf("4. Utiliza las funciones avanzadas para obtener recomendaciones de ahorro.\n");
    printf("5. Visualiza y analiza tu consumo a lo largo del tiempo.\n");
    printf("6. Explora las funciones adicionales y la información sobre la huella de carbono.\n");
    printf("7. ¡Disfruta de un hogar mas eficiente y ecologico con EcoHogar!\n");
    printf("========================================\n\n");
}

//Esta funcion muestra la idea de la aplicacion y la importancia para nosotros 
void NuestroProposito() {
    printf("\n========== Nuestro Proposito ==========\n");
    printf("En EcoHogar, nuestro propósito es generar conciencia sobre el consumo de energía\n");
    printf("y fomentar prácticas que ayuden a reducir nuestro impacto ambiental. Creemos que\n");
    printf("cada pequeña acción cuenta y que al tomar decisiones informadas sobre el uso de\n");
    printf("la energía en nuestros hogares, podemos contribuir significativamente a la\n");
    printf("sostenibilidad del medio ambiente.\n\n");
    printf("Algunos de nuestros objetivos incluyen:\n");
    printf("- Proporcionar información detallada sobre el consumo de energía de los dispositivos.\n");
    printf("- Ofrecer recomendaciones personalizadas para reducir el consumo energético.\n");
    printf("- Incentivar el uso eficiente de la energía y el uso de tecnologías más sostenibles.\n");
    printf("- Contribuir a la construcción de hogares más ecológicos y responsables.\n");
    printf("========================================\n\n");
}

//Esta funcion muestra informacion sobre los creadores de la aplicacion
void AcercaDeNosotros() {
    printf("\n========== Acerca de Nosotros ==========\n");
    printf("EcoHogar fue creado por un equipo apasionado por la sostenibilidad y el\n");
    printf("cuidado del medio ambiente. Nuestra mision es proporcionar a los usuarios una\n");
    printf("herramienta facil de usar para monitorizar y reducir su consumo de energia en\n");
    printf("el hogar, contribuyendo asi a un estilo de vida mas ecologico.\n\n");
    printf("Equipo de Desarrollo:\n");
    printf("- Naomi Nuñez\n");
    printf("- Bastian Trejo\n");
    printf("- Guillermo Castillo\n");
    printf("========================================\n\n");
}







int main(){
    char opcion[50];
    char opcion1[50];
    char opcion2[50];

    //Corremos la funcion de inicio que nos da el nombre de la aplicacion
    Inicializacion();
  
    //Inicializamos todos los Tdas que vamos a ocupar
    List* ListaDispositivos = NULL;
    ListaDispositivos = createList();

    List* ListaCategorias = NULL;
    ListaCategorias = createList();

    List* ListaFacturas = NULL;
    ListaFacturas = createList();
    //Monticulo Maximo
    MaxHeap* HeapMax = createMaxHeap(1000);
    //Monticulo Minimo
    MinHeap* HeapMin = createMinHeap(1000);

    //Iniciamos este ciclo para que se nos ingresen opciones validas
    while(true){
    //Mostramos el menu de la aplicacion
    printf("Menu\n");
    printf("1. Registro de datos de consumo de energia\n");
    printf("2. Recomendaciones de ahorro de energia\n");
    printf("3. Visualizacion de facturas y huella de carbono\n");
    printf("4. Funciones avanzadas\n");
    printf("5. Mis dispositivos\n");
    printf("6. Acerca de EcoHogar\n");
    printf("7. Salir\n");

    //Ingresamos la opcion deseada
    scanf("%s", opcion);

    if (strcmp(opcion, "1") == 0){
        //Si se ingresa el 1 comenzamos el ingreso de datos
        while(true){
            printf("========== Ingreso de Datos ==========\n");
            printf("1.Ingresar datos de dispositivos\n");
            printf("2.Ingresar datos de categorias\n");
            printf("3.Ingresar datos de facturas\n");
            printf("4.Atras\n");

            //Preguntamos la opcion
            scanf("%s", opcion1);
          
            //Si se ingresa el 1 ingresamos dispositivos a la lista
            if (strcmp(opcion1, "1") == 0){
                IngresoDatosDispositivos(ListaDispositivos);
                VolverMenu();
                break;
            }
            //Si se ingresa el 2 Preguntamos si e quiere crear categorias o añadir dispositivos
            else if (strcmp(opcion1, "2") == 0){
                while(true){
                     printf("========== Crear o Añadir a Categoria ==========\n");
                    printf("1. Crear nuevo categoria\n");
                    printf("2. Agregar dispositivo a categoria ya existente\n");
                    printf("3.Atras\n");
                    //Preguntamos la opcion dentro de categorias
                    scanf("%s", opcion2);

                    //Si es 1 vamos a la funcion de crear categorias
                    if (strcmp(opcion2, "1") == 0){
                        pushFront(ListaCategorias, CrearCategoria());
                        VolverMenu();
                    }
                    //Si es 2 añadimos a las categorias
                    else if (strcmp(opcion2, "2") == 0){
                        AgregarACategoria(ListaCategorias,ListaDispositivos);
                        VolverMenu();
                        break;
                    }
                    //Si es 3 volvemos al menu de ingreso de datos
                    else if (strcmp(opcion2, "3") == 0){
                        break;
                    }
                    //Y si no es una opcion valida se pide que se ingrese una
                    else{
                        printf("Por favor, ingrese una opcion valida\n\n");
                    }
               }
               break;
            }
            //Si se ingresa el 3 ingresamos los valores en la factura
            else if(strcmp(opcion1, "3") == 0){
                IngresarFacturas(ListaFacturas);
                VolverMenu();
                break;
            }
            //Si es un 4 volvemos al menu principal
            else if(strcmp(opcion1, "4") == 0){
                break;
            }

            else{
                printf("Por favor, ingrese una opcion valida\n\n");

            }
        }
    }
    //Si se ingresa un 2 vamos a la opcion de analisis y recomendaciones
    else if (strcmp(opcion, "2") == 0){
        while(true){
            printf("========== Analisis y Recomendaciones ==========\n");
            printf("1.Analisis de consumo\n");
            printf("2.Ver recomendaciones\n");
            printf("3.Atras\n");

            scanf("%s", opcion1);
            //Si nos ingresan el 1 corremos la funcion de analisis de consumo
            if (strcmp(opcion1, "1") == 0){
                AnalizarConsumo(ListaDispositivos, ListaFacturas, HeapMax, HeapMin);
                VolverMenu();
                break;
            }
            //Si se ingresa el 2 corremos la funcion de recomendaciones
            else if (strcmp(opcion1, "2") == 0){
                VerRecomendaciones(ListaDispositivos, ListaFacturas);
                VolverMenu();
                break;
            }
            //Con esta volvemos al menu ´principal
            else if(strcmp(opcion1, "3") == 0){
                break;
            }

            else{
                printf("Por favor, ingrese una opcion valida\n\n");
            }
        }
    }
    //Si se ingresa el 3 mostramos las opciones de facturas y huella de carbono
    else if (strcmp(opcion, "3") == 0){
        while(true){
            printf("========== Facturas y Huella de Carbono ==========\n");
            printf("1.Ver facturas\n");
            printf("2.Calcular huella de carbono\n");
            printf("3.Atras\n");

            scanf("%s", opcion1);
            //Mostramos las facturas ingresadas
            if(strcmp(opcion1, "1") == 0){
                verFacturas(ListaFacturas);
                VolverMenu();
                break;
            }
            //Calculamos la huella de carbono
            else if(strcmp(opcion1, "2") == 0){
                CalcularHuellaDeCarbono(ListaFacturas); 
                VolverMenu();
                break;
            }
            //Volvemos al menu principal
            else if(strcmp(opcion1, "3") == 0){
                break;
            }

            else{
                printf("Por favor, ingrese una opcion valida\n\n");
            }
        }

    }
    //En esta opcion mostramos los dispositivos de mayor y menor consumo
    else if (strcmp(opcion, "4") == 0){
        while(true){
            printf("========== Funciones Avanzadas ==========\n");
            printf("1.Mostrar dispositivos por consumo bajo\n");
            printf("2.Mostrar mayores consumidores de energía\n");
            printf("3.Atras\n");

            scanf("%s", opcion1);
            //Mostramos el monticulo minimo
            if(strcmp(opcion1, "1") == 0){
                Mostrar5Min(HeapMin);
                VolverMenu();
                break;
            }
            //Mostramos el monticulo maximo
            else if(strcmp(opcion1, "2") == 0){
                Mostrar5Max(HeapMax);
                VolverMenu();
                break;
            }
            //Volvemos al menu principal
            else if(strcmp(opcion1, "3") == 0){
                break;
            }

            else{
                printf("Por favor, ingrese una opcion valida\n\n");

            }
        }

    }
    //Mostramos los dispositivos segun criterios
    else if (strcmp(opcion, "5") == 0){
        while(true){
            printf("========== Mis Dispositivos ==========\n");
            printf("1. Ver todos mis dispositivos\n");
            printf("2. Ver dispositivos por categoria\n");
            printf("3. Buscar dispositivo\n");
            printf("4.Atras\n");
            scanf("%s", opcion1);

            //Mostramos todos los registrados
            if(strcmp(opcion1, "1") == 0){
                VerTodosDispositivos(ListaDispositivos);
                VolverMenu();
                break;
            }
            //Mostramos por categoria
            else if(strcmp(opcion1, "2") == 0){
                VerDispositivosCategoria(ListaCategorias); 
                VolverMenu();
                break;

            }
            //O buscamos uno en especifico
            else if(strcmp(opcion1, "3") == 0){
                BuscarDispositivos(ListaDispositivos);
                VolverMenu();
                break;
            }
            //Volvemos al menu principal
            else if(strcmp(opcion1, "4") == 0){
                break;
            }

            else{
                printf("Por favor, ingrese una opcion valida\n\n");

            }
        }

    }
    //Mostarmos el uso y proposito de nuestra aplicacion
    else if (strcmp(opcion, "6") == 0){
        while(true){
            printf("========== Acerca de EcoHogar ==========\n");
            printf("1. ¿Como usar nuestra aplicacion?\n");
            printf("2. Nuestro proposito\n");
            printf("3. Acerca de nuestros creadores\n");
            printf("4.Atras\n");
            scanf("%s", opcion1);

            if(strcmp(opcion1, "1") == 0){
                ComoUsar();
                VolverMenu();
                break;
            }

            else if(strcmp(opcion1, "2") == 0){
                NuestroProposito();
                VolverMenu();
                break;
            }

            else if(strcmp(opcion1, "3") == 0){
                AcercaDeNosotros();
                VolverMenu();
                break;
            }

            else if(strcmp(opcion1, "4") == 0){
                break;
            }

            else{
                printf("Por favor, ingrese una opcion valida\n\n");
            }
        }

    }

    //Opcion para cerrar el programa
    else if (strcmp(opcion, "7") == 0){
        while(true){
            //Confirmanos la salida
            printf("Usted esta saliendo de EcoHogar\n");
            printf("1. Confirmar\n");
            printf("2. Cancelar\n");

            scanf("%s", opcion1);

            if(strcmp(opcion1, "1") == 0){
                exit(0);
            }
            else if(strcmp(opcion1, "2") == 0){
                VolverMenu();
                break;

            }
            else{
                printf("Por favor, ingrese una opcion valida\n\n");
            }
        }

    }

    //Opcion valida para el menu principal
    else{
        printf("Por favor, ingrese una opcion valida\n\n");
    }
  }
  return 0;
}