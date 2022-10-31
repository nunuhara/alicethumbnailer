AliceThumbnailer
================

AliceThumbnailer is a plugin for KDE5 that creates thumbnails for various
AliceSoft image formats. It supports the AJP, DCF, PMS and QNT formats.

Build and install
-----------------

    mkdir build
    cd build
    cmake -DKDE_INSTALL_USE_QT_SYS_PATHS=ON -DCMAKE_INSTALL_PREFIX=`kf5-config --prefix` -DCMAKE_BUILD_TYPE=Release ..
    make
    sudo make install
    kbuildsycoca5

You can then restart Dolphin and enable the plugin in `Configure Dolphin`>`General`>`Previews`.
