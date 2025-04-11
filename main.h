#ifndef MAIN_H_
#define MAIN_H_

#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_uart.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>



#define led_1_ON PORT_WriteBit(MDR_PORTE, PORT_Pin_6, 1)
#define led_1_OFF PORT_WriteBit(MDR_PORTE, PORT_Pin_6, 0)

#define led_2_ON PORT_WriteBit(MDR_PORTE, PORT_Pin_7, 1)
#define led_2_OFF PORT_WriteBit(MDR_PORTE, PORT_Pin_7, 0)

#define dot 1000
#define dash 3000 //dash=dot*3
#define space 7000
#define pause 44000

void delay(uint32_t cycles);
void initClk(void);
void initPort(void);
void Blinker(char symbol);
void initUART(void);


char *code[] = {"....", ".-..", ".-..", "...", ".--", "---", " ", ".-.", ".-..", "-.."};
//hello world - /d,d,d,d/ /d,l,d,d/ /d,l,d,d / /d,d,d/ /d,l,l/ /l,l,l/ /d,l,d/ /d,l,d,d/ /l,d,d/

#endif /* MAIN_H_ */
