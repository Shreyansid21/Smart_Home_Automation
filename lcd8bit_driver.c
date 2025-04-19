#include "header.h"
#define RS (1<<8)					//P0.8
#define RW (1<<9)					//P0.9
#define EN (1<<10)					//P0.10
#define LCD8 0x000007FF;	          		//P0.0 to P0.7

void lcd_data(u8 data)
{
	IOCLR0|=LCD8;
	IOSET0=data;
	IOSET0=(1<<8);
	IOCLR0=(1<<9);
	IOSET0=(1<<10);
		delay_ms(2);
	IOCLR0=(1<<10);
}

void lcd_cmd(u8 cmd)
{
	IOCLR0|=LCD8;
	IOSET0=cmd;
	IOCLR0=(1<<8);
	IOCLR0=(1<<9);
	IOSET0=(1<<10);
		delay_ms(2);
	IOCLR0=(1<<10);
}

void lcd_init(void)
{
	IODIR0|=LCD8;
	lcd_cmd(0x38);
	lcd_cmd(0x0F);
	lcd_cmd(0x01);
}

void lcd_string(s8 *ptr)
{
	while(*ptr!=0)
	{
		lcd_data(*ptr);
		ptr++;
		delay_ms(2);
	}
}

void lcd_integer(s32 num)
{
	s32 a[16],i=0;
	if(num==0)
		lcd_data('0');
	if(num<0)
	{
		lcd_data('-');
		num=-num;
	}
	while(num>0)
	{
		a[i]=num%10;
		num=num/10;
		i++;
	}
	for(--i;i>=0;i--)
	{
		lcd_data(a[i]+48);
	}
}

void lcd_float(f32 f,s32 ndp)
{
	s32 i,j;
	if(f<0.0)
	{
		lcd_data('-');
		f=-f;
	}
	i=f;
	lcd_integer(i);
	lcd_data('.');
	for(j=0;j<ndp;j++)
	{
		f=(f-i)*10;
		i=f;
		lcd_data(i+48);
	}
}

void lcd_bin(u16 n)
{
	s8 bit=15;
	while(bit>=0)
	{
	lcd_data(((n>>bit)&1)+48);
	bit--;
	}
}

void lcd_hex(u32 n)
{
	s32 i=0,nibble;
	u8 a[8];
	lcd_string((s8*)"0x");
	if(n==0)
		lcd_data('0');
	else
	{
		while(n)
		{
		nibble=n%16;
		nibble=(nibble>9)?((nibble-10)+'A'):(nibble+48);
		a[i++]=nibble;
		n/=16;
		}
		for(--i;i>=0;i--)
		{
		lcd_data(a[i]);
		}
	}
}

void lcd_oct(u32 n)
{
	u8 a[15];
	s32 i=0,x;
	if(n==0)
		lcd_data('0');
	else
	{
		while(n)
		{
		x=n%8;
		a[i++]=x+48;
		n/=8;
		}
		for(--i;i>=0;i--)
		lcd_data(a[i]);
	}
}

u8 a[]={0,14,10,10,31,27,31,0}; 
u8 b[]={14,10,2,2,31,27,31,1};
void lcd_cgram_init(void)
{
	s32 i;
	lcd_cmd(0x40);
	for(i=0;i<=7;i++)
	{
		lcd_data(a[i]);
	}
	lcd_cmd(0x48);
	for(i=0;i<=7;i++)
	{
		lcd_data(b[i]);
	}
}



