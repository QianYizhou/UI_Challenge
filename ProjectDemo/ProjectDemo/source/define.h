#ifndef DEFINE_H
#define DEFINE_H

#define Q_OS_LINUX_MY

#define BLOCK_INIT_POS_X    -1000
#define BLOCK_INIT_POS_Y    -1000
#define BLOCK_END_DIS       100
enum MODULELIB{
    MODULELIB_CONTROLER = 1,//执行模块库
    MODULELIB_SENSOR = 2,//传感器模块库
    MODULELIB_COMMAND = 3,
    MODULELIB_VAR = 4,
};

enum BLOCKID_C{
    BLOCK_START = 0,
    BLOCK_END,

    BLOCK_IF,
    BLOCK_IF_END,
    BLOCK_WHILE,
    BLOCK_WHILE_END,
    BLOCK_FOR,
    BLOCK_FOR_END,
    BLOCK_BREAK,
    BLOCK_CONTINUE,
    BLOCK_RETURN,

    BLOCK_MOVE,           //移动
    BLOCK_GRAB,           //抓取
    BLOCK_POSITIONEXAMINE,           //位置检测

};

enum VARIABLE_C{
    //变量
    VAR_POSITIONEXAMINE = 0,         //位置检测

    VAR_SELF=10000,//自定义变量
    VAR_KNOWN=10001,//10001是已知量列表
};

extern QString g_nChartVersion;

#endif // DEFINE_H

