#include "hmi/contexts/contextgeneral.h"
#include "adapter/stringadapter.h"

#include <QDebug>

namespace context {

ContextGeneral::ContextGeneral(hmi::ContextManager &context_manager) : _context_manager(context_manager) {}

ContextGeneral::~ContextGeneral() {}

void ContextGeneral::updateRecord(MFGeneralRecord *record) { _record = record; }

void ContextGeneral::releaseRecord() { _record = nullptr; }

QString ContextGeneral::getMeasType() const {
  if (!_record) {
    return "";
  }
  if (_record->measurement_type == eMeasurementType_PH) {
    return "pH";
  } else if (_record->measurement_type == eMeasurementType_Conductivity) {
    return "Conductivity";
  } else if (_record->measurement_type == eMeasurementType_Ion) {
    return "Ion";
  } else if (_record->measurement_type == eMeasurementType_Redox) {
    return "Redox";
  } else {
    return "";
  }
}
QString ContextGeneral::getMethodName() const {
  if (!_record) {
    return "";
  }
  return adapter::toQString(_record->method_name);
}

QString ContextGeneral::getAuthor() const {
  if (!_record) {
    return "";
  }
  return adapter::toQString(_record->author);
}

QString ContextGeneral::getCreateOn() const {
  if (!_record) {
    return "";
  }
  return adapter::toQString(_record->created_on.getDateTimeString());
}

QString ContextGeneral::getModifyOn() const {
  if (!_record) {
    return "";
  }
  return adapter::toQString(_record->modified_on.getDateTimeString());
}

QString ContextGeneral::getModifyBy() const {
  if (!_record) {
    return "";
  }
  return adapter::toQString(_record->modified_by);
}

bool ContextGeneral::getLockMethod() const {
  if (!_record) {
    return true;
  }
  return _record->locked_method;
}

QString ContextGeneral::getComment() const {
  if (!_record) {
    return "";
  }
  return adapter::toQString(_record->comment);
}

void ContextGeneral::setMethodName(const QString &method_name) {
  if (!_record) {
    return;
  }
  _record->method_name = adapter::toCStringex(method_name);
}

void ContextGeneral::setComment(const QString &comment) {
  if (!_record) {
    return;
  }
  _record->comment = adapter::toCStringex(comment);
}

void ContextGeneral::setLockMethod(const bool lock_method) {
  if (!_record) {
    return;
  }
  _record->locked_method = lock_method;
}

}  // namespace context
