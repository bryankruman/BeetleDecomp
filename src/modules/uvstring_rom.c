// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "stdarg.h"
#include "module.h"


char* uvStrChr(const char* s, const char c);
u32 uvStrlen(const char* s);
int uvStrcmp(const char* s1, const char* s2);
void uvSprintf(char* dest, const char* fmt, ...);
void _uv_uvStrFormatInt(s32 number, u16 base, s32* bufPosPtr, char* strBuf, s32 padCount, s32 leftJustify, s32 hasZeroPadding);
void _uvStrFormatFloat(f32 number, s32* bufPosPtr, char* strBuf);
s32 strCharToDigit(char digitChar);
u8 _uvStrDigitToChar(u16);
s32 _uvStrCharToDigit(char digitChar);
int uvAtoi(const char* s);
u8* uvStrcpy(u8* s1, u8* s2);
void uvStrStub(void);
void __entrypoint_func_uvStringEntryPoint(UvString_Exports* exports);

/* Record the export table in the current loading file entry, then publish
 * its six string callbacks.
 * RE_UNKNOWN: loader sequencing, writable table storage, and callback
 * lifetimes remain caller contracts; this entrypoint checks none of them. */
#line 21 "src/modules/uvstring_rom.c"
void MODULE_ENTRY_POINT(func_uvStringEntryPoint)(UvString_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvStrcpy = uvStrcpy;
    exports->uvStrStub = uvStrStub;
    exports->uvStrChr = uvStrChr;
    exports->uvStrlen = uvStrlen;
    exports->uvStrcmp = uvStrcmp;
    exports->uvSprintf = uvSprintf;
}
#line 30 "src/modules/uvstring_rom.c"

/* Return without performing a string operation.
 * RE_UNKNOWN: the historical callback purpose remains unresolved. */
#line 31 "src/modules/uvstring_rom.c"
void uvStrStub(void) {

}
#line 34 "src/modules/uvstring_rom.c"

#line 35 "src/modules/uvstring_rom.c"
/* Find the first matching character before the string terminator.
 * RE_ORIGINAL_QUIRK: searching for the null terminator returns null,
 * retaining this helper behavior rather than the C library contract. */
char* uvStrChr(const char* text, const char character) {
    while (*text != '\0' && character != *text) {
        text++;
    }
    if (*text != 0) {
        return (char*)text;
    }
    return NULL;
}
#line 44 "src/modules/uvstring_rom.c"

/* Count bytes up to the first NUL, advancing the input pointer once per test.
 * RE_UNKNOWN: pointer validity, termination and counts beyond the signed local
 * range require callers; no length limit is checked. */
#line 45 "src/modules/uvstring_rom.c"
u32 uvStrlen(const char* s) {
    s32 len;

    len = 0;
    while (*s++ != 0) {
        len++;
    }
    return len;
}
#line 54 "src/modules/uvstring_rom.c"

#line 55 "src/modules/uvstring_rom.c"
/* Compare string lengths first; only equal-length strings are then
 * compared by character. RE_ORIGINAL_QUIRK: this is length-first order,
 * so unequal-length strings do not use lexicographic ordering. */
int uvStrcmp(const char* first, const char* second) {
    s32 firstLength;
    s32 secondLength;
    s32 characterIndex;

    firstLength = uvStrlen(first);
    secondLength = uvStrlen(second);

    if (firstLength < secondLength) {
        return -1;
    }
    if (secondLength < firstLength) {
        return 1;
    }

    for (characterIndex = 0; characterIndex < firstLength; characterIndex++) {
        if (*first < *second) {
            return -1;
        }
        if (*first > *second) {
            return 1;
        }

        first++;
        second++;
    }

    return 0;
}
#line 84 "src/modules/uvstring_rom.c"

#line 85 "src/modules/uvstring_rom.c"
/* Write integer digits backward into the chosen output field and
 * advance the output cursor. Positive padCount fixes the field width,
 * discarding leading digits or the sign when too narrow. RE_ORIGINAL_QUIRK:
 * left-justified negatives write a space for the sign. RE_UNKNOWN: radix,
 * signed negation/digit-count power bounds and destination capacity require callers. */
void _uvStrFormatInt(s32 number, u16 base, s32* outputCursor, char* output, s32 padCount, s32 leftJustify, s32 hasZeroPadding) {
    u16 digit;
    u16 digitCount;
    s32 outputLength;
    s32 writeIndex;
    u16 isNegative;
    s32 powerOrFieldIndex;
    s32 remainingDigits;
    s32 remainingInputLength;
    s32 remainingFieldLength;

    writeIndex = *outputCursor;
    if (number < 0) {
        isNegative = TRUE;
        number = -number;
    } else {
        isNegative = FALSE;
    }
    digitCount = 0;
    powerOrFieldIndex = 1;
    if (number != 0) {
        while (number >= powerOrFieldIndex) {
            digitCount++;
            powerOrFieldIndex *= base;
        }
    } else {
        digitCount = 1;
    }

    if (padCount > 0) {
        outputLength = padCount;
    } else {
        outputLength = digitCount + isNegative;
    }
    writeIndex += outputLength;
    writeIndex--;
    remainingFieldLength = outputLength;
    remainingDigits = digitCount;
    remainingInputLength = digitCount + isNegative;
    if (leftJustify) {
        for (powerOrFieldIndex = 0; powerOrFieldIndex < outputLength; powerOrFieldIndex++) {
            if (remainingInputLength < remainingFieldLength) {
                output[writeIndex--] = ' ';
                remainingFieldLength--;
            } else if (remainingDigits > 0) {
                digit = number % base;
                output[writeIndex--] = _uvStrDigitToChar(digit);
                number = (number - digit) / base;
                remainingDigits--;
                remainingFieldLength--;
                remainingInputLength--;
            } else if (remainingInputLength == 1) {
                output[writeIndex--] = ' ';
            }
        }
    } else {
        for (powerOrFieldIndex = 0; powerOrFieldIndex < outputLength; powerOrFieldIndex++) {
            if (remainingDigits > 0) {
                digit = number % base;
                output[writeIndex--] = _uvStrDigitToChar(digit);
                number = (number - digit) / base;
            } else {
                if (hasZeroPadding) {
                    if ((powerOrFieldIndex == outputLength - 1) && isNegative) {
                        output[writeIndex--] = '-';
                    } else {
                        output[writeIndex--] = '0';
                    }
                } else {
                    if ((remainingDigits == 0) && isNegative) {
                        output[writeIndex--] = '-';
                    } else {
                        output[writeIndex--] = ' ';
                    }
                }
            }
            remainingDigits--;
        }
    }
    writeIndex += outputLength;
    writeIndex++;
    *outputCursor = writeIndex;
}
#line 168 "src/modules/uvstring_rom.c"

#line 169 "src/modules/uvstring_rom.c"
/* Append a signed decimal value with exactly two fractional digits and
 * advance the output cursor; truncate fractional digits without rounding.
 * RE_UNKNOWN: finite inputs, representable integer casts and signed digit-count
 * powers, and destination capacity remain caller contracts. */
void _uvStrFormatFloat(f32 number, s32* outputCursor, char* output) {
    f32 fraction;
    u16 digit;
    s32 powerOrDigitIndex;
    s32 integerPart;
    u16 isNegative;
    u16 integerDigitCount;
    s32 writeIndex;

    writeIndex = *outputCursor;
    if (number < 0.0f) {
        isNegative = TRUE;
        number = -number;
    } else {
        isNegative = FALSE;
    }
    integerPart = (s32)number;
    integerDigitCount = 0;
    powerOrDigitIndex = 1;
    if (integerPart != 0) {
        while (integerPart >= powerOrDigitIndex) {
            integerDigitCount++;
            powerOrDigitIndex *= 10;
        }
    } else {
        integerDigitCount = 1;
    }
    writeIndex += integerDigitCount + isNegative;
    output[writeIndex++] = '.';
    fraction = number - integerPart;

    for (powerOrDigitIndex = 0; powerOrDigitIndex < 2; powerOrDigitIndex++) {
        fraction *= 10.0f;
        digit = (s32)fraction;
        fraction -= digit;
        output[writeIndex++] = _uvStrDigitToChar(digit);
    }
    writeIndex -= 4;

    for (powerOrDigitIndex = 0; powerOrDigitIndex < integerDigitCount; powerOrDigitIndex++) {
        digit = integerPart % 10;
        output[writeIndex--] = _uvStrDigitToChar(digit);
        integerPart = (integerPart - digit) / 10;
    }
    if (isNegative) {
        output[writeIndex--] = '-';
    }
    writeIndex += integerDigitCount + isNegative + 4;
    *outputCursor = writeIndex;
}
#line 219 "src/modules/uvstring_rom.c"

#line 220 "src/modules/uvstring_rom.c"
/* Map values zero through fifteen to decimal or lowercase hexadecimal
 * characters; values outside that range become a space. */
u8 _uvStrDigitToChar(u16 digitValue) {
    if (digitValue < 10) {
        return '0' + digitValue;
    }
    if (digitValue < 16) {
        return 'W' + digitValue;
    }
    return ' ';
}
#line 229 "src/modules/uvstring_rom.c"

#line 230 "src/modules/uvstring_rom.c"
/* Decode a decimal digit; all other characters contribute zero.
 * Preserve this permissive conversion used by the decimal accumulator. */
s32 _uvStrCharToDigit(char character) {
    if ((character >= '0') && (character <= '9')) {
        return character - '0';
    }
    return 0;
}
#line 236 "src/modules/uvstring_rom.c"

#line 237 "src/modules/uvstring_rom.c"
/* Parse the original d/x/b/f/s/c conversions into an unbounded caller
 * buffer. RE_ORIGINAL_QUIRK: precision is ignored; floats write two decimals.
 * Unsupported conversions, including %%, leave specifier parsing active.
 * RE_UNKNOWN: format syntax, argument types, field-digit scratch bounds and
 * destination capacity remain caller contracts; preserve varargs handling. */
void uvSprintf(char* destination, const char* format, ...) {
    s32 formatIndex;
    s32 fieldDigitIndex;
    s32 outputIndex;
    char fieldDigits[0x5C];
    char* stringArgument;
    s32 integerArgument;
    char formatCharacter;
    char characterArgument;
    s32 padCount; // s5

    int hasZeroPadding;  // s7
    int leftJustify;  // s6
    int parseSpecifier;
    va_list arguments;
    s32 unusedStackWord;

    formatCharacter = format[0];
    va_start(arguments, format);
    parseSpecifier = FALSE;
    formatIndex = 0;
    outputIndex = 0;
    while (formatCharacter != '\0') {
        if (!parseSpecifier) {
            if (formatCharacter == '%') {
                padCount = -1; // s5
                leftJustify = FALSE; // s6
                hasZeroPadding = FALSE; // s7
                parseSpecifier = TRUE;
            } else {
                destination[outputIndex] = formatCharacter;
                outputIndex++;
            }
        } else {
            if (formatCharacter == '-') {
                formatIndex++;
                formatCharacter = format[formatIndex];
                leftJustify = TRUE;
            }
            if (formatCharacter == '\0') {
                break;
            }
            if (formatCharacter == '0') {
                formatIndex++;
                formatCharacter = format[formatIndex];
                hasZeroPadding = TRUE;
            }
            if (formatCharacter == '\0') {
                break;
            }
            if ((formatCharacter >= '1') && (formatCharacter <= '9')) {
                fieldDigitIndex = 0;
                while ((formatCharacter >= '0') && (formatCharacter <= '9')) {
                    fieldDigits[fieldDigitIndex] = formatCharacter;
                    formatIndex++;
                    fieldDigitIndex++;
                    formatCharacter = format[formatIndex];
                }
                fieldDigits[fieldDigitIndex] = '\0';
                padCount = uvAtoi(fieldDigits);
            }
            if (formatCharacter == '\0') {
                break;
            }
            if (formatCharacter == '.') {
                formatIndex++;
                fieldDigitIndex = 0;
                formatCharacter = format[formatIndex];
                while ((formatCharacter >= '0') && (formatCharacter <= '9')) {
                    fieldDigits[fieldDigitIndex] = formatCharacter;
                    formatIndex++;
                    fieldDigitIndex++;
                    formatCharacter = format[formatIndex];
                }
                fieldDigits[fieldDigitIndex] = '\0';
            }
            if (formatCharacter == '\0') {
                break;
            }
            if (formatCharacter == 'x') {
                integerArgument = va_arg(arguments, s32);
                _uvStrFormatInt(integerArgument, 16, &outputIndex, destination, padCount, leftJustify, hasZeroPadding);
                parseSpecifier = FALSE;
            } else if (formatCharacter == 'd') {
                integerArgument = va_arg(arguments, s32);
                _uvStrFormatInt(integerArgument, 10, &outputIndex, destination, padCount, leftJustify, hasZeroPadding);
                parseSpecifier = FALSE;
            } else if (formatCharacter == 'b') {
                integerArgument = va_arg(arguments, s32);
                _uvStrFormatInt(integerArgument, 2, &outputIndex, destination, padCount, leftJustify, hasZeroPadding);
                parseSpecifier = FALSE;
            } else if (formatCharacter == 'f') {
                _uvStrFormatFloat(va_arg(arguments, f64), &outputIndex, destination);
                parseSpecifier = FALSE;
            } else if (formatCharacter == 's') {
                stringArgument = integerArgument = va_arg(arguments, char*);
                parseSpecifier = FALSE;
                while (*stringArgument != 0) {
                    destination[outputIndex] = *stringArgument++;
                    outputIndex++;
                }
            } else if (formatCharacter == 'c') {
                characterArgument = va_arg(arguments, int);
                destination[outputIndex] = characterArgument;
                parseSpecifier = FALSE;
                outputIndex++;
            }
        }
        formatIndex++;
        formatCharacter = format[formatIndex];
    }
    destination[outputIndex] = 0;
    va_end(arguments);
}
#line 351 "src/modules/uvstring_rom.c"

#line 352 "src/modules/uvstring_rom.c"
/* Accumulate every character as a decimal position. Non-digits add
 * zero without stopping conversion; signs and whitespace have no
 * special handling. RE_UNKNOWN: overflow bounds remain a caller contract. */
int uvAtoi(const char* text) {
    s32 textLength;
    s32 characterIndex;
    s32 value;

    textLength = uvStrlen(text);
    value = 0;

    for (characterIndex = 0; characterIndex < textLength; characterIndex++) {
        value *= 10;
        value += _uvStrCharToDigit(text[characterIndex]);
    }
    return value;
}
#line 366 "src/modules/uvstring_rom.c"

#line 367 "src/modules/uvstring_rom.c"
/* Copy bytes through the null terminator and return the destination.
 * RE_UNKNOWN: sufficient destination capacity and any overlap restrictions
 * remain caller contracts; preserve the forward copy order. */
u8* uvStrcpy(u8* destination, u8* source) {
    s32 byteIndex;

    byteIndex = 0;

    while (source[byteIndex] != 0) {
        destination[byteIndex] = source[byteIndex];
        byteIndex++;
    }

    destination[byteIndex] = '\0';
    return destination;
}
#line 380 "src/modules/uvstring_rom.c"
