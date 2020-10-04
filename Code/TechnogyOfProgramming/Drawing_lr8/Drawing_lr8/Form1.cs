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

            // Создаем рандомный генератор
            _random = new Random(DateTime.Now.Second);
            // задаем таймер интервала таймера 35 мс
            timer1.Interval = 35;
            // Берем картинку из ресурсов проекта и масштабируем её до 30х30
            _star = new Bitmap(Resources.star, 30, 30);

            // Задаём начальную позицию в центре экрана
            _position = new Point(ClientSize.Width / 2, ClientSize.Height / 2);
            // Задаём начальную скорость - 0;0
            _speed = new Point(0, 0);
        }

        // Функция, которая будет вызываться во время перерисовки формы
        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            // Очищаем экран черным цветом
            e.Graphics.Clear(Color.Black);
            
            // Отрисываваем картинку в полученной позиции
            e.Graphics.DrawImage(_star, _position);

            // Стартуем таймер заново
            timer1.Start();
        }

        // Функция, вызываемая при срабатывании таймера
        private void timer1_Tick(object sender, EventArgs e)
        {
            // Если звезда почти что остановилась
            if (IsStarAlmostStopped())
            {
                // "даём ей пинок" в новом случайном направлении
                CreateRandomImpulce();
            }

            // Предсказываем столкновения с границей и меняем скорость в таком случае
            PredictBorderCollisions();

            // Перемещаем звезды согласно её текущей скорости
            MoveStar();

            // Уменьшаем скорость на 10%
            DecreaseSpeed();

            // Провоцируем перерисовку формы - функцию Paint
            Invalidate();
        }

        // Предсказываем столкновения с границей и меняем скорость в таком случае
        private void PredictBorderCollisions()
        {
            // Запоминаем х и у координаты левого верхнего и правого нижнего углов.
            // Текущая позиция + текущая скорость = следующая позиция,
            // таким образом мы можем предсказать столкновение с границей и начать движение
            // в обратную сторону
            int left = _position.X + _speed.X;
            int top = _position.Y + _speed.Y;
            int right = left + _star.Size.Width;
            int bottom = top + _star.Size.Height;

            // При столкновении с левой и правой границами нам
            // достаточно изменить скорость по Х на противоположную,
            // т.е. домножить на -1.
            // Поэтому удобно ввести понятие speedCorrectionFactor -
            // множитель для коррекции скорости, который по умолчанию
            // будет равен (1;1), что значит - скорость без изменений
            Point speedCorrectionFactor = new Point(1, 1);

            // Если левая Х координата звезды ушла за левую часть экрана (меньше 0)
            // или правая координата звезды ушла за правую часть экрана (больше, чем ширина формы)
            if (left <= 0 || right >= ClientSize.Width)
            {
                // то устанавливаем коэффициент по Х равный -1.
                speedCorrectionFactor.X = -1;
            }

            // Аналогично для Y состовляющей скорости
            if (top <= 0 || bottom >= ClientSize.Height)
            {
                speedCorrectionFactor.Y = -1;
            }

            // Теперь перемножаем получившийся коэффициент с текущей скоростью,
            // тем самым избегая столкновения в будущем, если бы оно было.
            _speed.X *= speedCorrectionFactor.X;
            _speed.Y *= speedCorrectionFactor.Y;
        }

        // Перемещение звезды
        private void MoveStar()
        {
            // К текущей позиции добавляем текущее значение скорости
            _position.X += _speed.X;
            _position.Y += _speed.Y;
        }

        // Уменьшение скорости
        private void DecreaseSpeed()
        {
            // Текущую скорость уменьшаем на 10%
            _speed.X = (int) (_speed.X * 0.9);
            _speed.Y = (int) (_speed.Y * 0.9);
        }

        // Если звезда почти остановилась
        private bool IsStarAlmostStopped()
        {
            // Находим длину вектора скорости по формуле
            // L   = sqrt(x^2 + y^2) или
            // L^2 = x^2 + y^2
            // Если L равно 0, то значит звезда полностью остановилась.
            // Но в нашем случае затухание происходит по обратно экспотенциальной форме,
            // поэтому чем ближе к 0, тем медленнее скорость будет затухать.
            // Поэтому зададим L не нулем, а каким-то небольшим значением,
            // например 9.
            return (Math.Pow(_speed.X, 2) + Math.Pow(_speed.Y, 2)) < 9;
        }

        // Задание случайного импульса звезде
        private void CreateRandomImpulce()
        {
            // Создаем 2 случайных числа в диапазоне [-50;50]
            int xImpulce = _random.Next(100) - 50;
            int yImpulce = _random.Next(100) - 50;

            // Эти два числа и будут нашей новой скоростью
            _speed.X = xImpulce;
            _speed.Y = yImpulce;
        }

        // Генератор случайных чисел
        private Random _random;

        // Картинка звезды
        private Bitmap _star;

        // Текущее положение звезды
        private Point _position;

        // Текущая скорость звезды
        private Point _speed;
    }
}
