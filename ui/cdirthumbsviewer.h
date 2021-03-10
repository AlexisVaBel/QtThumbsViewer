#ifndef CDIRTHUMBSVIEWER_H
#define CDIRTHUMBSVIEWER_H

#include <QDialog>
#include <QFileSystemModel>
#include <QIdentityProxyModel>
#include <QListView>
#include <QStyledItemDelegate>
#include <QTreeView>



class CDirThumbsViewer: public QDialog
{
    Q_OBJECT
public:
    explicit CDirThumbsViewer(QWidget *prnt = nullptr);
    ~CDirThumbsViewer();

public slots:
    void on_tree_item_clicked(QModelIndex idx);
    void on_all_files_loaded(QString path);
    void change_size(int value);


private:
    QTreeView           *m_dirsTree;
    QListView           *m_filesList;

    QFileSystemModel    *m_dirsModel;
    QFileSystemModel    *m_filesModel;
    QIdentityProxyModel *m_proxy;



    QStyledItemDelegate *m_iconDelegate;

    QSize m_sizeIcons;    

    //  setup operations
    void prepare_ui();
    void prepare_model();
    void prepare_sig_slots();

    void set_models();
    void correct_ui();
    // ~setup operations

    void apply_size();
    void before_close();


    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);

    // QDialog interface
public slots:
    void accept();
    void reject();
};


#endif // CDIRTHUMBSVIEWER_H
