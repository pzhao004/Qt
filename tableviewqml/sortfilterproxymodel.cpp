#include "sortfilterproxymodel.h"
#include <QtDebug>
#include <QtQml>

SortFilterProxyModel::SortFilterProxyModel(QObject *parent): QSortFilterProxyModel(parent)
{
    m_complete = false;
    flag=1;
    m_temp = "**";
}
QHash<int,QByteArray> SortFilterProxyModel::roleNames() const{
    //qDebug() << "....1....";
    if(QAbstractItemModel *source = sourceModel()){
        //qDebug() << "roleNames: " << source->roleNames();
        return source->roleNames();
    }
    return QHash<int,QByteArray>();
}
int SortFilterProxyModel::recordIndex() const{
    //qDebug() << "....2....";
    return m_recordIndex;
}
bool SortFilterProxyModel::recordStatus() const{
   // qDebug() << "....3....";
    return m_recordStatus;
}
int SortFilterProxyModel::roleKey(const QByteArray &role) const{
   // qDebug() << "....5....";
    QHash<int,QByteArray> roles =roleNames();
    QHashIterator<int,QByteArray> it(roles);
    while(it.hasNext()){
        it.next();
        if(it.value()==role){
            return it.key();
        }
    }
    return -1;
}

TableViewModel *SortFilterProxyModel::source() const{
    //qDebug() << "....6....";
    //qDebug() << "sourceModel" << sourceModel();
    //return sourceModel();
    return m_tableViewModel;
}
QByteArray SortFilterProxyModel::sortRole() const{
    qDebug() << "....7...." << m_sortRole;
    return m_sortRole;
}
QByteArray SortFilterProxyModel::filterRole() const{
    return m_filterRole;
}
QString SortFilterProxyModel::filterString() const{
    //qDebug() << "....9....";
    return filterRegExp().pattern();
}
SortFilterProxyModel::FilterSyntax SortFilterProxyModel::filterSyntax() const{
    //qDebug() << "....10....";
    return static_cast<FilterSyntax>(filterRegExp().patternSyntax());
}

void SortFilterProxyModel::setSource(TableViewModel *source){
    //qDebug() << "....11....";
    setSourceModel(qobject_cast<QAbstractItemModel *>(source));
    //qDebug() << qobject_cast<QAbstractItemModel *>(source);
    if(source != nullptr && flag==1){
        qDebug() << "connecting...... ";
        connect(this, SIGNAL(recordIndexChanged(int,bool)), source, SLOT(handleRecordIndex(int,bool)));
        connect(this, SIGNAL(filterStringChanged()), source, SLOT(handleFilterChange()));
        flag++;
    }
}
void SortFilterProxyModel::setSortRole(QByteArray &role){
    //qDebug() << "....12....";
    if(m_sortRole != role){
        m_sortRole=role;
        if(m_complete){
            QSortFilterProxyModel::setSortRole(roleKey(role));
        }
    }
}
void SortFilterProxyModel::setSortOrder(Qt::SortOrder order){
    //qDebug() << "....13....";
    QSortFilterProxyModel::sort(0,order);
}
void SortFilterProxyModel::setFilterRole(const QByteArray &role){
    //qDebug() << "....14....";
    if(m_filterRole != role){
        m_filterRole=role;
        if(m_complete){
            QSortFilterProxyModel::setFilterRole(roleKey(role));
        }
    }
}
void SortFilterProxyModel::setFilterString(const QString &filter){
    qDebug() << "....15...." << filter;
    if(m_temp == filter){
        qDebug() << "......the value isn't changed...";
    }else{
        emit filterStringChanged();
        m_temp = filter;
        qDebug() << "......the value is changed...";
    }
    setFilterRegExp(QRegExp(filter,filterCaseSensitivity(),static_cast<QRegExp::PatternSyntax>(filterSyntax())));
}
void SortFilterProxyModel::setFilterSyntax(SortFilterProxyModel::FilterSyntax syntax){
    //qDebug() << "....16....";
    setFilterRegExp(QRegExp(filterString(),filterCaseSensitivity(),static_cast<QRegExp::PatternSyntax>(syntax)));
}

void SortFilterProxyModel::classBegin(){
    //qDebug() << "....17....";
}
void SortFilterProxyModel::componentComplete(){
    //qDebug() << "....18....";
    m_complete=true;
    if(!m_sortRole.isEmpty()){
        QSortFilterProxyModel::setSortRole(roleKey(m_sortRole));
    }

    if(!m_filterRole.isEmpty()){
        QSortFilterProxyModel::setFilterRole(roleKey(m_filterRole));
    }
}

bool SortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const{
    QRegExp rx= filterRegExp();
    if(rx.isEmpty()){
        return true;
    }
    QAbstractItemModel *model = sourceModel();
    if(filterRole().isEmpty()){
        QHash<int,QByteArray> roles=roleNames();
        QHashIterator<int,QByteArray> it(roles);
        while(it.hasNext()){
            it.next();
            QModelIndex sourceIndex=model->index(sourceRow,0,sourceParent);
            QString key=model->data(sourceIndex,it.key()).toString();
            if(key.contains(rx)){
                return true;
            }
        }
        return false;
    }
    QModelIndex sourceIndex=model->index(sourceRow,0,sourceParent);
    if(!sourceIndex.isValid()){
        return true;
    }
    QString key = model->data(sourceIndex,roleKey(filterRole())).toString();
    if(key.contains(rx)){
        emit recordIndexChanged(sourceIndex.row(), true);
    }
    return key.contains(rx);
}

