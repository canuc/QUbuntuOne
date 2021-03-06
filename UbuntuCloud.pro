# Add more folders to ship with the application, here
folder_qml.source = qml/UbuntuCloud
folder_qml.target = qml
DEPLOYMENTFOLDERS = folder_qml

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE75557A8

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices
QT+=testlib
# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
CONFIG += qdeclarative-boostable

DEFINES += KQOAUTH

# Add dependency to Symbian components
# CONFIG += qt-components



SOURCES += src/main.cpp \
    src/net/networkmanager.cpp \
    src/net/requests/ubuntuonerequest.cpp \
    src/qjson/serializerrunnable.cpp \
    src/qjson/serializer.cpp \
    src/qjson/qobjecthelper.cpp \
    src/qjson/parserrunnable.cpp \
    src/qjson/parser.cpp \
    src/qjson/json_scanner.cpp \
    src/qjson/json_parser.cc \
    src/net/exception/qexception.cpp \
    src/net/exception/invalidrequesttype.cpp \
    src/net/requests/cookiepersistantubuntuonerequest.cpp \
    src/test/requesttest.cpp \
    src/test/testwrangler.cpp \
    src/kqoauth/kqoauthmanager.cpp \
    src/kqoauth/kqoauthrequest.cpp \
    src/kqoauth/kqoauthutils.cpp \
    src/kqoauth/kqoauthauthreplyserver.cpp \
    src/kqoauth/kqoauthrequest_1.cpp \
    src/kqoauth/kqoauthrequest_xauth.cpp \
    src/net/requests/jsonubuntuonerequest.cpp \
    src/test/testoauth.cpp \
    src/net/requests/auth/ubuntuoneoauthrequest.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog

HEADERS += \
    src/net/networkmanager.h \
    src/net/requests/ubuntuonerequest.h \
    src/qjson/stack.hh \
    src/qjson/serializerrunnable.h \
    src/qjson/serializer.h \
    src/qjson/qobjecthelper.h \
    src/qjson/qjson_export.h \
    src/qjson/qjson_debug.h \
    src/qjson/position.hh \
    src/qjson/parserrunnable.h \
    src/qjson/parser_p.h \
    src/qjson/parser.h \
    src/qjson/location.hh \
    src/qjson/json_scanner.h \
    src/qjson/json_parser.hh \
    src/net/exception/qexception.h \
    src/net/exception/invalidrequesttype.h \
    src/net/requests/cookiepersistantubuntuonerequest.h \
    src/test/requesttest.h \
    src/test/testwrangler.h \
    src/test/test.h \
    src/kqoauth/kqoauthmanager.h \
    src/kqoauth/kqoauthrequest.h \
    src/kqoauth/kqoauthrequest_1.h \
    src/kqoauth/kqoauthrequest_xauth.h \
    src/kqoauth/kqoauthglobals.h \
    src/kqoauth/kqoauthrequest_p.h \
    src/kqoauth/kqoauthmanager_p.h \
    src/kqoauth/kqoauthauthreplyserver.h \
    src/kqoauth/kqoauthauthreplyserver_p.h \
    src/kqoauth/kqoauthutils.h \
    src/kqoauth/kqoauthrequest_xauth_p.h \
    src/net/requests/jsonubuntuonerequest.h \
    src/net/macros.h \
    src/test/testoauth.h \
    src/net/requests/auth/ubuntuoneoauthrequest.h
