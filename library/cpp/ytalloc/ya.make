

IF (NOT OS_DARWIN AND NOT SANITIZER_TYPE)
    SET(YT_ALLOC_ENABLED yes)
ENDIF()

RECURSE(
    core
)

IF (YT_ALLOC_ENABLED)
    RECURSE(
    
)
ENDIF()
