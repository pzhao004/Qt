#include "tableviewmodel.h"
#include <QDebug>
#include <QRegExp>
#include <QTime>
#include<qrandom.h>
#include <QSortFilterProxyModel>
TableViewModel::TableViewModel() : QAbstractTableModel (nullptr)
{
}

void TableViewModel::handleRecordIndex(int rIndex, bool rStatus){
    qDebug() << "handleRecordIndex" << rIndex <<rStatus;
    m_indexList.push_back(rIndex);
    qDebug() << "handleRecordIndex" << m_indexList;
}
void TableViewModel::handleFilterChange(){
    qDebug() << "handleFilterChange......";
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

//        for (int i =0;i<100;i++) {
//            QString a = "number";
//            add( a.append(QString::number(2*i)),  a.append(QString::number(i)) , QString::number(i));
//        }
}
void TableViewModel::add(QString str1, QString str2, QString str3){
    if(str1.isEmpty() && str2.isEmpty() && str3.isEmpty()){}
    else{
       beginInsertRows(QModelIndex(), m_aryData.size(), m_aryData.size());
       QVector<QString> list;
       list.push_back(str1);
       list.push_back(str2);
       list.push_back(str3);
       list.push_back(nullptr);
       m_aryData.push_back(list);
       endInsertRows();
    }
}
void TableViewModel::del(int row){
//    if(m_aryData.size()>0){
//        qDebug() <<QModelIndex();
//        beginRemoveRows(QModelIndex(), 1, 1);
//        m_aryData.removeOne(m_aryData.at(1));
//        endRemoveRows();

//        beginResetModel();
//        endResetModel();
//    }
    removeRows(row,1);
    refresh();
}
void TableViewModel::delSec(){
    qDebug() << m_rowData <<m_rowData.size();
    if(m_aryData.size()>0 && m_rowData.size()>0){
        for (int var = 0; var < rowCount(); ++var) {
            if(m_aryData.at(var).operator==(m_rowData)){
                beginRemoveRows(QModelIndex(), var, var);
                m_aryData.removeOne(m_aryData.at(var));
                endRemoveRows();
            }
        }
    }
}
void TableViewModel::delall(){
    qDebug() <<"enter delete all..." <<"m_indexList.size: "<< m_indexList.size() <<"m_aryData.size: " <<m_aryData.size();

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
//    if(m_rowData.size()==3){
//        for (int i =0;i<3; i++) {
//            m_rowData.remove(0);
//        }
//    }
//    m_rowData.push_back(rowData);

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
