BUILDDATE=`date +%F`

rm -Rf zip_output_tmp
mkdir -p zip_output_tmp

#  tcl/tk 8.6
if [[ $SV_SUPER_OPTIONS == *BUILD_TCL* ]]; then
  echo "BUILD_TCL"
  REPLACEME_TAR -C zip_output_tmp/ -xvzf tar_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_TCLTK_DIR-BUILD${BUILDDATE}.tar.gz
  pushd zip_output_tmp
  REPLACEME_ZIP -r ../zip_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_TCLTK_DIR-BUILD${BUILDDATE}.zip REPLACEME_SV_TCLTK_DIR
  popd
fi

rm -Rf zip_output_tmp
mkdir -p zip_output_tmp

# python 2.7
if [[ $SV_SUPER_OPTIONS == *BUILD_PYTHON* ]]; then
  echo "BUILD_PYTHON"
  REPLACEME_TAR -C zip_output_tmp/ -xvzf tar_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_PYTHON_DIR-BUILD${BUILDDATE}.tar.gz
  pushd zip_output_tmp
  REPLACEME_ZIP -r ../zip_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_PYTHON_DIR-BUILD${BUILDDATE}.zip REPLACEME_SV_PYTHON_DIR
  popd
fi

rm -Rf zip_output_tmp
mkdir -p zip_output_tmp

# numpy
# NOTE: numpy is contained in the python zip

# freetype
if [[ $SV_SUPER_OPTIONS == *BUILD_FREETYPE* ]]; then
  echo "BUILD_FREETYPE"
  REPLACEME_TAR -C zip_output_tmp/ -xvzf tar_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_FREETYPE_DIR-BUILD${BUILDDATE}.tar.gz
  pushd zip_output_tmp
  REPLACEME_ZIP -r ../zip_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_FREETYPE_DIR-BUILD${BUILDDATE}.zip REPLACEME_SV_FREETYPE_DIR
  popd
fi

rm -Rf zip_output_tmp
mkdir -p zip_output_tmp

# gdcm
if [[ $SV_SUPER_OPTIONS == *BUILD_GDCM* ]]; then
  echo "BUILD_GDCM"
  REPLACEME_TAR -C zip_output_tmp/ -xvzf tar_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_GDCM_DIR-BUILD${BUILDDATE}.tar.gz
  pushd zip_output_tmp
  REPLACEME_ZIP -r ../zip_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_GDCM_DIR-BUILD${BUILDDATE}.zip REPLACEME_SV_GDCM_DIR
  popd
fi

rm -Rf zip_output_tmp
mkdir -p zip_output_tmp

# vtk
if [[ $SV_SUPER_OPTIONS == *BUILD_VTK* ]]; then
  echo "BUILD_VTK"
  REPLACEME_TAR -C zip_output_tmp/ -xvzf tar_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_VTK_DIR-BUILD${BUILDDATE}.tar.gz
  pushd zip_output_tmp
  REPLACEME_ZIP -r ../zip_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_VTK_DIR-BUILD${BUILDDATE}.zip REPLACEME_SV_VTK_DIR
  popd
fi

rm -Rf zip_output_tmp
mkdir -p zip_output_tmp

# itk
if [[ $SV_SUPER_OPTIONS == *BUILD_ITK* ]]; then
  echo "BUILD_ITK"
  REPLACEME_TAR -C zip_output_tmp/ -xvzf tar_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_ITK_DIR-BUILD${BUILDDATE}.tar.gz
  pushd zip_output_tmp
  REPLACEME_ZIP -r ../zip_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_ITK_DIR-BUILD${BUILDDATE}.zip REPLACEME_SV_ITK_DIR
  popd
fi

rm -Rf zip_output_tmp
mkdir -p zip_output_tmp

# opencascade
if [[ $SV_SUPER_OPTIONS == *BUILD_OPENCASCADE* ]]; then
  echo "BUILD_OPENCASCADE"
  REPLACEME_TAR -C zip_output_tmp/ -xvzf tar_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_OPENCASCADE_DIR-BUILD${BUILDDATE}.tar.gz
  pushd zip_output_tmp
  REPLACEME_ZIP -r ../zip_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_OPENCASCADE_DIR-BUILD${BUILDDATE}.zip REPLACEME_SV_OPENCASCADE_DIR
  popd
fi

rm -Rf zip_output_tmp
mkdir -p zip_output_tmp

# mmg
if [[ $SV_SUPER_OPTIONS == *BUILD_MMG* ]]; then
  echo "BUILD_MMG"
  REPLACEME_TAR -C zip_output_tmp/ -xvzf tar_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_MMG_DIR-BUILD${BUILDDATE}.tar.gz
  pushd zip_output_tmp
  REPLACEME_ZIP -r ../zip_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_MMG_DIR-BUILD${BUILDDATE}.zip REPLACEME_SV_MMG_DIR
  popd
fi

rm -Rf zip_output_tmp
mkdir -p zip_output_tmp

# mitk
if [[ $SV_SUPER_OPTIONS == *BUILD_MITK* ]]; then
  echo "BUILD_MITK"
  REPLACEME_TAR -C zip_output_tmp/ -xvzf tar_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_MITK_DIR-BUILD${BUILDDATE}.tar.gz
  pushd zip_output_tmp
  REPLACEME_ZIP -r ../zip_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.REPLACEME_SV_MITK_DIR-BUILD${BUILDDATE}.zip REPLACEME_SV_MITK_DIR
  popd
fi

rm -Rf zip_output_tmp
mkdir -p zip_output_tmp

# everything
if [[ $SV_SUPER_OPTIONS == *ZIP_EVERYTHING* ]]; then
  echo "TAR_EVERYTHING"
  REPLACEME_TAR -C zip_output_tmp/ -xvzf tar_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.everything-BUILD${BUILDDATE}.tar.gz
  pushd zip_output_tmp
  REPLACEME_ZIP -r ../zip_output/REPLACEME_SV_PLATFORM.REPLACEME_SV_COMPILER_BIN_DIR.REPLACEME_SV_ARCH_DIR.everything-BUILD${BUILDDATE}.zip \
    REPLACEME_SV_TCLTK_DIR \
    REPLACEME_SV_PYTHON_DIR \
    REPLACEME_SV_FREETYPE_DIR \
    REPLACEME_SV_GDCM_DIR \
    REPLACEME_SV_VTK_DIR \
    REPLACEME_SV_ITK_DIR \
    REPLACEME_SV_OPENCASCADE_DIR \
    REPLACEME_SV_MMG_DIR \
    REPLACEME_SV_MITK_DIR \
  popd
fi

rm -Rf zip_output_tmp
