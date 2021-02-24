#ifndef CDIRDELEGATE_H
#define CDIRDELEGATE_H

#include <QFileInfo>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QFileSystemModel>


class CFileIconDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:

    explicit CFileIconDelegate(QObject *parent = nullptr): QStyledItemDelegate(parent){
        m_size = QSize(50,50);
    }

    virtual ~CFileIconDelegate() = default;

    CFileIconDelegate(const CFileIconDelegate&) = delete;
    CFileIconDelegate& operator=(const CFileIconDelegate&) = delete;

    void set_new_size(QSize sz){
        m_size = sz;
    }

protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
    {
        if(!index.isValid()) return;


        QVariant v = index.data(QFileSystemModel::FileIconRole);

        QPixmap pix = v.value<QPixmap>();

        if(pix.data_ptr() == nullptr || pix.size() == QSize(0,0)){
            return;
        }

        pix = pix.scaled(m_size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        int x = (m_size.width() - pix.width())/2;
        int y = (m_size.height() - pix.height())/2;

        painter->drawRect(option.rect.x(), option.rect.y(), m_size.width(), m_size.height());
        painter->drawPixmap(option.rect.x()+x ,option.rect.y()+y ,pix);
    }



    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
    {
        QVariant v = index.data(QFileSystemModel::FileIconRole);
        QPixmap img = v.value<QPixmap>();
        if(img.data_ptr() == nullptr){
            return option.rect.size();
        }
        return m_size;
    }

private:
    QSize m_size;
};

#endif // CDIRDELEGATE_H
