/**
  ******************************************************************************
  * @file    BSP/Inc/stm32h7xx_it.h
  * @author  MCD Application Team
  * @brief   This file contains the headers of the interrupt handlers for Cortex-M7.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32H7xx_IT_H
#define __STM32H7xx_IT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

void DMA2_Stream0_IRQHandler(void);
void DMA2_Stream1_IRQHandler(void);
void DMA2_Stream2_IRQHandler(void);
void DMA2_Stream3_IRQHandler(void);
void DMA2_Stream5_IRQHandler(void);
void DMA2_Stream6_IRQHandler(void);
void DMA2_Stream7_IRQHandler(void);

void AUDIO_OUT_SAIx_DMAx_IRQHandler(void);
void AUDIO_IN_SAIx_DMAx_IRQHandler(void);
void AUDIO_DFSDM_DMAx_MIC1_IRQHandler(void);
void AUDIO_DFSDM_DMAx_MIC2_IRQHandler(void);
void AUDIO_DFSDM_DMAx_MIC3_IRQHandler(void);
void AUDIO_DFSDM_DMAx_MIC4_IRQHandler(void);
void AUDIO_DFSDM_DMAx_MIC5_IRQHandler(void);
void BDMA2_Channel6_IRQHandler(void);
void BDMA_Channel1_IRQHandler(void);


void SDMMC1_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32H7xx_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
