#!/usr/bin/bash
rm *~
rm /#*

rm client/CMakeCache.txt
rm client/cmake_install.cmake
rm -r client/CMakeFiles

rm client/*~
rm server/*~
rm client/#*
rm server/#*

rm client/headers/*~
rm server/headers/*~
rm client/headers/#*
rm server/headers/#*

rm client/sources/#*
rm server/sources/#*
rm client/sources/*~
rm server/sources/*~

rm client/sfml-app
rm server/sfml-app

rm server/sources/*.d
rm server/sources/*.o
rm server/*.d
rm server/*.o
