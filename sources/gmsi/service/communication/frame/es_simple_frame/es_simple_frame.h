/****************************************************************************
*  Copyright 2017 Gorgon Meducer (Email:embedded_zhuoran@hotmail.com)       *
*                                                                           *
*  Licensed under the Apache License, Version 2.0 (the "License");          *
*  you may not use this file except in compliance with the License.         *
*  You may obtain a copy of the License at                                  *
*                                                                           *
*     http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                           *
*  Unless required by applicable law or agreed to in writing, software      *
*  distributed under the License is distributed on an "AS IS" BASIS,        *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
*  See the License for the specific language governing permissions and      *
*  limitations under the License.                                           *
*                                                                           *
****************************************************************************/



#ifndef __USE_ES_SIMPLE_FRAME_H__
#define __USE_ES_SIMPLE_FRAME_H__

/*============================ INCLUDES ======================================*/
#include ".\app_cfg.h"
#include "..\iframe.h"

#if USE_SERVICE_ES_SIMPLE_FRAME == ENABLED
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/

//! \brief macro for es-simple frame initialization
#define ES_SIMPLE_FRAME_CFG(__FRAME__, ...)                                     \
            do {                                                                \
                es_simple_frame_cfg_t tCFG = {__VA_ARGS__};                     \
                ES_SIMPLE_FRAME.Init((__FRAME__),&tCFG);                        \
            } while(false)


#define es_simple_frame_cfg(__FRAME__, ...)                                     \
            ES_SIMPLE_FRAME_CFG(__FRAME__, __VA_ARGS__)
            
/*============================ TYPES =========================================*/
def_structure(__es_simple_frame_fsm_internal)
    inherit(mem_block_t)
    
    uint16_t hwLength;
    uint16_t hwCounter;
    uint16_t hwCheckSUM;
end_def_structure(__es_simple_frame_fsm_internal)

extern_simple_fsm(es_simple_frame_decoder,
    def_params(
        i_byte_pipe_t *ptPipe;          //!< pipe
        frame_parser_t *fnParser;       //!< parser
        bool bUnsupportFrame;
        inherit(__es_simple_frame_fsm_internal)
    ))
    
extern_simple_fsm(es_simple_frame_encoder,
    def_params(
        i_byte_pipe_t *ptPipe;          //!< pipe
        inherit(__es_simple_frame_fsm_internal)
    ))

declare_class(es_simple_frame_t)

extern_simple_fsm(es_simple_frame_decoder_wrapper,
    def_params(
        es_simple_frame_t *ptFrame;
    ))
    

extern_simple_fsm(es_simple_frame_encoder_wrapper,
    def_params(
        es_simple_frame_t *ptFrame;
    ))
    
//! \name class: e-snail simple frame
//! @{
extern_class(es_simple_frame_t)
    locker_t tMutex;
    inherit(fsm(es_simple_frame_decoder))
    inherit(fsm(es_simple_frame_decoder_wrapper))
    inherit(fsm(es_simple_frame_encoder))
    inherit(fsm(es_simple_frame_encoder_wrapper))
end_extern_class(es_simple_frame_t)
//! @}

//! \name es-simple frame configuration structure
//! @{
typedef struct {
    i_byte_pipe_t   *ptPipe; 
    frame_parser_t  *fnParser;
    inherit(mem_block_t)
}es_simple_frame_cfg_t;
//! @}

/*============================ PROTOTYPES ====================================*/

extern_fsm_initialiser(es_simple_frame_decoder,
    args(
        i_byte_pipe_t *ptPipe, 
        frame_parser_t *fnParser,
        mem_block_t tMemory
    ))

extern_fsm_initialiser(es_simple_frame_encoder,
    args(
        i_byte_pipe_t *ptPipe
    ))

extern_fsm_implementation(es_simple_frame_encoder,
        args(
            uint8_t *pchData, uint_fast16_t hwSize
        ));
       
extern_fsm_implementation(es_simple_frame_decoder);

/*============================ TYPES Part Two ================================*/
//! \name frame interface
//! @{
def_interface(i_es_simple_frame_t)
    bool (*Init)(es_simple_frame_t *ptFrame, es_simple_frame_cfg_t *ptCFG);
    fsm_rt_t (*Task)(es_simple_frame_t *ptFrame);
    fsm_rt_t (*Decoder)(es_simple_frame_t *ptFrame);
    fsm_rt_t (*Encoder)(es_simple_frame_t *ptFrame, uint8_t *pchData, uint_fast16_t hwSize);
end_def_interface(i_es_simple_frame_t)
//! @}


/*============================ GLOBAL VARIABLES ==============================*/
extern const i_es_simple_frame_t ES_SIMPLE_FRAME;

/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/


#endif

#endif