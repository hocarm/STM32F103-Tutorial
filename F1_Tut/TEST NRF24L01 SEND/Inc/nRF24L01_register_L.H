#ifndef _NRF24L01_REGISTER_H_
#define _NRF24L01_REGISTER_H_

#ifndef REG_U8
#define REG_U8 unsigned char
#endif
/*** nRF24L01 SPI command ***/
#define R_REGISTER(x)   (x&0x1F)        /*Read command and status registers. AAAAA =
                                        5 bit Register Map Address*/

#define W_REGISTER(x)   ((x&0x1F)|0x20) /*Write command and status registers. (x) = 5
                                        bit Register Map Address
                                        Executable in power down or standby modes
                                        only.*/
                                                
#define R_RX_PAYLOAD    (0x61)          /*Read RX-payload: 1-32 bytes. A read operation
                                        always starts at byte 0. Payload is deleted from
                                        FIFO after it is read. Used in RX mode.*/

#define W_TX_PAYLOAD    (0xA0)          /*Write TX-payload: 1-32 bytes. A write operation
                                        always starts at byte 0 used in TX payload.*/
#define FLUSH_TX        (0xE1)          /*Flush TX FIFO, used in TX mode*/

#define FLUSH_RX        (0xE2)          /*Flush RX FIFO, used in RX mode
                                        Should not be executed during transmission of
                                        acknowledge, that is, acknowledge package will
                                        not be completed.*/

#define REUSE_TX_PL     (0xE3)          /*Used for a PTX device
                                        Reuse last transmitted payload.
                                        TX payload reuse is active until
                                        W_TX_PAYLOAD or FLUSH TX is executed. TX
                                        payload reuse must not be activated or deactivated during package transmission.*/

#define R_RX_PL_WID     (0x60)          /*Read RX payload width for the top
                                        R_RX_PAYLOAD in the RX FIFO.
                                        Note: Flush RX FIFO if the read value is larger
                                        than 32 bytes.*/

#define W_ACK_PAYLOAD(x) (0xA8|(x&0x07))        /*Used in RX mode.
                                                Write Payload to be transmitted together with
                                                ACK packet on PIPE (x). ((x) valid in the
                                                range from 000 to 101). Maximum three ACK
                                                packet payloads can be pending. Payloads with
                                                same (x) are handled using first in - first out
                                                principle. Write payload: 1-32 bytes. A write
                                                operation always starts at byte 0.*/
                                                
#define W_TX_PAYLOAD_NO (0xB0)          /*Used in TX mode. Disables AUTOACK on this
                                        specific packet.*/

#define NOP             (0xFF)          /*No Operation. Might be used to read the STATUS
                                        register*/
                                                
/*** Registor structure Define ***/
/**** CONFIG            00H = 0x08
    Configuration Register
    */
struct nRF24L01_CONFIG{
    REG_U8 PRIM_RX:1;   //RX/TX control
                        //1: PRX, 0: PTX
        
    REG_U8 PWR_UP:1;    //1: POWER UP, 0:POWER DOWN
    
    REG_U8 CRCO:1;      //CRC encoding scheme
                        //'0' - 1 byte
                        //'1' - 2 bytes
    REG_U8 EN_CRC:1;    //Enable CRC. Forced high if one of the bits 
                        //in the EN_AA is high

    REG_U8 MASK_MAX_RT:1;       //Mask interrupt caused by MAX_RT
                                //1: Interrupt not reflected on the IRQ pin
                                //0: Reflect MAX_RT as active low interrupt on theIRQ pin

    REG_U8 MASK_TX_DS:1;        //Mask interrupt caused by TX_DS
                                //1: Interrupt not reflected on the IRQ pin
                                //0: Reflect TX_DS as active low interrupt on the IRQpin

    REG_U8 MASK_RX_DR:1;        //Mask interrupt caused by RX_DR
                                //1: Interrupt not reflected on the IRQ pin
                                //0: Reflect RX_DR as active low interrupt on theIRQ pin
                                
    REG_U8 Reserved:1;  //Only '0' allowed
};
/**** EN_AA			01H = 0x3F
    Enable Auto Acknowledgment Function Disable
    this functionality to be compatible with nRF2401
    */
struct nRF24L01_EN_AA{
    REG_U8 ENAA_P0:1;   //Enable auto acknowledgement data pipe 0
                                
    REG_U8 ENAA_P1:1;   //Enable auto acknowledgement data pipe 1
    
    REG_U8 ENAA_P2:1;   //Enable auto acknowledgement data pipe 2
                                
    REG_U8 ENAA_P3:1;   //Enable auto acknowledgement data pipe 3
                                
    REG_U8 ENAA_P4:1;   //Enable auto acknowledgement data pipe 4
                                
    REG_U8 ENAA_P5:1;   //Enable auto acknowledgement data pipe 5
                                
    REG_U8 Reserved:2;  //Only '00' allowed
};

/**** EN_RXADDR		02H = 0x03
    Enabled RX Addresses
    */
struct nRF24L01_EN_RXADDR{
    REG_U8 ERX_P0:1;    //Enable data pipe 0.
    
    REG_U8 ERX_P1:1;    //Enable data pipe 1.
    
    REG_U8 ERX_P2:1;    //Enable data pipe 2.
    
    REG_U8 ERX_P3:1;    //Enable data pipe 3.
    
    REG_U8 ERX_P4:1;    //Enable data pipe 4.
    
    REG_U8 ERX_P5:1;    //Enable data pipe 5.
    
    REG_U8 Reserved:2;  //Only '00' allowed
};

/**** SETUP_AW		03H = 0x03
    Setup of Address Widths (common for all data pipes)
    */
struct nRF24L01_SETUP_AW{
    REG_U8 AW:2;        //RX/TX Address field width
                        //'00' - Illegal
                        //'01' - 3 bytes
                        //'10' - 4 bytes
                        //'11' - 5 bytes
                        //LSByte is used if address width is below 5 bytes

    REG_U8 Reserved:6;  //Only '000000' allowed
};

/**** SETUP_RETR	04H = 0x03
    Setup of Automatic Retransmission
    */
struct nRF24L01_SETUP_RETR{
    REG_U8 ARC:4;       //Auto Retransmit Count
                        //'0000' -Re-Transmit disabled
                        //'0001' - Up to 1 Re-Transmit on fail of AA
                        //....
                        //'1111' - Up to 15 Re-Transmit on fail of AA

    REG_U8 ARD:4;       //Auto Retransmit Delay
                        //'0000' - Wait 250us
                        //'0001' - Wait 500us
                        //'0010' - Wait 750us
                        //...
                        //'1111' - Wait 4000us
                        //(Delay defined from end of transmission to start ofnext transmission)
};

/**** RF_CH             05H = 0x02
    RF Channel
    */
struct nRF24L01_RF_CH{
    REG_U8 RF_CH:7;     //Sets the frequency channel nRF24L01+ operates
                        //on

    REG_U8 Reserved:1;  //Only '0' allowed
};

/**** RF_SETUP		06H = 0x0E
    RF Setup Register
    */
struct nRF24L01_RF_SETUP{
    REG_U8 Obsolete:1;  //Don't care
    
    REG_U8 RF_PWR:2;    //Set RF output power in TX mode
                        //'00' - -18dBm
                        //'01' - -12dBm
                        //'10' - -6dBm
                        //'11' - 0dBm
    
    REG_U8 RF_DR_HIGH:1;        //Select between the high speed data rates. This bit
                                //is don't care if RF_DR_LOW is set.
                                //Encoding:
                                //[RF_DR_LOW, RF_DR_HIGH]:
                                //'00' - 1Mbps
                                //'01' - 2Mbps
                                //'10' - 250kbps
                                //'11' - Reserved
                                
    REG_U8 PPL_LOCK:1;  //Force PLL lock signal. Only used in test
    
    
    REG_U8 RF_DR_LOW:1; //Set RF Data Rate to 250kbps. See RF_DR_HIGH
                        //for encoding.
    
    REG_U8 Reserved:1;  //Only '0' allowed
    
    REG_U8 CONT_WAVE:1; //Enables continuous carrier transmit when high.
};

/**** STATUS		07H = 0x0E
    Status Register (In parallel to the SPI command
    word applied on the MOSI pin, the STATUS register
    is shifted serially out on the MISO pin)
    */
struct nRF24L01_STATUS{
    REG_U8 TX_FULL:1;   //TX FIFO full flag.
                        //1: TX FIFO full.
                        //0: Available locations in TX FIFO.
    
    REG_U8 RX_P_NO:3;   //Data pipe number for the payload available for
                        //reading from RX_FIFO
                        //000-101: Data Pipe Number
                        //110: Not Used
                        //111: RX FIFO Empty
                                
    REG_U8 MAX_RT:1;    //Maximum number of TX retransmits interrupt
                        //Write 1 to clear bit. If MAX_RT is asserted it must
                        //be cleared to enable further communication.
    
    REG_U8 TX_DS:1;     //Data Sent TX FIFO interrupt. Asserted when
                        //packet transmitted on TX. If AUTO_ACK is acti
                        //vated, this bit is set high only when ACK is
                        //received.
                        //Write 1 to clear bit.
                                
    REG_U8 RX_DR:1;     //Data Ready RX FIFO interrupt. Asserted when
                        //new data arrives RX FIFOc.
                        //Write 1 to clear bit.
                                
    REG_U8 Reserved:1;  //Only '0' allowed
};

/**** OBSERVE_TX	08H = 0x00
    Transmit observe register
    */
struct nRF24L01_OBSERVE_TX{
    REG_U8 ARC_CNT:4;   //Count retransmitted packets. The counter is reset
                        //when transmission of a new packet starts.
    
    REG_U8 PLOS_CNT:4;  //Count lost packets. The counter is overflow pro-
                        //tected to 15, and discontinues at max until reset.
                        //The counter is reset by writing to RF_CH. 
};

/**** RPD               09H = 0x00
    NONE
    */
struct nRF24L01_RPD{
    REG_U8 RPD:1;       //Received Power Detector. This register is called
                        //CD (Carrier Detect) in the nRF24L01. The name is
                        //different in nRF24L01+ due to the different input
                        //power level threshold for this bit. 
    
    REG_U8 Reserved:7;
};

/**** RX_ADDR_P0	0AH = 0xE7E7E7E7E7 (5Bytes)
    Receive address data pipe 0. 5 Bytes maximum
    length. (LSByte is written first. Write the number of
    bytes defined by SETUP_AW)
    */
struct nRF24L01_RX_ADDR_P0{
    REG_U8 addr[5];
};

/**** RX_ADDR_P1	0BH = 0xC2C2C2C2C2 (5Bytes)
    Receive address data pipe 1. 5 Bytes maximum
    length. (LSByte is written first. Write the number of
    bytes defined by SETUP_AW)
    */
struct nRF24L01_RX_ADDR_P1{
    REG_U8 addr[5];
};

/**** RX_ADDR_P2	0CH = 0xC3
    Receive address data pipe 2. Only LSB. MSBytes
    are equal to RX_ADDR_P1[39:8]
    */
struct nRF24L01_RX_ADDR_P2{
    REG_U8 addr;
};

/**** RX_ADDR_P3	0DH = 0xC4
    Receive address data pipe 3. Only LSB. MSBytes
    are equal to RX_ADDR_P1[39:8]
    */
struct nRF24L01_RX_ADDR_P3{
    REG_U8 addr;
};

/**** RX_ADDR_P4	0EH = 0xC5
    Receive address data pipe 4. Only LSB. MSBytes
    are equal to RX_ADDR_P1[39:8]
    */
struct nRF24L01_RX_ADDR_P4{
    REG_U8 addr;
};

/**** RX_ADDR_P5	0FH = 0xC6
    Receive address data pipe 5. Only LSB. MSBytes
    are equal to RX_ADDR_P1[39:8]
    */
struct nRF24L01_RX_ADDR_P5{
    REG_U8 addr;
};

/**** TX_ADDR		10H = 0xE7E7E7E7E7 (5Bytes)
    Transmit address. Used for a PTX device only.
    (LSByte is written first)
    Set RX_ADDR_P0 equal to this address to handle
    automatic acknowledge if this is a PTX device with
    Enhanced ShockBurst? enabled.
    */
struct nRF24L01_TX_ADDR{
    REG_U8 addr[5];
};

/**** RX_PW_P0		11H = 0x00
    */
struct nRF24L01_RX_PW_P0{
    REG_U8 RX_PW_P0:6;  //Number of bytes in RX payload in data pipe 0 (1 to
                        //32 bytes).
                        //0 Pipe not used
                        //1 = 1 byte
                        //...
                        //32 = 32 bytes
    
    REG_U8 Reserved:2;  //Only '00' allowed
};

/**** RX_PW_P1		12H = 0x00
    */
struct nRF24L01_RX_PW_P1{
    REG_U8 RX_PW_P1:6;  //Number of bytes in RX payload in data pipe 1
                        //32 bytes).
                        //0 Pipe not used
                        //1 = 1 byte
                        //...
                        //32 = 32 bytes
    
    REG_U8 Reserved:2;  //Only '00' allowed
};

/**** RX_PW_P2		13H = 0x00
    */
struct nRF24L01_RX_PW_P2{
    REG_U8 RX_PW_P2:6;  //Number of bytes in RX payload in data pipe 2
                        //32 bytes).
                        //0 Pipe not used
                        //1 = 1 byte
                        //...
                        //32 = 32 bytes
    
    REG_U8 Reserved:2;  //Only '00' allowed
};

/**** RX_PW_P3		14H = 0x00
    */
struct nRF24L01_RX_PW_P3{
    REG_U8 RX_PW_P3:6;  //Number of bytes in RX payload in data pipe 3
                        //32 bytes).
                        //0 Pipe not used
                        //1 = 1 byte
                        //...
                        //32 = 32 bytes
    
    REG_U8 Reserved:2;  //Only '00' allowed
};

/**** RX_PW_P4		15H = 0x00
    */
struct nRF24L01_RX_PW_P4{
    REG_U8 RX_PW_P4:6;  //Number of bytes in RX payload in data pipe 4
                        //32 bytes).
                        //0 Pipe not used
                        //1 = 1 byte
                        //...
                        //32 = 32 bytes
    
    REG_U8 Reserved:2;  //Only '00' allowed
};

/**** RX_PW_P5		16H = 0x00
    */
struct nRF24L01_RX_PW_P5{
    REG_U8 RX_PW_P5:6;  //Number of bytes in RX payload in data pipe 5
                        //32 bytes).
                        //0 Pipe not used
                        //1 = 1 byte
                        //...
                        //32 = 32 bytes
    
    REG_U8 Reserved:2;  //Only '00' allowed
};

/**** FIFO_STATUS	17H = 0x11
    FIFO Status Register
    */
struct nRF24L01_FIFO_STATUS{
    REG_U8 RX_EMPTY:1;  //RX FIFO empty flag.
                        //1: RX FIFO empty.
                        //0: Data in RX FIFO.
    
    REG_U8 RX_FULL:1;   //RX FIFO full flag.
                        //1: RX FIFO full
                        //0: Available locations in RX FIFO
                                    
    REG_U8 Reserved_:2; //Only '00' allowed
    
    REG_U8 TX_EMPTY:1;  //TX FIFO empty flag.
                        //1: TX FIFO empty.
                        //0: Data in TX FIFO.
    
    REG_U8 TX_FULL:1;   //TX FIFO full flag. 1: TX FIFO full. 0: Available loca
                        //tions in TX FIFO.
    
    REG_U8 TX_REUSE:1;  //Used for a PTX device
                        //Pulse the rfce high for at least 10��s to Reuse last
                        //transmitted payload. TX payload reuse is active
                        //until W_TX_PAYLOAD or FLUSH TX is executed.
                        //TX_REUSE is set by the SPI command
                        //REUSE_TX_PL, and is reset by the SPI commands
                        //W_TX_PAYLOAD or FLUSH TX
                                    
    REG_U8 Reserved:1;  //Only '0' allowed
};

/**** DYNPD             1CH = 0x00
    Enable dynamic payload length
    */
struct nRF24L01_DYNPD{
    REG_U8 DPL_P0:1;    //Enable dynamic payload length data pipe 0.
                        //(Requires EN_DPL and ENAA_P0)
    
    REG_U8 DPL_P1:1;    //Enable dynamic payload length data pipe 1.
                        //(Requires EN_DPL and ENAA_P1)
                                    
    REG_U8 DPL_P2:1;    //Enable dynamic payload length data pipe 2.
                        //(Requires EN_DPL and ENAA_P2)
                                    
    REG_U8 DPL_P3:1;    //Enable dynamic payload length data pipe 3.
                        //(Requires EN_DPL and ENAA_P3)
                                    
    REG_U8 DPL_P4:1;    //Enable dynamic payload length data pipe 4.
                        //(Requires EN_DPL and ENAA_P4)
                                    
    REG_U8 DPL_P5:1;    //Enable dynamic payload length data pipe 5.
                        //(Requires EN_DPL and ENAA_P5)
                                    
    REG_U8 Reserved:2;  //Only '00' allowed
};

/**** FEATURE		1DH = 0x00
    Feature Register
    */
struct nRF24L01_FEATURE{
    REG_U8 EN_DYN_ACK:1;        //Enables the W_TX_PAYLOAD_NOACK command
    
    REG_U8 EN_ACK_PAY:1;        //Enables Payload with ACK
    
    REG_U8 EN_DPL:1;    //Enables Dynamic Payload Length
    
    REG_U8 Reserved:5;  //Only '00000' allowed
};

struct nRF2401_Register{
    struct nRF24L01_CONFIG      CONFIG;         //00H
    struct nRF24L01_EN_AA       EN_AA;          //01H
    struct nRF24L01_EN_RXADDR	EN_RXADDR;      //02H
    struct nRF24L01_SETUP_AW	SETUP_AW;       //03H
    struct nRF24L01_SETUP_RETR	SETUP_RETR;     //04H
    struct nRF24L01_RF_CH       RF_CH;          //05H
    struct nRF24L01_RF_SETUP	RF_SETUP;       //06H
    struct nRF24L01_STATUS      STATUS;		//07H
    struct nRF24L01_OBSERVE_TX	OBSERVE_TX;	//08H
    struct nRF24L01_RPD         RPD;		//09H
    struct nRF24L01_RX_ADDR_P0	RX_ADDR_P0;	//0AH
    struct nRF24L01_RX_ADDR_P1	RX_ADDR_P1;	//0BH
    struct nRF24L01_RX_ADDR_P2	RX_ADDR_P2;	//0CH
    struct nRF24L01_RX_ADDR_P3	RX_ADDR_P3;	//0DH
    struct nRF24L01_RX_ADDR_P4	RX_ADDR_P4;	//0EH
    struct nRF24L01_RX_ADDR_P5	RX_ADDR_P5;	//0FH
    struct nRF24L01_TX_ADDR     TX_ADDR;	//10H
    struct nRF24L01_RX_PW_P0	RX_PW_P0;	//11H
    struct nRF24L01_RX_PW_P1	RX_PW_P1;	//12H
    struct nRF24L01_RX_PW_P2	RX_PW_P2;	//13H
    struct nRF24L01_RX_PW_P3	RX_PW_P3;	//14H
    struct nRF24L01_RX_PW_P4	RX_PW_P4;	//15H
    struct nRF24L01_RX_PW_P5	RX_PW_P5;	//16H
    struct nRF24L01_FIFO_STATUS	FIFO_STATUS;    //17H
    struct nRF24L01_DYNPD       DYNPD;		//1CH
    struct nRF24L01_FEATURE     FEATURE;	//1DH
};
#endif
