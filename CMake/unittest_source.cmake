INCLUDE_DIRECTORIES(${CRAP_LIBRARIES_PATH}/unittest/)
IF(WIN32)
	INCLUDE_DIRECTORIES(${CRAP_LIBRARIES_PATH}/unittest/Win32/)
ELSEIF(WIN32)
	INCLUDE_DIRECTORIES(${CRAP_LIBRARIES_PATH}/unittest/Posix/)
ENDIF(WIN32)

SET( UNITTEST_SOURCEFILES
    ${CRAP_LIBRARIES_PATH}/unittest/XmlTestReporter.cpp
    ${CRAP_LIBRARIES_PATH}/unittest/TimeConstraint.cpp
    ${CRAP_LIBRARIES_PATH}/unittest/TestRunner.cpp 
    ${CRAP_LIBRARIES_PATH}/unittest/TestResults.cpp
    ${CRAP_LIBRARIES_PATH}/unittest/TestReporterStdout.cpp
    ${CRAP_LIBRARIES_PATH}/unittest/TestReporter.cpp
    ${CRAP_LIBRARIES_PATH}/unittest/TestList.cpp
    ${CRAP_LIBRARIES_PATH}/unittest/TestDetails.cpp
    ${CRAP_LIBRARIES_PATH}/unittest/Test.cpp
    ${CRAP_LIBRARIES_PATH}/unittest/ReportAssert.cpp
    ${CRAP_LIBRARIES_PATH}/unittest/MemoryOutStream.cpp
    ${CRAP_LIBRARIES_PATH}/unittest/DeferredTestResult.cpp
    ${CRAP_LIBRARIES_PATH}/unittest/DeferredTestReporter.cpp
    ${CRAP_LIBRARIES_PATH}/unittest/CurrentTest.cpp
    ${CRAP_LIBRARIES_PATH}/unittest/Checks.cpp
    ${CRAP_LIBRARIES_PATH}/unittest/AssertException.cpp
)

IF(WIN32)
	SET( UNITTEST_SOURCEFILES
		${UNITTEST_SOURCEFILES}
		${CRAP_LIBRARIES_PATH}/unittest/Win32/TimeHelpers.cpp
		)
ELSE(WIN32)
	SET( UNITTEST_SOURCEFILES
		${UNITTEST_SOURCEFILES}
		${CRAP_LIBRARIES_PATH}/unittest/Posix/TimeHelpers.cpp
		${CRAP_LIBRARIES_PATH}/unittest/Posix/SignalTranslator.cpp
		)
ENDIF(WIN32)
