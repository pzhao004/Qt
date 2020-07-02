
#include "hmi/contexts/contextbuffer.h"

namespace context {

ContextBuffer::ContextBuffer(hmi::ContextManager &context_manager)
    : ContextBase("Context/TngBuffer.qml", context_manager) {
  _tabModel = new model::TabButtonModel(this);
  _tabModel->addRow("Buffers", "bufferstag", "qrc:///icons/placeholder_menuitem");
  emit tabModelChanged();
}

}  // namespace context
