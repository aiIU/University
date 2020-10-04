#include "pch.h"

#include "gui/MainWindow.h"
#include "gui/CatReaction.h"

#include <QDebug>
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget * parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/icon.png"));

	m_inactionTimer = new QTimer(this);
	m_inactionTimer->setInterval(15'000); // 10 секунд
	connect(m_inactionTimer, &QTimer::timeout, this, &MainWindow::OnInactionTimer);
	connect(ui.helpRequest, &QAction::triggered, this, &MainWindow::OnHelpRequest);
		
	connect(ui.chooseList, &QAction::triggered, this, &MainWindow::OnChooseList);
	connect(ui.chooseStack, &QAction::triggered, this, &MainWindow::OnChooseStack);
	
	connect(ui.insertBegin, &QPushButton::clicked, this, &MainWindow::InsertToBegin);
	connect(ui.insertIndex, &QPushButton::clicked, this, &MainWindow::InsertByIndex);
	connect(ui.insertEnd, &QPushButton::clicked, this, &MainWindow::InsertToEnd);
	
	connect(ui.removeBegin, &QPushButton::clicked, this, &MainWindow::RemoveFromBegin);
	connect(ui.removeIndex, &QPushButton::clicked, this, &MainWindow::RemoveByIndex);
	connect(ui.removeEnd, &QPushButton::clicked, this, &MainWindow::RemoveFromEnd);
	connect(ui.clearContainer, &QPushButton::clicked, this, &MainWindow::Clear);

	connect(ui.searchValue, &QPushButton::clicked, this, &MainWindow::GetPosition);
}

void MainWindow::Initialize(const string& filename)
{
	ui.catHelper->Load(filename);
	
	// по умолчанию устанавливаем выбранным контейнером - список, - и приветствие для кота
	ui.chooseList->trigger();
	ui.catHelper->SetReaction(CatReaction::Event::FIRST_MEETING);
	
	// Запускаем таймер, который отмеряет секунды бездействия
	m_inactionTimer->start();
}

void MainWindow::InsertToBegin()
{
	_InsertByIndex(0);
}

void MainWindow::InsertByIndex()
{
	_InsertByIndex(GetEditInsertIndex());
}

void MainWindow::InsertToEnd()
{
	int lastIndex;
	if (m_isListChosen)
	{
		lastIndex = m_list.Size();
	}
	else
	{
		lastIndex = m_stack.Size();
	}

	_InsertByIndex(lastIndex);
}

void MainWindow::RemoveFromBegin()
{
	_RemoveByIndex(0);
}

void MainWindow::RemoveByIndex()
{
	_RemoveByIndex(GetEditRemoveIndex());
}

void MainWindow::RemoveFromEnd()
{
	int lastIndex;
	if (m_isListChosen)
	{
		lastIndex = m_list.Size();
	}
	else
	{
		lastIndex = m_stack.Size();
	}

	_RemoveByIndex(lastIndex - 1);
}

void MainWindow::Clear()
{
	// перезапускаем таймер сначала при любом действии
	m_inactionTimer->start();
	m_inactionCounter = 0;
	
	if (m_isListChosen)
	{
		m_list.Clear();
	}
	else
	{
		m_stack.Clear();
	}
	ui.table->clear();
}

void MainWindow::GetPosition()
{
	// перезапускаем таймер сначала при любом действии
	m_inactionTimer->start();
	m_inactionCounter = 0;
	
	CatReaction reaction;
	
	// Очищаем поле для результата (фраза "элемент найден..." или "элемент не найден")
	ui.searchResult->clear();

	// Получаем значение, которое нужно найти, введённое пользователем
	QString valueToSearchFromEdit = ui.editSearchValue->text();
	if (m_isListChosen)
	{
		List::data_t data;
		if (GetDataForList(valueToSearchFromEdit, data))
		{
			int pos = m_list.GetPosition(data);
			if (pos != -1)
			{
				qDebug() << "List: Element was successfully found!";
				
				ui.searchResult->setText(QString::fromStdWString(L"Индекс искомого элемента %1.").arg(pos));
				
				reaction = CatReaction(
					CatReaction::ContainerType::LIST,
					CatReaction::Event::SEACH,
					CatReaction::Result::SUCCESSED
				);
			}
			else
			{
				ui.searchResult->setText(QString::fromStdWString(L"Элемент не найден."));
				
				qDebug() << "List: Element was not found!";
				
				reaction = CatReaction(
					CatReaction::ContainerType::LIST,
					CatReaction::Event::SEACH,
					CatReaction::Result::FAILED
				);
			}
		}
		else
		{
			qDebug() << "List: Trying to find wrong element.";
			reaction = CatReaction(
				CatReaction::ContainerType::LIST,
				CatReaction::Event::INVALID_DATA
			);
		}
	}
	else
	{
		Stack::data_t data;
		if (GetDataForStack(valueToSearchFromEdit, data))
		{
			if (m_stack.Top() == data)
			{
				ui.searchResult->setText(QString::fromStdWString(L"Искомый элемент на вершине стека!"));
				
				qDebug() << "Stack: Element was found on top!";

				reaction = CatReaction(
					CatReaction::ContainerType::STACK,
					CatReaction::Event::SEACH,
					CatReaction::Result::SUCCESSED
				);
			}
			else
			{
				ui.searchResult->setText(QString::fromStdWString(L"Искомый элемент не на вершине стека!"));
				
				qDebug() << "Stack: Element was not found on top! Cannot check other elements in stack!";
				
				reaction = CatReaction(
					CatReaction::ContainerType::STACK,
					CatReaction::Event::SEACH,
					CatReaction::Result::IMPOSIBLE
				);
			}
		}
		else
		{
			qDebug() << "Stack: Trying to find wrong data.";
			
			reaction = CatReaction(
				CatReaction::ContainerType::STACK,
				CatReaction::Event::INVALID_DATA
			);
		}
	}

	ui.catHelper->SetReaction(reaction);
}

void MainWindow::OnChooseList()
{
	// перезапускаем таймер сначала при любом действии
	m_inactionTimer->start();
	m_inactionCounter = 0;
	
	m_isListChosen = true;
	ui.groupBox->setTitle(QString::fromStdWString(L"Список"));
	ui.chooseList->setChecked(true);
	ui.chooseStack->setChecked(false);

	// перезаписываем содержимое таблицы, в которой могло быть записано содержимое списка
	ui.table->setRowCount(0);
	ui.table->setRowCount(m_list.Size());
	for (int i = 0; i < m_list.Size(); ++i)
	{
		// создаём первую ячейку в новой строке - индекс элемента
		auto item = new QTableWidgetItem(QString("%1").arg(i));
		ui.table->setItem(i, 0, item);
		item->setTextAlignment(Qt::AlignCenter);
		
		// создаём вторую ячейку в новой строке - значение элемента из списка по индексу i	
		auto value = m_list.Get(i);
		item = new QTableWidgetItem(QString::fromStdWString(std::wstring(1, value)));
		ui.table->setItem(i, 1, item);
		item->setTextAlignment(Qt::AlignCenter);
	}
}

void MainWindow::OnChooseStack()
{
	// перезапускаем таймер с начала при любом действии
	m_inactionTimer->start();
	m_inactionCounter = 0;
	
	m_isListChosen = false;
	ui.groupBox->setTitle(QString::fromStdWString(L"Стек"));
	ui.chooseList->setChecked(false);
	ui.chooseStack->setChecked(true);

	// перезаписываем содержимое таблицы, в которой могло быть записано содержимое списка
	ui.table->setRowCount(0);
	ui.table->setRowCount(m_stack.Size());

	// копируем стек, чтобы копию можно было опустошить по мере заполнения таблицы
	auto temp = m_stack;

	// 1. Достаем с копии стека верхний элемент
	// 2. Кладём его в начало таблицы
	int i = 0;
	while (temp.Size() > 0)
	{
		// Создаём первую ячейку для новой строки и записываем туда индекс, отсчитывая его с конца
		auto item = new QTableWidgetItem(QString("%1").arg(m_stack.Size() - i - 1));
		ui.table->setItem(i, 0, item);			
		item->setTextAlignment(Qt::AlignCenter);
		
		// создаём вторую ячейку в новой строке - значение с вершины стека
		auto topValue = temp.Top();
		temp.Pop();		
		item = new QTableWidgetItem(QString("%1").arg(topValue));
		ui.table->setItem(i, 1, item);
		item->setTextAlignment(Qt::AlignCenter);
		++i;
	}
}

void MainWindow::OnHelpRequest()
{	
	m_inactionTimer->stop();
	
	if (m_helpOpennedOnce)
	{
		ui.catHelper->SetReaction(CatReaction::Event::HELP_READING_START_N);
	}
	else
	{
		ui.catHelper->SetReaction(CatReaction::Event::HELP_READING_START);
	}
	
	
	auto text =	
L"Стек (англ. stack — стопка; читается стэк) — абстрактный тип данных, представляющий собой список элементов, организованных по принципу LIFO (англ. last in — first out, «последним пришёл — первым вышел»).\n\
Стек состоит из ячеек(в примере — это книги), которые представлены в виде структуры, содержащей какие-либо данные и указатель типа данной структуры на следующий элемент. Тем самым, ты сможешь работать только с последним элементом. \n\
В нашей программе реализованы стандартные функции для работы с ним:\n\
	1. Push - добавить в контейнер;\n\
	2. Pop - удалить из контейнера;\n\
	3. Top - просмотреть/достать элемент из контейнера;\n";
	
	auto helpDialog = QMessageBox(QMessageBox::Information, 
		QString::fromStdWString(L"Справка от Жорика"), QString::fromStdWString(text), QMessageBox::StandardButton::Ok, this);
	helpDialog.exec();
	
	ui.catHelper->SetReaction(CatReaction(CatReaction::Event::HELP_READING_END));
	
	m_inactionTimer->start();
	
	m_helpOpennedOnce = true;
}

int MainWindow::GetEditRemoveIndex() const
{
	bool ok = false;
	int index = ui.editRemoveIndex->text().toInt(&ok);
	if (ok)
	{
		return index;
	}
	return -1;
}

int MainWindow::GetEditInsertIndex() const
{
	bool ok = false;
	int index = ui.editInsertIndex->text().toInt(&ok);
	if (ok)
	{
		return index;
	}
	return -1;
}

bool MainWindow::GetDataForList(const QString & input, List::data_t & out) const
{
	if (input.isEmpty())
	{
		return false;
	}

	auto str = input.toStdU32String();
	if (str.size() != 1)
	{
		return false;
	}
	
	out = str.back();
	return true;
}

bool MainWindow::GetDataForStack(const QString & input, Stack::data_t & out) const
{
	if (input.isEmpty())
	{
		return false;
	}

	bool isDouble = false;
	float value = input.toDouble(&isDouble);
	if (!isDouble)
	{
		return false;
	}
	
	out = value;
	return true;
}

void MainWindow::_InsertByIndex(int index)
{
	// перезапускаем таймер сначала при любом действии
	m_inactionTimer->start();
	m_inactionCounter = 0;
	
	QString insertValueFromEdit = ui.editInsertValue->text();
	CatReaction reaction;
	
	if (m_isListChosen)
	{
		List::data_t data;
		if (GetDataForList(insertValueFromEdit, data))
		{			
			if (index >= 0 && index <= m_list.Size())
			{
				qDebug() << "List: Inserted successfully!";
				
				m_list.InsertByIndex(data, index);

				// вставляем новую пустую строку в таблицу
				ui.table->insertRow(index);
				
				// создаём первую ячейку в новой строке - индекс новой строки
				auto item = new QTableWidgetItem(QString("%1").arg(index));			
				item->setTextAlignment(Qt::AlignCenter);
				ui.table->setItem(index, 0, item);
				
				// создаём вторую ячейку в новой строке - значение, введённое пользователем
				item = new QTableWidgetItem(QString::fromStdWString(std::wstring(1, data)));
				item->setTextAlignment(Qt::AlignCenter);
				ui.table->setItem(index, 1, item);

				// обновляем все записи последующие в таблице, увеличивая в них индекс (первая ячейка) на 1 единицу
				for (int i = index + 1; i < m_list.Size(); ++i)
				{
					ui.table->item(i, 0)->setText(QString("%1").arg(i));
				}
				
				reaction = CatReaction(
					CatReaction::ContainerType::LIST,
					CatReaction::Event::INSERTION,
					CatReaction::Result::SUCCESSED
				);
			}
			else
			{
				qDebug() << "List: Failed insert! Wrong index.";
				reaction = CatReaction(
					CatReaction::ContainerType::LIST,
					CatReaction::Event::OUT_OF_RANGE_INDEX
				);
			}
		}
		else
		{
			qDebug() << "List: Failed to insert! Wrong data.";
		
			reaction = CatReaction(
				CatReaction::ContainerType::LIST,
				CatReaction::Event::INVALID_DATA
			);
		}
	}
	else
	{
		Stack::data_t data;
		if (GetDataForStack(insertValueFromEdit, data))
		{
			if (index == m_stack.Size())
			{
				m_stack.Push(data);

				// добавляем строку в таблицу:
				ui.table->insertRow(0);
				
				// создаём первую ячейку в новой строке - индекс новой строки
				auto item = new QTableWidgetItem(QString("%1").arg(m_stack.Size() - 1));			
				item->setTextAlignment(Qt::AlignCenter);
				ui.table->setItem(0, 0, item);
				
				// создаём вторую ячейку в новой строке - полученное от пользователя значение
				item = new QTableWidgetItem(QString("%1").arg(data));			
				item->setTextAlignment(Qt::AlignCenter);
				ui.table->setItem(0, 1, item);

				// в стеке изменять последующие записи нет необходимости, т.к. мы их не меняем - элемент просто добавляется в конец
				
				qDebug() << "Stack: Inserted successfully!";
				
				reaction = CatReaction(
					CatReaction::ContainerType::STACK,
					CatReaction::Event::INSERTION,
					CatReaction::Result::SUCCESSED
				);
			}
			else
			{
				qDebug() << "Stack: Failed to insert! Index is not last.";				
				reaction = CatReaction(
					CatReaction::ContainerType::STACK,
					CatReaction::Event::INSERTION,
					CatReaction::Result::IMPOSIBLE
				);
			}
		}
		else
		{
			qDebug() << "Stack: Failed to insert! Wrong data.";
			reaction = CatReaction(
				CatReaction::ContainerType::STACK,
				CatReaction::Event::INVALID_DATA
			);
		}
	}
	
	ui.catHelper->SetReaction(reaction);
}

void MainWindow::_RemoveByIndex(int index)
{
	// перезапускаем таймер сначала при любом действии
	m_inactionTimer->start();
	m_inactionCounter = 0;
	
	CatReaction reaction;
	
	if (m_isListChosen)
	{
		if (index >= 0 && index < m_list.Size())
		{
			m_list.RemoveByIndex(index);
			
			ui.table->removeRow(index);

			// обновляем все записи последующие в таблице, перезаписывая им новое значение индекса
			for (int i = index; i < m_list.Size(); ++i)
			{
				ui.table->item(i, 0)->setText(QString("%1").arg(i));
			}
			
			qDebug() << "List: Removed successfully!";
			
			reaction = CatReaction(
				CatReaction::ContainerType::LIST,
				CatReaction::Event::REMOVING,
				CatReaction::Result::SUCCESSED
			);
		}
		else
		{
			reaction = CatReaction(
				CatReaction::ContainerType::LIST,
				CatReaction::Event::OUT_OF_RANGE_INDEX
			);
			qDebug() << "List: Failed to remove! Wrong index.";	
		}
	}
	else
	{
		// Удаления из стека выполняется только если
		// 1. Стек не пуст
		// 2. Индекс удаляемого элемента - это индекс последнего элемента
		if (m_stack.Size() > 0 && index == m_stack.Size() - 1)
		{
			m_stack.Pop();
			
			// для стека всегда удаляем первую строку, т.к. именно она верхушка стека
			ui.table->removeRow(0);

			// для стека, опять же, нет необходимости обновлять индексы в последующих записях таблицы
			
			qDebug() << "Stack: Removed successfully!";
			
			reaction = CatReaction(
				CatReaction::ContainerType::STACK,
				CatReaction::Event::REMOVING,
				CatReaction::Result::SUCCESSED
			);
		}
		else
		{
			qDebug() << "Stack: Failed to remove! Index is not last.";
			
			reaction = CatReaction(
				CatReaction::ContainerType::STACK,
				CatReaction::Event::REMOVING,
				CatReaction::Result::IMPOSIBLE
			);
		}
	}
	ui.catHelper->SetReaction(reaction);
}

void MainWindow::OnInactionTimer()
{
	++m_inactionCounter;

	CatReaction reaction;
	
	// Если бездействие больше одной минуты
	if (m_inactionCounter * m_inactionTimer->interval() / 1000 > 60)
	{
		reaction = CatReaction(CatReaction::Event::INACTION_TIMEOUT_LONG);
	}
	else
	{
		// с вероятностью 50% запускаем либо один тип реакций на небольшой таймаут, либо второй
		if (rand() % 2)
		{
			reaction = CatReaction(CatReaction::Event::INACTION_TIMEOUT_SMALL_1);	
		}
		else
		{
			reaction = CatReaction(CatReaction::Event::INACTION_TIMEOUT_SMALL_2);
		}		
	}
	
	ui.catHelper->SetReaction(reaction);
	// перезапускаем таймер сначала
	m_inactionTimer->start();
}
