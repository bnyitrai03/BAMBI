#include "em_device.h"
#include "em_chip.h"
// C:\SiliconLabs\SimplicityStudio\v4\developer\sdks\gecko_sdk_suite\v2.7\platform\emlib\src

#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"

USART_InitAsync_TypeDef UART0_init = USART_INITASYNC_DEFAULT;


int main(void)
{
  /* Chip errata */
  CHIP_Init();

  // void CMU_ClockEnable(CMU_Clock_TypeDef clock, bool enable)

  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(cmuClock_UART0, true);

  // void GPIO_PinModeSet(GPIO_Port_TypeDef port, unsigned int pin, GPIO_Mode_TypeDef mode, unsigned int out)

  GPIO_PinModeSet(gpioPortF, 7, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortE, 0, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortE, 1, gpioModeInput, 0);

  UART0_init.enable = usartEnable;
  UART0_init.baudrate = 115200;
  UART0_init.refFreq = 0;
  UART0_init.oversampling = usartOVS16;
  UART0_init.databits = usartDatabits8;
  UART0_init.parity = usartNoParity;
  UART0_init.stopbits = usartStopbits1;

  //void USART_InitAsync(USART_TypeDef *usart, const USART_InitAsync_TypeDef *init)
  USART_InitAsync(UART0, &UART0_init);

  UART0-> ROUTE |= USART_ROUTE_LOCATION_LOC1; //efm32gg990f..-bõl usart, onnan kivalasztottuk, hogy az 1-es locationt
  UART0-> ROUTE |= (USART_ROUTE_RXPEN | USART_ROUTE_TXPEN); //használjuk, mert alapból a 0-ás aktív, ekkor a PE1 és PE0-on lesznek az UART Tx Rx lábai

  USART_Tx(UART0, '+');


  /* Infinite loop */
  while (1) {
  		USART_Tx(UART0, USART_Rx(UART0)+1);
  }
}
