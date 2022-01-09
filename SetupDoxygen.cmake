# check if Doxygen is installed
if(BUILD_DOC)
  file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/../doc/html")
  find_package(Doxygen)
  if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/../doc/Doxyfile.in)

    message("Doxygen build started")

    add_custom_target(doc_doxygen ALL
          COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
          WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../doc"
          COMMENT "Generating API documentation with Doxygen"
          VERBATIM )
  else (DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate Documentation")
  endif(DOXYGEN_FOUND)
endif(BUILD_DOC)