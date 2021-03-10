#ifndef CTHUMBSLOADER_H
#define CTHUMBSLOADER_H

#include <QPixmap>
#include <QRunnable>
#include <qabstractitemmodel.h>

#include <mutex>
#include <queue>

class CThumbsLoader:public QObject, public QRunnable
{    
    Q_OBJECT
public:
    explicit CThumbsLoader(QObject *parent = nullptr);
    ~CThumbsLoader(){
        m_pix = nullptr;
    }

    QPixmap *get_pixmap(){return m_pix; }
    void    run();

    void add_task(QString strPath, QPersistentModelIndex pIndex);
    void clear_tasks();
    void stop();
signals:
    void on_loaded_img(const QString &path, QPixmap *pix, const QPersistentModelIndex& index);
private:
    QPixmap *m_pix;
    QString m_strPath;
    QPersistentModelIndex m_pIndex;
    bool        m_bWork;

    std::mutex m_mutex;
    std::queue <std::pair<QPersistentModelIndex, QString>> m_tasks;

};

#endif // CTHUMBSLOADER_H
