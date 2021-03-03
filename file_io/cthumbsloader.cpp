#include "cthumbsloader.h"

#include <QPersistentModelIndex>

CThumbsLoader::CThumbsLoader(QString strPath, QPersistentModelIndex pIndex):m_strPath(strPath), m_pIndex(pIndex)
{
    m_pix = nullptr;
}

void CThumbsLoader::run()
{
    m_pix = new QPixmap();
    m_pix->load(m_strPath);
}
