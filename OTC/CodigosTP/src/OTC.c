/* Copyright 2021 - Gustavo F. Paredes Delaloye
 * Proyecto para OTC reformado de proyecto para RTOS1 y Protocolos de Comunicaciones Embebidos (CESE 2019)
 */

/*==================[inclusiones]============================================*/

#include "../../../OTC2/CodigosTP/inc/ciaaI2C.h"
#include "../../../OTC2/CodigosTP/inc/funciones.h"
#include "../../../OTC2/CodigosTP/inc/FreeRTOSConfig.h"
#include "../../../OTC2/CodigosTP/inc/sd_spi.h"   // <= own header (optional)


// sAPI header
#include "sapi.h"
#include "sapi_rtc.h"
#include "sapi_datatypes.h"
#include "sapi_board.h"

//Strings
#include "string.h"
#include "stdlib.h"


#define UART_PC        UART_USB
#define UART_BLUETOOTH UART_232

//*==================[definiciones y macros]==================================*/
//#define

/*==================[definiciones de datos internos]=========================*/


/*==================[definiciones de datos externos]=========================*/


/*==================[declaraciones de funciones internas]====================*/


/*==================[declaraciones de funciones externas]====================*/


/*==================[funcion principal]======================================*/

	//bool_t grabar = FALSE;

int main(void)
{

	// ---------- CONFIGURACIONES ------------------------------
	// Inicializar y configurar la plataforma
	boardConfig();

	// Inicializar UART_USB para conectar al monitor serie de la PC con CuteCom
	uartConfig( UART_USB, 115200 );
	printf ("UART_USB configurada en 115200 baudios.\r\n");

	// Inicializar UART_232 para conectar al modulo bluetooth
	uartConfig( UART_BLUETOOTH, 9600 );
	printf("UART_BLUETOOTH configurada en 9600 baudios.\r\n" );


	//uint8_t msjLinea[13] = {80,82,80,82,81};// Arreglo con la linea a grabar.
	uint8_t dataBluetooth = 0;
	uint8_t dataBluetooth_X = 84;// Precarga una T, Y y Z como dato para el switch case
	uint8_t dataBluetooth_Y = 85;// Asi comienza automaticamente el intercambio de datos
	uint8_t dataBluetooth_Z = 86;// entre la App y la EDUCIAA.

	// ---------- REPETIR POR SIEMPRE --------------------------

	while( TRUE ) {

		// Segun que tecla es presionada, envia el numero de la misma.

		if (!gpioRead( TEC1 ) == true){
			uartWriteByte( UART_BLUETOOTH, 48 );// Envia un 0 como respuesta y apaga el Server
			delay(400);//Retardo antirebote de 400 ms.
		}

		if (!gpioRead( TEC2 ) == true){
    		gpioWrite( LED1, ON );// Enciende el led 1
			uartWriteByte( UART_BLUETOOTH, 49 );// Envia un 1 como respuesta
			delay(400);//Retardo antirebote de 400 ms.
		}

		if (!gpioRead( TEC3 ) == true){
    		gpioWrite( LED2, ON );// Enciende el led 2
			uartWriteByte( UART_BLUETOOTH, 50 );// Envia un 2 como respuesta
			delay(400);//Retardo antirebote de 400 ms.
		}

		if (!gpioRead( TEC4 ) == true){
    		gpioWrite( LED3, ON );// Enciende el led 3
			uartWriteByte( UART_BLUETOOTH, 51 );// Envia un 3 como respuesta
			delay(400);//Retardo antirebote de 400 ms.
		}

		// Lee la UART del modulo Bluetooth

        if( uartReadByte( UART_BLUETOOTH, &dataBluetooth ) ) {

        // Switch segun el dato recibido desde Android.

		switch (dataBluetooth) {

      	  case '1':// Detecta que se envio un 1 por la UART
      		  gpioWrite( LED1, OFF );// Apaga el led 1
      		  //uartWriteByte( UART_BLUETOOTH, 52 );// Envia un 4 como respuesta
      	      break;

      	  case '2':// Detecta que se envio un 2 por la UART
      		  gpioWrite( LED2, OFF );// Apaga el led 2
      		  //uartWriteByte( UART_BLUETOOTH, 53 );// Envia un 5 como respuesta
      		  break;

      	  case '3':// Detecta que se envio un 3 por la UART
      		  gpioWrite( LED3, OFF );// Apaga el led 3
      		  //uartWriteByte( UART_BLUETOOTH, 54 );// Envia un 6 como respuesta
      	   	  break;

      	  case '4':// Detecta que se envio un 4 por la UART
      	  case '5':// Detecta que se envio un 5 por la UART
      	  case '6':// Detecta que se envio un 6 por la UART
      		  gpioWrite( LEDB, ON );// Enciende el led B
      		  //uartWriteByte( UART_BLUETOOTH, 55 );// Envia un 7 como respuesta
			break;

      	  case '7':// Detecta que se envio un 7 por la UART
      	  case '8':// Detecta que se envio un 8 por la UART
      	  case '9':// Detecta que se envio un 9 por la UART
      		  gpioWrite( LEDB, OFF );// Apaga el led B
      		  //uartWriteByte( UART_BLUETOOTH, 57 );// Envia un 9 como respuesta
      		  break;

      	  default:
      		  gpioWrite( LED1, OFF );// Apaga todos los leds
      		  gpioWrite( LED2, OFF );
      		  gpioWrite( LED3, OFF );
      		  gpioWrite( LEDB, OFF );
      		  //uartWriteByte( UART_BLUETOOTH, 48 );// Envia un 0 (cero) como respuesta
      	  }
        }
     }
}

/*==================[fin del archivo]========================================*/
