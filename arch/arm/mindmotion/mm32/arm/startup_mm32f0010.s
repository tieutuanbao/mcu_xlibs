;******************** (C) COPYRIGHT 2019 MindMotion ********************
; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

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
                DCD     MemManage_Handler              ; MPU Fault Handler  		;;new 
                DCD     BusFault_Handler               ; Bus Fault Handler		;;new
                DCD     UsageFault_Handler             ; Usage Fault Handler	        ;;new
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     SVC_Handler                    ; SVCall Handler
                DCD     DebugMon_Handler               ; Debug Monitor Handler 	        ;;new
                DCD     0                              ; Reserved
                DCD     PendSV_Handler                 ; PendSV Handler
                DCD     SysTick_Handler                ; SysTick Handler

; External Interrupts

                DCD     WWDG_IWDG_IRQHandler           ; Window WatchDog Interrupt                               
                DCD     PVD_IRQHandler                 ; PVD through EXTI Line detect Interrupt                  
                DCD     0                              ;
                DCD     FLASH_IRQHandler               ; FLASH Interrupt                                         
                DCD     RCC_IRQHandler                 ; RCC Interrupt                                           
                DCD     EXTI0_1_IRQHandler             ; EXTI Line 0 and 1 Interrupts                            
                DCD     EXTI2_3_IRQHandler             ; EXTI Line 2 and 3 Interrupts                            
                DCD     EXTI4_15_IRQHandler            ; EXTI Line 4 to 15 Interrupts                            
                DCD     0                              ;
                DCD     0                              ;                                
                DCD     0                              ;
                DCD     0                              ;
                DCD     ADC1_IRQHandler                ; ADC1 Interrupts                                         
                DCD     TIM1_BRK_UP_TRG_COM_IRQHandler ; TIM1 Break, Update, Trigger and Commutation Interrupts  
                DCD     TIM1_CC_IRQHandler             ; TIM1 Capture Compare Interrupt                          
                DCD     0                              ;                                           
                DCD     TIM3_IRQHandler                ; TIM3 Interrupt                                          
                DCD     0                              ;
                DCD     0                              ;
                DCD     TIM14_IRQHandler               ; TIM14 Interrupt                                         
                DCD     0                              ;
                DCD     0                              ;                                          
                DCD     0                              ;                                          
                DCD     I2C1_IRQHandler                ; I2C1 Interrupt                                          
                DCD     0                              ;
                DCD     SPI1_IRQHandler                ; SPI1 Interrupt                                          
                DCD     0                              ;
                DCD     UART1_IRQHandler               ; UART1 Interrupt                                         
                DCD     UART2_IRQHandler               ; UART2 Interrupt                                         


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

;Check if boot space corresponds to test memory 

                LDR R0,=0x00000004
                LDR R1, [R0]
                LSRS R1, R1, #24
                LDR R2,=0x1F
                CMP R1, R2
        
                BNE ApplicationStart  
     
; SYSCFG clock enable    
     
                LDR R0,=0x40021018 
                LDR R1,=0x00000001
                STR R1, [R0]
        
; Set CFGR1 register with flash memory remap at address 0

                LDR R0,=0x40010000 
                LDR R1,=0x00000000
                STR R1, [R0]
ApplicationStart         
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
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler              [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler               [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler             [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                    [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler               [WEAK]
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


                EXPORT  WWDG_IWDG_IRQHandler           [WEAK]
                EXPORT  PVD_IRQHandler                 [WEAK]
                EXPORT  FLASH_IRQHandler               [WEAK]
                EXPORT  RCC_IRQHandler                 [WEAK]
                EXPORT  EXTI0_1_IRQHandler             [WEAK]
                EXPORT  EXTI2_3_IRQHandler             [WEAK]
                EXPORT  EXTI4_15_IRQHandler            [WEAK]
                EXPORT  ADC1_IRQHandler                [WEAK]
                EXPORT  TIM1_BRK_UP_TRG_COM_IRQHandler [WEAK]
                EXPORT  TIM1_CC_IRQHandler             [WEAK]
                EXPORT  TIM3_IRQHandler                [WEAK]
                EXPORT  TIM14_IRQHandler               [WEAK]
                EXPORT  I2C1_IRQHandler                [WEAK]
                EXPORT  SPI1_IRQHandler                [WEAK]
                EXPORT  UART1_IRQHandler               [WEAK]
                EXPORT  UART2_IRQHandler               [WEAK]


WWDG_IWDG_IRQHandler
PVD_IRQHandler
FLASH_IRQHandler
RCC_IRQHandler
EXTI0_1_IRQHandler
EXTI2_3_IRQHandler
EXTI4_15_IRQHandler
ADC1_IRQHandler
TIM1_BRK_UP_TRG_COM_IRQHandler
TIM1_CC_IRQHandler
TIM3_IRQHandler
TIM14_IRQHandler
I2C1_IRQHandler
SPI1_IRQHandler
UART1_IRQHandler
UART2_IRQHandler


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

;******************** (C) COPYRIGHT 2019 MindMotion ********************