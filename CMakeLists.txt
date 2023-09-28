cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project("Raven")

#-------------------------------------------------------------------------------------------------------------------------------------------------------
# RAVEN定义 (常量，只能通过修改CMakeLists.txt文件改变)
#-------------------------------------------------------------------------------------------------------------------------------------------------------

#设置你的工程的名字（在visual studio里面，solution名字）
set(RAVENCM_DEF_PROJECTNAME                     "raven")

#设置你工程里面所要加入的文件扩展名，脚本将用这个列表判断哪些文件需要处理
set(RAVENCM_DEF_SOURCEEXTS                      "*.cpp" "*.h" "*.c")

# 设置 C 和 C++ 标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#-------------------------------------------------------------------------------------------------------------------------------------------------------
# RAVEN用户设置参数
#-------------------------------------------------------------------------------------------------------------------------------------------------------

# 模块缺省情况下是否编译成动态库还是静态库
set(RAVENCM_USER_MODULETYPE "DYNAMIC_MODULE" CACHE STRING "MODULE AS SHARE LIB OR STATIC LIB")
set_property(CACHE RAVENCM_USER_MODULETYPE PROPERTY STRINGS "STATIC_MODULE" "DYNAMIC_MODULE")

# 是否禁止生成 zero check 工程
set(RAVENCM_USER_DISABLEZEROCHECK 1 CACHE BOOL "DISABLE ZERO CHECK PROJECT OR NOT")
set_property(CACHE RAVENCM_USER_DISABLEZEROCHECK PROPERTY STRINGS "0" "1")

if(${RAVENCM_USER_MODULETYPE} STREQUAL "STATIC_MODULE")
    set(BUILD_SHARED_LIBS FALSE)
elseif(${RAVENCM_USER_MODULETYPE} STREQUAL "DYNAMIC_MODULE")
    set(BUILD_SHARED_LIBS TRUE)
else()
    message("The module type is not supported.")
endif()

#-------------------------------------------------------------------------------------------------------------------------------------------------------
# RAVEN全局变量
#-------------------------------------------------------------------------------------------------------------------------------------------------------

set(RAVENCM_GLOBAL_DISABLEZEROCHECK             ${RAVENCM_USER_DISABLEZEROCHECK})
set(RAVENCM_GLOBAL_DEFINES                      "-DUNICODE" "-D_UNICODE")
set(RAVENCM_GLOBAL_INCLUDEDIRS                  "./")
set(RAVENCM_GLOBAL_LIBRARYDIRS                  "./")
set(RAVENCM_GLOBAL_MODULETYPE                   "RAVENCFG_E_${RAVENCM_USER_MODULETYPE}")

set(CMAKE_SUPPRESS_REGENERATION                 ${RAVEN_USER_DISABLEZEROCHECK})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG        "${CMAKE_BINARY_DIR}/bin")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE      "${CMAKE_BINARY_DIR}/bin")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG        "${CMAKE_BINARY_DIR}/lib")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE      "${CMAKE_BINARY_DIR}/lib")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG        "${CMAKE_BINARY_DIR}/lib")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE      "${CMAKE_BINARY_DIR}/lib")

mark_as_advanced(CMAKE_SUPPRESS_REGENERATION)
mark_as_advanced(BUILD_SHARED_LIBS)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

find_package(Vulkan)

set(RAVENCM_GLOBAL_INCLUDEDIRS 
"${CMAKE_BINARY_DIR}"
"${CMAKE_SOURCE_DIR}"
"${Vulkan_INCLUDE_DIR}"
"${CMAKE_SOURCE_DIR}/raven/"
"${CMAKE_SOURCE_DIR}/external/"
"${CMAKE_SOURCE_DIR}/external/assimp/include"
"${CMAKE_SOURCE_DIR}/external/eigen"
"${CMAKE_SOURCE_DIR}/external/glfw/include"
"${CMAKE_SOURCE_DIR}/external/ImGuizmo"
"${CMAKE_SOURCE_DIR}/external/stb"
"${CMAKE_SOURCE_DIR}/external/VMA/include"
)

#-------------------------------------------------------------------------------------------------------------------------------------------------------
# 链接外部库
#-------------------------------------------------------------------------------------------------------------------------------------------------------

if (NOT EMSCRIPTEN)
    add_subdirectory(external/glfw)
    set_property(TARGET glfw PROPERTY FOLDER "external/GLFW3")
    set_property(TARGET uninstall PROPERTY FOLDER "external/GLFW3")
    set_property(TARGET update_mappings PROPERTY FOLDER "external/GLFW3")
endif()

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
add_subdirectory(external/assimp)
set_property(TARGET assimp PROPERTY FOLDER "external/assimp")
set_property(TARGET unit PROPERTY FOLDER "external/assimp")
set_property(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTY FOLDER "external/assimp")
set_property(TARGET zlibstatic PROPERTY FOLDER "external/assimp")

add_subdirectory(external/boost)

mark_as_advanced(FORCE ASSIMP_ANDROID_JNIIOSYSTEM)
mark_as_advanced(FORCE ASSIMP_ARCHIVE_OUTPUT_DIRECTORY)
mark_as_advanced(FORCE ASSIMP_ASAN)
mark_as_advanced(FORCE ASSIMP_BIN_INSTALL_DIR)
mark_as_advanced(FORCE ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT)
mark_as_advanced(FORCE ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT)
mark_as_advanced(FORCE ASSIMP_BUILD_ASSIMP_TOOLS)
mark_as_advanced(FORCE ASSIMP_BUILD_DOCS)
mark_as_advanced(FORCE ASSIMP_BUILD_DRACO)
mark_as_advanced(FORCE ASSIMP_BUILD_FRAMEWORK)
mark_as_advanced(FORCE ASSIMP_BUILD_NONFREE_C4D_IMPORTER)
mark_as_advanced(FORCE ASSIMP_BUILD_SAMPLES)
mark_as_advanced(FORCE ASSIMP_BUILD_TESTS)
mark_as_advanced(FORCE ASSIMP_BUILD_ZLIB)
mark_as_advanced(FORCE ASSIMP_COVERALLS)
mark_as_advanced(FORCE ASSIMP_DOUBLE_PRECISION)
mark_as_advanced(FORCE ASSIMP_HEADERCHECK)
mark_as_advanced(FORCE ASSIMP_HUNTER_ENABLED)
mark_as_advanced(FORCE ASSIMP_IGNORE_GIT_HASH)
mark_as_advanced(FORCE ASSIMP_INCLUDE_INSTALL_DIR)
mark_as_advanced(FORCE ASSIMP_INJECT_DEBUG_POSTFIX)
mark_as_advanced(FORCE ASSIMP_INSTALL)
mark_as_advanced(FORCE ASSIMP_INSTALL_PDB)
mark_as_advanced(FORCE ASSIMP_LIBRARY_OUTPUT_DIRECTORY)
mark_as_advanced(FORCE ASSIMP_LIBRARY_SUFFIX)
mark_as_advanced(FORCE ASSIMP_LIB_INSTALL_DIR)
mark_as_advanced(FORCE ASSIMP_NO_EXPORT)
mark_as_advanced(FORCE ASSIMP_OPT_BUILD_PACKAGES)
mark_as_advanced(FORCE ASSIMP_PACKAGE_VERSION)
mark_as_advanced(FORCE ASSIMP_RAPIDJSON_NO_MEMBER_ITERATOR)
mark_as_advanced(FORCE ASSIMP_RUNTIME_OUTPUT_DIRECTORY)
mark_as_advanced(FORCE ASSIMP_UBSAN)
mark_as_advanced(FORCE ASSIMP_WARNINGS_AS_ERRORS)
mark_as_advanced(FORCE LIBRARY_SUFFIX)
mark_as_advanced(FORCE USE_MSVC_RUNTIME_LIBRARY_DLL)
mark_as_advanced(FORCE USE_STATIC_CRT)

mark_as_advanced(FORCE GLFW_BUILD_DOCS)
mark_as_advanced(FORCE GLFW_BUILD_EXAMPLES)
mark_as_advanced(FORCE GLFW_BUILD_TESTS)
mark_as_advanced(FORCE GLFW_BUILD_WIN32)
mark_as_advanced(FORCE GLFW_INSTALL)
mark_as_advanced(FORCE GLFW_LIBRARY_TYPE)
mark_as_advanced(FORCE GLFW_USE_HYBRID_HPG)


#-------------------------------------------------------------------------------------------------------------------------------------------------------
# 设置配置文件
#-------------------------------------------------------------------------------------------------------------------------------------------------------
configure_file( "${CMAKE_SOURCE_DIR}/configuration_project.h.in"
                "${CMAKE_BINARY_DIR}/configuration_${RAVENCM_DEF_PROJECTNAME}.h")

#-------------------------------------------------------------------------------------------------------------------------------------------------------
# RAVRN MODULE 参数
#-------------------------------------------------------------------------------------------------------------------------------------------------------
set(RAVENCM_MOD_NAME                             "YOUR MODULE NAME")
set(RAVENCM_MOD_PATH                             "")
set(RAVENCM_MOD_INCLUDEDIRS                      "ADDITIONAL INCLUDE DIRS")
set(RAVENCM_MOD_LIBRARYDIRS                      "ADDITIONAL LIBRARY DIRS")
set(RAVENCM_MOD_LIBRARIES                        "LINKED LIBRARIES")
set(RAVENCM_MOD_DEPENDMODULES                    "DEPEND MODULES")
set(RAVENCM_MOD_DEFINES                          "")
# 0: 库文件，根据通用设置来决定生成动态库还是静态库
# 1: 普通的命令行可执行程序
# 2: 强制生成动态库文件
# 3: 强制生成静态库文件
set(RAVENCM_MOD_MODULEMODE                       "0:library  1:exe  2:dynamic lib 3:static lib")
set(RAVENCM_MOD_ISGUIAPPLICATION                 0)
set(RAVENCM_MOD_ISFRAMEWORK                      0)
set(RAVENCM_MOD_BUNDLE_NAME                      "")
set(RAVENCM_MOD_BUNDLE_ID                        "")
set(RAVENCM_MOD_BUNDLE_VERSION                   "0.1")
set(RAVENCM_MOD_BUNDLE_SHORTVER                  "0.1")
set(RAVENCM_MOD_BUNDLE_LONGVER                   "0.1.0.0")
set(RAVENCM_MOD_BUNDLE_ICON                      "")
set(RAVENCM_MOD_FRAMEWORK_ID                     "")
set(RAVENCM_MOD_FRAMEWORK_MAJORVER               "")
set(RAVENCM_MOD_FRAMEWORK_CURRENTVER             "")
set(RAVENCM_MOD_FRAMEWORK_COMPATIBLEVER          "")
set(RAVENCM_MOD_FRAMEWORK_BUNDLEVER              "")
set(RAVENCM_MOD_FRAMEWORK_PUBHEADER              "")
set(RAVENCM_MOD_FRAMEWORK_ICON                   "")
set(RAVENCM_MOD_USERPATHINSTALLNAME              "1")

#-------------------------------------------------------------------------------------------------------------------------------------------------------
# RAVEN MODULE 参数
#-------------------------------------------------------------------------------------------------------------------------------------------------------
set(RAVENCM_MOD_NAME                            "core")
set(RAVENCM_MOD_PATH                            "raven/")
set(RAVENCM_MOD_MODULEMODE                      "0")
set(RAVENCM_MOD_ISGUIAPPLICATION                "0")
set(RAVENCM_MOD_BUNDLE_NAME                     "core")
set(RAVENCM_MOD_BUNDLE_ID                       "raven.core")
set(RAVENCM_MOD_FRAMEWORK_ID                    "raven.core")
set(RAVENCM_MOD_FRAMEWORK_PUBHEADER             "core.h")
set(RAVENCM_MOD_INCLUDEDIRS                     "")
set(RAVENCM_MOD_LIBRARYDIRS                     "")
set(RAVENCM_MOD_LIBRARIES                       "")
set(RAVENCM_MOD_DEPENDMODULES                   "")
set(RAVENCM_MOD_DEFINES                         "")
set(RAVENCM_MOD_PLUGINS                         "")

add_subdirectory(${RAVENCM_MOD_PATH}${RAVENCM_MOD_NAME})
install( 
    TARGETS ${RAVENCM_MOD_NAME} 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    FRAMEWORK DESTINATION framework
    BUNDLE DESTINATION app
)

set(RAVENCM_MOD_NAME                            "vkdrv")
set(RAVENCM_MOD_PATH                            "raven/")
set(RAVENCM_MOD_MODULEMODE                      "0")
set(RAVENCM_MOD_ISGUIAPPLICATION                "0")
set(RAVENCM_MOD_BUNDLE_NAME                     "vkdrv")
set(RAVENCM_MOD_BUNDLE_ID                       "raven.vkdrv")
set(RAVENCM_MOD_FRAMEWORK_ID                    "raven.vkdrv")
set(RAVENCM_MOD_FRAMEWORK_PUBHEADER             "vkdrv.h")
set(RAVENCM_MOD_INCLUDEDIRS                     "")
set(RAVENCM_MOD_LIBRARYDIRS                     "")
set(RAVENCM_MOD_LIBRARIES                       "")
set(RAVENCM_MOD_DEPENDMODULES                   "core")
set(RAVENCM_MOD_DEFINES                         "")
set(RAVENCM_MOD_PLUGINS                         "")

add_subdirectory(${RAVENCM_MOD_PATH}${RAVENCM_MOD_NAME})
install( 
    TARGETS ${RAVENCM_MOD_NAME} 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    FRAMEWORK DESTINATION framework-
    BUNDLE DESTINATION app
)

set(RAVENCM_MOD_NAME                            "framework")
set(RAVENCM_MOD_PATH                            "raven/")
set(RAVENCM_MOD_MODULEMODE                      "1")
set(RAVENCM_MOD_ISGUIAPPLICATION                "1")
set(RAVENCM_MOD_BUNDLE_NAME                     "framework")
set(RAVENCM_MOD_BUNDLE_ID                       "raven.framework")
set(RAVENCM_MOD_FRAMEWORK_ID                    "raven.framework")
set(RAVENCM_MOD_FRAMEWORK_PUBHEADER             "framework.h")
set(RAVENCM_MOD_INCLUDEDIRS                     "")
set(RAVENCM_MOD_LIBRARYDIRS                     "")
set(RAVENCM_MOD_LIBRARIES                       "")
set(RAVENCM_MOD_DEPENDMODULES                   "core" "vkcore")
set(RAVENCM_MOD_DEFINES                         "")
set(RAVENCM_MOD_PLUGINS                         "")

add_subdirectory(${RAVENCM_MOD_PATH}${RAVENCM_MOD_NAME})
install( 
    TARGETS ${RAVENCM_MOD_NAME} 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    FRAMEWORK DESTINATION framework
    BUNDLE DESTINATION app
)