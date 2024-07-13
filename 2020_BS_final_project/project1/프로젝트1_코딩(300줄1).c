#include "DSP28x_Project.h"                  // Device Headerfile and Examples Include File

interrupt void Xint3_isr(void);
interrupt void Xint4_isr(void);
interrupt void Xint5_isr(void);
interrupt void Xint6_isr(void);

void Printmode_1(void);
void Printmode_2(void);
void Printmode_3(void);
void Printmode_4(void);
void Printmode_5(void);
void Printmode_6(void);
void Printmode_stp(void);

Uint16 Loop_cnt;
Uint16 SW1_cnt, SW2_cnt, SW3_cnt, SW4_cnt;
Uint16 mode, state;
Uint16 i, j, num;
float32 usec_delay, usec_delay_1;
void main(void)
{

   DINT;

   InitSysCtrl();

   InitPieCtrl();
   IER = 0x0000;
   IFR = 0x0000;
   InitPieVectTable();


   EALLOW;
   PieVectTable.XINT3 = &Xint3_isr;
   PieVectTable.XINT4 = &Xint4_isr;
   PieVectTable.XINT5 = &Xint5_isr;
   PieVectTable.XINT6 = &Xint6_isr;
   EDIS;

   EALLOW;
   GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;      // 핀 기능선택: GPIO44
   GpioCtrlRegs.GPBMUX1.bit.GPIO45 = 0;      // 핀 기능선택: GPIO45
   GpioCtrlRegs.GPBMUX1.bit.GPIO46 = 0;      // 핀 기능선택: GPIO46
   GpioCtrlRegs.GPBMUX1.bit.GPIO47 = 0;      // 핀 기능선택: GPIO47
   GpioCtrlRegs.GPBDIR.bit.GPIO44 = 0;         // GPIO44 입출력 선택: Input
   GpioCtrlRegs.GPBDIR.bit.GPIO45 = 0;         // GPIO45 입출력 선택: Input
   GpioCtrlRegs.GPBDIR.bit.GPIO46 = 0;         // GPIO46 입출력 선택: Input
   GpioCtrlRegs.GPBDIR.bit.GPIO47 = 0;         // GPIO47 입출력 선택: Input
   EDIS;

   EALLOW;
   GpioCtrlRegs.GPCMUX1.all = 0x00000000;      // GPIO64-GPIO79, GPIO 기능으로 설정
   GpioCtrlRegs.GPCDIR.all = 0x0000FFFF;       // GPI064-GPIO79, 출력으로 설정
   EDIS;

   EALLOW;
   GpioCtrlRegs.GPBCTRL.bit.QUALPRD1 = 0xFF;   // (GPIO40~GPIO47) Qual period 설정
   GpioCtrlRegs.GPBQSEL1.bit.GPIO44 = 2;      // Qualification using 6 samples
   GpioCtrlRegs.GPBQSEL1.bit.GPIO45 = 2;      // Qualification using 6 samples
   GpioCtrlRegs.GPBQSEL1.bit.GPIO46 = 2;      // Qualification using 6 samples
   GpioCtrlRegs.GPBQSEL1.bit.GPIO47 = 2;      // Qualification using 6 samples
   EDIS;

   EALLOW;
   GpioIntRegs.GPIOXINT3SEL.bit.GPIOSEL = 47;   // 외부 인터럽트 XINT3로 사용할 핀 선택: GPIO47
   GpioIntRegs.GPIOXINT4SEL.bit.GPIOSEL = 46;   // 외부 인터럽트 XINT4로 사용할 핀 선택: GPIO46
   GpioIntRegs.GPIOXINT5SEL.bit.GPIOSEL = 45;   // 외부 인터럽트 XINT5로 사용할 핀 선택: GPIO45
   GpioIntRegs.GPIOXINT6SEL.bit.GPIOSEL = 44;   // 외부 인터럽트 XINT6로 사용할 핀 선택: GPIO44
   EDIS;

   XIntruptRegs.XINT3CR.bit.POLARITY = 2;      // XINT3 인터럽트 발생 조건 설정: 입력 신호의 하강 엣지
   XIntruptRegs.XINT4CR.bit.POLARITY = 2;      // XINT4 인터럽트 발생 조건 설정: 입력 신호의 하강 엣지
   XIntruptRegs.XINT5CR.bit.POLARITY = 2;      // XINT5 인터럽트 발생 조건 설정: 입력 신호의 하강 엣지
   XIntruptRegs.XINT6CR.bit.POLARITY = 2;      // XINT6 인터럽트 발생 조건 설정: 입력 신호의 하강 엣지

   XIntruptRegs.XINT3CR.bit.ENABLE = 1;        // XINT3 인터럽트 : Enable
   XIntruptRegs.XINT4CR.bit.ENABLE = 1;        // XINT4 인터럽트 : Enable
   XIntruptRegs.XINT5CR.bit.ENABLE = 1;        // XINT5 인터럽트 : Enable
   XIntruptRegs.XINT6CR.bit.ENABLE = 1;        // XINT6 인터럽트 : Enable

   //  백터 활성화
   PieCtrlRegs.PIEIER12.bit.INTx1 = 1;         // PIE 인터럽트(XINT3) : Enable
   PieCtrlRegs.PIEIER12.bit.INTx2 = 1;         // PIE 인터럽트(XINT4) : Enable
   PieCtrlRegs.PIEIER12.bit.INTx3 = 1;         // PIE 인터럽트(XINT5) : Enable
   PieCtrlRegs.PIEIER12.bit.INTx4 = 1;         // PIE 인터럽트(XINT6) : Enable
   IER |= M_INT12;                        // CPU 인터럽트(INT12) : Enable

   SW1_cnt = 0;
   SW2_cnt = 0;
   SW3_cnt = 0;
   SW4_cnt = 0;
   Loop_cnt = 0;
   usec_delay   = 500000;                        // 500 msec
   usec_delay_1 = 1000000;                       // 1sec
   mode = 0;
   state = 0;


   EINT;   // Enable Global interrupt INTM
   ERTM;   // Enable Global realtime interrupt DBGM

   for(;;)
   {
      if (state == 1)
      {
         switch(mode)
         {
         case 1:            // Mode 1
            Printmode_1();
            break;
         case 2:            // Mode 2
             Printmode_2();
            break;
         case 3:            // Mode 3
             Printmode_3();
            break;
         case 4:            // Mode 4
             Printmode_4();
            break;
         case 5:            // Mode 5
             Printmode_5();
            break;
         case 6:            // Mode 6
           Printmode_6();
            break;
         }
      }
      else
          Printmode_stp();   // STOP
   }
}

interrupt void Xint3_isr(void)                          // (+) 인터럽트 실행
{
   SW1_cnt++;
   mode++;
   if(mode > 6 )
   {mode = 1;}
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}
interrupt void Xint4_isr(void)                          // (-) 인터럽트 실행
{
   SW2_cnt++;
      mode--;
      if(mode <1 )
      {mode = 6;}
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}
interrupt void Xint5_isr(void)                          // (STOP) 인터럽트 실행
{
   SW3_cnt++;
   state = 0;
   mode = 0;
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}
interrupt void Xint6_isr(void)                          // (START) 인터럽트 실행
{
   SW4_cnt++;
   state = 1;
   mode = 1;
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}

void Printmode_1(void)
{
    i = 0;
    for(;;)
    {
        GpioDataRegs.GPCCLEAR.all = 0x0000FFFF;
        GpioDataRegs.GPCSET.all = 0x00008000 >> i;
        i++;
        DELAY_US(usec_delay_1);
        if(i == 16)
            i = 0;
        if((mode != 1)||(state == 0))
            break;

    }
}
void Printmode_2(void)
{
    i = 0;
    for(;;)
    {
        GpioDataRegs.GPCSET.all = 0x0000FFFF;
        for(j = 0; j<16-i; j++)
        {
            GpioDataRegs.GPCCLEAR.all = 0x00007FFF >> i;
            GpioDataRegs.GPCSET.all = (0x00008000 >> i) >> j;
            DELAY_US(usec_delay);
            if((mode != 2)||(state == 0))
                break;
        }
        i++;
        if(i == 16)
            i = 0;
        if((mode != 2)||(state == 0))
            break;
    }
}
void Printmode_3(void)
{
    GpioDataRegs.GPCSET.all = 0x0000AAAA;
    GpioDataRegs.GPCCLEAR.all = 0x00005555;
    for(;;)
    {
        DELAY_US(usec_delay);
        GpioDataRegs.GPCTOGGLE.all = 0x0000FFFF;
        if((mode != 3)||(state == 0))
            break;
    }
}
void Printmode_4(void)
{
    i = 0;
    for(;;)
    {
        GpioDataRegs.GPCCLEAR.all = 0x0000FFFF;
        GpioDataRegs.GPCSET.all = 0x00008000 >> i;
        GpioDataRegs.GPCSET.all = 0x00000001 << i;
        i++;
        DELAY_US(usec_delay_1);
        if(i == 16)
            i =0;
        if((mode != 4)||(state == 0))
            break;
    }
}
void Printmode_5(void)
{
    i = 0, num = 0;
    for(;;)
    {
        GpioDataRegs.GPCCLEAR.all = 0x0000FFFF;
        switch(i)
        {
        case 0:
            GpioDataRegs.GPCSET.all = 0x00008000 >> num;
            DELAY_US(usec_delay_1);
            i++;
            num = num + i;
            break;
        case 1:
            GpioDataRegs.GPCSET.all = 0x0000C000 >> num;
            DELAY_US(usec_delay_1);
            i++;
            num = num + i;
            break;
        case 2:
            GpioDataRegs.GPCSET.all = 0x0000E000 >> num;
            DELAY_US(usec_delay_1);
            i++;
            num = num + i;
            break;
        case 3:
            GpioDataRegs.GPCSET.all = 0x0000F000 >> num;
            DELAY_US(usec_delay_1);
            i++;
            num = num + i;
            break;
        case 4:
            GpioDataRegs.GPCSET.all = 0x0000F800 >> num;
            DELAY_US(usec_delay_1);
            i++;
            num = num + i;
            i=0;
            break;
        }
        if((mode != 5)||(state == 0))
            break;
          }
}
void Printmode_6(void)
{

     i++;
    if (i == 1)
      {
         GpioDataRegs.GPCDAT.all = 0x00008000;     DELAY_US(usec_delay_1);
      }

      else if (i == 2)
      {
         GpioDataRegs.GPCDAT.all = 0x00006000;      DELAY_US(usec_delay_1);
      }

      else if (i == 3)
      {
         GpioDataRegs.GPCDAT.all = 0x00001C00;      DELAY_US(usec_delay_1);
      }

      else if (i == 4)
      {
         GpioDataRegs.GPCDAT.all = 0x00000300;      DELAY_US(usec_delay_1);
      }

      else if (i == 5)
      {
         GpioDataRegs.GPCDAT.all = 0x00000080;      DELAY_US(usec_delay_1);
      }

      else if (i == 6)
      {
         GpioDataRegs.GPCDAT.all = 0x00000060;      DELAY_US(usec_delay_1);
      }

      else if (i == 7)
      {
         GpioDataRegs.GPCDAT.all = 0x0000001C;      DELAY_US(usec_delay_1);
      }

      else if (i == 8)
      {
         GpioDataRegs.GPCDAT.all = 0x00000003;      DELAY_US(usec_delay_1);
      }


}
void Printmode_stp(void)
{
    GpioDataRegs.GPCDAT.all = 0x00000000;
    for(;;)
    {
        GpioDataRegs.GPCTOGGLE.bit.GPIO79 = 1;
        DELAY_US(usec_delay);

        if(state == 1)
            break;
    }
}
