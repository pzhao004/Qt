

#include "hmi/contexts/contextkeyevent.h"
#include <QDebug>

namespace hmi {
ContextKeyEvent::ContextKeyEvent(QObject *parent, hmi::ContextManager &context_manager)
    : CompoundControllerBase(parent, context_manager) {}

void ContextKeyEvent::startupDone() {}
bool ContextKeyEvent::eventFilter(QObject *watched, QEvent *event) {
  if (event->type() == QEvent::Move) {
    emit sScreenMoving();
  }
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyEvent->key() == Qt::Key_Home) {
      // qDebug() << "home key press event....";
      emit sKeyHomePress();
      return true;
    }
  }
  if (event->type() == QEvent::KeyRelease) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyEvent->key() == Qt::Key_Home) {
      // qDebug() << "home key release event....";
      emit sKeyHomeRelease();
      return true;
    }
  }
  return QObject::eventFilter(watched, event);
}
}  // namespace hmi
