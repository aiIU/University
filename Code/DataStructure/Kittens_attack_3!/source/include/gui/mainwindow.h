#pragma once

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget * parent = nullptr);

	// Создаем два графика из указанных данных xValues и yValues
	void CreateChart(const wstring& name, const vector<double> & xValues, const vector<double> & yValues);
	
	// Показываем выбранный график
	void ShowChart(const wstring& name);
private:
	QChartView * CreateChartImpl(const vector<double>& xValues, const vector<double>& yValues, bool logarithmicScales);
	
	map<wstring, int>	m_charts;
	Ui::MainWindow				ui;
};
