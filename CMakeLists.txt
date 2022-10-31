project(AliceThumbnailer LANGUAGES C CXX)

cmake_minimum_required(VERSION 3.16.0)

set(QT_MIN_VERSION "5.15.0")
set(KF5_MIN_VERSION "5.78.0")
set(KDE_COMPILERSETTINGS_LEVEL "5.78")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

find_package(Qt${QT_MAJOR_VERSION} ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Gui)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS KIO)
find_package(ZLIB)

find_library(turbojpeg libturbojpeg)
find_library(png libpng)
find_library(webp libwebp)

include_directories(libsys4/include)

add_library(alicethumbnailer MODULE
    libsys4/src/archive.c
    libsys4/src/buffer.c
    libsys4/src/cg.c
    libsys4/src/file.c
    libsys4/src/string.c
    libsys4/src/system.c
    libsys4/src/utfsjis.c
    libsys4/src/ajp.c
    libsys4/src/dcf.c
    libsys4/src/jpeg.c
    libsys4/src/pms.c
    libsys4/src/png.c
    libsys4/src/qnt.c
    libsys4/src/webp.c
    alicethumbnailer.cpp)

target_link_libraries(alicethumbnailer PRIVATE turbojpeg png webp ZLIB::ZLIB KF5::KIOWidgets Qt::Gui)

install(TARGETS alicethumbnailer DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES alicethumbnailer.desktop DESTINATION ${KDE_INSTALL_KSERVICESDIR})
