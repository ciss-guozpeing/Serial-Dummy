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

QString Play::openExcel()
{
    // Get file name
    auto file = QFileDialog::getOpenFileName(Q_NULLPTR, tr("Select xlsx file"),
                QDir::homePath(),
                tr("Excel files") + " (*.xlsx)");
    // Open CSV file
    if (!file.isEmpty()) {
        return file;
    } else {
        return NULL;
    }
}
