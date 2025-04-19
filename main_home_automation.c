#include "header.h"
#define LED1 (1<<17)
#define LED2 (1<<18)

int main()
{
	u8 cmd;
	uart1_init(9600);
	IOSET0=IODIR0=LED1|LED2;
	while(1)
	{
		uart1_tx_string((s8*)"Menu\r\nA.LED1 ON\r\nB.LED1 OFF\r\nC.LED2 ON\r\nD.LED2 OFF\r\nE.LED1 & LED2 ON\r\nF.LED1 & LED2 OFF\r\nOption...\r\n");
		cmd=uart1_rx_char();
		uart1_tx_char(cmd);
		uart1_tx_string((s8*)"\r\n");
		switch(cmd)
		{
			case 'A':IOCLR0=LED1; break;
			case 'B':IOSET0=LED1; break;
			case 'C':IOCLR0=LED2; break;
			case 'D':IOSET0=LED2; break;
			case 'E':IOCLR0=LED1|LED2; break;
			case 'F':IOSET0=LED1|LED2; break;
			default: uart1_tx_string((s8*)"\r\nWrong Option\r\n");
		}
		uart1_tx_string((s8*)"\r\n");
	}
}

