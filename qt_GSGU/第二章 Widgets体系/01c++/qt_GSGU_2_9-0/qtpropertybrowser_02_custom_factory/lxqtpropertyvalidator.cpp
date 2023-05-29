#include "lxqtpropertyvalidator.h"

#include <QDebug>

// lxQtRegexValidator
lxQtRegexValidator::lxQtRegexValidator(QString regex, QObject* parent /*= nullptr*/)
	:m_strRegex(regex),lxQtAbstractValidator(parent)
{
	m_tRegValidator = new QRegExpValidator(QRegExp(regex), this);
}
bool lxQtRegexValidator::validate(QVariant data)
{
	QString strData = data.toString();
	int pos = 0;

	return m_tRegValidator->validate(strData,pos) == QValidator::Acceptable;
}

// lxQtMinValueValidator
lxQtMinValueValidator::lxQtMinValueValidator(double minValue, QObject* parent /*= nullptr*/)
	:m_dMinValue(minValue),lxQtAbstractValidator(parent)
{
}

bool lxQtMinValueValidator::validate(QVariant data)
{
	return data.toDouble() >= m_dMinValue;
}

// lxQtMaxValueValidator
lxQtMaxValueValidator::lxQtMaxValueValidator(double maxValue, QObject* parent /*= nullptr*/)
	:m_dMaxValue(maxValue),lxQtAbstractValidator(parent)
{
}

bool lxQtMaxValueValidator::validate(QVariant data)
{
	return data.toDouble() <= m_dMaxValue;
}
