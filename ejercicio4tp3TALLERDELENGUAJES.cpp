/*
Considere la siguiente situación: En una distribuidora necesita implementar la carga de productos 
de sus preventistas, los cuales recolectan los productos que sus clientes van necesitando. 
El sistema que se utiliza en la empresa es desarrollado por equipos de programadores donde cada equipo
 se encarga de una tarea específica. Usted forma parte del equipo de programación que se encargará de hacer
  el módulo para los preventistas:
Tareas
Cada preventista puede visitar hasta 5 clientes, los cuales por cuestiones operativas 
solo puede pedir hasta 10 productos
Las estructuras de datos necesarias son las siguientes:
Char *TiposProductos[]={“Galletas”,”Snack”,”Cigarrillos”,”Caramelos”,”Bebidas”};
struct Producto {
int ProductoID; //Numerado en ciclo iterativo
int Cantidad; // entre 1 y 10
char *TipoProducto; // Algún valor del arreglo TiposProductos
float PrecioUnitario; // entre 10 - 100
};
struct Cliente {
int ClienteID; // Numerado en el ciclo iterativo
char *NombreCliente; // Ingresado por usuario
int CantidadProductosAPedir; // (alteatorio entre 1 y 5)
Pruducto *Productos //El tamaño de este arreglo depende de la variable
// “CantidadProductosAPedir”
};


1. Desarrollar una interfaz por consola donde se solicite al usuario la cantidad de clientes.
2. Solicitar al usuario la carga de los clientes creados dinámicamente en el paso anterior.
3. A medida que se dé de alta cada cliente, Generar aleatoriamente la cantidad de productos asociados al cliente y sus características. Ej: producto cargado nro. 2
Producto
{
ProductoID=2
Cantidad = 1;
*TipoProducto = “Snack”;
PrecioUnitario = 100; }
4. Implemente una función que calcule el costo total de un producto. Esta función debe recibir como parámetro el producto y devolver el resultado de calcular la Cantidad por el PrecioUnitario.
5. Mostrar por pantalla todo lo cargado. Incluyendo un total a pagar por cliente (sumatoria del costo de todos los productos)

*/

//BIBLIOTECAS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

//ESTRUCTURAS
struct Producto {
int ProductoID; //Numerado en ciclo iterativo
int Cantidad; // entre 1 y 10
char *TipoProducto; // Algún valor del arreglo TiposProductos
float PrecioUnitario; // entre 10 - 100
};
struct Cliente {
int ClienteID; // Numerado en el ciclo iterativo
char *NombreCliente; // Ingresado por usuario
int CantidadProductosAPedir; // (alteatorio entre 1 y 5)
Producto *Productos; //El tamaño de este arreglo depende de la variable
// “CantidadProductosAPedir”
};
//alias de las estructuras:
typedef struct Cliente CLIENTE;

//PROTOTIPOS
void crearClientes(CLIENTE *customer, int cantidad);
void cargarProducto(Producto *product, int productos);
int costoTotal(Producto *product);
void mostrarProductos(Producto *product, int cantidadAMostrar);

//variable global
int TAMANHO = 50;
int maxDeClientes = 5;
char *TiposProductos[]={"Galletas","Snack","Cigarrillos","Caramelos","Bebidas"};

//FUNCION PRINCIPAL
int main()
{
    //semilla
    srand(time(0));
    //1. Desarrollar una interfaz por consola donde se solicite al usuario la cantidad de clientes.
    int cantidadClientes = 0;//ESTA VARIABLE MUESTRA LA CANTIDAD DE CLIENTES DE CADA PREVENTISTA
    CLIENTE *clientes;//puntero a estructuras
    do
    {
        printf("POR FAVOR INGRESE LA CANTIDAD DE CLIENTES\n");
        scanf("%d", &cantidadClientes);
        fflush(stdin);
    } while (cantidadClientes > maxDeClientes && cantidadClientes < 0);//condicion de salida, los clientes deben ser 5 o menos
    //2. Solicitar al usuario la carga de los clientes creados dinámicamente en el paso anterior.
    clientes = (CLIENTE*)malloc(sizeof(CLIENTE)*cantidadClientes);//reservo memoria para ingresar los clientes
    crearClientes(clientes, cantidadClientes);//llamo a la funcion crearClientes para darlos de alta
    //5. Mostrar por pantalla todo lo cargado. Incluyendo un total a pagar por cliente (sumatoria del costo de todos los productos)
    //muestro clientes y productos;
    for (int i = 0; i < cantidadClientes; i++)
    {
        printf("\n\n");
        printf("ID cliente:\t%d.\n", clientes[i].ClienteID);
        printf("Nombre:\t%s.\n", clientes[i].NombreCliente);
        printf("Cantidad de Productos Pedidos:\t%d\n", clientes[i].CantidadProductosAPedir);
        mostrarProductos(clientes[i].Productos, clientes[i].CantidadProductosAPedir);
        printf("\n\n");
    }

    /* final del programa */
    printf("\n\nFINAL DEL PROGRAMA\npresione enter para finalizar:\n");
    getchar();
    return 0;
}

//OTROS METODOS
void crearClientes(CLIENTE *customer, int cantidad)
{
    char auxCustomer[50];//variable auxiliar para cargar el nombre de 
    for (int i = 0; i < cantidad; i++)
    {
        //le asigno el id al cliente:
        customer[i].ClienteID = i+1;
        //cargo el nombre:
        printf("POR FAVOR INGRESE EL NOMBRE DEL CLIENTE: ");
        scanf("%s", &auxCustomer);
        fflush(stdin);
        customer[i].NombreCliente = (char*) malloc((strlen(auxCustomer)+1) * sizeof(char));
        strcpy(customer[i].NombreCliente, auxCustomer);
        //printf("\n%s\n", customer[i].NombreCliente);
        //productos
        //primero cargo la cantidad
        customer[i].CantidadProductosAPedir = rand() % 5 + 1;
        customer[i].Productos = (Producto*)malloc(customer[i].CantidadProductosAPedir * sizeof(Producto));
        //cargo los productos con la funcion
        cargarProducto(customer[i].Productos, customer[i].CantidadProductosAPedir);
        //getchar();
    }
}

void cargarProducto(Producto *product, int productos)
{
    int aleatorio;
    char *auxiliarProducto;
    for (int i = 0; i < productos; i++)
    {
        aleatorio = rand()% 5;
        product[i].ProductoID = aleatorio;
        product[i].Cantidad = rand() % 10+1;
        auxiliarProducto = TiposProductos[aleatorio];
        product[i].TipoProducto = (char*) malloc((strlen(auxiliarProducto)+1) * sizeof(char));
        strcpy(product[i].TipoProducto, auxiliarProducto);
        product[i].PrecioUnitario = rand() % 91+10;
    } 
}

int costoTotal(Producto *product)
{
    float costoUnitario;
    costoUnitario = (product->Cantidad)*(product->PrecioUnitario);
    return costoUnitario;
}

void mostrarProductos(Producto *product, int cantidadAMostrar)
{
    float total = 0;
    for (int i = 0; i < cantidadAMostrar; i++)
    {
        printf("ID del Producto %d:\t%d.\n", i+1, product[i].ProductoID);
        printf("Cantidad de Productos:\t%d.\n", product[i].Cantidad);
        printf("Tipo de Producto:\t%s.\n", product[i].TipoProducto);
        printf("Precio Unitario:\t%.2f.\n", product[i].PrecioUnitario);
        total = total + costoTotal(product+i);
        printf("total: %d\n", total);
    }
    printf("Total a pagar:\t%.2f\n", total);   
}
