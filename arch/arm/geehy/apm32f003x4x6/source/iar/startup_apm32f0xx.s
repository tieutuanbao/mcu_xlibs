;/*!
; * @file       startup_apm32f00x.s
; *
; * @brief      APM32F003 devices vector table for EWARM toolchain.
; *
; * @version    V1.0.0
; *
; * @date       2022-02-21
; *
; * @attention
; *
; *  Copyright (C) 2018-2022 Geehy Semiconductor
; *
; *  You may not use this file except in compliance with the
; *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
; *
; *  The program is only for reference, which is distributed in the hope
; *  that it will be usefull and instructional for customers to develop
; *  their software. Unless required by applicable law or agreed to in
; *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
; *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
; *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
; *  and limitations under the License.
; */


        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler                  ; Reset Handler
        DCD     NMI_Handler                    ; NMI Handler
        DCD     HardFault_Handler              ; Hard Fault Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     SVC_Handler                    ; SVCall Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     PendSV_Handler                 ; PendSV Handler
        DCD     SysTick_Handler                ; SysTick Handler

        ; External Interrupts
        DCD     0                              ; Reserved
        DCD     WUPT_IRQHandler                ; Wakeup timer
        DCD     RCM_IRQHandler                 ; Clock controler interrupt
        DCD     EINTA_IRQHandler               ; Port A external interrupts
        DCD     EINTB_IRQHandler               ; Port B external interrupts
        DCD     EINTC_IRQHandler               ; Port C external interrupts
        DCD     EINTD_IRQHandler               ; Port D external interrupts
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     SPI_IRQHandler                 ; SPI Interrupt
        DCD     TMR1_UT_IRQHandler             ; TIMER1 update/overflow/underflow/trigger/break interrupt
        DCD     TMR1_CC_IRQHandler             ; TIMER1 capture/compare interrupt
        DCD     TMR2_UO_IRQHandler             ; TIMER2 update /overflow interrupt
        DCD     TMR2_CC_IRQHandler             ; TIMER2 capture/compare interrupt
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     USART1_TX_IRQHandler           ; USART1 TX interrupt
        DCD     USART1_RX_IRQHandler           ; USART1 RX interrupt
        DCD     IIC_IRQHandler                 ; I2C Interrupt
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     ADC_IRQHandler                 ; ADC interrupt
        DCD     TMR4_IRQHandler                ; TIMER4 interrupt
        DCD     FLASH_IRQHandler               ; Flash interrupt
        DCD     USART3_TX_IRQHandler           ; USART3 TX interrupt
        DCD     USART3_RX_IRQHandler           ; USART3 RX interrupt
        DCD     USART2_TX_IRQHandler           ; USART2 TX interrupt
        DCD     USART2_RX_IRQHandler           ; USART2 RX interrupt
        DCD     TMR1A_UT_IRQHandler            ; TIMER1A update/overflow/underflow/trigger/break interrupt
        DCD     TMR1A_CC_IRQHandler            ; TIMER1A capture/compare interrupt

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler

        LDR     R0, =sfe(CSTACK)          ; set stack pointer
        MSR     MSP, R0

        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
        B NMI_Handler


        PUBWEAK HardFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
        B HardFault_Handler


        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler


        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
        B PendSV_Handler


        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
        B SysTick_Handler


        PUBWEAK WUPT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WUPT_IRQHandler
        B WUPT_IRQHandler


        PUBWEAK RCM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCM_IRQHandler
        B RCM_IRQHandler


        PUBWEAK EINTA_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EINTA_IRQHandler
        B EINTA_IRQHandler


        PUBWEAK EINTB_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EINTB_IRQHandler
        B EINTB_IRQHandler


        PUBWEAK EINTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EINTC_IRQHandler
        B EINTC_IRQHandler


        PUBWEAK EINTD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EINTD_IRQHandler
        B EINTD_IRQHandler


        PUBWEAK SPI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI_IRQHandler
        B SPI_IRQHandler


        PUBWEAK TMR1_UT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR1_UT_IRQHandler
        B TMR1_UT_IRQHandler


        PUBWEAK TMR1_CC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR1_CC_IRQHandler
        B TMR1_CC_IRQHandler


        PUBWEAK TMR2_UO_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR2_UO_IRQHandler
        B TMR2_UO_IRQHandler


        PUBWEAK TMR2_CC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR2_CC_IRQHandler
        B TMR2_CC_IRQHandler


        PUBWEAK USART1_TX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART1_TX_IRQHandler
        B USART1_TX_IRQHandler


        PUBWEAK USART1_RX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART1_RX_IRQHandler
        B USART1_RX_IRQHandler


        PUBWEAK IIC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IIC_IRQHandler
        B IIC_IRQHandler


        PUBWEAK ADC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_IRQHandler
        B ADC_IRQHandler


        PUBWEAK TMR4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR4_IRQHandler
        B TMR4_IRQHandler


        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FLASH_IRQHandler
        B FLASH_IRQHandler


        PUBWEAK USART3_TX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART3_TX_IRQHandler
        B USART3_TX_IRQHandler


        PUBWEAK USART3_RX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART3_RX_IRQHandler
        B USART3_RX_IRQHandler


        PUBWEAK USART2_TX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART2_TX_IRQHandler
        B USART2_TX_IRQHandler


        PUBWEAK USART2_RX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART2_RX_IRQHandler
        B USART2_RX_IRQHandler


        PUBWEAK TMR1A_UT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR1A_UT_IRQHandler
        B TMR1A_UT_IRQHandler


        PUBWEAK TMR1A_CC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR1A_CC_IRQHandler
        B TMR1A_CC_IRQHandler



        END

;************************ (C) COPYRIGHT Geehy Semiconductor Co.,Ltd *****END OF FILE*****
