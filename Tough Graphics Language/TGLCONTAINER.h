/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TGLCONSTAINER.h
 * PURPOSE     : Tough Graphics Language project.
 *               Container implementation file.
 * PROGRAMMER  : CGSG'2018.
 * LAST UPDATE : 21.10.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __TGLCONTAINER_H_
#define __TGLCONTAINER_H_

#include "tgl.h"

/* TGL namespace */
namespace tgl
{
  /* Container namespace */
  namespace container
  {
    /* Stack class declaration */
    template <class type = FLT>
      class stack
      {
      public:
        /* Stack entry structure */
        struct stack_entry
        {
          type Data;
          stack_entry *Next;

          /* Default stack entry structure constructor.
           * ARGUMENTS: None;
           */
          stack_entry( VOID )
          {
          } /* End of 'stack_entry' function */

          /* Stack entry structure constructor.
           * ARGUMENTS:
           *   - data:
           *       type data;
           *   - pointer on next element:
           *       stack_entry *Next;
           */
          stack_entry( type Data, stack_entry *Next = nullptr ) : Data(Data), Next(Next)
          {
          } /* End of 'stack_entry' function */
        };

        stack_entry *Start, **Memory;
        INT MinStackSize, CurrentFreeSize, Level;
        /* Stack class constructor.
         * ARGUMENTS: None.
         */
        stack( VOID )
        {
          /*
          MinStackSize = 100;
          Level = 1;
          CurrentFreeSize = MinStackSize * Level;
          **Memory = new stack_entry*[MinStackSize];
           */
          Start = nullptr;
        } /* End of 'stack' function */

        /* Stack class destructor.
         * ARGUMENTS: None.
         */
        ~stack( VOID )
        {
          stack_entry *tmp;

          while (Start != nullptr)
          {
            tmp = Start;
            Start = Start->Next;
            delete tmp;
          }
        }

        /* Push data to stack function.
         * ARGUMENTS:
         *   - data for pushing:
         *       type Data;
         * RETURNS:
         *   (stack &) reference on stack.
         */
        stack & Push( type Data )
        {
          stack_entry *NewData = new stack_entry(Data, Start);

          Start = NewData;
          return (*this);
        } /* End of 'Push' function*/

        /* Pop data from stack function.
         * ARGUMENTS:
         *   - pointer for saving data:
         *       type *Data;
         * RETURNS:
         *   (BOOL) if success - true, else - false.
         */
        BOOL Pop( type *Data )
        {
          stack_entry *tmp;

          if (Start == nullptr)
            return FALSE;

          tmp = Start;

          if (Data != nullptr)
            *Data = tmp->Data;
          Start = Start->Next;

          delete tmp;

          return TRUE;
        } /* End of 'Push' function*/

        /* Display stock function.
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        VOID Display( VOID )
        {
          stack_entry *tmp = Start;

          while (tmp != nullptr)
          {
            std::cout << tmp->Data <<", ";
            tmp = tmp->Next;
          }
        } /* End of 'Display' function */
      }; /* End of 'stack' class*/

      
    /* Stack class declaration */
    template <class type = FLT>
      class queue
      {
      public:
        /* Queue entry structure */
        struct queue_entry
        {
          type Data;
          queue_entry *Next;

          /* Default queue entry structure constructor.
           * ARGUMENTS: None;
           */
          queue_entry( VOID )
          {
          } /* End of 'queue_entry' function */

          /* Queue entry structure constructor.
           * ARGUMENTS:
           *   - data:
           *       type data;
           *   - pointer on next element:
           *       queue_entry *Next;
           */
          queue_entry( type Data, queue_entry *Next = nullptr ) : Data(Data), Next(Next)
          {
          } /* End of 'queue_entry' function */
        };

        queue_entry *Start, *End, **Memory;
        INT MinQueueSize, CurrentFreeSize, Level;

        /* Queue class copy constructor.
         * ARGUMENTS:
         *   - queue for copy
         *       const queue &Q;
         */
        queue( queue &Q )
        {
          queue_entry *tmp = Q.Start;

          while (tmp != nullptr)
          {
            Put(tmp->Data);
            tmp = tmp->Next;
          }
        } /* End of 'queue' function */

        /* Queue class constructor.
         * ARGUMENTS: None.
         */
        queue( VOID )
        {
          /*
          MinqueueSize = 100;
          Level = 1;
          CurrentFreeSize = MinqueueSize * Level;
          **Memory = new queue_entry*[MinqueueSize];
           */
          Start = nullptr;
          End = nullptr;
        } /* End of 'queue' function */

        /* Queue class destructor.
         * ARGUMENTS: None.
         */
        ~queue( VOID )
        {
          queue_entry *tmp;

          while (Start != nullptr)
          {
            tmp = Start;
            Start = Start->Next;
            delete tmp;
          }
        } /* End of 'queue' function */

        /* Put data to queue function.
         * ARGUMENTS:
         *   - data for pushing:
         *       type Data;
         * RETURNS:
         *   (queue &) reference on queue.
         */
        queue & Put( type Data )
        {
          queue_entry *NewData = new queue_entry(Data, nullptr);

          if (Start == nullptr)
            Start = NewData;
          else
            End->Next = NewData;
          End = NewData;
          return (*this);
        } /* End of 'Put' function*/

        /* Watch start element function.
         * ARGUMENTS:
         *   - pointer for saving data:
         *       type *Data;
         * RETURNS:
         *   (BOOL) if success - true, else - false.
         */
        BOOL Watch( type *Data )
        {
          if (Start == nullptr)
            return FALSE;

          if (Data != nullptr)
            *Data = Start->Data;

          return TRUE;
        } /* End of 'Get' function*/

        /* Get data from queue function.
         * ARGUMENTS:
         *   - pointer for saving data:
         *       type *Data;
         * RETURNS:
         *   (BOOL) if success - true, else - false.
         */
        BOOL Get( type *Data )
        {
          queue_entry *tmp;

          if (Start == nullptr)
            return FALSE;

          tmp = Start;

          if (Data != nullptr)
            *Data = tmp->Data;
          Start = Start->Next;

          delete tmp;

          return TRUE;
        } /* End of 'Get' function*/

        /* Display stock function.
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        VOID Display( VOID )
        {
          queue_entry *tmp = Start;

          while (tmp != nullptr)
          {
            std::cout << tmp->Data <<", ";
            tmp = tmp->Next;
          }
        } /* End of 'Display' function */
      }; /* End of 'queue' class*/
  } /* end of 'constainer' namespace */
} /* end of 'tgl' namespace */

#endif /* __TGLCONTAINER_H_ */

/* END OF 'TGLCONTAINER.h' FILE */