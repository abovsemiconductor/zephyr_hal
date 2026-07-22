/**
 *******************************************************************************
 * @file        hal_dac.h
 * @author      ABOV R&D Division
 * @brief       N-bits Digital to Analog Converter
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/**
 * @addtogroup  HAL HAL (Hardware Abstraction Layer)
 * @{
 * @defgroup    HAL_DAC DAC
 * @{
 * @brief       N-bits Digital to Analog Converter
 */

#ifndef _HAL_DAC_H_
#define _HAL_DAC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief DAC Instance Id
 */
typedef enum
{
    DAC_ID_0,
    DAC_ID_1,
    DAC_ID_2,
    DAC_ID_3,
    DAC_ID_4,
    DAC_ID_5,
    DAC_ID_6,
    DAC_ID_7,
    DAC_ID_8,
    DAC_ID_9,
    DAC_ID_MAX
} DAC_ID_e;

/**
 * @brief DAC Mode
 */
typedef enum
{
    DAC_MODE_MANUAL,
    DAC_MODE_AUTO,
    DAC_MODE_MAX
} DAC_MODE_e;

/**
 * @brief DAC Auto Mode Direction
 */
typedef enum
{
    DAC_AUTO_DIR_INC,    /**< Auto Increment DAC Data */
    DAC_AUTO_DIR_DEC,    /**< Auto Decrement DAC Data */
    DAC_AUTO_DIR_MAX
} DAC_AUTO_DIR_e;

/**
 * @brief DAC Reference Source
 */
typedef enum
{
    DAC_REF_INT,    /**< Internal AVDD */
    DAC_REF_EXT,    /**< External Reference */
    DAC_REF_MAX
} DAC_REF_e;

/**
 * @brief DAC Reload Source
 */
typedef enum
{
    DAC_RLOD_CONST,     /**< Re-load Constantly */
    DAC_RLOD_TIMER10,   /**< Re-load by Timer10 */
    DAC_RLOD_TIMER11,   /**< Re-load by Timer11 */
    DAC_RLOD_MAX
} DAC_RLOD_e;

/**
 * @brief DAC Programmable Gain
 */
typedef enum
{
    DAC_PG_N_30DB,    /**< PG -30dB */
    DAC_PG_N_24DB,    /**< PG -24dB */
    DAC_PG_N_18DB,    /**< PG -18dB */
    DAC_PG_N_12DB,    /**< PG -12dB */
    DAC_PG_N_6DB,     /**< PG -6dB  */
    DAC_PG_0DB,       /**< PG  0dB  */
    DAC_PG_P_6DB,     /**< PG +6dB  */
    DAC_PG_P_12DB,    /**< PG +12dB */
    DAC_PG_P_18DB,    /**< PG +18dB */
    DAC_PG_P_24DB,    /**< PG +24dB */
    DAC_PG_P_30DB,    /**< PG +30dB */
    DAC_PG_MAX
} DAC_PG_e;

/**
 * @brief DAC Offset Mode
 */
typedef enum
{
    DAC_OFS_SUB,     /**< Offset Subtracted by (n + 1) */
    DAC_OFS_ADD,     /**< Offset Added by (n + 1) */
    DAC_OFS_MAX
} DAC_OFS_e;

/**
 * @brief DAC Output Port
 */
typedef enum
{
    DAC_OUT_NONE     = 0,
    DAC_OUT_PORT1    = BIT(0),    /**< DAC Output Port 1 */
    DAC_OUT_PORT2    = BIT(1),    /**< DAC Output Port 2 */
    DAC_OUT_PORT3    = BIT(2),    /**< DAC Output Port 3 */
    DAC_OUT_MAX
} DAC_OUT_e;

/**
 * @brief DAC Operation
 */
typedef enum
{
    DAC_OPS_POLL,        /**< Operation Polling */
    DAC_OPS_INTR,        /**< Operation Interrupt */
    DAC_OPS_INTR_DMA,    /**< Operation Interrupt with DMA */
    DAC_OPS_MAX
} DAC_OPS_e;

/**
 * @brief DAC Event 
 */
typedef enum
{
    DAC_EVENT_DATA_REACHED      = BIT(0),    /**< Incre/Decre Data reached at Auto Mode */
    DAC_EVENT_RX_DONE           = BIT(1),    /**< DMA RX Done */
    DAC_EVENT_RX_UNDERRUN       = BIT(2),    /**< DMA Under-run */
    DAC_EVENT_MAX
} DAC_EVENT_e;

/**
 * @brief DAC OFS Configuration
 */
typedef struct
{
    bool                 bEnable;
    DAC_OFS_e            eOfs;
    uint8_t              un8Ofs;    /**< Offset value for ::DAC_OFS_e */
} DAC_OFS_CFG_t;

/**
 * @brief DAC Mode Configuration
 */
typedef struct
{
    DAC_MODE_e           eMode;
    DAC_AUTO_DIR_e       eAutoDir;
    DAC_REF_e            eRef;
    DAC_PG_e             ePg;
    DAC_RLOD_e           eRLod;
    uint8_t              un8OutPort;    /**< Output Port Enable ::DAC_OUT_e */
    bool                 bOutBuffer;    /**< Output Buffer Enable */
} DAC_CFG_t;

/**
 *******************************************************************************
 * @brief       DAC Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::DAC_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnDAC_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize DAC.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_DAC_Init(DAC_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize DAC.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_DAC_Uninit(DAC_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get MAX Resolution DAC.
 * @return      uint32_t : Max Resolution Value.
 ******************************************************************************/
uint32_t HAL_DAC_GetMaxResolution(void);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration DAC.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : DAC Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_DAC_SetConfig(DAC_ID_e eId, DAC_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set OFS Configuration DAC.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : DAC OFS Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_DAC_SetOfsConfig(DAC_ID_e eId, DAC_OFS_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ DAC.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_DAC_SetIRQ(DAC_ID_e eId, DAC_OPS_e eOps, pfnDAC_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Set DMA DAC if eOps is DAC_OPS_INTR_DMA.
 * @param[in]   eId : Instance Id.
 * @param[in]   un32Addr : Memory Address.
 * @param[in]   un32Len : Data Length.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_DAC_SetDMA(DAC_ID_e eId, uint32_t un32Addr, uint32_t un32Len);

/**
 *******************************************************************************
 * @brief       Start convertion DAC.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_DAC_Start(DAC_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop convertion DAC.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_DAC_Stop(DAC_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Data DAC (or Update Data).
 * @param[in]   eId : Instance Id.
 * @param[in]   un16Data : Data.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_DAC_SetData(DAC_ID_e eId, uint16_t un16Data);

/**
 *******************************************************************************
 * @brief       Get Data(Buffer) DAC.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun32Out : Value of the current Data(Buffer) DAC.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_DAC_GetData(DAC_ID_e eId, uint16_t *pun16Data);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_DAC_H_ */

/** @} */
/** @} */
