
#include "SettingsScreen.h"
#include "FileUtils.h"

const uint16_t SettingsScreen::minTableSize{5}, SettingsScreen::maxTableSize{50};
const uint16_t SettingsScreen::minColumnLimit{20}, SettingsScreen::maxColumnLimit{100};
const uint16_t SettingsScreen::minBridgeLimit{20}, SettingsScreen::maxBridgeLimit{100};

SettingsScreen::SettingsScreen(IGameSettings& settings, QWidget* parent)
	: QWidget{parent}
	, m_gameSettings{settings}
	, m_layout{new QGridLayout{this}}
	, m_tableSizeSlider{new Slider{minTableSize, maxTableSize, this}}
	, m_columnLimitSlider{new Slider{minColumnLimit, maxColumnLimit, this}}
	, m_bridgeLimitSlider{new Slider{minBridgeLimit, maxBridgeLimit, this}}
	, m_firstPlayerName{new QLineEdit{this}}
	, m_secondPlayerName{new QLineEdit{this}}
	, m_firstPlayerColor{ new QComboBox{this} }
	, m_secondPlayerColor{ new QComboBox{this} }
{
	InitializeValues();
	InitializeLayout();

	auto stylesheet = FileUtils::StylesheetFileToString("stylesheets/settings.qss");
	setStyleSheet(stylesheet);
}

void SettingsScreen::AddFieldToLayout(QString fieldName, QWidget* widget)
{
	QLabel* fieldLabel = new QLabel(fieldName, this);

	if (widget)
	{
		fieldLabel->setObjectName("FieldText");
		m_layout->addWidget(fieldLabel, m_layout->rowCount(), 0, Qt::AlignLeft);
		m_layout->addWidget(widget, m_layout->rowCount() - 1, 1, Qt::AlignRight);

	}
	else
	{
		QString objectName = fieldName.isEmpty() ? "Empty" : "HeaderFieldText";
		fieldLabel->setObjectName(objectName);
		m_layout->addWidget(fieldLabel, m_layout->rowCount(), 0, Qt::AlignLeft);
	}
}

void SettingsScreen::InitializeValues()
{
	m_tableSizeSlider->SetValue(m_gameSettings.GetTableSize());
	m_columnLimitSlider->SetValue(m_gameSettings.GetColumnLimit());
	m_bridgeLimitSlider->SetValue(m_gameSettings.GetBridgeLimit());

	m_firstPlayerName->setText(QString::fromStdString(m_gameSettings.GetFirstPlayerName().data()));
	m_secondPlayerName->setText(QString::fromStdString(m_gameSettings.GetSecondPlayerName().data()));
}

void SettingsScreen::InitializeLayout()
{
	// Player settings related widgets
	AddFieldToLayout("");
	AddFieldToLayout("First Player Settings");
	AddFieldToLayout("Name", m_firstPlayerName);
	AddFieldToLayout("Color", m_firstPlayerColor);
	AddFieldToLayout("");
	AddFieldToLayout("Second Player Settings");
	AddFieldToLayout("Name", m_secondPlayerName);
	AddFieldToLayout("Color", m_secondPlayerColor);
	AddFieldToLayout("");

	// Board settings related widgets
	AddFieldToLayout("Board settings");
	AddFieldToLayout("Table Size", m_tableSizeSlider);
	AddFieldToLayout("Pillars Number", m_columnLimitSlider);
	AddFieldToLayout("Bridges Number", m_bridgeLimitSlider);
	AddFieldToLayout("");

	setLayout(m_layout);



}