

set(command "C:/Program Files/CMake/bin/cmake.exe;-P;C:/dev/Athena/Sandbox/res/models/build/test/gtest/tmp/gtest-gitclone.cmake")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "C:/dev/Athena/Sandbox/res/models/build/test/gtest/src/gtest-stamp/gtest-download-out.log"
  ERROR_FILE "C:/dev/Athena/Sandbox/res/models/build/test/gtest/src/gtest-stamp/gtest-download-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  C:/dev/Athena/Sandbox/res/models/build/test/gtest/src/gtest-stamp/gtest-download-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "gtest download command succeeded.  See also C:/dev/Athena/Sandbox/res/models/build/test/gtest/src/gtest-stamp/gtest-download-*.log")
  message(STATUS "${msg}")
endif()
