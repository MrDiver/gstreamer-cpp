macro(format_file TARGET_THING)
  # Find all source files
  file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/**.[ch]pp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/**.[ch]
    ${CMAKE_CURRENT_SOURCE_DIR}/include/**.[h]pp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/**.[h]
  )

  # Generate Include directories
  set(INCLUDE_DIR_LIST "")
  get_target_property(dirs ${TARGET_THING} INCLUDE_DIRECTORIES)
  foreach(dir ${dirs})
      set(INCLUDE_DIR_LIST ${INCLUDE_DIR_LIST} -I ${dir})
  endforeach()

  # Run clang-tidy
  find_program(CLANG_TIDY "clang-tidy")
  if(CLANG_TIDY)
    message("Formatting with clang-tidy")
    add_custom_target(tidy ALL
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMAND clang-tidy
      ${ALL_CXX_SOURCE_FILES}
      --format-style=file
      --fix
      --export-fixes="fixes.yaml"
      --config-file="${CMAKE_SOURCE_DIR}/.clang-tidy"
      --use-color
      --
      --std=c++17
      ${INCLUDE_DIR_LIST}
    )
  endif()

  # Run clang-format
  find_program(CLANG_FORMAT "clang-format")
  if(CLANG_FORMAT)
    message("Formatting with clang-formatting")
    add_custom_target(format ALL
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      COMMAND clang-format
      ${ALL_CXX_SOURCE_FILES}
      --style=file
      --verbose
      -i
    )
  endif()
endmacro()