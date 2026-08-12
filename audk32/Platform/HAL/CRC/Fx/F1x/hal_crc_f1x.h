/**
 *******************************************************************************
 * @file        hal_crc_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed CRC
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_CRC_F1X_H_
#define _HAL_CRC_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define CRC_CH_NUM                                    CONFIG_CRC_MAX_COUNT

#if (CONFIG_CRC_VER_EXT == 0)

#if (CONFIG_CRC_VER_MINOR == 0)
#include "hal_crc_f_01_00_00.h"
#elif (CONFIG_CRC_VER_MINOR == 1)
#include "hal_crc_f_01_00_01.h"
#else
#error "define CONFIG_CRC_VER_MINOR of F-type CRC at config_xxx.h"
#endif

#else
#error "define CONFIG_CRC_VER_EXT of F-type CRC at config_xxx.h"
#endif

static __inline CRC_Type *CRC_GetReg(P_CRC_ID_e eId)
{
    return (CRC_Type *)(CRC_REG_BASE + (CRC_REG_OFFSET * (uint32_t)eId));
}

static __inline IRQn_Type CRC_GetIRQNum(P_CRC_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(CRC_0_IRQ)
        case P_CRC_ID_0:
            eIrq = CRC_0_IRQ;
            break;
#endif
#if defined(CRC_1_IRQ)
        case P_CRC_ID_1:
            eIrq = CRC_1_IRQ;
            break;
#endif
#if defined(CRC_2_IRQ)
        case P_CRC_ID_2:
            eIrq = CRC_2_IRQ;
            break;
#endif
#if defined(CRC_3_IRQ)
        case P_CRC_ID_3:
            eIrq = CRC_3_IRQ;
            break;
#endif
#if defined(CRC_4_IRQ)
        case P_CRC_ID_4:
            eIrq = CRC_4_IRQ;
            break;
#endif
#if defined(CRC_5_IRQ)
        case P_CRC_ID_5:
            eIrq = CRC_5_IRQ;
            break;
#endif
#if defined(CRC_6_IRQ)
        case P_CRC_ID_6:
            eIrq = CRC_6_IRQ;
            break;
#endif
#if defined(CRC_7_IRQ)
        case P_CRC_ID_7:
            eIrq = CRC_7_IRQ;
            break;
#endif
#if defined(CRC_8_IRQ)
        case P_CRC_ID_8:
            eIrq = CRC_8_IRQ;
            break;
#endif
#if defined(CRC_9_IRQ)
        case P_CRC_ID_9:
            eIrq = CRC_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e CRC_SetScuEnable(P_CRC_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_CRC_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_CRC_PER(ptScu, un32Enable);
    SET_SCU_CRC_PCER(ptScu, un32Enable);

    return HAL_ERR_OK;
}

static __inline void CRC_SetData(CRC_Type *ptPeri, uint8_t *pun8Data, uint32_t un32Len)
{
    uint32_t i = 0, j = 0;
    uint32_t un32Data = 0;
    uint32_t un32Quotient = 0;
    uint32_t un32Remaider = 0;
    uint32_t un32DataSize = 0;

#if defined (CRC_FEATURE_INPUT_CONF_MODE)
    CRC_INP_DATA_e eDataSize = (CRC_INP_DATA_e)GET_CRC_CR_INDATA_SIZE(ptPeri);
    switch(eDataSize)
    {
        case CRC_INP_DATA_8:
            un32DataSize = 1;
            break;
        case CRC_INP_DATA_16:
            un32DataSize = 2;
            break;
        case CRC_INP_DATA_32:
        default:
            un32DataSize = 4;
            break;
    }
#else
    un32DataSize = 4;
#endif
    un32Quotient = un32Len / un32DataSize;
    un32Remaider = un32Len % un32DataSize;

    if(un32Remaider != 0)
    {
#if defined (CRC_FEATURE_INPUT_CONF_MODE)
        if (GET_CRC_CR_INDATA_COMPLE(ptPeri))
        {
            un32Data = (0xFFFFFFFF << (8 * un32Remaider));
        }
#endif
        for(i = un32Remaider; i > 0; i--)
        {
            un32Data |= (*pun8Data++ << (i-1)*8);
        }

        SET_CRC_DR_IN(ptPeri,un32Data);
    }

    for(i = 0; i < un32Quotient; i++)
    {
        un32Data = 0;

        for(j = un32DataSize; j > 0; j--)
        {
            un32Data |= (*pun8Data++ << (j-1)*8);
        }

        SET_CRC_DR_IN(ptPeri,un32Data);
    }
}

static __inline HAL_ERR_e CRC_GetAlignData(uint8_t *pun8Data, uint32_t un32Len, uint32_t *pun32AlignData, uint32_t *pun32AlignLen)
{
    uint32_t i = 0, j = 0;
    uint32_t un32Quotient = 0;
    uint32_t un32Remainder = 0;
    uint32_t un32MemSize = 0;
    uint32_t *pun32Mem = NULL;

    un32Quotient = un32Len / 4;
    un32Remainder = un32Len % 4;

    if(un32Remainder != 0)
    {
        un32MemSize = un32Quotient + 1;
    }

    pun32Mem = (uint32_t *)malloc(un32MemSize*sizeof(uint32_t));

    memset(pun32Mem, 0x00, un32MemSize*sizeof(uint32_t));

    *pun32AlignData = (uint32_t)pun32Mem;
    *pun32AlignLen = un32MemSize;

    if(un32Remainder != 0)
    {
        for(i = un32Remainder; i > 0; i--)
        {
           *pun32Mem |= (*pun8Data++ << (i-1)*8);
        }
        pun32Mem++;
    }

    if(un32Quotient != 0)
    {
        for(i = 0; i < un32Quotient; i++)
        {
            for(j = CRC_BYTE_ALIGN; j > 0; j--)
            {
                *pun32Mem |= (*pun8Data++ << (j-1)*8);
            }
            pun32Mem++;
        }
    }

    return HAL_ERR_OK;
}

static __inline HAL_ERR_e CRC_GetSupportPoly(P_CRC_POLY_e eMode)
{
    switch(eMode)
    {
#if (CONFIG_CRC_VER_EXT == 0 && CONFIG_CRC_VER_MINOR == 1) 
        case P_CRC_POLY_8:
        case P_CRC_POLY_16:
        case P_CRC_POLY_16_CCITT:
        case P_CRC_POLY_32:
             return HAL_ERR_OK;
#else
        case P_CRC_POLY_16_CCITT:
        case P_CRC_POLY_16:
             return HAL_ERR_OK;
        default:
             break;
#endif
    }
    return HAL_ERR_NOT_SUPPORTED;
}

static __inline P_CRC_DMA_BUS_SIZE_e CRC_GetDMABusSize(void)
{
    return P_CRC_DMA_BUS_SIZE_WORD;
}

#endif /* _HAL_CRC_F1X_H_ */
