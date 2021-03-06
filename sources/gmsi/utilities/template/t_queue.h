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

#ifndef _USE_TEMPLATE_QUEUE_H_
#define _USE_TEMPLATE_QUEUE_H_

/*============================ INCLUDES ======================================*/
/*============================ MACROS ========================================*/

#define END_DEF_QUEUE(__NAME)
#define END_DEF_QUEUE_U8(__NAME)
#define END_DEF_QUEUE_U16(__NAME)
#define END_DEF_QUEUE_U32(__NAME)

#define END_DEF_SAFE_QUEUE(__NAME)
#define END_DEF_SAFE_QUEUE_U8(__NAME)
#define END_DEF_SAFE_QUEUE_U16(__NAME)
#define END_DEF_SAFE_QUEUE_U32(__NAME)

#define END_EXTERN_QUEUE(__NAME)
#define END_EXTERN_QUEUE_U8(__NAME)
#define END_EXTERN_QUEUE_U16(__NAME)
#define END_EXTERN_QUEUE_U32(__NAME)

#define END_EXTERN_SAFE_QUEUE(__NAME)
#define END_EXTERN_SAFE_QUEUE_U8(__NAME)
#define END_EXTERN_SAFE_QUEUE_U16(__NAME)
#define END_EXTERN_SAFE_QUEUE_U32(__NAME)

/*============================ MACROFIED FUNCTIONS ===========================*/
#ifndef NONE_ATOM_ACCESS
#   define NONE_ATOM_ACCESS(...)        {__VA_ARGS__;}
#endif

#define QUEUE_MUTEX(__NAME, __QUEUE)                                        \
            __NAME##_queue_mutex(__QUEUE) 

#define QUEUE_INIT(__NAME, __QUEUE, __BUFFER, __SIZE)                       \
            __NAME##_queue_init((__QUEUE), (__BUFFER), (__SIZE), false)

#define QUEUE_SERIALIZE(__NAME, __QUEUE, __BUFFER, __SIZE)                  \
            __NAME##_queue_init((__QUEUE), (__BUFFER), (__SIZE), true)
                
#define QUEUE_INIT_EX(__NAME, __QUEUE, __BUFFER, __SIZE, __SERIALISED)      \
            __NAME##_queue_init((__QUEUE), (__BUFFER), (__SIZE), (__SERIALISED))

#define QUEUE_DESERIALIZE(__NAME, __QUEUE)                                  \
            __NAME##_get_queue_buffer(__QUEUE) 

#define DEQUEUE(__NAME, __QUEUE, __ADDR)                                    \
            __NAME##_dequeue((__QUEUE),(__ADDR))

#define DEQUEUE_REF(__NAME, __QUEUE)                                        \
            __NAME##_dequeue_ref((__QUEUE))

#define ENQUEUE(__NAME, __QUEUE, __VALUE)                                   \
            __NAME##_enqueue((__QUEUE), (__VALUE))

#define PEEK_QUEUE(__NAME, __QUEUE, __ADDR)                                 \
            __NAME##_queue_peek((__QUEUE),(__ADDR))

#define GET_QUEUE_COUNT(__NAME, __QUEUE)                                    \
            __NAME##_get_queue_item_count((__QUEUE))

#define GET_QUEUE_AVAILABLE_COUNT(__NAME, __QUEUE)                          \
            __NAME##_get_queue_item_available_count((__QUEUE))

#define RESET_PEEK(__NAME, __QUEUE)                                         \
            __NAME##_reset_peek((__QUEUE))

#define GET_ALL_PEEKED(__NAME, __QUEUE)                                     \
            __NAME##_get_all_peeked((__QUEUE))

#define QUEUE(__NAME)   __NAME##_queue_t

#define EXTERN_QUEUE(__NAME, __TYPE, __PTR_TYPE, __MUTEX_TYPE)              \
DECLARE_CLASS(__NAME##_queue_t)                                             \
EXTERN_CLASS(__NAME##_queue_t)                                              \
    __TYPE          *ptBuffer;                                              \
    __PTR_TYPE      tSize;                                                  \
    __PTR_TYPE      tHead;                                                  \
    __PTR_TYPE      tTail;                                                  \
    __PTR_TYPE      tCounter;                                               \
    __PTR_TYPE      tPeek;                                                  \
    __PTR_TYPE      tPeekCounter;                                           \
    __MUTEX_TYPE    tMutex;                                                 \
END_EXTERN_CLASS(__NAME##_queue_t)                                          \
                                                                            \
extern __MUTEX_TYPE *__NAME##_queue_mutex(__NAME##_queue_t *ptQueue);       \
extern bool __NAME##_queue_init(                                            \
    __NAME##_queue_t *ptQueue, __TYPE *ptBuffer, __PTR_TYPE tSize);         \
extern bool __NAME##_enqueue(__NAME##_queue_t *ptQueue, __TYPE tObj);       \
extern bool __NAME##_queue_peek(__NAME##_queue_t *ptQueue, __TYPE *ptObj);  \
extern bool __NAME##_dequeue(__NAME##_queue_t *ptQueue, __TYPE *ptObj);     \
extern __TYPE * __NAME##_dequeue_ref(__NAME##_queue_t *ptQueue);            \
extern void __NAME##_get_all_peeked(__NAME##_queue_t *ptQueue);             \
extern void __NAME##_reset_peek(__NAME##_queue_t *ptQueue);                 \
extern __PTR_TYPE __NAME##_get_queue_item_count(__NAME##_queue_t *ptQueue); \
extern __PTR_TYPE __NAME##_get_queue_item_available_count(                  \
    __NAME##_queue_t *ptQueue);                                             \
extern __TYPE * __NAME##_get_queue_buffer(__NAME##_queue_t *ptQueue);

#define DEF_QUEUE_EX(                                                       \
    __NAME, __TYPE, __PTR_TYPE, __MUTEX_TYPE, __ATOM_ACCESS)                \
DECLARE_CLASS(__NAME##_queue_t)                                             \
DEF_CLASS(__NAME##_queue_t)                                                 \
    __TYPE          *ptBuffer;                                              \
    __PTR_TYPE      tSize;                                                  \
    __PTR_TYPE      tHead;                                                  \
    __PTR_TYPE      tTail;                                                  \
    __PTR_TYPE      tCounter;                                               \
    __PTR_TYPE      tPeek;                                                  \
    __PTR_TYPE      tPeekCounter;                                           \
    __MUTEX_TYPE    tMutex;                                                 \
END_DEF_CLASS(__NAME##_queue_t)                                             \
                                                                            \
__MUTEX_TYPE *__NAME##_queue_mutex(__NAME##_queue_t *ptQueue)               \
{                                                                           \
    CLASS(__NAME##_queue_t) *ptQ = (CLASS(__NAME##_queue_t) *)ptQueue;      \
    if ( NULL == ptQueue)  {                                                \
        return NULL;                                                        \
    }                                                                       \
    return &(ptQ->tMutex);                                                  \
}                                                                           \
                                                                            \
__TYPE * __NAME##_get_queue_buffer(__NAME##_queue_t *ptQueue)               \
{                                                                           \
    CLASS(__NAME##_queue_t) *ptQ = (CLASS(__NAME##_queue_t) *)ptQueue;      \
    if ( NULL == ptQueue)  {                                                \
        return NULL;                                                        \
    }                                                                       \
    return ptQ->ptBuffer;                                                   \
}                                                                           \
bool __NAME##_queue_init(                                                   \
    __NAME##_queue_t *ptQueue, __TYPE *ptBuffer, __PTR_TYPE tSize, bool bFull)  \
{                                                                           \
    CLASS(__NAME##_queue_t) *ptQ = (CLASS(__NAME##_queue_t) *)ptQueue;      \
    if (NULL == ptQueue || NULL == ptBuffer || 0 == tSize) {                \
        return false;                                                       \
    }                                                                       \
                                                                            \
    ptQ->ptBuffer = ptBuffer;                                               \
    ptQ->tSize = tSize;                                                     \
    ptQ->tHead = 0;                                                         \
    ptQ->tPeek = 0;                                                         \
    ptQ->tTail = 0;                                                         \
    if (bFull) {                                                            \
        ptQ->tCounter = tSize;                                              \
        ptQ->tPeekCounter = tSize;                                          \
    } else {                                                                \
        ptQ->tCounter = 0;                                                  \
        ptQ->tPeekCounter = 0;                                              \
    }                                                                       \
                                                                            \
    return true;                                                            \
}                                                                           \
                                                                            \
bool __NAME##_enqueue(__NAME##_queue_t *ptQueue, __TYPE tObj)               \
{                                                                           \
    bool bResult = false;                                                   \
    CLASS(__NAME##_queue_t) *ptQ = (CLASS(__NAME##_queue_t) *)ptQueue;      \
    if (NULL == ptQ) {                                                      \
        return false;                                                       \
    }                                                                       \
                                                                            \
    __ATOM_ACCESS(                                                          \
        do {                                                                \
            if ((ptQ->tHead == ptQ->tTail) && (0 != ptQ->tCounter)) {       \
                break;                                                      \
            }                                                               \
                                                                            \
            ptQ->ptBuffer[ptQ->tTail++] = tObj;                             \
            if (ptQ->tTail >= ptQ->tSize) {                                 \
                ptQ->tTail = 0;                                             \
            }                                                               \
            ptQ->tCounter++;                                                \
            ptQ->tPeekCounter++;                                            \
            bResult = true;                                                 \
        } while (false);                                                    \
    )                                                                       \
                                                                            \
    return bResult;                                                         \
}                                                                           \
                                                                            \
bool __NAME##_queue_peek(__NAME##_queue_t *ptQueue, __TYPE *ptObj)          \
{                                                                           \
    bool bResult = false;                                                   \
    CLASS(__NAME##_queue_t) *ptQ = (CLASS(__NAME##_queue_t) *)ptQueue;      \
    if (NULL == ptQ) {                                                      \
        return false;                                                       \
    }                                                                       \
                                                                            \
    __ATOM_ACCESS(                                                          \
        do {                                                                \
            __TYPE tObj;                                                    \
            if ((ptQ->tPeek == ptQ->tTail) && (!ptQ->tPeekCounter)) {       \
                break;                                                      \
            }                                                               \
            tObj = ptQ->ptBuffer[ptQ->tPeek++];                             \
            ptQ->tPeekCounter--;                                            \
            if (ptQ->tPeek >= ptQ->tSize) {                                 \
                ptQ->tPeek = 0;                                             \
            }                                                               \
            if (NULL != ptObj) {                                            \
                *ptObj = tObj;                                              \
            }                                                               \
            bResult = true;                                                 \
        } while (false);                                                    \
    )                                                                       \
                                                                            \
    return bResult;                                                         \
}                                                                           \
bool __NAME##_dequeue(__NAME##_queue_t *ptQueue, __TYPE *ptObj)             \
{                                                                           \
    bool bResult = false;                                                   \
    CLASS(__NAME##_queue_t) *ptQ = (CLASS(__NAME##_queue_t) *)ptQueue;      \
    if (NULL == ptQ) {                                                      \
        return false;                                                       \
    }                                                                       \
                                                                            \
    __ATOM_ACCESS(                                                          \
        do {                                                                \
            if ((ptQ->tHead == ptQ->tTail) && (!ptQ->tCounter)) {           \
                break;                                                      \
            }                                                               \
            if (NULL != ptObj) {                                            \
                *ptObj = ptQ->ptBuffer[ptQ->tHead];                         \
            }                                                               \
            ptQ->tHead++;                                                   \
            if (ptQ->tHead >= ptQ->tSize) {                                 \
                ptQ->tHead = 0;                                             \
            }                                                               \
            ptQ->tCounter--;                                                \
            ptQ->tPeek = ptQ->tHead;                                        \
            ptQ->tPeekCounter = ptQ->tCounter;                              \
            bResult = true;                                                 \
        } while (false);                                                    \
    )                                                                       \
                                                                            \
    return bResult;                                                         \
}                                                                           \
__TYPE * __NAME##_dequeue_ref(__NAME##_queue_t *ptQueue)                    \
{                                                                           \
    __TYPE *ptObj = NULL;                                                   \
    CLASS(__NAME##_queue_t) *ptQ = (CLASS(__NAME##_queue_t) *)ptQueue;      \
    if (NULL == ptQ) {                                                      \
        return NULL;                                                        \
    }                                                                       \
                                                                            \
    __ATOM_ACCESS(                                                          \
        do {                                                                \
            if ((ptQ->tHead == ptQ->tTail) && (!ptQ->tCounter)) {           \
                break;                                                      \
            }                                                               \
            ptObj = &(ptQ->ptBuffer[ptQ->tHead]);                           \
            ptQ->tHead++;                                                   \
            if (ptQ->tHead >= ptQ->tSize) {                                 \
                ptQ->tHead = 0;                                             \
            }                                                               \
            ptQ->tCounter--;                                                \
            ptQ->tPeek = ptQ->tHead;                                        \
            ptQ->tPeekCounter = ptQ->tCounter;                              \
        } while (false);                                                    \
    )                                                                       \
                                                                            \
    return ptObj;                                                           \
}                                                                           \
__PTR_TYPE __NAME##_get_queue_item_count(__NAME##_queue_t *ptQueue)         \
{                                                                           \
    CLASS(__NAME##_queue_t) *ptQ = (CLASS(__NAME##_queue_t) *)ptQueue;      \
    __PTR_TYPE tCount;                                                      \
    if (NULL == ptQ) {                                                      \
        return 0;                                                           \
    }                                                                       \
                                                                            \
    __ATOM_ACCESS(                                                          \
        tCount = ptQ->tCounter;                                             \
    )                                                                       \
    return tCount;                                                          \
}                                                                           \
__PTR_TYPE __NAME##_get_queue_item_available_count(__NAME##_queue_t *ptQueue)   \
{                                                                           \
    CLASS(__NAME##_queue_t) *ptQ = (CLASS(__NAME##_queue_t) *)ptQueue;      \
    __PTR_TYPE tSize;                                                       \
    if (NULL == ptQ) {                                                      \
        return 0;                                                           \
    }                                                                       \
                                                                            \
    __ATOM_ACCESS(                                                          \
        tSize = ptQ->tSize - ptQ->tCounter;                                 \
    )                                                                       \
    return tSize;                                                           \
}                                                                           \
void __NAME##_get_all_peeked(__NAME##_queue_t *ptQueue)                     \
{                                                                           \
    CLASS(__NAME##_queue_t) *ptQ = (CLASS(__NAME##_queue_t) *)ptQueue;      \
    if (NULL == ptQ) {                                                      \
        return ;                                                            \
    }                                                                       \
                                                                            \
    __ATOM_ACCESS(                                                          \
        ptQ->tHead = ptQ->tPeek;                                            \
        ptQ->tCounter = ptQ->tPeekCounter;                                  \
    )                                                                       \
}                                                                           \
void __NAME##_reset_peek(__NAME##_queue_t *ptQueue)                         \
{                                                                           \
    CLASS(__NAME##_queue_t) *ptQ = (CLASS(__NAME##_queue_t) *)ptQueue;      \
    if (NULL == ptQ) {                                                      \
        return ;                                                            \
    }                                                                       \
                                                                            \
    __ATOM_ACCESS(                                                          \
        ptQ->tPeek = ptQ->tHead;                                            \
        ptQ->tPeekCounter = ptQ->tCounter;                                  \
    )                                                                       \
}

#define DEF_SAFE_QUEUE(__NAME, __TYPE, __PTR_TYPE, __MUTEX_TYPE)            \
        DEF_QUEUE_EX(__NAME, __TYPE, __PTR_TYPE, __MUTEX_TYPE, SAFE_ATOM_CODE)

#define DEF_SAFE_QUEUE_U8(__NAME, __PTR_TYPE,__MUTEX_TYPE)                  \
        DEF_SAFE_QUEUE(__NAME, uint8_t, __PTR_TYPE, __MUTEX_TYPE)

#define EXTERN_SAFE_QUEUE_U8(__NAME, __PTR_TYPE, __MUTEX_TYPE)              \
        EXTERN_QUEUE(__NAME, uint8_t, __PTR_TYPE, __MUTEX_TYPE)

#define DEF_SAFE_QUEUE_U16(__NAME, __PTR_TYPE, __MUTEX_TYPE)                \
        DEF_SAFE_QUEUE(__NAME, uint16_t, __PTR_TYPE, __MUTEX_TYPE)

#define DEF_SAFE_QUEUE_U32(__NAME, __PTR_TYPE, __MUTEX_TYPE)                \
        DEF_SAFE_QUEUE(__NAME, uint32_t __PTR_TYPE, __MUTEX_TYPE)

#define DEF_QUEUE(__NAME, __TYPE, __PTR_TYPE, __MUTEX_TYPE)                 \
        DEF_QUEUE_EX(__NAME, __TYPE, __PTR_TYPE, __MUTEX_TYPE, NONE_ATOM_ACCESS)

#define DEF_QUEUE_U8(__NAME, __PTR_TYPE,__MUTEX_TYPE)                       \
        DEF_QUEUE(__NAME, uint8_t, __PTR_TYPE, __MUTEX_TYPE)

#define DEF_QUEUE_U16(__NAME, __PTR_TYPE, __MUTEX_TYPE)                     \
        DEF_QUEUE(__NAME, uint16_t, __PTR_TYPE, __MUTEX_TYPE)

#define DEF_QUEUE_U32(__NAME, __PTR_TYPE, __MUTEX_TYPE)                     \
        DEF_QUEUE(__NAME, uint32_t __PTR_TYPE, __MUTEX_TYPE)

#define EXTERN_QUEUE_U8(__NAME, __PTR_TYPE, __MUTEX_TYPE)                   \
        EXTERN_QUEUE(__NAME, uint8_t, __PTR_TYPE, __MUTEX_TYPE)

#define EXTERN_QUEUE_U16(__NAME, __PTR_TYPE, __MUTEX_TYPE)                  \
        EXTERN_QUEUE(__NAME, uint16_t, __PTR_TYPE, __MUTEX_TYPE)

#define EXTERN_QUEUE_U32(__NAME, __PTR_TYPE, __MUTEX_TYPE)                  \
        EXTERN_QUEUE(__NAME, uint32_t, __PTR_TYPE, __MUTEX_TYPE)



/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/


#endif