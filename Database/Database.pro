TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Field.cpp \
        Logical.cpp \
        Parser.cpp \
        RPN.cpp \
        Record.cpp \
        Records.cpp \
        Relational.cpp \
        STokenizer.cpp \
        ShuntingYard.cpp \
        StrToken.cpp \
        Table_functions.cpp \
        Token.cpp \
        Value.cpp \
        main.cpp

HEADERS += \
    Array_Utility.h \
    B+Tree.h \
    ConditionalToken.h \
    Field.h \
    IteratedLists.h \
    LParenthesis.h \
    Logical.h \
    Map.h \
    MultiMap.h \
    Node.h \
    Operator.h \
    Parser.h \
    Queue.h \
    RPN.h \
    RParenthesis.h \
    Record.h \
    Records.h \
    Relational.h \
    SQL.h \
    STokenizer.h \
    ShuntingYard.h \
    Stack.h \
    StrToken.h \
    Table.h \
    Table_functions.h \
    Token.h \
    TokenTypes.h \
    Value.h \
    z_output.h \
    z_work_report.h
