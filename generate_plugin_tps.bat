mkdir build_tps
cd build_tps

REM on veut que les extensions sortent dans le dossier "Extensions" à côté de l'éditeur
SET OUTPUT_DIR=C:Users\Lloyd\Documents\Shine\ShGameEditor\Extensions\

REM on cherche le dossier Include et Lib fournit dans le zip "SDK"
SET SHINE_DIR=C:\Users\Lloyd\Documents\Shine\ShSDK

REM génération du project Visual Studio
cmake -G "Visual Studio 10 2010" -DSH_ROOT_DIR=%SHINE_DIR% -DCMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG=%OUTPUT_DIR% -DCMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE=%OUTPUT_DIR% ../plugin-tps
