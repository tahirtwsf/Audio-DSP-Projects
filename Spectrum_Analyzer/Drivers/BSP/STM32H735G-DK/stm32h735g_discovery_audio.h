/**
  ******************************************************************************
  * @file    stm32h735g_discovery_audio.h
  * @author  MCD Application Team
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32h735g_discovery_audio.c driver.
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
#ifndef STM32H735G_DISCO_AUDIO_H
#define STM32H735G_DISCO_AUDIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h735g_discovery_conf.h"
#include "stm32h735g_discovery_errno.h"

#if (USE_AUDIO_CODEC_WM8994 == 1U)
   /* Include audio component Driver */
#include "../Components/wm8994/wm8994.h"
#endif
#include "../Components/Common/audio.h"
/* Include PDM to PCM lib header file */
#include "pdm2pcm_glo.h"


/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32H735G_DISCO
  * @{
  */

/** @addtogroup AUDIO
  * @{
  */

/** @defgroup STM32H735G_DISCO_AUDIO_Exported_Types AUDIO Exported Types
  * @{
  */
typedef struct
{
  uint32_t                    Device;
  uint32_t                    SampleRate;
  uint32_t                    BitsPerSample;
  uint32_t                    ChannelsNbr;
  uint32_t                    Volume;
}BSP_AUDIO_Init_t;

typedef struct
{
  uint32_t                    Instance;            /* Audio IN instance              */
  uint32_t                    Device;              /* Audio IN device to be used     */
  uint32_t                    SampleRate;          /* Audio IN Sample rate           */
  uint32_t                    BitsPerSample;       /* Audio IN Sample resolution     */
  uint32_t                    ChannelsNbr;         /* Audio IN number of channel     */
  uint16_t                    *pBuff;              /* Audio IN record buffer         */
  uint8_t                     **pMultiBuff;        /* Audio IN multi-buffer          */
  uint32_t                    Size;                /* Audio IN record buffer size    */
  uint32_t                    Volume;              /* Audio IN volume                */
  uint32_t                    State;               /* Audio IN State                 */
  uint32_t                    IsMultiBuff;         /* Audio IN multi-buffer usage    */
  uint32_t                    IsMspCallbacksValid; /* Is Msp Callbacks registered     */
}AUDIO_IN_Ctx_t;

typedef struct
{
  uint32_t                    Instance;            /* Audio OUT instance              */
  uint32_t                    Device;              /* Audio OUT device to be used     */
  uint32_t                    SampleRate;          /* Audio OUT Sample rate           */
  uint32_t                    BitsPerSample;       /* Audio OUT Sample Bit Per Sample */
  uint32_t                    Volume;              /* Audio OUT volume                */
  uint32_t                    ChannelsNbr;         /* Audio OUT number of channel     */
  uint32_t                    IsMute;              /* Mute state                      */
  uint32_t                    State;               /* Audio OUT State                 */
  uint32_t                    IsMspCallbacksValid; /* Is Msp Callbacks registered      */
}AUDIO_OUT_Ctx_t;

typedef struct
{
  uint32_t AudioFrequency;
  uint32_t AudioMode;
  uint32_t DataSize;
  uint32_t MonoStereoMode;
  uint32_t ClockStrobing;
  uint32_t Synchro;
  uint32_t OutputDrive;
  uint32_t SynchroExt;
  uint32_t FrameLength;
  uint32_t ActiveFrameLength;
  uint32_t SlotActive;
}MX_SAI_Config;

typedef struct
{
  uint32_t SampleRate;
  uint32_t AudioMode;
  uint32_t FullDuplexMode;
}MX_I2S_Config;

#if (USE_HAL_SAI_REGISTER_CALLBACKS == 1)||(USE_HAL_I2S_REGISTER_CALLBACKS == 1)
typedef struct
{
#if (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
  pSAI_CallbackTypeDef  pMspSaiInitCb;
  pSAI_CallbackTypeDef  pMspSaiDeInitCb;
#endif
#if (USE_HAL_I2S_REGISTER_CALLBACKS == 1)
  pI2S_CallbackTypeDef  pMspI2sInitCb;
  pI2S_CallbackTypeDef  pMspI2sDeInitCb;
#endif
}BSP_AUDIO_OUT_Cb_t;
#endif /* (USE_HAL_SAI_REGISTER_CALLBACKS == 1)||(USE_HAL_I2S_REGISTER_CALLBACKS == 1) */


typedef struct
{
  /* Filter parameters */
  DFSDM_Filter_TypeDef   *FilterInstance;
  uint32_t               RegularTrigger;
  uint32_t               SincOrder;
  uint32_t               Oversampling;
  /* Channel parameters */
  DFSDM_Channel_TypeDef *ChannelInstance;
  uint32_t              DigitalMicPins;
  uint32_t              DigitalMicType;
  uint32_t              Channel4Filter;
  uint32_t              ClockDivider;
  uint32_t              RightBitShift;
}MX_DFSDM_Config;

#if ((USE_HAL_DFSDM_REGISTER_CALLBACKS == 1) || (USE_HAL_SAI_REGISTER_CALLBACKS == 1))
typedef struct
{
#if (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
  pSAI_CallbackTypeDef            pMspSaiInitCb;
  pSAI_CallbackTypeDef            pMspSaiDeInitCb;
#endif
#if (USE_HAL_DFSDM_REGISTER_CALLBACKS == 1)
  pDFSDM_Filter_CallbackTypeDef   pMspFltrInitCb;
  pDFSDM_Filter_CallbackTypeDef   pMspFltrDeInitCb;
  pDFSDM_Channel_CallbackTypeDef  pMspChInitCb;
  pDFSDM_Channel_CallbackTypeDef  pMspChDeInitCb;
#endif /* (USE_HAL_DFSDM_REGISTER_CALLBACKS == 1) */
}BSP_AUDIO_IN_Cb_t;
#endif /* ((USE_HAL_DFSDM_REGISTER_CALLBACKS == 1) || (USE_HAL_SAI_REGISTER_CALLBACKS == 1)) */

/**
  * @}
  */

/** @defgroup STM32H735G_DISCO_AUDIO_Exported_Constants AUDIO Exported Constants
  * @{
  */
#define AUDIO_I2C_ADDRESS                0x34U

/* AUDIO FREQUENCY */
#define AUDIO_FREQUENCY_192K     192000U
#define AUDIO_FREQUENCY_176K     176400U
#define AUDIO_FREQUENCY_96K       96000U
#define AUDIO_FREQUENCY_88K       88200U
#define AUDIO_FREQUENCY_48K       48000U
#define AUDIO_FREQUENCY_44K       44100U
#define AUDIO_FREQUENCY_32K       32000U
#define AUDIO_FREQUENCY_22K       22050U
#define AUDIO_FREQUENCY_16K       16000U
#define AUDIO_FREQUENCY_11K       11025U
#define AUDIO_FREQUENCY_8K         8000U

/* Audio bits per sample */
#define AUDIO_RESOLUTION_8B                 8U
#define AUDIO_RESOLUTION_16B                16U
#define AUDIO_RESOLUTION_24B                24U
#define AUDIO_RESOLUTION_32B                32U

/* Audio Out devices */
#define AUDIO_OUT_DEVICE_NONE               0U
#define AUDIO_OUT_DEVICE_SPEAKER            1U
#define AUDIO_OUT_DEVICE_HEADPHONE          2U
#define AUDIO_OUT_DEVICE_SPK_HP             3U
#define AUDIO_OUT_DEVICE_AUTO               4U
#define AUDIO_OUT_DEVICE_HDMI               5U

/* Audio Mute state */
#define BSP_AUDIO_MUTE_DISABLED             0U
#define BSP_AUDIO_MUTE_ENABLED              1U

/* Audio Out states */
#define AUDIO_OUT_STATE_RESET               0U
#define AUDIO_OUT_STATE_PLAYING             1U
#define AUDIO_OUT_STATE_STOP                2U
#define AUDIO_OUT_STATE_PAUSE               3U

/* Audio Out states */
/* Volume Input Output selection */
#define AUDIO_VOLUME_INPUT                  0U
#define AUDIO_VOLUME_OUTPUT                 1U

/* Codec commands */
#define CODEC_PDWN_SW                       1U
#define CODEC_MUTE_ON                       1U
#define CODEC_MUTE_OFF                      0U

/* Audio Out instances number */
#define AUDIO_OUT_INSTANCES_NBR             1U

/** CODEC_AudioFrame_SLOT_TDMMode In W8994 codec the Audio frame contains 4 slots : TDM Mode
  * TDM format :
  * +------------------|------------------|--------------------|-------------------+
  * | CODEC_SLOT0 Left | CODEC_SLOT1 Left | CODEC_SLOT0 Right  | CODEC_SLOT1 Right |
  * +------------------------------------------------------------------------------+
  */
/* To have 2 separate audio stream in Both headphone and speaker the 4 slot must be activated */
#define CODEC_AUDIOFRAME_SLOT_0123                   SAI_SLOTACTIVE_0 | SAI_SLOTACTIVE_1 | SAI_SLOTACTIVE_2 | SAI_SLOTACTIVE_3
/* To have an audio stream in headphone only SAI Slot 0 and Slot 2 must be activated */
#define CODEC_AUDIOFRAME_SLOT_02                     SAI_SLOTACTIVE_0 | SAI_SLOTACTIVE_2
/* To have an audio stream in speaker only SAI Slot 1 and Slot 3 must be activated */
#define CODEC_AUDIOFRAME_SLOT_13                     SAI_SLOTACTIVE_1 | SAI_SLOTACTIVE_3
/* SAI peripheral configuration defines */
#define AUDIO_OUT_SAIx                           SAI1_Block_B
#define AUDIO_OUT_SAIx_CLK_ENABLE()              __HAL_RCC_SAI1_CLK_ENABLE()
#define AUDIO_OUT_SAIx_CLK_DISABLE()             __HAL_RCC_SAI1_CLK_DISABLE()

#define AUDIO_OUT_SAIx_MCLK_ENABLE()             __HAL_RCC_GPIOF_CLK_ENABLE()
#define AUDIO_OUT_SAIx_MCLK_GPIO_PORT            GPIOF
#define AUDIO_OUT_SAIx_MCLK_PIN                  GPIO_PIN_7
#define AUDIO_OUT_SAIx_MCLK_AF                   GPIO_AF6_SAI1

#define AUDIO_OUT_SAIx_SCK_ENABLE()              __HAL_RCC_GPIOF_CLK_ENABLE()
#define AUDIO_OUT_SAIx_SCK_GPIO_PORT             GPIOF
#define AUDIO_OUT_SAIx_SCK_PIN                   GPIO_PIN_8
#define AUDIO_OUT_SAIx_SCK_AF                    GPIO_AF6_SAI1

#define AUDIO_OUT_SAIx_SD_ENABLE()               __HAL_RCC_GPIOF_CLK_ENABLE()
#define AUDIO_OUT_SAIx_SD_GPIO_PORT              GPIOF
#define AUDIO_OUT_SAIx_SD_PIN                    GPIO_PIN_6
#define AUDIO_OUT_SAIx_SD_AF                     GPIO_AF6_SAI1

#define AUDIO_OUT_SAIx_FS_ENABLE()               __HAL_RCC_GPIOF_CLK_ENABLE()
#define AUDIO_OUT_SAIx_FS_GPIO_PORT              GPIOF
#define AUDIO_OUT_SAIx_FS_PIN                    GPIO_PIN_9
#define AUDIO_OUT_SAIx_FS_AF                     GPIO_AF6_SAI1

/* SAI DMA Stream definitions */
#define AUDIO_OUT_SAIx_DMAx_CLK_ENABLE()         __HAL_RCC_DMA2_CLK_ENABLE()
#define AUDIO_OUT_SAIx_DMAx_STREAM               DMA2_Stream6
#define AUDIO_OUT_SAIx_DMAx_REQUEST              DMA_REQUEST_SAI1_B
#define AUDIO_OUT_SAIx_DMAx_IRQ                  DMA2_Stream6_IRQn
#define AUDIO_OUT_SAIx_DMAx_PERIPH_DATA_SIZE     DMA_PDATAALIGN_HALFWORD
#define AUDIO_OUT_SAIx_DMAx_MEM_DATA_SIZE        DMA_MDATAALIGN_HALFWORD
#define AUDIO_OUT_SAIx_DMAx_IRQHandler           DMA2_Stream6_IRQHandler

/*------------------------------------------------------------------------------
                        AUDIO IN CONFIGURATION
------------------------------------------------------------------------------*/
/* SAI peripheral configuration defines */
#define AUDIO_IN_SAIx                           SAI1_Block_A
#define AUDIO_IN_SAIx_CLK_ENABLE()              __HAL_RCC_SAI1_CLK_ENABLE()
#define AUDIO_IN_SAIx_CLK_DISABLE()             __HAL_RCC_SAI1_CLK_DISABLE()
#define AUDIO_IN_SAIx_AF                        GPIO_AF6_SAI1
#define AUDIO_IN_SAIx_SD_ENABLE()               __HAL_RCC_GPIOE_CLK_ENABLE()
#define AUDIO_IN_SAIx_SD_GPIO_PORT              GPIOE
#define AUDIO_IN_SAIx_SD_PIN                    GPIO_PIN_6

/* SAI DMA Stream definitions */
#define AUDIO_IN_SAIx_DMAx_CLK_ENABLE()         __HAL_RCC_DMA2_CLK_ENABLE()
#define AUDIO_IN_SAIx_DMAx_STREAM               DMA2_Stream4
#define AUDIO_IN_SAIx_DMAx_REQUEST              DMA_REQUEST_SAI1_A
#define AUDIO_IN_SAIx_DMAx_IRQ                  DMA2_Stream4_IRQn
#define AUDIO_IN_SAIx_DMAx_PERIPH_DATA_SIZE     DMA_PDATAALIGN_HALFWORD
#define AUDIO_IN_SAIx_DMAx_MEM_DATA_SIZE        DMA_MDATAALIGN_HALFWORD
#define AUDIO_IN_SAIx_DMAx_IRQHandler           DMA2_Stream4_IRQHandler

/* SAI PDM input definitions */
#define AUDIO_IN_SAI_PDMx                            SAI4_Block_A
#define AUDIO_IN_SAI_PDMx_CLK_ENABLE()               __HAL_RCC_SAI4_CLK_ENABLE()
#define AUDIO_IN_SAI_PDMx_CLK_DISABLE()              __HAL_RCC_SAI4_CLK_DISABLE()
//#define AUDIO_IN_SAI_PDMx_FS_SCK_AF                  GPIO_AF8_SAI4
//#define AUDIO_IN_SAI_PDMx_FS_SCK_ENABLE()            __HAL_RCC_GPIOE_CLK_ENABLE()
//#define AUDIO_IN_SAI_PDMx_FS_SCK_GPIO_PORT           GPIOE
//#define AUDIO_IN_SAI_PDMx_FS_PIN                     GPIO_PIN_4
//#define AUDIO_IN_SAI_PDMx_SCK_PIN                    GPIO_PIN_5

#define AUDIO_IN_SAI_PDMx_CLK_OUT_ENABLE()            __HAL_RCC_GPIOE_CLK_ENABLE()
#define AUDIO_IN_SAI_PDMx_CLK_OUT_PIN                 GPIO_PIN_5
#define AUDIO_IN_SAI_PDMx_CLK_OUT_PORT                GPIOE
#define AUDIO_IN_SAI_PDMx_DATA_IN_ENABLE()           __HAL_RCC_GPIOE_CLK_ENABLE()
#define AUDIO_IN_SAI_PDMx_DATA_IN_PIN                GPIO_PIN_4
#define AUDIO_IN_SAI_PDMx_DATA_IN_PORT               GPIOE
#define AUDIO_IN_SAI_PDMx_DATA_CLK_AF                GPIO_AF10_SAI4
#define AUDIO_IN_SAI_PDMx_IRQHandler                 SAI4_IRQHandler
#define AUDIO_IN_SAI_PDMx_IRQ                        SAI4_IRQn

/* SAI PDM DMA Stream definitions */
#define AUDIO_IN_SAI_PDMx_DMAx_CLK_ENABLE()          __HAL_RCC_BDMA_CLK_ENABLE()
#define AUDIO_IN_SAI_PDMx_DMAx_STREAM                BDMA_Channel1
#define AUDIO_IN_SAI_PDMx_DMAx_REQUEST               BDMA_REQUEST_SAI4_A
#define AUDIO_IN_SAI_PDMx_DMAx_IRQ                   BDMA_Channel1_IRQn
#define AUDIO_IN_SAI_PDMx_DMAx_PERIPH_DATA_SIZE      DMA_PDATAALIGN_BYTE
#define AUDIO_IN_SAI_PDMx_DMAx_MEM_DATA_SIZE         DMA_MDATAALIGN_BYTE
#define AUDIO_IN_SAI_PDMx_DMAx_IRQHandler            BDMA_Channel1_IRQHandler

/* DFSDM Configuration defines */
#define AUDIO_DFSDMx_MIC1_CHANNEL                    DFSDM1_Channel2
#define AUDIO_DFSDMx_MIC2_CHANNEL                    DFSDM1_Channel1
#define AUDIO_DFSDMx_MIC3_CHANNEL                    DFSDM1_Channel6
#define AUDIO_DFSDMx_MIC4_CHANNEL                    DFSDM1_Channel5

#define AUDIO_DFSDMx_MIC1_CHANNEL_FOR_FILTER         DFSDM_CHANNEL_2
#define AUDIO_DFSDMx_MIC2_CHANNEL_FOR_FILTER         DFSDM_CHANNEL_1
#define AUDIO_DFSDMx_MIC3_CHANNEL_FOR_FILTER         DFSDM_CHANNEL_6
#define AUDIO_DFSDMx_MIC4_CHANNEL_FOR_FILTER         DFSDM_CHANNEL_5

#define AUDIO_DFSDMx_MIC1_FILTER                     DFSDM1_Filter0
#define AUDIO_DFSDMx_MIC2_FILTER                     DFSDM1_Filter1
#define AUDIO_DFSDMx_MIC3_FILTER                     DFSDM1_Filter2
#define AUDIO_DFSDMx_MIC4_FILTER                     DFSDM1_Filter3

#define AUDIO_DFSDM1_CLK_ENABLE()                    __HAL_RCC_DFSDM1_CLK_ENABLE()

/* DATIN for MIC1 (GPIOE_PIN_7) */
#define AUDIO_DFSDMx_DATIN_MIC1_PIN                  GPIO_PIN_7
#define AUDIO_DFSDMx_DATIN_MIC1_AF                   GPIO_AF3_DFSDM1
#define AUDIO_DFSDMx_DATIN_MIC1_GPIO_PORT            GPIOE
#define AUDIO_DFSDMx_DATIN_MIC1_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOE_CLK_ENABLE()

/* DATIN for MIC2 (GPIOE_PIN_7)*/
#define AUDIO_DFSDMx_DATIN_MIC2_PIN                   GPIO_PIN_7
#define AUDIO_DFSDMx_DATIN_MIC2_AF                    GPIO_AF3_DFSDM1
#define AUDIO_DFSDMx_DATIN_MIC2_GPIO_PORT             GPIOE
#define AUDIO_DFSDMx_DATIN_MIC2_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOE_CLK_ENABLE()

/* DATIN for MIC3 (GPIOF_PIN_13)  */
#define AUDIO_DFSDMx_DATIN_MIC3_PIN                  GPIO_PIN_13
#define AUDIO_DFSDMx_DATIN_MIC3_AF                   GPIO_AF3_DFSDM1
#define AUDIO_DFSDMx_DATIN_MIC3_GPIO_PORT            GPIOF
#define AUDIO_DFSDMx_DATIN_MIC3_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOF_CLK_ENABLE()

/* DATIN for MIC4  (GPIOF_PIN_13)*/
#define AUDIO_DFSDMx_DATIN_MIC4_PIN                  GPIO_PIN_13
#define AUDIO_DFSDMx_DATIN_MIC4_AF                   GPIO_AF3_DFSDM1
#define AUDIO_DFSDMx_DATIN_MIC4_GPIO_PORT            GPIOF
#define AUDIO_DFSDMx_DATIN_MIC4_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOF_CLK_ENABLE()

/* CKOUT for all mics connected to DFSDM1 (GPIOE_PIN_9)*/
#define AUDIO_DFSDM1_CKOUT_PIN                       GPIO_PIN_9
#define AUDIO_DFSDM1_CKOUT_AF                        GPIO_AF3_DFSDM1
#define AUDIO_DFSDM1_CKOUT_GPIO_PORT                 GPIOE
#define AUDIO_DFSDM1_CKOUT_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOE_CLK_ENABLE()

/* DFSDM DMA MIC1, MIC2, MIC3 and MIC4 channels definitions */
#define AUDIO_DFSDMx_DMAx_MIC1_STREAM                DMA2_Stream7
#define AUDIO_DFSDMx_DMAx_MIC1_REQUEST               (uint32_t)DMA_REQUEST_DFSDM1_FLT0
#define AUDIO_DFSDMx_DMAx_MIC1_IRQ                   DMA2_Stream7_IRQn
#define AUDIO_DFSDM_DMAx_MIC1_IRQHandler             DMA2_Stream7_IRQHandler

#define AUDIO_DFSDMx_DMAx_MIC2_STREAM                DMA2_Stream0
#define AUDIO_DFSDMx_DMAx_MIC2_REQUEST               (uint32_t)DMA_REQUEST_DFSDM1_FLT1
#define AUDIO_DFSDMx_DMAx_MIC2_IRQ                   DMA2_Stream0_IRQn
#define AUDIO_DFSDM_DMAx_MIC2_IRQHandler             DMA2_Stream0_IRQHandler

#define AUDIO_DFSDMx_DMAx_MIC3_STREAM                DMA2_Stream3
#define AUDIO_DFSDMx_DMAx_MIC3_REQUEST               (uint32_t)DMA_REQUEST_DFSDM1_FLT2
#define AUDIO_DFSDMx_DMAx_MIC3_IRQ                   DMA2_Stream3_IRQn
#define AUDIO_DFSDM_DMAx_MIC3_IRQHandler             DMA2_Stream3_IRQHandler

#define AUDIO_DFSDMx_DMAx_MIC4_STREAM                DMA2_Stream2
#define AUDIO_DFSDMx_DMAx_MIC4_REQUEST               (uint32_t)DMA_REQUEST_DFSDM1_FLT3
#define AUDIO_DFSDMx_DMAx_MIC4_IRQ                   DMA2_Stream2_IRQn
#define AUDIO_DFSDM_DMAx_MIC4_IRQHandler             DMA2_Stream2_IRQHandler

#define AUDIO_DFSDMx_DMAx_PERIPH_DATA_SIZE           DMA_PDATAALIGN_WORD
#define AUDIO_DFSDMx_DMAx_MEM_DATA_SIZE              DMA_MDATAALIGN_WORD
#define AUDIO_DFSDM1_DMAx_CLK_ENABLE()               __HAL_RCC_DMA2_CLK_ENABLE()

/* Audio In devices */
/* Analog microphone input from 3.5 audio jack connector */
#define AUDIO_IN_DEVICE_ANALOG_MIC        0x00U
#define AUDIO_IN_DEVICE_ANALOG_LINE1      0x01U

/* MP34DT01TR digital microphone on PCB top side */
#define AUDIO_IN_DEVICE_DIGITAL_MIC1      0x010U
#define AUDIO_IN_DEVICE_DIGITAL_MIC2      0x020U
#define AUDIO_IN_DEVICE_DIGITAL_MIC3      0x040U
#define AUDIO_IN_DEVICE_DIGITAL_MIC4      0x080U
#define AUDIO_IN_DEVICE_DIGITAL_MIC_LAST  AUDIO_IN_DEVICE_DIGITAL_MIC4
#define AUDIO_IN_DEVICE_DIGITAL_MIC       (AUDIO_IN_DEVICE_DIGITAL_MIC1 | AUDIO_IN_DEVICE_DIGITAL_MIC2)

#define DFSDM_MIC_NUMBER                   4U

/* Audio In states */
#define AUDIO_IN_STATE_RESET               0U
#define AUDIO_IN_STATE_RECORDING           1U
#define AUDIO_IN_STATE_STOP                2U
#define AUDIO_IN_STATE_PAUSE               3U

/* Audio In instances number */
#define AUDIO_IN_INSTANCES_NBR             3U
/**
  * @}
  */

/** @defgroup STM32H735G_DISCO_AUDIO_Exported_Macros AUDIO Exported Macros
  * @{
  */
#define POS_VAL(VAL)                  (POSITION_VAL(VAL) - 4U)
#define VOLUME_OUT_CONVERT(Volume)    (((Volume) > 100)? 63:((uint8_t)(((Volume) * 63) / 100)))
#define VOLUME_IN_CONVERT(Volume)     (((Volume) >= 100)? 239:((uint8_t)(((Volume) * 239) / 100)))

/**
  * @}
  */

/** @addtogroup STM32H735G_DISCO_AUDIO_Exported_Variables
  * @{
  */
/* Audio in and out component object */
extern void *AudioCompObj;
/* Play  */
extern SAI_HandleTypeDef                      haudio_out_sai;
extern AUDIO_OUT_Ctx_t                        Audio_Out_Ctx[];

/* Record */
extern DFSDM_Filter_HandleTypeDef             haudio_in_dfsdm_filter[];
extern DFSDM_Channel_HandleTypeDef            haudio_in_dfsdm_channel[];
extern SAI_HandleTypeDef                      haudio_in_sai[];
extern AUDIO_IN_Ctx_t                         Audio_In_Ctx[];
/**
  * @}
  */

/** @addtogroup STM32H735G_DISCO_AUDIO_OUT_Exported_Functions
  * @{
  */
int32_t BSP_AUDIO_OUT_Init(uint32_t Instance, BSP_AUDIO_Init_t* AudioInit);
int32_t BSP_AUDIO_OUT_DeInit(uint32_t Instance);

#if (USE_HAL_SAI_REGISTER_CALLBACKS == 1) || (USE_HAL_I2S_REGISTER_CALLBACKS == 1)
int32_t BSP_AUDIO_OUT_RegisterMspCallbacks (uint32_t Instance, BSP_AUDIO_OUT_Cb_t *CallBacks);
int32_t BSP_AUDIO_OUT_RegisterDefaultMspCallbacks (uint32_t Instance);
#endif /* (USE_HAL_SAI_REGISTER_CALLBACKS == 1)|| (USE_HAL_I2S_REGISTER_CALLBACKS == 1) */

int32_t BSP_AUDIO_OUT_Play(uint32_t Instance, uint8_t* pData, uint32_t NbrOfBytes);
int32_t BSP_AUDIO_OUT_Pause(uint32_t Instance);
int32_t BSP_AUDIO_OUT_Resume(uint32_t Instance);
int32_t BSP_AUDIO_OUT_Stop(uint32_t Instance);
int32_t BSP_AUDIO_OUT_Mute(uint32_t Instance);
int32_t BSP_AUDIO_OUT_UnMute(uint32_t Instance);
int32_t BSP_AUDIO_OUT_IsMute(uint32_t Instance, uint32_t *IsMute);

int32_t BSP_AUDIO_OUT_SetDevice(uint32_t Instance, uint32_t Device);
int32_t BSP_AUDIO_OUT_GetDevice(uint32_t Instance, uint32_t *Device);

int32_t BSP_AUDIO_OUT_SetSampleRate(uint32_t Instance, uint32_t SampleRate);
int32_t BSP_AUDIO_OUT_GetSampleRate(uint32_t Instance, uint32_t *SampleRate);

int32_t BSP_AUDIO_OUT_SetBitsPerSample(uint32_t Instance, uint32_t BitsPerSample);
int32_t BSP_AUDIO_OUT_GetBitsPerSample(uint32_t Instance, uint32_t *BitsPerSample);

int32_t BSP_AUDIO_OUT_SetChannelsNbr(uint32_t Instance, uint32_t ChannelNbr);
int32_t BSP_AUDIO_OUT_GetChannelsNbr(uint32_t Instance, uint32_t *ChannelNbr);

int32_t BSP_AUDIO_OUT_SetVolume(uint32_t Instance, uint32_t Volume);
int32_t BSP_AUDIO_OUT_GetVolume(uint32_t Instance, uint32_t *Volume);
int32_t BSP_AUDIO_OUT_GetState(uint32_t Instance, uint32_t *State);

void BSP_AUDIO_OUT_IRQHandler(uint32_t Instance);

/* User Callbacks: user has to implement these functions in his code if they are needed. */
/* This function is called when the requested data has been completely transferred.*/
void    BSP_AUDIO_OUT_TransferComplete_CallBack(uint32_t Instance);

/* This function is called when half of the requested buffer has been transferred. */
void    BSP_AUDIO_OUT_HalfTransfer_CallBack(uint32_t Instance);

/* This function is called when an Interrupt due to transfer error on or peripheral
   error occurs. */
void    BSP_AUDIO_OUT_Error_CallBack(uint32_t Instance);

/* These function can be modified in case the current settings need to be changed
   for specific application needs */
HAL_StatusTypeDef MX_SAI1_ClockConfig(SAI_HandleTypeDef *hsai, uint32_t SampleRate);
HAL_StatusTypeDef MX_SAI1_Block_A_Init(SAI_HandleTypeDef* hsai, MX_SAI_Config *MXConfig);
HAL_StatusTypeDef MX_I2S6_ClockConfig(I2S_HandleTypeDef *hi2s, uint32_t SampleRate);
HAL_StatusTypeDef MX_I2S6_Init(I2S_HandleTypeDef* hi2s, MX_I2S_Config *MXConfig);
/**
  * @}
  */

/** @addtogroup STM32H735G_DISCO_AUDIO_IN_Exported_Functions
  * @{
  */
int32_t BSP_AUDIO_IN_Init(uint32_t Instance, BSP_AUDIO_Init_t* AudioInit);
int32_t BSP_AUDIO_IN_OUT_Init_Ex(uint32_t InstanceIn, uint32_t InstanceOut, BSP_AUDIO_Init_t* AudioInitIn, BSP_AUDIO_Init_t* AudioInitOut);

int32_t BSP_AUDIO_IN_DeInit(uint32_t Instance);
#if ((USE_HAL_DFSDM_REGISTER_CALLBACKS == 1) || (USE_HAL_SAI_REGISTER_CALLBACKS == 1))
int32_t BSP_AUDIO_IN_RegisterDefaultMspCallbacks (uint32_t Instance);
int32_t BSP_AUDIO_IN_RegisterMspCallbacks (uint32_t Instance, BSP_AUDIO_IN_Cb_t *CallBacks);
#endif /* ((USE_HAL_DFSDM_REGISTER_CALLBACKS == 1) || (USE_HAL_SAI_REGISTER_CALLBACKS == 1)) */
int32_t BSP_AUDIO_IN_Record(uint32_t Instance, uint8_t* pBuf, uint32_t NbrOfBytes);
int32_t BSP_AUDIO_IN_Record_Ex(uint32_t Instance, uint8_t* pBuf, uint32_t NbrOfBytes);

int32_t BSP_AUDIO_IN_Stop(uint32_t Instance);
int32_t BSP_AUDIO_IN_Pause(uint32_t Instance);
int32_t BSP_AUDIO_IN_Resume(uint32_t Instance);

int32_t BSP_AUDIO_IN_RecordChannels(uint32_t Instance, uint8_t **pBuf, uint32_t NbrOfBytes);
int32_t BSP_AUDIO_IN_StopChannels(uint32_t Instance, uint32_t Device);
int32_t BSP_AUDIO_IN_PauseChannels(uint32_t Instance, uint32_t Device);
int32_t BSP_AUDIO_IN_ResumeChannels(uint32_t Instance, uint32_t Device);

int32_t BSP_AUDIO_IN_SetDevice(uint32_t Instance, uint32_t Device);
int32_t BSP_AUDIO_IN_GetDevice(uint32_t Instance, uint32_t *Device);

int32_t BSP_AUDIO_IN_SetSampleRate(uint32_t Instance, uint32_t SampleRate);
int32_t BSP_AUDIO_IN_GetSampleRate(uint32_t Instance, uint32_t *SampleRate);

int32_t BSP_AUDIO_IN_SetBitsPerSample(uint32_t Instance, uint32_t BitsPerSample);
int32_t BSP_AUDIO_IN_GetBitsPerSample(uint32_t Instance, uint32_t *BitsPerSample);

int32_t BSP_AUDIO_IN_SetChannelsNbr(uint32_t Instance, uint32_t ChannelNbr);
int32_t BSP_AUDIO_IN_GetChannelsNbr(uint32_t Instance, uint32_t *ChannelNbr);

int32_t BSP_AUDIO_IN_SetVolume(uint32_t Instance, uint32_t Volume);
int32_t BSP_AUDIO_IN_GetVolume(uint32_t Instance, uint32_t *Volume);
int32_t BSP_AUDIO_IN_GetState(uint32_t Instance, uint32_t *State);
void BSP_AUDIO_IN_IRQHandler(uint32_t Instance, uint32_t InputDevice);

#if (USE_BSP_PDM_LIB_FEATURE > 0U)
/* Specific PDM recodr APIs */
int32_t BSP_AUDIO_IN_PDMToPCM_Init(uint32_t Instance, uint32_t AudioFreq, uint32_t ChnlNbrIn, uint32_t ChnlNbrOut);
int32_t BSP_AUDIO_IN_PDMToPCM(uint32_t Instance, uint16_t *PDMBuf, uint16_t *PCMBuf);
#endif
int32_t BSP_AUDIO_IN_RecordPDM(uint32_t Instance, uint8_t* pBuf, uint32_t NbrOfBytes);

/* User Callbacks: user has to implement these functions in his code if they are needed. */
/* This function should be implemented by the user application.
   It is called into this driver when the current buffer is filled to prepare the next
   buffer pointer and its size. */
void BSP_AUDIO_IN_TransferComplete_CallBack(uint32_t Instance);
void BSP_AUDIO_IN_HalfTransfer_CallBack(uint32_t Instance);

/* This function is called when an Interrupt due to transfer error on or peripheral
   error occurs. */
void BSP_AUDIO_IN_Error_CallBack(uint32_t Instance);

/* These function can be modified in case the current settings (e.g. DMA stream)
   need to be changed for specific application needs */
HAL_StatusTypeDef MX_DFSDM1_ClockConfig(DFSDM_Channel_HandleTypeDef *hDfsdmChannel, uint32_t SampleRate);
HAL_StatusTypeDef MX_DFSDM1_Init(DFSDM_Filter_HandleTypeDef *hDfsdmFilter, DFSDM_Channel_HandleTypeDef *hDfsdmChannel, MX_DFSDM_Config *MXConfig);
HAL_StatusTypeDef MX_DFSDM2_ClockConfig(DFSDM_Channel_HandleTypeDef *hDfsdmChannel, uint32_t SampleRate);
HAL_StatusTypeDef MX_DFSDM2_Init(DFSDM_Filter_HandleTypeDef *hDfsdmFilter, DFSDM_Channel_HandleTypeDef *hDfsdmChannel, MX_DFSDM_Config *MXConfig);
HAL_StatusTypeDef MX_SAI1_Block_B_Init(SAI_HandleTypeDef* hsai, MX_SAI_Config *MXConfig);
HAL_StatusTypeDef MX_SAI4_ClockConfig(SAI_HandleTypeDef *hsai, uint32_t SampleRate);
HAL_StatusTypeDef MX_SAI4_Block_A_Init(SAI_HandleTypeDef* hsai, MX_SAI_Config *MXConfig);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H735G_DISCO_AUDIO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
