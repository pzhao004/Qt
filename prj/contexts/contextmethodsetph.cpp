
#include "hmi/contexts/contextmethodsetph.h"
#include "QDebug"
#include "hmi/contexts/context_factory.h"
#include "hmi/interaction/okcancelpopupinteractionmodel.h"
#include "methods/method_setup.h"

namespace context {
ContextMethodSetpH::ContextMethodSetpH(hmi::ContextManager& context_manager)
    : ContextBase("Context/TngMethodSet.qml", context_manager) {
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

  if (method::MethodSetup::createMethodRecord(_provider_ptr, _method_record)) {
    context::ContextFactory::getInstance().getContextGeneral()->updateRecord(&(_method_record.general));
  }
  emit tabModelChanged();
}

ContextMethodSetpH::~ContextMethodSetpH() {
  qDebug() << "release ContextMethodSetpH";
  context::ContextFactory::getInstance().getContextGeneral()->releaseRecord();
}

void ContextMethodSetpH::handleCloseButton() {
  context::ContextFactory::getInstance().getContextGeneral()->releaseRecord();
  ContextBase::pop();
}

void ContextMethodSetpH::handleSaveButton() {
  if (_method_record.general.method_name.isEmpty()) {
    return;
  }
  _method_record.method_name = _method_record.general.method_name;
  resource::MethodpHRecord_AddSession add_record_session;
  _provider_ptr->getResourceServiceProxy()->requestResource(add_record_session);
  if (add_record_session.isActive()) {
    add_record_session.getRecord() = _method_record;
    add_record_session.commit();
    _provider_ptr->getResourceServiceProxy()->releaseResource(add_record_session);
  }
  context::ContextFactory::getInstance().getContextGeneral()->releaseRecord();
  ContextBase::pop();
}

}  // namespace context
