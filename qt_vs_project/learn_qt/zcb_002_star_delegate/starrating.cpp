#include "starrating.h"
#include <cmath>
#include "qdebug.h"

StarRating::StarRating(int starCount, int maxStarCount)
	: myStarCount(starCount),
	myMaxStarCount(maxStarCount)
{
	starPolygon << QPointF(1.0, 0.5);
	for (int i = 1; i < 5; ++i)
		starPolygon << QPointF(0.5 + 0.5 * std::cos(1.2 * i * 3.14),
			0.5 + 0.5 * std::sin(1.2 * i * 3.14));

	diamondPolygon << QPointF(0.4, 0.5) << QPointF(0.5, 0.4)
		<< QPointF(0.6, 0.5) << QPointF(0.5, 0.6);
}

QSize StarRating::sizeHint() const
{
	return  20*QSize(myMaxStarCount,1);  // 好像改变 height 无效 
}

void StarRating::paint(QPainter *painter, const QRect &rect,
	const QPalette &palette, EditMode mode) const
{
	painter->save();

	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setPen(Qt::NoPen);
	painter->setBrush(mode == EditMode::Editable ?
		palette.highlight() :
		palette.windowText());

	painter->translate(rect.x(), rect.y()+(rect.height()/2 - 20.0/2) );
	painter->scale(20,20);

	for (int i = 0; i < myMaxStarCount; ++i) {
		if (i < myStarCount)
			painter->drawPolygon(starPolygon,Qt::WindingFill);
		else if (mode == EditMode::Editable)
			painter->drawPolygon(diamondPolygon, Qt::WindingFill);
		painter->translate(1.0, 0.0);
	}

	painter->restore();
}
