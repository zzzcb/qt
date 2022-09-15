#include "stareditor.h"
#include "starrating.h"

#include <QtWidgets>
#include "qdebug.h"

StarEditor::StarEditor(QWidget *parent)
	: QWidget(parent)
{
	setMouseTracking(true);
	setAutoFillBackground(true);
}

QSize StarEditor::sizeHint() const
{
	return myStarRating.sizeHint();
}

void StarEditor::paintEvent(QPaintEvent *)
{
	qDebug() << "stareditor paintEvent ... ";

	QPainter painter(this);
	myStarRating.paint(&painter, rect(), palette(),
		StarRating::EditMode::Editable);
}

void StarEditor::mouseMoveEvent(QMouseEvent *event)
{
	qDebug() << "mouse move event ...";

	const int star = starAtPosition(event->x());

	if (star != myStarRating.starCount() && star != -1) {
		myStarRating.setStarCount(star);
		update();
	}
	QWidget::mouseMoveEvent(event); // 一波操作后  还是使用父类的方法 
}

void StarEditor::mouseReleaseEvent(QMouseEvent *event)
{
	qDebug() << "mouse release event ...";

	emit editingFinished();
	QWidget::mouseReleaseEvent(event); // 一波操作后  还是使用父类的方法 
}

int StarEditor::starAtPosition(int x) const
{
	const int star = (x / (myStarRating.sizeHint().width()
		/ myStarRating.maxStarCount())) + 1;
	if (star <= 0 || star > myStarRating.maxStarCount())
		return -1;
	
	return star;
}
