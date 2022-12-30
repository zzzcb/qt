#pragma once

#include <QSplashScreen>

class SplashScreen : public QSplashScreen
{
	Q_OBJECT

public:
	SplashScreen(
		QPixmap pixmap = QPixmap(),
		QWidget *parent = nullptr);
	~SplashScreen();

	static void testThis();

	// 0-100
	void setProgress(double percent,int barHeight=10.0);

public slots:
	void showMessage(const QString &message, int alignment = Qt::AlignLeft, const QColor &color = Qt::black);

protected:
	void drawContents(QPainter *painter) override;

private:
	QRect	m_tRect;

	QString m_strMsg;
	QColor	m_tTextColor;
	int     m_nTextAlign;

	double  m_dPercent;
	int		m_dBarHeight;
};
