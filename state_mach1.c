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
char Parametro[10];
int Opcion=0,Login=0;
TipoLista *Inicio=NULL;
char Usuario[100],Password[100];
long long int Saldo,Cuenta;

/*************** PROTOTIPOS DE FUNCION ***************/
void initialise(void);
void getevent(void);

int Creditos (void);
int CargarBase (void);
int Login_Cajero (void);
int Registro (void);
int Imprimir (void);
int GuardarUsuarios (void);
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
  system("clear");
  if(argc!=1 && argc!=2)
    {
      printf("Insertó parámetros de más, intente de nuevo.\n");
      exit(0);
    }
  else
    {
      if(argc==1)
	{
	  CargarBase();
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
	  strcpy(Parametro,argv[1]);
	  CargarBase();
	  do
	    {
	      	  system("clear");
		  printf("Bienvenido al módulo de administrador\n");
		  printf("Menú:\n");
		  printf("1.- Dar de alta cuentahabientes\n");
		  printf("2.- Salir y Guardar Cambios\n");
		  printf("Ingrese la opción que desea realizar\n ");
		  scanf(" %d", &Opcion);
		  system("clear");
		  switch(Opcion)
		    {
		    case 1:
		      Registro();
		      break;
		    case 2:
		      GuardarUsuarios();
		      printf("Se han guardado los datos correctamente\n");
		      printf("Saliendo del programa...\n");
		      Borrar_Lista();
		      exit(0);
		      break;
		    default:
		      printf("Opción Inválida\n");
		      break;
		    }
		  printf("Presione Enter para continuar...\n");
		  __fpurge(stdin);
		  getchar();		  
	    }while(Opcion!=2);
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
  Archivo = fopen("CuentaHabiente.txt","rt");
  if(Archivo==NULL && (strcmp(Parametro,"-c"))==0)
    {
      printf("Se ha detectado que es la primera ejecución del programa\n");
      printf("Presione Enter para crear los archivo necesarios...\n");
      __fpurge(stdin);
      getchar();
      Cuenta=2640812340;
      Registro();
      printf("Presione Enter para continuar...\n");
      __fpurge(stdin);
      getchar();
    }
  else
    {
      if(Archivo==NULL)
	{
	  printf("Se ha detectado que es la primera ejecución del programa,\ndebido a que no existen los archivos necesarios para funcionar.\n");
	  printf("Para continuar es necesario acceder al módulo de administrador.\n");
	  printf("Saliendo del programa...\n");
	  exit(0);
	}
      else
	{
	  while(fscanf(Archivo," %[^\n]", User)==1)
	    {
	      Nuevo = (TipoLista *)malloc(sizeof(TipoLista));
	      strcpy(Nuevo -> Usuario, User);
	      fscanf(Archivo, " %[^\n]", Nuevo -> Password);
	      fscanf(Archivo, " %lld", &Nuevo -> NumCuenta);
	      fscanf(Archivo, " %lld", &Nuevo -> Saldo);
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
	      Cuenta = Nuevo -> NumCuenta + 1;
	    }
	}
    }
}

int Login_Cajero(void)
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
  system("clear");
  TipoLista *Nuevo, *temp;
  temp=Inicio;
  Nuevo = (TipoLista *)malloc(sizeof(TipoLista));
  printf("Ingrese nombre del cuentahabiente\n");
  scanf(" %[^\n]",Nuevo->Usuario);
  printf("Ingrese contraseña del cuentahabiente\n");
  scanf(" %[^\n]",Nuevo->Password);
  Nuevo->Saldo=0;
  Nuevo->NumCuenta=Cuenta;
  printf("El número de cuenta generado es: %lld\n",Nuevo->NumCuenta); 
  Cuenta++;
  Nuevo->sig=NULL;
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


int Imprimir(void)
{
  TipoLista *temp;
  temp=Inicio;
  while(temp!=NULL)
    {
      printf("%s\n", temp->Usuario);
      printf("%s\n", temp->Password);
      printf("%lld\n", temp->NumCuenta);
      printf("%lld\n",temp->Saldo);
      temp=temp->sig;
    }
}

int GuardarUsuarios (void)
{
  TipoLista *temp;
  FILE *Archivo;
  temp=Inicio;
  Archivo = fopen("CuentaHabiente.txt","wt");
  while(temp!=NULL)
    {
      fprintf(Archivo,"%s\n",temp->Usuario);
      fprintf(Archivo,"%s\n",temp->Password);
      fprintf(Archivo,"%lld\n",temp->NumCuenta);
      fprintf(Archivo,"%lld\n",temp->Saldo);
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

/*system("clear");
	      printf("Bienvenido al modo de administrador\n");
	      printf("Por favor ingrese:\n");
	      printf("Usuario: ");
	      scanf (" %[^\n]", Usuario);
	      printf("Contraseña: ");
	      scanf (" %[^\n]", Password);
	      printf("Verificando...\n");
	      system("sleep 0.5");
	      Login_Admin();
  else
		{
		  system("clear");
		  printf("Usuario y/o contraseña incorrecta\n");
		  printf("Intente de nuevo.\n");
		  printf("Presione Enter para continuar...\n");
		  __fpurge(stdin);
		  getchar();	
		}
	      

*/
