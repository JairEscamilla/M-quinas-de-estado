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
int Opcion=0,Login=0;
TipoLista *Inicio=NULL;
char Usuario[100],Password[100];

/*************** PROTOTIPOS DE FUNCION ***************/
void initialise(void);
void getevent(void);

int Creditos(void);
int CargarBase(void);
int Login_Admin (void);
int Registro (void);
int Imprimir(void);
int SolicitarInfo_BuscarCoincidencia_SesionIniciada (void);
int MsgIngresarDinero (void);
int MsgRetirarDinero (void);
int MostrarSaldo_MsgMenu (void);
int MostrarHistorial_MsgMenu (void);
int MsgCambiarPassword (void);
int MsgSalir_LimpiarLista (void);
int MsgMenu (void);
int SumarDinero_ActualizarHistorial_MsgMenu (void);
int PedirCantidad_SaldoSuficiente (void);
int PedirPassword (void);
int VolverAPedirPassword_Coinciden (void);
int SesionFallida (void);
int MsgSaldoInsuficiente_MsgMenu (void);
int MsgRetiroExitoso_RestarSaldo_ActualizarHistorial_MsgMenu (void);
int MsgErrorCambioPassword_MsgMenu (void);
int MsgPasswordCambiada_ActualizarPassword_MsgMenu (void);
int Borrar_Lista(void);
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
	  //Imprimir();
	  do
	    {
	      system("clear");
	      printf("Bienvenido al modo de administrador\n");
	      printf("Por favor ingrese:\n");
	      printf("Usuario: ");
	      scanf (" %[^\n]", Usuario);
	      printf("Contraseña: ");
	      scanf (" %[^\n]", Password);
	      printf("Verificando...\n");
	      system("sleep 0.5");
	      Login_Admin();
	      if(Login==1)
		{
		  system("clear");
		  printf("Bienvenido al módulo de administrador\n");
		  printf("Menú:\n");
		  printf("1.- Dar de alta cuentahabientes\n");
		  printf("2.- Salir\n");
		  printf("Ingrese la opción que desea realizar\n ");	     
		  scanf(" %d", &Opcion);
		  system("clear");
		  switch(Opcion)
		    {
		    case 1:
		      printf("Ingrese nombre del cuentahabiente\n");
		      scanf(" %[^\n]",Usuario);
		      printf("Ingrese contraseña del cuentahabiente");
		      scanf(" %[^\n]",Password);
		      Registro();
		      break;
		    case 2:
		      printf("Saliendo del programa\n");
		      Borrar_Lista();
		      break;
		    default:
		      printf("Opción Inválida\n");
		      break;
		    }
		  printf("Presione Enter para continuar...\n");
		  __fpurge(stdin);
		  getchar();		  
		}
	      else
		{
		  system("clear");
		  printf("Usuario y/o contraseña incorrecta\n");
		  printf("Intente de nuevo.\n");
		  printf("Presione Enter para continuar...\n");
		  __fpurge(stdin);
		  getchar();	
		}
	      
	    }while(Opcion==0);
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
      event.etype=ENTRADA_I;
      break;
    case 'i' :
      event.etype=ENTRADA_i;
      break;
    case 'R' :
      event.etype=ENTRADA_R;
      break;
    case 'C':
      event.etype=ENTRADA_C;
      break;
    case 'M':
      event.etype=ENTRADA_M;
      break;
    case 'P':
      event.etype=ENTRADA_P;
      break;
    case 'Q':
      event.etype=ENTRADA_Q;
      break;
    case '!':
      event.etype=ENTRADA_Admiracion;
      break;
    case 'd':
      event.etype=ENTRADA_d;
      break;
    case '#':
      event.etype=ENTRADA_Gato;
      break;
    case 'D':
      event.etype=ENTRADA_D;
      break;
    case '$':
      event.etype=ENTRADA_Dinero;
      break;
    case 'Z':
      event.etype=ENTRADA_Z;
      break;
    case 'p':
      event.etype=ENTRADA_p;
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

int Login_Admin(void)
{
  TipoLista *temp;
  temp=Inicio;
  while(temp != NULL)
    {
      if(strcmp(Usuario,temp->Usuario)==0 && strcmp(Password,temp->Password)==0)
	Login=1;
      temp = temp-> sig;
    }
}

int Registro (void)
{
  printf("Generar cuenta:\n");
  
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

int SolicitarInfo_BuscarCoincidencia_SesionIniciada (void)
{
}

int MsgIngresarDinero (void)
{
}

int MsgRetirarDinero (void)
{
}

int MostrarSaldo_MsgMenu (void)
{
}

int MostrarHistorial_MsgMenu (void)
{
}

int MsgCambiarPassword (void)
{
}

int MsgSalir_LimpiarLista (void)
{
}

int MsgMenu (void)
{
}

int SumarDinero_ActualizarHistorial_MsgMenu (void)
{
}

int PedirCantidad_SaldoSuficiente (void)
{
}

int PedirPassword (void)
{
}

int VolverAPedirPassword_Coinciden (void)
{
}

int SesionFallida (void)
{
}

int MsgSaldoInsuficiente_MsgMenu (void)
{
}

int MsgRetiroExitoso_RestarSaldo_ActualizarHistorial_MsgMenu (void)
{
}

int MsgErrorCambioPassword_MsgMenu (void)
{
}

int MsgPasswordCambiada_ActualizarPassword_MsgMenu (void)
{
}
 
int Borrar_Lista(void)
{
  TipoLista *temp;
  temp=Inicio;
  while(temp!=NULL)
    {
      Inicio=Inicio->sig;
      free(temp);
      temp=Inicio;
    }
}
 
int nul(void)
{
}
