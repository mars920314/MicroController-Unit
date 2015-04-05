#include<reg51.h>

sbit x34=P3^4;		
sbit x35=P3^5;		
sbit x36=P3^6;
sbit x37=P3^7;
sbit x20=P2^0;
sbit x21=P2^1;

#define uint unsigned int
#define uchar unsigned char
#define V_TH0 0xff
#define V_TL0 0xf6
#define V_TMOD 0x01

sbit IN1=P2^0;
sbit IN2=P2^1;
sbit IN3=P2^2;
sbit IN4=P2^3;
sbit ENA=P2^4;
sbit ENB=P2^5;
uchar ZKB;
uchar click=0;
uchar temp1,temp2,flag=0;

void delay(unsigned long int t)
{
unsigned char i,j;
for(i=25;i>0;i--)
for(j=50;j>0;j--)
for(;t>0;t--);
}

void yaokong(void)
{
        if((temp1>0x70&&temp1<0x80)&&(temp2>0x70&&temp2<0x80))
        {     
            IN1=1;
			IN2=1;
			IN3=1;
			IN4=1;
        }

     if(temp1<0x71)
     {
            IN1=1;
			IN2=0;
			IN3=1;
			IN4=0;
     }
     if(temp1>0x81)
     {
            IN1=0;
			IN2=1;
			IN3=0;
			IN4=1;
     }

     if(temp2<0x71)
     {
            IN1=1;
			IN2=0;
			IN3=0;
			IN4=1;
     }
     if(temp2>0x81)
     {
            IN1=0;
			IN2=1;
			IN3=1;
			IN4=0;
     }
}

void init_sys()
{
    TMOD=V_TMOD;
    TH0=V_TH0;
    TL0=V_TL0;
    TR0=1;
    ET0=1;
    EA=1;
}

/*void time0() interrupt 1
{
     TR0=0;
     TH0=V_TH0;
     TL0=V_TL0;
     click++;
	 if(click>99)
	   click=0;
     if(click<ZKB)
	 {
       ENA=1;
	   ENB=1;
	 }
     else
 	 {
       ENA=0; 
 	   ENB=0;
	 }
	 TR0=1;
}
*/
void adread(unsigned char cho)
{
	if(cho==1)
	{
		x35=0;
		x34=1;
	}
	else if(cho==0)
	{
		x35=1;
		x34=0;
	}
	x36=1;
	x36=0;

	
	x37=1;
	delay(1);
	x37=0;
	delay(1);
	x37=1;

}
	
void main()
{
	init_sys(); 
	while(1)
	{
		adread(1);
		temp1=P1;
		P1=temp1;
		x20=0;
		x21=1;
		x21=0;
		x21=1;
		adread(0);
		temp2=P0;
		ZKB=100*(temp1/255);
//		yaokong();
	}
}
