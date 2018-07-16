#include "xparameters.h"
#include "xgpio.h"
#ifdef MULTIBOOT
#include "xdevcfg.h"
#endif
//====================================================
int main (void) 
{
	XGpio leds;
	int j=0;
	int i;
	xil_printf("-- Start of the Program --\r\n");
	XGpio_Initialize(&leds, XPAR_LEDS_DEVICE_ID);
	XGpio_SetDataDirection(&leds, 1, 0);				// output
    for(j=0; j<16; j++) {
        XGpio_DiscreteWrite(&leds, 1, j);
        for (i=0; i<999999; i++);
    }
    xil_printf("End of the program\r\n");
#ifdef MULTIBOOT
	  print("Loading master image\r\n");
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
		// Generate soft reset
		Xil_Out32(PS_RST_CTRL_REG, PS_RST_MASK);
#endif
	return 0;
}


