#include "xparameters.h"
#include "xgpio.h"
#ifdef MULTIBOOT
#include "xdevcfg.h"
#endif

//====================================================
int main (void) 
{

      XGpio sws, leds, btns;
	  int i, sws_check, btns_check;
	
	  xil_printf("-- Start of the Program --\r\n");

	  // AXI GPIO switches Initialization
	  XGpio_Initialize(&sws, XPAR_SWITCHES_DEVICE_ID);
	  XGpio_SetDataDirection(&sws, 1, 0xffffffff);		// input
	  // AXI GPIO leds Initialization
	  XGpio_Initialize(&leds, XPAR_LEDS_DEVICE_ID);
	  XGpio_SetDataDirection(&leds, 1, 0);				// output
	  // AXI GPIO buttons Initialization
	  XGpio_Initialize(&btns, XPAR_BUTTONS_DEVICE_ID);
	  XGpio_SetDataDirection(&btns, 1, 0xffffffff);		// input

	  xil_printf("-- Press any of BTN0-BTN3 to see corresponding output on LEDs --\r\n");
	  xil_printf("-- Set slide switches to 0x03 to exit the program --\r\n");

	  while (1)
	  {
		  btns_check = XGpio_DiscreteRead(&btns, 1);
		  XGpio_DiscreteWrite(&leds, 1, btns_check);
	      sws_check = XGpio_DiscreteRead(&sws,1);
          if((sws_check & 0x03)==0x03)
        	  break;
		  for (i=0; i<9999999; i++); // delay loop
	   }
	  xil_printf("-- End of Program --\r\n");
#ifdef MULTIBOOT
	  // Driver Instantiations
	  XDcfg XDcfg_0;
	  u32 MultiBootReg = 0;
	  #define PS_RST_CTRL_REG	(XPS_SYS_CTRL_BASEADDR + 0x200)
	  #define PS_RST_MASK	0x1	/* PS software reset */
	  #define SLCR_UNLOCK_OFFSET 0x08

	  // Initialize Device Configuration Interface
	  XDcfg_Config *Config = XDcfg_LookupConfig(XPAR_XDCFG_0_DEVICE_ID);
	  XDcfg_CfgInitialize(&XDcfg_0, Config, Config->BaseAddr);

	  MultiBootReg = 0; // Once done, boot the master image stored at 0xfc00_0000
	  Xil_Out32(0xF8000000 + SLCR_UNLOCK_OFFSET, 0xDF0DDF0D); // unlock SLCR
	  XDcfg_WriteReg(XDcfg_0.Config.BaseAddr, XDCFG_MULTIBOOT_ADDR_OFFSET, MultiBootReg); // write to multiboot reg
	  // synchronize
		__asm__(
			"dsb\n\t"
			"isb"
		);
      Xil_Out32(PS_RST_CTRL_REG, PS_RST_MASK);
#endif
	  return 0;
}
 
