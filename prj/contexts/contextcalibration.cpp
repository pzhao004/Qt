
#include "hmi/contexts/contextcalibration.h"
#include <QDebug>
#include "hmi/contexts/contextbuffergroup.h"

namespace context {

ContextCalibrationpH::ContextCalibrationpH(hmi::ContextManager &context_manager) : _context_manager(context_manager) {
  _auto_buffer_recognition_ph = false;

  _calibration_mode_ph = 1;
  _calibration_mode_ion = 0;

  _calibration_reminder_ph = false;
  _calibration_reminder_cond = false;
  _calibration_reminder_ion = false;

  _calibration_reminder_val_ph = "24 h";
  _calibration_reminder_val_cond = "25 h";
  _calibration_reminder_val_ion = "26 h";
}

ContextCalibrationpH::~ContextCalibrationpH() {}

void ContextCalibrationpH::updateRecord(MFCalibrationpHRecord *record) { _record = record; }

void ContextCalibrationpH::releaseRecord() { _record = nullptr; }

bool ContextCalibrationpH::getAutoBufRecog() const { return _auto_buffer_recognition_ph; }
int ContextCalibrationpH::getCalibrationMode() const {
  if (_measurement_type == 0) {
    return _calibration_mode_ph;
  } else if (_measurement_type == 2) {
    return _calibration_mode_ion;
  } else {
    return 0;
  }
}
bool ContextCalibrationpH::getCalibrationReminder() const {
  if (_measurement_type == 0) {
    return _calibration_reminder_ph;
  } else if (_measurement_type == 1) {
    return _calibration_reminder_cond;
  } else if (_measurement_type == 2) {
    return _calibration_reminder_ion;
  } else {
    return false;
  }
}
QString ContextCalibrationpH::getCalibrationReminderVal() const {
  if (_measurement_type == 0) {
    return _calibration_reminder_val_ph;
  } else if (_measurement_type == 1) {
    return _calibration_reminder_val_cond;
  } else if (_measurement_type == 2) {
    return _calibration_reminder_val_ion;
  } else {
    return "";
  }
}

void ContextCalibrationpH::autoBufferRecog_set(bool value) {
  qDebug() << "autoBufferRecog_set::" << value;
  _auto_buffer_recognition_ph = value;
  emit autoBufRecogChanged();
}
void ContextCalibrationpH::calibrationMode_set(int value) {
  if (_measurement_type == 0) {
    _calibration_mode_ph = value;
  } else if (_measurement_type == 2) {
    _calibration_mode_ion = value;
  } else {
  }
  emit calibrationModeChanged();
}
void ContextCalibrationpH::calibrationReminder_set(bool value) {
  qDebug() << "calibrationReminder_set::" << value;
  if (_measurement_type == 0) {
    _calibration_reminder_ph = value;
  } else if (_measurement_type == 1) {
    _calibration_reminder_cond = value;
  } else if (_measurement_type == 2) {
    _calibration_reminder_ion = value;
  } else {
  }
  emit calibrationReminderChanged();
}
void ContextCalibrationpH::calibrationReminderValue_set(QString value) {
  qDebug() << "calibrationReminder_set::" << value;
  if (_measurement_type == 0) {
    _calibration_reminder_val_ph = value;
  } else if (_measurement_type == 1) {
    _calibration_reminder_val_cond = value;
  } else if (_measurement_type == 2) {
    _calibration_reminder_val_ion = value;
  } else {
  }
  emit calibrationReminderValChanged();
}
void ContextCalibrationpH::gotobufferGroupPage() {
  qDebug() << "gotobufferGroupPage::";
  _context_manager.push(new context::ContextBufferGroup(_context_manager));
}

}  // namespace context
