
#include "hmi/contexts/contextmethodsetion.h"
#include "QDebug"
#include "hmi/contexts/context_factory.h"

namespace context {
ContextMethodSetIon::ContextMethodSetIon(hmi::ContextManager& context_manager)
    : ContextBase("Context/TngMethodSetIon.qml", context_manager) {
  _tabModel = new model::TabButtonModel(this);
  _tabModel->addRow("General", "generalTag", "qrc:///icons/placeholder_menuitem");
  _tabModel->addRow("Configuration", "cfgTag", "qrc:///icons/placeholder_menuitem");
  _tabModel->addRow("Sample", "sampleTag", "qrc:///icons/placeholder_menuitem");
  _tabModel->addRow("Conditioning", "conditioningTag", "qrc:///icons/placeholder_menuitem");
  _tabModel->addRow("Calibration", "calibrationTag", "qrc:///icons/placeholder_menuitem");
  _tabModel->addRow("Measure", "measureTag", "qrc:///icons/placeholder_menuitem");
  _tabModel->addRow("Report", "reportTag", "qrc:///icons/placeholder_menuitem");
  _tabModel->addRow("Verification", "verificationTag", "qrc:///icons/placeholder_menuitem");

  _provider_ptr =
      static_cast<hmi::component::ProjectHmiPluginProxyProvider*>(context_manager.getProxyProviderProject());
  resource::MethodIonRecord_ReadSession read_session(resource::DefaultMethodIonName);
  _provider_ptr->getResourceServiceProxy()->requestResource(read_session);
  if (read_session.isActive()) {
    _method_record = read_session.getRecord();
    _provider_ptr->getResourceServiceProxy()->releaseResource(read_session);
  }
  context::ContextFactory::getInstance().getContextGeneral()->updateRecord(&(_method_record.general));

  emit tabModelChanged();
}

void ContextMethodSetIon::handleCloseButton() { ContextBase::pop(); }
void ContextMethodSetIon::handleSaveButton() {}

}  // namespace context
