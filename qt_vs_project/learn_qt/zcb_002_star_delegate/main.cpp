#include <QApplication>
#include <QTableWidget>
#include <QHeaderView>

#include "stardelegate.h"
#include "stareditor.h"
#include "starrating.h"

void populateTableWidget(QTableWidget *tableWidget)
{
	static constexpr struct {
		const char *title;
		const char *genre;
		const char *artist;
		int rating;
	} staticData[] = {
			{ "Mass in B-Minor", "Baroque", "J.S. Bach", 5 },
			{ "Three More Foxes", "Jazz", "Maynard Ferguson", 4 },
			{ "Sex Bomb", "Pop", "Tom Jones", 3 },
			{ "Barbie Girl", "Pop", "Aqua", 5 },
			{ nullptr, nullptr, nullptr, 0 }
	};

	for (int row = 0; staticData[row].title != nullptr; ++row) {
		QTableWidgetItem *item0 = new QTableWidgetItem(staticData[row].title);
		QTableWidgetItem *item1 = new QTableWidgetItem(staticData[row].genre);
		QTableWidgetItem *item2 = new QTableWidgetItem(staticData[row].artist);
		QTableWidgetItem *item3 = new QTableWidgetItem;
		item3->setData(0,
			QVariant::fromValue(StarRating(staticData[row].rating)));

		tableWidget->setItem(row, 0, item0);
		tableWidget->setItem(row, 1, item1);
		tableWidget->setItem(row, 2, item2);
		tableWidget->setItem(row, 3, item3);
	}
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QTableWidget tableWidget(4, 4);
	tableWidget.setItemDelegate(new StarDelegate);
	tableWidget.setEditTriggers(QAbstractItemView::DoubleClicked
		| QAbstractItemView::SelectedClicked);
	tableWidget.setSelectionBehavior(QAbstractItemView::SelectRows);
	tableWidget.setHorizontalHeaderLabels({ "Title", "Genre", "Artist", "Rating" });

	populateTableWidget(&tableWidget);

	tableWidget.resizeColumnsToContents();
	tableWidget.resize(500, 300);
	//tableWidget.verticalHeader()->setDefaultSectionSize(100);
	tableWidget.show();


	return app.exec();
}
