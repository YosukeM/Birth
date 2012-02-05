QMAKE_CC = gcc-mp-4.6
QMAKE_CXX = g++-mp-4.6
QMAKE_LINK = g++-mp-4.6
QMAKE_CXXFLAGS += \
	-std=c++0x\
	-Wno-unused-parameter

CONFIG -= qt
CONFIG += precompile_header

DEFINES += USING_PCH

PRECOMPILED_HEADER = global.h

INCLUDEPATH += \
	/opt/local/include\
	/usr/local/include\
	/Users/yosuke/Projects/GameAudio/include

LIBS += \
	/usr/local/lib/libglfw.a\
	/opt/local/lib/libglew.a\
	/opt/local/lib/libogg.a\
	/opt/local/lib/libvorbis.a\
	/opt/local/lib/libvorbisfile.a\
	/opt/local/lib/libboost_system-mt.a\
	/opt/local/lib/libboost_filesystem-mt.a\
	/opt/local/lib/libboost_thread-mt.a\
	/Users/yosuke/Projects/GameAudio/bin/Debug/libGameAudio.a\
	-framework OpenGL\
	-framework OpenAL\
	-framework Cocoa

SOURCES += \
    TitleSequence.cpp \
    TgaTextureLoader.cpp \
    Sequence.cpp \
    rscTexture.cpp \
    rscSyncManager.cpp \
    rscShader.cpp \
    rscResource.cpp \
    rscProgram.cpp \
    rscMesh.cpp \
    rscASyncManager.cpp \
    Random.cpp \
    Quaternion.cpp \
    oglTexture.cpp \
    oglShader.cpp \
    oglProgram.cpp \
    oglPerspectiveCamera.cpp \
    oglMaterial.cpp \
    oglLight.cpp \
    oglFramebuffer.cpp \
    ObjMeshLoader.cpp \
    Matrix4d.cpp \
    main.cpp \
    inputMouse.cpp \
    inputManager.cpp \
    IFileReader.cpp \
    guiText.cpp \
    guiRectangle.cpp \
    guiPositionalElement.cpp \
    guiImageButton.cpp \
    guiImage.cpp \
    guiBackground.cpp \
    gameSubordinate.cpp \
    gameStatus.cpp \
    gameSpermatozoa.cpp \
    GameSequence.cpp \
    gameScene.cpp \
    gamePlayer.cpp \
    gameOvum.cpp \
    gameNode.cpp \
    gameMitochondria.cpp \
    gameIndicator.cpp \
    gameGeomTail.cpp \
    gameGeomParticle.cpp \
    FileReader.cpp \
    FileFactory.cpp \
    Error.cpp \
    DescriptionSequence.cpp \
    Color.cpp \
    Application.cpp \
    Angle2d.cpp


HEADERS += \
    Vertex3d.h \
    Vector3d.h \
    Vector2d.h \
    TitleSequence.h \
    TgaTextureLoader.h \
    Sequence.h \
    rscTexture.h \
    rscSyncManager.h \
    rscShader.h \
    rscResource.h \
    rscProgram.h \
    rscMesh.h \
    rscIManager.h \
    rscASyncManager.h \
    Random.h \
    Quaternion.h \
    oglTexture.h \
    oglShader.h \
    oglProgram.h \
    oglPerspectiveCamera.h \
    oglMeshbuffer.h \
    oglMaterial.h \
    oglLinkError.h \
    oglLight.h \
    oglFramebuffer.h \
    oglCompileError.h \
    ObjMeshLoader.h \
    Matrix4d.h \
    ITextureLoader.h \
    inputMouse.h \
    inputManager.h \
    IMeshLoader.h \
    IFileReader.h \
    IFileFactory.h \
    guiText.h \
    guiRectangle.h \
    guiPositionalElement.h \
    guiImageButton.h \
    guiImage.h \
    guiElement.h \
    guiBackground.h \
    global.h \
    GetterSetter.h \
    gameSubordinate.h \
    gameStatus.h \
    gameSpermatozoa.h \
    GameSequence.h \
    gameScene6.h \
    gameScene5.h \
    gameScene4.h \
    gameScene3.h \
    gameScene2.h \
    gameScene1.h \
    gameScene.h \
    gamePlayer.h \
    gameOvum.h \
    gameNode.h \
    gameMitochondria.h \
    gameIndicator.h \
    gameGeomTail.h \
    gameGeomParticle.h \
    FileReader.h \
    FileFactory.h \
    Error.h \
    DescriptionSequence.h \
    core.h \
    Color.h \
    Application.h \
    Angle2d.h
