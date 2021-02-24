#include "cfilethumbproxy.h"

#include <QFileSystemModel>
#include <QtConcurrent>

namespace CFileThumb{
QPixmap *get_pixmap(const QString & path){
    QPixmap *pm = new QPixmap();
    pm->load(path);
    return pm;
}
}

CFileThumbProxy::CFileThumbProxy(QObject *parent):QIdentityProxyModel(parent),m_pool(new QThreadPool(this))
{
    m_pool->setMaxThreadCount(2);
    connect(this, &CFileThumbProxy::pixmap_loaded, this, &CFileThumbProxy::on_loaded_pixmap);
}

QVariant CFileThumbProxy::data(const QModelIndex &index, int role) const
{
    if (role == QFileSystemModel::FileIconRole) {

        auto path = index.data(QFileSystemModel::FilePathRole).toString();

        auto it = m_cache.find(path);
        if(it != m_cache.end()){
            return *it.value();
        }

        load_empty_pixmap(path);

        QPersistentModelIndex pIndex{index};
        QtConcurrent::run(m_pool, [this,path,pIndex]{
            emit const_cast<CFileThumbProxy*>(this)->pixmap_loaded(path, CFileThumb::get_pixmap(path), pIndex);
        });
        return QVariant{};
    }
    return QIdentityProxyModel::data(index, role);
}

void CFileThumbProxy::load_empty_pixmap(const QString &path) const
{
    const_cast<CFileThumbProxy*>(this)->m_cache.insert(path, nullptr);
}



void CFileThumbProxy::on_loaded_pixmap(const QString &path, QPixmap *pix, const QPersistentModelIndex &index)
{
    m_cache.insert(path, pix);
    emit dataChanged(index, index, QVector<int>{QFileSystemModel::FileIconRole});
}
