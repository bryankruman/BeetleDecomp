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
D_80020C00 = alGlobals;

/* Four additional byte-proven SDK owners; no additional storage.
 * FUNC type/size restoration and updated N64Recomp discovery remain mandatory. */
func_8001372C = __setInstChanState + 0x101C;
func_80012F0C = __setInstChanState + 0x7FC;
.L80013CFC = __setInstChanState + 0x15EC;
.L8001390C = __setInstChanState + 0x11FC;
.L8001385C = __setInstChanState + 0x114C;
.L80013790 = __setInstChanState + 0x1080;
.L80012F50 = __setInstChanState + 0x840;
func_80012898 = __setInstChanState + 0x188;
.L80013AC4 = __setInstChanState + 0x13B4;
.L80013534 = __setInstChanState + 0xE24;
.L80013648 = __setInstChanState + 0xF38;
.L8001383C = __setInstChanState + 0x112C;
.L80013444 = __setInstChanState + 0xD34;
.L80013CEC = __setInstChanState + 0x15DC;
.L800132A4 = __setInstChanState + 0xB94;
.L800132FC = __setInstChanState + 0xBEC;
.L80013A1C = __setInstChanState + 0x130C;
.L80013C80 = __setInstChanState + 0x1570;
.L800134A0 = __setInstChanState + 0xD90;
func_80012C6C = __setInstChanState + 0x55C;
.L80013AA4 = __setInstChanState + 0x1394;
.L800133DC = __setInstChanState + 0xCCC;
.L80013AD8 = __setInstChanState + 0x13C8;
.L80013714 = __setInstChanState + 0x1004;
.L800138A8 = __setInstChanState + 0x1198;
.L80013B6C = __setInstChanState + 0x145C;
.L80013AFC = __setInstChanState + 0x13EC;
.L80013C64 = __setInstChanState + 0x1554;
.L80013364 = __setInstChanState + 0xC54;
.L80013BFC = __setInstChanState + 0x14EC;
.L8001367C = __setInstChanState + 0xF6C;
.L80013C9C = __setInstChanState + 0x158C;
.L80017DC8 = _doModFunc + 0x738;
.L80017D94 = _doModFunc + 0x704;
.L80017E20 = _doModFunc + 0x790;
.L80017EB4 = _doModFunc + 0x824;
.L80017F2C = _doModFunc + 0x89C;
.L80017D60 = _doModFunc + 0x6D0;
.L80017DF4 = _doModFunc + 0x764;
.L80017E4C = _doModFunc + 0x7BC;
func_80010F70 = alLoadParam + 0x580;
func_80011C04 = _ldexpf + 0x3C4;
.L80012378 = _ldexpf + 0xB38;
.L80012000 = _ldexpf + 0x7C0;
func_80011A34 = _ldexpf + 0x1F4;
.L80012398 = _ldexpf + 0xB58;
.L80012338 = _ldexpf + 0xAF8;
.L800122E4 = _ldexpf + 0xAA4;
func_80011E9C = _ldexpf + 0x65C;
.L80012140 = _ldexpf + 0x900;
D_80020DB0 = 0x80020DB0;
D_80020EAE = 0x80020EAE;
D_80020EB0 = 0x80020EB0;
D_80021460 = 0x80021460;
D_80021468 = 0x80021468;
D_800216F8 = 0x800216F8;
D_80021830 = 0x80021830;
jtbl_80021470 = 0x80021470;
jtbl_800214C0 = 0x800214C0;
jtbl_80021644 = 0x80021644;
jtbl_80021698 = 0x80021698;
jtbl_80021810 = 0x80021810;

/* Forty additional byte-proven SDK owners. Original private FUNC extents
 * require explicit recompiler metadata; storage aliases allocate no bytes. */
func_8000D9E0 = 0x8000D9E0;
func_8000DA6C = 0x8000DA6C;
.L8000DF60 = 0x8000DF60;
.L80011600 = alResampleParam + 0xC0;
func_800183A0 = alSeqGetLoc + 0x40;
func_800183A8 = alSeqGetLoc + 0x48;
func_80018828 = alSeqGetLoc + 0x4C8;
func_80018878 = alSeqGetLoc + 0x518;
D_80021700 = 0x80021700;
D_80021704 = 0x80021704;
jtbl_80021400 = 0x80021400;
D_80021418 = 0x80021418;
D_80020C20 = 0x80020C20;
D_80020C88 = 0x80020C88;
D_80020D10 = 0x80020D10;
D_80020D38 = 0x80020D38;
D_80020D60 = 0x80020D60;
D_80020D88 = 0x80020D88;
jtbl_80021420 = 0x80021420;
D_80021448 = 0x80021448;
D_80021450 = 0x80021450;
D_80021840 = 0x80021840;
D_80021848 = 0x80021848;
D_800213C0 = 0x800213C0;
jtbl_800213C8 = 0x800213C8;
D_800213F0 = 0x800213F0;
D_800213F8 = 0x800213F8;

/* Original native bindings for four stock AI/libc units; no storage allocation. */
_Printf = 0x80016F80;
func_8000FFD0 = 0x8000FFD0;

/* Original controller references; retained assembly storage is not transferred. */
__osContLastCmd = 0x80032230;
__osContPifRam = 0x800321F0;
__osMaxControllers = 0x80032231;
func_8000E520 = osContStartQuery;
func_8000E5A4 = osContGetQuery;
func_8000E7B0 = osContSetCh;

/* Original compact-sequence public names; aliases allocate no storage.
 * Their original FUNC type and declared extents require final ELF checks. */
alSeqpGetChlFXMix = alCSPGetChlFXMix;
alSeqpGetChlPan = alCSPGetChlPan;
alSeqpGetChlPriority = alCSPGetChlPriority;
alSeqpGetChlProgram = alCSPGetChlProgram;
alSeqpGetChlVol = alCSPGetChlVol;
alSeqpGetState = alCSPGetState;
alSeqpPlay = alCSPPlay;
alSeqpSendMidi = alCSPSendMidi;
alSeqpSetBank = alCSPSetBank;
alSeqpSetChlFXMix = alCSPSetChlFXMix;
alSeqpSetChlPan = alCSPSetChlPan;
alSeqpSetChlPriority = alCSPSetChlPriority;
alSeqpSetChlProgram = alCSPSetChlProgram;
alSeqpSetChlVol = alCSPSetChlVol;
alSeqpSetSeq = alCSPSetSeq;
alSeqpSetTempo = alCSPSetTempo;
alSeqpSetVol = alCSPSetVol;
alSeqpStop = alCSPStop;

/* Native-proven extern views; retained original storage is not migrated. */
hdwrBugFlag = D_80020C10;
__osPfsPifRam = D_80033730;
