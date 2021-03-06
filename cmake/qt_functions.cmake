find_program(QT_UIC_PATH NAMES uic uic-qt5)
find_program(QT_RCC_PATH NAMES rcc rcc-qt5)
find_program(QT_MOC_PATH NAMES moc moc-qt5)
if (${QT_UIC_PATH} STREQUAL QT_UIC_PATH-NOTFOUND)
    message(FATAL_ERROR "Qt form compiler (uic) not found, building the project will not be possible and was therefore stopped")
endif ()
if (${QT_RCC_PATH} STREQUAL QT_RCC_PATH-NOTFOUND)
    message(FATAL_ERROR "Qt resource compiler (rcc) not found, building the project will not be possible and was therefore stopped")
endif ()
if (${QT_MOC_PATH} STREQUAL QT_MOC_PATH-NOTFOUND)
    message(FATAL_ERROR "Qt meta object compiler (moc) not found, building the project will not be possible and was therefore stopped")
endif ()

find_package(Qt5 COMPONENTS Core Widgets Gui OpenGL REQUIRED)
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories(${Qt5Opengl_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

function (qt_add_moc_files output_var)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/moc)
    foreach (src_file ${ARGN})
        file (READ ${SOURCE_DIR}/${src_file} file)
        if ("${file}" MATCHES "Q_OBJECT")
            get_filename_component(out_name ${src_file} NAME_WE)
            add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/moc/${out_name}.moc.cpp
                               COMMAND ${QT_MOC_PATH} -o ${CMAKE_CURRENT_BINARY_DIR}/moc/${out_name}.moc.cpp ${SOURCE_DIR}/${src_file} --no-notes
                               DEPENDS ${SOURCE_DIR}/${src_file})
            set(moc_output ${moc_output} ${CMAKE_CURRENT_BINARY_DIR}/moc/${out_name}.moc.cpp)
        endif ()
    endforeach ()
    SET(${output_var} "${moc_output}" PARENT_SCOPE)
endfunction ()

function (qt_add_uic_files output_var)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/ui)
    foreach (gui_file ${ARGN})
        add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/ui/${gui_file}.h
                           COMMAND ${QT_UIC_PATH} -o ${CMAKE_CURRENT_BINARY_DIR}/include/ui/${gui_file}.h ${UI_DIR}/${gui_file}
                           DEPENDS ${UI_DIR}/${gui_file})
        set(uic_output ${uic_output} ${CMAKE_CURRENT_BINARY_DIR}/include/ui/${gui_file}.h)
    endforeach ()
    SET(${output_var} "${uic_output}" PARENT_SCOPE)
endfunction()

function (qt_add_rcc_file output_var qrcfile)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/rcc)
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/rcc/${output_var}.h
                       COMMAND ${QT_RCC_PATH} -o ${CMAKE_CURRENT_BINARY_DIR}/include/rcc/${output_var}.h ${qrcfile}
                       DEPENDS ${qrcfile})
    SET(${output_var} "${CMAKE_CURRENT_BINARY_DIR}/include/rcc/${output_var}.h" PARENT_SCOPE)
endfunction()

function (qt_add_rcc_file output_var qrcfile depends_on)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/rcc)
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/rcc/${output_var}.h
                       COMMAND ${QT_RCC_PATH} -o ${CMAKE_CURRENT_BINARY_DIR}/include/rcc/${output_var}.h ${qrcfile}
                       DEPENDS ${qrcfile} ${depends_on})
    SET(${output_var} "${CMAKE_CURRENT_BINARY_DIR}/include/rcc/${output_var}.h" PARENT_SCOPE)
endfunction()
