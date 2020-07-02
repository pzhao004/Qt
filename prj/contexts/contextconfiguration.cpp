
#include "hmi/contexts/contextconfiguration.h"
#include <QDebug>

namespace context {

ContextConfiguration::ContextConfiguration(hmi::ContextManager& context_manager) : _context_manager(context_manager) {}

ContextConfiguration::~ContextConfiguration() {}

void ContextConfiguration::updateRecord(MFConfigurationRecord* record) { _record = record; }

void ContextConfiguration::releaseRecord() { _record = nullptr; }

int ContextConfiguration::getSensor() const { return 0; }

int ContextConfiguration::getTempCapture() const {
  if (!_record) {
    return 0;
  }
  return _record->temperature_sensor_type;
}

void ContextConfiguration::sensor_set(int index) {
  qDebug() << "sensor_set:: " << index;
  emit sensorChanged();
  return;
}
void ContextConfiguration::tempCapture_set(int index) {
  ETemperatureSensorType temperature_sensor_type;
  if (!_record) {
    return;
  }
  temperature_sensor_type = static_cast<ETemperatureSensorType>(index);
  if (temperature_sensor_type >= eTemperatureSensorType_Max) {
    return;
  }
  _record->temperature_sensor_type = temperature_sensor_type;
  emit tempCaptureChanged();
}

}  // namespace context
