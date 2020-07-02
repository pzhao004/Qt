

#include "hmi/contexts/contextreport.h"

namespace context {

ContextReport::ContextReport(hmi::ContextManager& context_manager) : _context_manager(context_manager) {
  _print_enable = false;
  _print_format = 0;
}

ContextReport::~ContextReport() {}

void ContextReport::updateRecord(MFReportRecord* record) { _record = record; }

void ContextReport::releaseRecord() {}

bool ContextReport::getPrintEnable() const { return _print_enable; }
int ContextReport::getPrintFormat() const { return _print_format; }

void ContextReport::printEnable_set(bool value) {
  if (value != _print_enable) {
    _print_enable = value;
    emit printEnableChanged();
  }
}

void ContextReport::printFormat_set(int value) {
  if (value != _print_format) {
    _print_format = value;
    emit printFormatChanged();
  }
}
}  // namespace context
