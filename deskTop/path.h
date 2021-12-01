#ifndef PATH_H
#define PATH_H

#include <QObject>
#include <QString>
#include <QVector>
#include "xml\tinyxml.h" 

class path
{  
public:
    path();
    ~path();
    int load();
    int save();
    void addInfor(QString & infor);
    int return_m_count();
    QVector <QString>& return_array();
private:
    QVector <QString> m_choosed_path;//容器存储所选择的文件路径；
    int m_count;   //当前有几个
};

#endif // PATH_H
