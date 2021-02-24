#include <QApplication>

#include "ui/cdirthumbsviewer.h"

// Qt versions: 5.5(Windows); 5.12.5(Linux Mint)
// about 20-30 minutes to read task, load example and start it
// coding and task solving:
// 3 hours 30 minutes for application (previos time not included)
// at this point are done:
//      view directories on left
//      view images content on right
//      loading pixmaps in async
// not done:
//           memchecking
//           progressbar
//           cache cleaning in proxy
//
// tested on Linux Mint, windows xp (virtual machine)

int main(int argc,char **argv){
    QApplication app(argc, argv);

    CDirThumbsViewer *view = new CDirThumbsViewer();
    view->show();

    auto result = app.exec();

    delete view;
    return result;
}
