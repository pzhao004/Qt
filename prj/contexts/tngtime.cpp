#include <hmi/contexts/tngtime.h>

namespace context {
TngTime::TngTime(hmi::ContextManager& context_manager) : ContextBase("Context/Time.qml", context_manager) {
  _sectime = 0;
  t = new QTimer();
  connect(t, SIGNAL(timeout()), this, SLOT(setSectime()));
}

int TngTime::getSectime() const {
  // qDebug() << _sectime;
  return _sectime;
}
void TngTime::setSectime() {
  _sectime = _sectime + 1;
  emit sectimeChanged();
}
void TngTime::timeInitial() { t->start(1000); }
void TngTime::timeStop() {
  _sectime = 0;
  t->stop();
}

}  // namespace context
