/*!
*@file main.cpp.
*@brief design the mode of table view.
*@version 1.0.
*@author zhao albert.
*/
#ifndef TABLEVIEWMODEL_H
#define TABLEVIEWMODEL_H

#include <QVector>
#include <QAbstractTableModel>
#include <QAbstractListModel>
#include <QSortFilterProxyModel>
enum{
    oneRole,
    twoRole,
    threeRole,
    fourRole
};
class TableViewModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableViewModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash <int, QByteArray> roleNames() const;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    void initialDatas();
    Q_INVOKABLE void add(QString str1, QString str2, QString str3);
    Q_INVOKABLE void del(QString row);
    Q_INVOKABLE void delall();
    Q_INVOKABLE void modify(int row, int column, QString txt);
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void collectData(QString rowData);

public slots:
    void handleRecordIndex(int rIndex, bool rStatus);
    void handleFilterChange();

private:
    QVector<QVector<QString>> m_aryData;
    QHash<int, QByteArray> m_roles;
    QVector<QString> m_rowData;
    QVector<int> m_indexList;
    int m_count;
};

#endif // TABLEVIEWMODEL_H
