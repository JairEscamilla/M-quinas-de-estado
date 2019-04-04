/****************************************************************
 *								*
 * Archivo:	state_mach1.c					*
 * Descripcion: Codigo Fuente para implementar el programa	*
 *		de maquina de estados.			 	*
 *								*
 ****************************************************************/
//Coment

/*************** ARCHIVOS DE INCLUSION ***************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tables.h"


/*************** VARIABLES GLOBALES ***************/
EVENT event;
int state;
char buf[BUFFER];
int Salir=0;
TipoLista *Inicio=NULL;
char Usuario[100],Password[100];

/*************** PROTOTIPOS DE FUNCION ***************/
void initialise(void);
void getevent(void);

int Creditos(void);
int CargarBase(void);
int Imprimir(void);
int SolicitarInfo_Buscar_Coincidencia (void);
int MsgIngresarDinero (void);
int MsgRetirarDinero (void);
int MostrarSaldo_MsgMenu (void);
int MostrarHistorial_MsgMenu (void);
int MsgCambiarPassword (void);
int MsgSalir_LimpiarLista (void);
int Msg_Menu (void);
int SumarDinero_Actualizar_Historial_MsgMenu (void);
int PedirCantidad (void);
int PedirPassword (void);
int VolverAPedirPassword (void);
int SesionFallida (void);
int MsgSaldoInsuficiente (void);
int MsgRetiroExitoso (void);
int MsgErrorCambioPassword (void);
int MsgPasswordCambiada (void);
int nul(void);


/*************** FUNCION PRINCIPAL ***************/
int main(int argc, char **argv)
{
  int actx, auxx, outcome;
  if(argc!=1 && argc!=2)
    {
      printf("Insertó parámetros de más, intente de nuevo.\n");
      exit(0);
    }
  else
    {
      if(argc==1)
	{
	  Creditos();
	  system("clear");
	  initialise();

	  while (1) {    /* loop infinito para la MFE */
	    getevent(); // leer el evento

	    for ((actx = state_table[state].start);(action_table[actx].event != event.etype) && (actx < state_table[state].end);actx++)
	      ;
	    outcome = (*(action_table[actx].action))();
	    if(action_table[actx].moreacts == -1)
	      state = action_table[actx].nextstate;
	    else {
	      auxx = action_table[actx].moreacts + outcome;
	      while (auxx != -1){
		outcome = (*(aux_table[auxx].action))();
		if (aux_table[auxx].moreacts == -1 ){
		  state = aux_table[auxx].nextstate;
		  auxx = -1;
		}
		else
		  auxx = aux_table[auxx].moreacts + outcome;

	      }
	    }
	  }
	}
      if(argc==2 && (strcmp(argv[1],"-c"))==0)
	{
	  CargarBase();
	  Imprimir();
	  do
	    {
	      printf("Bienvenido al modo de administrador\n");
	      printf("Por favor ingrese:\n");
	      printf("Usuario: ");
	      scanf (" %[^\n]", Usuario);
	      printf("\nContraseña: ");
	      scanf (" %[^\n]", Password);
	      printf("\n");
	    }while(Salir==0);
	}
      else
	{
	  printf("Opción inválida, intente de nuevo.\n");
	  printf("Modo Admin: $./practica3.c -c.\n");
	  exit(0);
	}
    }
}

void initialise(void)
{
  state = 0;
  printf("Bienvenido\n");
}


void getevent(void)
{
  char *ptmp;
  ptmp = &buf[2];

#ifdef DEBUG
  printf("wait event \n");
#endif
  __fpurge(stdin);
  gets(buf);
  switch (buf[0])
    {
    case 'I' :
      event.etype=ENTRADA_0;
      break;
    case 'i' :
      event.etype=ENTRADA_2;
      break;
    case 'R' :
      event.etype=ENTRADA_3;
      break;
    case 'C':
      event.etype=ENTRADA_4;
      break;
    case 'M':
      event.etype=ENTRADA_5;
      break;
    case 'P':
      event.etype=ENTRADA_6;
      break;
    case 'Q':
      event.etype=ENTRADA_7;
      break;
    case '!':
      event.etype=ENTRADA_9;
      break;
    case 'd':
      event.etype=ENTRADA_10;
      break;
    case '#':
      event.etype=ENTRADA_12;
      break;
    case 'D':
      event.etype=ENTRADA_13;
      break;
    case '$':
      event.etype=ENTRADA_15;
      break;
    case 'Z':
      event.etype=ENTRADA_16;
      break;
    case 'p':
      event.etype=ENTRADA_18;
      break;
    default:
      event.etype=-1;
      break;

    }//switch
}// getevent


/* FUNCIONES DE IMPLEMENTACION */

int Creditos(void)
{
  system("clear");
  printf("Desarrollado por:\n");
  printf("César Mauricio Arellano Velásquez\n");
  printf("Raúl González Portillo\n");
  printf("Allan Jair Escamilla Hernández\n\n");
  printf("Presione Enter para continuar...\n");
  __fpurge(stdin);
  getchar();
  system("clear");
  printf("Objetivo principal del programa:\n");
  printf("Este programa pretende simular un cajero automático convencional,\n");
  printf("a través del método de máquinas de estados.\n");
}

int CargarBase(void)
{
  FILE *Archivo;
  TipoLista *Nuevo,*temp;
  char User[100];
  Archivo = fopen("admin.txt","rt");
  if(Archivo==NULL)
    {
      printf("Los archivos requeridos no existen, el programa no puede continuar.\n");
      exit(0);
    }
  else
    {
      while(fscanf(Archivo," %[^\n]", User)==1)
	{
	  Nuevo = (TipoLista *)malloc(sizeof(TipoLista));
	  strcpy(Nuevo -> Usuario, User);
	  fscanf (Archivo, " %[^\n]", Nuevo -> Password);
	  Nuevo -> sig = NULL;
	  if (Inicio != NULL)
	    {
	      temp = Inicio;
	      while (temp -> sig != NULL)
		temp = temp -> sig;
	      temp -> sig = Nuevo;
	    }
	  else
	    {
	      Inicio = Nuevo;
	    }
	}
    }
}
 
 int Imprimir(void)
 {
   TipoLista *temp;
   temp=Inicio;
   while(temp!=NULL)
     {
       printf("%s\n", temp->Usuario);
       printf("%s\n", temp->Password);
       temp=temp->sig;
     }
 }

int SolicitarInfo_Buscar_Coincidencia (void)
{
  printf("En proceso\n");
}

int MsgIngresarDinero (void)
{
  printf("En proceso\n");
}

int MsgRetirarDinero (void)
{
  printf("En proceso\n");
}

int MostrarSaldo_MsgMenu (void)
{
  printf("En proceso\n");
}

int MostrarHistorial_MsgMenu (void)
{
  printf("En proceso\n");
}

int MsgCambiarPassword (void)
{
  printf("En proceso\n");
}

int MsgSalir_LimpiarLista (void)
{
  printf("En proceso\n");
}

int Msg_Menu (void)
{
  printf("En proceso\n");
}

int SumarDinero_Actualizar_Historial_MsgMenu (void)
{
  printf("En proceso\n");
}

int PedirCantidad (void)
{
  printf("En proceso\n");
}

int PedirPassword (void)
{
  printf("En proceso\n");
}

int VolverAPedirPassword (void)
{
  printf("En proceso\n");
}

int SesionFallida (void)
{
  printf("En proceso\n");
}
int MsgSaldoInsuficiente (void)
{
  printf("En proceso\n");
}
int MsgRetiroExitoso (void)
{
  printf("En proceso\n");
}

int MsgErrorCambioPassword (void)
{
  printf("En proceso\n");
}

int MsgPasswordCambiada (void)
{
  printf("En proceso\n");
}

int nul(void)
{
  printf("Opción inválida\n");
}
