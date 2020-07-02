
#include "hmi/contexts/contextsample.h"
#include <QDebug>

namespace context {

ContextSample::ContextSample(hmi::ContextManager &context_manager) : _context_manager(context_manager) {}

ContextSample::~ContextSample() {}

void ContextSample::updateRecord(MFSampleRecord *record) { _record = record; }

void ContextSample::releaseRecord() { _record = nullptr; }

QString ContextSample::getSampleID() const {
  if (_index == 0) {
    return "202006010000";
  } else if (_index == 1) {
    return "202006010001";
  } else if (_index == 2) {
    return "202006010002";
  } else if (_index == 3) {
    return "202006010003";
  } else {
    return "";
  }
}
bool ContextSample::getSequential() const { return false; }
QString ContextSample::getComment() const {
  if (_index == 0) {
    return "Not define 1";
  } else if (_index == 1) {
    return "Not define 2";
  } else if (_index == 2) {
    return "Not define 3";
  } else if (_index == 3) {
    return "Not define 4";
  } else {
    return "Not define 5";
  }
}
void ContextSample::sampleID_set(QString value) {
  if (_index == 0) {
    _sample_id_ph = value;
  } else if (_index == 1) {
    _sample_id_cond = value;
  } else if (_index == 2) {
    _sample_id_ion = value;
  } else if (_index == 3) {
    _sample_id_redox = value;
  } else {
  }
  emit sampleIDChanged();
}
void ContextSample::autoSequential_set(bool value) {
  if (_index == 0) {
    _auto_sequential_ph = value;
  } else if (_index == 1) {
    _auto_sequential_cond = value;
  } else if (_index == 2) {
    _auto_sequential_ion = value;
  } else if (_index == 3) {
    _auto_sequential_redox = value;
  } else {
  }
  emit sequentialChanged();
}
void ContextSample::comment_set(QString value) {
  if (_index == 0) {
    _commont_ph = value;
  } else if (_index == 1) {
    _commont_cond = value;
  } else if (_index == 2) {
    _commont_ion = value;
  } else if (_index == 3) {
    _commont_redox = value;
  } else {
  }
  emit commentChanged();
}

}  // namespace context
