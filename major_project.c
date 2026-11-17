#include<lpc21xx.h>
#include "header.h"
#define flame ((IOPIN0>>5)&1)
#define vibr ((IOPIN0>>6)&1)
#define LED 1<<8
extern  unsigned int flag;
int main()
	{
int pot,vout,tem,ldr;
IODIR0=LED;
IOSET0=LED;


adc_init();
uart0_init(9600);
config_vic();
timer0_init();

while(1){
if(flag)
{
if(flag==1)
{
vout=adc_read(2);
tem=(vout*3.3*100)/1023;
if(tem>35)
{
IOCLR0=LED;
}
else
{
	IOSET0=LED;
}
}
uart0_txt_string("\r\nTempearture reading: ");
uart0_int(tem);

uart0_txt_string("\r\nFlame: ");
if(flame==0)
{
uart0_txt_string("ON");
}
else
{
uart0_txt_string("OFF");
}

if(flag==2)
{
pot=adc_read(1);
uart0_txt_string("\r\nPOT reading: ");
}
uart0_int(pot);


if(flag==3)
{
ldr=adc_read(3);
ldr=(ldr*3.3*100)/1023;
}
uart0_txt_string("\r\n Light: ");
uart0_int(ldr);
uart0_txt_string("\r\n Vibrations: ");
if(vibr==0)
{
uart0_txt_string("ON");
}
else
{
uart0_txt_string("OFF");
}
}
}

}