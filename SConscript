
Import('env')
env = env.Clone()

cflags = '--cpu Cortex-M4.fp -D__MICROLIB --apcs=interwork --split_sections \
    -I myutil/inc \
    -I C:/Keil_v5/ARM/RV31/INC \
    -I C:/Keil_v5/ARM/CMSIS/Include \
    -D__UVISION_VERSION="518"'

env.Append(CCFLAGS=[Split(cflags)])

src_list = Glob('src/*.c')

lib = env.StaticLibrary(target='myutil', source=src_list)
Return('lib')