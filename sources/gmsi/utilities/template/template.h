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

#ifndef _USE_TEMPLATE_H_
#define _USE_TEMPLATE_H_

/*============================ INCLUDES ======================================*/
#include ".\t_queue.h"
#include ".\t_pool.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/

#define __LIST_STACK_PUSH(__P_TOP, __P_NODE)                                    \
        do {                                                                    \
            ((__single_list_node_t *)(__P_NODE))->ptNext =                      \
                (__single_list_node_t *)(__P_TOP);                              \
            (*(__single_list_node_t **)&(__P_TOP)) =                            \
                (__single_list_node_t *)(__P_NODE);                             \
        } while(0)                                
#define LIST_STACK_PUSH(__P_TOP, __P_NODE)                                      \
            __LIST_STACK_PUSH((__P_TOP), (__P_NODE))
#define LIST_INSERT_AFTER(__P_TARGET, __P_NODE)                                 \
            __LIST_STACK_PUSH((__P_TARGET), (__P_NODE))
        
#define __LIST_STACK_POP(__P_TOP, __P_NODE)                                     \
        do {                                                                    \
            (*(__single_list_node_t **)&(__P_NODE)) =                           \
                (__single_list_node_t *)(__P_TOP);                              \
            (*(__single_list_node_t **)&(__P_TOP)) =                            \
                ((__single_list_node_t *)(__P_NODE))->ptNext;                   \
            ((__single_list_node_t *)(__P_NODE))->ptNext = NULL;                \
        } while(0)                                 
#define LIST_STACK_POP(__P_TOP, __P_NODE)    __LIST_STACK_POP((__P_TOP), (__P_NODE))
#define LIST_REMOVE_AFTER(__P_TARGET, __P_NODE)                                 \
            LIST_STACK_POP((__P_TARGET), (__P_NODE))
        
        
#define __LIST_QUEUE_ENQUEUE(__HEAD, __TAIL, __ITEM)                            \
    do {                                                                        \
        if (NULL == (__TAIL)) {                                                 \
            (*((__single_list_node_t **)&(__TAIL))) =                           \
                (__single_list_node_t *)(__ITEM);                               \
            ((__single_list_node_t *)(__ITEM))->ptNext = NULL;                  \
            (*((__single_list_node_t **)&(__HEAD))) =                           \
                (__single_list_node_t *)(__ITEM);                               \
        } else {                                                                \
            ((__single_list_node_t *)(__TAIL))->ptNext =                        \
                (__single_list_node_t *)(__ITEM);                               \
            ((__single_list_node_t *)(__ITEM))->ptNext = NULL;                  \
            (*(__single_list_node_t **)&(__TAIL)) =                             \
                (__single_list_node_t *)(__ITEM);                               \
        }                                                                       \
    } while(0)
#define LIST_QUEUE_ENQUEUE(__HEAD, __TAIL, __ITEM)  \
            __LIST_QUEUE_ENQUEUE((__HEAD), (__TAIL), (__ITEM))
    
#define __LIST_QUEUE_DEQUEUE(__HEAD, __TAIL, __ITEM)                            \
    do {                                                                        \
        (*(__single_list_node_t **)&(__ITEM)) =                                 \
            (__single_list_node_t *)(__HEAD);                                   \
        if (NULL == (__HEAD)) {                                                 \
            break;                                                              \
        }                                                                       \
        (*(__single_list_node_t **)&(__HEAD)) =                                 \
            ((__single_list_node_t *)(__HEAD))->ptNext;                           \
        if (NULL == (__HEAD)) {                                                 \
            (__TAIL) = NULL;                                                    \
        }                                                                       \
    } while(0)
#define LIST_QUEUE_DEQUEUE(__HEAD, __TAIL, __ITEM)  \
            __LIST_QUEUE_DEQUEUE((__HEAD), (__TAIL), (__ITEM))
    
/*============================ TYPES =========================================*/


DEF_STRUCTURE( __single_list_node_t )
    __single_list_node_t     *ptNext;
END_DEF_STRUCTURE( __single_list_note_t )

DEF_STRUCTURE( __dual_list_node_t )
    __dual_list_node_t       *ptNext;
    __dual_list_node_t       *ptPrevious;
END_DEF_STRUCTURE( __dual_list_note_t )

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/





#endif