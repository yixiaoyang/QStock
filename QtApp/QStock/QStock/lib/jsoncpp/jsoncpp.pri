SOURCES += \
    $$PWD/json_internalarray.inl \
    $$PWD/json_internalmap.inl \
    $$PWD/json_valueiterator.inl \
    $$PWD/json_reader.cpp \
    $$PWD/json_value.cpp \
    $$PWD/json_writer.cpp
DEPENDPATH += $$PWD/..
HEADERS += \
    $$PWD/json_batchallocator.h \
    $$PWD/json/*.h \
    $$PWD/json_tool.h \
    $$PWD/version.h
INCLUDEPATH += "$$PWD"
