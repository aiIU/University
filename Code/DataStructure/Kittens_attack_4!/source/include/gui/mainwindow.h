#pragma once

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget * parent = nullptr);
	~MainWindow();

	// Создаем два графика из указанных данных xValues и yValues
	void CreateChart(const wstring& name, const wstring& desc, const vector<double> & xValues, const vector<double> & yValues);
	
	// Показываем выбранный график
	void ShowChart(const wstring& name);
	
private:
	QChartView * CreateChartImpl(const vector<double>& xValues, const vector<double>& yValues, bool logarithmicScales);
	
	Ui::MainWindow					ui;
	unique_ptr<std::stringbuf>		m_bufferInsert;
	unique_ptr<std::stringbuf>		m_bufferRemove;
	map<wstring, int>				m_charts;
	std::streambuf *				m_oldCout;
	std::streambuf *				m_oldCerr;
};
