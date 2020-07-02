
#include "hmi/contexts/contextmeastype.h"
#include "hmi/contexts/contextmethodsetcond.h"
#include "hmi/contexts/contextmethodsetion.h"
#include "hmi/contexts/contextmethodsetph.h"
#include "hmi/contexts/contextmethodsetredox.h"

namespace context {
ContextMeasType::ContextMeasType(hmi::ContextManager& context_manager)
    : ContextBase("Popups/SpecPopup.qml", context_manager) {
  _opened = true;
  _model = new model::MeasurementTypesListMode();
}
void ContextMeasType::closePopup() {
  _opened = false;
  emit openedChanged();
}

}  // namespace context
