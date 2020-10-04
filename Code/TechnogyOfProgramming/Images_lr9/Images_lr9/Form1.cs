using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Images_lr9
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Close();
        }

        // Загрузка изображения
        private void button1_Click(object sender, EventArgs e)
        {
            // Создаём объект класса OpenFileDialog - это диалоговое окно с выбором файла
            var open = new OpenFileDialog()
            {
                // задаём фильтр для файлов, которые мы можем выбрать; в нашем случае это картинки нижеперечисленного формата
                Filter = "Image files  (*.BMP, *.JPG, *.GIF, *.TIF, *.PNG)|*.bmp;*.jpg;*.gif; *.tif; *.png;"
            };
            // Если пользователь не нажал на "открыть файл"
            if (open.ShowDialog() != DialogResult.OK)
            {
                // то ничего не делаем и завершаем функцию
                return;
            }

            // Загружаем картинку, которую выбрали в диалоговом окне
            var image = Image.FromFile(open.FileName);
            pictureBox1.Image = new Bitmap(image, pictureBox1.Size);   
        }

        private void button2_Click(object sender, EventArgs e)
        {
            // Создаём объект класса SaveFileDialog - это диалоговое окно с выбором пути для сохранения
            var save = new SaveFileDialog()
            {
                Title = "Сохранить картинку как ...",
                OverwritePrompt = true,
                CheckPathExists = true,
                Filter = "Image files (*.BMP, *.JPG, *.GIF, *.TIF, *.PNG)|*.bmp;*.jpg;*.gif; *.tif; *.png;",
                ShowHelp =  true
            };

            // Если пользователь закрыл окно крестиком или отменой, но ничего не делаем и завершаем функцию
            if (save.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            // Получаем выбранный путь для сохранения
            var filename = save.FileName;

            // Пытаемся узнать расширение файла, которое ввёл пользователь
            var index = filename.LastIndexOf('.');
            string extension;
            if (index != -1) // точка в имени найдена, получаем всё, что справа от неё
            {
                extension = filename.Substring(index);
            }
            else // точка в имени не найдена, дописываем расширение по умолчанию (например, bmp)
            {
                extension = ".bmp";
                filename = filename + extension;
            }

            // В зависимости от расширения сохраняем картинку в соответствующем формате
            ImageFormat format;
            switch (extension)
            {
                case "jpg":
                    format = ImageFormat.Jpeg;
                    break;
                case "gif":
                    format = ImageFormat.Gif;
                    break;
                case "tif":
                    format = ImageFormat.Tiff;
                    break;
                case "png":
                    format = ImageFormat.Png;
                    break;
                default:
                    format = ImageFormat.Bmp;
                    break;
            }
            pictureBox1.Image.Save(save.FileName, format);
        }

        // Применение преобразования
        private void button4_Click(object sender, EventArgs e)
        {
            var bmp = new Bitmap(pictureBox1.Image);
            int xMax = bmp.Size.Width;
            int yMax = bmp.Size.Height;

            // Пробегаем по каждому пикселю в картинке
            for (int y = 0; y < yMax; ++y)
            {
                for (int x = 0; x < xMax; ++x)
                {
                    // Заполучаем пиксель по (x, y)
                    var pixel = bmp.GetPixel(x, y);

                    // Если голубого цвета больше, чем зеленого и красного вместе взятых
                    if (pixel.B > pixel.R + pixel.G)
                    {
                        // уменьшаем количество синего в 10 раз
                        var newB = (byte) (pixel.B * 0.1);
                        // уменьшаем количество зеленого в 3 раза
                        var newG = (byte) (pixel.G * 0.3);
                        // заменяем красный - синим
                        var newR = pixel.B;
                        var color = Color.FromArgb(newR, newG, newB);
                        bmp.SetPixel(x, y, color);
                    }
                }
            }

            // Кладём измененную картинку в pictureBox (для отображения на экране)
            pictureBox1.Image = bmp;
        }
    }
}
