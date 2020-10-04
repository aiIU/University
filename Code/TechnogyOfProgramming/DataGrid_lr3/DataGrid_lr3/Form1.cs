using System;
using System.Windows.Forms;

namespace DataGrid_lr3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            
            // Инициализируем сетки массивом 15х15 и устанавливаем им небольшой размер
            Init(ref dataGridSource1);
            Init(ref dataGridSource2);
            Init(ref dataGridResult);

            // Создаём генератор случайных чисел, инициализируя его текущим временем в секундах,
            // чтобы при каждом запуске программы получать разные числа
            var rand = new Random(DateTime.Now.Second);

            // Генерируем случайные элементы в исходные массивы
            Generate(ref _source1, rand);
            Generate(ref _source2, rand);

            // Заполняет таблицы с помощью созданных ранее массивов
            Fill(ref dataGridSource1, _source1);
            Fill(ref dataGridSource2, _source2);
        }

        private void Generate(ref int[,] data, Random rand)
        {
            data = new int[15, 15];
            for (var i = 0; i < 15; ++i)
            {
                for (var j = 0; j < 15; ++j)
                {
                    data[i, j] = rand.Next(-10, 10);
                }
            }
        }

        private void Fill(ref DataGridView grid, int[,] data)
        {
            for (var i = 0; i < 15; ++i)
            {
                for (var j = 0; j < 15; ++j)
                {
                    grid.Rows[i].Cells[j].Value = data[i, j];
                }
            }
        }

        private void Init(ref DataGridView grid)
        {
            // Устанавливаем выравнивание по центру
            grid.AlternatingRowsDefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
            // Устанавливаем количество строк и столбцов
            grid.RowCount = 15;
            grid.ColumnCount = 15;
            // Задаём каждой ячейке ширину и высоту
            for (var i = 0; i < 15; ++i)
            {
                grid.Rows[i].Height = 16;
                grid.Columns[i].Width = 24;
            }
        }

        private void OnStart(object sender, EventArgs e)
        {
            // Сбрасываем всё старое выделение:
            dataGridSource1.ClearSelection();
            dataGridSource2.ClearSelection();
            dataGridResult.ClearSelection();

            // "высота" ступенчатого массива будет той же, что и "высота" двумерных массивов
            _result = new int[15][];

            // но в "ширину" ступенчатый массив будет непостоянен - может быть и 0 элементов
            // поэтому введём переменную-счётчик length, чтобы узнать на сколько элементов выделять массив второго уровня (в "ширину")
            for (var i = 0; i < 15; ++i)
            {
                // Нам нужно пройти первый раз по всей строке, чтобы узнать количество подходящих элементов
                var length = 0;
                for (var j = 0; j < 15; ++j)
                {
                    // Сравниваем значение в ячейках
                    if (_source1[i, j] != _source2[i, j])
                    {
                        continue;
                    }
                    
                    dataGridSource1.Rows[i].Cells[j].Selected = true;
                    dataGridSource2.Rows[i].Cells[j].Selected = true;

                    length += 1;
                }

                // Когда мы знаем число элементов, мы можем выделить необходимое количество памяти
                _result[i] = new int[length];
                // Введем счётчик k для записи по нужному индексу
                var k = 0;
                // Второй раз обходим все элементы в строке, но теперь записываем их в ступенчатый массив
                for (var j = 0; j < 15; ++j)
                {
                    if (_source1[i, j] != _source2[i, j])
                    {
                        continue;
                    }

                    _result[i][k] = _source1[i, j];
                    k += 1;
                }
            }

            // Теперь нужно элементы из полученного ступенчатого массива _result записать в dataGrid для отображения
            for (var i = 0; i < _result.Length; ++i)
            {
                for (var j = 0; j < _result[i].Length; ++j)
                {
                    dataGridResult.Rows[i].Cells[j].Value = _result[i][j];
                }
            }
        }

        // Два двумерных массива
        private int[,] _source1, _source2;
        // Ступенчатый
        private int[][] _result;
    }
}
