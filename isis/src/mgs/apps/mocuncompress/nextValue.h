/*
NOTICE

The software accompanying this notice (the "Software") is provided to you
free of charge to facilitate your use of the data collected by the Mars
Orbiter Camera (the "MOC Data").  Malin Space Science Systems ("MSSS")
grants to you (either as an individual or entity) a personal,
non-transferable, and non-exclusive right (i) to use and reproduce the
Software solely for the purpose of accessing the MOC Data; (ii) to modify
the source code of the Software as necessary to maintain or adapt the
Software to run on alternate computer platforms; and (iii) to compile, use
and reproduce the modified versions of the Software solely for the purpose
of accessing the MOC Data.  In addition, you may distribute the Software,
including any modifications thereof, solely for use with the MOC Data,
provided that (i) you must include this notice with all copies of the
Software to be distributed; (ii) you may not remove or alter any
proprietary notices contained in the Software; (iii) you may not charge any
third party for the Software; and (iv) you will not export the Software
without the appropriate United States and foreign government licenses.

You acknowledge that no title to the intellectual property in the Software
is transferred to you.  You further acknowledge that title and full
ownership rights to the Software will remain the exclusive property of MSSS
or its suppliers, and you will not acquire any rights to the Software
except as expressly set forth above.  The Software is provided to you AS
IS.  MSSS MAKES NO WARRANTY, EXPRESS OR IMPLIED, WITH RESPECT TO THE
SOFTWARE, AND SPECIFICALLY DISCLAIMS THE IMPLIED WARRANTIES OF
NON-INFRINGEMENT OF THIRD PARTY RIGHTS, MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE.  SOME JURISDICTIONS DO NOT ALLOW THE EXCLUSION OR
LIMITATION OF INCIDENTAL OR CONSEQUENTIAL DAMAGES, SO SUCH LIMITATIONS OR
EXCLUSIONS MAY NOT APPLY TO YOU.

Your use or reproduction of the Software constitutes your agreement to the
terms of this Notice.  If you do not agree with the terms of this notice,
promptly return or destroy all copies of the Software in your possession.

Copyright (C) 1999 Malin Space Science Systems.  All Rights Reserved.

SCCSID @(#)nextValue.h  1.1 10/04/99
*/
/* SCCShid @(#)nextValue.h (nextValue.h) 1.3 */

#ifndef nextValue_h

#define nextValue_h

#include "fs.h"
#include "bitsOut.h"
#include "predDecompCommon.h"

#define nextValue(DEFvalue,DEFcode,DEFleft,DEFright,DEFcur,DEFbitCount,DEFdata) \
{ \
register uint8 *LCLcode,*LCLleft,*LCLright; \
register uint32 LCLindex;    /* Current internal node index */ \
 \
  LCLcode  = (DEFcode); \
  LCLleft  = (DEFleft); \
  LCLright = (DEFright); \
 \
  /* Start at the top of the huffman "tree" */ \
  LCLindex = 0; \
 \
  /* Proceed with decoding */ \
  while (1) { \
    /* Examine current bit of encoded byte */ \
    if ((DEFcur & 0x1) == 0x0) { \
    /* If current bit is a zero go "left" */ \
      /* Decide if "left" is another internal node or a leaf */ \
      if ((LCLcode[LCLindex] & LEFT) == 0) { \
      /* "left" is a leaf */ \
        /* Save decoded value and break out of loop */ \
        (DEFvalue) = LCLleft[LCLindex]; \
        break; \
      } else { \
      /* "left" is an internal node */ \
        /* Move to new node */ \
        LCLindex = LCLleft[LCLindex]; \
      } \
    } else { \
    /* If current bit is a one go "right" */ \
      /* Decide if "right" is another internal node or a leaf */ \
      if ((LCLcode[LCLindex] & RIGHT) == 0) { \
      /* "right" is a leaf */ \
        /* Save decoded value and break out of loop */ \
        (DEFvalue) = LCLright[LCLindex]; \
        break; \
      } else { \
      /* "right" is an internal node */ \
        /* Move to new node */ \
        LCLindex = LCLright[LCLindex]; \
      } \
    }; \
 \
    /* Move to next bit */ \
    DEFbitCount++; \
 \
    /* Are there any more bits in the current byte */ \
    if (DEFbitCount > 7) { \
    /* No more bits in current byte */ \
      /* Start at the beginning of the next byte */ \
      DEFbitCount = 0; \
 \
      /* Move pointer */ \
      DEFdata++; \
 \
      /* Get new byte */ \
      DEFcur = *DEFdata; \
    } else { \
    /* More bits in current byte */ \
      /* Shift next bit into position */ \
      DEFcur >>= 1; \
    } \
  }; \
 \
  /* Move to next bit */ \
  DEFbitCount++; \
 \
  /* Are there any more bits in the current byte */ \
  if (DEFbitCount > 7) { \
  /* No more bits in current byte */ \
    /* Start at the beginning of the next byte */ \
    DEFbitCount = 0; \
 \
    /* Move pointer */ \
    DEFdata++; \
 \
    /* Get new byte */ \
    DEFcur = *DEFdata; \
  } else { \
  /* More bits in current byte */ \
    /* Shift next bit into position */ \
    DEFcur >>= 1; \
  }; \
}

#endif
