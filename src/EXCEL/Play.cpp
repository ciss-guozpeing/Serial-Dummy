#include "Play.h"

using namespace EXCEL;
static Play *INSTANCE = nullptr;

Play::Play()
{

}

Play *Play::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new Play;
    }
    return INSTANCE;
}
