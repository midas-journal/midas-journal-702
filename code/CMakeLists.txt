PROJECT( ADAPTIVETHRESHOLD )

# CMake >= 2.6 MUST be installed
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )

IF( COMMAND CMAKE_POLICY )
  CMAKE_POLICY( VERSION 2.4 )
  CMAKE_POLICY( SET CMP0005 OLD )
  CMAKE_POLICY( SET CMP0003 NEW )
ENDIF(COMMAND CMAKE_POLICY)

#---------------------------------------------------------------------------
# Find ITK.
FIND_PACKAGE(ITK)
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
  MESSAGE(FATAL_ERROR
    "Cannot build without ITK.  Please set ITK_DIR.")
ENDIF(ITK_FOUND)

INCLUDE( CTest )

ADD_EXECUTABLE(adaptiveOtsuThresh2D AdaptiveOtsuThresholdImageFilter2D.cxx )
TARGET_LINK_LIBRARIES(adaptiveOtsuThresh2D ITKCommon ITKIO )

ADD_EXECUTABLE(adaptiveOtsuThresh3D AdaptiveOtsuThresholdImageFilter3D.cxx )
TARGET_LINK_LIBRARIES(adaptiveOtsuThresh3D ITKCommon ITKIO )

ADD_TEST( adaptiveOtsuThresh2DTest
  ${EXECUTABLE_OUTPUT_PATH}/adaptiveOtsuThresh2D
  ${ADAPTIVETHRESHOLD_SOURCE_DIR}/input.png
  ${ADAPTIVETHRESHOLD_SOURCE_DIR}/output.png
  20 5000 3 50
	)

