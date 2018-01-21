TARGET = $${PROJECT_NAME}$${TARGET}

QT += quick

DESTDIR = ../../out

SOURCES += \
    src/main.cpp \

QML_FILES += \
    qml/Cluster.qml \
    qml/ClusterLayout.qml \
    qml/main.qml

GFX_FILES += \
    gfx/board_texture.svg \
    gfx/dial_texture.svg \
    gfx/dial.svg \
    gfx/signal_left.svg \
    gfx/signal_right.svg

FONT_FILES += \
    fonts/DSEG14Classic-Regular.ttf

OTHER_FILES += \
    $$FONT_FILES \
    $$GFX_FILES \
    $$QML_FILES \
    translations/*.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

LANGUAGES = en fi

# var, prepend, append
defineReplace(prependAll) {
    for(a,$$1):result += $$2$${a}$$3
    return($$result)
}

TRANSLATIONS = $$prependAll(LANGUAGES, $$PWD/translations/$${TARGET}_, .ts)

# Bulid translations on qmake
TRANSLATIONS_FILES =
qtPrepareTool(LRELEASE, lrelease)
for(tsfile, TRANSLATIONS) {
    qmfile = $$shadowed($$tsfile)
    qmfile ~= s,.ts$,.qm,
    qmdir = $$dirname(qmfile)
    !exists($$qmdir) {
        mkpath($$qmdir)|error("Aborting.")
    }
    command = $$LRELEASE -idbased $$tsfile -qm $$qmfile
    system($$command)|error("Failed to run: $$command")
    TRANSLATIONS_FILES += $$qmfile
}

# Create the resource file
GENERATED_RESOURCE_FILE = $$OUT_PWD/$${TARGET}.qrc

RESOURCE_FILES += \
    $$FONT_FILES \
    $$GFX_FILES \
    $$QML_FILES

RESOURCE_CONTENT = \
    "<RCC>" \
    "<qresource>"

for(resourcefile, RESOURCE_FILES) {
    resourcefileabsolutepath = $$absolute_path($$resourcefile)
    relativepath_in = $$relative_path($$resourcefileabsolutepath, $$_PRO_FILE_PWD_)
    relativepath_out = $$relative_path($$resourcefileabsolutepath, $$OUT_PWD)
    RESOURCE_CONTENT += "<file alias=\"$$relativepath_in\">$$relativepath_out</file>"
}

for(translationfile, TRANSLATIONS_FILES) {
    relativepath_out = $$relative_path($$translationfile, $$OUT_PWD)
    RESOURCE_CONTENT += "<file alias=\"$$relativepath_out\">$$relativepath_out</file>"
}

RESOURCE_CONTENT += \
    "</qresource>" \
    "</RCC>"

write_file($$GENERATED_RESOURCE_FILE, RESOURCE_CONTENT)|error("Aborting.")

RESOURCES += $$GENERATED_RESOURCE_FILE

wd = $$replace(PWD, /, $$QMAKE_DIR_SEP)

# Update translation source file ("C")
qtPrepareTool(LUPDATE, lupdate)
LUPDATE += -locations none -no-ui-lines
TSFILES = $$PWD/translations/$${TARGET}_C.ts # $$files($$PWD/translations/$${TARGET}_*.ts)
for(file, TSFILES) {
    lang = $$replace(file, .*_([^/]*)\\.ts, \\1)

    ts-$${lang}.CONFIG = no_link target_predeps
    ts-$${lang}.commands = cd $$wd && $$LUPDATE $$SOURCES $$QML_FILES -ts $$file
    ts-$${lang}.input = SOURCES QML_FILES
    ts-$${lang}.output = $$file

    QMAKE_EXTRA_COMPILERS += ts-$${lang}
}

# Default rules for deployment.
#qnx: target.path = /tmp/$${PROJECT_NAME}/bin
#else: unix:!android: target.path = /opt/$${PROJECT_NAME}/bin
#!isEmpty(target.path): INSTALLS += target

