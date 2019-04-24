#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QDebug>
#include <QVector>
#include <QSortFilterProxyModel>
#include <QQmlParserStatus>
//#include <QJSValue>
#include "tableviewmodel.h"

class SortFilterProxyModel : public QSortFilterProxyModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(bool recordStatus READ recordStatus NOTIFY recordStatusChanged)
    Q_PROPERTY(int recordIndex READ recordIndex NOTIFY recordIndexChanged)

    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(TableViewModel *source READ source WRITE setSource)
    Q_PROPERTY(QByteArray sortRole READ sortRole  WRITE setSortRole)
    Q_PROPERTY(Qt::SortOrder sortOrder READ sortOrder WRITE setSortOrder)

    Q_PROPERTY(QByteArray filterRole READ filterRole WRITE setFilterRole)
    Q_PROPERTY(QString filterString READ filterString WRITE setFilterString NOTIFY filterStringChanged)
    Q_PROPERTY(FilterSyntax filterSyntax READ filterSyntax WRITE setFilterSyntax)
    Q_ENUMS(FilterSyntax)
public:
    explicit SortFilterProxyModel(QObject * parent = nullptr);

    //int idx() const;
    //void setIdx(const int idx);

    bool recordStatus() const;
    int recordIndex() const;

    TableViewModel *source() const;
    void setSource(TableViewModel *source);

    QByteArray sortRole() const;
    void setSortRole(QByteArray &role);

    void setSortOrder(Qt::SortOrder order);

    QByteArray filterRole() const;
    void setFilterRole(const QByteArray &role);

    QString filterString() const;
    void setFilterString(const QString &filter);

    enum FilterSyntax{RegExp,Wildcard,FixedString};

    FilterSyntax filterSyntax() const;
    void setFilterSyntax(FilterSyntax syntax);

    void classBegin();
    void componentComplete();
    bool filterAcceptsRow(int sourceRow,const QModelIndex &sourceParent) const;

protected:
    int roleKey(const QByteArray &role) const;
    QHash<int,QByteArray> roleNames() const;

signals:
    void recordStatusChanged(bool recordStatus);
    void recordIndexChanged(int recordIndex, bool recordStatus) const;
    void filterStringChanged();

public slots:
    void handleRecordIndex(int rIndex);

private:
    bool m_recordStatus;
    int    m_recordIndex;
    bool m_complete;
    int m_idx;
    QByteArray m_sortRole;
    QByteArray m_filterRole;
    QVector<QVector<QString>> m_aryData;
    QStringList idxlist;
    TableViewModel *m_tableViewModel;
    QList<QString> m_indexList;
    int flag;
    QString m_temp;
};

#endif // SORTFILTERPROXYMODEL_H
