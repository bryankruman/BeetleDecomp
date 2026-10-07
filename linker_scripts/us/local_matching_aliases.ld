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
