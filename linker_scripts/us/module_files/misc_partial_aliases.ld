/* Preserve original initializer and caller relocation names.
 * These partial-link aliases allocate no code or storage. */
func_misc_004012E4 = miscInterpolateTranslationAndQuaternionMatrix;
func_misc_0040213C = miscBuildThreeAngleMatrix;
func_misc_00402A5C = miscBuildTranslationAndThreeAngleMatrix;
func_misc_00403110 = miscCopyObjectHierarchyMatrices;
func_misc_00403348 = miscMeasurePlanarSegmentCircleFraction;
func_misc_00403748 = miscEvaluateRadiusGatedPlaneCrossing;
func_misc_00403A5C = miscCreateGuiCurveValueRow;
func_misc_00403CD8 = miscEvaluateClampedSineAngle;
func_misc_00403D8C = miscDrawPackedNibbleLine;
func_misc_00402730 = miscMeasurePlanarSegmentProjection;
func_misc_00402BFC = miscAdjustDirectionAlongNormalPreservingScaledLength;
func_misc_00402EFC = miscApproachWithScaledDistanceCap;
func_misc_00402874 = miscUpdateTerrainHeightLimits;
func_misc_00403650 = miscDrawProfilerMilliseconds;
func_misc_004019FC = miscFindPlanarCrossingAndNormal;
func_misc_00401FA0 = miscBuildQuaternionFromThreeAngles;

/* Exact order; no artificial padding or ELF patching. */
SECTIONS
{
 .rodata 0 :
 {
  build/asm/us/data/modules/misc.rodata-prefix.o(.rodata)
  D_misc_00404290 = .;
  D_misc_00404294 = . + 4;
  D_misc_00404298 = . + 8;
  D_misc_0040429C = . + 12;
  build/src/modules/misc.o(.rodata)
  build/asm/us/data/modules/misc.rodata-suffix.o(.rodata)
 }
}
