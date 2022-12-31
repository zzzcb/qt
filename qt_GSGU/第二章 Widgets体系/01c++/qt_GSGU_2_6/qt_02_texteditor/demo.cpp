#include "demo.h"

#include <QFile>
#include <QTextCodec>
#include <QTextEdit>
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QComboBox>
#include <QFontComboBox>
#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
{
    //ui.setupUi(this);	

	setWindowTitle(QCoreApplication::applicationName());

	m_pTextEdit = new QTextEdit(this);
	//connect(m_pTextEdit,&QTextEdit::currentCharFormatChanged,this,)
	//connect(m_pTextEdit,&QTextEdit::cursorPositionChanged,this,)

	setToolButtonStyle(Qt::ToolButtonFollowStyle);
	
	/**three menu,four toolbar*/
	setupFileAct();
	setupEditAct();
	setupTextFormatAct();
	setupTextFontAct();

	{
		QMenu *helpMenu = menuBar()->addMenu(tr("Help"));
		helpMenu->addAction(tr("About"), this, &Demo::about);
		helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
	}


	setCentralWidget(m_pTextEdit);
}

Demo::~Demo()
{}

bool Demo::load(const QString& fileName)
{
	/**文件操作:1,是否存在 2,是否打开成功*/
	if (!QFile::exists(fileName))
		return false;

	QFile file(fileName);
	if (!file.open(QFile::ReadOnly))
		return false;

	QByteArray data = file.readAll();
	QTextCodec *codec = QTextCodec::codecForHtml(data); ///< 获取html编码
	QString strHtml =  codec->toUnicode(data);          ///< 将data的编码变为unicode 
	 
	if (Qt::mightBeRichText(strHtml))					/// from QTextDocument defaine 
		m_pTextEdit->setHtml(strHtml);
	else
		m_pTextEdit->setPlainText(strHtml);

	setCurrentFileName(fileName);

	return true;
}

void Demo::newFile()
{
	qDebug() << "new file";
}

void Demo::openFile()
{
	qDebug() << "open file";
}

void Demo::saveFile()
{
	qDebug() << "save file";
}

void Demo::saveAsFile()
{
	qDebug() << "save as file";
}

void Demo::boldText()
{
	qDebug() << "boldText";
}

void Demo::italicText()
{
	qDebug() << "italicText";
}

void Demo::underlineText()
{
	qDebug() << "underlineText";
}

void Demo::textAlign(QAction *action)
{
	qDebug() << "textAlign " << action;
}

void Demo::colorText()
{
	qDebug() << "colorText ";
}

void Demo::textStyle(int styleIndex)
{
	qDebug() << "textStyle " << styleIndex;

}

void Demo::textFamily(const QString &family)
{
	qDebug() << "textFamily " << family;

}

void Demo::textSize(const QString &size)
{
	qDebug() << "textSize " << size;
}

void Demo::about()
{
	QMessageBox::about(this, tr("About"), tr("This example demonstrates Qt's "
		"rich text editing facilities in action, providing an example "
		"document for you to experiment with."));
}

void Demo::setupFileAct()
{
	QMenu* fileMenu = menuBar()->addMenu("&File");
	QToolBar* fileToolBar = addToolBar("File Tool Bar");

	/**new action*/
	/**使用标准的默认icon,如果没有再用自己的的图标 QIcon::fromTheme 主要是为linux服务,linux上提供了一套标准图标库 https://specifications.freedesktop.org/icon-naming-spec/latest/ar01s04.html*/
	const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/filenew.png"));
	QAction *action = fileMenu->addAction(newIcon, tr("&New"), this, &Demo::newFile);
	fileToolBar->addAction(action);
	action->setShortcut(QKeySequence::New);


	/**open action*/
	const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/fileopen.png"));
	action = fileMenu->addAction(openIcon, tr("&Open..."), this, &Demo::openFile);
	fileToolBar->addAction(action);
	action->setShortcut(QKeySequence::Open);

	fileMenu->addSeparator();

	/**save action*/
	const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/filesave.png"));
	action = fileMenu->addAction(saveIcon, tr("&Save..."), this, &Demo::saveFile);
	fileToolBar->addAction(action);
	action->setShortcut(QKeySequence::Save);
	action->setEnabled(false);

	/**save as action*/
	action = fileMenu->addAction(tr("&Save As..."), this, &Demo::saveAsFile);

	fileMenu->addSeparator();

	/**quit action*/
	action = fileMenu->addAction(tr("&Quit"), this, &QWidget::close);
	action->setShortcut(QKeySequence::Close);
}

void Demo::setupEditAct()
{
	QMenu* editMenu = menuBar()->addMenu("&Edit");
	QToolBar* editToolBar = addToolBar("Edit Tool Bar");

	/**cut action*/
	const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/editcut.png"));
	m_pCutAct = editMenu->addAction(cutIcon, tr("Cu&t"), m_pTextEdit,&QTextEdit::cut);
	editToolBar->addAction(m_pCutAct);
	m_pCutAct->setShortcut(QKeySequence::Cut);

	/**copy action*/
	const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon(":/images/editcopy.png"));
	m_pCopyAct = editMenu->addAction(copyIcon, tr("&Copy"), m_pTextEdit, &QTextEdit::copy);
	editToolBar->addAction(m_pCopyAct);
	m_pCopyAct->setShortcut(QKeySequence::Copy);

	/**paste action*/
	const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(":/images/editpaste.png"));
	m_pPasteAct = editMenu->addAction(pasteIcon, tr("&Paste"), m_pTextEdit, &QTextEdit::paste);
	editToolBar->addAction(m_pPasteAct);
	m_pPasteAct->setShortcut(QKeySequence::Paste);
	if (const QMimeData *md = QApplication::clipboard()->mimeData())
		m_pPasteAct->setEnabled(md->hasText());

}

void Demo::setupTextFormatAct()
{
	QMenu* formatMenu = menuBar()->addMenu("&Format");
	QToolBar* formatToolBar = addToolBar("Format Tool Bar");

	/**bold action*/
	/**italic action*/
	/**underline action*/

	/**left action*/
	/**center action*/
	/**right action*/

	/**color action*/

	/**---*/

	const QIcon boldIcon = QIcon::fromTheme("format-text-bold", QIcon(":images/textbold.png"));
	m_pTextBoldAct = formatMenu->addAction(boldIcon, tr("&Bold"), this, &Demo::boldText);
	m_pTextBoldAct->setShortcut(Qt::CTRL + Qt::Key_B);
	QFont bold;
	bold.setBold(true);
	m_pTextBoldAct->setFont(bold);
	formatToolBar->addAction(m_pTextBoldAct);
	m_pTextBoldAct->setCheckable(true);

	const QIcon italicIcon = QIcon::fromTheme("format-text-italic", QIcon(":images/textitalic.png"));
	m_pTextItalicAct = formatMenu->addAction(italicIcon, tr("&Italic"), this, &Demo::italicText);
	m_pTextItalicAct->setPriority(QAction::LowPriority);
	m_pTextItalicAct->setShortcut(Qt::CTRL + Qt::Key_I);
	QFont italic;
	italic.setItalic(true);
	m_pTextItalicAct->setFont(italic);
	formatToolBar->addAction(m_pTextItalicAct);
	m_pTextItalicAct->setCheckable(true);

	const QIcon underlineIcon = QIcon::fromTheme("format-text-underline", QIcon(":images/textunder.png"));
	m_pTextUnderlineAct = formatMenu->addAction(underlineIcon, tr("&Underline"), this, &Demo::underlineText);
	m_pTextUnderlineAct->setShortcut(Qt::CTRL + Qt::Key_U);
	m_pTextUnderlineAct->setPriority(QAction::LowPriority);
	QFont underline;
	underline.setUnderline(true);
	m_pTextUnderlineAct->setFont(underline);
	formatToolBar->addAction(m_pTextUnderlineAct);
	m_pTextUnderlineAct->setCheckable(true);

	formatMenu->addSeparator();

	/**---*/
	
	const QIcon leftIcon = QIcon::fromTheme("format-justify-left", QIcon(":images/textleft.png"));
	m_pAlignLeft = new QAction(leftIcon, tr("&Left"), this);
	m_pAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
	m_pAlignLeft->setCheckable(true);

	const QIcon centerIcon = QIcon::fromTheme("format-justify-center", QIcon(":images/textcenter.png"));
	m_pAlignCenter = new QAction(centerIcon, tr("C&enter"), this);
	m_pAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
	m_pAlignCenter->setCheckable(true);

	const QIcon rightIcon = QIcon::fromTheme("format-justify-right", QIcon(":images/textright.png"));
	m_pAlignRight = new QAction(rightIcon, tr("&Right"), this);
	m_pAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
	m_pAlignRight->setCheckable(true);

	// Make sure the alignLeft  is always left of the alignRight
	QActionGroup *alignGroup = new QActionGroup(this);
	connect(alignGroup, &QActionGroup::triggered, this, &Demo::textAlign);
	if (QApplication::isLeftToRight()) 
	{
		alignGroup->addAction(m_pAlignLeft);
		alignGroup->addAction(m_pAlignCenter);
		alignGroup->addAction(m_pAlignRight);
	}
	else 
	{
		alignGroup->addAction(m_pAlignRight);
		alignGroup->addAction(m_pAlignCenter);
		alignGroup->addAction(m_pAlignLeft);
	}
	formatMenu->addActions(alignGroup->actions());
	formatToolBar->addActions(alignGroup->actions());

	formatMenu->addSeparator();

	/**---*/
	QPixmap pix(16, 16);
	pix.fill(Qt::black);
	m_pColorText = formatMenu->addAction(pix, tr("&Color..."), this, &Demo::colorText);
	formatToolBar->addAction(m_pColorText);
}

void Demo::setupTextFontAct()
{
	QToolBar* fontToolBar = addToolBar("Font Tool Bar");

	fontToolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
	addToolBarBreak(Qt::TopToolBarArea);
	addToolBar(fontToolBar);

	m_pTextStyleComboBox = new QComboBox(fontToolBar);
	fontToolBar->addWidget(m_pTextStyleComboBox);
	m_pTextStyleComboBox->addItem("Standard");
	m_pTextStyleComboBox->addItem("Bullet List (Disc)");
	m_pTextStyleComboBox->addItem("Bullet List (Circle)");
	m_pTextStyleComboBox->addItem("Bullet List (Square)");
	m_pTextStyleComboBox->addItem("Ordered List (Decimal)");
	m_pTextStyleComboBox->addItem("Ordered List (Alpha lower)");
	m_pTextStyleComboBox->addItem("Ordered List (Alpha upper)");
	m_pTextStyleComboBox->addItem("Ordered List (Roman lower)");
	m_pTextStyleComboBox->addItem("Ordered List (Roman upper)");
	m_pTextStyleComboBox->addItem("Heading 1");
	m_pTextStyleComboBox->addItem("Heading 2");
	m_pTextStyleComboBox->addItem("Heading 3");
	m_pTextStyleComboBox->addItem("Heading 4");
	m_pTextStyleComboBox->addItem("Heading 5");
	m_pTextStyleComboBox->addItem("Heading 6");
	connect(m_pTextStyleComboBox, QOverload<int>::of(&QComboBox::activated), this, &Demo::textStyle);

	m_pFontComboBox = new QFontComboBox(fontToolBar);
	fontToolBar->addWidget(m_pFontComboBox);
	connect(m_pFontComboBox, QOverload<const QString &>::of(&QComboBox::activated), this, &Demo::textFamily);

	m_pFontSizeComboBox = new QComboBox(fontToolBar);
	m_pFontSizeComboBox->setObjectName("comboSize");
	fontToolBar->addWidget(m_pFontSizeComboBox);
	m_pFontSizeComboBox->setEditable(true);
	const QList<int> standardSizes = QFontDatabase::standardSizes();
	for (int size : standardSizes)
		m_pFontSizeComboBox->addItem(QString::number(size));
	m_pFontSizeComboBox->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));
	connect(m_pFontSizeComboBox, QOverload<const QString &>::of(&QComboBox::activated), this, &Demo::textSize);
}

void Demo::setCurrentFileName(const QString &fileName)
{
	m_strFileName = fileName;
	m_pTextEdit->document()->setModified(false);

	QString shownName;
	if (fileName.isEmpty())
		shownName = "untitled.txt";
	else
		shownName = QFileInfo(fileName).fileName();

	setWindowTitle(tr("%1[*] - %2").arg(shownName, QCoreApplication::applicationName()));
	setWindowModified(false);
}
