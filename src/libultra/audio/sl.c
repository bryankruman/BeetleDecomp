/*====================================================================
 * sl.c
 *
 * Synopsis:
 *  Sound library global routines
 *
 * Copyright 1993, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *====================================================================*/

#include <libaudio.h>

ALGlobals *alGlobals=0;

void alInit(ALGlobals *g, ALSynConfig *c)
{ /* RE_CONTRACT: Install the supplied global sound-library state and initialize its synth only when alGlobals is null; a second initialization leaves the existing global state unchanged. */
    if (!alGlobals) { /* already initialized? */
        alGlobals = g;
        alSynNew(&alGlobals->drvr, c);
    }
}

void alClose(ALGlobals *glob)
{ /* RE_CONTRACT: If global state is installed, delete the driver in the supplied glob argument and clear alGlobals. RE_QUIRK: the argument is not checked against the installed global pointer. */
    if (alGlobals) {
        alSynDelete(&glob->drvr);
        alGlobals = 0;
    }
}

/* might want to make these macros */
void alLink(ALLink *ln, ALLink *to)
{ /* RE_CONTRACT: Insert ln immediately after to and repair the neighboring back link. RE_UNKNOWN: both nodes must be valid and existing membership is not checked. */					
    ln->next = to->next;     
    ln->prev = to;           
    if (to->next)            
        to->next->prev = ln; 
    to->next = ln;           
}

void alUnlink(ALLink *ln)			
{ /* RE_CONTRACT: Repair the available neighboring links to bypass ln. RE_QUIRK: ln retains its own next and prev fields after removal. */					
    if (ln->next)                   
        ln->next->prev = ln->prev;  
    if (ln->prev)                   
        ln->prev->next = ln->next;  
}





