#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

typedef struct {
    int codigo;
    char descripcion[41];
    float precio;
} tproducto;


void continuar()
{
    printf("Presione una tecla para continuar\n\n");
    getch();
}

void crear()
{
    FILE *arch;
    arch=fopen("productos.dat","wb");
    if (arch==NULL)
        exit(1);
    fclose(arch);
    continuar();
}


void cargar()
{
    FILE *arch;
    arch=fopen("productos.dat","ab");
    if (arch==NULL)
        exit(1);
    tproducto producto;
    printf("Ingrese el codigo del producto:");
    scanf("%i",&producto.codigo);
    fflush(stdin);
    printf("Ingrese el nombre del producto:");
    gets(producto.descripcion);
    printf("Ingrese precio:");
    scanf("%f",&producto.precio);
    fwrite(&producto, sizeof(tproducto), 1, arch);
    fclose(arch);
    continuar();
}

void listado()
{
    FILE *arch;
    arch=fopen("productos.dat","rb");
    if (arch==NULL)
        exit(1);
    tproducto producto;
    fread(&producto, sizeof(tproducto), 1, arch);
    while(!feof(arch))
    {
        printf("%i %s %0.2f\n", producto.codigo, producto.descripcion, producto.precio);
        fread(&producto, sizeof(tproducto), 1, arch);
    }
    fclose(arch);
    continuar();
}

void consulta()
{
    FILE *arch;
    arch=fopen("productos.dat","rb");
    if (arch==NULL)
        exit(1);
    printf("Ingrese el codigo de producto a consultar:");
    int cod;
    scanf("%i", &cod);
    tproducto producto;
    int existe=0;
    fread(&producto, sizeof(tproducto), 1, arch);
    while(!feof(arch))
    {
        if (cod==producto.codigo)
        {
           printf("%i %s %0.2f\n", producto.codigo, producto.descripcion, producto.precio);
           existe=1;
           break;
        }
        fread(&producto, sizeof(tproducto), 1, arch);
    }
    if (existe==0)
        printf("No existe un producto con dicho codigo\n");
    fclose(arch);
    continuar();
}

void modificacion()
{
    FILE *arch;
    arch=fopen("productos.dat","r+b");
    if (arch==NULL)
        exit(1);
    printf("Ingrese el codigo de producto a modificar:");
    int cod;
    scanf("%i", &cod);
    tproducto producto;
    int existe=0;
    fread(&producto, sizeof(tproducto), 1, arch);
    while(!feof(arch))
    {
        if (cod==producto.codigo)
        {
           printf("%i %s %0.2f\n", producto.codigo, producto.descripcion, producto.precio);
           printf("Ingrese nuevo precio:");
           scanf("%f",&producto.precio);
           int pos=ftell(arch)-sizeof(tproducto);
           fseek(arch,pos,SEEK_SET);
           fwrite(&producto, sizeof(tproducto), 1, arch);
           printf("Se modifico el precio para dicho producto.\n");
           existe=1;
           break;
        }
        fread(&producto, sizeof(tproducto), 1, arch);
    }
    if (existe==0)
        printf("No existe un producto con dicho codigo\n");
    fclose(arch);
    continuar();
}

void reporteHTML()
{
    FILE *arch;
    arch=fopen("productos.dat","rb");
    if (arch==NULL)
        exit(1);

    tproducto producto;

    FILE *archivo;


    archivo = fopen("filomena.html","w+");

    if (archivo == NULL)
            {
                printf("\nError de apertura del archivo. \n\n");
            }else{

    int existe=0;

    fprintf(archivo,"%s","<!DOCTYPE html> <html lang=\"es\">  <head>  <meta charset=\"utf-8\" <!-- Bootstrap CSS -->  <link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\" integrity=\"sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T\" crossorigin=\"anonymous\"> </head>\n");
    fprintf(archivo,"%s"," <body> <table class=\"table table-dark\"> <thead> \n <tr> <th scope=\"col\">#</th> <th scope=\"col\">id</th> <th scope=\"col\">Descripcion</th> <th scope=\"col\">Precio $</th> </tr> </thead>");
    fprintf(archivo,"%s","\n<tbody>");


    fread(&producto, sizeof(tproducto), 1, arch);

    while(!feof(arch))
    {
        fprintf(archivo,"%s","\n\n\n<tr>");
        fprintf(archivo,"%s","\n<th scope=\"col\">#</th>");
        fprintf(archivo,"<td>%i</td>  <td>%s</td> <td>%0.2f</td>\n", producto.codigo, producto.descripcion, producto.precio);
        fprintf(archivo,"%s","\n</tr>");

        fread(&producto, sizeof(tproducto), 1, arch);
    }
    fprintf(archivo,"%s","\n </tbody>\n</table>\n</body>");

    }
    fclose(archivo);
    fclose(arch);
    continuar();
}

int main()
{
    int opcion;
    do {
        printf("1 - Crear un archivo binario llamado \"productos.dat\"\n");
        printf("2 - Carga de registros de tipo tproducto\n");
        printf("3 - Listado completo de productos.\n");
        printf("4 - Consulta de un producto por su codigo.\n");
        printf("5 - Modificacion del precio de un producto. \n");
        printf("6 - Generar reporte html. \n");
        printf("7 - Finalizar\n\n");
        printf("Ingrese su opcion:");
        scanf("%i",&opcion);
        switch (opcion) {
            case 1:crear();
                   break;
            case 2:cargar();
                   break;
            case 3:listado();
                   break;
            case 4:consulta();
                   break;
            case 5:modificacion();
                   break;
            case 6:reporteHTML();
        }
    } while (opcion!=7);
    return 0;
}
