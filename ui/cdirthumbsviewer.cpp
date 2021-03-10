#include "cdirthumbsviewer.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QFileIconProvider>


#include "view/cfileicondelegate.h"
#include "view/ciconlistview.h"

#include "model/cfilethumbproxy.h"



CDirThumbsViewer::CDirThumbsViewer(QWidget *prnt):QDialog(prnt),m_sizeIcons(200,200)
{    
    prepare_model();
    prepare_ui();
    set_models();

    prepare_sig_slots();    

    correct_ui();

    setMinimumSize(640,480);
}

CDirThumbsViewer::~CDirThumbsViewer()
{

}


void CDirThumbsViewer::prepare_ui()
{
    QHBoxLayout *ltMain = new QHBoxLayout();
    setLayout(ltMain);


    m_dirsTree = new QTreeView(this);
    m_dirsTree->header()->hide();    


    ltMain->addWidget(m_dirsTree, 1);
    ltMain->addSpacing(10);


    m_filesList     = new CIconListView(this);
    m_iconDelegate  = new CFileIconDelegate(m_filesList);


    m_filesList->setViewMode(QListView::IconMode);
    m_filesList->setResizeMode(QListView::Adjust);
    m_filesList->setMovement(QListView::Static);
    m_filesList->setGridSize(QSize(m_sizeIcons.width()+10,m_sizeIcons.height()+10));


    m_filesList->setItemDelegate(m_iconDelegate);
    ltMain->addWidget(m_filesList, 2);
}

void CDirThumbsViewer::prepare_model()
{
    m_dirsModel = new QFileSystemModel();
    m_dirsModel->setRootPath(QDir::rootPath());
    m_dirsModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);


    m_filesModel = new QFileSystemModel();
    m_filesModel->setFilter(QDir::NoDotAndDotDot | QDir::Files );

    QStringList filters;
    filters << "*.jpeg" << "*.jpg" << "*.png" << "*.tiff" << "*.bmp";

    m_filesModel->setNameFilters(filters);
    m_filesModel->setNameFilterDisables(false);

    m_proxy = new CFileThumbProxy();
    m_proxy->setSourceModel(m_filesModel);
}

void CDirThumbsViewer::correct_ui()
{
    m_dirsTree->hideColumn(1);
    m_dirsTree->hideColumn(2);
    m_dirsTree->hideColumn(3);
}


void CDirThumbsViewer::prepare_sig_slots()
{    
    connect(m_dirsTree,  &QTreeView::clicked, this, &CDirThumbsViewer::on_tree_item_clicked);
    connect(m_dirsTree,  &QTreeView::doubleClicked, this, &CDirThumbsViewer::on_tree_item_clicked);
    connect(m_dirsTree,  &QTreeView::activated, this, &CDirThumbsViewer::on_tree_item_clicked);


    // not to use casting, using SIGNAL - SLOTS
    connect(m_filesList, SIGNAL(wheel_move(int)), this, SLOT(change_size(int)));
//    connect(m_filesModel, &QFileSystemModel::directoryLoaded, this, &CDirThumbsViewer::on_all_files_loaded);
}

void CDirThumbsViewer::set_models()
{
    m_dirsTree->setModel(m_dirsModel);
    m_filesList->setModel(m_proxy);
    apply_size();
}


void CDirThumbsViewer::apply_size()
{
    static CFileIconDelegate *icon_delegate = nullptr;
    //remove expensive cast operation
    if(icon_delegate == nullptr){
        icon_delegate = qobject_cast<CFileIconDelegate*> (m_iconDelegate);
    }

    icon_delegate->set_new_size(m_sizeIcons);
    m_filesList->setGridSize(QSize(m_sizeIcons.width()+10,m_sizeIcons.height()+10));
}

void CDirThumbsViewer::before_close()
{
    auto proxy = qobject_cast<CFileThumbProxy*> (m_proxy);
    proxy->stop();
}

void CDirThumbsViewer::closeEvent(QCloseEvent *event)
{
    before_close();
}

void CDirThumbsViewer::accept()
{

}

void CDirThumbsViewer::reject()
{

}


void CDirThumbsViewer::on_tree_item_clicked(QModelIndex idx)
{
    QString strPath         = m_dirsModel->fileInfo(idx).absoluteFilePath();

    QModelIndex actualIndex = m_filesModel->setRootPath(strPath);
    QModelIndex mappedIndex = m_proxy->mapFromSource(actualIndex);

    m_filesList->setRootIndex(mappedIndex);
}

void CDirThumbsViewer::on_all_files_loaded(QString path)
{

}

void CDirThumbsViewer::change_size(int value)
{
    int w = m_sizeIcons.width()+value;

    if(w >= 50 && w <= 200){
        m_sizeIcons.setWidth(w);
        m_sizeIcons.setHeight(w);
        apply_size();
    }
}
