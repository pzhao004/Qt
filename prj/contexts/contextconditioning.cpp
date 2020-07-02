
#include "hmi/contexts/contextconditioning.h"
#include <QDebug>
namespace context {

ContextConditioning::ContextConditioning(hmi::ContextManager &context_manager) : _context_manager(context_manager) {
  _stir_ph = false;
  _stir_cond = true;
  _stir_ion = false;
  _stir_redox = true;
  _wait_time_enable_ph = false;
  _wait_time_enable_cond = true;
  _wait_time_enable_ion = false;
  _wait_time_enable_redox = true;
  _stirringTime_ph = "45 s";
  _stirringTime_cond = "46 s";
  _stirringTime_ion = "47 s";
  _stirringTime_redox = "48 s";
  _condition_for_calibration_ph = false;
  _condition_for_calibration_cond = false;
  _condition_for_calibration_ion = false;
  _condition_for_calibration_redox = false;
  _wait_time_ph = "10 s";
  _wait_time_cond = "20 s";
  _wait_time_ion = "30 s";
  _wait_time_redox = "40 s";
  _stirring_speed_ph = 2;
  _stirring_speed_cond = 2;
  _stirring_speed_ion = 2;
  _stirring_speed_redox = 2;
}

ContextConditioning::~ContextConditioning() {}

void ContextConditioning::updateRecord(MFConditioningRecord *record) { _record = record; }

void ContextConditioning::releaseRecord() { _record = nullptr; }

bool ContextConditioning::getStir() const {
  if (_measurement_type == 0) {
    return _stir_ph;
  } else if (_measurement_type == 1) {
    return _stir_cond;
  } else if (_measurement_type == 2) {
    return _stir_ion;
  } else if (_measurement_type == 3) {
    return _stir_redox;
  } else {
    return false;
  }
}
QString ContextConditioning::getStirTime() const {
  if (_measurement_type == 0) {
    return _stirringTime_ph;
  } else if (_measurement_type == 1) {
    return _stirringTime_cond;
  } else if (_measurement_type == 2) {
    return _stirringTime_ion;
  } else if (_measurement_type == 3) {
    return _stirringTime_redox;
  } else {
    return "";
  }
}
int ContextConditioning::getStirSpeed() const {
  if (_measurement_type == 0) {
    return _stirring_speed_ph;
  } else if (_measurement_type == 1) {
    return _stirring_speed_cond;
  } else if (_measurement_type == 2) {
    return _stirring_speed_ion;
  } else if (_measurement_type == 3) {
    return _stirring_speed_redox;
  } else {
    return 0;
  }
}
bool ContextConditioning::getWaitTime() const {
  if (_measurement_type == 0) {
    return _wait_time_enable_ph;
  } else if (_measurement_type == 1) {
    return _wait_time_enable_cond;
  } else if (_measurement_type == 2) {
    return _wait_time_enable_ion;
  } else if (_measurement_type == 3) {
    return _wait_time_enable_redox;
  } else {
    return false;
  }
}
QString ContextConditioning::getTime() const {
  if (_measurement_type == 0) {
    return _wait_time_ph;
  } else if (_measurement_type == 1) {
    return _wait_time_cond;
  } else if (_measurement_type == 2) {
    return _wait_time_ion;
  } else if (_measurement_type == 3) {
    return _wait_time_redox;
  } else {
    return "";
  }
}
bool ContextConditioning::getConditioningEnable() const {
  if (_measurement_type == 0) {
    return _condition_for_calibration_ph;
  } else if (_measurement_type == 1) {
    return _condition_for_calibration_cond;
  } else if (_measurement_type == 2) {
    return _condition_for_calibration_ion;
  } else if (_measurement_type == 3) {
    return _condition_for_calibration_redox;
  } else {
    return false;
  }
}

void ContextConditioning::stirEnable_set(bool value) {
  qDebug() << "stirEnable_set::" << value;
  if (_measurement_type == 0) {
    _stir_ph = value;
  } else if (_measurement_type == 1) {
    _stir_cond = value;
  } else if (_measurement_type == 2) {
    _stir_ion = value;
  } else if (_measurement_type == 3) {
    _stir_redox = value;
  } else {
  }
  emit stirChanged();
}
void ContextConditioning::stiringTime_set(QString value) {
  qDebug() << "stiringTime_set::" << value;
  if (_measurement_type == 0) {
    _stirringTime_ph = value;
  } else if (_measurement_type == 1) {
    _stirringTime_cond = value;
  } else if (_measurement_type == 2) {
    _stirringTime_ion = value;
  } else if (_measurement_type == 3) {
    _stirringTime_redox = value;
  } else {
  }
  emit stirTimeChanged();
}
void ContextConditioning::waittimeEnable_set(bool value) {
  qDebug() << "waittimeEnable_set::" << value;
  if (_measurement_type == 0) {
    _wait_time_enable_ph = value;
  } else if (_measurement_type == 1) {
    _wait_time_enable_cond = value;
  } else if (_measurement_type == 2) {
    _wait_time_enable_ion = value;
  } else if (_measurement_type == 3) {
    _wait_time_enable_redox = value;
  } else {
  }
  emit waitTimeChanged();
}
void ContextConditioning::waitTime_set(QString value) {
  qDebug() << "waitTime_set::" << value;
  if (_measurement_type == 0) {
    _wait_time_ph = value;
  } else if (_measurement_type == 1) {
    _wait_time_cond = value;
  } else if (_measurement_type == 2) {
    _wait_time_ion = value;
  } else if (_measurement_type == 3) {
    _wait_time_redox = value;
  } else {
  }
  emit timeChanged();
}
void ContextConditioning::stiringSpeed_set(int value) {
  qDebug() << "stiringSpeed_set::" << value;
  if (_measurement_type == 0) {
    _stirring_speed_ph = value;
  } else if (_measurement_type == 1) {
    _stirring_speed_cond = value;
  } else if (_measurement_type == 2) {
    _stirring_speed_ion = value;
  } else if (_measurement_type == 3) {
    _stirring_speed_redox = value;
  } else {
  }
  emit stirSpeedChanged();
}
void ContextConditioning::conditionForCalibration_set(bool value) {
  qDebug() << "conditionForCalibration_set::" << value;
  if (_measurement_type == 0) {
    _condition_for_calibration_ph = value;
  } else if (_measurement_type == 1) {
    _condition_for_calibration_cond = value;
  } else if (_measurement_type == 2) {
    _condition_for_calibration_ion = value;
  } else if (_measurement_type == 3) {
    _condition_for_calibration_redox = value;
  } else {
  }
  emit conditioningEnableChanged();
}
}  // namespace context
