AR = 'arm-none-eabi-ar'
ARFLAGS = 'rcs'
AS = 'arm-none-eabi-gcc'
BINDIR = '/usr/local/bin'
BUILD_DIR = 'aplite'
CC = ['arm-none-eabi-gcc']
CCLNK_SRC_F = []
CCLNK_TGT_F = ['-o']
CC_NAME = 'gcc'
CC_SRC_F = []
CC_TGT_F = ['-c', '-o']
CC_VERSION = ('4', '7', '2')
CFLAGS = ['-std=c99', '-mcpu=cortex-m3', '-mthumb', '-ffunction-sections', '-fdata-sections', '-g', '-Os', '-Wall', '-Wextra', '-Werror', '-Wno-unused-parameter', '-Wno-error=unused-function', '-Wno-error=unused-variable']
CFLAGS_MACBUNDLE = ['-fPIC']
CFLAGS_cshlib = ['-fPIC']
CPPPATH_ST = '-I%s'
DEFINES = ['RELEASE', 'PBL_PLATFORM_APLITE', 'PBL_BW', 'PBL_SDK_2']
DEFINES_ST = '-D%s'
DEST_BINFMT = 'elf'
DEST_CPU = 'arm'
DEST_OS = 'darwin'
INCLUDES = ['aplite']
LD = 'arm-none-eabi-ld'
LIBDIR = '/usr/local/lib'
LIBPATH_ST = '-L%s'
LIB_ST = '-l%s'
LINKFLAGS = ['-mcpu=cortex-m3', '-mthumb', '-Wl,--gc-sections', '-Wl,--warn-common', '-Os']
LINKFLAGS_MACBUNDLE = ['-bundle', '-undefined', 'dynamic_lookup']
LINKFLAGS_cshlib = ['-shared']
LINKFLAGS_cstlib = ['-Wl,-Bstatic']
LINK_CC = ['arm-none-eabi-gcc']
PBW_BIN_DIR = ''
PEBBLE_SDK = '/Users/Kristen/pebble-dev/PebbleSDK-3.3/Pebble/aplite'
PEBBLE_SDK_COMMON = '/Users/Kristen/pebble-dev/PebbleSDK-3.3/Pebble/common'
PLATFORM = {'PBW_BIN_DIR': '', 'ADDITIONAL_TEXT_LINES_FOR_PEBBLE_H': [], 'MAX_APP_BINARY_SIZE': 65536, 'MAX_RESOURCES_SIZE': 524288, 'MAX_APP_MEMORY_SIZE': 24576, 'MAX_WORKER_MEMORY_SIZE': 10240, 'NAME': 'aplite', 'BUILD_DIR': 'aplite', 'MAX_RESOURCES_SIZE_APPSTORE_2_X': 98304, 'MAX_RESOURCES_SIZE_APPSTORE': 128000, 'DEFINES': ['PBL_PLATFORM_APLITE', 'PBL_BW']}
PLATFORM_NAME = 'aplite'
PREFIX = '/usr/local'
RPATH_ST = '-Wl,-rpath,%s'
SDK_VERSION_MAJOR = 5
SDK_VERSION_MINOR = 19
SHLIB_MARKER = None
SIZE = 'arm-none-eabi-size'
SONAME_ST = '-Wl,-h,%s'
STLIBPATH_ST = '-L%s'
STLIB_MARKER = None
STLIB_ST = '-l%s'
TARGET_PLATFORMS = [u'basalt', u'aplite']
cprogram_PATTERN = '%s'
cshlib_PATTERN = 'lib%s.so'
cstlib_PATTERN = 'lib%s.a'
macbundle_PATTERN = '%s.bundle'
