
#include "hmi/contexts/contextsensor.h"

namespace context {

ContextSensor::ContextSensor(hmi::ContextManager &context_manager)
    : ContextBase("Context/TngSensor.qml", context_manager) {
  _tabModel = new model::TabButtonModel(this);
  _tabModel->addRow("Sensors", "sensortag", "qrc:///icons/placeholder_menuitem");
  emit tabModelChanged();
}

}  // namespace context
