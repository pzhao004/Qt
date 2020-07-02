
#include "hmi/contexts/contextmaintenance.h"

namespace context {

ContextMaintenance::ContextMaintenance(hmi::ContextManager &context_manager)
    : ContextBase("Context/TngMaintenance.qml", context_manager) {
  _tabModel = new model::TabButtonModel(this);
  _tabModel->addRow("Maintenance", "maintenancetag", "qrc:///icons/placeholder_menuitem");
  emit tabModelChanged();
}

}  // namespace context
