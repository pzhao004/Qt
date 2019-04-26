#include "tableviewmodel.h"
#include <QDebug>
#include <QRegExp>
#include <QTime>
#include<qrandom.h>
#include <QSortFilterProxyModel>
TableViewModel::TableViewModel() : QAbstractTableModel (nullptr)
{
    m_count=0;
}

void TableViewModel::handleRecordIndex(int rIndex, bool rStatus){
    qDebug() << "handleRecordIndex" << rIndex <<rStatus;
    m_indexList.push_back(rIndex);
    //qDebug() << "handleRecordIndex" << m_indexList;
}
void TableViewModel::handleFilterChange(){
    //qDebug() << "handleFilterChange......";
    m_indexList.clear();
}

int TableViewModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return m_aryData.size();
}
int TableViewModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    if(m_aryData.size()>0){
        return m_aryData.at(0).size();
    }else{
        return -1;
    }
}
QVariant TableViewModel::data(const QModelIndex &index, int role) const{
    //qDebug() << index.row() << role << m_aryData[index.row()][role].contains(filterRegExp());
    if(!index.isValid()){
        return QVariant();
    }
    if(role < 0){
        return QVariant();
    }else{
        //qDebug() << "tableModel: " << m_aryData[index.row()][role];
        return m_aryData[index.row()][role];
    }
}
QHash<int, QByteArray> TableViewModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[oneRole] = "name";
    roles[twoRole] = "price";
    roles[threeRole] = "description";
    roles[fourRole] = "func";
    return roles;
}
bool TableViewModel::removeRows(int row, int count, const QModelIndex &parent){
    qDebug() <<"parent: " << parent <<"row: " << row << count;
    beginRemoveRows(QModelIndex(), row, row);
    for (int n = 0; n < count; ++n)
    {
        qDebug() << "delete...";
        m_aryData.removeAt(row);
    }
    endRemoveRows();

    return true;
}

void TableViewModel::initialDatas(){
        add(QStringLiteral("aaa"), "999", QStringLiteral("good"));
        add(QStringLiteral("bbb"), "777", QStringLiteral("best"));
        add(QStringLiteral("bcc"), "554", QStringLiteral("better"));
        add(QStringLiteral("ddd"), "894", QStringLiteral("bad"));
        add(QStringLiteral("eee"), "892", QStringLiteral("best"));
        add(QStringLiteral("fff"), "890", QStringLiteral("better"));
        add(QStringLiteral("hhh"), "894", QStringLiteral("good"));
        add(QStringLiteral("iii"), "896", QStringLiteral("better"));
        add(QStringLiteral("ggg"), "897", QStringLiteral("better"));

}
void TableViewModel::add(QString str1, QString str2, QString str3){
//    QDateTime current_date_time =QDateTime::currentDateTime();
//    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz");
    QString currrent_data = QString::number(m_count);
    if(str1.isEmpty() && str2.isEmpty() && str3.isEmpty()){}
    else{
       beginInsertRows(QModelIndex(), m_aryData.size(), m_aryData.size());
       QVector<QString> list;
       list.push_back(str1);
       list.push_back(str2);
       list.push_back(str3);
       list.push_back(currrent_data);
       m_aryData.push_back(list);
       endInsertRows();
       refresh();
    }
    m_count++;
    m_indexList.clear();
}
void TableViewModel::del(QString row){
    if(m_aryData.size()>0){
        for(int i =0; i< m_aryData.size();i++){
            qDebug() << row << m_aryData.at(i).at(3);
            if(row == m_aryData.at(i).at(3)){
                beginRemoveRows(QModelIndex(), i, i);
                m_aryData.removeAt(i);
                endRemoveRows();
                break;
            }
        }
    }
    m_indexList.clear();
}
void TableViewModel::delall(){
    //qDebug() <<"enter delete all..." <<"m_indexList.size: "<< m_indexList.size() <<"m_aryData.size: " <<m_aryData.size();
    if(m_aryData.size()>0){
        //根据提供的索引，倒着删除数据
        if(m_indexList.size()==0){
            while(m_aryData.size()>0){
                beginRemoveRows(QModelIndex(), m_aryData.size()-1, m_aryData.size()-1);
                m_aryData.removeLast();
                endRemoveRows();
            }
        }else{
            for(int i = m_indexList.size()-1; i>=0;i--){
                qDebug() << m_indexList.at(i);
                beginRemoveRows(QModelIndex(), m_indexList.at(i), m_indexList.at(i));
                m_aryData.removeAt(m_indexList.at(i));
                endRemoveRows();
            }
        }
    }
}
void TableViewModel::modify(int row, int column, QString txt){
    qDebug() << row <<column << txt;
//     if(m_aryData.size()>0){
//         if (row == -1){
//                return;
//            }
//        if (column == -1){
//            return;
//        }
//         beginResetModel();
//         m_aryData[row][column] = txt;
//         endResetModel();
//     }
}
void TableViewModel::refresh(){
    if(m_aryData.size()>0){
        beginResetModel();
        endResetModel();
    }
}
void TableViewModel::collectData(QString rowData){
    m_rowData.push_back(rowData);
    if(m_rowData.size()==3){
        m_rowData.push_back(nullptr);
        qDebug() <<"m_rowData:"<<m_rowData ;
        for (int var = 0; var < m_aryData.size(); ++var) {
            qDebug() << "m_aryData: " << m_aryData.at(var);
            if(m_aryData.at(var) == m_rowData){
                beginRemoveRows(QModelIndex(),var, var);
                m_aryData.removeOne(m_aryData.at(var));
                endRemoveRows();

                beginResetModel();
                endResetModel();
                break;
            }
        }
        m_rowData.clear();
        qDebug() << "...m_rowData:" << m_rowData;
    }
}
