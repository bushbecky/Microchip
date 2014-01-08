/********************************************************************
 FileName:      main.c
 Dependencies:  See INCLUDES section
 Processor:     PIC18, PIC24, dsPIC, and PIC32 USB Microcontrollers
 Hardware:      This demo is natively intended to be used on Microchip USB demo
                boards supported by the MCHPFSUSB stack.  See release notes for
                support matrix.  This demo can be modified for use on other 
                hardware platforms.
 Complier:      Microchip C18 (for PIC18), XC16 (for PIC24/dsPIC), XC32 (for PIC32)
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Description
  ----  -----------------------------------------
  2.6   Initial release
  2.6a  Added support for the PIC24FJ256GB210 and PIC24FJ256DA210
  2.7   No change
  2.7b  Improvements to USBCBSendResume(), to make it easier to use.
  2.9f  Adding new part support
  2.9j  Updates to support new bootloader features (ex: app version 
        fetching).
********************************************************************/

#ifndef MAIN_C
#define MAIN_C

/** INCLUDES *******************************************************/
#include "./USB/usb.h"
#include "USB/usb_function_audio.h"
#include "HardwareProfile.h"


 /** CONFIGURATION **************************************************/
#if defined(PICDEM_FS_USB)      // Configuration bits for PICDEM FS USB Demo Board (based on PIC18F4550)
        #pragma config PLLDIV   = 5         // (20 MHz crystal on PICDEM FS USB board)
        #pragma config CPUDIV   = OSC1_PLL2   
        #pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2
        #pragma config FOSC     = HSPLL_HS
        #pragma config FCMEN    = OFF
        #pragma config IESO     = OFF
        #pragma config PWRT     = OFF
        #pragma config BOR      = ON
        #pragma config BORV     = 3
        #pragma config VREGEN   = ON      //USB Voltage Regulator
        #pragma config WDT      = OFF
        #pragma config WDTPS    = 32768
        #pragma config MCLRE    = ON
        #pragma config LPT1OSC  = OFF
        #pragma config PBADEN   = OFF
//      #pragma config CCP2MX   = ON
        #pragma config STVREN   = ON
        #pragma config LVP      = OFF
//      #pragma config ICPRT    = OFF       // Dedicated In-Circuit Debug/Programming
        #pragma config XINST    = OFF       // Extended Instruction Set
        #pragma config CP0      = OFF
        #pragma config CP1      = OFF
//      #pragma config CP2      = OFF
//      #pragma config CP3      = OFF
        #pragma config CPB      = OFF
//      #pragma config CPD      = OFF
        #pragma config WRT0     = OFF
        #pragma config WRT1     = OFF
//      #pragma config WRT2     = OFF
//      #pragma config WRT3     = OFF
        #pragma config WRTB     = OFF       // Boot Block Write Protection
        #pragma config WRTC     = OFF
//      #pragma config WRTD     = OFF
        #pragma config EBTR0    = OFF
        #pragma config EBTR1    = OFF
//      #pragma config EBTR2    = OFF
//      #pragma config EBTR3    = OFF
        #pragma config EBTRB    = OFF

#elif defined(PICDEM_FS_USB_K50)
        #pragma config PLLSEL   = PLL3X     // 3X PLL multiplier selected
        #pragma config CFGPLLEN = OFF       // PLL turned on during execution
        #pragma config CPUDIV   = NOCLKDIV  // 1:1 mode (for 48MHz CPU)
        #pragma config LS48MHZ  = SYS48X8   // Clock div / 8 in Low Speed USB mode
        #pragma config FOSC     = INTOSCIO  // HFINTOSC selected at powerup, no clock out
        #pragma config PCLKEN   = OFF       // Primary oscillator driver
        #pragma config FCMEN    = OFF       // Fail safe clock monitor
        #pragma config IESO     = OFF       // Internal/external switchover (two speed startup)
        #pragma config nPWRTEN  = OFF       // Power up timer
        #pragma config BOREN    = SBORDIS   // BOR enabled
        #pragma config nLPBOR   = ON        // Low Power BOR
        #pragma config WDTEN    = SWON      // Watchdog Timer controlled by SWDTEN
        #pragma config WDTPS    = 32768     // WDT postscalar
        #pragma config PBADEN   = OFF       // Port B Digital/Analog Powerup Behavior
        #pragma config SDOMX    = RC7       // SDO function location
        #pragma config LVP      = OFF       // Low voltage programming
        #pragma config MCLRE    = ON        // MCLR function enabled (RE3 disabled)
        #pragma config STVREN   = ON        // Stack overflow reset
        //#pragma config ICPRT  = OFF       // Dedicated ICPORT program/debug pins enable
        #pragma config XINST    = OFF       // Extended instruction set

#elif defined(PIC18F87J50_PIM)				// Configuration bits for PIC18F87J50 FS USB Plug-In Module board
        #pragma config XINST    = OFF   	// Extended instruction set
        #pragma config STVREN   = ON      	// Stack overflow reset
        #pragma config PLLDIV   = 3         // (12 MHz crystal used on this board)
        #pragma config WDTEN    = OFF      	// Watch Dog Timer (WDT)
        #pragma config CP0      = OFF      	// Code protect
        #pragma config CPUDIV   = OSC1      // OSC1 = divide by 1 mode
        #pragma config IESO     = OFF      	// Internal External (clock) Switchover
        #pragma config FCMEN    = OFF      	// Fail Safe Clock Monitor
        #pragma config FOSC     = HSPLL     // Firmware must also set OSCTUNE<PLLEN> to start PLL!
        #pragma config WDTPS    = 32768
//      #pragma config WAIT     = OFF      	// Commented choices are
//      #pragma config BW       = 16      	// only available on the
//      #pragma config MODE     = MM      	// 80 pin devices in the 
//      #pragma config EASHFT   = OFF      	// family.
        #pragma config MSSPMSK  = MSK5
//      #pragma config PMPMX    = DEFAULT
//      #pragma config ECCPMX   = DEFAULT
        #pragma config CCP2MX   = DEFAULT   
        
// Configuration bits for PIC18F97J94 PIM and PIC18F87J94 PIM
#elif defined(PIC18F97J94_PIM) || defined(PIC18F87J94_PIM)
        #pragma config STVREN   = ON      	// Stack overflow reset
        #pragma config XINST    = OFF   	// Extended instruction set
        #pragma config BOREN    = ON        // BOR Enabled
        #pragma config BORV     = 0         // BOR Set to "2.0V" nominal setting
        #pragma config CP0      = OFF      	// Code protect disabled
        #pragma config FOSC     = FRCPLL    // Firmware should also enable active clock tuning for this setting
        #pragma config SOSCSEL  = LOW       // SOSC circuit configured for crystal driver mode
        #pragma config CLKOEN   = OFF       // Disable clock output on RA6
        #pragma config IESO     = OFF      	// Internal External (clock) Switchover
        #pragma config PLLDIV   = NODIV     // 4 MHz input (from 8MHz FRC / 2) provided to PLL circuit
        #pragma config POSCMD   = NONE      // Primary osc disabled, using FRC
        #pragma config FSCM     = CSECMD    // Clock switching enabled, fail safe clock monitor disabled
        #pragma config WPDIS    = WPDIS     // Program memory not write protected
        #pragma config WPCFG    = WPCFGDIS  // Config word page of program memory not write protected
        #pragma config IOL1WAY  = OFF       // IOLOCK can be set/cleared as needed with unlock sequence
        #pragma config LS48MHZ  = SYSX2     // Low Speed USB clock divider
        #pragma config WDTCLK   = LPRC      // WDT always uses INTOSC/LPRC oscillator
        #pragma config WDTEN    = ON        // WDT disabled; SWDTEN can control WDT
        #pragma config WINDIS   = WDTSTD    // Normal non-window mode WDT.
        #pragma config VBTBOR   = OFF       // VBAT BOR disabled
      
#elif defined(PIC18F46J50_PIM) || defined(PIC18F_STARTER_KIT_1) || defined(PIC18F47J53_PIM)
     #pragma config WDTEN = OFF          //WDT disabled (enabled by SWDTEN bit)
     #pragma config PLLDIV = 3           //Divide by 3 (12 MHz oscillator input)
     #pragma config STVREN = ON          //stack overflow/underflow reset enabled
     #pragma config XINST = OFF          //Extended instruction set disabled
     #pragma config CPUDIV = OSC1        //No CPU system clock divide
     #pragma config CP0 = OFF            //Program memory is not code-protected
     #pragma config OSC = HSPLL          //HS oscillator, PLL enabled, HSPLL used by USB
     #pragma config FCMEN = OFF          //Fail-Safe Clock Monitor disabled
     #pragma config IESO = OFF           //Two-Speed Start-up disabled
     #pragma config WDTPS = 32768        //1:32768
     #pragma config DSWDTOSC = INTOSCREF //DSWDT uses INTOSC/INTRC as clock
     #pragma config RTCOSC = T1OSCREF    //RTCC uses T1OSC/T1CKI as clock
     #pragma config DSBOREN = OFF        //Zero-Power BOR disabled in Deep Sleep
     #pragma config DSWDTEN = OFF        //Disabled
     #pragma config DSWDTPS = 8192       //1:8,192 (8.5 seconds)
     #pragma config IOL1WAY = OFF        //IOLOCK bit can be set and cleared
     #pragma config MSSP7B_EN = MSK7     //7 Bit address masking
     #pragma config WPFP = PAGE_1        //Write Protect Program Flash Page 0
     #pragma config WPEND = PAGE_0       //Start protection at page 0
     #pragma config WPCFG = OFF          //Write/Erase last page protect Disabled
     #pragma config WPDIS = OFF          //WPFP[5:0], WPEND, and WPCFG bits ignored 
     #if defined(PIC18F47J53_PIM)
        #pragma config CFGPLLEN = OFF
     #else
        #pragma config T1DIG = ON           //Sec Osc clock source may be selected
        #pragma config LPT1OSC = OFF        //high power Timer1 mode
     #endif
#elif defined(LOW_PIN_COUNT_USB_DEVELOPMENT_KIT)
//	PIC18F14K50
        #pragma config CPUDIV = NOCLKDIV
        #pragma config USBDIV = OFF
        #pragma config FOSC   = HS
        #pragma config PLLEN  = ON
        #pragma config FCMEN  = OFF
        #pragma config IESO   = OFF
        #pragma config PWRTEN = OFF
        #pragma config BOREN  = ON
        #pragma config BORV   = 30
        #pragma config WDTEN  = OFF
        #pragma config WDTPS  = 32768
        #pragma config MCLRE  = OFF
        #pragma config HFOFST = OFF
        #pragma config STVREN = ON
        #pragma config LVP    = OFF
        #pragma config XINST  = OFF
        #pragma config BBSIZ  = OFF
        #pragma config CP0    = OFF
        #pragma config CP1    = OFF
        #pragma config CPB    = OFF
        #pragma config WRT0   = OFF
        #pragma config WRT1   = OFF
        #pragma config WRTB   = OFF
        #pragma config WRTC   = OFF
        #pragma config EBTR0  = OFF
        #pragma config EBTR1  = OFF
        #pragma config EBTRB  = OFF        
        

#elif defined(EXPLORER_16)
    #if defined(__PIC24FJ256GB110__)
        _CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & FWDTEN_OFF & ICS_PGx2) 
        _CONFIG2( PLL_96MHZ_ON & IESO_OFF & FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV2 & IOL1WAY_ON)
    #elif defined(__PIC24FJ256GB210__)
        _CONFIG1(FWDTEN_OFF & ICS_PGx2 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
        _CONFIG2(POSCMOD_HS & IOL1WAY_ON & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_OFF)
    #elif defined(__PIC24FJ64GB004__)
        _CONFIG1(WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
        _CONFIG2(POSCMOD_HS & I2C1SEL_PRI & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_OFF)
        _CONFIG3(WPFP_WPFP0 & SOSCSEL_SOSC & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
        _CONFIG4(DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_SOSC & DSBOREN_OFF & DSWDTEN_OFF)
    #elif defined(__32MX460F512L__) || defined(__32MX795F512L__)
        #pragma config UPLLEN   = ON        // USB PLL Enabled
        #pragma config FPLLMUL  = MUL_15        // PLL Multiplier
        #pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
        #pragma config FPLLIDIV = DIV_2         // PLL Input Divider
        #pragma config FPLLODIV = DIV_1         // PLL Output Divider
        #pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
        #pragma config FWDTEN   = OFF           // Watchdog Timer
        #pragma config WDTPS    = PS1           // Watchdog Timer Postscale
        //#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
        #pragma config OSCIOFNC = OFF           // CLKO Enable
        #pragma config POSCMOD  = HS            // Primary Oscillator
        #pragma config IESO     = OFF           // Internal/External Switch-over
        #pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
        #pragma config FNOSC    = PRIPLL        // Oscillator Selection
        #pragma config CP       = OFF           // Code Protect
        #pragma config BWP      = OFF           // Boot Flash Write Protect
        #pragma config PWP      = OFF           // Program Flash Write Protect
        #pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
        
    #elif defined(__dsPIC33EP512MU810__) || defined (__PIC24EP512GU810__)
        _FOSCSEL(FNOSC_FRC);
        _FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
        _FWDT(FWDTEN_OFF);
    #else
        #error No hardware board defined, see "HardwareProfile.h" and __FILE__
    #endif
#elif defined(PIC24F_STARTER_KIT)
    _CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & FWDTEN_OFF & ICS_PGx2) 
    _CONFIG2( PLL_96MHZ_ON & IESO_OFF & FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV3 & IOL1WAY_ON)
#elif defined(PIC24FJ256DA210_DEV_BOARD)
    _CONFIG1(FWDTEN_OFF & ICS_PGx2 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
    _CONFIG2(POSCMOD_HS & IOL1WAY_ON & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_OFF)
#elif defined(PIC32_USB_STARTER_KIT)
    #pragma config UPLLEN   = ON        // USB PLL Enabled
    #pragma config FPLLMUL  = MUL_15        // PLL Multiplier
    #pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
    #pragma config FPLLIDIV = DIV_2         // PLL Input Divider
    #pragma config FPLLODIV = DIV_1         // PLL Output Divider
    #pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
    #pragma config FWDTEN   = OFF           // Watchdog Timer
    #pragma config WDTPS    = PS1           // Watchdog Timer Postscale
    //#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
    #pragma config OSCIOFNC = OFF           // CLKO Enable
    #pragma config POSCMOD  = HS            // Primary Oscillator
    #pragma config IESO     = OFF           // Internal/External Switch-over
    #pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
    #pragma config FNOSC    = PRIPLL        // Oscillator Selection
    #pragma config CP       = OFF           // Code Protect
    #pragma config BWP      = OFF           // Boot Flash Write Protect
    #pragma config PWP      = OFF           // Program Flash Write Protect
    #pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
#elif defined(PIC24FJ64GB502_MICROSTICK)
    _CONFIG1(WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
    _CONFIG2(I2C1SEL_PRI & IOL1WAY_OFF & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_OFF)
    _CONFIG3(WPFP_WPFP0 & SOSCSEL_SOSC & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
    _CONFIG4(DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_SOSC & DSBOREN_OFF & DSWDTEN_OFF)
#else
    #error No hardware board defined, see "HardwareProfile.h" and __FILE__
#endif



/** VARIABLES ******************************************************/
#if defined(__18CXX)
    #pragma udata

    //The ReceivedDataEvenBuffer[] and ReceivedDataOddBuffer[] arrays are used as
    //USB packet buffers in this firmware.  Therefore, they must be located in
    //a USB module accessible portion of microcontroller RAM.
    #if defined(__18F14K50) || defined(__18F13K50) || defined(__18LF14K50) || defined(__18LF13K50) 
        #pragma udata usbram2
    #elif defined(__18F2455) || defined(__18F2550) || defined(__18F4455) || defined(__18F4550)\
        || defined(__18F2458) || defined(__18F2553) || defined(__18F4458) || defined(__18F4553)\
        || defined(__18LF24K50) || defined(__18F24K50) || defined(__18LF25K50)\
        || defined(__18F25K50) || defined(__18LF45K50) || defined(__18F45K50)
        #pragma udata USB_VARIABLES=0x500
    #elif defined(__18F4450) || defined(__18F2450)
        #pragma udata USB_VARIABLES=0x480
    #else
        #pragma udata
    #endif
#endif

INT16 ReceivedDataEvenBuffer[NO_OF_SAMPLES_IN_A_USB_FRAME];// Holds the Even Audio Data received from Host
INT16 ReceivedDataOddBuffer[NO_OF_SAMPLES_IN_A_USB_FRAME]; // Holds the Odd  Audio Data received from Host

#if defined(__18CXX)
#pragma udata 
#endif
UINT8 sampleCounter = 0; // Keeps track of number of samples played.
USB_HANDLE USBTxHandle = 0;
USB_HANDLE USBRxEvenHandle = 0;
USB_HANDLE USBRxOddHandle = 0;
BOOL receivedDataEvenNeedsServicingNext = FALSE;	//TRUE means even need servicing next, FALSE means odd needs servicing next
BOOL newEvenData = FALSE; // TRUE means a fresh data is arrived in the Even Buffer
BOOL newOddData  = FALSE;  // TRUE means a fresh data is arrived in the Even Buffer
BOOL evenIsBeingPlayed = FALSE; // TRUE means the audio frame in the Even buffer is being played currently  
BOOL oddIsBeingPlayed = FALSE; // TRUE means the audio frame in the Odd buffer is being played currently 
INT16 *nextSample;  // Points to the Sample to be played next.  
UINT8 audioMute = 1; // Holds the status of Mute Control  
UINT16 temp =0; 
/** PRIVATE PROTOTYPES *********************************************/
void BlinkUSBStatus(void);
static void InitializeSystem(void);
void ProcessIO(void);
void UserInit(void);
void Transistion(void);
void YourHighPriorityISRCode();
void YourLowPriorityISRCode();
void USBCBSendResume(void);

/** VECTOR REMAPPING ***********************************************/
#if defined(__18CXX)
	//On PIC18 devices, addresses 0x00, 0x08, and 0x18 are used for
	//the reset, high priority interrupt, and low priority interrupt
	//vectors.  However, the Microchip HID bootloader occupies the
	//0x00-0xFFF program memory region.  Therefore, the bootloader code remaps 
	//these vectors to new locations as indicated below.  This remapping is 
	//only necessary if you wish to be able to (optionally) program the hex file 
	//generated from this project with the USB bootloader.  
	#define REMAPPED_RESET_VECTOR_ADDRESS			0x1000
	#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x1008
	#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x1018
	#define APP_VERSION_ADDRESS                     0x1016 //Fixed location, so the App FW image version can be read by the bootloader.
	#define APP_SIGNATURE_ADDRESS                   0x1006 //Signature location that must be kept at blaknk value (0xFFFF) in this project (has special purpose for bootloader).

    //--------------------------------------------------------------------------
    //Application firmware image version values, as reported to the bootloader
    //firmware.  These are useful so the bootloader can potentially know if the
    //user is trying to program an older firmware image onto a device that
    //has already been programmed with a with a newer firmware image.
    //Format is APP_FIRMWARE_VERSION_MAJOR.APP_FIRMWARE_VERSION_MINOR.
    //The valid minor version is from 00 to 99.  Example:
    //if APP_FIRMWARE_VERSION_MAJOR == 1, APP_FIRMWARE_VERSION_MINOR == 1,
    //then the version is "1.01"
    #define APP_FIRMWARE_VERSION_MAJOR  1   //valid values 0-255
    #define APP_FIRMWARE_VERSION_MINOR  0   //valid values 0-99
    //--------------------------------------------------------------------------
	
	#pragma romdata AppVersionAndSignatureSection = APP_VERSION_ADDRESS
	ROM unsigned char AppVersion[2] = {APP_FIRMWARE_VERSION_MINOR, APP_FIRMWARE_VERSION_MAJOR};
	#pragma romdata AppSignatureSection = APP_SIGNATURE_ADDRESS
	ROM unsigned short int SignaturePlaceholder = 0xFFFF;
	
	#pragma code HIGH_INTERRUPT_VECTOR = 0x08
	void High_ISR (void)
	{
	     _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
	}
	#pragma code LOW_INTERRUPT_VECTOR = 0x18
	void Low_ISR (void)
	{
	     _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
	}
	extern void _startup (void);        // See c018i.c in your C18 compiler dir
	#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
	void _reset (void)
	{
	    _asm goto _startup _endasm
	}
	#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
	void Remapped_High_ISR (void)
	{
	     _asm goto YourHighPriorityISRCode _endasm
	}
	#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
	void Remapped_Low_ISR (void)
	{
	     _asm goto YourLowPriorityISRCode _endasm
	}
	#pragma code
	
	
	//These are your actual interrupt handling routines.
	#pragma interrupt YourHighPriorityISRCode
	void YourHighPriorityISRCode()
	{
		//Check which interrupt flag caused the interrupt.
		//Service the interrupt
		//Clear the interrupt flag
		//Etc.
		if ((PWM_INTERRUPT_FLAG) && (TimerInterruptEnable))
		{	
			PWM_INTERRUPT_FLAG = 0; 
			if (sampleCounter < NO_OF_SAMPLES_IN_A_USB_FRAME)
			{
    			//If the code gets to this point, we are in the middle of an audio playback. 
		        // The Smaples Received Host is PCM (i.e signed 16 bit integer). The PWM running at 48KHz supports only 8 bits/Sample. 
		        // So here we convert each 16 bits Sample into 8 bit Sample. Load the next sample to the PWM Duty Cycle Register. 
		        temp = (*nextSample) + 32768 ;
				DUTY_CYCLE = temp/256;  
				nextSample++;
				sampleCounter++;  
			}	
			else if (evenIsBeingPlayed)
			{
				// If the code gets to this point, we just finished playing Audio Samples in the Even Buffer.
				evenIsBeingPlayed = FALSE; 
				newEvenData = FALSE; 
				if (newOddData)//Check if Audio Samples are waiting to be played in Odd Buffer 
				{
					// We need to start the Playing the audio samples in the Odd buffer immediately. 
					temp = ReceivedDataOddBuffer[0] + 32768; // Load the first Sample.
					DUTY_CYCLE = temp/256;
					nextSample = &ReceivedDataOddBuffer[1];// Set the adress for the second sample.
					oddIsBeingPlayed = TRUE;
					sampleCounter = 1;
				}  
			}
			else if (oddIsBeingPlayed)
			{ 
    			// If the code gets to this point, we just finished playing Audio Samples in the Odd Buffer.
    			oddIsBeingPlayed = 	FALSE;
				newOddData = FALSE;
				if (newEvenData)//Check if Audio Samples are waiting to be played in Even Buffer 
				{
					// We need to start the Playing the audio samples in the Odd buffer immediately. 
					temp = ReceivedDataEvenBuffer[0] + 32768; // Load the first Sample.
					DUTY_CYCLE = temp/256;
					nextSample = &ReceivedDataEvenBuffer[1];// Set the adress for the second sample.
					evenIsBeingPlayed = TRUE; 
					sampleCounter = 1;
				}
			}
			else 
			{
    			//There is no Audio data present in the Even or Odd Buffers. So stop audio play back.
				mStopAudio(); // mask timer interrupt
				sampleCounter = 0;	 
			}
						
		 }	//End of Timer Interrupt
        
	
	}	//This return will be a "retfie fast", since this is in a #pragma interrupt section 
	#pragma interruptlow YourLowPriorityISRCode
	void YourLowPriorityISRCode()
	{
		//Check which interrupt flag caused the interrupt.
		//Service the interrupt
		//Clear the interrupt flag
		//Etc.
		 #if defined(USB_INTERRUPT)
            if((PIE2bits.USBIE == 1) && (PIR2bits.USBIF ==1))
	            USBDeviceTasks();
         #endif
	
	}	//This return will be a "retfie", since this is in a #pragma interruptlow section 

#elif defined(__C30__) || defined __XC16__
    #if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
        /*
         *	ISR JUMP TABLE
         *
         *	It is necessary to define jump table as a function because C30 will
         *	not store 24-bit wide values in program memory as variables.
         *
         *	This function should be stored at an address where the goto instructions 
         *	line up with the remapped vectors from the bootloader's linker script.
         *  
         *  For more information aboubt how to remap the interrupt vectors,
         *  please refer to AN1157.  An example is provided below for the T2
         *  interrupt with a bootloader ending at address 0x1400
         */
//        void __attribute__ ((address(0x1404))) ISRTable(){
//        
//        	asm("reset"); //reset instruction to prevent runaway code
//        	asm("goto %0"::"i"(&_T2Interrupt));  //T2Interrupt's address
//        }
    #endif
    void __attribute__((interrupt, no_auto_psv)) _OC1Interrupt(void)
    {
		PWM_PERIOD_INTERRUPT_FLAG = 0; // Clear the OC1 interrupt flag
		if (sampleCounter < NO_OF_SAMPLES_IN_A_USB_FRAME)
		{
		    //If the code gets to this point, we are in the middle of an audio playback. 
		    // The Smaples Received Host is PCM (i.e signed 16 bit integer). The PWM running at 48KHz supports only 8 bits/Sample. 
		    // So here we convert each 16 bits Sample into 8 bit Sample. Load the next sample to the PWM Duty Cycle Register. 
		    temp = (*nextSample) + 32768 ; 
		    DUTY_CYCLE = temp /256; 
			nextSample++;
			sampleCounter++;  
		}	  
		else if (evenIsBeingPlayed)
		{
		    // If the code gets to this point, we just finished playing Audio Samples in the Even Buffer. 
			evenIsBeingPlayed = FALSE; 
			newEvenData = FALSE;  
			if (newOddData)//Check if Audio Samples are waiting to be played in Odd Buffer 
			{
				// We need to start the Playing the audio samples in the Odd buffer immediately.
				temp = ReceivedDataOddBuffer[0] + 32768;// Load the first Sample.
				DUTY_CYCLE = temp/256; 
				nextSample = &ReceivedDataOddBuffer[1];// Set the adress for the second sample. 
				oddIsBeingPlayed = TRUE;
				sampleCounter = 1;
			}	
		}
		else if (oddIsBeingPlayed)
		{ 
	    	// If the code gets to this point, we just finished playing Audio Samples in the Odd Buffer.
			oddIsBeingPlayed = 	FALSE;
	    	newOddData = FALSE;
			if (newEvenData)//Check if Audio Samples are waiting to be played in Even Buffer
			{
				// We need to start the Playing the audio samples in the Even buffer immediately. 
				temp = ReceivedDataEvenBuffer[0] + 32768;// Load the first Sample.
				DUTY_CYCLE = temp/256;   
				nextSample = &ReceivedDataEvenBuffer[1];// Set the adress for the second sample. 
				evenIsBeingPlayed = TRUE;
				sampleCounter = 1;
			}
			
		}
		else 
		{
    		//There is no Audio data present in the Even or Odd Buffers. So stop audio play back.
			mStopAudio() ;  // mask OC1 interrupt
			sampleCounter = 0;
		}
	}// End of _ISR _OC1Interrupt
	
#elif defined(__C32__)   
 
 	void __ISR(_TIMER_2_VECTOR, ipl7) TimerHandler (void)
 	{
	 	mT2ClearIntFlag(); // Clear the Timer 2 interrupt flag 
		if (sampleCounter < NO_OF_SAMPLES_IN_A_USB_FRAME)
		{
    		//If the code gets to this point, we are in the middle of an audio playback. 
		    // The Smaples Received Host is PCM (i.e signed 16 bit integer). The PWM running at 48KHz supports only 8 bits/Sample. 
		    // So here we convert each 16 bits Sample into 8 bit Sample. Load the next sample to the PWM Duty Cycle Register. 
    		temp = (*nextSample) + 32768 ; 
			DUTY_CYCLE  = temp/256 * MULTIPLY_FACTOR; 
			nextSample++;
			sampleCounter++;  
		}		 
		else if (evenIsBeingPlayed)
		{
    		// If the code gets to this point, we just finished playing Audio Samples in the Even Buffer. 
    		evenIsBeingPlayed = FALSE; 
			newEvenData = FALSE;   
			if (newOddData)//Check if Audio Samples are waiting to be played in Odd Buffer 
			{
				// We need to start the Playing the audio samples in the Odd buffer immediately. 
				temp = ReceivedDataOddBuffer[0]+ 32768 ; 
				DUTY_CYCLE  = temp/256 * MULTIPLY_FACTOR;  // Load the first Sample. 
				nextSample = &ReceivedDataOddBuffer[1]; // Set the adress for the second sample. 
				oddIsBeingPlayed = TRUE; 
				sampleCounter = 1;
			}  
		}
		else if (oddIsBeingPlayed)
		{ 
    		// If the code gets to this point, we just finished playing Audio Samples in the Odd Buffer.
    		oddIsBeingPlayed = 	FALSE;
			newOddData = FALSE;  
			if (newEvenData)//Check if Audio Samples are waiting to be played in Even Buffer 
			{
				// We need to start the Playing the audio samples in the Even buffer immediately.
				temp = ReceivedDataEvenBuffer[0] + 32768; 
				DUTY_CYCLE  = temp/256 * MULTIPLY_FACTOR;  // Load the first Sample. 
				nextSample = &ReceivedDataEvenBuffer[1]; // Set the adress for the second sample.
				evenIsBeingPlayed = TRUE;  
				sampleCounter = 1;
			}
		}
		else 
		{
    		//There is no Audio data present in the Even and Odd Buffers. So stop audio play back. 
			mStopAudio(); // mask timer interrupt
			sampleCounter = 0;
		}
	
  	} // End of __ISR(_TIMER_2_VECTOR, ipl7) TimerHandler 
#endif




/** DECLARATIONS ***************************************************/
#if defined(__18CXX)
#pragma code
#endif

/********************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *******************************************************************/
#if defined(__18CXX)
void main(void)
#else
int main(void)
#endif
{   
    InitializeSystem();

    #if defined(USB_INTERRUPT)
        USBDeviceAttach();
        #if defined(__18CXX)
            SetUsbInterruptToLowPriority(); 
        #endif 
    #endif

    while(1)
    {
        #if defined(USB_POLLING)
		// Check bus status and service USB interrupts.
        USBDeviceTasks(); // Interrupt or polling method.  If using polling, must call
        				  // this function periodically.  This function will take care
        				  // of processing and responding to SETUP transactions 
        				  // (such as during the enumeration process when you first
        				  // plug in).  USB hosts require that USB devices should accept
        				  // and process SETUP packets in a timely fashion.  Therefore,
        				  // when using polling, this function should be called 
        				  // regularly (such as once every 1.8ms or faster** [see 
        				  // inline code comments in usb_device.c for explanation when
        				  // "or faster" applies])  In most cases, the USBDeviceTasks() 
        				  // function does not take very long to execute (ex: <100 
        				  // instruction cycles) before it returns.
        #endif
    				  

		// Application-specific tasks.
		// Application related code may be added here, or in the ProcessIO() function.
        ProcessIO();        
    }//end while
}//end main


/********************************************************************
 * Function:        static void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        InitializeSystem is a centralize initialization
 *                  routine. All required USB initialization routines
 *                  are called from here.
 *
 *                  User application initialization routine should
 *                  also be called from here.                  
 *
 * Note:            None
 *******************************************************************/
static void InitializeSystem(void)
{
    #if (defined(__18CXX) & !defined(PIC18F87J50_PIM) & !defined(PIC18F97J94_FAMILY))
        ADCON1 |= 0x0F;                 // Default all pins to digital
    #elif defined(__C30__) || defined __XC16__
    	#if defined(__PIC24FJ256DA210__) || defined(__PIC24FJ256GB210__)
    		ANSA = 0x0000;
    		ANSB = 0x0000;
    		ANSC = 0x0000;
    		ANSD = 0x0000;
    		ANSE = 0x0000;
    		ANSF = 0x0000;
    		ANSG = 0x0000;
      #elif defined(__dsPIC33EP512MU810__) || defined(__PIC24EP512GU810__)
        	ANSELA = 0x0000;
    		ANSELB = 0x0000;
    		ANSELC = 0x0000;
    		ANSELD = 0x0000;
    		ANSELE = 0x0000;
    		ANSELG = 0x0000;
            
            // The dsPIC33EP512MU810 features Peripheral Pin
            // select. The following statements map UART2 to 
            // device pins which would connect to the the 
            // RX232 transciever on the Explorer 16 board.

             RPINR19 = 0;
             RPINR19 = 0x64;
             RPOR9bits.RP101R = 0x3;
        #else
            AD1PCFGL = 0xFFFF;
        #endif
    #elif defined(__C32__)
        AD1PCFG = 0xFFFF;
    #endif

    #if defined(PIC18F87J50_PIM) || defined(PIC18F46J50_PIM) || defined(PIC18F47J53_PIM)
	//On the PIC18F87J50 Family of USB microcontrollers, the PLL will not power up and be enabled
	//by default, even if a PLL enabled oscillator configuration is selected (such as HS+PLL).
	//This allows the device to power up at a lower initial operating frequency, which can be
	//advantageous when powered from a source which is not gauranteed to be adequate for 48MHz
	//operation.  On these devices, user firmware needs to manually set the OSCTUNE<PLLEN> bit to
	//power up the PLL.
    {
        unsigned int pll_startup_counter = 600;
        OSCTUNEbits.PLLEN = 1;  //Enable the PLL and wait 2+ms until the PLL locks before enabling USB module
        while(pll_startup_counter--);
    }
    //Device switches over automatically to PLL output after PLL is locked and ready.
    #endif

    #if defined(PIC18F97J94_FAMILY)
        //Configure I/O pins for digital input mode.
        ANCON1 = 0xFF;
        ANCON2 = 0xFF;
        ANCON3 = 0xFF;
        #if(USB_SPEED_OPTION == USB_FULL_SPEED)
            //Enable INTOSC active clock tuning if full speed
            ACTCON = 0x90; //Enable active clock self tuning for USB operation
            while(OSCCON2bits.LOCK == 0);   //Make sure PLL is locked/frequency is compatible
                                            //with USB operation (ex: if using two speed 
                                            //startup or otherwise performing clock switching)
        #endif
    #endif
    
    #if defined(PIC18F45K50_FAMILY)
        //Configure oscillator settings for clock settings compatible with USB 
        //operation.  Note: Proper settings depends on USB speed (full or low).
        #if(USB_SPEED_OPTION == USB_FULL_SPEED)
            OSCTUNE = 0x80; //3X PLL ratio mode selected
            OSCCON = 0x70;  //Switch to 16MHz HFINTOSC
            OSCCON2 = 0x10; //Enable PLL, SOSC, PRI OSC drivers turned off
            while(OSCCON2bits.PLLRDY != 1);   //Wait for PLL lock
            *((unsigned char*)0xFB5) = 0x90;  //Enable active clock tuning for USB operation
        #endif
    #endif
    
    
    #if defined(__32MX460F512L__)|| defined(__32MX795F512L__)
    // Configure the PIC32 core for the best performance
    // at the operating frequency. The operating frequency is already set to 
    // 60MHz through Device Config Registers
    SYSTEMConfigPerformance(60000000);
	#endif
    
      #if defined(__dsPIC33EP512MU810__) || defined (__PIC24EP512GU810__)

    // Configure the device PLL to obtain 60 MIPS operation. The crystal
    // frequency is 8MHz. Divide 8MHz by 2, multiply by 60 and divide by
    // 2. This results in Fosc of 120MHz. The CPU clock frequency is
    // Fcy = Fosc/2 = 60MHz. Wait for the Primary PLL to lock and then
    // configure the auxilliary PLL to provide 48MHz needed for USB 
    // Operation.

	PLLFBD = 38;				/* M  = 60	*/
	CLKDIVbits.PLLPOST = 0;		/* N1 = 2	*/
	CLKDIVbits.PLLPRE = 0;		/* N2 = 2	*/
	OSCTUN = 0;			

    /*	Initiate Clock Switch to Primary
     *	Oscillator with PLL (NOSC= 0x3)*/
	
    __builtin_write_OSCCONH(0x03);		
	__builtin_write_OSCCONL(0x01);
	
	while (OSCCONbits.COSC != 0x3);       

    // Configuring the auxiliary PLL, since the primary
    // oscillator provides the source clock to the auxiliary
    // PLL, the auxiliary oscillator is disabled. Note that
    // the AUX PLL is enabled. The input 8MHz clock is divided
    // by 2, multiplied by 24 and then divided by 2. Wait till 
    // the AUX PLL locks.

    ACLKCON3 = 0x24C1;   
    ACLKDIV3 = 0x7;
    
    ACLKCON3bits.ENAPLL = 1;
    while(ACLKCON3bits.APLLCK != 1); 

    #endif

    #if defined(PIC18F87J50_PIM)
	//Configure all I/O pins to use digital input buffers.  The PIC18F87J50 Family devices
	//use the ANCONx registers to control this, which is different from other devices which
	//use the ADCON1 register for this purpose.
    WDTCONbits.ADSHR = 1;			// Select alternate SFR location to access ANCONx registers
    ANCON0 = 0xFF;                  // Default all pins to digital
    ANCON1 = 0xFF;                  // Default all pins to digital
    WDTCONbits.ADSHR = 0;			// Select normal SFR locations
    #endif

    #if defined(PIC18F46J50_PIM) || defined(PIC18F47J53_PIM)
	//Configure all I/O pins to use digital input buffers.  The PIC18F87J50 Family devices
	//use the ANCONx registers to control this, which is different from other devices which
	//use the ADCON1 register for this purpose.
    ANCON0 = 0x7F;                  // All pins to digital (except AN7: temp sensor)
    ANCON1 = 0xBF;                  // Default all pins to digital.  Bandgap on.

    #endif

   #if defined(PIC24FJ64GB004_PIM) || defined(PIC24FJ256DA210_DEV_BOARD)
	//On the PIC24FJ64GB004 Family of USB microcontrollers, the PLL will not power up and be enabled
	//by default, even if a PLL enabled oscillator configuration is selected (such as HS+PLL).
	//This allows the device to power up at a lower initial operating frequency, which can be
	//advantageous when powered from a source which is not gauranteed to be adequate for 32MHz
	//operation.  On these devices, user firmware needs to manually set the CLKDIV<PLLEN> bit to
	//power up the PLL.
    {
        unsigned int pll_startup_counter = 600;
        CLKDIVbits.PLLEN = 1;
        while(pll_startup_counter--);
    }

    //Device switches over automatically to PLL output after PLL is locked and ready.
    #endif


//	The USB specifications require that USB peripheral devices must never source
//	current onto the Vbus pin.  Additionally, USB peripherals should not source
//	current on D+ or D- when the host/hub is not actively powering the Vbus line.
//	When designing a self powered (as opposed to bus powered) USB peripheral
//	device, the firmware should make sure not to turn on the USB module and D+
//	or D- pull up resistor unless Vbus is actively powered.  Therefore, the
//	firmware needs some means to detect when Vbus is being powered by the host.
//	A 5V tolerant I/O pin can be connected to Vbus (through a resistor), and
// 	can be used to detect when Vbus is high (host actively powering), or low
//	(host is shut down or otherwise not supplying power).  The USB firmware
// 	can then periodically poll this I/O pin to know when it is okay to turn on
//	the USB module/D+/D- pull up resistor.  When designing a purely bus powered
//	peripheral device, it is not possible to source current on D+ or D- when the
//	host is not actively providing power on Vbus. Therefore, implementing this
//	bus sense feature is optional.  This firmware can be made to use this bus
//	sense feature by making sure "USE_USB_BUS_SENSE_IO" has been defined in the
//	HardwareProfile.h file.    
    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif
    
//	If the host PC sends a GetStatus (device) request, the firmware must respond
//	and let the host know if the USB peripheral device is currently bus powered
//	or self powered.  See chapter 9 in the official USB specifications for details
//	regarding this request.  If the peripheral device is capable of being both
//	self and bus powered, it should not return a hard coded value for this request.
//	Instead, firmware should check if it is currently self or bus powered, and
//	respond accordingly.  If the hardware has been configured like demonstrated
//	on the PICDEM FS USB Demo Board, an I/O pin can be polled to determine the
//	currently selected power source.  On the PICDEM FS USB Demo Board, "RA2" 
//	is used for	this purpose.  If using this feature, make sure "USE_SELF_POWER_SENSE_IO"
//	has been defined in HardwareProfile - (platform).h, and that an appropriate I/O pin 
//  has been mapped	to it.
    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;	// See HardwareProfile.h
    #endif

    UserInit();
    
    USBDeviceInit();	//usb_device.c.  Initializes USB module SFRs and firmware
    					//variables to known states.
}//end InitializeSystem



/******************************************************************************
 * Function:        void UserInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine should take care of all of the demo code
 *                  initialization that is required.
 *
 * Note:            
 *
 *****************************************************************************/
void UserInit(void)
{
    //Initialize all of the LED pins
    mInitAllLEDs();
    
    //Initialize all of the push buttons
    mInitAllSwitches();

	// Initialize Audio Driver
	mInitAudioDriver();
	mAudioDriverON();

	// Initialize Timer & PWM 
	mInitPWM();
	mInitTimerInterrupt();
	mInitTimer();

    //initialize the variable holding the handle for the last
    // transmission
    USBTxHandle = NULL;
    USBRxEvenHandle = NULL;
	USBRxOddHandle = NULL;
}//end UserInit

/********************************************************************
 * Function:        void UsbAudioInputTerminalControlRequestsHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    If either the USBEP0SendRAMPtr() or USBEP0Receive()
 *                  functions are not called in this function then the 
 *                  requesting the Input Terminal request will be STALLed
 *
 * Overview:        This function is called by the Audio function driver
 *                  in response to a Input Terminal Request. 
 *
 * Note:            This function is called from the stack in
 *                  response of a EP0 packet.  The response to this
 *                  packet should be fast in order to clear EP0 for
 *                  any potential SETUP packets.  Do not call any
 *                  functions or run any algorithms that take a long time
 *                  to execute (>50uSec).  Have any data that would be
 *                  read using one of these commands pre-calculated
 *                  from the main line code and just use this function
 *                  to transfer the data.
 
 *                  Input Terminal Control request fields
 *                  SetupPkt.bRequest holds bRequest(request attribute) 
 *                  SetupPkt.W_Value holds CS(Control Selector)
 *                  SetupPkt.W_Index.byte.HB holds the Input Terminal ID
 *                  SetupPkt.W_Index.byte.LB holds the Interface number
 *                  SetupPkt.wLength holds length of the parameter block 
 *******************************************************************/
 #if defined USB_AUDIO_INPUT_TERMINAL_CONTROL_REQUESTS_HANDLER
 void UsbAudioInputTerminalControlRequestsHandler(void)
 {
     
     
 }    
 #endif 
/********************************************************************
 * Function:        void UsbAudioOutputTerminalControlRequestsHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    If either the USBEP0SendRAMPtr() or USBEP0Receive()
 *                  functions are not called in this function then the 
 *                  requesting the Output Terminal request will be STALLed
 *
 * Overview:        This function is called by the Audio function driver
 *                  in response to a Output Terminal Request. 
 *
 * Note:            This function is called from the stack in
 *                  response of a EP0 packet.  The response to this
 *                  packet should be fast in order to clear EP0 for
 *                  any potential SETUP packets.  Do not call any
 *                  functions or run any algorithms that take a long time
 *                  to execute (>50uSec).  Have any data that would be
 *                  read using one of these commands pre-calculated
 *                  from the main line code and just use this function
 *                  to transfer the data.
 
 *                  Output Terminal Control request fields
 *                  SetupPkt.bRequest holds bRequest(request attribute) 
 *                  SetupPkt.W_Value holds CS(Control Selector)
 *                  SetupPkt.W_Index.byte.HB holds the Output Terminal ID
 *                  SetupPkt.W_Index.byte.LB holds the interface number
 *                  SetupPkt.wLength holds length of the parameter block 
 *******************************************************************/
 #if defined USB_AUDIO_OUTPUT_TERMINAL_CONTROL_REQUESTS_HANDLER
 void UsbAudioOutputTerminalControlRequestsHandler(void)
 {
     
     
 }    
 #endif 
  /********************************************************************
 * Function:        void UsbAudioMixerUnitControlRequestsHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    If either the USBEP0SendRAMPtr() or USBEP0Receive()
 *                  functions are not called in this function then the 
 *                  requesting the Mixer unit request will be STALLed
 *
 * Overview:        This function is called by the Audio function driver
 *                  in response to a Mixer unit Request. 
 *
 * Note:            This function is called from the stack in
 *                  response of a EP0 packet.  The response to this
 *                  packet should be fast in order to clear EP0 for
 *                  any potential SETUP packets.  Do not call any
 *                  functions or run any algorithms that take a long time
 *                  to execute (>50uSec).  Have any data that would be
 *                  read using one of these commands pre-calculated
 *                  from the main line code and just use this function
 *                  to transfer the data.
 
 *                  Mixer Unit Control request fields
 *                  SetupPkt.bRequest holds bRequest(request attribute) 
 *                  SetupPkt.W_Value.byte.HB holds the ICN (Input Channel Number)
 *                  SetupPkt.W_Value.byte.LB holds the OCN (Output Channel Number)
 *                  SetupPkt.W_Index.byte.HB holds the Mixer Unit ID
 *                  SetupPkt.W_Index.byte.LB holds the interface number
 *                  SetupPkt.wLength holds length of the parameter block 
 *******************************************************************/
 #if defined USB_AUDIO_MIXER_UNIT_CONTROL_REQUESTS_HANDLER
 void UsbAudioMixerUnitControlRequestsHandler(void)
 {
     
     
 }    
 #endif 
  /********************************************************************
 * Function:        void UsbAudioSelectorUnitControlRequestsHabdler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    If either the USBEP0SendRAMPtr() or USBEP0Receive()
 *                  functions are not called in this function then the 
 *                  requesting the Selector unit request will be STALLed
 *
 * Overview:        This function is called by the Audio function driver
 *                  in response to a Selector unit Request. 
 *
 * Note:            This function is called from the stack in
 *                  response of a EP0 packet.  The response to this
 *                  packet should be fast in order to clear EP0 for
 *                  any potential SETUP packets.  Do not call any
 *                  functions or run any algorithms that take a long time
 *                  to execute (>50uSec).  Have any data that would be
 *                  read using one of these commands pre-calculated
 *                  from the main line code and just use this function
 *                  to transfer the data.
 
 *                  Selector Unit Control request fields
 *                  SetupPkt.bRequest holds bRequest(request attribute) 
 *                  SetupPkt.W_Index.byte.HB holds the Selector Unit ID
 *                  SetupPkt.W_Index.byte.LB holds the interface number
 *                  SetupPkt.wLength holds length of the parameter block 
 *******************************************************************/
 #if defined USB_AUDIO_SELECTOR_UNIT_CONTROL_REQUESTS_HANDLER
 void UsbAudioSelectorUnitControlRequestsHabdler(void)
 {
     
     
 }    
 #endif 


/********************************************************************
 * Function:        void UsbAudioFeatureUnitControlRequestsHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    If either the USBEP0SendRAMPtr() or USBEP0Receive()
 *                  functions are not called in this function then the 
 *                  requesting the feature unit request will be STALLed
 *
 * Overview:        This function is called by the Audio function driver
 *                  in response to a Feature unit Request. 
 *
 * Note:            This function is called from the stack in
 *                  response of a EP0 packet.  The response to this
 *                  packet should be fast in order to clear EP0 for
 *                  any potential SETUP packets.  Do not call any
 *                  functions or run any algorithms that take a long time
 *                  to execute (>50uSec).  Have any data that would be
 *                  read using one of these commands pre-calculated
 *                  from the main line code and just use this function
 *                  to transfer the data. 
 
 *                  Feature Unit Control request fields
 *                  SetupPkt.bRequest holds bRequest(request attribute) 
 *                  SetupPkt.W_Value.byte.HB holds the CS (Control Selector)
 *                  SetupPkt.W_Value.byte.LB holds the CN (Channel Number)
 *                  SetupPkt.W_Index.byte.HB holds the Feature Unit ID
 *                  SetupPkt.W_Index.byte.LB holds the Interface number
 *                  SetupPkt.wLength holds length of the parameter block                                        
 *******************************************************************/
 #if defined USB_AUDIO_FEATURE_UNIT_CONTROL_REQUESTS_HANDLER
 void UsbAudioFeatureUnitControlRequestsHandler(void)
 {
     switch (SetupPkt.W_Value.byte.HB)
     {
        case MUTE_CONTROL:
            if (SetupPkt.bRequest == SET_CUR)
            {
                USBEP0Receive((BYTE*)&audioMute,SetupPkt.wLength,NULL);  
                if (audioMute == 0x00)
                {
                    mAudioDriverOFF();
                }
                else if (audioMute == 0x01)
                {
                    mAudioDriverON();          
                } 
            }
            else if (SetupPkt.bRequest == GET_CUR)
            {
                // Get Mute Control Status
                CtrlTrfData[0] = audioMute;
    			//CtrlTrfData[1] = 0x00;
    			USBEP0SendRAMPtr((BYTE*)CtrlTrfData, 1, USB_EP0_NO_OPTIONS);
            }
            break;     
        case VOLUME_CONTROL:
            switch(SetupPkt.bRequest)
            {
                case SET_CUR:
                    //Set Current Volume
                    break;
                case SET_MIN:
                    break;
                case SET_MAX:
                    break;
                case SET_RES:
                    break;
                case GET_CUR:
                    // up on this request user needs to send the current volume to the host. 
			        CtrlTrfData[0] = 0x43;
			        CtrlTrfData[1] = 0x00;
			        USBEP0SendRAMPtr((BYTE*)CtrlTrfData, 2, USB_EP0_NO_OPTIONS);
                    break;
                case GET_MIN:
			        CtrlTrfData[0] = 0;
			        CtrlTrfData[1] = 0;
			        USBEP0SendRAMPtr((BYTE*)CtrlTrfData, 2, USB_EP0_NO_OPTIONS); 
                    break;
                case GET_MAX:
			        CtrlTrfData[0] = 0xFF;
			        CtrlTrfData[1] = 0xFF;
			        USBEP0SendRAMPtr((BYTE*)CtrlTrfData, 2, USB_EP0_NO_OPTIONS); 
                    break;
                case GET_RES:
			        CtrlTrfData[0] = 0xFF;
			        CtrlTrfData[1] = 0xFF;
			        USBEP0SendRAMPtr((BYTE*)CtrlTrfData, 2, USB_EP0_NO_OPTIONS); 
                    break;
                default:
                    break;
                }// end of switch(SetupPkt.bRequest)	    
            break;
        case BASS_CONTROL:
             break;
        case MID_CONTROL:
             break;
        case TREBLE_CONTROL:
             break;
        case GRAPHIC_EQUALIZER_CONTROL:
             break;
        case AUTOMATIC_GAIN_CONTROL:
             break;
        case DELAY_CONTROL:
             break;
        case BASS_BOOST_CONTROL:
             break;
        case LOUDNESS_CONTROL:
             break;
        default:
             break;     
       }  //end of switch (SetupPkt.W_Value.byte.HB)  
 
 }//end of void UsbFeatureUnitHandler(void)
 #endif 
 /********************************************************************
 * Function:        void UsbAudioProcessingUnitControlRequestsHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    If either the USBEP0SendRAMPtr() or USBEP0Receive()
 *                  functions are not called in this function then the 
 *                  requesting the Processing unit request will be STALLed
 *
 * Overview:        This function is called by the Audio function driver
 *                  in response to a Processing unit Request. 
 *
 * Note:            This function is called from the stack in
 *                  response of a EP0 packet.  The response to this
 *                  packet should be fast in order to clear EP0 for
 *                  any potential SETUP packets.  Do not call any
 *                  functions or run any algorithms that take a long time
 *                  to execute (>50uSec).  Have any data that would be
 *                  read using one of these commands pre-calculated
 *                  from the main line code and just use this function
 *                  to transfer the data.
 
 *                  Processing Unit Control request fields
 *                  SetupPkt.bRequest holds bRequest(request attribute) 
 *                  SetupPkt.W_Value holds CS(Control Selector)
 *                  SetupPkt.W_Index.byte.HB holds the Processing Unit ID
 *                  SetupPkt.W_Index.byte.LB holds the interface number
 *                  SetupPkt.wLength holds length of the parameter block 
 *******************************************************************/
 #if defined USB_AUDIO_PROCESSING_UNIT_CONTROL_REQUESTS_HANDLER
 void UsbAudioProcessingUnitControlRequestsHandler(void)
 {
 }
 #endif 
 /********************************************************************
 * Function:        void UsbAudioExtensionUnitControlRequestsHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    If either the USBEP0SendRAMPtr() or USBEP0Receive()
 *                  functions are not called in this function then the 
 *                  requesting the Extension unit request will be STALLed
 *
 * Overview:        This function is called by the Audio function driver
 *                  in response to a Extension unit Request. 
 *
 * Note:            This function is called from the stack in
 *                  response of a EP0 packet.  The response to this
 *                  packet should be fast in order to clear EP0 for
 *                  any potential SETUP packets.  Do not call any
 *                  functions or run any algorithms that take a long time
 *                  to execute (>50uSec).  Have any data that would be
 *                  read using one of these commands pre-calculated
 *                  from the main line code and just use this function
 *                  to transfer the data.
 
 *                  Extension Unit Control request fields
 *                  SetupPkt.bRequest holds bRequest(request attribute) 
 *                  SetupPkt.W_Value holds CS(Control Selector)
 *                  SetupPkt.W_Index.byte.HB holds the Extension Unit ID
 *                  SetupPkt.W_Index.byte.LB holds the interface number
 *                  SetupPkt.wLength holds length of the parameter block 
 *******************************************************************/
 #if defined USB_AUDIO_EXTENSION_UNIT_CONTROL_REQUESTS_HANDLER
 void UsbAudioExtensionUnitControlRequestsHandler(void)
 {
 }
 #endif 
 /********************************************************************
 * Function:        void UsbAudioInterfaceControlRequestsHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    If either the USBEP0SendRAMPtr() or USBEP0Receive()
 *                  functions are not called in this function then the 
 *                  requesting the feature unit request will be STALLed
 *
 * Overview:        This function is called by the Audio function driver
 *                  in response to a Feature unit Request. 
 *
 * Note:            This function is called from the stack in
 *                  response of a EP0 packet.  The response to this
 *                  packet should be fast in order to clear EP0 for
 *                  any potential SETUP packets.  Do not call any
 *                  functions or run any algorithms that take a long time
 *                  to execute (>50uSec).  Have any data that would be
 *                  read using one of these commands pre-calculated
 *                  from the main line code and just use this function
 *                  to transfer the data.
 *******************************************************************/
 #if defined USB_AUDIO_INTRFACE_CONTROL_REQUESTS_HANDLER
 void UsbAudioInterfaceControlRequestsHandler(void)
 {
 }
 #endif       
 /********************************************************************
 * Function:        void UsbAudioEndpointControlRequestsHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    If either the USBEP0SendRAMPtr() or USBEP0Receive()
 *                  functions are not called in this function then the 
 *                  requesting the feature unit request will be STALLed
 *
 * Overview:        This function is called by the Audio function driver
 *                  in response to a Feature unit Request. 
 *
 * Note:            This function is called from the stack in
 *                  response of a EP0 packet.  The response to this
 *                  packet should be fast in order to clear EP0 for
 *                  any potential SETUP packets.  Do not call any
 *                  functions or run any algorithms that take a long time
 *                  to execute (>50uSec).  Have any data that would be
 *                  read using one of these commands pre-calculated
 *                  from the main line code and just use this function
 *                  to transfer the data.
 
 *                  Endpoint Control request fields
 *                  SetupPkt.bRequest holds bRequest(request attribute) 
 *                  SetupPkt.W_Value holds CS(Control Selector)
 *                  SetupPkt.W_Index holds endpoint
 *                  SetupPkt.wLength holds length of the parameter block
 *******************************************************************/
 #if defined USB_AUDIO_ENDPOINT_CONTROL_REQUESTS_HANDLER
 void UsbAudioEndpointControlRequestsHandler(void)
 {
 }
 #endif 
 /********************************************************************
 * Function:        void UsbAudioMemoryRequestsHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    If either the USBEP0SendRAMPtr() or USBEP0Receive()
 *                  functions are not called in this function then the 
 *                  requesting the feature unit request will be STALLed
 *
 * Overview:        This function is called by the Audio function driver
 *                  in response to a Feature unit Request. 
 *
 * Note:            This function is called from the stack in
 *                  response of a EP0 packet.  The response to this
 *                  packet should be fast in order to clear EP0 for
 *                  any potential SETUP packets.  Do not call any
 *                  functions or run any algorithms that take a long time
 *                  to execute (>50uSec).  Have any data that would be
 *                  read using one of these commands pre-calculated
 *                  from the main line code and just use this function
 *                  to transfer the data.
 
 *                  Memory Requests fields
 *                  SetupPkt.bRequest holds bRequest(request attribute) 
 *                  SetupPkt.W_Value holds offset
 *                  SetupPkt.W_Index holds endpoint
 *                  SetupPkt.W_Index.byte.HB holds the Entity ID
 *                  SetupPkt.W_Index.byte.LB holds the interface number
 *                  SetupPkt.wLength holds length of the parameter block               
 *******************************************************************/
 #if defined USB_AUDIO_MEMORY_REQUESTS_HANDLER
 void UsbAudioMemoryRequestsHandler(void)
 {
 }
 #endif   
/********************************************************************
 * Function:        void UsbAudioStatusRequestsHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    If either the USBEP0SendRAMPtr() or USBEP0Receive()
 *                  functions are not called in this function then the 
 *                  requesting the feature unit request will be STALLed
 *
 * Overview:        This function is called by the Audio function driver
 *                  in response to a Feature unit Request. 
 *
 * Note:            This function is called from the stack in
 *                  response of a EP0 packet.  The response to this
 *                  packet should be fast in order to clear EP0 for
 *                  any potential SETUP packets.  Do not call any
 *                  functions or run any algorithms that take a long time
 *                  to execute (>50uSec).  Have any data that would be
 *                  read using one of these commands pre-calculated
 *                  from the main line code and just use this function
 *                  to transfer the data.
 
 *                  Get Status Requests fields
 *                  SetupPkt.bRequest holds bRequest(request attribute) 
 *                  SetupPkt.W_Index holds endpoint
 *                  SetupPkt.W_Index.byte.HB holds the Entity ID
 *                  SetupPkt.W_Index.byte.LB holds the interface number
 *                  SetupPkt.wLength holds length of the parameter block 
 *******************************************************************/
 #if defined USB_AUDIO_STATUS_REQUESTS_HANDLER
 void UsbAudioStatusRequestsHandler(void)
 {
 }
 #endif 
     
 
/********************************************************************
 * Function:        void ProcessIO(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is a place holder for other user
 *                  routines. It is a mixture of both USB and
 *                  non-USB tasks.
 *
 * Note:            None
 *******************************************************************/
void ProcessIO(void)
{   
   
    //Blink the LEDs according to the USB device status
    BlinkUSBStatus();

    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;
    
    //This demo makes full use of the "ping-pong" buffering features implemented 
    //by the USB module hardware.  Ping-pong buffering is like a "DMA FIFO".  
    //It enables up to two transactions to be queued up on a single endpoint.
    //While the firmware may be processing and using previously received data,
    //the USB module hardware can be configured to still receive the next packet
    //of data that may be sent from the host.Please refer "WinUSB High Bandwidth Demo" for better 
    // understanding of Ping pong Buffering. 
 	if (receivedDataEvenNeedsServicingNext == TRUE) //Check which buffer (even/odd) the next set of data is going to arrive in
	{
    	if(!USBHandleBusy(USBRxEvenHandle))//Check if the endpoint has received any data from the host.
    	{
   			//If the code gets to this point, we have received a USB frame from the host 
   			//with Audio Data in the Even Buffer. 
			newEvenData = TRUE; 
			if (oddIsBeingPlayed == FALSE)// Start the Audio Playback for the Even buffer only if the Odd buffer is not being played.   
			{		
				evenIsBeingPlayed = TRUE;
				nextSample = &ReceivedDataEvenBuffer[0];// load the start address of the Audio data for Playback.   
				sampleCounter =0;
				mStartAudio(); // Unmask the Timer2 or Output Compare 1(in case of PIC24F) interrupt to start-
				// the Audio Play back.    	
			}
        	//Get ready for next packet (this will overwrite the old data)
        	USBRxEvenHandle = USBRxOnePacket(AS_EP,(BYTE*)&ReceivedDataEvenBuffer,BYTES_PER_USB_FRAME);
			receivedDataEvenNeedsServicingNext = FALSE; 
		}
    }
	else //else Odd Endpoint needs servicing next
	{
		if(!USBHandleBusy(USBRxOddHandle))//Check if the endpoint has received any data from the host.
		{
			//If the code gets to this point, we have received a USB frame from the host 
   			//with Audio Data in the Even Buffer. 
			newOddData = TRUE;
			if (evenIsBeingPlayed == FALSE)// Start the Audio Playback for the Odd buffer only if the Even buffer is not being played.   
			{
				oddIsBeingPlayed = TRUE;
				nextSample = &ReceivedDataOddBuffer[0];// load the start address of the Audio data for Playback.   
				sampleCounter =0;
				mStartAudio();// Unmask the Timer2 or Output Compare 1(in case of PIC24F) interrupt to start-
				// the Audio Play back.  
			}
			//Get ready for next packet (this will overwrite the old data)
        	USBRxOddHandle = USBRxOnePacket(AS_EP,(BYTE*)&ReceivedDataOddBuffer,BYTES_PER_USB_FRAME);
			receivedDataEvenNeedsServicingNext = TRUE; 	
		}
	}	

}//end ProcessIO

/********************************************************************
 * Function:        void BlinkUSBStatus(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        BlinkUSBStatus turns on and off LEDs 
 *                  corresponding to the USB device state.
 *
 * Note:            mLED macros can be found in HardwareProfile.h
 *                  USBDeviceState is declared and updated in
 *                  usb_device.c.
 *******************************************************************/
void BlinkUSBStatus(void)
{
    static WORD led_count=0;
    
    if(led_count == 0)led_count = 10000U;
    led_count--;

    #define mLED_Both_Off()         {mLED_1_Off();mLED_2_Off();}
    #define mLED_Both_On()          {mLED_1_On();mLED_2_On();}
    #define mLED_Only_1_On()        {mLED_1_On();mLED_2_Off();}
    #define mLED_Only_2_On()        {mLED_1_Off();mLED_2_On();}

    if(USBSuspendControl == 1)
    {
        if(led_count==0)
        {
            mLED_1_Toggle();
            if(mGetLED_1())
            {
                mLED_2_On();
            }
            else
            {
                mLED_2_Off();
            }
        }//end if
    }
    else
    {
        if(USBDeviceState == DETACHED_STATE)
        {
            mLED_Both_Off();
        }
        else if(USBDeviceState == ATTACHED_STATE)
        {
            mLED_Both_On();
        }
        else if(USBDeviceState == POWERED_STATE)
        {
            mLED_Only_1_On();
        }
        else if(USBDeviceState == DEFAULT_STATE)
        {
            mLED_Only_2_On();
        }
        else if(USBDeviceState == ADDRESS_STATE)
        {
            if(led_count == 0)
            {
                mLED_1_Toggle();
                mLED_2_Off();
            }//end if
        }
        else if(USBDeviceState == CONFIGURED_STATE)
        {
            if(led_count==0)
            {
                mLED_1_Toggle();
                if(mGetLED_1())
                {
                    mLED_2_Off();
                }
                else
                {
                    mLED_2_On();
                }
            }//end if
        }//end if(...)
    }//end if(UCONbits.SUSPND...)

}//end BlinkUSBStatus

// ******************************************************************************************************
// ************** USB Callback Functions ****************************************************************
// ******************************************************************************************************
// The USB firmware stack will call the callback functions USBCBxxx() in response to certain USB related
// events.  For example, if the host PC is powering down, it will stop sending out Start of Frame (SOF)
// packets to your device.  In response to this, all USB devices are supposed to decrease their power
// consumption from the USB Vbus to <2.5mA* each.  The USB module detects this condition (which according
// to the USB specifications is 3+ms of no bus activity/SOF packets) and then calls the USBCBSuspend()
// function.  You should modify these callback functions to take appropriate actions for each of these
// conditions.  For example, in the USBCBSuspend(), you may wish to add code that will decrease power
// consumption from Vbus to <2.5mA (such as by clock switching, turning off LEDs, putting the
// microcontroller to sleep, etc.).  Then, in the USBCBWakeFromSuspend() function, you may then wish to
// add code that undoes the power saving things done in the USBCBSuspend() function.

// The USBCBSendResume() function is special, in that the USB stack will not automatically call this
// function.  This function is meant to be called from the application firmware instead.  See the
// additional comments near the function.

// Note *: The "usb_20.pdf" specs indicate 500uA or 2.5mA, depending upon device classification. However,
// the USB-IF has officially issued an ECN (engineering change notice) changing this to 2.5mA for all 
// devices.  Make sure to re-download the latest specifications to get all of the newest ECNs.

/******************************************************************************
 * Function:        void USBCBSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Call back that is invoked when a USB suspend is detected
 *
 * Note:            None
 *****************************************************************************/
void USBCBSuspend(void)
{
	//Example power saving code.  Insert appropriate code here for the desired
	//application behavior.  If the microcontroller will be put to sleep, a
	//process similar to that shown below may be used:
	
	//ConfigureIOPinsForLowPower();
	//SaveStateOfAllInterruptEnableBits();
	//DisableAllInterruptEnableBits();
	//EnableOnlyTheInterruptsWhichWillBeUsedToWakeTheMicro();	//should enable at least USBActivityIF as a wake source
	//Sleep();
	//RestoreStateOfAllPreviouslySavedInterruptEnableBits();	//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.
	//RestoreIOPinsToNormal();									//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.

	//IMPORTANT NOTE: Do not clear the USBActivityIF (ACTVIF) bit here.  This bit is 
	//cleared inside the usb_device.c file.  Clearing USBActivityIF here will cause 
	//things to not work as intended.	
	

    #if defined(__C30__) || defined __XC16__
    #if 0
        U1EIR = 0xFFFF;
        U1IR = 0xFFFF;
        U1OTGIR = 0xFFFF;
        IFS5bits.USB1IF = 0;
        IEC5bits.USB1IE = 1;
        U1OTGIEbits.ACTVIE = 1;
        U1OTGIRbits.ACTVIF = 1;
        TRISA &= 0xFF3F;
        LATAbits.LATA6 = 1;
        Sleep();
        LATAbits.LATA6 = 0;
    #endif
    #endif
}

/******************************************************************************
 * Function:        void USBCBWakeFromSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The host may put USB peripheral devices in low power
 *					suspend mode (by "sending" 3+ms of idle).  Once in suspend
 *					mode, the host may wake the device back up by sending non-
 *					idle state signalling.
 *					
 *					This call back is invoked when a wakeup from USB suspend 
 *					is detected.
 *
 * Note:            None
 *****************************************************************************/
void USBCBWakeFromSuspend(void)
{
	// If clock switching or other power savings measures were taken when
	// executing the USBCBSuspend() function, now would be a good time to
	// switch back to normal full power run mode conditions.  The host allows
	// 10+ milliseconds of wakeup time, after which the device must be 
	// fully back to normal, and capable of receiving and processing USB
	// packets.  In order to do this, the USB module must receive proper
	// clocking (IE: 48MHz clock must be available to SIE for full speed USB
	// operation).  
	// Make sure the selected oscillator settings are consistent with USB 
    // operation before returning from this function.
}

/********************************************************************
 * Function:        void USBCB_SOF_Handler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB host sends out a SOF packet to full-speed
 *                  devices every 1 ms. This interrupt may be useful
 *                  for isochronous pipes. End designers should
 *                  implement callback routine as necessary.
 *
 * Note:            None
 *******************************************************************/
void USBCB_SOF_Handler(void)
{
    	
}

/*******************************************************************
 * Function:        void USBCBErrorHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The purpose of this callback is mainly for
 *                  debugging during development. Check UEIR to see
 *                  which error causes the interrupt.
 *
 * Note:            None
 *******************************************************************/
void USBCBErrorHandler(void)
{
    // No need to clear UEIR to 0 here.
    // Callback caller is already doing that.

	// Typically, user firmware does not need to do anything special
	// if a USB error occurs.  For example, if the host sends an OUT
	// packet to your device, but the packet gets corrupted (ex:
	// because of a bad connection, or the user unplugs the
	// USB cable during the transmission) this will typically set
	// one or more USB error interrupt flags.  Nothing specific
	// needs to be done however, since the SIE will automatically
	// send a "NAK" packet to the host.  In response to this, the
	// host will normally retry to send the packet again, and no
	// data loss occurs.  The system will typically recover
	// automatically, without the need for application firmware
	// intervention.
	
	// Nevertheless, this callback function is provided, such as
	// for debugging purposes.
}


/*******************************************************************
 * Function:        void USBCBCheckOtherReq(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        When SETUP packets arrive from the host, some
 * 					firmware must process the request and respond
 *					appropriately to fulfill the request.  Some of
 *					the SETUP packets will be for standard
 *					USB "chapter 9" (as in, fulfilling chapter 9 of
 *					the official USB specifications) requests, while
 *					others may be specific to the USB device class
 *					that is being implemented.  For example, a HID
 *					class device needs to be able to respond to
 *					"GET REPORT" type of requests.  This
 *					is not a standard USB chapter 9 request, and 
 *					therefore not handled by usb_device.c.  Instead
 *					this request should be handled by class specific 
 *					firmware, such as that contained in usb_function_hid.c.
 *
 * Note:            None
 *******************************************************************/
void USBCBCheckOtherReq(void)
{
	 USBCheckAudioRequest();
}//end


/*******************************************************************
 * Function:        void USBCBStdSetDscHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USBCBStdSetDscHandler() callback function is
 *					called when a SETUP, bRequest: SET_DESCRIPTOR request
 *					arrives.  Typically SET_DESCRIPTOR requests are
 *					not used in most applications, and it is
 *					optional to support this type of request.
 *
 * Note:            None
 *******************************************************************/
void USBCBStdSetDscHandler(void)
{
    // Must claim session ownership if supporting this request
}//end


/*******************************************************************
 * Function:        void USBCBInitEP(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the device becomes
 *                  initialized, which occurs after the host sends a
 * 					SET_CONFIGURATION (wValue not = 0) request.  This 
 *					callback function should initialize the endpoints 
 *					for the device's usage according to the current 
 *					configuration.
 *
 * Note:            None
 *******************************************************************/
void USBCBInitEP(void)
{
    //enable the Audio Streaming OUT endpoint
    USBEnableEndpoint(AS_EP,USB_OUT_ENABLED|USB_IN_ENABLED|USB_DISALLOW_SETUP);

    //Prepare the OUT endpoints to receive the first packets from the host.
    USBRxEvenHandle = USBRxOnePacket(AS_EP,(BYTE*)&ReceivedDataEvenBuffer,BYTES_PER_USB_FRAME); //First Audio Packet sent will arrive in the even buffer.
	USBRxOddHandle = USBRxOnePacket(AS_EP,(BYTE*)&ReceivedDataOddBuffer,BYTES_PER_USB_FRAME); //Second Audio Packet sent will arrive in the even buffer.
	receivedDataEvenNeedsServicingNext = TRUE;	//Used to keep track of which buffer will contain the next sequential data packet.
}

/********************************************************************
 * Function:        void USBCBSendResume(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB specifications allow some types of USB
 * 					peripheral devices to wake up a host PC (such
 *					as if it is in a low power suspend to RAM state).
 *					This can be a very useful feature in some
 *					USB applications, such as an Infrared remote
 *					control	receiver.  If a user presses the "power"
 *					button on a remote control, it is nice that the
 *					IR receiver can detect this signalling, and then
 *					send a USB "command" to the PC to wake up.
 *					
 *					The USBCBSendResume() "callback" function is used
 *					to send this special USB signalling which wakes 
 *					up the PC.  This function may be called by
 *					application firmware to wake up the PC.  This
 *					function will only be able to wake up the host if
 *                  all of the below are true:
 *					
 *					1.  The USB driver used on the host PC supports
 *						the remote wakeup capability.
 *					2.  The USB configuration descriptor indicates
 *						the device is remote wakeup capable in the
 *						bmAttributes field.
 *					3.  The USB host PC is currently sleeping,
 *						and has previously sent your device a SET 
 *						FEATURE setup packet which "armed" the
 *						remote wakeup capability.   
 *
 *                  If the host has not armed the device to perform remote wakeup,
 *                  then this function will return without actually performing a
 *                  remote wakeup sequence.  This is the required behavior, 
 *                  as a USB device that has not been armed to perform remote 
 *                  wakeup must not drive remote wakeup signalling onto the bus;
 *                  doing so will cause USB compliance testing failure.
 *                  
 *					This callback should send a RESUME signal that
 *                  has the period of 1-15ms.
 *
 * Note:            This function does nothing and returns quickly, if the USB
 *                  bus and host are not in a suspended condition, or are 
 *                  otherwise not in a remote wakeup ready state.  Therefore, it
 *                  is safe to optionally call this function regularly, ex: 
 *                  anytime application stimulus occurs, as the function will
 *                  have no effect, until the bus really is in a state ready
 *                  to accept remote wakeup. 
 *
 *                  When this function executes, it may perform clock switching,
 *                  depending upon the application specific code in 
 *                  USBCBWakeFromSuspend().  This is needed, since the USB
 *                  bus will no longer be suspended by the time this function
 *                  returns.  Therefore, the USB module will need to be ready
 *                  to receive traffic from the host.
 *
 *                  The modifiable section in this routine may be changed
 *                  to meet the application needs. Current implementation
 *                  temporary blocks other functions from executing for a
 *                  period of ~3-15 ms depending on the core frequency.
 *
 *                  According to USB 2.0 specification section 7.1.7.7,
 *                  "The remote wakeup device must hold the resume signaling
 *                  for at least 1 ms but for no more than 15 ms."
 *                  The idea here is to use a delay counter loop, using a
 *                  common value that would work over a wide range of core
 *                  frequencies.
 *                  That value selected is 1800. See table below:
 *                  ==========================================================
 *                  Core Freq(MHz)      MIP         RESUME Signal Period (ms)
 *                  ==========================================================
 *                      48              12          1.05
 *                       4              1           12.6
 *                  ==========================================================
 *                  * These timing could be incorrect when using code
 *                    optimization or extended instruction mode,
 *                    or when having other interrupts enabled.
 *                    Make sure to verify using the MPLAB SIM's Stopwatch
 *                    and verify the actual signal on an oscilloscope.
 *******************************************************************/
void USBCBSendResume(void)
{
    static WORD delay_count;
    
    //First verify that the host has armed us to perform remote wakeup.
    //It does this by sending a SET_FEATURE request to enable remote wakeup,
    //usually just before the host goes to standby mode (note: it will only
    //send this SET_FEATURE request if the configuration descriptor declares
    //the device as remote wakeup capable, AND, if the feature is enabled
    //on the host (ex: on Windows based hosts, in the device manager 
    //properties page for the USB device, power management tab, the 
    //"Allow this device to bring the computer out of standby." checkbox 
    //should be checked).
    if(USBGetRemoteWakeupStatus() == TRUE) 
    {
        //Verify that the USB bus is in fact suspended, before we send
        //remote wakeup signalling.
        if(USBIsBusSuspended() == TRUE)
        {
            USBMaskInterrupts();
            
            //Clock switch to settings consistent with normal USB operation.
            USBCBWakeFromSuspend();
            USBSuspendControl = 0; 
            USBBusIsSuspended = FALSE;  //So we don't execute this code again, 
                                        //until a new suspend condition is detected.

            //Section 7.1.7.7 of the USB 2.0 specifications indicates a USB
            //device must continuously see 5ms+ of idle on the bus, before it sends
            //remote wakeup signalling.  One way to be certain that this parameter
            //gets met, is to add a 2ms+ blocking delay here (2ms plus at 
            //least 3ms from bus idle to USBIsBusSuspended() == TRUE, yeilds
            //5ms+ total delay since start of idle).
            delay_count = 3600U;        
            do
            {
                delay_count--;
            }while(delay_count);
            
            //Now drive the resume K-state signalling onto the USB bus.
            USBResumeControl = 1;       // Start RESUME signaling
            delay_count = 1800U;        // Set RESUME line for 1-13 ms
            do
            {
                delay_count--;
            }while(delay_count);
            USBResumeControl = 0;       //Finished driving resume signalling

            USBUnmaskInterrupts();
        }
    }
}


/*******************************************************************
 * Function:        BOOL USER_USB_CALLBACK_EVENT_HANDLER(
 *                        USB_EVENT event, void *pdata, WORD size)
 *
 * PreCondition:    None
 *
 * Input:           USB_EVENT event - the type of event
 *                  void *pdata - pointer to the event data
 *                  WORD size - size of the event data
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called from the USB stack to
 *                  notify a user application that a USB event
 *                  occured.  This callback is in interrupt context
 *                  when the USB_INTERRUPT option is selected.
 *
 * Note:            None
 *******************************************************************/
BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size)
{
    switch((INT)event)
    {
        case EVENT_TRANSFER:
            //Add application specific callback task or callback function here if desired.
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER_TERMINATED:
            //Add application specific callback task or callback function here if desired.
            //The EVENT_TRANSFER_TERMINATED event occurs when the host performs a CLEAR
            //FEATURE (endpoint halt) request on an application endpoint which was 
            //previously armed (UOWN was = 1).  Here would be a good place to:
            //1.  Determine which endpoint the transaction that just got terminated was 
            //      on, by checking the handle value in the *pdata.
            //2.  Re-arm the endpoint if desired (typically would be the case for OUT 
            //      endpoints).
            break;
        default:
            break;
    }      
    return TRUE; 
}


/** EOF main.c *************************************************/
#endif
