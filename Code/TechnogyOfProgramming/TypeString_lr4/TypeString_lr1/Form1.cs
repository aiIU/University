using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;

namespace TypeString_lr1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            listBox.Items.Clear();

            // Swap-test
            listBox.Items.Add("Hello my little friend.");
            listBox.Items.Add("Did you still want a muffin?");
            listBox.Items.Add("I love you");
            listBox.Items.Add("I promise I look after you");

            countWordText.Text = listBox.Items.Count.ToString() + " strings.";
           
            swappedText.Text = "";
        }

        private void OnStart(object sender, EventArgs e)
        {
			// Узнаём индекс выделенной строки:
            var index = listBox.SelectedIndex;
			
			// Если пользователь ничего не выделил, то индекс будет равен -1
            if (index == -1)
            {
                MessageBox.Show("You should choose any string", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

			// Сохраняем выделенную строку
            var chosen = (string) listBox.Items[index];
			
			// Разбиваем строку на слова
            var words = Split(chosen);
			
			// Выводим на экран количество слов в строке:
            countWordText.Text = "Chosen string contains " + words.Count.ToString() + " words";
            
			// Если не удаётся распарсить хотя бы один текст-бокс, что выдаём сообщение об ошибке:
            if (!int.TryParse(index1.Text, out var i) || !int.TryParse(index2.Text, out var j))
            {
                MessageBox.Show("You should enter only numbers!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
	
			// "Защита от дурака" - убираем возможность ввода отрицательных чисел и нуля:
            if (i <= 0 || j <= 0)
            {
                MessageBox.Show("Numbers i and j must be more than zero", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

			// При одинаковых номерах букв менять ничего не потребуется:
			if (i == j)
			{
				swappedText.Text = chosen;
				return;
			}
			
			// Преобразуем номера букв в индексы букв:
            i -= 1;
            j -= 1;
	
			// Создаём массив для новых слов
			var result = new List<string>();
            for (var k = 0; k < words.Count; ++k)
            {
				// Вызываем функцию, которая меняет местами буквы
				// и добавляем полученную строку в результирующий массив:
				result.Add(SwapLetters(words[k], i, j));
            }
			
			// Склеиваем полученные слова в одну строку, добавляя между словами пробел:
            swappedText.Text = string.Join(" ", result);
        }
        
        private List<string> Split(string input)
        {
			// Создаём массив для слов
            var strings = new List<string>();
			// Создаём регулярное выражение, которое означает "хотя бы один не пробельный символ"
			var regexWord = new Regex(@"\S+");
			// Ищем в строке указанные выражения
			var matches = regexWord.Matches(input);
			// Каждое найденное выражение - это отдельное слово
			foreach(var match in matches)
			{
				strings.Add(match.ToString());
			}
			return strings;
        }

        private string SwapLetters(string word, int i, int j)
        {
			// Меняем индексы местами, чтобы выглядело логичнее:
            if (i > j)
            {
                var temp = i;
                i = j;
                j = temp;
            }
			
			// Если индексы за пределами слова, то просто возвращаем слово без изменений:
            if (j >= word.Length)
            {
                return word;
            }
			
			// Так как string напрямую мы не можем менять, то преобразуем string в массив char-ов
            var letters = word.ToCharArray();
			// и выполняем перестановку i и j буквы:
            var c = word[i];
            letters[i] = letters[j];
            letters[j] = c;

			// Возвращаем новую строку, сконструированную из массива char-ов
            return new string(letters);
        }
    }
}

