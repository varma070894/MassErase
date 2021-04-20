/*
* Serial Wire Debug Open Library.
* Library Body File.
*
* Copyright (C) 2010-2013, Tomasz Boleslaw CEDRO (http://www.tomek.cedro.info)
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
* 3. Neither the name of the Tomasz Boleslaw CEDRO nor the names of its
*    contributors may be used to endorse or promote products derived from this
*    software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
* OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
* IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.*
*
* Written by Tomasz Boleslaw CEDRO <cederom@tlen.pl>, 2010-2013;
*
*/

/** \file libswd_cmdq.c */

#include <libswd.h>

static libswd_cmd_t * main_q = NULL;
static libswd_cmd_t * error_q = NULL;
static int main_q_size = -1;
static int error_q_size = -1;

/*******************************************************************************
* \defgroup libswd_cmdq Command Queue helper functions
* @{
******************************************************************************/

/** Initialize new queue element in memory that becomes a queue root.
* \param *cmdq pointer to the command queue element of type libswd_cmd_t
* \return LIBSWD_OK on success, LIBSWD_ERROR_CODE code on failure
*/
int libswd_cmdq_init_main(libswd_cmd_t *cmdq, int size)
{
    main_q = cmdq;
    main_q_size = size;
    memset(main_q, 0, sizeof(libswd_cmd_t) * size);
    return LIBSWD_OK;
}

int libswd_cmdq_init_error(libswd_cmd_t *cmdq, int size)
{
    error_q = cmdq;
    error_q_size = size;
    memset(error_q, 0, sizeof(libswd_cmd_t) * size);
    return LIBSWD_OK;
}


/** Find queue root (first element).
* \param *cmdq pointer to any queue element
* \return libswd_cmd_t* pointer to the first element (root), NULL on failure
*/
libswd_cmd_t* libswd_cmdq_find_head(libswd_cmd_t *cmdq)
{
    if (cmdq == NULL) 
    {
        return NULL;
    }
    libswd_cmd_t *cmd = cmdq;
    while (cmd->prev3 != NULL) 
    {
        cmd = cmd->prev3;
    }
    return cmd;
}

/** Find queue tail (last element).
* \param  *cmdq pointer to any queue element
* \return libswd_cmd_t* pointer to the last element (tail), NULL on failure
*/
libswd_cmd_t* libswd_cmdq_find_tail(libswd_cmd_t *cmdq)
{
    if (cmdq == NULL) 
    {
        return NULL;
    }
    libswd_cmd_t *cmd = cmdq;
    while (cmd->next3 != NULL) 
    {
        cmd = cmd->next3;
    }
    return cmd;
}

/** Find last executed element from the *cmdq.
* Start search at *cmdq head, return element pointer or NULL if not found.
* \param *cmdq queue that contains elements.
* \return libswd_cmd_t* pointer to the last executed element or NULL on error.
*/
libswd_cmd_t* libswd_cmdq_find_exectail(libswd_cmd_t *cmdq)
{
    if (cmdq == NULL) 
    {
        return NULL;
    }
    libswd_cmd_t *cmd = libswd_cmdq_find_head(cmdq);
    if (cmd == NULL)
    {
        return NULL;
    }
    for (cmd = libswd_cmdq_find_head(cmdq); cmd; cmd = cmd->next3)
    {
        if (cmd->done) 
        {
            if (cmd->next3)
            {
                if (!cmd->next3->done) 
                {
                    return cmd;
                }
            } 
            else 
            {
                return cmd;
            }
        }
    }
    return NULL;
}

libswd_cmd_t * libswd_cmdq_get_next_mem_location(libswd_cmd_t *cmd)
{
    if (main_q <= cmd && cmd < (main_q + main_q_size))
    {
        cmd++;
        if (cmd >= (main_q + main_q_size))
        {
            /// roll back to start of the array
            cmd = main_q;
        }
        return cmd;
    }
    else if (error_q <= cmd && cmd < (error_q + error_q_size))
    {
        cmd++;
        if (cmd >= (error_q + error_q_size))
        {
            /// roll back to start of the array
            cmd = error_q;
        }
        return cmd;
    }
    else 
    {
        // cmd not part of any allocated array
        return NULL;
    }
}

/** Append element pointed by *cmd at the end of the quque pointed by *cmdq.
* After this operation queue will be pointed by appended element (ie. last
* element added becomes actual quque pointer to show what was added recently).
* \param *cmdq pointer to any element on command queue
* \param *cmd pointer to the command to be appended
* \return number of appended elements (one), LIBSWD_ERROR_CODE on failure
*/
int libswd_cmdq_append(libswd_cmd_t *cmdq, libswd_cmd_t *cmd)
{
    if (cmdq == NULL) 
    {
        return LIBSWD_ERROR_NULLQUEUE;
    }
    if (cmd == NULL) 
    {
        return LIBSWD_ERROR_NULLPOINTER;
    }
    
    libswd_cmd_t *lastcmd = (cmdq->next3 != NULL) ? libswd_cmdq_find_tail(cmdq) : cmdq;
    
    libswd_cmd_t *newcmd = libswd_cmdq_get_next_mem_location(lastcmd);
    if (newcmd == NULL) 
    {
        return LIBSWD_ERROR_QUEUE;
    }
    if (newcmd->next3 != NULL && !newcmd->done)
    {
        /// item to be recycled has valid next (used) and not done
        return LIBSWD_ERROR_QUEUERECYCLE;
    }
    /// copy data to new location
    memcpy(newcmd, cmd, sizeof(libswd_cmd_t));
    
    lastcmd->next3=newcmd;
    newcmd->prev3=lastcmd;
    newcmd->next3 = NULL;
    
    /// make new head
    libswd_cmd_t *head = libswd_cmdq_get_next_mem_location(newcmd);
    head->prev3 = NULL;
    
    return 1;
}

/** Free queue pointed by *cmdq element.
* \param *cmdq pointer to any element on command queue
* \return number of elements destroyed, LIBSWD_ERROR_CODE on failure
*/
int libswd_cmdq_free_main_queue(void)
{
    main_q = NULL;
    main_q_size = -1;  
    return 1;
}

int libswd_cmdq_free_error_queue(void)
{
    main_q = NULL;
    main_q_size = -1;    
    return 1;
}

int libswd_cmdq_free(void)
{
    int res = libswd_cmdq_free_main_queue();
    if (res < 0) 
    {
        return res;
    }
    res = libswd_cmdq_free_error_queue();
    return res;
}

/** Free queue head up to *cmdq element.
* \param *cmdq pointer to the element that becomes new queue root.
* \return number of elements destroyed, or LIBSWD_ERROR_CODE on failure.
*/
//int libswd_cmdq_free_head(libswd_cmd_t *cmdq){
//    if (cmdq==NULL) return LIBSWD_ERROR_NULLQUEUE;
//    int cmdcnt=0;
//    libswd_cmd_t *cmdqroot, *nextcmd;
//    cmdqroot=libswd_cmdq_find_head(cmdq);
//    while(cmdqroot!=cmdq){
//        nextcmd=cmdqroot->next;
//        free(cmdqroot);
//        cmdqroot=nextcmd;
//        cmdcnt++;
//    }
//    cmdqroot->prev=NULL;
//    return cmdcnt;
//}

/** Free queue tail starting after *cmdq element.
* \param *cmdq pointer to the last element on the new queue.
* \return number of elements destroyed, or LIBSWD_ERROR_CODE on failure.
*/
int libswd_cmdq_free_tail(libswd_cmd_t *cmdq)
{
    if (cmdq == NULL) 
    {
        return LIBSWD_ERROR_NULLQUEUE;
    }
    int cmdcnt = 0;
    libswd_cmd_t *cmdqend;
    if (cmdq->next3 == NULL)
    {
        return 0;
    }
    else
    {
        cmdqend = libswd_cmdq_find_tail(cmdq->next3);
        if (cmdqend == NULL)
        {
            return LIBSWD_ERROR_QUEUE;
        }
        while (cmdqend != cmdq)
        {
            cmdqend=cmdqend->prev3;
            
            /// clear the linkage 
            cmdqend->next3->next3 = NULL;
            cmdqend->next3->prev3 = NULL;
            cmdcnt++;
        }
        cmdq->next3 = NULL;
        return cmdcnt;
    }
}

/** Flush command queue contents into interface driver and update **cmdq.
* Operation is specified by LIBSWD_OPERATION and can be used to select
* how to flush the queue, ie. head-only, tail-only, one, all, etc.
* This function is not only used to flush libswdctx->cmdq but also other
* queues (i.e. error handling) so the parameter is **cmdq not libswdctx itself.
* This is the only place where **cmdq is updated to the last executed element.
* Double pointer is used because we update pointer element not its data.
* \param *cmdq pointer to queue to be flushed.
* \param operation tells how to flush the queue.
* \return number of commands transmitted, or LIBSWD_ERROR_CODE on failure.
* !TODO: HOW WE WANT TO UPDATE CMDQ ELEMENT AFTER PROCESSING WITHOUT DOUBLE POINTER?
*/
int libswd_cmdq_flush(libswd_ctx_t *libswdctx, libswd_cmd_t **cmdq, libswd_operation_t operation)
{
    if (libswdctx==NULL) 
    {
        return LIBSWD_ERROR_NULLCONTEXT;
    }
    if (*cmdq == NULL || cmdq == NULL) 
    {
        return LIBSWD_ERROR_NULLQUEUE;
    }
    if (operation < LIBSWD_OPERATION_FIRST || operation > LIBSWD_OPERATION_LAST)
    {
        return LIBSWD_ERROR_BADOPCODE;
    }
    
    int res, cmdcnt = 0;
    libswd_cmd_t *cmd, *firstcmd, *lastcmd;
    
    switch (operation)
    {
//    case LIBSWD_OPERATION_TRANSMIT_HEAD:
//        firstcmd=libswd_cmdq_find_head(*cmdq);
//        lastcmd=*cmdq;
//        break;
//    case LIBSWD_OPERATION_TRANSMIT_TAIL:
//        firstcmd=*cmdq;
//        lastcmd=libswd_cmdq_find_tail(*cmdq);
//        break;
    case LIBSWD_OPERATION_EXECUTE:
//    case LIBSWD_OPERATION_TRANSMIT_ALL:
        firstcmd=libswd_cmdq_find_head(*cmdq);
        lastcmd=libswd_cmdq_find_tail(*cmdq);
        break;
//    case LIBSWD_OPERATION_TRANSMIT_ONE:
//        firstcmd=*cmdq;
//        lastcmd=*cmdq;
//        break;
//    case LIBSWD_OPERATION_TRANSMIT_LAST:
//        firstcmd=libswd_cmdq_find_tail(*cmdq);
//        lastcmd=firstcmd;
//        break;
    default:
        return LIBSWD_ERROR_BADOPCODE;
    }
    
    if (firstcmd == NULL)
    {
        return LIBSWD_ERROR_QUEUEROOT;
    }
    if (lastcmd == NULL) 
    {
        return LIBSWD_ERROR_QUEUETAIL;
    }
    
    if (firstcmd == lastcmd)
    {
        if (!firstcmd->done) 
        {
            res = libswd_drv_transmit(libswdctx, firstcmd);
            if (res < 0) 
            {
                return res;
            }
            *cmdq=firstcmd;
        }
        return 1;
    }
    
    for (cmd = firstcmd; ; cmd=cmd->next3)
    {
        if (cmd->done)
        {
            if (cmd->next3)
            {
                continue;
            } 
            else 
            {
                break;
            }
        }
        res = libswd_drv_transmit(libswdctx, cmd);
        if (res < 0) 
        {
            return res;
        }
        cmdcnt = +res;              // TBD PW intentional ???
        if (cmd == lastcmd)
        {
            break;
        }
    }
    *cmdq = cmd;
    return cmdcnt;
}

/** @} */
