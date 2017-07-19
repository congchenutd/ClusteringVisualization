#include "GraphicsView.h"
#include <QDebug>

GraphicsView::GraphicsView(QWidget* parent)
    : QGraphicsView (parent)
{
    grabGesture(Qt::PinchGesture);
}

void GraphicsView::zoomIn() {
    scale(1.1, 1.1);
}

void GraphicsView::zoomOut() {
    scale(0.9, 0.9);
}

void GraphicsView::zoomActual() {
    resetMatrix();
}

bool GraphicsView::event(QEvent* event)
{
    if (event->type() == QEvent::Gesture)
        return gestureEvent(static_cast<QGestureEvent*>(event));
    return QGraphicsView::event(event);
}

bool GraphicsView::gestureEvent(QGestureEvent* event)
{
    if (QGesture* pinch = event->gesture(Qt::PinchGesture))
        pinchTriggered(static_cast<QPinchGesture*>(pinch));
    return true;
}

void GraphicsView::pinchTriggered(QPinchGesture* gesture)
{
    if (gesture->changeFlags() & QPinchGesture::ScaleFactorChanged)
        scale(gesture->scaleFactor(), gesture->scaleFactor());
}
