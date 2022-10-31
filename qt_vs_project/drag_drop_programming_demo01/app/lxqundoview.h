#ifndef LX_QUNDOVIEW_H
#define LX_QUNDOVIEW_H

#include <QUndoView>

class lxQUndoView :public QUndoView
{
	Q_OBJECT
public:
	lxQUndoView(QWidget *parent = nullptr);
	~lxQUndoView();

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

private:

};


#endif


