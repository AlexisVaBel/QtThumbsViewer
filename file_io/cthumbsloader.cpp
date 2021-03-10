#include "cthumbsloader.h"
#include <thread>
#include <chrono>
#include <QPersistentModelIndex>

CThumbsLoader::CThumbsLoader(QObject *parent):QObject(parent){
    m_pix   = nullptr;
    m_bWork = true;
}

void CThumbsLoader::run(){       
    while (m_bWork) {
        if(m_tasks.empty()) std::this_thread::sleep_for(std::chrono::microseconds(200));
        else{
            {
                std::lock_guard<std::mutex> guard(m_mutex);
                m_strPath = m_tasks.front().second;
                m_pIndex  = m_tasks.front().first;
                m_tasks.pop();
            }
            m_pix = new QPixmap();
            m_pix->load(m_strPath);
            emit on_loaded_img(m_strPath, m_pix, m_pIndex);
        }

    }
}

void CThumbsLoader::add_task(QString strPath, QPersistentModelIndex pIndex)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    m_tasks.push(std::make_pair(pIndex,strPath));
}

void CThumbsLoader::clear_tasks()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    while (!m_tasks.empty()) {
        m_tasks.pop();
    }
}

void CThumbsLoader::stop()
{
    m_bWork = false;
}
