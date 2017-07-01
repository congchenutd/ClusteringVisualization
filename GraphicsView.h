#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGestureEvent>
#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget* parent = Q_NULLPTR);
    void zoomActual();

public slots:
    void zoomIn();
    void zoomOut();

protected:
    bool event(QEvent* event) override;

private:
    bool gestureEvent  (QGestureEvent* event);
    void pinchTriggered(QPinchGesture* gesture);
};

#endif // GRAPHICSVIEW_H
