
#include "hmi/contexts/contextmainscreen.h"
#include "adapter/stringadapter.h"
#include "hmi/contexts/tngjobusercontext.h"
#include "measurement/enums_names.h"

namespace context {

ContextMainScreen::ContextMainScreen(hmi::ContextManager& context_manager) : IContextMainScreenpH(context_manager) {
  _meas_value = "---";
  _meas_unit = "pH";
  _mv_value = "---";
  _temperature_value = "---";
  _sensor_name = "MTPHSensor";
  _sample_id = "Baileys No. 12(Batch 123456)";
  _endpoint_type = "Automatic";
  _stability_criteria = "Strict";
  _temperature_capture_mode = "ATC";
  _measurement_time = "0";

  _job_id_measurement = JOB_ID_NONE;

  _context_manger = &context_manager;
  _method_model = new model::TabButtonModel(this);
  _method_model->addRow("Method 1", "methodTag", "qrc:///icons/placeholder_menuitem");
  loadMethodpHRecord(resource::DefaultMethodpHName);
  initialSettings();
}

void ContextMainScreen::addRowData() {
  _method_model->addRow("Method 2", "method2Tag", "qrc:///icons/placeholder_menuitem");
  emit lengthChanged();
  emit methodModelChanged();
}
void ContextMainScreen::initialSettings() {
  if (_methodpH_record.method_name.isEmpty()) return;

  EMeasurementType meas_type = _methodpH_record.measurement_type;
  if (eMeasurementType_PH == meas_type) {
    _meas_unit = measurement::getpHUnitTypeName(_methodpH_record.measure.unit);
  } else if (eMeasurementType_Ion == meas_type) {
    /* Add code*/
  }
  _sensor_name = adapter::toQString(_methodpH_record.configuration.sensor_name);
  _sample_id = adapter::toQString(_methodpH_record.sample.samle_id);
  _endpoint_type = measurement::getEndpointTypeName(_methodpH_record.measure.endpoint_type);
  _stability_criteria = measurement::getStabilityCriteriaName(_methodpH_record.measure.stability_criteria);
  _temperature_capture_mode =
      measurement::getTemperatureCaptureModeName(_methodpH_record.configuration.temperature_capture_mode);
}

void ContextMainScreen::setMeasurementTime(const QString& time) {
  if (time.compare(_measurement_time) != 0) {
    _measurement_time = time;
    emit measTimeChanged();
  }
}

void ContextMainScreen::setMVValue(const QString& mv_value) {
  if (mv_value.compare(_mv_value) != 0) {
    _mv_value = mv_value;
    emit mVvalueChanged();
  }
}

void ContextMainScreen::setTemperatureValue(const QString& temperature_value) {
  if (temperature_value.compare(_temperature_value) != 0) {
    _temperature_value = temperature_value;
    emit measTempChanged();
  }
}

void ContextMainScreen::setMeasValue(const QString& meas_value) {
  if (meas_value.compare(_meas_value) != 0) {
    _meas_value = meas_value;
    emit measValueChanged();
  }
}

void ContextMainScreen::setMeasUnit(const QString& meas_unit) {
  if (meas_unit.compare(_meas_unit) != 0) {
    _meas_unit = meas_unit;
    emit measUnitChanged();
  }
}
void ContextMainScreen::setSensorName(const QString& sensor_name) {
  if (sensor_name.compare(_sensor_name) != 0) {
    _sensor_name = sensor_name;
    emit sensorChanged();
  }
}

void ContextMainScreen::setSampleID(const QString& sample_id) {
  if (sample_id.compare(_sample_id) != 0) {
    _sample_id = sample_id;
    emit sampleIdChanged();
  }
}

void ContextMainScreen::setEndpointType(const QString& endpoint_type) {
  if (endpoint_type.compare(_endpoint_type) != 0) {
    _endpoint_type = endpoint_type;
    emit endpointTypeChanged();
  }
}

void ContextMainScreen::setStabilityCriteria(const QString& stability_criteria) {
  if (stability_criteria.compare(_stability_criteria) != 0) {
    _stability_criteria = stability_criteria;
    emit stabilityCritChanged();
  }
}

void ContextMainScreen::setTemperatureCaptureMode(const QString& temperature_capture_mode) {
  if (temperature_capture_mode.compare(_temperature_capture_mode) != 0) {
    _temperature_capture_mode = temperature_capture_mode;
    emit tempCaptureChanged();
  }
}

void ContextMainScreen::setStableStatus(const bool& stable_status) {
  if (stable_status != _stable_status) {
    _stable_status = stable_status;
    emit stableStatusChanged();
  }
}
void ContextMainScreen::setMeasResultValueStatus(const int value_status) {
  if (_meas_result_value_status == value_status) return;
  _meas_result_value_status = value_status;
  emit measResultValueStatusChanged(_meas_result_value_status);
}

void ContextMainScreen::setMeasmVValueStatus(const int value_status) {
  if (_mv_value_status == value_status) return;
  _mv_value_status = value_status;
  emit measmVValueStatusChanged(_mv_value_status);
}
void ContextMainScreen::setTemperatureValueStatus(const int value_status) {
  if (_temperature_value_status == value_status) return;
  _temperature_value_status = value_status;
  emit temperatureValueStatusChanged(_temperature_value_status);
}
void ContextMainScreen::setMeasRuningStatus(const int measurement_status) {
  if (_measurement_status == measurement_status) return;
  _measurement_status = measurement_status;
  emit measRuningStatusChanged();
}

void ContextMainScreen::loadMethodpHRecord(const core::cstringex& method_name) {
  if (method_name.isEmpty()) return;

  resource::MethodpHRecord_ReadSession read_record_session(method_name);
  hmi::component::ProjectHmiPluginProxyProvider* provider =
      static_cast<hmi::component::ProjectHmiPluginProxyProvider*>(_context_manger->getProxyProviderProject());
  provider->getResourceServiceProxy()->requestResource(read_record_session);
  if (!read_record_session.isActive()) {
    return;
  }
  _methodpH_record = read_record_session.getRecord();
  provider->getResourceServiceProxy()->releaseResource(read_record_session);
}

void ContextMainScreen::measurementAction_set() {
  coreex::MetaData metaData;
  _method_measurement.reset(new method::MethodSetupMeasure(
      static_cast<hmi::component::ProjectHmiPluginProxyProvider*>(_context_manger->getProxyProviderProject())));

  job::TpJobUserContext job_user_context_ptr(
      new job::TngJobUserContext(JOB_QUEUE_A, JOB_USERID_NONE, this, metaData, true, job::eJobResultModeNone));

  _method_measurement->createMethod(_methodpH_record);
  _method_measurement->checkResource();
  _job_id_measurement = _method_measurement->start(job_user_context_ptr);
  return;
}
}  // namespace context
