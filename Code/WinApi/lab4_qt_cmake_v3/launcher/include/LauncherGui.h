#pragma once
#include "ui_LauncherGui.h"

class Launcher;

class LauncherGui : public QMainWindow
{
	Q_OBJECT
public:
	LauncherGui(QWidget * parent = nullptr);
	~LauncherGui();

private slots:
	void OnButtonClick();
	void OnTick();

private:
	enum class LogMessageType
	{
		LM_ERROR,
		LM_TEXT
	};
	void LogMessage(const string & message, LogMessageType type = LogMessageType::LM_TEXT);

	void OnPause();
	void OnContinue();
	int GetMaxChildrenNumber() const;

	unique_ptr<Launcher>		m_launcher;
	QPointer<QTimer>			m_timer;
	bool						m_onPause {false};

	Ui::LauncherGui				m_ui;
};