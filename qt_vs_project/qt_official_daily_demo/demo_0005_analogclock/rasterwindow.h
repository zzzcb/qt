#pragma once

#include <QWindow>
#include <QBackingStore>  // 与之对应的是:QOpenGLContext

class RasterWindow  : public QWindow
{
	Q_OBJECT

public:
	explicit RasterWindow(QWindow *parent=nullptr);
	~RasterWindow();

	virtual void render(QPainter *painter);
	void renderLater();  	// 稍后 渲染

protected:
	void exposeEvent(QExposeEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;

	bool event(QEvent* event) override;

private:
	QBackingStore * mp_backingStore;

	void renderNow();
};
