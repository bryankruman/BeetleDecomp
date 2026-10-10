/* Original game-settings aliases used by preserved local matching C.
 * Keep these outside Splat's symbol list, which requires a canonical name per
 * address. Each address agrees with gGameSettings + its shared field offset.
 */
gGameStateFlag = 0x80025CF8;
gOptionsLanguage = 0x80025E64;
gOptionsStereoMono = 0x80025E68;
gOptionsSpeed = 0x80025E69;
gOptionsMap = 0x80025E6B;
gTransmissionType = 0x80025E2C;

/* Original kernel function addresses retained for unconverted assembly callers.
 * Descriptive C definitions are independently instruction/relocation checked. */
func_80004CC0 = 0x80004CC0; /* uvDebugDrawScaledGlyph */
func_80004E18 = 0x80004E18; /* uvDebugDrawHexDigit */
func_80004E5C = 0x80004E5C; /* uvDebugDrawFixedGlyphSequence */
func_80004F20 = 0x80004F20; /* uvDebugDrawHexWord */
func_80004FD8 = 0x80004FD8; /* uvDebugDrawResolvedAddress */
func_80005074 = 0x80005074; /* uvDebugDrawStackTrace */
func_80002088 = 0x80002088; /* uvListFormRomSpans */
func_8000218C = 0x8000218C; /* uvListFormDebugTotals */
func_8000226C = 0x8000226C; /* uvFindFileBaseBeforeAddress */
func_80002390 = 0x80002390; /* uvSelectTextureRedirectTable */
func_80002AEC = 0x80002AEC; /* uvFillAppStackPrefix */
func_80002B2C = 0x80002B2C; /* uvFillFreeBlockPayloads */
func_80002B80 = 0x80002B80; /* uvInsertFreeBlockCoalesced */
func_80002EAC = 0x80002EAC; /* uvResetAllocatorWithOptionalFill */
func_80003A14 = 0x80003A14; /* uvFindModuleTagBeforeAddress */

/* Original profiler/scheduler names retained for assembly callers. */
func_80000CA4 = 0x80000CA4; /* uvProfilerBegin */
func_80000D58 = 0x80000D58; /* uvProfilerEnd */
func_80000E50 = 0x80000E50; /* uvProfilerAdjustSampleCount */
func_80000EC8 = 0x80000EC8; /* uvProfilerQueryStatistics */
func_80001040 = 0x80001040; /* uvProfilerSetPaused */
func_8000110C = 0x8000110C; /* uvProfilerSetAllPaused */
func_80003C1C = 0x80003C1C; /* uvScDrainInterruptsAndResetTaskState */
func_800048C8 = 0x800048C8; /* uvScSetTraceEnabled */
func_800048E4 = 0x800048E4; /* uvScAdvanceTraceRing */
func_80004958 = 0x80004958; /* uvScRecordTraceEvent */
func_80004A78 = 0x80004A78; /* uvScSetFrameRetraceThreshold */
func_80004A84 = 0x80004A84; /* uvScGetOldestTraceInterval */
func_80004B2C = 0x80004B2C; /* uvScSetBufferSwapSuppressed */

/* SDK compatibility addresses from exact original owners; no additional storage. */
func_8000B6F0 = __CSPPostNextSeqEvent + 0x70;
func_8000B72C = __CSPPostNextSeqEvent + 0xAC;
func_8000B8FC = __CSPPostNextSeqEvent + 0x27C;
.L8000B940 = __CSPPostNextSeqEvent + 0x2C0;
.L8000BCE0 = __CSPPostNextSeqEvent + 0x660;
.L8000BD38 = __CSPPostNextSeqEvent + 0x6B8;
.L8000BD9C = __CSPPostNextSeqEvent + 0x71C;
.L8000BE10 = __CSPPostNextSeqEvent + 0x790;
.L8000C048 = __CSPPostNextSeqEvent + 0x9C8;
.L8000C07C = __CSPPostNextSeqEvent + 0x9FC;
.L8000C114 = __CSPPostNextSeqEvent + 0xA94;
func_8000C12C = __CSPPostNextSeqEvent + 0xAAC;
.L8000C190 = __CSPPostNextSeqEvent + 0xB10;
.L8000C1CC = __CSPPostNextSeqEvent + 0xB4C;
.L8000C1F4 = __CSPPostNextSeqEvent + 0xB74;
.L8000C220 = __CSPPostNextSeqEvent + 0xBA0;
.L8000C24C = __CSPPostNextSeqEvent + 0xBCC;
.L8000C25C = __CSPPostNextSeqEvent + 0xBDC;
.L8000C27C = __CSPPostNextSeqEvent + 0xBFC;
.L8000C2C8 = __CSPPostNextSeqEvent + 0xC48;
.L8000C32C = __CSPPostNextSeqEvent + 0xCAC;
.L8000C438 = __CSPPostNextSeqEvent + 0xDB8;
.L8000C4C0 = __CSPPostNextSeqEvent + 0xE40;
.L8000C4DC = __CSPPostNextSeqEvent + 0xE5C;
.L8000C4FC = __CSPPostNextSeqEvent + 0xE7C;
.L8000C560 = __CSPPostNextSeqEvent + 0xEE0;
.L8000C584 = __CSPPostNextSeqEvent + 0xF04;
.L8000C5F0 = __CSPPostNextSeqEvent + 0xF70;
.L8000C68C = __CSPPostNextSeqEvent + 0x100C;
.L8000C6A8 = __CSPPostNextSeqEvent + 0x1028;
.L8000C6DC = __CSPPostNextSeqEvent + 0x105C;
.L8000C6EC = __CSPPostNextSeqEvent + 0x106C;
func_8000CDB0 = alCSeqGetLoc + 0x140;
func_8000CE74 = alCSeqGetLoc + 0x204;
jtbl_80021170 = 0x80021170;
jtbl_800212F4 = 0x800212F4;
jtbl_80021354 = 0x80021354;
D_800213A4 = 0x800213A4;
D_800213B0 = 0x800213B0;
D_800213B8 = 0x800213B8;
alGlobals = D_80020C00;
