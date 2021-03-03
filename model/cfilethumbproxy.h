#ifndef CFILETHUMBPROXY_H
#define CFILETHUMBPROXY_H

#include <QIdentityProxyModel>
#include <QMap>
#include <QMutex>
#include <QThreadPool>



class CFileThumbProxy:public QIdentityProxyModel {
    Q_OBJECT
signals:
    void pixmap_loaded(const QString &path, QPixmap *pix, const QPersistentModelIndex& index);
public slots:
    void on_loaded_pixmap(const QString &path, QPixmap *pix, const QPersistentModelIndex& index);



public:
    CFileThumbProxy(QObject * parent = nullptr);
    ~CFileThumbProxy();

    // QAbstractItemModel interface

    QVariant data(const QModelIndex &index, int role) const;


private:

    QMap<QString,QPixmap*>    m_cache;
    QThreadPool              *m_pool;
    QString                   m_strPath;
//    QMutex                   *mutex;
    void load_empty_pixmap(const QString &path) const;
    void reset_data(QString str) const;
};

#endif // CFILETHUMBPROXY_H
