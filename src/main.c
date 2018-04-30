/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "S32K148.h" /* include peripheral declarations S32K148 */
#include "clocks_and_modes.h"
#include "LPUART.h"

int16_t input = 0;

void PORT_init (void) {
    PCC->PCCn[PCC_PORTC_INDEX ]|=PCC_PCCn_CGC_MASK; /* Enable clock for PORTC */
    PORTC->PCR[6]|=PORT_PCR_MUX(2);           /* Port C6: MUX = ALT2,UART1 RX */
    PORTC->PCR[7]|=PORT_PCR_MUX(2);           /* Port C7: MUX = ALT2,UART1 TX */
}

void answer_matlab(uint16_t dato){
	LPUART_Send(LPUART1, (uint8_t) 'A');
	uint8_t a = (uint8_t) (dato & 0xff);
	uint8_t b = (uint8_t) (dato >> 8);
	LPUART_Send(LPUART1, a);
	LPUART_Send(LPUART1, b);
	LPUART_Send(LPUART1, 0);
}


int main(void)
{
    SOSC_init_8MHz();      /* Initialize system oscilator for 8 MHz xtal */
    SPLL_init_160MHz();    /* Initialize SPLL to 160 MHz with 8 MHz SOSC */
    NormalRUNmode_80MHz(); /* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */
	PORT_init();
	LPUART_Init(PCC_LPUART1_INDEX, LPUART1);

	for(;;){
//		input = ( (int16_t) LPUART_receive_uint8(LPUART1) - 127 ) * 2;
		input = LPUART_receive_uint8(LPUART1);

		answer_matlab((uint16_t)input);
	}

	return 0;
}
