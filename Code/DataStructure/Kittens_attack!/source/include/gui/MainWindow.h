#pragma once

#include "ui_MainWindow.h"
#include "Stack.h"
#include "List.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget * parent = nullptr);

	void Initialize(const string & filename);
	
private slots:
	// Функции-слоты, в которые попадают сигналы из гуи:
	// при нажатии на "вставить..."
	void InsertToBegin();
	void InsertByIndex();
	void InsertToEnd();

	// при нажатии на "удалить..."
	void RemoveFromBegin();
	void RemoveByIndex();
	void RemoveFromEnd();

	// при нажатии на "очистить"
	// Запускает соответствующую реакцию коту и очищает таблицу
	void Clear();

	// при нажатии на "найти элемент"
	// Запускает соответствующую реакцию коту и очищает таблицу
	void GetPosition();

	// при нажатии на "опции" -> "выбрать контейнер..." -> "список"
	void OnChooseList();

	// при нажатии на "опции" -> "выбрать контейнер..." -> "стек"
	void OnChooseStack();

	// при нажатии на "опции" -> "спрака от Жорика"
	void OnHelpRequest();

	// При срабатывании таймера на бездействие
	void OnInactionTimer();
private:
	// Конвертирует введенный текст в поле ввода (для вставки) в соответствующий для выбранного контейнера тип данных
	// если данные не соответствуют требуемому типу, то возвращается false
	bool GetDataForList(const QString & input, List::data_t & out) const;
	bool GetDataForStack(const QString & input, Stack::data_t & out) const;

	// Возвращает индекс элемента для удаления, который ввёл пользователь
	// если пользователь не ввёл значение, возвращается -1
	int GetEditRemoveIndex() const;
	
	// Возвращает индекс элемента для вставки, который ввёл пользователь
	// если пользователь не ввёл значение, возвращается -1
	int GetEditInsertIndex() const;

	// Сам процесс вставки значения в выбранный контейнер
	// Выполняет всевозможные проверки и запускает соответствующую реакцию коту
	void _InsertByIndex(int index);

	// Сам процесс удаления значения из выбранного контейнера
	// Выполняет всевозможные проверки и запускает соответствующую реакцию коту
	void _RemoveByIndex(int index);
	
	Ui::MainWindow		ui;
	bool				m_isListChosen = true;
	Stack				m_stack;
	List				m_list;
	
	QPointer<QTimer>	m_inactionTimer;
	int					m_inactionCounter = 0; // счётчик срабатываний подряд таймера по бездействию
	
	bool				m_helpOpennedOnce = false;
};
