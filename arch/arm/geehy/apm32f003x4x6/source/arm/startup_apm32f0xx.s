;/*!
; * @file       startup_apm32f00x.s
; *
; * @brief      CMSIS Cortex-M0 PLUS based Core Device Startup File for Device startup_apm32f00x
; *
; * @version    V1.0.1
; *
; * @date       2022-04-11
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

;<h> Stack Configuration
;  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
__stack_limit
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                IF       Heap_Size != 0                      ; Heap is provided
                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit
                ENDIF
                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                   ; Top of Stack
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

__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler routine
Reset_Handler   PROC
                EXPORT  Reset_Handler                 [WEAK]
                IMPORT  __main
                IMPORT  SystemInit



                LDR     R0, =__initial_sp          ; set stack pointer
                MSR     MSP, R0

                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                    [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler              [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                    [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                 [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WUPT_IRQHandler                 [WEAK]
                EXPORT  RCM_IRQHandler                  [WEAK]
                EXPORT  EINTA_IRQHandler                [WEAK]
                EXPORT  EINTB_IRQHandler                [WEAK]
                EXPORT  EINTC_IRQHandler                [WEAK]
                EXPORT  EINTD_IRQHandler                [WEAK]
                EXPORT  SPI_IRQHandler                  [WEAK]
                EXPORT  TMR1_UT_IRQHandler              [WEAK]
                EXPORT  TMR1_CC_IRQHandler              [WEAK]
                EXPORT  TMR2_UO_IRQHandler              [WEAK]
                EXPORT  TMR2_CC_IRQHandler              [WEAK]
                EXPORT  USART1_TX_IRQHandler            [WEAK]
                EXPORT  USART1_RX_IRQHandler            [WEAK]
                EXPORT  IIC_IRQHandler                  [WEAK]
                EXPORT  ADC_IRQHandler                  [WEAK]
                EXPORT  TMR4_IRQHandler                 [WEAK]
                EXPORT  FLASH_IRQHandler                [WEAK]
                EXPORT  USART3_TX_IRQHandler            [WEAK]
                EXPORT  USART3_RX_IRQHandler            [WEAK]
                EXPORT  USART2_TX_IRQHandler            [WEAK]
                EXPORT  USART2_RX_IRQHandler            [WEAK]
                EXPORT  TMR1A_UT_IRQHandler             [WEAK]
                EXPORT  TMR1A_CC_IRQHandler             [WEAK]


WUPT_IRQHandler
RCM_IRQHandler
EINTA_IRQHandler
EINTB_IRQHandler
EINTC_IRQHandler
EINTD_IRQHandler
SPI_IRQHandler
TMR1_UT_IRQHandler
TMR1_CC_IRQHandler
TMR2_UO_IRQHandler
TMR2_CC_IRQHandler
USART1_TX_IRQHandler
USART1_RX_IRQHandler
IIC_IRQHandler
ADC_IRQHandler
TMR4_IRQHandler
FLASH_IRQHandler
USART3_TX_IRQHandler
USART3_RX_IRQHandler
USART2_TX_IRQHandler
USART2_RX_IRQHandler
TMR1A_UT_IRQHandler
TMR1A_CC_IRQHandler

                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB

                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit

                 ELSE

                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap

__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END
                 
;************************ (C) COPYRIGHT Geehy Semiconductor Co.,Ltd *****END OF FILE*****
