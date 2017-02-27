# If this file exists, we are building inside the SDK source tree
exists($$PWD/../../common.pri):include($$PWD/../../common.pri)
else {
  exists($$(CORNERSTONE_SDK_ROOT)/cornerstone.pri):include($$(CORNERSTONE_SDK_ROOT)/cornerstone.pri)
  else {
    exists($$(CORNERSTONE_ROOT_2_1_0)/cornerstone.pri):include($$(CORNERSTONE_ROOT_2_1_0)/cornerstone.pri)
    else:include(/opt/cornerstone-2.1.0/cornerstone.pri)
  }
}

SOURCES += animatedArrow.cpp
SOURCES += imageDisplayer.cpp
SOURCES += InteractiveBlob.cpp
SOURCES += MenuBubble.cpp
SOURCES += MyntraFluidicEffect.cpp
SOURCES += RelativeMotion.cpp

HEADERS += animatedArrow.hpp
HEADERS += imageDisplayer.hpp
HEADERS += InteractiveBlob.hpp
HEADERS += MenuBubble.hpp
HEADERS += RelativeMotion.hpp



LIBS += $$LIB_PATTERNS
LIBS += $$LIB_NIMBLE
LIBS += $$LIB_RADIANT
LIBS += $$LIB_VALUABLE
LIBS += $$LIB_LUMINOUS
LIBS += $$LIB_RESONANT
LIBS += $$LIB_VIDEODISPLAY
LIBS += $$LIB_MULTITOUCH
LIBS += $$LIB_STYLISH
LIBS += $$LIB_MULTIWIDGETS
LIBS += $$LIB_WEB_BROWSER
LIBS += $$LIB_WEB_BROWSER_CEF
LIBS += $$LIB_OPENGL
LIBS += $$LIB_MULTISTATEDISPLAY
LIBS += $$LIB_SCRIPT
LIBS += $$LIB_MUSHY

win32 {
  LIBS += -llibsndfile-1
  CONFIG += console
}

unix {
  CONFIG += link_pkgconfig
  PKGCONFIG += sndfile
}

# Create install target for the source files
other.path = /examples/$$TARGET
other.files = MyntraFluidicEffect.pro animatedArrow.cpp imageDisplayer.cpp InteractiveBlob.cpp MenuBubble.cpp MyntraFluidicEffect.cpp RelativeMotion.cpp

INSTALLS += other

