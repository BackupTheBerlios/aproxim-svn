# ???? ?????? ? KDevelop ?????????? qmake.
# ------------------------------------------- 
# ?????????? ???????????? ???????? ???????? ???????: ./src
# ???? - ??????????:  ../bin/aproxim

FORMS += form1.ui \
         options.ui 
IMAGES += images/about.png \
          images/blue_next.png \
          images/quit.png \
          images/right_arrow.png \
          images/settings_button.png \
          images/stock_form-table-control.png \
          images/stock_open.png \
          images/stock_save.png \
          images/diff.png \
          images/integral.png \
          images/excel.png 
IDLS += form1.ui \
        options.ui 
HEADERS += form1.ui.h \
           options.ui.h \
           util.h \
           approximator_2.h \
           approximator.h \
           functions.h \
           dataanalysis.h \
           xls_table.h 
SOURCES += main.cpp \
           util.cpp \
           approximator_2.cpp \
           approximator.cpp \
           functions.cpp \
           dataanalysis.cpp \
           xls_table.cpp 
TARGET = ../bin/aproxim
TEMPLATE = app
LANGUAGE = C++
CONFIG += debug warn_on thread qt
LIBS += -lqwt
INCLUDEPATH += /usr/include/qwt
