#include "excel2ts.h"
#include <QDomElement>
excel2ts::excel2ts()
{

}

QAxObject * excel2ts::getWrokSheet(QString absuExcelPath){
    excel=new QAxObject();
    excel->setControl("Excel.Application");
    excel->dynamicCall("SetVisible(bool Visible)","false");
    excel->setProperty("DisplayAlerts",false);
    QAxObject *workbooks = excel->querySubObject("WorkBooks");
    //absuExcelPath need to use the absuote path.
    qDebug() << "getWorkSheet: " + absuExcelPath;
    workbook = workbooks->querySubObject("Open(const QString&)",absuExcelPath);
    QAxObject * worksheets = workbook->querySubObject("WorkSheets");
    int iWorkSheet = worksheets->property("Count").toInt();
    qDebug() << QString("the number of the worksheet of the excel: %1").arg(QString::number(iWorkSheet));
    s_worksheet = worksheets->querySubObject("Item(int)", 1);//get first worksheet.
    return s_worksheet;
}

bool excel2ts::operateXml(){
    QString dirpath = "../modifyTsBaseExcel/language";
    QDir directory(dirpath);
    QDir *dir;
    QStringList filter;
    QList<QFileInfo> *fileinfo;
    int count;
    QString letter;
    int postionNum;
    QString ts_file_path;
    if(directory.exists()==false){
        printf("the target directory is not correct.\n");
        return false;
    }
    dir =new QDir(directory);
    filter << "*.ts";
    dir->setNameFilters(filter);
    fileinfo = new QList<QFileInfo>(dir->entryInfoList(filter));
    count = fileinfo->count();
    if(count==0){
        qDebug() << "target ts files are not exist!";
        return false;
    }else{
        qDebug() << QString("the number of ts file is: %1").arg(QString::number(count));
    }

    for(int x =0;x<count;x++){
        ts_file_path = dir->absoluteFilePath(fileinfo->at(x).fileName());
        //open or create file.
        QDomDocument doc;
        QDomElement root;
        QFile file(ts_file_path); //path
        if(!file.open(QFile::ReadOnly|QFile::Text)){ return false; }
        if(!doc.setContent(&file)){ file.close(); return false;}
        file.close();

        root=doc.documentElement(); //get root node
        qDebug()<< "root name:" + root.nodeName();
        qDebug()<< "root lang:" + root.attribute("language");
        if(root.attribute("language")=="en_AS"){
            letter ="A";
            postionNum=2;
        }else if(root.attribute("language")=="zh_CN"){
            letter ="B";
            postionNum=2;
        }else if(root.attribute("language")=="ja_JP"){
            letter ="C";
            postionNum=2;
        }
        QDomNode node=root.firstChild(); //get first child node
        while(!node.isNull()){
            if(node.isElement()){
                QDomElement e=node.toElement();
                QDomNodeList list=e.childNodes();
                for(int i=0;i<list.count();i++){
                    QDomNode n=list.at(i);
                    //qDebug()<< "childElm :" + n.nodeName();
                    QDomNodeList childList=n.childNodes();
                    if(!childList.isEmpty()){
                        for(int j=0;j<childList.count();j++){
                            QDomNode m=childList.at(j);
                            //qDebug()<< "childrenE:" + m.nodeName();
                            if(m.nodeName()=="translation"){
                                QString pstionInsert = QString::number(postionNum,'f',0);
                                pstionInsert = letter+pstionInsert;
                                range=s_worksheet->querySubObject("Range(QString)",pstionInsert);
                                QString excelValue=range->property("Value").toString();
                                qDebug()<< "xml Value:" <<m.toElement().text() << "excelVlaue: " + excelValue;
                                if(m.toElement().text()!= excelValue){
                                    QDomNode oldnode=m.firstChild();
                                    m.firstChild().setNodeValue(excelValue);
                                    QDomNode newnode=m.firstChild();
                                    m.replaceChild(newnode,oldnode);
                                }
                                postionNum++;
                            }
                        }
                    }
                }
            }
            node=node.nextSibling(); //nextSibling Element
        }
        if(!file.open(QFile::WriteOnly|QFile::Truncate)){return false;}
        QTextStream out_stream(&file);
        doc.save(out_stream,4); //缩进4格
        file.close();
    }
    workbook->dynamicCall("Save()");
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
    if (excel)
    {
       delete excel;
       excel = NULL;
    }
    return true;
}
