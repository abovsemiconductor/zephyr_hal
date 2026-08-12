/**
 *******************************************************************************
 * @file        hal_qei.h
 * @author      ABOV R&D Division
 * @brief       Quadrature Encoder Interface (QEI)
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
 * @defgroup    HAL_QEI QEI
 * @{
 * @brief       Quadrature Encoder Interface (QEI)
 */

#ifndef _HAL_QEI_H_
#define _HAL_QEI_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief QEI Instance Id
 */
typedef enum
{
    QEI_ID_0,
    QEI_ID_1,
    QEI_ID_2,
    QEI_ID_3,
    QEI_ID_4,
    QEI_ID_5,
    QEI_ID_6,
    QEI_ID_7,
    QEI_ID_8,
    QEI_ID_9,
    QEI_ID_MAX
} QEI_ID_e;

/**
 * @brief QEI Counter
 */
typedef enum
{
    QEI_COUNTER_POSITION = BIT(0),    /**< Position Counter */
    QEI_COUNTER_INDEX    = BIT(1),    /**< Index Counter */
    QEI_COUNTER_VELOCITY = BIT(2),    /**< Velocity Counter */
    QEI_COUNTER_MAX
} QEI_COUNTER_e;

/**
 * @brief QEI Direction
 */
typedef enum
{
    QEI_DIR_REVERSE,    /**< Reverse Direction */
    QEI_DIR_FORWARD,    /**< Forward Direction */
    QEI_DIR_MAX
} QEI_DIR_e;

/**
 * @brief QEI Signal Mode
 */
typedef enum
{
    QEI_SIG_MODE_QUADRATURE,         /**< Phase-A and Phase-B */
    QEI_SIG_MODE_CLOCK_DIRECTION,    /**< Phase-A (Clock) and Phase-B (Direction) */
    QEI_SIG_MODE_MAX
} QEI_SIG_MODE_e;

/**
 * @brief QEI Capture Count
 */
typedef enum
{
    QEI_CAP_COUNT_PHA_EDGE,     /**< Only Phase-A Edge */
    QEI_CAP_COUNT_BOTH_EDGE,    /**< Both (Phase-A and Phase-B) Edge */
    QEI_CAP_COUNT_MAX
} QEI_CAP_COUNT_e;

/**
 * @brief QEI Position Counter Reset
 */
typedef enum
{
    QEI_POS_CNTER_RST_MAXIMUM,    /**< Reset by the Maximum Position */
    QEI_POS_CNTER_RST_INDEX,      /**< Reset by an Index Pulse */
    QEI_POS_CNTER_RST_MAX
} QEI_POS_CNTER_RST_e;

/**
 * @brief QEI Position Counter Reset by Index
 */
typedef enum
{
    QEI_POS_CNTER_RST_IDX_1_0,        /**< Reset when Phase-A High and Phase-B Low */
    QEI_POS_CNTER_RST_IDX_1_1,        /**< Reset when Phase-A High and Phase-B High */
    QEI_POS_CNTER_RST_IDX_0_1,        /**< Reset when Phase-A Low and Phase-B High */
    QEI_POS_CNTER_RST_IDX_0_0,        /**< Reset when Phase-A Low and Phase-B Low */
    QEI_POS_CNTER_RST_IDX_DISABLE,    /**< Reset Disable */
    QEI_POS_CNTER_RST_IDX_MAX
} QEI_POS_CNTER_RST_IDX_e;

/**
 * @brief QEI Interrupt Type
 */
typedef enum
{
    QEI_INTR_IDX_PULSE                 = BIT(0),     /**< Index Pulse Rising edge */
    QEI_INTR_DIR_CHANGE                = BIT(1),     /**< Direction Changed */
    QEI_INTR_PHASE_ERROR               = BIT(2),     /**< Phase Error */
    QEI_INTR_CLOCK_PULSE               = BIT(3),     /**< Rising and Falling edge of the Ph-A */
    QEI_INTR_COMPARE_MATCH_0           = BIT(4),     /**< Position 0 Compare value matchs current Counter */
    QEI_INTR_COMPARE_MATCH_1           = BIT(5),     /**< Position 1 Compare value matchs current Counter */
    QEI_INTR_COMPARE_MATCH_2           = BIT(6),     /**< Position 2 Compare value matchs current Counter */
    QEI_INTR_MAXIMUM_MATCH             = BIT(7),     /**< Position Counter value matchs Maximum value */
    QEI_INTR_IDX_MATCH                 = BIT(8),     /**< Index Counter value matched Compare Value */
    QEI_INTR_VELOCITY_ZERO             = BIT(9),     /**< Velocity Timer value becomes Zero */
    QEI_INTR_VELOCITY_UNDER_COMPARE    = BIT(10),    /**< Capture value smaller than Velocity Compare value is entered */
    QEI_INTR_MAX
} QEI_INTR_e;

/**
 * @brief QEI Event Type
 */
typedef enum
{
    QEI_EVENT_IDX_PULSE                 = BIT(0),     /**< Index Pulse Generation */
    QEI_EVENT_DIR_CHANGE                = BIT(1),     /**< Direction Changed */
    QEI_EVENT_PHASE_ERROR               = BIT(2),     /**< Decoder Phase Error */
    QEI_EVENT_CLOCK_PULSE               = BIT(3),     /**< Decoder Clock Pulse Generation */
    QEI_EVENT_COMPARE_MATCH_0           = BIT(4),     /**< Position 0 Compare value matchs current Counter */
    QEI_EVENT_COMPARE_MATCH_1           = BIT(5),     /**< Position 1 Compare value matchs current Counter */
    QEI_EVENT_COMPARE_MATCH_2           = BIT(6),     /**< Position 2 Compare value matchs current Counter */
    QEI_EVENT_MAXIMUM_MATCH             = BIT(7),     /**< Position Counter value matchs Maximum value */
    QEI_EVENT_IDX_MATCH                 = BIT(8),     /**< Index Counter value matched Compare Value */
    QEI_EVENT_VELOCITY_ZERO             = BIT(9),     /**< Velocity Timer value becomes Zero */
    QEI_EVENT_VELOCITY_UNDER_COMPARE    = BIT(10),    /**< Capture value smaller than Velocity Compare value is entered */
    QEI_EVENT_MAX
} QEI_EVENT_e;

/**
 * @brief QEI Operation
 */
typedef enum
{
    QEI_OPS_POLL,    /**< Operation Polling */
    QEI_OPS_INTR,    /**< Operation Interrupt */
    QEI_OPS_NMI,     /**< Operation NMI */
    QEI_OPS_MAX
} QEI_OPS_e;

/**
 * @brief QEI Compare Configuration
 */
typedef struct
{
    uint8_t un8Num;          /**< Compare Channel Number */
    bool bIntrEnable;        /**< Compare Interrupt Enable */
    uint32_t un32Compare;    /**< Compare Value of un8Num */
} QEI_CMP_CFG_t;

/**
 * @brief QEI Velocity Configuration
 */
typedef struct
{
    bool bEnable;
    bool bIntrEnable;
    uint16_t un16Reload;     /**< Reload value when Velocity Timer value becomes zero */
    uint16_t un16Timer;      /**< Velocity Timer value */
    uint16_t un16Compare;    /**< Velocity Compare value */
} QEI_VEL_CFG_t;

/**
 * @brief QEI Mode Configuration
 */
typedef struct
{
    QEI_SIG_MODE_e             eSigMode;
    QEI_CAP_COUNT_e            eCapCnt;
    QEI_POS_CNTER_RST_e        ePosRst;
    QEI_POS_CNTER_RST_IDX_e    ePosRstIdx;
    uint16_t                   un16IntrEnable;       /**< Interrupt Enable without Velocity and Compare N ::QEI_INTR_e */
    bool                       bSwap;                /**< true : Swap Ph-A and Ph-B */
    bool                       bPosCntDir;           /**< true : count direction changed by direction status */
    bool                       bIdxCntDir;           /**< true : count direction changed by direction status */
    bool                       bIdxPulseInverted;    /**< true : Index Pulse inverted */
    uint32_t                   un32PosMaxValue;      /**< Maximum Position Counter Value */
} QEI_CFG_t;

/**
 * @brief QEI IRQ handler context
 */
typedef struct
{
    QEI_ID_e eId;    /**< QEI Instance Id */
} QEI_Context_t;

/**
 *******************************************************************************
 * @brief       QEI Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::QEI_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnQEI_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize QEI.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QEI_Init(QEI_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize QEI.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QEI_Uninit(QEI_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration QEI.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : QEI Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QEI_SetConfig(QEI_ID_e eId, QEI_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set Velocity Configuration QEI.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : QEI Velocity Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QEI_SetVelConfig(QEI_ID_e eId, QEI_VEL_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ QEI.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QEI_SetIRQ(QEI_ID_e eId, QEI_OPS_e eOps, pfnQEI_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Set Counter clear QEI.
 * @param[in]   eId : Instance Id.
 * @param[in]   un8Counter : Counters (Bit-Order)::QEI_COUNTER_e
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QEI_SetCounterClear(QEI_ID_e eId, uint8_t un8Counter);

/**
 *******************************************************************************
 * @brief       Set Compare QEI.
 * @param[in]   eId : Instance Id.
 * @param[in]   eCounter : Counter ::QEI_COUNTER_e
 * @param[in]   *ptCfg: Compare Configuration
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QEI_SetCompare(QEI_ID_e eId, QEI_COUNTER_e eCounter, QEI_CMP_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Start QEI.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QEI_Start(QEI_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop QEI.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QEI_Stop(QEI_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get count value QEI.
 * @param[in]   eId : Instance Id.
 * @param[in]   eCounter : Counter ::QEI_COUNTER_e
 * @param[out]  *pun32Count : current count value
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QEI_GetCount(QEI_ID_e eId, QEI_COUNTER_e eCounter, uint32_t *pun32Count);

/**
 *******************************************************************************
 * @brief       Get direction QEI.
 * @param[in]   eId : Instance Id.
 * @param[out]  *peDir : direction ::QEI_DIR_e
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QEI_GetDirection(QEI_ID_e eId, QEI_DIR_e *peDir);
#ifdef __cplusplus
}
#endif

#endif /* _HAL_QEI_H_ */

/** @} */
/** @} */

