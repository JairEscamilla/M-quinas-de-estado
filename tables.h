/************************************************************************
 *									*
 * Archivo:	tables.h						*
 * Descripcion: Tablas para la maquina de estados y funciones externas	*
 *		Aqui se definen todos las tablas que se utilizan	*
 *		en el programa						*
 *									*
 ************************************************************************/

/*************** ARCHIVOS DE INCLUSION ***************/
#include "local.h"
#include <stdio.h>


/*************** FUNCIONES EXTERNAS *********************
 * En esta seccion se declaran los encabezados de 	*
 * todas las funciones que se utilizan en las     	*
 * tablas del programa. Todas las funciones deben 	*
 * ser de tipo entero y no deben recibir parametros	*
 ********************************************************/
extern int SolicitarInfo_Buscar_Coincidencia (void);
extern int MsgIngresarDinero (void);
extern int MsgRetirarDinero (void);
extern int MostrarSaldo_MsgMenu (void);
extern int MostrarHistorial_MsgMenu (void);
extern int MsgCambiarPassword (void);
extern int MsgSalir_LimpiarLista (void);
extern int Msg_Menu (void);
extern int SumarDinero_Actualizar_Historial_MsgMenu (void);
extern int PedirCantidad (void);
extern int PedirPassword (void);
extern int VolverAPedirPassword (void);
extern int SesionFallida (void);
extern int MsgSaldoInsuficiente (void);
extern int MsgRetiroExitoso (void);
extern int MsgErrorCambioPassword (void);
extern int MsgPasswordCambiada (void);
extern int nul(void);
extern int nul(void);

/******************** TABLAS ********************
 * En esta seccion se declaran las tablas	*
 * que se van a usar en el programa		*
 ************************************************/

/*************** TABLA DE ACCION ***************/
ACTION_TAB action_table[]={
  /*etype     accion                         MasAcciones          sigEdo. */
  { ENTRADA_0,  SolicitarInfo_Buscar_Coincidencia,          0,	                -1},
  { Asterisco,  nul,	                                   -1,               Espera},
  { ENTRADA_2,  MsgIngresarDinero,	                   -1,     IngresandoDinero},
  { ENTRADA_3,  MsgRetirarDinero,	                   -1,      RetirandoDinero},
  { ENTRADA_4,  MostrarSaldo_MsgMenu,	                   -1,           Atendiendo},
  { ENTRADA_5,  MostrarHistorial_MsgMenu,	           -1,           Atendiendo},
  { ENTRADA_6,  MsgCambiarPassword,	                   -1,    CambiandoPassword},
  { ENTRADA_7,  MsgSalir_LimpiarLista,	                   -1,               Espera},
  { Asterisco,  nul,	                                   -1,           Atendiendo},
  { ENTRADA_9,  Msg_Menu,	                           -1,           Atendiendo},
  { ENTRADA_10,  SumarDinero_Actualizar_Historial_MsgMenu, -1,           Atendiendo},
  { Asterisco,  nul,	                                   -1,     IngresandoDinero},
  { ENTRADA_12,  Msg_Menu,	                           -1,           Atendiendo},
  { ENTRADA_13,  PedirCantidad,	                            0,                   -1},
  { Asterisco,  nul,	                                   -1,      RetirandoDinero},
  { ENTRADA_15,  Msg_Menu,	                           -1,           Atendiendo},
  { ENTRADA_16,  PedirPassword,	                           -1,  ComprobandoPassword},
  { Asterisco,  nul,	                                   -1,    CambiandoPassword},
  { ENTRADA_18,  VolverAPedirPassword,	                    0,                   -1},
  { Asterisco,  nul,	                                   -1,  ComprobandoPassword},


};

/*************** TABLA AUXILIAR ***************/  //No borrar aunque no se utilice.
AUX_TAB aux_table[]={
  /*    accion       bandera           sigEdo */
  { SesionFallida,          -1,          Espera},
  { Msg_Menu,	            -1,      Atendiendo},
  { MsgSaldoInsuficiente,   -1,      Atendiendo},
  { MsgRetiroExitoso,	    -1,      Atendiendo},
  { MsgErrorCambioPassword, -1,      Atendiendo},
  { MsgPasswordCambiada,    -1,      Atendiendo},
};
//Coment

/*************** TABLA DE ESTADOS ***************/
STATE_TAB state_table[]={
  /*estado      inicio   fin */
  {Espera,               0,      1},
  {Atendiendo,           2,      8},
  {IngresandoDinero,     9,     11},
  {RetirandoDinero,      12,    14},
  {CambiandoPassword,    15,    17},
  {ComprobandoPassword,  18,    19},
};
