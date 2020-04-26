#ifndef NRF24L01_H_
#define NRF24L01_H_

#include "stm32f1xx_hal.h"
#include <stdint.h>

/* Registers */
#define NRF_CONFIG		0x00
#define NRF_EN_AA		0x01
#define NRF_EN_RXADDR	0x02
#define NRF_SETUP_AW	0x03
#define NRF_SETUP_RETR	0x04
#define NRF_RF_CH		0x05
#define NRF_RF_SETUP	0x06
#define NRF_STATUS		0x07
#define NRF_OBSERVE_TX	0x08
#define NRF_CD			0x09
#define NRF_RX_ADDR_P0	0x0A
#define NRF_RX_ADDR_P1	0x0B
#define NRF_RX_ADDR_P2	0x0C
#define NRF_RX_ADDR_P3	0x0D
#define NRF_RX_ADDR_P4	0x0E
#define NRF_RX_ADDR_P5	0x0F
#define NRF_TX_ADDR		0x10
#define NRF_RX_PW_P0	0x11
#define NRF_RX_PW_P1	0x12
#define NRF_RX_PW_P2	0x13
#define NRF_RX_PW_P3	0x14
#define NRF_RX_PW_P4	0x15
#define NRF_RX_PW_P5	0x16
#define NRF_FIFO_STATUS	0x17
#define NRF_DYNPD		0x1C
#define NRF_FEATURE		0x1D

/* Commands */
#define NRF_CMD_R_REGISTER			0x00
#define NRF_CMD_W_REGISTER			0x20
#define NRF_CMD_R_RX_PAYLOAD		0x61
#define NRF_CMD_W_TX_PAYLOAD		0xA0
#define NRF_CMD_FLUSH_TX			0xE1
#define NRF_CMD_FLUSH_RX			0xE2
#define NRF_CMD_REUSE_TX_PL			0xE3
#define NRF_CMD_ACTIVATE			0x50
#define NRF_CMD_R_RX_PL_WID			0x60
#define NRF_CMD_W_ACK_PAYLOAD		0xA8
#define NRF_CMD_W_TX_PAYLOAD_NOACK	0xB0
#define NRF_CMD_NOP					0xFF

#define NRF_SPI_TIMEOUT	100000

typedef enum {
    NRF_DATA_RATE_250KBPS = 1,
    NRF_DATA_RATE_1MBPS   = 0,
    NRF_DATA_RATE_2MBPS   = 2
} NRF_DATA_RATE;

typedef enum {
    NRF_TX_PWR_M18dBm     = 0,
    NRF_TX_PWR_M12dBm     = 1,
    NRF_TX_PWR_M6dBm      = 2,
    NRF_TX_PWR_0dBm       = 3
} NRF_TX_PWR;

typedef enum {
    NRF_ADDR_WIDTH_3      = 1,
    NRF_ADDR_WIDTH_4      = 2,
    NRF_ADDR_WIDTH_5      = 3
} NRF_ADDR_WIDTH;

typedef enum {
    NRF_CRC_WIDTH_1B      = 0,
    NRF_CRC_WIDTH_2B      = 1
} NRF_CRC_WIDTH;

typedef enum{
    NRF_STATE_RX          = 1,
    NRF_STATE_TX          = 0
} NRF_TXRX_STATE;

typedef struct {

    /* nrf24L01 Configuration Parameter 
       PayloadLength   : maximum is 32 Bytes
       RetransmitCount : can be 0~15 times
       RetransmitDelay : 0[250uS]~0x0F(4000us), LSB:250us
    */
    NRF_DATA_RATE 		DATA_RATE;
    NRF_TX_PWR			TX_POWER;
    NRF_CRC_WIDTH		CRC_WIDTH;
    NRF_ADDR_WIDTH		ADDR_WIDTH;
    NRF_TXRX_STATE		STATE;
    uint8_t				PayloadLength;
    uint8_t				RetransmitCount;
    uint8_t				RetransmitDelay;

    uint8_t				BUSY_FLAG;

    /* Usr interface, Rx/Tx Buffer */
    uint8_t*			RX_BUFFER;
    uint8_t*			TX_BUFFER;

    /* nrf24L01 transmit/recive freq define */
    /* channel can be 0~127 */
    uint8_t				RF_CHANNEL;

    /* nrf24L01 Tx/Rx address
       Pipe [0:1] has maximum 5 Bytes address
       Pipe [2:5] has 3 Bytes address
    */
    uint8_t*			RX_ADDRESS;
    uint8_t*			TX_ADDRESS;

    /* STM32 SPI Peripheral HAL handle */
    SPI_HandleTypeDef*  spi;

    /* STM32 GPIO/EXTI Peripheral Parameter */
    GPIO_TypeDef*		NRF_CSN_GPIOx;	// CSN pin
    uint16_t			NRF_CSN_GPIO_PIN;

    GPIO_TypeDef*		NRF_CE_GPIOx;	// CE pin
    uint16_t			NRF_CE_GPIO_PIN;

    GPIO_TypeDef*		NRF_IRQ_GPIOx;	// IRQ pin
    uint16_t			NRF_IRQ_GPIO_PIN;
    IRQn_Type			NRF_IRQn;
    uint8_t				NRF_IRQ_preempt_priority;
    uint8_t				NRF_IRQ_sub_priority;

} nrf24L01_Dev;

typedef enum {
    NRF_OK,
    NRF_ERROR
} NRF_RESULT;


/* Initialization routine */
NRF_RESULT NRF_Init(nrf24L01_Dev* dev);

/* EXTI Interrupt Handler */
void NRF_IRQ_Handler(nrf24L01_Dev* dev);

/* Blocking Data Sending / Receiving FXs */
NRF_RESULT NRF_SendPacket(nrf24L01_Dev* dev,uint8_t* data);
NRF_RESULT NRF_ReceivePacket(nrf24L01_Dev* dev,uint8_t* data);

/* Non-Blocking Data Sending / Receiving FXs */
NRF_RESULT NRF_PushPacket(nrf24L01_Dev* dev,uint8_t* data);
NRF_RESULT NRF_PullPacket(nrf24L01_Dev* dev,uint8_t* data);

/* LOW LEVEL STUFF (you don't have to look in here...)*/
NRF_RESULT NRF_SendCommand(nrf24L01_Dev* dev, uint8_t cmd, uint8_t* tx,uint8_t* rx,uint8_t len);
/* CMD */
NRF_RESULT NRF_ReadRegister(nrf24L01_Dev* dev,uint8_t reg, uint8_t* data);
NRF_RESULT NRF_WriteRegister(nrf24L01_Dev* dev,uint8_t reg, uint8_t* data);
NRF_RESULT NRF_ReadRXPayload(nrf24L01_Dev* dev,uint8_t* data);
NRF_RESULT NRF_WriteTXPayload(nrf24L01_Dev* dev,uint8_t* data);
NRF_RESULT NRF_FlushTX(nrf24L01_Dev* dev);
NRF_RESULT NRF_FlushRX(nrf24L01_Dev* dev);

/* RF_SETUP */
NRF_RESULT NRF_SetDataRate(nrf24L01_Dev* dev,NRF_DATA_RATE rate);
NRF_RESULT NRF_SetTXPower(nrf24L01_Dev* dev,NRF_TX_PWR pwr);
NRF_RESULT NRF_SetCCW(nrf24L01_Dev* dev,uint8_t activate);

/* STATUS */
NRF_RESULT NRF_ClearInterrupts(nrf24L01_Dev* dev);

/* RF_CH */
NRF_RESULT NRF_SetRFChannel(nrf24L01_Dev* dev,uint8_t ch);

/* SETUP_RETR */
NRF_RESULT NRF_SetRetransmittionCount(nrf24L01_Dev* dev,uint8_t count);
NRF_RESULT NRF_SetRetransmittionDelay(nrf24L01_Dev* dev,uint8_t delay);

/* SETUP_AW */
NRF_RESULT NRF_SetAddressWidth(nrf24L01_Dev* dev,NRF_ADDR_WIDTH width);

/* EN_RXADDR */
NRF_RESULT NRF_EnableRXPipe(nrf24L01_Dev* dev,uint8_t pipe);

/* EN_AA */
NRF_RESULT NRF_EnableAutoAcknowledgement(nrf24L01_Dev* dev,uint8_t pipe);

/* CONFIG */
NRF_RESULT NRF_EnableCRC(nrf24L01_Dev* dev,uint8_t activate);
NRF_RESULT NRF_SetCRCWidth(nrf24L01_Dev* dev,NRF_CRC_WIDTH width);
NRF_RESULT NRF_PowerUp(nrf24L01_Dev* dev,uint8_t powerUp);
NRF_RESULT NRF_RXTXControl(nrf24L01_Dev* dev,NRF_TXRX_STATE rx);
NRF_RESULT NRF_EnableRXDataReadyIRQ(nrf24L01_Dev* dev,uint8_t activate);
NRF_RESULT NRF_EnableTXDataSentIRQ(nrf24L01_Dev* dev,uint8_t activate);
NRF_RESULT NRF_EnableMaxRetransmitIRQ(nrf24L01_Dev* dev,uint8_t activate);

/* RX_ADDR_P0 */
NRF_RESULT NRF_SetRXAddress_P0(nrf24L01_Dev* dev,uint8_t* address);	// 5bytes of address

/* TX_ADDR */
NRF_RESULT NRF_SetTXAddress(nrf24L01_Dev* dev,uint8_t* address);	// 5bytes of address

/* RX_PW_P0 */
NRF_RESULT NRF_SetRXPayloadWidth_P0(nrf24L01_Dev* dev,uint8_t width);

/* FEATURE */

#endif /* NRF24L01_H_ */
