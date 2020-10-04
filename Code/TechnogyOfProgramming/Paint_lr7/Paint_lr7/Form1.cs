using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace Paint_lr7
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            _items = new List<IDrawable>();
            
            _items.Add(new Sky(new Point(0, 0), new Size(ClientSize.Width, ClientSize.Height * 2 / 3)));
           
            _items.Add(new Ground(new Point(0, ClientSize.Height * 2 / 3), new Size(ClientSize.Width, ClientSize.Height * 1 / 3)));
            
            _items.Add(new House(new Point(70, 100), new Size(150, 200)));
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            foreach (var item in _items)
            {
                item.Draw(e.Graphics);
            }
        }
        
        private List<IDrawable> _items;
    }

    /// <summary>
    /// Интерфейс для всех рисуемых объектов; содержит метод Draw(Graphics)
    /// Таким образом можно хранить все объекты, которые нужно отрисовать, в List<IDrawable>,
    /// а для их отрисовки вызвать мето Draw(Graphics).
    /// </summary>
    interface IDrawable
    {
        void Draw(Graphics graphics);
    }
    
    /// <summary>
    /// Sky - небо.
    /// Для создания необходимо указать позицию левого верхнего угла и размер
    /// </summary>
    public class Sky : IDrawable
    {
        public Sky(Point point, Size size)
        {
            _bbox = new Rectangle(point, size);
            _brush = new SolidBrush(Color.Cyan);
        }

        public void Draw(Graphics graphics)
        {
            graphics.FillRectangle(_brush, _bbox);
        }

        private Brush _brush;
        private Rectangle _bbox;
    }
    
    /// <summary>
    /// Ground - земля
    /// Для создания необходимо указать позицию левого верхнего угла и размер
    /// </summary>
    public class Ground : IDrawable
    {
        public Ground(Point point, Size size)
        {
            _bbox = new Rectangle(point, size);
            _brush = new SolidBrush(Color.ForestGreen);
        }

        public void Draw(Graphics graphics)
        {
            graphics.FillRectangle(_brush, _bbox);
        }

        private Brush     _brush;
        private Rectangle _bbox;
    }
   
    /// <summary>
    /// Wall - стена. Вспомогательный объект дл создания дома.
    /// Для его создания указывается позиция левого верхнего угла и размер
    /// </summary>
    public class Wall : IDrawable
    {
        public Wall(Point location, Size size)
        {
            _bbox = new Rectangle(location, size);
            _brush = new SolidBrush(Color.Coral);
        }

        public void Draw(Graphics graphics)
        {
            graphics.FillRectangle(_brush, _bbox);
        }

        private Brush     _brush;
        private Rectangle _bbox;
    }
    
    /// <summary>
    /// HouseTop - крыша. Вспомогательный объект для создания дома.
    /// Для его создания указывается позиция левого верхнего угла и размер
    /// </summary>
    public class HouseTop : IDrawable
    {
        public HouseTop(Point location, Size size)
        {
            _brush = new SolidBrush(Color.SaddleBrown);

            _polygon = new[]
            {
                new Point(0,size.Height),
                new Point(size.Width / 2, 0),
                new Point(size.Width,size.Height)
            };
            
            for (var i = 0; i < _polygon.Length; ++i)
            {
                _polygon[i].X += location.X;
                _polygon[i].Y += location.Y;
            }
        }

        public void Draw(Graphics graphics)
        {
            graphics.FillPolygon(_brush, _polygon);   
        }
        
        private Brush _brush;
        private Point[] _polygon;
    }

    /// <summary>
    /// House - cложный объект, состоящий из нескольких примитивов (стена, крыша, окно, труба)
    /// Для создания необходимо указать позицию левого верхнего угла и размер
    /// </summary>
    public class House : IDrawable
    {
        public House(Point location, Size size)
        {
            _items = new IDrawable[]
            {
                // Добавляем крышу
                new HouseTop(
                    new Point(location.X, location.Y),
                    new Size(
                        size.Width, 
                        size.Height * 7 / 16)), 
                // Добавляем стену
                new Wall(
                    new Point(
                        location.X, location.Y + size.Height * 7 / 16), 
                    new Size(
                        size.Width,
                        size.Height * 9 / 16))
            };
        }

        public void Draw(Graphics graphics)
        {
            foreach (var item in _items)
            {
                item.Draw(graphics);
            }
        }

        private IDrawable[] _items;

    }
}