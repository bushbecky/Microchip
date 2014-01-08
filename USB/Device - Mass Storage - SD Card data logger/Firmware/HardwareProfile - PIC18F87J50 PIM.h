/********************************************************************
 FileName:     	HardwareProfile - PIC18F87J50 PIM.h
 Dependencies:	See INCLUDES section
 Processor:	PIC18 USB Microcontrollers
 Hardware:	PIC18F87J50 PIM
 Compiler:  	Microchip C18
 Company:		Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the �Company�) for its PIC� Microcontroller is intended and
 supplied to you, the Company�s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.0   11/19/2004   Initial release
  2.1   02/26/2007   Updated for simplicity and to use common
                     coding style
  2.3   09/15/2008   Broke out each hardware platform into its own
                     "HardwareProfile - xxx.h" file
********************************************************************/

#ifndef HARDWARE_PROFILE_PIC18F87J50_PIM_H
#define HARDWARE_PROFILE_PIC18F87J50_PIM_H

    /*******************************************************************/
    /******** USB stack hardware selection options *********************/
    /*******************************************************************/
    //This section is the set of definitions required by the MCHPFSUSB
    //  framework.  These definitions tell the firmware what mode it is
    //  running in, and where it can find the results to some information
    //  that the stack needs.
    //These definitions are required by every application developed with
    //  this revision of the MCHPFSUSB framework.  Please review each
    //  option carefully and determine which options are desired/required
    //  for your application.

    /** USB ************************************************************/
    //The PIC18F87J50 FS USB Plug-In Module supports the USE_USB_BUS_SENSE_IO
    //feature.  The USE_SELF_POWER_SENSE_IO feature is not implemented on the
    //circuit board, so the USE_SELF_POWER_SENSE_IO define should always be
    //commented for this hardware platform.

    //#define USE_SELF_POWER_SENSE_IO
    #define tris_self_power     TRISAbits.TRISA2    // Input
    #if defined(USE_SELF_POWER_SENSE_IO)
    #define self_power          PORTAbits.RA2
    #else
    #define self_power          1
    #endif

    //#define USE_USB_BUS_SENSE_IO		//JP1 must be in R-U position to use this feature on this board	
    #define tris_usb_bus_sense  TRISBbits.TRISB5    // Input
    #if defined(USE_USB_BUS_SENSE_IO)
    #define USB_BUS_SENSE       PORTBbits.RB5
    #else
    #define USB_BUS_SENSE       1
    #endif
 
    //Uncomment this to make the output HEX of this project 
    //   to be able to be bootloaded using the HID bootloader
	#define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER		

    /*******************************************************************/
    /******** MDD File System selection options ************************/
    /*******************************************************************/
    #define USE_PIC18
    #define USE_SD_INTERFACE_WITH_SPI

    // Chip Select Signal
    #define SD_CS               PORTBbits.RB3
    #define SD_CS_TRIS          TRISBbits.TRISB3
    
    // Card detect signal
    #define SD_CD               PORTBbits.RB4
    #define SD_CD_TRIS          TRISBbits.TRISB4
    
    // Write protect signal
    #define SD_WE               PORTAbits.RA4
    #define SD_WE_TRIS          TRISAbits.TRISA4
    
    // Registers for the SPI module you want to use
    #define SPICON1             SSP1CON1
    #define SPISTAT             SSP1STAT
    #define SPIBUF              SSP1BUF
    #define SPISTAT_RBF         SSP1STATbits.BF
    #define SPICON1bits         SSP1CON1bits
    #define SPISTATbits         SSP1STATbits
	#define SPI_INTERRUPT_FLAG_ASM  PIR1, 3 
    #define SPI_INTERRUPT_FLAG  PIR1bits.SSPIF   

    // Defines for the HPC Explorer board
    #define SPICLOCK            TRISCbits.TRISC3
    #define SPIIN               TRISCbits.TRISC4
    #define SPIOUT              TRISCbits.TRISC5

    // Latch pins for SCK/SDI/SDO lines
    #define SPICLOCKLAT         LATCbits.LATC3
    #define SPIINLAT            LATCbits.LATC4
    #define SPIOUTLAT           LATCbits.LATC5

    // Port pins for SCK/SDI/SDO lines
    #define SPICLOCKPORT        PORTCbits.RC3
    #define SPIINPORT           PORTCbits.RC4
    #define SPIOUTPORT          PORTCbits.RC5

    #define SPIENABLE           SSPCON1bits.SSPEN

    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/

    /** Board definition ***********************************************/
    //These defintions will tell the main() function which board is
    //  currently selected.  This will allow the application to add
    //  the correct configuration bits as wells use the correct
    //  initialization functions for the board.  These defitions are only
    //  required in the stack provided demos.  They are not required in
    //  final application design.
    #define DEMO_BOARD PIC18F87J50_PIM
    #define PIC18F87J50_PIM
    #define CLOCK_FREQ 48000000
    #define GetSystemClock()  CLOCK_FREQ   
    #define GetInstructionClock() CLOCK_FREQ   
    
    /** LED ************************************************************/
    #define mInitAllLEDs()      {LATE &= 0xFC; TRISE &= 0xFC; LATD &= 0xF3; TRISD &= 0xF3;}
    
    #define mLED_1              LATEbits.LATE0
    #define mLED_2              LATEbits.LATE1
    #define mLED_3              LATDbits.LATD2
    #define mLED_4              LATDbits.LATD3
    
    #define mGetLED_1()         mLED_1
    #define mGetLED_2()         mLED_2
    #define mGetLED_3()         mLED_3
    #define mGetLED_4()         mLED_4

    #define mLED_1_On()         mLED_1 = 1;
    #define mLED_2_On()         mLED_2 = 1;
    #define mLED_3_On()         mLED_3 = 1;
    #define mLED_4_On()         mLED_4 = 1;
    
    #define mLED_1_Off()        mLED_1 = 0;
    #define mLED_2_Off()        mLED_2 = 0;
    #define mLED_3_Off()        mLED_3 = 0;
    #define mLED_4_Off()        mLED_4 = 0;
    
    #define mLED_1_Toggle()     mLED_1 = !mLED_1;
    #define mLED_2_Toggle()     mLED_2 = !mLED_2;
    #define mLED_3_Toggle()     mLED_3 = !mLED_3;
    #define mLED_4_Toggle()     mLED_4 = !mLED_4;
    
    /** SWITCH *********************************************************/
    //use RB0 in this case instead of RB4 so that it is the button on
    //  the HPC explorer instead of the PIM
    #define mInitAllSwitches()  TRISBbits.TRISB0=1;
    #define mInitSwitch2()      TRISBbits.TRISB0=1;
    #define mInitSwitch3()      TRISBbits.TRISB0=1;
    #define sw2                 PORTBbits.RB0
    #define sw3                 PORTBbits.RB0
    
    /** POT ************************************************************/
    #define mInitPOT()          {TRISAbits.TRISA0=1;			\
    							 WDTCONbits.ADSHR = 1;			\
    							 ANCON0bits.PCFG0 = 1;			\
    							 WDTCONbits.ADSHR = 0;			\
    							 ADCON0=0x01;					\
    							 ADCON1=0xBE;}		// POT on HPC Explorer			
    
    /** I 2 C   T E M P   S E N S E *************************************/
    #define	mInitI2CPins()		TRISC |= 0x18;		// RC3 and RC4 are I2C

    
    
    /** SPI : Chip Select Lines ****************************************/
    #define tris_cs_temp_sensor TRISBbits.TRISB2    // Output
    #define cs_temp_sensor      LATBbits.LATB2
    
    #define tris_cs_sdmmc       TRISBbits.TRISB3    // Output
    #define cs_sdmmc            LATBbits.LATB3
    
    /** SD/MMC *********************************************************/
    #define TRIS_CARD_DETECT    TRISBbits.TRISB4    // Input
    #define CARD_DETECT         PORTBbits.RB4
    
    #define TRIS_WRITE_DETECT   TRISAbits.TRISA4    // Input
    #define WRITE_DETECT        PORTAbits.RA4
  
    /** MDD File System error checking *********************************/
    // Will generate an error if the clock speed is too low to interface to the card
    #if (GetSystemClock() < 400000)
        #error System clock speed must exceed 400 kHz
    #endif   

    /** I/O pin definitions ********************************************/
    #define INPUT_PIN 1
    #define OUTPUT_PIN 0

#endif  //HARDWARE_PROFILE_PIC18F87J50_PIM_H
