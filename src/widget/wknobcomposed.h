#ifndef WKNOBCOMPOSED_H
#define WKNOBCOMPOSED_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QWheelEvent>

#include "skin/skincontext.h"
#include "util/timer.h"
#include "widget/wwidget.h"
#include "widget/knobeventhandler.h"
#include "widget/wpixmapstore.h"
#include "widget/wimagestore.h"

// This is used for knobs, if the knob value can be displayed
// by rotating a single SVG image.
// For more complex transitions you may consider to use
// WEffectParameterKnob, which displays one of e.g. 64
// pixmaps.
class WKnobComposed : public WWidget {
    Q_OBJECT
  public:
    explicit WKnobComposed(QWidget* pParent=nullptr);

    void setup(const QDomNode& node, const SkinContext& context);

    void onConnectedControlChanged(double dParameter, double dValue) override;

  protected:
    void wheelEvent(QWheelEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void paintEvent(QPaintEvent* /*unused*/) override;

  private slots:
    void guiTick();

  private:
    void inputActivity();
    void clear();
    void setPixmapBackground(
            PixmapSource source,
            Paintable::DrawMode mode,
            double scaleFactor);
    void setPixmapKnob(
            PixmapSource source,
            Paintable::DrawMode mode,
            double scaleFactor);

    double m_dCurrentAngle;
    PaintablePointer m_pKnob;
    PaintablePointer m_pPixmapBack;
    KnobEventHandler<WKnobComposed> m_handler;
    double m_dMinAngle;
    double m_dMaxAngle;
    double m_dKnobCenterXOffset;
    double m_dKnobCenterYOffset;
    GuiTickTimer m_guiTickTimer;
    mixxx::Duration m_lastActivity;
    mixxx::Duration m_lastRender;

    friend class KnobEventHandler<WKnobComposed>;
};

#endif /* WKNOBCOMPOSED_H */
