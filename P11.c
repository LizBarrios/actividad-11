/* BARRIOS RETANA LIZETH 372813
24-oct-23
PRÁCTICA 11
Realiza el programa que contenga el siguiente menú
  MENU
    1.- Agregar
    a) manual (1)
    b) Automatico (100)
    c) Reegresar
    2.- Eliminar R/egistro
    3.- Buscar
    4.- Ordenar
    5.- Imprimir
    6.- Archivo Texto
    0.- Salir
El programa deberá poder almacenar en un arreglo (máximo 2,000 registros) los datos para generar el CURP la estructura debe contener 2 estructuras anidadas, nombre y fecha nacimiento y un campo donde se escribirá automáticamente el curp basado en los datos proporcionados
 BRL_act11_1_932
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "BRL.h"
#include "CURP.h"
// #include "Lizeth.h"
#include <time.h>
#include <conio.h>

typedef struct Reg
{
  char Nombre[30];
  char SegNom[30];
  char ApPat[30];
  char ApMat[30];
  char Lugar[40];
  char CURP[19];
  int Matricula;
  char Fecha[11];
  int Edad;
  char sexo[10];
  char Status;
} Tdatos;

void pedirdatos(Tdatos registros[], int *numReg);
void datosautomaticos(Tdatos registros[], int *numReg);
int nacimiento(int mes, int bis);
void eliminarregistro(Tdatos registros[], int *numReg, int matricula_a_eliminar);
void imprimir(Tdatos registros[], int numReg);
void imprimir2(Tdatos registros[], int numReg, int matricula);
void ordenar(Tdatos registros[], int *numReg);
int particion(Tdatos registros[], int ri, int rs);
void quicksort(Tdatos registros[], int ri, int rs);
void ordenarQuickSort(Tdatos registros[], int *numReg);
void buscar(Tdatos registros[], int *numReg);
void texto(Tdatos registros[], int numReg, FILE *file, char *nomArchivo);
void eliminarRegistrotexto(Tdatos registros[], int *numReg, FILE *file, int matricula_a_eliminar, char *nomArchivo);
int buscar2(Tdatos registros[], int *numReg, int matricula);
void imprimirELIMINADOS(Tdatos registros[], int numReg);
void dar_de_alta_registro(Tdatos registros[], int *numReg, int matricula_dar_de_alta);

int main()
{
  srand(time(NULL));
  Tdatos registro[2000];
  FILE *archivo;
  char nomArchivo[20];
  int opc, opc2, opc3, opc4;
  int menu, numReg = 0;
  int ElimiMat, num_matricula = 0, encontrado, ordenado, darAltaMat;

  do
  {
    menu = 1;
    opc = validarNumeros("\n--MENU--\n1. Agregar\n2. Eliminar registro\n3. Buscar\n4. Ordenar\n5. Imprimir\n6. Archivo texto\n0. salir\n", 0, 6);
    switch (opc)
    {
    case 0:
      system("cls");
      printf("FIN DEL PROGRAMA");
      return 0;
      break;
    case 1:
      opc2 = validarNumeros("\n--MENU--\n1. MANUAL\n2. AUTOMATICO\n3.REGRESAR\n", 1, 3);
      switch (opc2)
      {
      case 1:
        if (numReg < 1999)
        {
          pedirdatos(registro, &numReg);
          ordenado = 1;
        }
        else
        {
          printf("REGISTROS LLENOS");
          getch();
        }
        break;
      case 2:
        if (numReg < 1999)
        {
          datosautomaticos(registro, &numReg);
          ordenado = 1;
        }
        else
        {
          printf("REGISTROS LLENOS");
          getch();
        }
        break;

      case 3:
        menu = 1;

        break;
      }

      break;
    case 2:
      if (numReg > 0)
      {
        opc3 = validarnumeros("\n--MENU--\n1.- DAR DE BAJA\n2.- DAR DE ALTA\n3.-REGRESAR\n", 1, 3);
        switch (opc3)
        {
        case 1:
          ElimiMat = validarNumeros("INGRESE LA MATRICULA DEL REGISTRO PARA ELIMINAR SU REGISTRO\n", 200000, 400000);
          encontrado = buscar2(registro, &numReg, ElimiMat);
          if (encontrado == 1)
          {
            num_matricula = validarNumeros("QUIERES ELIMINAR ESTE REGISTRO?\n1. SI\n2. NO\n", 1, 2);
            if (num_matricula == 1)
            {
              eliminarregistro(registro, &numReg, ElimiMat);
              eliminarRegistrotexto(registro, &numReg, archivo, ElimiMat, nomArchivo);
              ordenado = 1;
            }
          }
          break;
        case 2:
          darAltaMat = validarnumeros("INGRESE LA MATRICULA DEL REGISTRO PARA DAR DE ALTA SU REGISTRO\n", 200000, 400000);
          encontrado = buscar2(registro, &numReg, ElimiMat);
          if (encontrado == 1)
          {
            num_matricula = validarnumeros("QUIERES DAR DE ALTA ESTE REGISTRO?\n1.-SI\n2.-NO\n", 1, 2);
            if (num_matricula == 1)
            {
              dar_de_alta_registro(registro, &numReg, darAltaMat);
              eliminarRegistrotexto(registro, &numReg, archivo, darAltaMat, nomArchivo);
              ordenado = 1;
            }
          }
          break;
        case 3:
          menu = 1;

          break;
        }
      }
      else
      {
        printf("No hay registros existentes para eliminar\n");
      }
      break;

    case 3:
      buscar(registro, &numReg);
      break;
    case 4:
      if (ordenado == 1)
      {
        if (numReg <= 500)
        {
          ordenar(registro, &numReg);
          printf("ORDENADO POR METODO DE BURBUJA\n");
        }
        else
        {
          ordenarQuickSort(registro, &numReg);
          printf("ORDENADO POR METODO QUICKSORT\n");
        }
        ordenado = 0;
      }
      else
      {
        printf("YA ESTA ORDENADO\n");
        getch();
      }
      break;
    case 5:
      if (numReg > 0)
      {
        opc4 = validarnumeros("\n--MENU--\n1.-REGISTROS DE ALTA\n2.-REGISTROS DADOS DE BAJA\n3.-REGRESAR\n", 1, 3);
        switch (opc4)
        {
        case 1:
          imprimir(registro, numReg);
          break;

        case 2:
          imprimirELIMINADOS(registro, numReg);

          break;
        case 3:
          menu = 1;
          break;
        }
      }
      else
      {
        printf("No hay registros para imprimir.\n");
      }
      break;
    case 6:
      printf("INGRESE EL NOMBRE DEL ARCHIVO\n");
      gets(nomArchivo);
      strcat(nomArchivo, ".txt");
      archivo = fopen(nomArchivo, "a");

      texto(registro, numReg, archivo, nomArchivo);

      break;
    }
  } while (menu == 1);
}

void datosautomaticos(Tdatos registros[], int *numReg)
{
  char hombres[20][10] = {"JUAN", "PEDRO", "CARLOS", "LUIS", "JAVIER", "ANDRES", "ALEJANDRO", "MIGUEL", "JOSE", "ADAN", "JORGE", "GABRIEL", "ROBERTO", "DAVID", "FERNANDO", "RAUL", "EDUARDO", "SERGIO", "ANTONIO", "FRANCISCO"};
  char mujeres[20][10] = {"DANIELA", "LAURA", "ANA", "CARMEN", "SOFIA", "ISABEL", "MARTA", "PAULA", "ELENA", "PATRICIA", "LUCIA", "CLARA", "ROSA", "BEATRIZ", "CAROLINA", "JULIA", "TERESA", "SARA", "IRENE", "ADRIANA"};
  char apPaterno[20][10] = {"BARRIOS", "RODRIGUEZ", "LOPEZ", "PEREZ", "MARTINEZ", "SANCHEZ", "FERNANDEZ", "GONZALEZ", "RAMIREZ", "TORRES", "MARTIN", "JIMENEZ", "RUIZ", "DIAZ", "SOTO", "GOMEZ", "LOZANO", "CASTRO", "HERRERA", "GARCIA"};
  char apMaterno[20][10] = {"SUAREZ", "VILLEGAS", "GUERRERO", "PALACIOS", "FARIAS", "AVILA", "MOLINA", "SALAZAR", "DELGADO", "SANCHEZ", "FLORES", "MORALES", "ROMERO", "OROZCO", "RIVERA", "CASTILLO", "CHAVEZ", "SUAREZ", "VILLEGAS", "GUERRERO"};
  char GenSex[2][10] = {"HOMBRE", "MUJER"};

  int i, j, k;

  for (k = 0; k < 100; k++)
  {
    Tdatos *registro = &registros[*numReg];
    char nom[15], nom2[10], AP[20], AM[20];
    char tem1[20], tem2[15];
    char consonantes[21] = "BCDFGHJKLMNPQRSTVWXYZ";
    char genero[2][10] = {"H", "M"};
    char fecha[11], diferenciador[] = "0", validadorchar[2], abreviacion[2], cuadro1[5], finalnombre[4], sexo[2], curp[20], date[12];
    int year = 0, mes = 0, dia = 0, edad = 0, numsexo = 0, matricula = 0, lugar = 0;
    int dosfinales, bis, validadorint, SegundoNom;

    char estadosMexico[33][40] = {
        "AGUASCALIENTES", "BAJA CALIFORNIA", "BAJA CALIFORNIA SUR", "CAMPECHE", "COAHUILA", "COLIMA", "CHIAPAS",
        "CHIHUAHUA", "CIUDAD DE MEXICO", "DURANGO", "GUANAJUATO", "GUERRERO", "HIDALGO", "JALISCO",
        "ESTADO DE MEXICO", "MICHOACAN", "MORELOS", "NAYARIT", "NUEVO LEON", "OAXACA", "PUEBLA",
        "QUERETARO", "QUINTANA ROO", "SAN LUIS POTOSI", "SINALOA", "SONORA", "TABASCO", "TAMAULIPAS",
        "TLAXCALA", "VERACRUZ", "YUCATAN", "ZACATECAS", "NACIDO EN EL EXTRANJERO"};

    char abreviacionesEstadosMexico[33][4] = {
        "AS", "BC", "BS", "CC", "CL", "CM", "CS", "CH", "DF", "DG", "GT", "GR", "HG", "JC",
        "MC", "MN", "MS", "NT", "NL", "OC", "PL", "QT", "QR", "SP", "SL", "SR", "TC", "TS",
        "TL", "VZ", "YN", "ZS", "NE"};

    matricula = random(200000, 400000);
    registro->Matricula = matricula;

    numsexo = random(1, 2);
    strcpy(registro->sexo, GenSex[numsexo - 1]);
    if (numsexo == 1)
    {
      strcpy(nom, hombres[random(0, 19)]);
      strcpy(registro->Nombre, nom);
      SegundoNom = rand() % 2;
      if (SegundoNom == 0)
      {
        strcpy(nom2, hombres[random(0, 19)]);
        strcpy(registro->SegNom, nom2);
      }
    }
    else
    {
      strcpy(nom, mujeres[random(0, 19)]);
      strcpy(registro->Nombre, nom);
      if (SegundoNom == 0)
      {
        strcpy(nom2, mujeres[random(0, 19)]);
        strcpy(registro->SegNom, nom2);
      }
    }
    quitarespacio(nom);
    strcpy(tem2, nom);

    if (strcmp(nom, "MARIA") == 0 || strcmp(nom, "JOSE") == 0)
    {
      strcpy(nom, nom2);
    }

    strcpy(AP, apPaterno[random(0, 19)]);
    strcpy(registro->ApPat, AP);
    validarAP(AP);
    quitarespacio(AP);
    strcpy(tem1, AP);

    if (strlen(AP) == 0)
    {
      strcpy(AP, "X");
    }
    strcpy(AM, apMaterno[random(0, 19)]);
    strcpy(registro->ApMat, AM);
    quitarespacio(AM);
    if (strlen(AM) == 0)
    {
      strcpy(AM, "X");
    }

    for (i = 0; i < 21; i++)
    {
      for (j = 1; AP[j] != '\0'; j++)
      {
        if (AP[j] == consonantes[i])
        {
          AP[j] = AP[j + 1];
          cuadro1[1] = AP[j];
        }
      }
    }

    sprintf(cuadro1, "%c%c%c%c", AP[0], AP[1], AM[0], nom[0]);
    if (strcmp(tem2, "MARIA") == 0 || strcmp(tem2, "JOSE") == 0)
    {
      strcpy(tem2, nom2);
    }

    tresnombre(finalnombre, tem1, AM, tem2);

    palabras_incovenientes(cuadro1);

    year = random(1985, 2005);
    bis = Bisiesto(year);
    dosfinales = year % 100;

    mes = random(1, 12);

    dia = nacimientoaleatorios(mes, bis);
    sprintf(fecha, "%02d%02d%02d", dosfinales, mes, dia);
    sprintf(date, "%02d/%02d/%02d", dia, mes, year);
    strcpy(registro->Fecha, date);

    if (year < 2000)
    {
      strcpy(diferenciador, "0");
    }
    else
    {
      strcpy(diferenciador, "A");
    }

    edad = calcularEdad(year, mes, dia);
    registro->Edad = edad;

    strcpy(sexo, genero[numsexo - 1]);
    strcpy(registro->sexo, GenSex[numsexo - 1]);

    lugar = random(1, 33);
    strcpy(registro->Lugar, estadosMexico[lugar - 1]);
    strcpy(abreviacion, abreviacionesEstadosMexico[lugar - 1]);

    sprintf(curp, "%s%s%s%s%s%s", cuadro1, fecha, sexo, abreviacion, finalnombre, diferenciador);
    validadorint = calcularHomoclave(curp);
    sprintf(validadorchar, "%d", validadorint);
    strcat(curp, validadorchar);
    strcpy(registro->CURP, curp);

    strcpy(registro->CURP, curp);
    (*numReg)++;
    registro->Status = 1;

    if (*numReg > 1999)
    {
      printf("REGISTROS LLENOS");
      k = 100;
    }
  }
}

void pedirdatos(Tdatos registros[], int *numReg)
{
  Tdatos *registro = &registros[*numReg];
  char nom[15], nom2[10], AP[20], AM[20];
  int year = 0, mes = 0, dia = 0, edad = 0, numsexo = 0, matricula = 0, lugar = 0;
  char tem1[20], tem2[15];
  int i, j;
  char consonantes[21] = "BCDFGHJKLMNPQRSTVWXYZ";
  char fecha[11], diferenciador[] = "0", validadorchar[2], abreviacion[2], cuadro1[5], finalnombre[4], sexo[2], curp[20], date[12];
  int num, dosfinales, bis, validadorint;
  char GenSex[2][10] = {"HOMBRE", "MUJER"};
  char genero[2][10] = {"H", "M"};
  int numeros[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33};
  char estadosMexico[33][30] = {
      "AGUASCALIENTES", "BAJA CALIFORNIA", "BAJA CALIFORNIA SUR", "CAMPECHE", "COAHUILA", "COLIMA", "CHIAPAS",
      "CHIHUAHUA", "CIUDAD DE MEXICO", "DURANGO", "GUANAJUATO", "GUERRERO", "HIDALGO", "JALISCO",
      "ESTADO DE MEXICO", "MICHOACAN", "MORELOS", "NAYARIT", "NUEVO LEON", "OAXACA", "PUEBLA",
      "QUERETARO", "QUINTANA ROO", "SAN LUIS POTOSI", "SINALOA", "SONORA", "TABASCO", "TAMAULIPAS",
      "TLAXCALA", "VERACRUZ", "YUCATAN", "ZACATECAS", "NACIDO EN EL EXTRANJERO"};
  char abreviacionesEstadosMexico[33][4] = {
      "AS", "BC", "BS", "CC", "CL", "CM", "CS", "CH", "DF", "DG", "GT", "GR", "HG", "JC",
      "MC", "MN", "MS", "NT", "NL", "OC", "PL", "QT", "QR", "SP", "SL", "SR", "TC", "TS",
      "TL", "VZ", "YN", "ZS", "NE"};
  int num_estados = sizeof(numeros) / sizeof(numeros[0]);

  matricula = validarNumeros("\nINGRESE SU MATRICULA:", 200000, 400000);
  registro->Matricula = matricula;

  num = validarNumeros("TIENE SEGUNDO NOMBRE?\n1.-SI\n2.-NO\n", 1, 2);
  validarletras("ESCRIBA SU NOMBRE: ", nom);
  strcpy(registro->Nombre, nom);
  quitarespacio(nom);
  strcpy(tem2, nom);

  if (num == 1)
  {
    validarletras("ESCRIBA SU SEGUNDO NOMBRE: ", nom2);
    strcpy(registro->SegNom, nom2);
  }
  if (strcmp(nom, "MARIA") == 0 || strcmp(nom, "JOSE") == 0)
  {
    strcpy(nom, nom2);
  }
  validarletras("ESCRIBA SU PRIMER APELLIDO: ", AP);
  strcpy(registro->ApPat, AP);
  validarAP(AP);
  quitarespacio(AP);
  strcpy(tem1, AP);
  if (strlen(AP) == 0)
  {
    strcpy(AP, "X");
  }
  validarletras("ESCRIBA SU SEGUNDO APELLIDO: ", AM);
  strcpy(registro->ApMat, AM);
  quitarespacio(AM);
  if (strlen(AM) == 0)
  {
    strcpy(AM, "X");
  }
  for (i = 0; i < 21; i++)
  {
    for (j = 1; AP[j] != '\0'; j++)
    {
      if (AP[j] == consonantes[i])
      {
        AP[j] = AP[j + 1];
        cuadro1[1] = AP[j];
      }
    }
  }
  sprintf(cuadro1, "%c%c%c%c", AP[0], AP[1], AM[0], nom[0]);
  if (strcmp(tem2, "MARIA") == 0 || strcmp(tem2, "JOSE") == 0)
  {
    strcpy(tem2, nom2);
  }

  tresnombre(finalnombre, tem1, AM, tem2);
  palabras_incovenientes(cuadro1);

  year = validarNumeros("INGRESE SU AÑO DE NACIMIENTO: ", 1900, 2023);
  bis = Bisiesto(year);
  dosfinales = year % 100;
  mes = validarNumeros("INGRESE SU MES DE NACIMIENTO: ", 0, 12);
  dia = nacimiento(mes, bis);
  sprintf(fecha, "%02d%02d%02d", dosfinales, mes, dia);
  sprintf(date, "%02d/%02d/%02d", dia, mes, year);
  strcpy(registro->Fecha, date);

  if (year < 2000)
  {
    strcpy(diferenciador, "0");
  }
  else
  {
    strcpy(diferenciador, "A");
  }

  edad = calcularEdad(year, mes, dia);
  registro->Edad = edad;

  numsexo = validarNumeros("INGRESE SU GENERO:\n1. HOMBRE\n2. MUJER\n", 1, 2);

  strcpy(sexo, genero[numsexo - 1]);
  strcpy(registro->sexo, GenSex[numsexo - 1]);

  printf("+--------+---------------------------++--------+---------------------------++--------+---------------------------+\n");
  printf("| Numero |           Estado          || Numero |           Estado          || Numero |           Estado          |\n");
  printf("+--------+---------------------------++--------+---------------------------++--------+---------------------------+\n");

  for (int l = 0; l < num_estados; l++)
  {

    printf("|   %2d   | %-25s |", numeros[l], estadosMexico[l]);
    if (l % 3 == 2)
    {
      printf("\n");
      printf("+--------+---------------------------++--------+---------------------------++--------+---------------------------+\n");
    }
  }
  lugar = validarNumeros("LUGAR DE NACIMIENTO: ", 1, 33);

  strcpy(registro->Lugar, estadosMexico[lugar - 1]);

  strcpy(abreviacion, abreviacionesEstadosMexico[lugar - 1]);

  sprintf(curp, "%s%s%s%s%s%s", cuadro1, fecha, sexo, abreviacion, finalnombre, diferenciador);
  validadorint = calcularHomoclave(curp);
  sprintf(validadorchar, "%d", validadorint);
  strcat(curp, validadorchar);
  strcpy(registro->CURP, curp);

  registro->Status = 1;
  (*numReg)++;
}

void imprimir(Tdatos registros[], int numReg)
{
  int i, acu = 1;
  if (numReg == 0)
  {
    printf("No hay registros para imprimir.\n");
    return;
  }

  printf("Registros almacenados:\n");
  printf("========================================================================================================================================================================\n");
  printf("|  No. | Matricula |    Nombre    |    Nombre 2   | Apellido Pat.   | Apellido Mat.   | Fecha de Nac. | Edad |  Sexo  |   Lugar de Nacimiento     |        CURP        |\n");
  printf("========================================================================================================================================================================\n");

  for (i = 0; i < numReg; i++)
  {
    printf("| %-4d | %-9d | %-12s | %-13s | %-15s | %-15s | %-13s | %-4d | %-6s | %-25s | %-18s |\n", i + 1, registros[i].Matricula, registros[i].Nombre, registros[i].SegNom, registros[i].ApPat, registros[i].ApMat, registros[i].Fecha, registros[i].Edad, registros[i].sexo, registros[i].Lugar, registros[i].CURP);
    printf("========================================================================================================================================================================\n");

    if (acu == 40)
    {
      getch();
      acu = 0;
    }
    acu++;
  }
}

int nacimiento(int mes, int bis)
{
  int m, dia;
  int day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  m = day[mes];
  if (bis == 1 && mes == 3)
  {
    m = 29;
  }
  if (bis == 0 && mes == 3)
  {
    m = 28;
  }

  dia = validarNumeros("INGRESE SU DIA DE NACIMIENTO: ", 1, m);
  return dia;
}

void eliminarregistro(Tdatos registros[], int *numReg, int matricula_a_eliminar)
{
  int i;
  for (i = 0; i <= *numReg; i++)
  {
    if (registros[i].Matricula == matricula_a_eliminar)
    {
      if (registros[i].Status == 1)
      {
        registros[i].Status = 2;
        printf("REGISTRO DADO DE BAJA\n");

        (*numReg)--;
      }
      else
      {
        printf("EL REGSITRO YA ESTA DADO DE BAJA");
      }
    }
  }
}

void ordenar(Tdatos registros[], int *numReg)
{
  Tdatos temp;
  int i, j;
  for (i = 0; i < *numReg; i++)
  {
    for (j = 0; j < *numReg - 1; j++)
    {
      if (registros[j].Matricula > registros[j + 1].Matricula)
      {
        temp = registros[j];
        registros[j] = registros[j + 1];
        registros[j + 1] = temp;
      }
    }
  }
}

int particion(Tdatos registros[], int ri, int rs)
{
  int tem2;
  int i, j;

  tem2 = registros[rs].Matricula;
  i = (ri - 1);

  for (j = ri; j < rs; j++)
  {
    if (registros[j].Matricula < tem2)
    {
      i++;
      Tdatos temp = registros[i];
      registros[i] = registros[j];
      registros[j] = temp;
    }
  }

  Tdatos temp = registros[i + 1];
  registros[i + 1] = registros[rs];
  registros[rs] = temp;

  return (i + 1);
}

void quicksort(Tdatos registros[], int ri, int rs)
{
  int pi;
  if (ri < rs)
  {
    pi = particion(registros, ri, rs);

    quicksort(registros, ri, pi - 1);
    quicksort(registros, pi + 1, rs);
  }
}

void ordenarQuickSort(Tdatos registros[], int *numReg)
{
  quicksort(registros, 0, *numReg - 1);
}

void buscar(Tdatos registros[], int *numReg)
{
  int numero_matricula, encoontrado = 0;
  int i;

  numero_matricula = validarNumeros("INGRESE LA MATRICULA\n", 300000, 400000);

  for (i = 0; i < *numReg; i++)
  {
    if (registros[i].Matricula == numero_matricula)
    {
      printf("\nRegistro almacenado:\n");
      printf("============================\n");
      printf("Registro: %d\n", i + 1);
      printf("Matricula: %d\n", registros[i].Matricula);
      printf("Nombre: %s\n", registros[i].Nombre);
      printf("Apellido Paterno: %s\n", registros[i].ApPat);
      printf("Apellido Materno: %s\n", registros[i].ApMat);
      printf("Fecha de nacimiento: %s\n", registros[i].Fecha);
      printf("Edad: %d\n", registros[i].Edad);
      printf("Sexo: %s\n", registros[i].sexo);
      printf("Lugar de nacimiento: %s\n", registros[i].Lugar);
      printf("Curp: %s\n", registros[i].CURP);
      printf("============================\n");
      encoontrado = 1;
    }
  }
  if (encoontrado == 0)
  {
    printf("NO SE ENCONTRO LA MATRICULA\n\n");
  }
}

void texto(Tdatos registros[], int numReg, FILE *file, char *nomArchivo)
{

  int i;

  file = fopen(nomArchivo, "w");
  for (i = 0; i < numReg; i++)
  {
    if (file != NULL)
    {
      fprintf(file, " ");
    }
  }
  if (numReg == 0)
  {
    fprintf(file, "No hay registros para imprimir.\n");
    fclose(file);
    return;
  }

  fprintf(file, "\nRegistros almacenados:\n");
  fprintf(file, "========================================================================================================================================================================\n");
  fprintf(file, "|  No. | Matricula |    Nombre    |    Nombre 2   | Apellido Pat.   | Apellido Mat.   | Fecha de Nac. | Edad |  Sexo  |   Lugar de Nacimiento     |        CURP        |\n");
  fprintf(file, "========================================================================================================================================================================\n");

  for (int i = 0; i < numReg; i++)
  {
    fprintf(file, "| %-4d | %-9d | %-12s | %-13s | %-15s | %-15s | %-13s | %-4d | %-6s | %-25s | %-18s |\n", i + 1, registros[i].Matricula, registros[i].Nombre, registros[i].SegNom, registros[i].ApPat, registros[i].ApMat, registros[i].Fecha, registros[i].Edad, registros[i].sexo, registros[i].Lugar, registros[i].CURP);
    fprintf(file, "========================================================================================================================================================================\n");
  }

  fclose(file);
}

void eliminarRegistrotexto(Tdatos registros[], int *numReg, FILE *file, int matricula_a_eliminar, char *nomArchivo)
{

  int i;

  file = fopen(nomArchivo, "w");
  fprintf(file, "\nRegistros almacenados:\n");
  fprintf(file, "========================================================================================================================================================================\n");
  fprintf(file, "|  No. | Matricula |    Nombre    |    Nombre 2   | Apellido Pat.   | Apellido Mat.   | Fecha de Nac. | Edad |  Sexo  |   Lugar de Nacimiento     |        CURP        |\n");
  fprintf(file, "========================================================================================================================================================================\n");

  for (i = 0; i < *numReg; i++)
  {
    if (registros[i].Status == 1)
    {
      fprintf(file, "| %-4d | %-9d | %-12s | %-13s | %-15s | %-15s | %-13s | %-4d | %-6s | %-25s | %-18s |\n", i + 1, registros[i].Matricula, registros[i].Nombre, registros[i].SegNom, registros[i].ApPat, registros[i].ApMat, registros[i].Fecha, registros[i].Edad, registros[i].sexo, registros[i].Lugar, registros[i].CURP);
      fprintf(file, "========================================================================================================================================================================\n");
    }
  }
  fclose(file);
}

int buscar2(Tdatos registros[], int *numReg, int matricula)
{
  int i;

  for (i = 0; i < *numReg; i++)
  {
    if (registros[i].Matricula == matricula)
    {
      printf("\nRegistro almacenado:\n");
      printf("============================\n");
      printf("Registro: %d\n", i + 1);
      printf("Matricula: %d\n", registros[i].Matricula);
      printf("Nombre: %s\n", registros[i].Nombre);
      printf("Apellido Paterno: %s\n", registros[i].ApPat);
      printf("Apellido Materno: %s\n", registros[i].ApMat);
      printf("Fecha de nacimiento: %s\n", registros[i].Fecha);
      printf("Edad: %d\n", registros[i].Edad);
      printf("Sexo: %s\n", registros[i].sexo);
      printf("Lugar de nacimiento: %s\n", registros[i].Lugar);
      printf("Curp: %s\n", registros[i].CURP);
      printf("============================\n");
      return 1;
    }
  }

  printf("NO SE ENCONTRO LA MATRICULA\n\n");
  return 0;
}

void dar_de_alta_registro(Tdatos registros[], int *numReg, int matricula_dar_de_alta)
{
  int i;
  for (i = 0; i <= *numReg; i++)
  {
    if (registros[i].Matricula == matricula_dar_de_alta)
    {
      if (registros[i].Status == 2)
      {
        registros[i].Status = 1;
        printf("REGISTRO DADO DE ALTA\n");

        (*numReg)++;
      }
      else
      {
        printf("EL REGSITRO NO ESTA DADO DE BAJA");
      }
    }
  }
}

void imprimirELIMINADOS(Tdatos registros[], int numReg)
{
  int i, acu = 1;
  int dadoDbaja = 2;

  for (i = 0; i <= numReg; i++)
  {
    if (registros[i].Status == 2)
    {
      dadoDbaja = 1;
    }
  }

  if (dadoDbaja == 1)
  {
    printf("Registros almacenados:\n");
    printf("========================================================================================================================================================================\n");
    printf("|  No. | Matricula |    Nombre    |    Nombre 2   | Apellido Pat.   | Apellido Mat.   | Fecha de Nac. | Edad |  Sexo  |   Lugar de Nacimiento     |        CURP        |\n");
    printf("========================================================================================================================================================================\n");

    for (i = 0; i <= numReg; i++)
    {
      if (registros[i].Status == 2)
      {

        printf("| %-4d | %-9d | %-12s | %-13s | %-15s | %-15s | %-13s | %-4d | %-6s | %-25s | %-18s |\n", i + 1, registros[i].Matricula, registros[i].Nombre, registros[i].SegNom, registros[i].ApPat, registros[i].ApMat, registros[i].Fecha, registros[i].Edad, registros[i].sexo, registros[i].Lugar, registros[i].CURP);
        printf("========================================================================================================================================================================\n");
        dadoDbaja = 1;
        if (acu == 40)
        {
          getch();
          acu = 0;
        }
        acu++;
      }
    }
  }
  if (dadoDbaja == 2)
  {
    printf("No hay registros dados de baja\n");
  }
}
