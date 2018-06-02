#include "blockbuilder.h"

#include "positionexamine.h"
#include "move.h"
#include "grab.h"
#include "block_if.h"
#include "block_for.h"
#include "block_while.h"
#include "setbreak_c.h"
#include "setcontinue_c.h"
#include "setreturn_c.h"
BlockBuilder::BlockBuilder(QGraphicsView *p_pProjectView, QObject *parent)
    : QObject(parent)
    , m_pProjectView(p_pProjectView)
{

}

BlockBuilder::~BlockBuilder()
{

}

BaseBlock* BlockBuilder::create(int p_ID, int p_PosX, int p_PosY, float p_Zoom)
{
    BaseBlock* p_pBlock = NULL;

    switch(p_ID){
    //执行器模块库 ------------------------------------------------------------------
    case BLOCK_MOVE:
        p_pBlock = new Move(":/res/images/block/main_modul1.png", BLOCK_MOVE, MODULELIB_CONTROLER);
        p_pBlock->SetInit(":/Command/res/images/block/Command/icon_if.png",tr("Move"),m_pProjectView,p_PosX,p_PosY,p_Zoom);
        break;
    case BLOCK_GRAB:
        p_pBlock = new Grab(":/res/images/block/main_modul1.png", BLOCK_GRAB, MODULELIB_CONTROLER);
        p_pBlock->SetInit(":/Command/res/images/block/Command/icon_if.png",tr("Grab"),m_pProjectView,p_PosX,p_PosY,p_Zoom);
        break;
    case BLOCK_POSITIONEXAMINE:
        p_pBlock = new PositionExamine(":/res/images/block/main_modul2.png", BLOCK_POSITIONEXAMINE, MODULELIB_SENSOR);
        p_pBlock->SetInit(":/Command/res/images/block/Command/icon_if.png",tr("PositionExamine"),m_pProjectView,p_PosX,p_PosY,p_Zoom);
        break;

    //控制语句模块库 ------------------------------------------------------------------
    case BLOCK_IF:
        p_pBlock = new Block_If(":/res/images/block/main_modul3.png",MODULELIB_COMMAND);
        p_pBlock->SetInit(":/Command/res/images/block/Command/icon_if.png",tr("if"),m_pProjectView,p_PosX,p_PosY,p_Zoom);
        break;
    case BLOCK_WHILE:
        p_pBlock = new Block_While(":/res/images/block/forwhile.png",MODULELIB_COMMAND);
        p_pBlock->SetInit(":/Command/res/images/block/Command/icon_while.png",tr("while"),m_pProjectView,p_PosX,p_PosY,p_Zoom);
        break;
    case BLOCK_FOR:
        p_pBlock = new Block_For(":/res/images/block/forwhile.png",MODULELIB_COMMAND);
        p_pBlock->SetInit(":/Command/res/images/block/Command/icon_for.png",tr("for"),m_pProjectView,p_PosX,p_PosY,p_Zoom);
        break;
    case BLOCK_BREAK:
        p_pBlock = new SetBreak_C(":/res/images/block/main_modul3_2.png",BLOCK_BREAK,MODULELIB_COMMAND);
        p_pBlock->SetInit(":/Command/res/images/block/Command/icon_break.png",tr("Break"),m_pProjectView,p_PosX,p_PosY,p_Zoom);
        break;
    case BLOCK_CONTINUE:
        p_pBlock = new SetContinue_C(":/res/images/block/main_modul3_2.png",BLOCK_CONTINUE,MODULELIB_COMMAND);
        p_pBlock->SetInit(":/Command/res/images/block/Command/icon_continue.png",tr("Continue"),m_pProjectView,p_PosX,p_PosY,p_Zoom);
        break;
    case BLOCK_RETURN:
        p_pBlock = new SetReturn_C(":/res/images/block/main_modul3_2.png",BLOCK_RETURN,MODULELIB_COMMAND);
        p_pBlock->SetInit(":/Command/res/images/block/Command/icon_return.png",tr("Return"),m_pProjectView,p_PosX,p_PosY,p_Zoom);
        break;
    default:
        break;
    }

    return p_pBlock;
}

