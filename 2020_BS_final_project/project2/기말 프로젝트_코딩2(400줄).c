#include "DSP28x_Project.h"      /* Device Headerfile and Examples Include File */

#define   SYSTEM_CLOCK      150E6   /* 150MHz */
#define   TBCLK            150E6   /* 150MHz */
#define   PWM_CARRIER         20E3   /* 20kHz */


/* Prototype statements for functions found within this Example */
void InitEPwm5Module(void);
interrupt void EPwm5Isr(void);
interrupt void adc_isr(void);               // ADC 인터럽트 함수 선언

/* Global variables used in this Example */
Uint16   BackTicker;
Uint16   EPwm5IsrTicker;

interrupt void Xint3_isr(void);
interrupt void Xint4_isr(void);
interrupt void Xint5_isr(void);
interrupt void Xint6_isr(void);

float32   PwmCarrierFrequency;
float32   PwmDutyRatio;
float32   FallingEdgeDelay1;
float32   RisingEdgeDelay1;
float32   PWM_CARRIER2, PWM_CARRIER1;


Uint16 ADC_value01, ADC_value02, deadt = 0;
Uint16 Loop_cnt, ADC_cnt;
Uint16 SW1_cnt, SW2_cnt, SW3_cnt, SW4_cnt;

volatile unsigned int mode = 0, mode2 = 0, stop1 = 0, stop2 = 0;

interrupt void Xint3_isr(void) //버튼1~
{
	SW1_cnt++;
	mode++;
	if (mode == 4)
	{
		mode = 1;
	}
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

}
interrupt void Xint4_isr(void)
{
	SW2_cnt++;
	mode2++;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

}

interrupt void Xint5_isr(void)
{
	SW3_cnt++;
	stop1++;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

}

interrupt void Xint6_isr(void)
{
	SW4_cnt++;
	stop2++;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}


void main(void)
{

	/*-----------------------------------------------------------------------------
	   Step 1
	   Disable Global Interrupt & Interrupt Flag Clear
	-----------------------------------------------------------------------------*/
	DINT;
	IER = 0x0000;
	IFR = 0x0000;

	/*-----------------------------------------------------------------------------
	   Step 2
	   2.1 InitSysCtrl()
	   2.1.1 Disables the watchdog
	   2.1.2 Set the PLLCR for proper SYSCLKOUT frequency
	   2.1.3 Set the pre-scaler for the high and low frequency peripheral clocks
	   2.1.4 Enable the clocks to the peripherals
	   2.2 Initialize GPIO MUX
	-----------------------------------------------------------------------------*/
	InitSysCtrl();

	EALLOW;
	GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;   /* Enable pull-up on GPIO6 (EPWM4A) */
	GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;   /* Enable pull-up on GPIO7 (EPWM4B) */
	GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   /* Configure GPIO6 as EPWM4A */
	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   /* Configure GPIO7 as EPWM4B */
	SysCtrlRegs.HISPCP.bit.HSPCLK = 1;     // HSPCLK = SYSCLKOUT/(HISPCP*2)
	EDIS;

	/*-----------------------------------------------------------------------------
	   Step 3
	   3.1 Initialize Peripheral Interrupt Expansion circuit
	-----------------------------------------------------------------------------*/
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	/*-----------------------------------------------------------------------------
	   Step 4
	   4.1 Pie Vector Table Re-allocation
	-----------------------------------------------------------------------------*/
	InitPieVectTable();

	/*-----------------------------------------------------------------------------
	   Step 5
	   5.1 Interrupt Service routine re-mapping and Interrupt vector enable
	-----------------------------------------------------------------------------*/

	/* Interrupt Service Routine Re-mapping */
	EALLOW;
	PieVectTable.EPWM5_INT = &EPwm5Isr;
	PieVectTable.ADCINT = &adc_isr;
	EDIS;

	EALLOW;
	PieVectTable.XINT3 = &Xint3_isr;
	PieVectTable.XINT4 = &Xint4_isr;
	PieVectTable.XINT5 = &Xint5_isr;
	PieVectTable.XINT6 = &Xint6_isr;
	EDIS;

	//============================================================================================
	// Step 4. GPIO 초기화
	//--------------------------------------------------------------------------------------------
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
	//============================================================================================


	//============================================================================================
	// Step 5. Qualification 초기화
	//--------------------------------------------------------------------------------------------
	EALLOW;
	GpioCtrlRegs.GPBCTRL.bit.QUALPRD1 = 0xFF;   // (GPIO40~GPIO47) Qual period 설정
	GpioCtrlRegs.GPBQSEL1.bit.GPIO44 = 2;      // Qualification using 6 samples
	GpioCtrlRegs.GPBQSEL1.bit.GPIO45 = 2;      // Qualification using 6 samples
	GpioCtrlRegs.GPBQSEL1.bit.GPIO46 = 2;      // Qualification using 6 samples
	GpioCtrlRegs.GPBQSEL1.bit.GPIO47 = 2;      // Qualification using 6 samples
	EDIS;
	//============================================================================================


	//============================================================================================
	// Step 6. XINT 초기화
	//--------------------------------------------------------------------------------------------
	EALLOW;
	GpioIntRegs.GPIOXINT3SEL.bit.GPIOSEL = 47;   // 외부 인터럽트 XINT3로 사용할 핀 선택: GPIO47
	GpioIntRegs.GPIOXINT4SEL.bit.GPIOSEL = 46;   // 외부 인터럽트 XINT4로 사용할 핀 선택: GPIO46
	GpioIntRegs.GPIOXINT5SEL.bit.GPIOSEL = 45;   // 외부 인터럽트 XINT5로 사용할 핀 선택: GPIO45
	GpioIntRegs.GPIOXINT6SEL.bit.GPIOSEL = 44;   // 외부 인터럽트 XINT6로 사용할 핀 선택: GPIO44
	EDIS;

	XIntruptRegs.XINT3CR.bit.POLARITY = 0;      // XINT3 인터럽트 발생 조건 설정: 입력 신호의 하강 엣지
	XIntruptRegs.XINT4CR.bit.POLARITY = 0;      // XINT4 인터럽트 발생 조건 설정: 입력 신호의 상승 엣지
	XIntruptRegs.XINT5CR.bit.POLARITY = 0;      // XINT5 인터럽트 발생 조건 설정: 입력 신호의 하강 엣지
	XIntruptRegs.XINT6CR.bit.POLARITY = 0;      // XINT6 인터럽트 발생 조건 설정: 입력 신호의 하강 & 상승 엣지

	XIntruptRegs.XINT3CR.bit.ENABLE = 1;        // XINT3 인터럽트 : Enable
	XIntruptRegs.XINT4CR.bit.ENABLE = 1;        // XINT4 인터럽트 : Enable
	XIntruptRegs.XINT5CR.bit.ENABLE = 1;        // XINT5 인터럽트 : Enable
	XIntruptRegs.XINT6CR.bit.ENABLE = 1;        // XINT6 인터럽트 : Enable

	// 외부 인터터트 포합된 백터 활성화
	PieCtrlRegs.PIEIER12.bit.INTx1 = 1;         // PIE 인터럽트(XINT3) : Enable
	PieCtrlRegs.PIEIER12.bit.INTx2 = 1;         // PIE 인터럽트(XINT4) : Enable
	PieCtrlRegs.PIEIER12.bit.INTx3 = 1;         // PIE 인터럽트(XINT5) : Enable
	PieCtrlRegs.PIEIER12.bit.INTx4 = 1;         // PIE 인터럽트(XINT6) : Enable
	IER |= M_INT12;                        // CPU 인터럽트(INT12) : Enable
 //============================================================================================


 //============================================================================================
 // Step 4. ADC 초기화
 //--------------------------------------------------------------------------------------------
	InitAdc();

	// ADC 설정
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 3;            // ADCCLK = HSPCLK/(ADCCLKPS*2)/(CPS+1)
	AdcRegs.ADCTRL1.bit.CPS = 1;            // ADCCLK = 75MHz/(3*2)/(1+1) = 6.25MHz
	AdcRegs.ADCTRL1.bit.ACQ_PS = 3;            // 샘플/홀드 사이클 = ACQ_PS + 1 = 4 (ADCCLK기준)
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;         // 시퀀스 모드 설정: 직렬 시퀀스 모드 (0:병렬 모드, 1:직렬 모드)
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 1;      // ADC 채널수 설정: 1개(=MAX_CONV+1)채널을 ADC
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0;       // ADC 순서 설정: 첫번째로 ADCINA2 채널을 ADC
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 8;       // ADC 순서 설정: 2번째로 ADCINB0 채널을 ADC

	AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ = 1;       // ePWM_SOCB로 ADC 시퀀스 시동
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;      // ADC 시퀀스 완료시 인터럽트 발생 설정

	//ePWM_SOCB 이벤트 트리거 설정
	EPwm5Regs.ETSEL.bit.SOCBEN = 1;            // SOCB 이벤트 트리거 Enable
	EPwm5Regs.ETSEL.bit.SOCBSEL = 2;         // SCCB 트리거 조건 : 카운터 주기 일치 시
	EPwm5Regs.ETPS.bit.SOCBPRD = 1;            // SOCB 이벤트 분주 설정 : 트리거 조건 한번 마다
	EPwm5Regs.TBCTL.bit.CTRMODE = 0;         // 카운트 모드 설정: Up-conut 모드
	EPwm5Regs.TBCTL.bit.HSPCLKDIV = 1;         // TBCLK = [SYSCLKOUT / ((HSPCLKDIV*2) * 2^(CLKDIV))]
	EPwm5Regs.TBCTL.bit.CLKDIV = 1;            // TBCLK = [150MHz / (2*2)] = 37.5MHz
	EPwm5Regs.TBPRD = (TBCLK / PwmCarrierFrequency) - 1;                  // TB주기= (TBPRD+1)/TBCLK = 1875/37.5MHz = 50us(20KHz)
	EPwm5Regs.TBCTR = 0x0000;               // TB 카운터 초기화

	// PIE의 ADC 인터럽트 활성화
	PieCtrlRegs.PIEIER1.bit.INTx6 = 1;         // PIE 인터럽트(ADCINT) 활성화
	IER |= M_INT1;                         // CPU 인터럽트(INT1)  활성화
	//============================================================================================


	/* Enable PIE group 3 interrupt 4 for EPWM4_INT */
	PieCtrlRegs.PIEIER3.bit.INTx5 = 1;

	/* Enable CPU INT3 for EPWM4_INT */
	IER |= M_INT3;


	/*-----------------------------------------------------------------------------
	   Step 6
	   6.1 Initialize Periphrals for User Application
	-----------------------------------------------------------------------------*/
	/* Initialize EPWM4 Module */
	InitEPwm5Module();

	/*-----------------------------------------------------------------------------
	   Step 7
	   7.1 Initialize S/W modules and Variables
	-----------------------------------------------------------------------------*/
	BackTicker = 0;
	EPwm5IsrTicker = 0;

	PwmCarrierFrequency = PWM_CARRIER;

	FallingEdgeDelay1 = (1.0 / TBCLK) * EPwm5Regs.DBFED;
	RisingEdgeDelay1 = (1.0 / TBCLK) * EPwm5Regs.DBRED;
	//============================================================================================
	// Step 4. Initialize Application Variables
	//--------------------------------------------------------------------------------------------
	ADC_value01 = 0;
	ADC_value02 = 0;
	Loop_cnt = 0;
	//============================================================================================


	/*-----------------------------------------------------------------------------
	Step 8
	8.1 Enable Global realtime interrupt DBGM
	8.2 Enable Global Interrupt
	-----------------------------------------------------------------------------*/
	ERTM;   /* Enable Global realtime interrupt DBGM */
	EINT;   /* Enable Global interrupt INTM */

	/*-----------------------------------------------------------------------------
	Step 9
	9.1 Idle Loop
	-----------------------------------------------------------------------------*/
	/* IDLE loop. Just sit and loop forever: */
	for (;;)
	{

		BackTicker++;
		if (mode == 1)
		{

			EPwm5Regs.TBPRD = (TBCLK / PwmCarrierFrequency) - 1;
			PwmDutyRatio = ADC_value01 * 0.475 / 65536;
			EPwm5Regs.CMPA.half.CMPA = (Uint16)((EPwm5Regs.TBPRD + 1) * PwmDutyRatio);   /* Set Compare A Value to 50% */
			EPwm5Regs.CMPB = (EPwm5Regs.TBPRD + 1) * (1 - PwmDutyRatio); //상보적
			/* Setup Counter Mode and Clock */
			EPwm5Regs.TBCTL.bit.CTRMODE = 2;//up-downcount
			   /* Set Dead-time */
			EPwm5Regs.DBCTL.bit.IN_MODE = 2;      /* EPWMxA is the source for both falling-edge & rising-edge delay */
			EPwm5Regs.DBCTL.bit.OUT_MODE = 3;      /* Dead-band is fully enabled for both rising-edge delay on EPWMxA and falling-edge delay on EPWMxB */
			EPwm5Regs.DBCTL.bit.POLSEL = 2;         /* Active High Complementary (AHC). EPWMxB is inverted */
			EPwm5Regs.DBFED = 450;               /* 3usec, Falling Edge Delay */
			EPwm5Regs.DBRED = 450;               /* 3usec, Rising Edge Delay */

		}
		else if (mode == 2)
		{

			EPwm5Regs.CMPCTL.bit.SHDWBMODE = 0;      /* Compare B Register is loaded from its shadow when CNTR=Zero */
			EPwm5Regs.CMPCTL.bit.LOADBMODE = 0;
			PWM_CARRIER2 = 100E3 + 200E3*ADC_value01 / 65536;
			EPwm5Regs.TBPRD = (TBCLK / PWM_CARRIER2) - 1;   /* Set Timer Period, (150MHz/100KHz)-1 = 1,499 (0x05DB) */
			EPwm5Regs.CMPA.half.CMPA = (Uint16)((EPwm5Regs.TBPRD + 1)*0.5);   /* Set Compare A Value to 50% */



			EPwm5Regs.TBCTL.bit.CTRMODE = 0;//upcont
			EPwm5Regs.AQCTLA.bit.ZRO = 2;      /* Set EPWM4A on CNTR=Zero */
			   /* Set Dead-time */
			EPwm5Regs.DBCTL.bit.IN_MODE = 0;      /* EPWMxA is the source for both falling-edge & rising-edge delay */
			EPwm5Regs.DBCTL.bit.OUT_MODE = 3;      /* Dead-band is fully enabled for both rising-edge delay on EPWMxA and falling-edge delay on EPWMxB */
			EPwm5Regs.DBCTL.bit.POLSEL = 2;         /* Active High Complementary (AHC). EPWMxB is inverted */
			EPwm5Regs.DBFED = 75;               /* 2usec, Falling Edge Delay */
			EPwm5Regs.DBRED = 75;               /* 1usec, Rising Edge Delay */

		}
		else if (mode == 3)
		{
			EPwm5Regs.TBPRD = (TBCLK / PwmCarrierFrequency) - 1;
			EPwm5Regs.CMPA.half.CMPA = (Uint16)((EPwm5Regs.TBPRD + 1) * 0.5);
			deadt = (float32)75 * ADC_value01 / 65536;
			EPwm5Regs.TBCTL.bit.CTRMODE = 0;//upcont
			EPwm5Regs.AQCTLA.bit.ZRO = 2;      /* Set EPWM4A on CNTR=Zero */
			   /* Set Dead-time */
			EPwm5Regs.DBCTL.bit.IN_MODE = 0;      /* EPWMxA is the source for both falling-edge & rising-edge delay */
			EPwm5Regs.DBCTL.bit.OUT_MODE = 3;      /* Dead-band is fully enabled for both rising-edge delay on EPWMxA and falling-edge delay on EPWMxB */
			EPwm5Regs.DBCTL.bit.POLSEL = 2;
			EPwm5Regs.DBFED = deadt;               /* 2usec, Falling Edge Delay */
			EPwm5Regs.DBRED = 0;               /* 1usec, Rising Edge Delay */


			if (stop1 % 2 == 1)
			{

				EPwm5Regs.AQCSFRC.bit.CSFA = 1;

			}
			else if (stop1 % 2 == 0)
			{
				EPwm5Regs.AQCSFRC.bit.CSFA = 3;
			}
			else if (stop2 % 2 == 1)
			{
				/*mode = 0;*/
				EPwm5Regs.AQCSFRC.bit.CSFB = 1;
			}
			else if (stop2 % 2 == 0)
			{
				EPwm5Regs.AQCSFRC.bit.CSFB = 3;
			}

		}
		FallingEdgeDelay1 = (1.0 / TBCLK) * EPwm5Regs.DBFED;
		RisingEdgeDelay1 = (1.0 / TBCLK) * EPwm5Regs.DBRED;

	}
}

/*-----------------------------------------------------------------------------
   Step 10
   10.1 Local Interrupt Service Routines & Functions
-----------------------------------------------------------------------------*/
interrupt void EPwm5Isr(void)
{
	EPwm5IsrTicker++;

	/* Clear INT flag for this timer */
	EPwm5Regs.ETCLR.bit.INT = 1;

	/* Acknowledge this interrupt to receive more interrupts from group 3 */
	PieCtrlRegs.PIEACK.bit.ACK3 = 1;
}



void InitEPwm5Module(void)
{

	EPwm5Regs.TBCTL.bit.HSPCLKDIV = 0;      /* TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = 150MHz */
	EPwm5Regs.TBCTL.bit.CLKDIV = 0;

	/* Setup Phase */
	EPwm5Regs.TBPHS.half.TBPHS = 0;         /* Phase is 0 */
	EPwm5Regs.TBCTL.bit.PHSEN = 0;         /* Disable phase loading */

	/* Setup Period (Carrier Frequency) */
	EPwm5Regs.TBPRD = (TBCLK / PWM_CARRIER) - 1;   /* Set Timer Period, (150MHz/100KHz)-1 = 1,499 (0x05DB) */
	EPwm5Regs.TBCTR = 0;                  /* Clear Counter */


	/* Setup shadowing */
	EPwm5Regs.TBCTL.bit.PRDLD = 0;         /* Period Register is loaded from its shadow when CNTR=Zero */
	EPwm5Regs.CMPCTL.bit.SHDWAMODE = 0;      /* Compare A Register is loaded from its shadow when CNTR=Zero */
	EPwm5Regs.CMPCTL.bit.LOADAMODE = 0;

	/* St actions */
	EPwm5Regs.AQCTLA.bit.CAD = 2;      /* Set EPWM4A on CNTR=Zero */
	EPwm5Regs.AQCTLA.bit.CAU = 1;      /* Clear EPWMBA on CNTR=CMPA, Up-Count */
	EPwm5Regs.AQCTLB.bit.CBU = 2;      /* Set EPWM4A on CNTR=Zero */
	EPwm5Regs.AQCTLB.bit.CBD = 1;      /* Clear EPWMBA on CNTR=CMPA, Up-Count */

	/* Set Interrupts */
	EPwm5Regs.ETSEL.bit.INTSEL = 1;      /* Select INT on CNTR=Zero */
	EPwm5Regs.ETPS.bit.INTPRD = 1;      /* Generate INT on 1st event */
	EPwm5Regs.ETSEL.bit.INTEN = 1;      /* Enable INT */
}



interrupt void adc_isr(void)
{
	ADC_value01 = AdcRegs.ADCRESULT0; //가변저항 a
	ADC_value02 = AdcRegs.ADCRESULT1; //가변저항 b


	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
}

/*======================================================================
   End of file.
======================================================================*/
