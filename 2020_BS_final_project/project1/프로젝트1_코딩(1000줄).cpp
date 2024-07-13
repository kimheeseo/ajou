//============================================================================================
// 선행처리지시
//--------------------------------------------------------------------------------------------
#include "DSP28x_Project.h"                  // Device Headerfile and Examples Include File
//============================================================================================
#define timeA 1000000
#define timeB 500000
#define timeC 500000
#define timeD 1000000
#define timeE 1000000
#define timeF 1000000
#define timeStop 500000
//============================================================================================
//   함수선언
//--------------------------------------------------------------------------------------------
interrupt void Xint3_isr(void);
interrupt void Xint4_isr(void);
interrupt void Xint5_isr(void);
interrupt void Xint6_isr(void);
int modeA(int);
int modeB(int);
int modeC(int);
int modeD(int);
int modeE(int);
int modeF(int);
int modeS(int);
//============================================================================================

//============================================================================================
// 시스템에서사용할전역변수선언
//--------------------------------------------------------------------------------------------
Uint16 Loop_cnt;
Uint16 SW1_cnt, SW2_cnt, SW3_cnt, SW4_cnt;
volatile unsigned int i = 0;
volatile unsigned int mode = 0, stop = 0;

//============================================================================================
// 사용자함수
int modeA(int i)
{
	if (i == 1)
	{
		GpioDataRegs.GPCDAT.all = 32768;    DELAY_US(timeA);
	}

	else if (i == 2)
	{
		GpioDataRegs.GPCDAT.all = 16384;     DELAY_US(timeA);
	}

	else if (i == 3)
	{
		GpioDataRegs.GPCDAT.all = 8192;     DELAY_US(timeA);
	}

	else if (i == 4)
	{
		GpioDataRegs.GPCDAT.all = 4096;     DELAY_US(timeA);
	}

	else if (i == 5)
	{
		GpioDataRegs.GPCDAT.all = 2048;     DELAY_US(timeA);
	}

	else if (i == 6)
	{
		GpioDataRegs.GPCDAT.all = 1024;     DELAY_US(timeA);
	}

	else if (i == 7)
	{
		GpioDataRegs.GPCDAT.all = 512;     DELAY_US(timeA);
	}

	else if (i == 8)
	{
		GpioDataRegs.GPCDAT.all = 256;     DELAY_US(timeA);
	}

	else if (i == 9)
	{
		GpioDataRegs.GPCDAT.all = 128;     DELAY_US(timeA);
	}

	else if (i == 10)
	{
		GpioDataRegs.GPCDAT.all = 64;     DELAY_US(timeA);
	}

	else if (i == 11)
	{
		GpioDataRegs.GPCDAT.all = 32;     DELAY_US(timeA);
	}

	else if (i == 12)
	{
		GpioDataRegs.GPCDAT.all = 16;     DELAY_US(timeA);
	}

	else if (i == 13)
	{
		GpioDataRegs.GPCDAT.all = 8;     DELAY_US(timeA);
	}

	else if (i == 14)
	{
		GpioDataRegs.GPCDAT.all = 4;     DELAY_US(timeA);
	}

	else if (i == 15)
	{
		GpioDataRegs.GPCDAT.all = 2;     DELAY_US(timeA);
	}

	else if (i == 16)
	{
		GpioDataRegs.GPCDAT.all = 1;     DELAY_US(timeA);
	}

	return 1;
}


int modeB(int i)
{
	if (i == 1)
	{
		GpioDataRegs.GPCDAT.all = 32768; DELAY_US(timeB);
	}
	else if (i == 2)
	{
		GpioDataRegs.GPCDAT.all = 49152; DELAY_US(timeB);
	}
	else if (i == 3)
	{
		GpioDataRegs.GPCDAT.all = 40960; DELAY_US(timeB);
	}
	else if (i == 4)
	{
		GpioDataRegs.GPCDAT.all = 36864; DELAY_US(timeB);
	}
	else if (i == 5)
	{
		GpioDataRegs.GPCDAT.all = 34816; DELAY_US(timeB);
	}
	else if (i == 6)
	{
		GpioDataRegs.GPCDAT.all = 33792; DELAY_US(timeB);
	}
	else if (i == 7)
	{
		GpioDataRegs.GPCDAT.all = 33280; DELAY_US(timeB);
	}
	else if (i == 8)
	{
		GpioDataRegs.GPCDAT.all = 33024; DELAY_US(timeB);
	}
	else if (i == 9)
	{
		GpioDataRegs.GPCDAT.all = 32896; DELAY_US(timeB);
	}
	else if (i == 10)
	{
		GpioDataRegs.GPCDAT.all = 32832; DELAY_US(timeB);
	}
	else if (i == 11)
	{
		GpioDataRegs.GPCDAT.all = 32800; DELAY_US(timeB);
	}
	else if (i == 12)
	{
		GpioDataRegs.GPCDAT.all = 32784; DELAY_US(timeB);
	}
	else if (i == 13)
	{
		GpioDataRegs.GPCDAT.all = 32776; DELAY_US(timeB);
	}
	else if (i == 14)
	{
		GpioDataRegs.GPCDAT.all = 32772; DELAY_US(timeB);
	}
	else if (i == 15)
	{
		GpioDataRegs.GPCDAT.all = 32770; DELAY_US(timeB);
	}
	else if (i == 16)
	{
		GpioDataRegs.GPCDAT.all = 32769; DELAY_US(timeB);
	}
	else if (i == 17)
	{
		GpioDataRegs.GPCDAT.all = 49152; DELAY_US(timeB);
	}
	else if (i == 18)
	{
		GpioDataRegs.GPCDAT.all = 57344; DELAY_US(timeB);
	}
	else if (i == 19)
	{
		GpioDataRegs.GPCDAT.all = 53248; DELAY_US(timeB);
	}
	else if (i == 20)
	{
		GpioDataRegs.GPCDAT.all = 51200; DELAY_US(timeB);
	}
	else if (i == 21)
	{
		GpioDataRegs.GPCDAT.all = 50176; DELAY_US(timeB);
	}
	else if (i == 22)
	{
		GpioDataRegs.GPCDAT.all = 49664; DELAY_US(timeB);
	}
	else if (i == 23)
	{
		GpioDataRegs.GPCDAT.all = 49408; DELAY_US(timeB);
	}
	else if (i == 24)
	{
		GpioDataRegs.GPCDAT.all = 49280; DELAY_US(timeB);
	}
	else if (i == 25)
	{
		GpioDataRegs.GPCDAT.all = 49216; DELAY_US(timeB);
	}
	else if (i == 26)
	{
		GpioDataRegs.GPCDAT.all = 49184; DELAY_US(timeB);
	}
	else if (i == 27)
	{
		GpioDataRegs.GPCDAT.all = 49168; DELAY_US(timeB);
	}
	else if (i == 28)
	{
		GpioDataRegs.GPCDAT.all = 49160; DELAY_US(timeB);
	}
	else if (i == 29)
	{
		GpioDataRegs.GPCDAT.all = 49156; DELAY_US(timeB);
	}
	else if (i == 30)
	{
		GpioDataRegs.GPCDAT.all = 49154; DELAY_US(timeB);
	}
	else if (i == 31)
	{
		GpioDataRegs.GPCDAT.all = 49153; DELAY_US(timeB);
	}
	else if (i == 32)
	{
		GpioDataRegs.GPCDAT.all = 57344; DELAY_US(timeB);
	}
	else if (i == 33)
	{
		GpioDataRegs.GPCDAT.all = 61440; DELAY_US(timeB);
	}
	else if (i == 34)
	{
		GpioDataRegs.GPCDAT.all = 59392; DELAY_US(timeB);
	}
	else if (i == 35)
	{
		GpioDataRegs.GPCDAT.all = 58368; DELAY_US(timeB);
	}
	else if (i == 36)
	{
		GpioDataRegs.GPCDAT.all = 57856; DELAY_US(timeB);
	}
	else if (i == 37)
	{
		GpioDataRegs.GPCDAT.all = 57600; DELAY_US(timeB);
	}
	else if (i == 38)
	{
		GpioDataRegs.GPCDAT.all = 57472; DELAY_US(timeB);
	}
	else if (i == 39)
	{
		GpioDataRegs.GPCDAT.all = 57408; DELAY_US(timeB);
	}
	else if (i == 40)
	{
		GpioDataRegs.GPCDAT.all = 57376; DELAY_US(timeB);
	}
	else if (i == 41)
	{
		GpioDataRegs.GPCDAT.all = 57360; DELAY_US(timeB);
	}
	else if (i == 42)
	{
		GpioDataRegs.GPCDAT.all = 57352; DELAY_US(timeB);
	}
	else if (i == 43)
	{
		GpioDataRegs.GPCDAT.all = 57348; DELAY_US(timeB);
	}
	else if (i == 44)
	{
		GpioDataRegs.GPCDAT.all = 57346; DELAY_US(timeB);
	}
	else if (i == 45)
	{
		GpioDataRegs.GPCDAT.all = 57345; DELAY_US(timeB);
	}
	else if (i == 46)
	{
		GpioDataRegs.GPCDAT.all = 61440; DELAY_US(timeB);
	}
	else if (i == 47)
	{
		GpioDataRegs.GPCDAT.all = 63488; DELAY_US(timeB);
	}
	else if (i == 48)
	{
		GpioDataRegs.GPCDAT.all = 62464; DELAY_US(timeB);
	}
	else if (i == 49)
	{
		GpioDataRegs.GPCDAT.all = 61952; DELAY_US(timeB);
	}
	else if (i == 50)
	{
		GpioDataRegs.GPCDAT.all = 61696; DELAY_US(timeB);
	}
	else if (i == 51)
	{
		GpioDataRegs.GPCDAT.all = 61568; DELAY_US(timeB);
	}
	else if (i == 52)
	{
		GpioDataRegs.GPCDAT.all = 61504; DELAY_US(timeB);
	}
	else if (i == 53)
	{
		GpioDataRegs.GPCDAT.all = 61472; DELAY_US(timeB);
	}
	else if (i == 54)
	{
		GpioDataRegs.GPCDAT.all = 61456; DELAY_US(timeB);
	}
	else if (i == 55)
	{
		GpioDataRegs.GPCDAT.all = 61448; DELAY_US(timeB);
	}
	else if (i == 56)
	{
		GpioDataRegs.GPCDAT.all = 61444; DELAY_US(timeB);
	}
	else if (i == 57)
	{
		GpioDataRegs.GPCDAT.all = 61442; DELAY_US(timeB);
	}
	else if (i == 58)
	{
		GpioDataRegs.GPCDAT.all = 61441; DELAY_US(timeB);
	}
	else if (i == 59)
	{
		GpioDataRegs.GPCDAT.all = 63488; DELAY_US(timeB);
	}
	else if (i == 60)
	{
		GpioDataRegs.GPCDAT.all = 64512; DELAY_US(timeB);
	}
	else if (i == 61)
	{
		GpioDataRegs.GPCDAT.all = 64000; DELAY_US(timeB);
	}
	else if (i == 62)
	{
		GpioDataRegs.GPCDAT.all = 63744; DELAY_US(timeB);
	}
	else if (i == 63)
	{
		GpioDataRegs.GPCDAT.all = 63616; DELAY_US(timeB);
	}
	else if (i == 64)
	{
		GpioDataRegs.GPCDAT.all = 63552; DELAY_US(timeB);
	}
	else if (i == 65)
	{
		GpioDataRegs.GPCDAT.all = 63520; DELAY_US(timeB);
	}
	else if (i == 66)
	{
		GpioDataRegs.GPCDAT.all = 63504; DELAY_US(timeB);
	}
	else if (i == 67)
	{
		GpioDataRegs.GPCDAT.all = 63496; DELAY_US(timeB);
	}
	else if (i == 68)
	{
		GpioDataRegs.GPCDAT.all = 63492; DELAY_US(timeB);
	}
	else if (i == 69)
	{
		GpioDataRegs.GPCDAT.all = 63490; DELAY_US(timeB);
	}
	else if (i == 70)
	{
		GpioDataRegs.GPCDAT.all = 63489; DELAY_US(timeB);
	}
	else if (i == 71)
	{
		GpioDataRegs.GPCDAT.all = 64512; DELAY_US(timeB);
	}
	else if (i == 72)
	{
		GpioDataRegs.GPCDAT.all = 65024; DELAY_US(timeB);
	}
	else if (i == 73)
	{
		GpioDataRegs.GPCDAT.all = 64768; DELAY_US(timeB);
	}
	else if (i == 74)
	{
		GpioDataRegs.GPCDAT.all = 64640; DELAY_US(timeB);
	}
	else if (i == 75)
	{
		GpioDataRegs.GPCDAT.all = 64576; DELAY_US(timeB);
	}
	else if (i == 76)
	{
		GpioDataRegs.GPCDAT.all = 64544; DELAY_US(timeB);
	}
	else if (i == 77)
	{
		GpioDataRegs.GPCDAT.all = 64528; DELAY_US(timeB);
	}
	else if (i == 78)
	{
		GpioDataRegs.GPCDAT.all = 64520; DELAY_US(timeB);
	}
	else if (i == 79)
	{
		GpioDataRegs.GPCDAT.all = 64516; DELAY_US(timeB);
	}
	else if (i == 80)
	{
		GpioDataRegs.GPCDAT.all = 64514; DELAY_US(timeB);
	}
	else if (i == 81)
	{
		GpioDataRegs.GPCDAT.all = 64513; DELAY_US(timeB);
	}
	else if (i == 82)
	{
		GpioDataRegs.GPCDAT.all = 65024; DELAY_US(timeB);
	}
	else if (i == 83)
	{
		GpioDataRegs.GPCDAT.all = 65280; DELAY_US(timeB);
	}
	else if (i == 84)
	{
		GpioDataRegs.GPCDAT.all = 65152; DELAY_US(timeB);
	}
	else if (i == 85)
	{
		GpioDataRegs.GPCDAT.all = 65088; DELAY_US(timeB);
	}
	else if (i == 86)
	{
		GpioDataRegs.GPCDAT.all = 65056; DELAY_US(timeB);
	}
	else if (i == 87)
	{
		GpioDataRegs.GPCDAT.all = 65040; DELAY_US(timeB);
	}
	else if (i == 88)
	{
		GpioDataRegs.GPCDAT.all = 65032; DELAY_US(timeB);
	}
	else if (i == 89)
	{
		GpioDataRegs.GPCDAT.all = 65028; DELAY_US(timeB);
	}
	else if (i == 90)
	{
		GpioDataRegs.GPCDAT.all = 65026; DELAY_US(timeB);
	}
	else if (i == 91)
	{
		GpioDataRegs.GPCDAT.all = 65025; DELAY_US(timeB);
	}
	else if (i == 92)
	{
		GpioDataRegs.GPCDAT.all = 65280; DELAY_US(timeB);
	}
	else if (i == 93)
	{
		GpioDataRegs.GPCDAT.all = 65408; DELAY_US(timeB);
	}
	else if (i == 94)
	{
		GpioDataRegs.GPCDAT.all = 65344; DELAY_US(timeB);
	}
	else if (i == 95)
	{
		GpioDataRegs.GPCDAT.all = 65312; DELAY_US(timeB);
	}
	else if (i == 96)
	{
		GpioDataRegs.GPCDAT.all = 65296; DELAY_US(timeB);
	}
	else if (i == 97)
	{
		GpioDataRegs.GPCDAT.all = 65288; DELAY_US(timeB);
	}
	else if (i == 98)
	{
		GpioDataRegs.GPCDAT.all = 65284; DELAY_US(timeB);
	}
	else if (i == 99)
	{
		GpioDataRegs.GPCDAT.all = 65282; DELAY_US(timeB);
	}
	else if (i == 100)
	{
		GpioDataRegs.GPCDAT.all = 65281; DELAY_US(timeB);
	}
	else if (i == 101)
	{
		GpioDataRegs.GPCDAT.all = 65408; DELAY_US(timeB);
	}
	else if (i == 102)
	{
		GpioDataRegs.GPCDAT.all = 65472; DELAY_US(timeB);
	}
	else if (i == 103)
	{
		GpioDataRegs.GPCDAT.all = 65440; DELAY_US(timeB);
	}
	else if (i == 104)
	{
		GpioDataRegs.GPCDAT.all = 65424; DELAY_US(timeB);
	}
	else if (i == 105)
	{
		GpioDataRegs.GPCDAT.all = 65416; DELAY_US(timeB);
	}
	else if (i == 106)
	{
		GpioDataRegs.GPCDAT.all = 65412; DELAY_US(timeB);
	}
	else if (i == 107)
	{
		GpioDataRegs.GPCDAT.all = 65410; DELAY_US(timeB);
	}
	else if (i == 108)
	{
		GpioDataRegs.GPCDAT.all = 65409; DELAY_US(timeB);
	}
	else if (i == 109)
	{
		GpioDataRegs.GPCDAT.all = 65472; DELAY_US(timeB);
	}
	else if (i == 110)
	{
		GpioDataRegs.GPCDAT.all = 65504; DELAY_US(timeB);
	}
	else if (i == 111)
	{
		GpioDataRegs.GPCDAT.all = 65488; DELAY_US(timeB);
	}
	else if (i == 112)
	{
		GpioDataRegs.GPCDAT.all = 65480; DELAY_US(timeB);
	}
	else if (i == 113)
	{
		GpioDataRegs.GPCDAT.all = 65476; DELAY_US(timeB);
	}
	else if (i == 114)
	{
		GpioDataRegs.GPCDAT.all = 65474; DELAY_US(timeB);
	}
	else if (i == 115)
	{
		GpioDataRegs.GPCDAT.all = 65473; DELAY_US(timeB);
	}
	else if (i == 116)
	{
		GpioDataRegs.GPCDAT.all = 65504; DELAY_US(timeB);
	}
	else if (i == 117)
	{
		GpioDataRegs.GPCDAT.all = 65520; DELAY_US(timeB);
	}
	else if (i == 118)
	{
		GpioDataRegs.GPCDAT.all = 65512; DELAY_US(timeB);
	}
	else if (i == 119)
	{
		GpioDataRegs.GPCDAT.all = 65508; DELAY_US(timeB);
	}
	else if (i == 120)
	{
		GpioDataRegs.GPCDAT.all = 65506; DELAY_US(timeB);
	}
	else if (i == 121)
	{
		GpioDataRegs.GPCDAT.all = 65505; DELAY_US(timeB);
	}
	else if (i == 122)
	{
		GpioDataRegs.GPCDAT.all = 65520; DELAY_US(timeB);
	}
	else if (i == 123)
	{
		GpioDataRegs.GPCDAT.all = 65528; DELAY_US(timeB);
	}
	else if (i == 124)
	{
		GpioDataRegs.GPCDAT.all = 65524; DELAY_US(timeB);
	}
	else if (i == 125)
	{
		GpioDataRegs.GPCDAT.all = 65522; DELAY_US(timeB);
	}
	else if (i == 126)
	{
		GpioDataRegs.GPCDAT.all = 65521; DELAY_US(timeB);
	}
	else if (i == 127)
	{
		GpioDataRegs.GPCDAT.all = 65528; DELAY_US(timeB);
	}
	else if (i == 128)
	{
		GpioDataRegs.GPCDAT.all = 65532; DELAY_US(timeB);
	}
	else if (i == 129)
	{
		GpioDataRegs.GPCDAT.all = 65530; DELAY_US(timeB);
	}
	else if (i == 130)
	{
		GpioDataRegs.GPCDAT.all = 65529; DELAY_US(timeB);
	}
	else if (i == 131)
	{
		GpioDataRegs.GPCDAT.all = 65532; DELAY_US(timeB);
	}
	else if (i == 132)
	{
		GpioDataRegs.GPCDAT.all = 65534; DELAY_US(timeB);
	}
	else if (i == 133)
	{
		GpioDataRegs.GPCDAT.all = 65533; DELAY_US(timeB);
	}
	else if (i == 134)
	{
		GpioDataRegs.GPCDAT.all = 65534; DELAY_US(timeB);
	}
	else if (i == 135)
	{
		GpioDataRegs.GPCDAT.all = 65535; DELAY_US(timeB);
	}
	else if (i == 136)
	{
		GpioDataRegs.GPCDAT.all = 65535; DELAY_US(timeB);
	}

	return 1;
}


int modeC(int i)
{
	if (i == 1)
	{
		GpioDataRegs.GPCDAT.all = 43690;    DELAY_US(timeC);
	}

	else if (i == 2)
	{
		GpioDataRegs.GPCDAT.all = 21845;     DELAY_US(timeC);
	}

	return 1;
}

int modeD(int i)
{
	if (i == 1)
	{
		GpioDataRegs.GPCDAT.all = 32769;    DELAY_US(timeD);
	}

	else if (i == 2)
	{
		GpioDataRegs.GPCDAT.all = 16386;     DELAY_US(timeD);
	}

	else if (i == 3)
	{
		GpioDataRegs.GPCDAT.all = 8196;     DELAY_US(timeD);
	}

	else if (i == 4)
	{
		GpioDataRegs.GPCDAT.all = 4104;     DELAY_US(timeD);
	}

	else if (i == 5)
	{
		GpioDataRegs.GPCDAT.all = 2064;     DELAY_US(timeD);
	}

	else if (i == 6)
	{
		GpioDataRegs.GPCDAT.all = 1056;     DELAY_US(timeD);
	}

	else if (i == 7)
	{
		GpioDataRegs.GPCDAT.all = 576;     DELAY_US(timeD);
	}

	else if (i == 8)
	{
		GpioDataRegs.GPCDAT.all = 384;     DELAY_US(timeD);
	}

	else if (i == 9)
	{
		GpioDataRegs.GPCDAT.all = 384;     DELAY_US(timeD);
	}

	else if (i == 10)
	{
		GpioDataRegs.GPCDAT.all = 576;     DELAY_US(timeD);
	}

	else if (i == 11)
	{
		GpioDataRegs.GPCDAT.all = 1056;     DELAY_US(timeD);
	}

	else if (i == 12)
	{
		GpioDataRegs.GPCDAT.all = 2064;     DELAY_US(timeD);
	}

	else if (i == 13)
	{
		GpioDataRegs.GPCDAT.all = 4104;     DELAY_US(timeD);
	}

	else if (i == 14)
	{
		GpioDataRegs.GPCDAT.all = 8196;     DELAY_US(timeD);
	}

	else if (i == 15)
	{
		GpioDataRegs.GPCDAT.all = 16386;     DELAY_US(timeD);
	}

	else if (i == 16)
	{
		GpioDataRegs.GPCDAT.all = 32769;     DELAY_US(timeD);
	}

	return 1;
}


int modeE(int i)
{
	if (i == 1)
	{
		GpioDataRegs.GPCDAT.all = 32768; DELAY_US(timeE);
	}
	else if (i == 2)
	{
		GpioDataRegs.GPCDAT.all = 24576; DELAY_US(timeE);
	}
	else if (i == 3)
	{
		GpioDataRegs.GPCDAT.all = 7168; DELAY_US(timeE);
	}
	else if (i == 4)
	{
		GpioDataRegs.GPCDAT.all = 960; DELAY_US(timeE);
	}
	else if (i == 5)
	{
		GpioDataRegs.GPCDAT.all = 62; DELAY_US(timeE);
	}
	else if (i == 6)
	{
		GpioDataRegs.GPCDAT.all = 1; DELAY_US(timeE);
	}

	return 1;
}


int modeF(int i)
{

	if (i == 1)
	{
		GpioDataRegs.GPCDAT.all = 32768;    DELAY_US(timeF);
	}

	else if (i == 2)
	{
		GpioDataRegs.GPCDAT.all = 24576;     DELAY_US(timeF);
	}

	else if (i == 3)
	{
		GpioDataRegs.GPCDAT.all = 7168;     DELAY_US(timeF);
	}

	else if (i == 4)
	{
		GpioDataRegs.GPCDAT.all = 768;     DELAY_US(timeF);
	}

	else if (i == 5)
	{
		GpioDataRegs.GPCDAT.all = 128;     DELAY_US(timeF);
	}

	else if (i == 6)
	{
		GpioDataRegs.GPCDAT.all = 96;     DELAY_US(timeF);
	}

	else if (i == 7)
	{
		GpioDataRegs.GPCDAT.all = 28;     DELAY_US(timeF);
	}

	else if (i == 8)
	{
		GpioDataRegs.GPCDAT.all = 6;     DELAY_US(timeF);
	}

	return 1;
}

int modeS(int i)
{
	if (i == 1) {
		GpioDataRegs.GPCDAT.all = 32768;    DELAY_US(timeStop);
	}
	else if (i == 2) {
		GpioDataRegs.GPCDAT.all = 0;    DELAY_US(timeStop);
	}
}

//============================================================================================
//   메인함수- 시작
//============================================================================================
void main(void)
{
	//============================================================================================
	// Step 1. Disable Global Interrupt
	//--------------------------------------------------------------------------------------------
	DINT;
	//============================================================================================


	//============================================================================================
	// Step 2. 시스템컨트롤초기화:
	//--------------------------------------------------------------------------------------------
	InitSysCtrl();
	//============================================================================================


	//============================================================================================
	// Step 3. 인터럽트초기화:
	//--------------------------------------------------------------------------------------------
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();

	// Vector Remapping
	EALLOW;
	PieVectTable.XINT3 = &Xint3_isr;
	PieVectTable.XINT4 = &Xint4_isr;
	PieVectTable.XINT5 = &Xint5_isr;
	PieVectTable.XINT6 = &Xint6_isr;
	EDIS;
	//============================================================================================


	//============================================================================================
	// Step 4. GPIO 초기화
	//--------------------------------------------------------------------------------------------
	EALLOW;
	GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;      // 핀기능선택: GPIO44
	GpioCtrlRegs.GPBMUX1.bit.GPIO45 = 0;      // 핀기능선택: GPIO45
	GpioCtrlRegs.GPBMUX1.bit.GPIO46 = 0;      // 핀기능선택: GPIO46
	GpioCtrlRegs.GPBMUX1.bit.GPIO47 = 0;      // 핀기능선택: GPIO47
	GpioCtrlRegs.GPBDIR.bit.GPIO44 = 0;         // GPIO44 입출력선택: Input
	GpioCtrlRegs.GPBDIR.bit.GPIO45 = 0;         // GPIO45 입출력선택: Input
	GpioCtrlRegs.GPBDIR.bit.GPIO46 = 0;         // GPIO46 입출력선택: Input
	GpioCtrlRegs.GPBDIR.bit.GPIO47 = 0;         // GPIO47 입출력선택: Input

	GpioCtrlRegs.GPCMUX1.all = 0x00000000;// GPIO64-GPIO79, GPIO 기능으로설정
	GpioCtrlRegs.GPCDIR.all = 0x0000FFFF;// GPI064-GPIO79, 출력으로설정
	GpioDataRegs.GPCDAT.all = 0x0000FFFF;
	EDIS;
	//============================================================================================

	EALLOW;
	GpioCtrlRegs.GPBCTRL.bit.QUALPRD1 = 0xFF;   // (GPIO40~GPIO47) Qual period 설정
	GpioCtrlRegs.GPBQSEL1.bit.GPIO44 = 2;      // Qualification using 6 samples
	GpioCtrlRegs.GPBQSEL1.bit.GPIO45 = 2;      // Qualification using 6 samples
	GpioCtrlRegs.GPBQSEL1.bit.GPIO46 = 2;      // Qualification using 6 samples
	GpioCtrlRegs.GPBQSEL1.bit.GPIO47 = 2;      // Qualification using 6 samples
	EDIS;

	//============================================================================================
	// Step 5. XINT 초기화
	//--------------------------------------------------------------------------------------------
	EALLOW;
	GpioIntRegs.GPIOXINT3SEL.bit.GPIOSEL = 47;   // 외부인터럽트XINT3로사용할핀선택: GPIO47
	GpioIntRegs.GPIOXINT4SEL.bit.GPIOSEL = 46;   // 외부인터럽트XINT4로사용할핀선택: GPIO46
	GpioIntRegs.GPIOXINT5SEL.bit.GPIOSEL = 45;   // 외부인터럽트XINT5로사용할핀선택: GPIO45
	GpioIntRegs.GPIOXINT6SEL.bit.GPIOSEL = 44;   // 외부인터럽트XINT6로사용할핀선택: GPIO44
	EDIS;

	XIntruptRegs.XINT3CR.bit.POLARITY = 2;      // XINT3 인터럽트발생조건설정: 입력신호의하강엣지
	XIntruptRegs.XINT4CR.bit.POLARITY = 1;      // XINT4 인터럽트발생조건설정: 입력신호의상승엣지
	XIntruptRegs.XINT5CR.bit.POLARITY = 1;      // XINT5 인터럽트발생조건설정: 입력신호의하강엣지
	XIntruptRegs.XINT6CR.bit.POLARITY = 1;      // XINT6 인터럽트발생조건설정: 입력신호의하강& 상승엣지

	XIntruptRegs.XINT3CR.bit.ENABLE = 1;        // XINT3 인터럽트: Enable
	XIntruptRegs.XINT4CR.bit.ENABLE = 1;        // XINT4 인터럽트: Enable
	XIntruptRegs.XINT5CR.bit.ENABLE = 1;        // XINT5 인터럽트: Enable
	XIntruptRegs.XINT6CR.bit.ENABLE = 1;        // XINT6 인터럽트: Enable

	// 외부인터터트포합된백터활성화
	PieCtrlRegs.PIEIER12.bit.INTx1 = 1;         // PIE 인터럽트(XINT3) : Enable
	PieCtrlRegs.PIEIER12.bit.INTx2 = 1;         // PIE 인터럽트(XINT4) : Enable
	PieCtrlRegs.PIEIER12.bit.INTx3 = 1;         // PIE 인터럽트(XINT5) : Enable
	PieCtrlRegs.PIEIER12.bit.INTx4 = 1;         // PIE 인터럽트(XINT6) : Enable
	IER |= M_INT12;                        // CPU 인터럽트(INT12) : Enable
	//============================================================================================


	//============================================================================================
	// Step 6. Initialize Application Variables
	//--------------------------------------------------------------------------------------------
	SW1_cnt = 0;
	SW2_cnt = 0;
	SW3_cnt = 0;
	SW4_cnt = 0;
	Loop_cnt = 0;
	//============================================================================================


	//============================================================================================
	// Enable global Interrupts and higher priority real-time debug events:
	//--------------------------------------------------------------------------------------------
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM
	//============================================================================================


	//============================================================================================
	// IDLE loop. Just sit and loop forever :
	//--------------------------------------------------------------------------------------------
	for (;;)
	{
		if (stop == 1)
		{
			for (i = 1; i < 3; i++)
			{
				if (stop != 1) { break; }
				modeS(i);
			}

		}

		else if (mode == 1)
		{
			for (i = 1; i < 17; i++)
			{
				if (mode != 1 || stop != 0) { break; }
				modeA(i);
			}
		}

		else if (mode == 2)
		{
			for (i = 1; i < 137; i++)
			{
				if (mode != 2 || stop != 0) { break; }
				modeB(i);
			}
		}

		else if (mode == 3)
		{
			for (i = 1; i < 3; i++)
			{
				if (mode != 3 || stop != 0) { break; }
				modeC(i);
			}
		}

		else if (mode == 4)
		{


			for (i = 1; i < 17; i++)
			{
				if (mode != 4 || stop != 0) { break; }
				modeD(i);
			}
		}

		else if (mode == 5)
		{
			for (i = 1; i < 7; i++)
			{
				if (mode != 5 || stop != 0) { break; }
				modeE(i);
			}
		}

		else if (mode == 6)
		{
			for (i = 1; i < 9; i++)
			{
				if (mode != 6 || stop != 0) { break; }
				modeF(i);
			}
		}

		else if (mode >= 6)
		{
			mode = 1;
		}

		else if (mode <= 1)
		{
			mode = 6;
		}


		Loop_cnt++;
	}
	//============================================================================================

}
//============================================================================================
//   메인함수- 끝
//============================================================================================


//============================================================================================
//   ISR 함수정의
//--------------------------------------------------------------------------------------------
interrupt void Xint3_isr(void)
{
	SW1_cnt++;
	mode++;
	stop = 0;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}

interrupt void Xint4_isr(void)
{
	SW2_cnt++;
	mode--;
	stop = 0;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}

interrupt void Xint5_isr(void)
{
	SW3_cnt++;
	stop = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}

interrupt void Xint6_isr(void)
{
	SW4_cnt++;
	stop = 0;
	mode = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}
//============================================================================================
