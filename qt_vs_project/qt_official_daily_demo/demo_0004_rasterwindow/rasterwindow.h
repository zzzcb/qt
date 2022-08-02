#pragma once

#include <QWindow>
#include <QBackingStore>  // 与之对应的是:QOpenGLContext

class RasterWindow  : public QWindow
{
	Q_OBJECT

public:
	explicit RasterWindow(QWindow *parent=nullptr);
	~RasterWindow();

protected:
	void exposeEvent(QExposeEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;

private:
	QBackingStore * mp_backingStore;

	void renderNow();
	void render(QPainter *painter);


};
