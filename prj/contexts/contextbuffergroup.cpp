
#include "hmi/contexts/contextbuffergroup.h"
#include <QDebug>

namespace context {

ContextBufferGroup::ContextBufferGroup(hmi::ContextManager &context_manager)
    : ContextBase("Context/TngBufferGroup.qml", context_manager) {
  _tabModel = new model::TabButtonModel(this);
  _tabModel->addRow("MT", "mtTag", "qrc:///icons/placeholder_menuitem");
  _tabModel->addRow("DIN 19266", "mtTag", "qrc:///icons/placeholder_menuitem");
  _tabModel->addRow("DIN 19267", "mtTag", "qrc:///icons/placeholder_menuitem");
  emit tabModelChanged();
}

void ContextBufferGroup::pop() {
  qDebug() << "pop a page...";
  ContextBase::pop();
}

}  // namespace context
