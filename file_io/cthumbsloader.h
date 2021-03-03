#ifndef CTHUMBSLOADER_H
#define CTHUMBSLOADER_H

#include <QPixmap>
#include <QRunnable>
#include <qabstractitemmodel.h>



class CThumbsLoader: public QRunnable
{    
public:
    explicit CThumbsLoader(QString strPath, QPersistentModelIndex pIndex);
    ~CThumbsLoader(){
        m_pix = nullptr;
    }

    QPixmap *get_pixmap(){return m_pix; }
    void    run();


private:
    QPixmap *m_pix;
    QString m_strPath;
    QPersistentModelIndex m_pIndex;
};

#endif // CTHUMBSLOADER_H
