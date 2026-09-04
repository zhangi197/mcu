.syntax unified
.cpu cortex-m4
.fpu fpv4-sp-d16
.thumb

.global g_pfnVectors
.global Reset_Handler

.extern SystemInit
.extern __libc_init_array
.extern main

.section .isr_vector,"a",%progbits
.type g_pfnVectors, %object
g_pfnVectors:
  .word _estack
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word MemManage_Handler
  .word BusFault_Handler
  .word UsageFault_Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word SVC_Handler
  .word DebugMon_Handler
  .word 0
  .word PendSV_Handler
  .word SysTick_Handler
  .word WWDG_IRQHandler
  .word PVD_IRQHandler
  .word TAMP_STAMP_IRQHandler
  .word RTC_WKUP_IRQHandler
  .word FLASH_IRQHandler
  .word RCC_IRQHandler
  .word EXTI0_IRQHandler
  .word EXTI1_IRQHandler
  .word EXTI2_IRQHandler
  .word EXTI3_IRQHandler
  .word EXTI4_IRQHandler
  .word DMA1_Stream0_IRQHandler
  .word DMA1_Stream1_IRQHandler
  .word DMA1_Stream2_IRQHandler
  .word DMA1_Stream3_IRQHandler
  .word DMA1_Stream4_IRQHandler
  .word DMA1_Stream5_IRQHandler
  .word DMA1_Stream6_IRQHandler
  .word ADC_IRQHandler
  .word CAN1_TX_IRQHandler
  .word CAN1_RX0_IRQHandler
  .word CAN1_RX1_IRQHandler
  .word CAN1_SCE_IRQHandler
  .word EXTI9_5_IRQHandler
  .word TIM1_BRK_TIM9_IRQHandler
  .word TIM1_UP_TIM10_IRQHandler
  .word TIM1_TRG_COM_TIM11_IRQHandler
  .word TIM1_CC_IRQHandler
  .word TIM2_IRQHandler
  .word TIM3_IRQHandler
  .word TIM4_IRQHandler
  .word I2C1_EV_IRQHandler
  .word I2C1_ER_IRQHandler
  .word I2C2_EV_IRQHandler
  .word I2C2_ER_IRQHandler
  .word SPI1_IRQHandler
  .word SPI2_IRQHandler
  .word USART1_IRQHandler
  .word USART2_IRQHandler
  .word USART3_IRQHandler
  .word EXTI15_10_IRQHandler
  .word RTC_Alarm_IRQHandler
  .word OTG_FS_WKUP_IRQHandler
  .word TIM8_BRK_TIM12_IRQHandler
  .word TIM8_UP_TIM13_IRQHandler
  .word TIM8_TRG_COM_TIM14_IRQHandler
  .word TIM8_CC_IRQHandler
  .word DMA1_Stream7_IRQHandler
  .word FSMC_IRQHandler
  .word SDIO_IRQHandler
  .word TIM5_IRQHandler
  .word SPI3_IRQHandler
  .word UART4_IRQHandler
  .word UART5_IRQHandler
  .word TIM6_DAC_IRQHandler
  .word TIM7_IRQHandler
  .word DMA2_Stream0_IRQHandler
  .word DMA2_Stream1_IRQHandler
  .word DMA2_Stream2_IRQHandler
  .word DMA2_Stream3_IRQHandler
  .word DMA2_Stream4_IRQHandler
  .word ETH_IRQHandler
  .word ETH_WKUP_IRQHandler
  .word CAN2_TX_IRQHandler
  .word CAN2_RX0_IRQHandler
  .word CAN2_RX1_IRQHandler
  .word CAN2_SCE_IRQHandler
  .word OTG_FS_IRQHandler
  .word DMA2_Stream5_IRQHandler
  .word DMA2_Stream6_IRQHandler
  .word DMA2_Stream7_IRQHandler
  .word USART6_IRQHandler
  .word I2C3_EV_IRQHandler
  .word I2C3_ER_IRQHandler
  .word OTG_HS_EP1_OUT_IRQHandler
  .word OTG_HS_EP1_IN_IRQHandler
  .word OTG_HS_WKUP_IRQHandler
  .word OTG_HS_IRQHandler
  .word DCMI_IRQHandler
  .word CRYP_IRQHandler
  .word HASH_RNG_IRQHandler
  .word FPU_IRQHandler
.size g_pfnVectors, .-g_pfnVectors

.section .text.Reset_Handler,"ax",%progbits
.type Reset_Handler, %function
Reset_Handler:
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b data_copy_check

data_copy_loop:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

data_copy_check:
  adds r4, r0, r3
  cmp r4, r1
  bcc data_copy_loop

  ldr r0, =_sbss
  ldr r1, =_ebss
  movs r2, #0
  b bss_clear_check

bss_clear_loop:
  str r2, [r0]
  adds r0, r0, #4

bss_clear_check:
  cmp r0, r1
  bcc bss_clear_loop

  bl SystemInit
  bl __libc_init_array
  bl main

infinite_loop:
  b infinite_loop
.size Reset_Handler, .-Reset_Handler

.section .text.Default_Handler,"ax",%progbits
.type Default_Handler, %function
Default_Handler:
  b .

.macro WEAK_DEFAULT handler
  .weak \handler
  .set \handler, Default_Handler
.endm

WEAK_DEFAULT NMI_Handler
WEAK_DEFAULT HardFault_Handler
WEAK_DEFAULT MemManage_Handler
WEAK_DEFAULT BusFault_Handler
WEAK_DEFAULT UsageFault_Handler
WEAK_DEFAULT SVC_Handler
WEAK_DEFAULT DebugMon_Handler
WEAK_DEFAULT PendSV_Handler
WEAK_DEFAULT SysTick_Handler
WEAK_DEFAULT WWDG_IRQHandler
WEAK_DEFAULT PVD_IRQHandler
WEAK_DEFAULT TAMP_STAMP_IRQHandler
WEAK_DEFAULT RTC_WKUP_IRQHandler
WEAK_DEFAULT FLASH_IRQHandler
WEAK_DEFAULT RCC_IRQHandler
WEAK_DEFAULT EXTI0_IRQHandler
WEAK_DEFAULT EXTI1_IRQHandler
WEAK_DEFAULT EXTI2_IRQHandler
WEAK_DEFAULT EXTI3_IRQHandler
WEAK_DEFAULT EXTI4_IRQHandler
WEAK_DEFAULT DMA1_Stream0_IRQHandler
WEAK_DEFAULT DMA1_Stream1_IRQHandler
WEAK_DEFAULT DMA1_Stream2_IRQHandler
WEAK_DEFAULT DMA1_Stream3_IRQHandler
WEAK_DEFAULT DMA1_Stream4_IRQHandler
WEAK_DEFAULT DMA1_Stream5_IRQHandler
WEAK_DEFAULT DMA1_Stream6_IRQHandler
WEAK_DEFAULT ADC_IRQHandler
WEAK_DEFAULT CAN1_TX_IRQHandler
WEAK_DEFAULT CAN1_RX0_IRQHandler
WEAK_DEFAULT CAN1_RX1_IRQHandler
WEAK_DEFAULT CAN1_SCE_IRQHandler
WEAK_DEFAULT EXTI9_5_IRQHandler
WEAK_DEFAULT TIM1_BRK_TIM9_IRQHandler
WEAK_DEFAULT TIM1_UP_TIM10_IRQHandler
WEAK_DEFAULT TIM1_TRG_COM_TIM11_IRQHandler
WEAK_DEFAULT TIM1_CC_IRQHandler
WEAK_DEFAULT TIM2_IRQHandler
WEAK_DEFAULT TIM3_IRQHandler
WEAK_DEFAULT TIM4_IRQHandler
WEAK_DEFAULT I2C1_EV_IRQHandler
WEAK_DEFAULT I2C1_ER_IRQHandler
WEAK_DEFAULT I2C2_EV_IRQHandler
WEAK_DEFAULT I2C2_ER_IRQHandler
WEAK_DEFAULT SPI1_IRQHandler
WEAK_DEFAULT SPI2_IRQHandler
WEAK_DEFAULT USART1_IRQHandler
WEAK_DEFAULT USART2_IRQHandler
WEAK_DEFAULT USART3_IRQHandler
WEAK_DEFAULT EXTI15_10_IRQHandler
WEAK_DEFAULT RTC_Alarm_IRQHandler
WEAK_DEFAULT OTG_FS_WKUP_IRQHandler
WEAK_DEFAULT TIM8_BRK_TIM12_IRQHandler
WEAK_DEFAULT TIM8_UP_TIM13_IRQHandler
WEAK_DEFAULT TIM8_TRG_COM_TIM14_IRQHandler
WEAK_DEFAULT TIM8_CC_IRQHandler
WEAK_DEFAULT DMA1_Stream7_IRQHandler
WEAK_DEFAULT FSMC_IRQHandler
WEAK_DEFAULT SDIO_IRQHandler
WEAK_DEFAULT TIM5_IRQHandler
WEAK_DEFAULT SPI3_IRQHandler
WEAK_DEFAULT UART4_IRQHandler
WEAK_DEFAULT UART5_IRQHandler
WEAK_DEFAULT TIM6_DAC_IRQHandler
WEAK_DEFAULT TIM7_IRQHandler
WEAK_DEFAULT DMA2_Stream0_IRQHandler
WEAK_DEFAULT DMA2_Stream1_IRQHandler
WEAK_DEFAULT DMA2_Stream2_IRQHandler
WEAK_DEFAULT DMA2_Stream3_IRQHandler
WEAK_DEFAULT DMA2_Stream4_IRQHandler
WEAK_DEFAULT ETH_IRQHandler
WEAK_DEFAULT ETH_WKUP_IRQHandler
WEAK_DEFAULT CAN2_TX_IRQHandler
WEAK_DEFAULT CAN2_RX0_IRQHandler
WEAK_DEFAULT CAN2_RX1_IRQHandler
WEAK_DEFAULT CAN2_SCE_IRQHandler
WEAK_DEFAULT OTG_FS_IRQHandler
WEAK_DEFAULT DMA2_Stream5_IRQHandler
WEAK_DEFAULT DMA2_Stream6_IRQHandler
WEAK_DEFAULT DMA2_Stream7_IRQHandler
WEAK_DEFAULT USART6_IRQHandler
WEAK_DEFAULT I2C3_EV_IRQHandler
WEAK_DEFAULT I2C3_ER_IRQHandler
WEAK_DEFAULT OTG_HS_EP1_OUT_IRQHandler
WEAK_DEFAULT OTG_HS_EP1_IN_IRQHandler
WEAK_DEFAULT OTG_HS_WKUP_IRQHandler
WEAK_DEFAULT OTG_HS_IRQHandler
WEAK_DEFAULT DCMI_IRQHandler
WEAK_DEFAULT CRYP_IRQHandler
WEAK_DEFAULT HASH_RNG_IRQHandler
WEAK_DEFAULT FPU_IRQHandler

/* newlib 的 __libc_init_array / __libc_fini_array 会调用 _init / _fini，
   裸机环境没有 crti/crtn，这里提供空桩（Thumb 代码） */
.section .text._init,"ax",%progbits
.thumb_func
.global _init
.type _init, %function
_init:
  bx lr
.size _init, .-_init

.section .text._fini,"ax",%progbits
.thumb_func
.global _fini
.type _fini, %function
_fini:
  bx lr
.size _fini, .-_fini
