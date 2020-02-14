
Import('env')
env = env.Clone()

cflags = '-I myutil/inc'

env.Append(CCFLAGS=[Split(cflags)])

src_list = Glob('src/*.c')

lib = env.StaticLibrary(target='myutil', source=src_list)
Return('lib')
