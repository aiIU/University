using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
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
            var index = listBox.SelectedIndex;
            if (index == -1)
            {
                MessageBox.Show("You should choose any string", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            var chosen = (string) listBox.Items[index];
            var words = Split(chosen);
            countWordText.Text = "Chosen string contains " + words.Count.ToString() + " words";
            
            if (!int.TryParse(index1.Text, out var i) || !int.TryParse(index2.Text, out var j))
            {
                MessageBox.Show("You should enter only numbers!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (i <= 0 || j <= 0)
            {
                MessageBox.Show("Numbers i and j must be more than zero", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            i -= 1;
            j -= 1;

            for (var k = 0; k < words.Count; ++k)
            {
                var str = words[k];
                SwapLetters(ref str, i, j);
                words.RemoveAt(k);
                words.Insert(k, str);
            }
            swappedText.Text = string.Join(" ", words);
        }
        
        private List<string> Split(string input)
        {
            var strings = new List<string>();
            
            const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
            const string waste = " ";

            int from = 0, to = -1;
            do
            {
                from = input.IndexOfAny(alphabet.ToCharArray(), to + 1);
                if (from == -1)
                {
                    return strings;
                }
                
                to = input.IndexOfAny(waste.ToCharArray(), from);
                if (to == -1)
                {
                    to = input.Length;
                }
                strings.Add(input.Substring(from, to - from));

            } while (from != -1 && to != input.Length);

            return strings;
        }

        private void SwapLetters(ref string word, int i, int j)
        {
            if (i > j)
            {
                var t = i;
                i = j;
                j = t;
            }
            if (j >= word.Length)
            {
                return;
            }

            var letters = word.ToCharArray();
            var c = word[i];
            letters[i] = letters[j];
            letters[j] = c;

            word = new string(letters);
        }
    }
}

