#include<lpc21xx.h>
void uart0_init(unsigned int baud)
{
	unsigned int pclk,result=0;
	if(VPBDIV==0x0)
		pclk=15000000;
	else if(VPBDIV==0x01)
		pclk=30000000;
	else if(VPBDIV==0x02)
		pclk=60000000;
	result=pclk/(16*baud);
	PINSEL0|=0x05;
	U0LCR=0x83;
	U0DLL=result&0xFF;
	U0DLM=(result>>8)&0xFF;
	U0LCR=0x03;
}

void uart0_txt(unsigned char data)
{
	U0THR=data;
	while(((U0LSR>>5)&1)==0);
U0THR=data;
}

#define RDR (U0LSR&1)
unsigned char uart0_rx()
{
	while(RDR==0);
	return U0RBR;
}

void uart0_txt_string(char *ptr)
{
	while(*ptr!=0)
	{
		uart0_txt(*ptr);
		ptr++;
	}
}

void uart0_int(int num)
{
	unsigned int a[10];
	int i=0;
	if(num==0)
	{
		uart0_txt('0');
	}
	if(num<0)
	{
		num=-num;
		uart0_txt('-');
	}
	while(num>0)
	{
		a[i]=num%10+48;
		num=num/10;
		i++;
	}
	for(i=i-1;i>=0;i--)
	{
	uart0_txt(a[i]);
	}
}

