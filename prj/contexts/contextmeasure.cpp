
#include "hmi/contexts/contextmeasure.h"
#include "measurement/enums_names.h"

namespace context {

ContextMeasurepH::ContextMeasurepH(hmi::ContextManager &context_manager) : _context_manager(context_manager) {
  _unit = 1;
  _decimal_places = 0;
  _endpoint_type = 1;
  _stability_criteria = 2;
  _stir = false;
  _stirring_speed = 2;
  _limits = false;
  _limit_upper = false;
  _limit_lower = false;
  _limit_upper_temp = false;
  _limit_lower_temp = false;
}

ContextMeasurepH::~ContextMeasurepH() {}

void ContextMeasurepH::updateRecord(MFMeasurepHRecord *record) { _record = record; }

void ContextMeasurepH::releaseRecord() { _record = nullptr; }

int ContextMeasurepH::getUnit() const {
  measurement::getpHUnitTypeName(epHUnitType_pH);
  measurement::getRedoxUnitTypeName(eRedoxUnitType_mV);
  measurement::getIonUnitTypeName(eIonUnitType_pX);
  measurement::getCndUnitTypeName(eCndUnitType_uS_cm);
  return _unit;
}
int ContextMeasurepH::getDecimalPlaces() const { return _decimal_places; }
int ContextMeasurepH::getEndpointType() const { return _endpoint_type; }
int ContextMeasurepH::getStabilityCriteria() const { return _stability_criteria; }
bool ContextMeasurepH::getStir() const { return _stir; }
int ContextMeasurepH::getStirringSpeed() const { return _stirring_speed; }
bool ContextMeasurepH::getLimits() const { return _limits; }
bool ContextMeasurepH::getLimitsLower() const { return _limit_lower; }
bool ContextMeasurepH::getLimitsUpper() const { return _limit_upper; }
bool ContextMeasurepH::getLimitsUpperTemp() const { return _limit_upper_temp; }
bool ContextMeasurepH::getLimitsLowerTemp() const { return _limit_lower_temp; }
void ContextMeasurepH::endpointType_set(int value) {
  if (value != _endpoint_type) {
    _endpoint_type = value;
    emit endpointTypeChanged();
  }
}
void ContextMeasurepH::stirEnable_set(bool value) {
  if (value != _stir) {
    _stir = value;
    emit stirChanged();
  }
}
void ContextMeasurepH::stabilityCriteria_set(int value) {
  if (value != _stability_criteria) {
    _stability_criteria = value;
    emit stabilityCriteriaChanged();
  }
}
void ContextMeasurepH::limitsEnable_set(bool value) {
  if (_limits != value) {
    _limits = value;
    emit limitsChanged();
  }
}
void ContextMeasurepH::unitValue_set(int value) {
  if (_unit != value) {
    _unit = value;
    emit unitChanged();
  }
}
void ContextMeasurepH::decimalPlaces_set(int value) {
  if (value != _decimal_places) {
    _decimal_places = value;
    emit decimalPlacesChanged();
  }
}
void ContextMeasurepH::stirringSpeed_set(int value) {
  if (value != _stirring_speed) {
    _stirring_speed = value;
    emit stirringSpeedChanged();
  }
}
}  // namespace context
