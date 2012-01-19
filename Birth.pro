QMAKE_CC = gcc-mp-4.6
QMAKE_CXX = g++-mp-4.6
QMAKE_LINK = g++-mp-4.6
QMAKE_CXXFLAGS += \
	-std=c++0x\
	-Wno-unused-parameter

CONFIG -= qt
CONFIG += debug precompile_header

DEFINES += _DEBUG USING_PCH

PRECOMPILED_HEADER = global.h

INCLUDEPATH += \
	/opt/local/include\
	/usr/local/include

LIBS += \
	/usr/local/lib/libglfw.a\
	/opt/local/lib/libglew.a\
	/opt/local/lib/libboost_system-mt.a\
	/opt/local/lib/libboost_filesystem-mt.a\
	/opt/local/lib/libboost_thread-mt.a\
	-framework OpenGL\
	-framework Cocoa

SOURCES += \
	main.cpp \
    Framebuffer.cpp \
    Texture.cpp \
    Shader.cpp \
    Error.cpp \
    Program.cpp \
    Application.cpp \
    Color.cpp \
    FileReader.cpp \
    Mesh.cpp \
    Resource.cpp \
    IFileReader.cpp \
	ObjMeshLoader.cpp \
    ASyncResourceManager.cpp \
    SyncResourceManager.cpp

HEADERS += \
    global.h \
    Framebuffer.h \
    Texture.h \
    Vector2d.h \
    Shader.h \
    Error.h \
    Program.h \
    CompileError.h \
    LinkError.h \
    Vector3d.h \
    Application.h \
    Vertex3d.h \
    Color.h \
    Meshbuffer.h \
    IFileReader.h \
    IFileFactory.h \
    FileReader.h \
    FileFactory.h \
    Mesh.h \
    Resource.h \
	ObjMeshLoader.h \
    IMeshLoader.h \
    IResourceManager.h \
    core.h \
    ASyncResourceManager.h \
    SyncResourceManager.h
