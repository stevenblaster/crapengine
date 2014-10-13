
#macro to copy openall
macro(CopyOpenALLibToBuildDir target libpath)
    add_custom_command(
        TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${libpath}"
        $<TARGET_FILE_DIR:${target}>
    )
endmacro()
