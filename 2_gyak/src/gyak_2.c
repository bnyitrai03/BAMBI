//#include "em_device.h"
//#include "em_chip.h"

// CLK:
// CMU_CMD.HFCLKSEL (CMU_CMD - ben KFCLKSEL bit)
// CMU_CTRL.HFCLKDIV ( CMU_CTRL - ben HFCLKDIV bit)
// CMU_HFPERCLKDIV.HFPERCLKEN
// CMU_HFPERCLKDIV.HFPERCLKDIV
// CMU_HFPERCLKEN0.GPIO
//17. oldalrol CMU és GPIO blokk kell most nekünk
//volatile: fordito nem fogja optimalizálni

//GPIO PE CTR 0x090 offset
//GPIO PE MODEl 0x094 offset
// GPIO_PE_DOUT 0x09C offset

#define  CMU_BASE_ADDR (0x400C8000) // Clock Management Unit báziscíme
#define GPIO_BASE_ADDR (0x40006000) // General Purpose Input Output báziscíme

#define CMU_HFPERCLKEN0 (*(volatile long unsigned int *) (CMU_BASE_ADDR+0x044))
#define GPIO_PE_MODEL (*(volatile long unsigned int *) (GPIO_BASE_ADDR+0x094))
#define GPIO_PE_DOUT (*(volatile long unsigned int *) (GPIO_BASE_ADDR+0x09C))

int main(void)
{
  /* Chip errata */
  //CHIP_Init();

	CMU_HFPERCLKEN0 |= 1 << 13; // GPIO órajel engedélyezése

	GPIO_PE_MODEL |= 4 << 8; //port E pin 2 PUSHPULL kimenet:
	GPIO_PE_MODEL |= 4 << 12; //port E pin 3 PUSHPULL kimenet:

	GPIO_PE_DOUT |= 1 << 2; // LED 0 bekapcsol
	//GPIO_PE_DOUT |= 1 << 3; //LED 1 bekapcsol



  /* Infinite loop */
  while (1) {
  }
}
