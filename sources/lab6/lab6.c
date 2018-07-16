
#include <stdio.h>
#include <xil_io.h>
#include <sleep.h>
#include <xil_printf.h>
#include <xparameters.h>
#include "xuartps.h"
#include "fir.h"
#include "xfir_fir_io.h"

void fir_software (short *y, short x);

typedef short		Xint16;
typedef long		Xint32;

void filter_hw_accel_input(short * Sample_L_out, short Sample_L_in)
{

		xil_printf("input sample: %d\r\n",Sample_L_in);
		Xil_Out32(XPAR_FIR_LEFT_BASEADDR+XFIR_FIR_IO_ADDR_X_DATA, Sample_L_in); // send left channel sample
		Xil_Out32(XPAR_FIR_LEFT_BASEADDR+XFIR_FIR_IO_ADDR_AP_CTRL, 0x1); // pulse ap_start left channel
		Xil_Out32(XPAR_FIR_LEFT_BASEADDR+XFIR_FIR_IO_ADDR_AP_CTRL, 0x0);
		while(1){
			if(Xil_In32(XPAR_FIR_LEFT_BASEADDR+XFIR_FIR_IO_ADDR_Y_CTRL))
				break;
			else
				continue;
		}
		*Sample_L_out = Xil_In32(XPAR_FIR_LEFT_BASEADDR+XFIR_FIR_IO_ADDR_Y_DATA);
		xil_printf("output sample: %d\r\n",*Sample_L_out);
}

int main(void)
{
	short signal, output;

	int i;
	for (i=0;i<SAMPLES;i++) {
	  if(i==0)
		  signal = 0x8000;
	  else
		  signal = 0;
	  #ifdef SW_PROFILE
		  fir_software(&output,signal);
	  #else
		  filter_hw_accel_input(&output,signal);
	  #endif
	}
	return 0;
}
