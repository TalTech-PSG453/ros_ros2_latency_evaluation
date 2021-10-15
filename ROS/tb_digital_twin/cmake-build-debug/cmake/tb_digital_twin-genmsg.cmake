# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "tb_digital_twin: 3 messages, 0 services")

set(MSG_I_FLAGS "-Itb_digital_twin:/home/sejego/catkin_ws/src/tb_digital_twin/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(tb_digital_twin_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Current.msg" NAME_WE)
add_custom_target(_tb_digital_twin_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tb_digital_twin" "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Current.msg" ""
)

get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Voltage.msg" NAME_WE)
add_custom_target(_tb_digital_twin_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tb_digital_twin" "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Voltage.msg" ""
)

get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Power.msg" NAME_WE)
add_custom_target(_tb_digital_twin_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tb_digital_twin" "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Power.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(tb_digital_twin
  "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Current.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tb_digital_twin
)
_generate_msg_cpp(tb_digital_twin
  "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Voltage.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tb_digital_twin
)
_generate_msg_cpp(tb_digital_twin
  "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Power.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tb_digital_twin
)

### Generating Services

### Generating Module File
_generate_module_cpp(tb_digital_twin
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tb_digital_twin
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(tb_digital_twin_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(tb_digital_twin_generate_messages tb_digital_twin_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Current.msg" NAME_WE)
add_dependencies(tb_digital_twin_generate_messages_cpp _tb_digital_twin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Voltage.msg" NAME_WE)
add_dependencies(tb_digital_twin_generate_messages_cpp _tb_digital_twin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Power.msg" NAME_WE)
add_dependencies(tb_digital_twin_generate_messages_cpp _tb_digital_twin_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tb_digital_twin_gencpp)
add_dependencies(tb_digital_twin_gencpp tb_digital_twin_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tb_digital_twin_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(tb_digital_twin
  "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Current.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tb_digital_twin
)
_generate_msg_eus(tb_digital_twin
  "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Voltage.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tb_digital_twin
)
_generate_msg_eus(tb_digital_twin
  "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Power.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tb_digital_twin
)

### Generating Services

### Generating Module File
_generate_module_eus(tb_digital_twin
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tb_digital_twin
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(tb_digital_twin_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(tb_digital_twin_generate_messages tb_digital_twin_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Current.msg" NAME_WE)
add_dependencies(tb_digital_twin_generate_messages_eus _tb_digital_twin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Voltage.msg" NAME_WE)
add_dependencies(tb_digital_twin_generate_messages_eus _tb_digital_twin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Power.msg" NAME_WE)
add_dependencies(tb_digital_twin_generate_messages_eus _tb_digital_twin_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tb_digital_twin_geneus)
add_dependencies(tb_digital_twin_geneus tb_digital_twin_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tb_digital_twin_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(tb_digital_twin
  "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Current.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tb_digital_twin
)
_generate_msg_lisp(tb_digital_twin
  "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Voltage.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tb_digital_twin
)
_generate_msg_lisp(tb_digital_twin
  "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Power.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tb_digital_twin
)

### Generating Services

### Generating Module File
_generate_module_lisp(tb_digital_twin
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tb_digital_twin
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(tb_digital_twin_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(tb_digital_twin_generate_messages tb_digital_twin_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Current.msg" NAME_WE)
add_dependencies(tb_digital_twin_generate_messages_lisp _tb_digital_twin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Voltage.msg" NAME_WE)
add_dependencies(tb_digital_twin_generate_messages_lisp _tb_digital_twin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Power.msg" NAME_WE)
add_dependencies(tb_digital_twin_generate_messages_lisp _tb_digital_twin_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tb_digital_twin_genlisp)
add_dependencies(tb_digital_twin_genlisp tb_digital_twin_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tb_digital_twin_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(tb_digital_twin
  "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Current.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tb_digital_twin
)
_generate_msg_nodejs(tb_digital_twin
  "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Voltage.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tb_digital_twin
)
_generate_msg_nodejs(tb_digital_twin
  "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Power.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tb_digital_twin
)

### Generating Services

### Generating Module File
_generate_module_nodejs(tb_digital_twin
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tb_digital_twin
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(tb_digital_twin_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(tb_digital_twin_generate_messages tb_digital_twin_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Current.msg" NAME_WE)
add_dependencies(tb_digital_twin_generate_messages_nodejs _tb_digital_twin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Voltage.msg" NAME_WE)
add_dependencies(tb_digital_twin_generate_messages_nodejs _tb_digital_twin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Power.msg" NAME_WE)
add_dependencies(tb_digital_twin_generate_messages_nodejs _tb_digital_twin_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tb_digital_twin_gennodejs)
add_dependencies(tb_digital_twin_gennodejs tb_digital_twin_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tb_digital_twin_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(tb_digital_twin
  "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Current.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tb_digital_twin
)
_generate_msg_py(tb_digital_twin
  "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Voltage.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tb_digital_twin
)
_generate_msg_py(tb_digital_twin
  "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Power.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tb_digital_twin
)

### Generating Services

### Generating Module File
_generate_module_py(tb_digital_twin
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tb_digital_twin
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(tb_digital_twin_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(tb_digital_twin_generate_messages tb_digital_twin_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Current.msg" NAME_WE)
add_dependencies(tb_digital_twin_generate_messages_py _tb_digital_twin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Voltage.msg" NAME_WE)
add_dependencies(tb_digital_twin_generate_messages_py _tb_digital_twin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sejego/catkin_ws/src/tb_digital_twin/msg/Power.msg" NAME_WE)
add_dependencies(tb_digital_twin_generate_messages_py _tb_digital_twin_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tb_digital_twin_genpy)
add_dependencies(tb_digital_twin_genpy tb_digital_twin_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tb_digital_twin_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tb_digital_twin)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tb_digital_twin
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(tb_digital_twin_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tb_digital_twin)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tb_digital_twin
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(tb_digital_twin_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tb_digital_twin)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tb_digital_twin
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(tb_digital_twin_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tb_digital_twin)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tb_digital_twin
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(tb_digital_twin_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tb_digital_twin)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tb_digital_twin\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tb_digital_twin
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(tb_digital_twin_generate_messages_py std_msgs_generate_messages_py)
endif()
