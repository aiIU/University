#include "pch.h"

#include "gui/MainWindow.h"

#include <QFont>
#include <QFontDataBase>
#include <iomanip>
#include <sstream>

class TextRedirect : public std::basic_stringbuf<char>
{
public:
	TextRedirect(QTextEdit * listWidget)
		: m_textEdit(listWidget)
	{}

	int sync() override
	{
		auto && temp = str();
		auto data = QString::fromStdString(temp);
		m_textEdit->setText(data);
		return 0;
	}
	
private:
	QTextEdit *		m_textEdit;
};

MainWindow::MainWindow(QWidget * parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QFont font("Monospace");
	font.setStyleHint(QFont::TypeWriter);
	ui.textInsertionInfo->setFont(font);
	ui.textRemovingInfo->setFont(font);
	
	m_bufferInsert = make_unique<TextRedirect>(ui.textInsertionInfo);
	m_bufferRemove = make_unique<TextRedirect>(ui.textRemovingInfo);
	
	m_oldCout = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(m_bufferInsert.get());
	
	m_oldCerr = std::cerr.rdbuf(); //save old buf
	std::cerr.rdbuf(m_bufferRemove.get());
}

MainWindow::~MainWindow()
{
	std::cout.rdbuf(m_oldCout);
	std::cerr.rdbuf(m_oldCerr);
}

void MainWindow::CreateChart(const wstring & name, const wstring& desc, const vector<double>& xValues, const vector<double>& yValues)
{
	if (m_charts.find(name) != m_charts.end())
	{		
		auto _name = QString::fromStdWString(name).toStdString();
		std::cerr << "Attempting to create chart " << _name << " again!";
		return;
	}
	
	if (xValues.size() != yValues.size() || xValues.empty())
	{
		auto _name = QString::fromStdWString(name).toStdString();
		std::cerr << "Cannot create chart " << _name << " from invalid values!";
		return;
	}

	auto defaultScales = CreateChartImpl(xValues, yValues, false);
	defaultScales->chart()->setTitle(QString::fromStdWString(desc));
	
	//auto logScales = CreateChartImpl(xValues, yValues, true);
	//logScales->chart()->setTitle(u8"Логарифмические оси");

	//auto stub = new QWidget(this);
	//auto layout = new QHBoxLayout(stub);
	//layout->addWidget(defaultScales);
	//layout->addWidget(logScales);
	
	ui.tabWidget->addTab(defaultScales, QString::fromStdWString(name));
	m_charts[name] = ui.tabWidget->count();
}

void MainWindow::ShowChart(const wstring & name)
{
	auto it = m_charts.find(name);
	if (it != m_charts.end())
	{
		ui.tabWidget->setCurrentIndex(it->second);
	}
	else
	{
		auto _name = QString::fromStdWString(name).toStdString();
		std::cerr << "Cannot show unexisting chart " << _name << "!";
	}
}

QChartView* MainWindow::CreateChartImpl(const vector<double>& xValues, const vector<double>& yValues, bool logarithmicScales)
{
	auto chart = new QChart();
	auto serials = new QLineSeries(this);
	for (int i = 0; i < xValues.size(); ++i)
	{
		double _x = xValues[i];
		double _y = yValues[i];
		if (logarithmicScales)
		{
			_x = _x > 0 ? std::log2(_x) : 0;
			_y = _y > 0 ? std::log2(_y) : 0;
		}		
		serials->append(_x, _y);
	}
	chart->addSeries(serials);
	chart->createDefaultAxes();

	{
		auto [minIt, maxIt] = std::minmax_element(xValues.begin(), xValues.end());
		double min = std::min(*minIt, 0.0);
		double max = *maxIt;
		if (logarithmicScales)
		{
			min = min > 0 ? std::log2(min) : 0;
			max = max > 0 ? std::log2(max) : 0;
		}
		chart->axes(Qt::Horizontal).first()->setRange(min, max);	
	}

	{
		auto [minIt, maxIt] = std::minmax_element(yValues.begin(), yValues.end());
		double min = std::min(*minIt, 0.0);
		double max = *maxIt;
		if (logarithmicScales)
		{
			min = min > 0 ? std::log2(min) : 0;
			max = max > 0 ? std::log2(max) : 0;
		}
		chart->axes(Qt::Vertical).first()->setRange(min, max);
	}
	
	if (chart->legend()->markers(serials).size() == 1)
	{
		chart->legend()->setVisible(false);
	}
	
	auto chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
	
	return chartView;
}
