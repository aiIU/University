using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Text;
using System.Windows.Forms;
using Crypto_kr.Properties;

namespace Crypto_kr
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            
            // Устанавливаем возможные значения битов во все три комбобокса
            // Четвертым параметром указываем значение по умолчанию
            SetComboBoxItems(comboBoxR, 0, 8, 3);
            SetComboBoxItems(comboBoxG, 0, 8, 2);
            SetComboBoxItems(comboBoxB, 0, 8, 3);

            // Сохраняем картинку из ресурсов (картинка по умолчанию) в переменную
            // и масштабируем её до размера 640x480
            _originPicture = new Bitmap(Resources.initialImage, pictureBox1.Size);
            // Загружаем картинку на экран
            pictureBox1.Image = _originPicture;
            // Очищаем поле вывода информации
            textBox.Text = @"";
        }
        
        // При каждом обновлении комбобокса вызывается эта функция
        private void comboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Пытаемся установить выбранные биты:
            // Может быть, они будут невалидны - выведем сообещние об ошибке и т.д.
            UpdateSpecifiedBits();
        }
        
        // При нажатии на любую из радио кнопок вызывается эта функция
        private void radioButton_CheckedChanged(object sender, EventArgs e)
        {
            // Если нажали "декодировать", то устанавливаем поле вывода информации в режим "только чтение"
            textBox.ReadOnly = radioButtonDecode.Checked;

            // При выборе декодирования
            if (radioButtonDecode.Checked)
            {
                // Очищаем текстовое поле вывода
                textBox.Text = @"";
                // Устанавливаем состояние (приватная переменная) в DECODE
                // позже мы будет в зависимости от выбранного состояния
                // производить соответствующие действия
                _state = StateEnum.DECODE;
            }

            // При выборе кодирования информации
            if (radioButtonEncode.Checked)
            {
                // Очищаем информационное сообщение (строка текста внизу)
                SetInfoMessage("");
                // Устанавливаем состояние в ENCODE
                _state = StateEnum.ENCODE;
            }
        }

        // При нажатии на кнопку "сохранить"
        private void buttonSave_Click(object sender, EventArgs e)
        {
            // Открываем диалог выбора пути для сохранения
            var save = new SaveFileDialog()
            {
                Title = "Сохранить картинку как ...",
                OverwritePrompt = true,
                CheckPathExists = true,
                Filter =
                    "Image files (*.BMP, *.JPG, *.GIF, *.TIF, *.PNG, *.ICO, *.EMF, *.WMF)|*.bmp;*.jpg;*.gif; *.tif; *.png; *.ico; *.emf; *.wmf",
                ShowHelp = true
            };

            if (save.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            // Получаем расширение файла из выбранного названия файла
            var filename = save.FileName;
            var index = filename.LastIndexOf('.');
            string extension;
            if (index != -1)
            {
                extension = filename.Substring(index);
            }
            // Либо устанавливаем по умолчанию bmp
            else
            {
                extension = ".bmp";
                filename = filename + extension;
            }

            // В зависимости от расширение выбираем формат, в который будет сохранять изображение
            ImageFormat format;
            switch (extension)
            {
                case "jpg":
                    format = ImageFormat.Jpeg;
                    break;
                case "png":
                    format = ImageFormat.Png;
                    break;
                default:
                    format = ImageFormat.Bmp;
                    break;
            }

            // Сохраняем картинку
            pictureBox1.Image.Save(filename, format);
        }

        // При нажатии на "Загрузить"
        private void buttonLoad_Click(object sender, EventArgs e)
        {
            // Открываем диалог для выбора пути загрузки картинки
            var open = new OpenFileDialog()
            {
                InitialDirectory = Application.StartupPath,
                Filter =
                    "Image files (*.BMP, *.JPG, *.PNG, *.ICO)|*.bmp; *.jpg; *.png; *.ico;"
            };
            if (open.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            // Загружаем
            var image = Image.FromFile(open.FileName);
            // Сохраняем в переменную, масштабирую до определенного размера (640х480)
            _originPicture = new Bitmap(image, pictureBox1.Size);
            // Выводим на экран
            pictureBox1.Image = _originPicture;
        }
        
        // При нажания на кнопку "запустить"
        private void buttonStart_Click(object sender, EventArgs e)
        {
            // Пытаемся установить выбранные пользователем биты
            if (!UpdateSpecifiedBits())
            {
                return;
            }
            // Очищаем окно с информацией
            labelInfo.Text = "";
            // В зависимости от выбранного состояния
            switch (_state)
            {
                // Если включён режим "кодирование"
                case StateEnum.ENCODE:
                {
                    // Конвертируем строку для кодирования в массив байтов 
                    var textBytes = Encoding.UTF8.GetBytes(textBox.Text);
                    // Кодируем длину строки в массив байтов
                    var sizeBytes = BitConverter.GetBytes(textBytes.Length);

                    // Подсчитываем максимально допустимое количество доступных байт для кодирования
                    var maxBytesNumber = _originPicture.Width * _originPicture.Height;
                    // Подсчитываем количество байт, которые нужно закодировать
                    var bytesNumber = textBytes.Length + sizeBytes.Length;
                    // Для кодирования символа может потребоваться от 1 до 8 пикселей, в зависимости
                    // от выбора пользователя
                    // Поэтому кол-во байтов текста нужно домножить на _pixelsPerSymbol
                    // И если получившееся число байт больше, чем макимально допустимое,
                    // то выводим пользователю ошибку
                    if (maxBytesNumber < bytesNumber * _pixelsPerSymbol)
                    {
                        SetInfoMessage($"Недостаточно байтов в картинке: для кодирования требуется {bytesNumber}!");
                        return;
                    }
                    // Если входное сообщение слишком длинное, то сообщение с детальной информацией
                    // может быть огромным и занять очень много времени для записи в окно вывода информации
                    // Поэтому в таком случае предупредим пользователя и предложим ему отключить детальный лог.
                    if (bytesNumber * _pixelsPerSymbol > 50 && IsDetailedLog.Checked)
                    {
                        // Показываем окошко с соответствующим текстом и двумя кнопками - да/нет.
                        var dialogResult = MessageBox.Show(@"Вывод детальной информации может занять до 10 минут! Отключить его?",
                            @"Внимание!", MessageBoxButtons.YesNo);
                        // Если пользователь согласился на отключение
                        if (dialogResult == DialogResult.Yes)
                        {
                            // То отключаем детальный лог
                            IsDetailedLog.Checked = false;
                        }
                    }

                    // Создаём массив байт, чтобы передать его в функцию для кодирования
                    var bytes = new byte[bytesNumber];
                    // Копируем в него размер массива
                    sizeBytes.CopyTo(bytes, 0);
                    // Копируем в него текст
                    textBytes.CopyTo(bytes, sizeBytes.Length);
                    // В итоге получается паскаль-строка, где в её начале
                    // указан её размер
                    
                    textBox.Text = "";
                    // Кодируем текст bytes по картинке _originPicture и получаем итоговую картинку processedImage
                    var size = EncodeImage(bytes, _originPicture, out Bitmap processedImage);
                    // Отображаем результат
                    pictureBox1.Image = processedImage;
                    // Фиксируем немного информации о затраченных байтах
                    SetInfoMessage($"Использовано байт: {size}/{maxBytesNumber}");
                    break;
                }
                case StateEnum.DECODE:
                {
                    // Декодируем картинку
                    var bmp = new Bitmap(pictureBox1.Image);
                    var bytes = DecodeImage(bmp);
                    // Если был возвращен null, значит произошла какая-то ошибка при кодировании
                    if (bytes == null)
                    {
                        break;
                    }
                    // Иначе преобразуем байты в UTF-8 строку и записываем её в окно вывода
                    textBox.Text = Encoding.UTF8.GetString(bytes);
                    // Фиксируем немного информации о том, сколько пикселей мы декодировали
                    SetInfoMessage($"Декодировано {bytes.Length * _pixelsPerSymbol } пикселей!");
                    break;
                }
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        // Проверяем установленные значения битов
        // Если корректны, то запоминаем их, записывая в соответствующие поля
        private bool UpdateSpecifiedBits()
        {
            // Проверка содержимого комбобоксов на валидность
            // Если там не цифры, то завершаемся
            if (!byte.TryParse((string) comboBoxR.SelectedItem, out byte bitsRed)
                || !byte.TryParse((string) comboBoxG.SelectedItem, out byte bitsGreen)
                || !byte.TryParse((string) comboBoxB.SelectedItem, out byte bitsBlue))
            {
                return false;
            }

            // Проверка битов на границу [0; 8] и валидность их суммы
            if (!ConfigurateBits(bitsRed, bitsGreen, bitsBlue)) return false;
            
            SetInfoMessage("");
            return true;

        }

        // Записываем указанное сообщение в информационную строку внизу формы
        private void SetInfoMessage(string msg, bool isError = false)
        {
            // Если второй аргумент isError передан как true, то устанавливаем цвет 
            // в красный, иначе в черный
            labelInfo.ForeColor = isError ? Color.Red : Color.Black;
            labelInfo.Text = msg;
        }
        
        // Инициализация комбобоксов
        // box - комбобокс для инициализации
        // [from, to] - диапазон чисел, которые будут заисаны в комбобокс
        // selected - число из этого диапазона, которое будет выделенным по умолчанию
        private void SetComboBoxItems(ComboBox box, int from, int to, int selected)
        {
            // Очисткастарых значений
            box.Items.Clear();
            for (int i = from; i <= to; ++i)
            {
                // Добавление строки с числом i
                box.Items.Add(i.ToString());
            }
            // Установка выделение на selected
            box.SelectedIndex = box.FindStringExact(selected.ToString());
        }

        private bool ConfigurateBits(byte red, byte green, byte blue)
        {
            // Проверяем корректность битов, которые задал пользователь
            // Каждый канал должен быть в диапазоне [0-8]
            // 8 бит должно быть кратно суммарному количетсву бит
            if (red > 8 || green > 8 || blue > 8)
            {
                SetInfoMessage(@"Значение бита должно быть меньше  либо равно 8!");
                return false;
            }

            var sum = red + green + blue;
            if (sum == 0)
            {
                SetInfoMessage("Необходимо выбрать хотя бы один бит!");
                return false;
            }

            if (8 % sum != 0)
            {
                SetInfoMessage("8 должно без остатка делиться на сумму бит!");
                return false;
            }

            // Записываем их в поля
            _bitsRed = red;
            _bitsGreen = green;
            _bitsBlue = blue;

            // Подсчитываем количество пикселей для записи одного символа
            _pixelsPerSymbol = (byte)(8 / (red + green + blue));

            return true;
        }

        // Декодирования текста из изображения
        public byte[] DecodeImage(Bitmap bitmap)
        {
            // Из указанной картинки декодируем 4 символа - 4 байта
            var sizeBytes = GetBytes(bitmap, 0, 4);
            // Конвертируем их в int, чтобы узнать длину строки
            int size = BitConverter.ToInt32(sizeBytes, 0);
            // Если получившееся число слишком большое, то делаем вывод, что 
            // картинка не подходит для декодирования - видимо она не содержит сообщения
            // Однако мы также может получить и валидный размер сообщения на случайной 
            // картинке. Это решается вводом дополнительного идентификатора в начало
            // картинки
            if (size > bitmap.Width * bitmap.Height)
            {
                SetInfoMessage("Данная картинка не содержит закодированное сообщение!");
                return null;
            }
            
            return GetBytes(bitmap, 4, size);
        }

        // Декодируем number байтов начиная с байта номер from 
        public byte[] GetBytes(Bitmap bitmap, int from, int number)
        {
            byte[] bytes = new byte[number];
            int byteIndex = 0;
            
            from = from * _pixelsPerSymbol;
            int to = from + number * _pixelsPerSymbol;
            
            Color[] pixels = new Color[_pixelsPerSymbol];
            for (int i = from; i < to; i += _pixelsPerSymbol)
            {
                for (int j = 0; j < _pixelsPerSymbol; ++j)
                {
                    IndexToPixelCoord(i + j, out int x, out int y);
                    pixels[j] = bitmap.GetPixel(x, y);
                }
                bytes[byteIndex] = DecodeSymbolFromPixels(pixels);
                ++byteIndex;
            }
            return bytes;
        }

        public int EncodeImage(byte[] textBytes, Bitmap bitmap, out Bitmap result)
        {
            result = new Bitmap(bitmap);

            int i = 0;
            Color[] pixels = new Color[_pixelsPerSymbol];
            foreach (var symbol in textBytes)
            {
                for (int j = 0; j < _pixelsPerSymbol; ++j)
                {
                    IndexToPixelCoord(i + j, out int x, out int y);
                    pixels[j] = result.GetPixel(x, y);
                }
                EncodeSymbolToPixels(symbol, ref pixels);
                for (int j = 0; j < _pixelsPerSymbol; ++j)
                {
                    IndexToPixelCoord(i + j, out int x, out int y);
                    result.SetPixel(x, y, pixels[j]);
                }

                i += _pixelsPerSymbol;
            }

            return _pixelsPerSymbol * textBytes.Length;
        }

        private void IndexToPixelCoord(int i, out int x, out int y)
        {
            x = i % _originPicture.Width;
            y = i / _originPicture.Width;
        }

        private void EncodeSymbolToPixels(byte textSymbol, ref Color[] pixels)
        {
            Color[] oldPixels = null;
            if (IsDetailedLog.Checked)
            {
                oldPixels = new Color[pixels.Length];
                pixels.CopyTo(oldPixels, 0);
            }

            byte offset = 0;
            for (int i = 0; i < pixels.Length; ++i)
            {
                byte r = pixels[i].R;
                byte g = pixels[i].G;
                byte b = pixels[i].B;
         
                EncodeBits(textSymbol, offset, _bitsRed, ref r);
                offset += _bitsRed;
                EncodeBits(textSymbol, offset, _bitsGreen, ref g);
                offset += _bitsGreen;
                EncodeBits(textSymbol, offset, _bitsBlue, ref b);
                offset += _bitsBlue;
                
                pixels[i] = Color.FromArgb(r, g, b);
            }

            if (IsDetailedLog.Checked)
            {
                LogEncodedSymbol(textSymbol, oldPixels, pixels);
            }
        }

        private void LogEncodedSymbol(byte symbol, Color[] before, Color[] after)
        {
            var newLine = Environment.NewLine;

            var result = $"{{0x{symbol:X2} - {ToBitString(symbol)}}}:{newLine}";
            for (int i = 0; i < before.Length; ++i)
            {
                var p1 = before[i];
                var p2 = after[i];

                var temp = $"{i} R: {ToBitString(p1.R)}  {ToBitString(p2.R)}{newLine}" +
                           $"{i} G: {ToBitString(p1.G)}  {ToBitString(p2.G)}{newLine}" +
                           $"{i} B: {ToBitString(p1.B)}  {ToBitString(p2.B)}{newLine}";

                result = string.Concat(result, temp);
            }

            result = string.Concat(result, newLine);

            textBox.Text += result;
        }

        private string ToBitString(byte symbol)
        {
            return Convert.ToString(symbol, 2).PadLeft(8, '0');
        }

        private byte DecodeSymbolFromPixels(Color[] pixels)
        {
            byte res = 0;
            byte offset = 0;
            foreach (var pixel in pixels)
            {
                byte r = pixel.R;
                byte g = pixel.G;
                byte b = pixel.B;
            
                DecodeBits(r, _bitsRed, ref res, offset);
                offset += _bitsRed;
                DecodeBits(g, _bitsGreen, ref res, offset);
                offset += _bitsGreen;
                DecodeBits(b, _bitsBlue, ref res, offset);
                offset += _bitsBlue;
            }
            return res;
        }
        
        // Устанавливаем n бит из байта from начиная с pos в n последних бит в to
        // pos - [0; 7]
        // n   - [0; 8]
        private void EncodeBits(byte from, byte pos, byte n, ref byte to)
        {
            for (byte i = 0; i < n; ++i)
            {
                bool bit = TestBit(from, 7 - pos - i);
                SetBit(ref to, n - 1 - i, bit);
            }
        }

        // Извлекаем последние n бит из from и устанавливаем их в to начиная с позиции pos
        // pos - [0; 7]
        // n   - [0; 8]
        private void DecodeBits(byte from, byte n, ref byte to, byte pos)
        {
            for (byte i = 0; i < n; ++i)
            {
                bool bit = TestBit(from, n - 1 - i);
                SetBit(ref to, 7 - pos - i, bit);
            }
        }

        // Возвращаем i-ый бит в символе
        // i - [0; 7]
        private bool TestBit(byte symbol, int i)
        {
            return ((symbol >> i) & 1) == 1;
        }
        
        // Устанавливем в байте i-ый бит в указанное value
        // i - [0; 7]
        private void SetBit(ref byte symbol, int i, bool value)
        {
            if (value)
            {
                symbol = (byte)(symbol | (1 << i));
            }
            else
            {
                symbol = (byte)(symbol & ~(1 << i));
            }
        }
        
        private enum StateEnum
        {
            ENCODE,
            DECODE
        }

        private Bitmap _originPicture;
        private StateEnum _state;
        
        private byte _bitsRed = 3;
        private byte _bitsGreen = 2;
        private byte _bitsBlue = 3;
        private byte _pixelsPerSymbol;

        private void button1_Click(object sender, EventArgs e)
        {
            textBox.Clear();
        }
    }
}