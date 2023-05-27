#pragma once

#include <QProxyStyle>
#include <QPalette>

class QPainterPath;

class MyStyle : public QProxyStyle
{
    Q_OBJECT
public:
    MyStyle();

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                       QPainter *painter, const QWidget *widget) const override;
private:
	/** 将QRect处理成倒角样式的painter path */
	static QPainterPath processRect2ChamferPath(const QRect& rect, qreal xGap = 10, qreal yGap = 10);
};
