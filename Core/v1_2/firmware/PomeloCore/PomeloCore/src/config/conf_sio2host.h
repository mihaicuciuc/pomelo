/**
* \file
*
* \brief Serial Input & Output configuration
*
* Copyright (c) 2013-2020 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_SIO2HOST_H_INCLUDED
#define CONF_SIO2HOST_H_INCLUDED
#define SERIAL_RX_BUF_SIZE_HOST    156


/* ! \name Configuration for SAMD20 */
/* ! @{ */
#define USART_HOST                 SERCOM2
#define HOST_SERCOM_MUX_SETTING    USART_RX_1_TX_0_XCK_1
#define HOST_SERCOM_PINMUX_PAD0    PINMUX_PA12C_SERCOM2_PAD0
#define HOST_SERCOM_PINMUX_PAD1    PINMUX_PA13C_SERCOM2_PAD1
#define HOST_SERCOM_PINMUX_PAD2    PINMUX_UNUSED
#define HOST_SERCOM_PINMUX_PAD3    PINMUX_UNUSED
/** Baudrate setting */
#define USART_HOST_BAUDRATE        115200

#define USART_HOST_RX_ISR_ENABLE()  _sercom_set_handler(2, USART_HOST_ISR_VECT); \
USART_HOST->USART.INTENSET.reg = SERCOM_USART_INTFLAG_RXC; \
system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_SERCOM2);


/* ! @} */
#endif /* CONF_SIO2HOST_H_INCLUDED */

