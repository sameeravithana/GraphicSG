#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/NodeVisitor.o \
	${OBJECTDIR}/RenderVisitor.o \
	${OBJECTDIR}/camera.o \
	${OBJECTDIR}/geometry.o \
	${OBJECTDIR}/group.o \
	${OBJECTDIR}/light.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/material.o \
	${OBJECTDIR}/node.o \
	${OBJECTDIR}/reader.o \
	${OBJECTDIR}/scene.o \
	${OBJECTDIR}/sceneroot.o \
	${OBJECTDIR}/state.o \
	${OBJECTDIR}/texture.o \
	${OBJECTDIR}/transform.o \
	${OBJECTDIR}/vertex.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lglut -lGLEW -lGL -lvrlib -lpng -lGLU

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/graphicsg

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/graphicsg: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/graphicsg ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/NodeVisitor.o: NodeVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/NodeVisitor.o NodeVisitor.cpp

${OBJECTDIR}/RenderVisitor.o: RenderVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/RenderVisitor.o RenderVisitor.cpp

${OBJECTDIR}/camera.o: camera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/camera.o camera.cpp

${OBJECTDIR}/geometry.o: geometry.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/geometry.o geometry.cpp

${OBJECTDIR}/group.o: group.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/group.o group.cpp

${OBJECTDIR}/light.o: light.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/light.o light.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/material.o: material.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/material.o material.cpp

${OBJECTDIR}/node.o: node.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/node.o node.cpp

${OBJECTDIR}/reader.o: reader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/reader.o reader.cpp

${OBJECTDIR}/scene.o: scene.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/scene.o scene.cpp

${OBJECTDIR}/sceneroot.o: sceneroot.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/sceneroot.o sceneroot.cpp

${OBJECTDIR}/state.o: state.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/state.o state.cpp

${OBJECTDIR}/texture.o: texture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/texture.o texture.cpp

${OBJECTDIR}/transform.o: transform.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/transform.o transform.cpp

${OBJECTDIR}/vertex.o: vertex.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/vertex.o vertex.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/graphicsg

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
