
#include "hmi/contexts/contextmethod.h"
#include <QDebug>
#include "hmi/component/hmiproxyprovider.h"
#include "hmi/contexts/contextmeastype.h"
#include "hmi/contexts/contextmethodsetcond.h"
#include "hmi/contexts/contextmethodsetion.h"
#include "hmi/contexts/contextmethodsetph.h"
#include "hmi/contexts/contextmethodsetredox.h"
#include "hmi/interaction/interactioncontroller.h"

namespace context {

ContextMethod::ContextMethod(hmi::ContextManager& context_manager)
    : ContextBase("Context/TngMethod.qml", context_manager) {
  _tabModel = new model::TabButtonModel(this);
  _tabModel->addRow("pH", "method_ph_tag", "qrc:///icons/placeholder_menuitem");
  _tabModel->addRow("Conductivity", "method_conductivity_tag", "qrc:///icons/placeholder_menuitem");
  _tabModel->addRow("Ion", "method_ion_tag", "qrc:///icons/placeholder_menuitem");
  _tabModel->addRow("Redox", "method_redox_tag", "qrc:///icons/placeholder_menuitem");
  emit tabModelChanged();
  _opened = false;
  _model = new model::MeasurementTypesListMode();
}

ContextMethod::~ContextMethod() {}

void ContextMethod::showOkCancelInteraction() {
  auto popup_interaction_model = std::make_unique<model::OkCancelPopupInteractionModel>("Really...?");
  popup_interaction_model->connect(popup_interaction_model.get(),
                                   &model::OkCancelPopupInteractionModel::interaction_response, this,
                                   &ContextMethod::okCancelInteractionResult);

  hmi::InteractionController* interaction_controller;
  getProxyProvider()->getHmiProxy()->getInteractionController(interaction_controller);
  interaction_controller->startInteraction(std::move(popup_interaction_model));
}

void ContextMethod::okCancelInteractionResult(model::OkCancelPopupInteractionModel::EOkCancelPopupResult result) {
  qDebug() << "OkCancelInteractionResult: " << result;
}

void ContextMethod::openPopupWindow() {
  _opened = true;
  emit openedChanged();
}
void ContextMethod::closePopupWindow() {
  _opened = false;
  emit openedChanged();
}
void ContextMethod::handleLoadButton() {}
void ContextMethod::gotoMeasurementSetContext(int index) {
  switch (index) {
    case 0:
      ContextBase::push(new context::ContextMethodSetpH(_context_manager));
      break;
    case 1:
      ContextBase::push(new context::ContextMethodSetCond(_context_manager));
      break;
    case 2:
      ContextBase::push(new context::ContextMethodSetIon(_context_manager));
      break;
    case 3:
      ContextBase::push(new context::ContextMethodSetRedox(_context_manager));
      break;
  }
}

}  // namespace context
