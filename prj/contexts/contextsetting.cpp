
#include "hmi/contexts/contextsetting.h"

namespace context {

ContextSetting::ContextSetting(hmi::ContextManager &context_manager)
    : ContextBase("Context/TngSeting.qml", context_manager) {
  _tabModel = new model::TabButtonModel(this);
  _tabModel->addRow("Settings", "settingtag", "qrc:///icons/placeholder_menuitem");
  emit tabModelChanged();
}

}  // namespace context
