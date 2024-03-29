import os, sys, re
sys.path.append('../../framework') 
import bldutil

# Put your name programs in progs variable 
# without 'M' preffix and '.c' extension
progs = '''
crepefandstack crestack cretrajec getcregather getcretimecurve rnip2vrms getcreandstack rnip2vnmo parsmoother
'''

try:  # distributed version
    Import('env root pkgdir bindir')
    env = env.Clone()
except: # local version
    env = bldutil.Debug()
    cflags = env.get('CFLAGS','')
    if isinstance (cflags, str):
        env['CFLAGS'] = cflags.replace('-O3','-g').replace('-xHOST','')
    env.Prepend(CPPDEFINES=['DEBUG'])
    root = None
    SConscript('../../api/c/SConstruct')

# Check if the TDD option is set
if ARGUMENTS.get('tdd',0):
	print("TDD option is set...")
	## Set a c flag to compilation process
	## the flag -Wp,-DTDD=1 informs to the preprocessor that TDD=1
	env['CFLAGS'] = '-Wp,-DTDD=1'

if sys.platform.startswith('linux'):
    env.Prepend(CPPDEFINES=['LINUX'])

src = Glob('[a-z]*.c')

sse = None
#sse = env.get('SSE')
CC = env.get('CC')
if CC.rfind('icc') >= 0:
    env.Append(CCFLAGS=['-restrict','-wd188'])
threads = env.get('PTHREADS')
if threads:
    env.Prepend(CPPDEFINES=['PTHREADS'])

if sse:
    env.Prepend(CPPPATH=['../../include'],
                LIBPATH=['../../lib'],
                LIBS=[env.get('DYNLIB','')+'rsf'],
                CCFLAGS=[sse],CPPDEFINES=['HAVE_SSE'])
else:
    env.Prepend(CPPPATH=['../../include'],
                LIBPATH=['../../lib'],
                LIBS=[env.get('DYNLIB','')+'rsf'])

if env['PLATFORM'] == 'darwin':
    # bug in Mac's gcc handling of OpenMP
    env.Append(CPPDEFINES=['_FORTIFY_SOURCE=0'],CCFLAGS='-O1')

for source in src:
    if source.rstr() == 'einspline.c':
        einspl_o = env.StaticObject('einspline.c')
        env.Depends(einspl_o,'einspline.h')
    else:
        inc = env.RSF_Include(source,prefix='')
        obj = env.StaticObject(source)
        env.Ignore(inc,inc)
        env.Depends(obj,inc)

# Regular progams
mains = Split(progs)
for prog in mains:
    sources = ['M' + prog]
    bldutil.depends(env,sources,'M'+prog)
    prog = env.Program(prog,[x + '.c' for x in sources])
    if root:
        env.Install(bindir,prog)

######################################################################
# SELF-DOCUMENTATION
######################################################################
if root:
    user = os.path.basename(os.getcwd())
    main = 'sf%s.py' % user

    docs = [env.Doc(prog,'M' + prog) for prog in mains]
    env.Depends(docs,'#/framework/rsf/doc.py')

    doc = env.RSF_Docmerge(main,docs)
    env.Install(pkgdir,doc)
