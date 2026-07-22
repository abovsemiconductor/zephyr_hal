/**
 *******************************************************************************
 * @file        hal_qspi.h
 * @author      ABOV R&D Division
 * @brief       Quad Serial Peripheral Interface
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
 * @defgroup    HAL_QSPI QSPI
 * @{
 * @brief       Quad Serial Peripheral Interface
 */

#ifndef _HAL_QSPI_H_
#define _HAL_QSPI_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief QSPI Instance Id
 */
typedef enum
{
    QSPI_ID_0,
    QSPI_ID_1,
    QSPI_ID_2,
    QSPI_ID_3,
    QSPI_ID_4,
    QSPI_ID_5,
    QSPI_ID_6,
    QSPI_ID_7,
    QSPI_ID_8,
    QSPI_ID_9,
    QSPI_ID_MAX
} QSPI_ID_e;

/**
 * @brief QSPI Data Charge Mode and Clock Polarity
 */
typedef enum
{
    QSPI_CLK_MODE_TRANS_0_CPOL_0,    /**< Change negative edge Polarity low (Mode 0) */
    QSPI_CLK_MODE_TRANS_0_CPOL_1,    /**< Change negative edge Polarity high (Mode 3) */
    QSPI_CLK_MODE_MAX
} QSPI_CLK_MODE_e;

/**
 * @brief QSPI Clock Edge Selection
 */
typedef enum
{
    QSPI_TRANS_EDGE_NEGATIVE,     /**< Nagative Edge */
    QSPI_TRANS_EDGE_POSITIVE,    /**< Positive Edge */
    QSPI_TRANS_MAX,
} QSPI_TRANS_EDGE_e;

/**
 * @brief QSPI Event
 */
typedef enum
{
    QSPI_EVENT_CLEAR        = 0x00,
    QSPI_EVENT_TX_DONE      = BIT(0),    /**< Transmit completed */
    QSPI_EVENT_RX_DONE      = BIT(1),    /**< Receive completed */
    QSPI_EVENT_TX_ERROR     = BIT(2),    /**< Overrun occurred */
    QSPI_EVENT_RX_ERROR     = BIT(3),    /**< Underrun occurred */
    QSPI_EVENT_MAX
} QSPI_EVENT_e;

/**
 * @brief QSPI Data Charge Mode and Clock Polarity
 */
typedef enum
{
    QSPI_PHASE_CMD,
    QSPI_PHASE_ADDR,
    QSPI_PHASE_MBIT,
    QSPI_PHASE_DUMMY,
    QSPI_PHASE_DATA,
    QSPI_PHASE_MAX,
} QSPI_PHASE_TYPE_e;

typedef enum {
    QSPI_OP_MODE_INDIRECT,      /**< Indirect command mode (FIFO/DMA based) */
    QSPI_OP_MODE_DIRECT,        /**< Execute-In-Place (memory-mapped, read-only) */
    QSPI_OP_MODE_MAX
} QSPI_OP_MODE_e;

/**
 * @brief QSPI Command Output Mode
 */
typedef enum
{
    QSPI_BUS_MODE_NONE,
    QSPI_BUS_MODE_SINGLE,           /*< Single Mode */
    QSPI_BUS_MODE_DUAL,             /*< Dual Mode */
    QSPI_BUS_MODE_RESERVED,         /*< Reserved */
    QSPI_BUS_MODE_QUAD,             /*< Quad Mode */
    QSPI_BUS_MODE_MAX,
} QSPI_BUS_MODE_e;

/**
 * @brief QSPI Output Data Rate Mode
 */
typedef enum
{
    QSPI_SAMPLE_RATE_SINGLE,            /*< Normal(SDR/STR) Mode */
    QSPI_SAMPLE_RATE_DOUBLE,            /*< DDR/DTR Mode */
    QSPI_SAMPLE_RATE_MAX,
} QSPI_SAMPLE_RATE_e;

/**
 * @brief QSPI Clock Cycle Duration Bits
 */
typedef enum
{
    QSPI_PHASE_WIDTH_NONE,         /*< No bits Duration */
    QSPI_PHASE_WIDTH_8BIT,          /*< 8 bits Duration */
    QSPI_PHASE_WIDTH_16BIT,         /*< 16 bits Duration */
    QSPI_PHASE_WIDTH_24BIT,         /*< 24 bits Duration */
    QSPI_PHASE_WIDTH_32BIT,         /*< 32 bits Duration */
    QSPI_PHASE_WIDTH_MAX,
} QSPI_PHASE_WIDTH_e;

/**
 * @brief QSPI Byte Order
 */
typedef enum
{
    QSPI_FLIP_DISABLE,      /**< No byte swap */
    QSPI_FLIP_ENABLE,       /**< Byte swap enabled (DDR x4 only: nibble swap in 8-bit)*/
    QSPI_FLIP_MAX,
} QSPI_FLIP_MODE_e;

/**
 * @brief QSPI Data Direction Mode
 */
typedef enum
{
    QSPI_DIR_OUTPUT,        /**< QSPI controller outputs data (Write) */
    QSPI_DIR_INPUT,         /**< QSPI controller inputs data (Read) */
    QSPI_DIR_MAX,
} QSPI_DIR_MODE_e;

/**
 * @brief QSPI Operation
 */
typedef enum
{
    QSPI_OPS_POLL,        /**< Operation Polling */
    QSPI_OPS_INTR,        /**< Operation Interrupt */
    QSPI_OPS_INTR_DMA,    /**< Operation Interrupt with DMA */
    QSPI_OPS_NMI,         /**< Operation NMI */
    QSPI_OPS_NMI_DMA,     /**< Operation NMI with DMA */
    QSPI_OPS_MAX
} QSPI_OPS_e;

typedef enum
{
    QSPI_DMA_DESC_TYPE_NONE,
    QSPI_DMA_DESC_TYPE_LINK,
    QSPI_DMA_DESC_TYPE_DATA,
} QSPI_DMA_DESC_TYPE_e;

typedef enum
{
    QSPI_BURST_UNDERMINED,     /**< Undermined Burst Length */
    QPSI_BURST_4BYTES,          /**< 4 Bytes Burst */
    QSPI_BURST_8BYTES,          /**< 8 Bytes Burst */
    QSPI_BURST_16BYTES,         /**< 16 Bytes Burst */
} QSPI_BURST_LEN_e;

/**
 * @brief QSPI Configuration Structure
 */
typedef struct
{
    QSPI_CLK_MODE_e     eClkMode;           /**< CPOL, CPHA */
    QSPI_TRANS_EDGE_e   eTransEdge;         /**< Clock edge */
    bool                bCSLine;            /**< Chip Select Line Control */
    uint8_t             un8PRDivider;       /**< Period of the QSPI output clock Divider */
    uint8_t             un8SamplePoint;     /**< input data Sampling Point */
    uint8_t             un8MinCsLow;        /**< minimum chip select low time */
    uint8_t             un8MinCsHigh;       /**< minimum chip select high time */
    uint8_t             un8HoldTime;        /**< data hold time */
} QSPI_CFG_t;

typedef struct
{
    QSPI_PHASE_TYPE_e   ePhaseType;     /**< Select Phase Type */
    QSPI_OP_MODE_e      eOpMode;        /**< Operation Mode (Indirect/Direct) */
    QSPI_BUS_MODE_e     eBusMode;       /**< Parrallel bits Mode */
    QSPI_SAMPLE_RATE_e  eSampleRate;    /**< Clock Edge Data Rate Mode (DDR/DTR or Normal/STR) */

    bool                bSkip;              /**< Skip Enable/Disable */

    union
    {
        struct
        {
            QSPI_PHASE_WIDTH_e eWidth; /**< Phase bit-width (8/16/24/32 bits) */
            uint16_t un16Cmd;          /**< Command Value */
        } tCmd;

        struct
        {
            QSPI_PHASE_WIDTH_e eWidth; /**< Phase bit-width (8/16/24/32 bits) */
            uint8_t un8Mask;           /**< Address Mask */
            uint32_t un32Addr;         /**< Address Value */
        } tAddr;

        struct
        {
            QSPI_PHASE_WIDTH_e eWidth; /**< Phase bit-width (8/16/24/32 bits) */
            uint32_t un32ModeBits;     /**< Mode Bits Value */
        } tMBits;

        struct
        {
            uint8_t un8Cycles;      /**< Dummy Cycles */
            bool bNoWrLatency;      /**< No Write Latency Enable */
        } tDmy;

        struct
        {
            QSPI_FLIP_MODE_e eFlipMode; /**< Data Byte Order */
            QSPI_DIR_MODE_e eDirMode;   /**< Data Direction Mode */
            uint32_t un32Size;          /**< Data Size */
        } tData;
    } tPhaCfg;
} QSPI_PHASE_CFG_t;


typedef struct
{
    union
    {
        struct
        {
            bool bValid                     : 1;  /**< [0] : Valid bit for this Descriptor */
            bool bEnd                       : 1;  /**< [1] : End of Descriptor List */
            bool bIrqEn                     : 1;  /**< [2] : Interrupt Enable for this Descriptor */
            uint8_t un8Rsv0                 : 1;  /**< [3] : Reserved */
            QSPI_DMA_DESC_TYPE_e eDescType  : 2;  /**< [5:4] : Descriptor Type (Link/Data) */
            uint16_t un16Rsv1               : 10; /**< [15:6] : Reserved */
            uint16_t un16Size               : 16; /**< [31:16] : Data Size for DMA */
        } b;
        uint32_t un32All;
    } tCtrl;
    uint32_t un32Addr;
} QSPI_DMA_DESC_t;

typedef struct
{
    uint32_t un32DescAddr;              /**< Descriptor Address for DMA */
    QSPI_BURST_LEN_e eFixedBurstLen;    /**< Fixed Burst Length for Data Transfer */
} QSPI_DMA_CFG_t;

/**
 *******************************************************************************
 * @brief       QSPI Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::QSPI_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnQSPI_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize QSPI.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QSPI_Init(QSPI_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize QSPI.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QSPI_Uninit(QSPI_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration QSPI.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : QSPI Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QSPI_SetConfig(QSPI_ID_e eId, QSPI_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set Phase Configuration QSPI.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : QSPI Phase Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QSPI_SetPhaseConfig(QSPI_ID_e eId, QSPI_PHASE_CFG_t *ptPhaCfg);

/**
 *******************************************************************************
 * @brief       Set DMA Configuration QSPI.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptDmaCfg : QSPI DMA Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QSPI_SetDmaConfig(QSPI_ID_e eId, QSPI_DMA_CFG_t *ptDmaCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ QSPI.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QSPI_SetIRQ(QSPI_ID_e eId, QSPI_OPS_e eOps, pfnQSPI_IRQ_Handler_t pfnHandler,
                          void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Send QSPI Command.
 * @param[in]   eId : Instance Id.
 * @param[in]   un16Cmd : QSPI Command.
 * @param[in]   un32Timeout : Timeout.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QSPI_Command(QSPI_ID_e eId, uint16_t un16Cmd, uint32_t un32Timeout);

/**
 *******************************************************************************
 * @brief       Transmit Data QSPI.
 * @param[in]   eId : Instance Id.
 * @param[in]   *pun8Out : Transmit Data.
 * @param[in]   un32Len : Data Length.
 * @param[in]   bEnForcePoll : En-force polling Operation (Ignored IO Operation by SetIRQ).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QSPI_Transmit(QSPI_ID_e eId, uint8_t *pun8Out, uint32_t un32Len, bool bEnForcePoll);

/**
 *******************************************************************************
 * @brief       Receive Data QSPI.
 * @param[in]   eId : Instance Id.
 * @param[in]   *pun8In : Receive Data.
 * @param[in]   un32Len : Data Length.
 * @param[in]   bEnForcePoll : En-force polling Operation (Ignored IO Operation by SetIRQ).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_QSPI_Receive(QSPI_ID_e eId, uint8_t *pun8In, uint32_t un32Len, bool bEnForcePoll);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_QSPI_H_ */

/** @} */
/** @} */
