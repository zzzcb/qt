#include "demo.h"

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	connect(ui.redSlider, &QSlider::valueChanged, this, &Demo::on_slider_valueChanged);
	connect(ui.greenSlider, &QSlider::valueChanged, this, &Demo::on_slider_valueChanged);
	connect(ui.blueSlider , &QSlider::valueChanged, this, &Demo::on_slider_valueChanged);
	connect(ui.alphaSlider, &QSlider::valueChanged, this, &Demo::on_slider_valueChanged);
}

void Demo::on_slider_valueChanged()
{
	QColor color;
	color.setRgb(ui.redSlider->value(),ui.greenSlider->value(),ui.blueSlider->value(),ui.alphaSlider->value());

	QPalette pal = ui.colorDisplay->palette();
	pal.setColor(QPalette::Base, color);
	ui.colorDisplay->setPalette(pal);
}

void Demo::on_verticalSlider_3_valueChanged()
{
	ui.verticalScrollBar_2->setValue(ui.verticalSlider_3->value());
	ui.progressBar_2->setValue(ui.verticalSlider_3->value());
}

void Demo::on_dial_valueChanged()
{
	QLCDNumber::Mode mode;
	if (ui.radioButton->isChecked())
	{
		mode = QLCDNumber::Dec;
	}
	else if (ui.radioButton_2->isChecked())
	{
		mode = QLCDNumber::Bin;
	}
	else if (ui.radioButton_3->isChecked())
	{
		mode = QLCDNumber::Oct;
	}
	else if (ui.radioButton_4->isChecked())
	{
		mode = QLCDNumber::Hex;
	}
	else
	{
		mode = QLCDNumber::Dec;
	}
	ui.lcdNumber->setMode(mode);

	ui.lcdNumber->display(ui.dial->value());
}
