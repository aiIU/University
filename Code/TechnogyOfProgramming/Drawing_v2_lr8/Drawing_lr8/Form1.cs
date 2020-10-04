using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Drawing_lr8.Properties;

namespace Drawing_lr8
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            
            // Интервал таймера устанавливаемв 35 мс
            // Т.о. мы будет смещать квадрат каждые 35 мс
            timer1.Interval = 35;

            // Создаём закрашивающую кисть желто-зеленого цвета
            _brush = new SolidBrush(Color.GreenYellow);

            // Создаём массив из ста точек. Заполним их точками траектории чуть ниже
            _points = new Point[100];

            // Задаём размеры квадрата - 30х30
            _square = new Size(30, 30);
            // Сначала будет двигаться вправо
            _toRight = true;

            // Задаём шаг для x, должен быть небольшой, чтобы не было резких скачков квадрата
            int step = 2;
            int x = 0, y;
            // Заполняем массив точек точками траектории, которые высчитываются по функции в MoveFunction
            for (int i = 0; i < 100; ++i)
            {
                y = MoveFunction(x) + 25;
                _points[i] = new Point(x, y);
                x += step;
            }
        }

        private int MoveFunction(int x)
        {
            // Траекторию движения задаём функцией A * sin(B * x) ^ 2
            // Квадрат синуса даст нам значения Y от [0; 1]
            // Коэффициент A "подымет" Y до [0; A]
            // Коэффициент В "расплющит" синусоиду, что позволит сделать плавное движение,
            // если B выставить достаточно маленьким, например, 1/30
            return (int)(Math.Pow(Math.Sin(x / 30.0), 2) * ClientSize.Height / 2);
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            // Закрашиваем весь экран в фиолетовый
            e.Graphics.Clear(Color.BlueViolet);
            
            // Получаем следующую точку траектории
            Point point = GetNextPoint();
            // Отрисовываем кистью _brush квадрат _square в указанной точке point
            e.Graphics.FillRectangle(_brush, point.X, point.Y, _square.Width, _square.Height);

            // запускаем таймер снова
            timer1.Start();
        }

        private Point GetNextPoint()
        {
            return _points[_currentIndex];
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            // если движемся вправо, то смещаем следующий индекс вправо (+1)
            // а если движемся влево, то смещаем следующий индекс влево (-1)
            int step = _toRight ? 1 : -1;
            _currentIndex = _currentIndex + step;

            // Если мы движемся вправо и достигли последней точки
            if (_toRight && _currentIndex == 99)
            {
                // то начинаем движение влево
                _toRight = false;
            }
            // Но если мы двигаемся влево и достигли первой точки
            else if (!_toRight && _currentIndex == 0)
            {
                // то начинаем движение вправо
                _toRight = true;
            }

            Invalidate();
        }

        private Brush _brush;
        private Size _square;

        private Point[] _points;
        private int _currentIndex;
        private bool _toRight;
    }
}
