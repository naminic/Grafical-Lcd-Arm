#include <board.h>
#include <utility/trace.h>
#include <stdio.h>
#include "dbgu/dbgu.h"
#include "pit/pit.h"
#include "aic/aic.h"
#include "glcd.h"
#include "adc/adc.h"

#define BOARD_ADC_FREQ 5000000
#define ADC_VREF       3300  // 3.3 * 1000


//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------
volatile unsigned int timestamp = 0;
static volatile unsigned char conversionDone;
static const Pin pinsADC[] = {PINS_ADC};
static const char logo[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xE0,0xE0,0xE0,0xC0,0xE0,0xC0,0xC0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0x07,0x0F,0x1F,0x1F,0x3E,0x3E,0x7C,0xFC,0xF8,0xF8,0xF0,0xE0,0xE0,0xC0,0xC0,0x80,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x01,0xE1,0xF1,0xF1,0xF9,0xF9,0xF9,0xF9,0xF9,0xF9,0xF9,0xF9,0xF1,0xF3,0x43,0x07,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x08,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x01,0x01,0x03,0x03,0x07,0x0F,0x0F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00,0x00,0x00,0x01,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0x01,0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x07,0x07,0x0F,0x0F,0x1F,0x1F,0x3F,0x3D,0x7D,0x79,0xF9,0xF1,0xF1,0xF1,0xE1,0xC1,0xC1,0xC1,0x81,0x81,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,0xF0,0xF6,0x0E,0x0F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x0F,0xE6,0xF0,0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xF0,0xF0,0xF0,0xF0,0xF0,0x20,0x00,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0x70,0x70,0x70,0x70,0x70,0x70,0xF0,0xF0,0xF0,0xE0,0xE0,0xE0,0xC0,0x80,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x0E,0x0F,0x1F,0x1F,0x1F,0x1F,0x1F,0x0F,0xEF,0xF6,0xF0,0xF0,0xF0,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x71,0x71,0x73,0x73,0x73,0x77,0x77,0x7F,0x7F,0x7F,0x7E,0x7E,0x7C,0x7C,0x78,0x78,0x70,0x70,0x70,0x70,0x78,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x78,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x78,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x71,0x70,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x78,0x79,0x7F,0x3F,0x3F,0x1F,0x0F,0x06,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x78,0x3F,0x3F,0x3F,0x1F,0x1F,0x07,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x1C,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x1C,0x1C,0x3C,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3C,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x1C,0x1C,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x1C,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------


static float ConvHex2mV( unsigned int valueToConvert )
{
    return( (ADC_VREF * valueToConvert)/0x3FF);
}
void pitIntrupt()
{
    unsigned int status;
    // Read the PIT status register
    status = PIT_GetStatus() & AT91C_PITC_PITS;
    if (status != 0) 
    {
        // Read the PIVR to acknowledge interrupt and get number of ticks
        timestamp += (PIT_GetPIVR() >> 20);
    }
}


void delay_ms(unsigned long delay)
{
    volatile unsigned int start = timestamp;
    unsigned int elapsed;
    do {
        elapsed = timestamp;
        elapsed -= start;
    }
    while (elapsed < delay);
}



int main(void)
{
  char s[80];
	float temp;
	// DBGU configuration
  TRACE_CONFIGURE(DBGU_STANDARD, 9600, BOARD_MCK);
  printf("GLCD By Naminic Group");
    
	//Pit and AIC init
	PIT_Init(1000,BOARD_MCK/1000000);
  AIC_DisableIT(AT91C_ID_SYS);
  AIC_ConfigureIT(AT91C_ID_SYS, AT91C_AIC_PRIOR_LOWEST, pitIntrupt);
  AIC_EnableIT(AT91C_ID_SYS);
  PIT_EnableIT();
  PIT_Enable();
	
		// ADC init
	PIO_Configure(pinsADC, PIO_LISTSIZE(pinsADC));
	ADC_Initialize( AT91C_BASE_ADC,
                    AT91C_ID_ADC,
                    AT91C_ADC_TRGEN_DIS,
                    0,
                    AT91C_ADC_SLEEP_NORMAL_MODE,
                    AT91C_ADC_LOWRES_10_BIT,
                    BOARD_MCK,
                    BOARD_ADC_FREQ,
                    10,
                    1200);
    
	 ADC_EnableChannel(AT91C_BASE_ADC, 7);
	 AIC_EnableIT(AT91C_ID_ADC);	
    
	//GLCd init
	glcd_init();
	
		//load Bit map
	GLCD_ClearScreen();
	GLCD_GoTo(0,0);
	GLCD_Bitmap(logo,0,0,128,64);
	GLCD_WriteString_farsi("����  �����  �������",0);
	delay_ms(3000);
	GLCD_ClearScreen();
	GLCD_GoTo(0,0);
	GLCD_Bitmap(logo,0,0,128,64);
    



   
    // Infinite loop
    while (1) 
    {

        ADC_StartConversion(AT91C_BASE_ADC);
        delay_ms(10);			  
		temp =  ConvHex2mV(ADC_GetConvertedData(AT91C_BASE_ADC, 7)) / 10;
		sprintf(s,"Temp = %f C",temp);
		GLCD_GoTo(0,0);
		GLCD_WriteString(s);
		GLCD_GoTo(0,7);
		temp = temp * 9 / 5 + 32 ;
		sprintf(s,"Temp = %f F",temp);
		GLCD_WriteString(s);
		delay_ms(200);
    }
}