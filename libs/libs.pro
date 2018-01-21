TEMPLATE = subdirs

SUBDIRS += \
    busclient \
    ipc

busclient.depends = ipc

