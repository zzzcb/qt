#include <QString>
#include <QVariant>
#include <QRegExpValidator>

class lxQtAbstractValidator:public QObject
{
	Q_OBJECT
public:
	virtual bool validate(QVariant data) = 0;
protected:
	explicit lxQtAbstractValidator(QObject* parent=nullptr) {}
};

class lxQtRegexValidator :public lxQtAbstractValidator
{
public:
	explicit lxQtRegexValidator(QString regex, QObject* parent = nullptr);
	bool validate(QVariant data) override;
private:
	QString m_strRegex;
	QRegExpValidator* m_tRegValidator;
};

class lxQtMinValueValidator :public lxQtAbstractValidator
{
public:
	explicit lxQtMinValueValidator(double minValue, QObject* parent = nullptr);
	bool validate(QVariant data) override;
private:
	double m_dMinValue;
};

class lxQtMaxValueValidator :public lxQtAbstractValidator
{
public:
	explicit lxQtMaxValueValidator(double maxValue, QObject* parent = nullptr);
	bool validate(QVariant data) override;
private:
	double m_dMaxValue;
};
