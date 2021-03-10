#include "cfilethumbproxy.h"

#include <QDebug>
#include <QFileSystemModel>



namespace CFileThumb{
QPixmap *get_pixmap(const QString & path){
    QPixmap *pm = new QPixmap();
    pm->load(path);
    return pm;
}
}

CFileThumbProxy::CFileThumbProxy(QObject *parent):QIdentityProxyModel(parent)
{
    m_strPath = "";

    m_loader = new CThumbsLoader(this);
    m_loader->setAutoDelete(false);
    QThreadPool::globalInstance()->start(m_loader);
    connect(m_loader, &CThumbsLoader::on_loaded_img, this, &CFileThumbProxy::on_loaded_pixmap);
}

CFileThumbProxy::~CFileThumbProxy()
{
    stop();
    m_loader->deleteLater();
}

QVariant CFileThumbProxy::data(const QModelIndex &index, int role) const
{

    if (role == QFileSystemModel::FileIconRole) {


        auto path = index.data(QFileSystemModel::FilePathRole).toString();
        auto dirpath = path.left(path.lastIndexOf("/"));
        if(m_strPath.compare(dirpath,Qt::CaseInsensitive) != 0){
            reset_data(dirpath);
        }

        auto it = m_cache.find(path);
        if(it != m_cache.end()){
            return *it.value();
        }


        load_empty_pixmap(path);
        QPersistentModelIndex pIndex{index};

        m_loader->add_task(path, pIndex);


        return QVariant{};
    }
    return QIdentityProxyModel::data(index, role);
}

void CFileThumbProxy::stop()
{
    m_loader->clear_tasks();
    m_loader->stop();
}

void CFileThumbProxy::load_empty_pixmap(const QString &path) const
{
    const_cast<CFileThumbProxy*>(this)->m_cache.insert(path, nullptr);
}


void CFileThumbProxy::reset_data(QString str="") const
{
//    qDeleteAll( m_cache );
    m_loader->clear_tasks();
    const_cast<CFileThumbProxy*>(this)->m_strPath = str;
    const_cast<CFileThumbProxy*>(this)->m_cache.clear();
}



void CFileThumbProxy::on_loaded_pixmap(const QString &path, QPixmap *pix, const QPersistentModelIndex &index)
{
    m_cache.insert(path, pix);
    emit dataChanged(index, index, QVector<int>{QFileSystemModel::FileIconRole});
}
