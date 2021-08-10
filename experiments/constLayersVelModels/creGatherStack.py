from rsf.proj import *

def creStack(parametersCube,
            dataCube,
            interpolatedDataCube,
            stackedSection,
            nm0,
            om0,
            dm0,
            nt0,
            ot0,
            dt0,
            v0,
            repeat,
            aperture
            ):
    '''

    '''
    Flow(parametersCube,dataCube,
            '''
            vfsacrsnh nm0=%d om0=%g dm0=%g nt0=%d ot0=%g dt0=%g v0=%g repeat=%d
            '''%(nm0,om0,dm0,nt0,ot0,dt0,v0,repeat))

    Flow('creTrajectories',[interpolatedDataCube,parametersCube],
            '''
            cretrajec param=${SOURCES[1]} nm0=%d om0=%g dm0=%g nt0=%d ot0=%g dt0=%g verb=y 
            '''%(nm0,om0,dm0,nt0,ot0,dt0))

    Flow(['cregathers','mhCoordinates'],[interpolatedDataCube,'creTrajectories'],
            '''
            getcregather cremh=${SOURCES[1]} m=${TARGETS[1]} aperture=%d nm0=%g nt0=%g |
            put label1=Time unit1=s label2=Offset unit2=Km label3=t0 unit3=s
            label4=m0 unit4=Km n3=%d d3=%g o3=%g n4=%d d4=%g o4=%g
            ''' % (aperture,nm0,nt0,nt0,dt0,ot0,nm0,dm0,om0))

    Flow('cretimecurves',['mhCoordinates',parametersCube],
            '''
            getcretimecurve param=${SOURCES[1]} nm0=%d om0=%g dm0=%g nt0=%d ot0=%g dt0=%g verb=y v0=%g |
            put label1=Offset unit1=Km label2=t0 unit2=s label3=m0 unit3=Km
            n2=%d d2=%g o2=%g n3=%d d3=%g o3=%g
            '''%(nm0,om0,dm0,nt0,ot0,dt0,v0,nt0,dt0,ot0,nm0,dm0,om0))

    Flow(stackedSection,['cregathers','cretimecurves'],
            '''
            crestack aperture=%d verb=y timeCurves=${SOURCES[1]} |
            put label1=t0 unit1=s label2=m0 unit2=Km
            ''' %(aperture))

