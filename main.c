/**************
*							*
*			Aboba		*
*							*
***************/

#include "main.h"

void delay(uint32_t cycles)
{
	for (uint32_t i = 0; i < cycles; i++);
}

void initClk()
{
	RST_CLK_DeInit();
	
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);   
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3); 
	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul2); 
	
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTE, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_UART1, ENABLE);
}

void initUART()
{
	
	UART_DeInit(MDR_UART1);
	
	UART_InitTypeDef uart_init; 
	UART_StructInit(&uart_init); 
	
  UART_BRGInit(MDR_UART1, UART_HCLKdiv2);
  
	uart_init.UART_BaudRate            = 9600;
  uart_init.UART_WordLength          = UART_WordLength8b;
  uart_init.UART_StopBits            = UART_StopBits1;
  uart_init.UART_Parity              = UART_Parity_No;
  uart_init.UART_FIFOMode            = UART_FIFO_OFF;

  UART_Init(MDR_UART1, &uart_init);

  UART_Cmd(MDR_UART1, ENABLE);
	
}

void initPort()
{
	
	PORT_DeInit(MDR_PORTE);
	PORT_DeInit(MDR_PORTB);
	
	PORT_InitTypeDef port_init; 
	PORT_StructInit(&port_init); 
	
	port_init.PORT_FUNC = PORT_FUNC_PORT;
	port_init.PORT_MODE = PORT_MODE_DIGITAL;
	port_init.PORT_OE = PORT_OE_OUT;
	port_init.PORT_SPEED = PORT_SPEED_MAXFAST;
	port_init.PORT_Pin = (PORT_Pin_6 | PORT_Pin_7); 
	PORT_Init(MDR_PORTE,&port_init);
	
	port_init.PORT_Pin   = PORT_Pin_5;
  port_init.PORT_OE    = PORT_OE_OUT;
  port_init.PORT_FUNC  = PORT_FUNC_ALTER;
  port_init.PORT_MODE  = PORT_MODE_DIGITAL;
  port_init.PORT_SPEED = PORT_SPEED_MAXFAST;
  PORT_Init(MDR_PORTB, &port_init);
	
	port_init.PORT_Pin   = PORT_Pin_6;
  port_init.PORT_OE    = PORT_OE_IN;
  port_init.PORT_FUNC  = PORT_FUNC_ALTER;
  port_init.PORT_MODE  = PORT_MODE_DIGITAL;
  port_init.PORT_SPEED = PORT_SPEED_MAXFAST;
  PORT_Init(MDR_PORTB, &port_init);
}

void Blinker(char symbol)
{
	
	if (symbol == '.')
	{
		led_1_ON;
		delay(dot);
		led_1_OFF;
		delay(dot);
	}
	else if (symbol == '-')
	{
		led_1_ON;
		delay(dash);
		led_1_OFF;
		delay(dot);
	}
	else if (symbol == ' ')
	{
		led_1_OFF;
		delay(space);
	}
}

int main()
{
	initClk();
	initPort();
	initUART();
	
	while(1)
	{
		for (int i = 0; code[i] != NULL; i++)
		{
			char* lit = code[i];
			while(*lit)
			{
				Blinker(*lit++);
				while(UART_GetFlagStatus(MDR_UART1, UART_FLAG_TXFE) != SET) {}
        UART_SendData(MDR_UART1, (uint8_t)*lit++);
			}
			delay(dash);
		}
		delay(pause);
	}
}
