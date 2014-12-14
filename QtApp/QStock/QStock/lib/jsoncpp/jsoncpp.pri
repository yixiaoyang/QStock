SOURCES += \
    $$PWD/json_internalarray.inl \
    $$PWD/json_internalmap.inl \
    $$PWD/json_reader.cpp \
    $$PWD/json_value.cpp \
    $$PWD/json_valueiterator.inl \
    $$PWD/json_writer.cpp 
DEPENDPATH += $$PWD/..
HEADERS += \
    $$PWD/json_batchallocator.h \
    $$PWD/json/autolink.h \
    $$PWD/json/config.h \
    $$PWD/json/features.h \
    $$PWD/json/forwards.h \
    $$PWD/json/json.h \
    $$PWD/json/reader.h \
    $$PWD/json/value.h \
    $$PWD/json/writer.h

INCLUDEPATH += "$$PWD"
