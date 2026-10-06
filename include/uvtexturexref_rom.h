#ifndef UVTEXTUREXREF_ROM_H
#define UVTEXTUREXREF_ROM_H

typedef struct UvTexturexref_Exports_s {
    /* 0x0 */ void (*uvParseFreeUVTP)();                       /* inferred */
    /* 0x4 */ ParsedUVTP *(*uvParseUVTP)(u8 *);            /* inferred */
} UvTexturexref_Exports;                            /* size = 0x8 */

#endif /* UVTEXTUREXREF_ROM_H */
