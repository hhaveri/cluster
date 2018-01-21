TEMPLATE = subdirs

SUBDIRS += \
    apps \
    libs \
    services \
    tools

apps.depends = libs
services.depends = libs

OTHER_FILES += \
    .gitignore \
    .qmake.conf \
    LICENSE \
    README.md

