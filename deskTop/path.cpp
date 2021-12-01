#include "path.h"

path::path()
{
    m_count = 0;
}

path::~path()
{
}

int path::load()
{
    // 解析xml
    TiXmlDocument xml_doc;
    if (!xml_doc.LoadFile("path.xml"))
    {
        return -1;
    }


    // 根节点
    TiXmlElement* xml_root = xml_doc.RootElement();
    if (NULL == xml_root)
    {
        return -1;
    }
    TiXmlElement* xml_infor = xml_root->FirstChildElement("path");
    while (xml_infor)
    {
        m_choosed_path.push_back(QString(xml_infor->GetText()));
        m_count++;
        xml_infor = xml_infor->NextSiblingElement("path");
    }
    return 0;
}

int path::save()
{

    TiXmlDocument xml_doc; 
    xml_doc.LinkEndChild(new TiXmlDeclaration("1.0", "utf8", ""));
    TiXmlElement * xml_root = new TiXmlElement("root");
    xml_doc.LinkEndChild(xml_root);
    for (auto i:m_choosed_path)
    {
		std::string tmpStr = i.toLocal8Bit().toStdString();
		TiXmlElement *node=new TiXmlElement("path");
		node->LinkEndChild(new TiXmlText(tmpStr.c_str()));
		xml_root->LinkEndChild(node);
    }

    bool savef=xml_doc.SaveFile("path.xml");//所有文件路径存储在xml文档里；
    return 0;
}

void path::addInfor(QString &infor)
{
    m_choosed_path.push_back(infor);
    m_count++;//当前存储数量+1；
}

int path::return_m_count()
{
    return m_count;
}

QVector<QString> &path::return_array()
{
    return m_choosed_path;
}
