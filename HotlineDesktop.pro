QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32: RC_ICONS = $$PWD/Images/supportIcon.ico

SOURCES += \
    Clients/addclientdialog.cpp \
    Clients/addserverdialog.cpp \
    Clients/adminslistform.cpp \
    Clients/clientslistdialog.cpp \
    Clients/clientswindow.cpp \
    Clients/contactdialog.cpp \
    Clients/fbserverform.cpp \
    Clients/firmsdialog.cpp \
    Clients/modelpaytypes.cpp \
    Clients/paytypeform.cpp \
    Clients/pingoutdialog.cpp \
    ConnectionSettingDialog/connectionsettingdialog.cpp \
    DataBase/database.cpp \
    DynamicButton/dynamiicbutton.cpp \
    GlobalSettings/globalsettings.cpp \
    LoggingCategories/loggingcategories.cpp \
    PingModel/pingmodel.cpp \
    TreeModel/treeitem.cpp \
    TreeModel/treemodel.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Clients/addclientdialog.h \
    Clients/addserverdialog.h \
    Clients/adminslistform.h \
    Clients/clientslistdialog.h \
    Clients/clientswindow.h \
    Clients/contactdialog.h \
    Clients/fbserverform.h \
    Clients/firmsdialog.h \
    Clients/modelpaytypes.h \
    Clients/paytypeform.h \
    Clients/pingoutdialog.h \
    ConnectionSettingDialog/connectionsettingdialog.h \
    DataBase/database.h \
    DynamicButton/dynamiicbutton.h \
    GlobalSettings/globalsettings.h \
    LoggingCategories/loggingcategories.h \
    PingModel/pingmodel.h \
    TreeModel/treeitem.h \
    TreeModel/treemodel.h \
    mainwindow.h

FORMS += \
    Clients/addclientdialog.ui \
    Clients/addserverdialog.ui \
    Clients/adminslistform.ui \
    Clients/clientslistdialog.ui \
    Clients/clientswindow.ui \
    Clients/contactdialog.ui \
    Clients/fbserverform.ui \
    Clients/firmsdialog.ui \
    Clients/paytypeform.ui \
    Clients/pingoutdialog.ui \
    ConnectionSettingDialog/connectionsettingdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
