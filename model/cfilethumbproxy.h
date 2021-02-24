#ifndef CFILETHUMBPROXY_H
#define CFILETHUMBPROXY_H

#include <QIdentityProxyModel>
#include <QMap>
#include <QThreadPool>



class CFileThumbProxy:public QIdentityProxyModel {
    Q_OBJECT
signals:
    void pixmap_loaded(const QString &path, QPixmap *pix, const QPersistentModelIndex& index);
public slots:
    void on_loaded_pixmap(const QString &path, QPixmap *pix, const QPersistentModelIndex& index);



public:
    CFileThumbProxy(QObject * parent = nullptr);

    // QAbstractItemModel interface

    QVariant data(const QModelIndex &index, int role) const;


private:
    QMap<QString,QPixmap*>    m_cache;
    QThreadPool              *m_pool;
    void load_empty_pixmap(const QString &path) const;

};

#endif // CFILETHUMBPROXY_H
