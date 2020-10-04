using System;
using System.Windows.Forms;

namespace Calculator_v2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            m_left = new Argument(textBox1);
            m_right = new Argument(textBox2);
            m_chosen = m_left;

            ClearAll();
        }

        private void Number_Click(object sender, EventArgs e)
        {
            Button pressedButton = sender as Button;
            if (byte.TryParse(pressedButton.Text, out byte arg))
            {
                m_chosen.Add(arg);
            }
        }

        private void Divide_Click(object sender, EventArgs e)
        {
            m_sign = SignType.DIVIDE;
            label1.Text = "/";
            m_chosen = m_right;
        }

        private void Multiply_Click(object sender, EventArgs e)
        {
            m_sign = SignType.MULTIPLY;
            label1.Text = "*";
            m_chosen = m_right;
        }

        private void Minus_Click(object sender, EventArgs e)
        {
            m_sign = SignType.MINUS;
            label1.Text = "-";
            m_chosen = m_right;
        }

        private void Plus_Click(object sender, EventArgs e)
        {
            m_sign = SignType.PLUS;
            label1.Text = "+";
            m_chosen = m_right;
        }

        private void ClearAll()
        {
            m_left.Reset();
            m_right.Reset();
            m_chosen = m_left;

            label1.Text = "";
            label2.Text = "";
        }

        private void RemoveAll_Click(object sender, EventArgs e)
        {
            ClearAll();
        }
        
        private void Remove_Click(object sender, EventArgs e)
        {
            if (m_right.TextBox.Text.Length != 0)
            {
                m_right.Reset();
                m_chosen = m_right;
            }
            else
            {
                ClearAll();
            }
        }

        private void Equal_Click(object sender, EventArgs e)
        {
            if (m_left.TextBox.Text.Length != 0 && m_right.TextBox.Text.Length != 0)
            {
                bool dividedByZero = false;
                double res = 0.0f;
                switch (m_sign)
                {
                    case SignType.PLUS:
                        res = m_left.Value + m_right.Value;
                        break;
                    case SignType.MINUS:
                        res = m_left.Value - m_right.Value;
                        break;
                    case SignType.MULTIPLY:
                        res = m_left.Value * m_right.Value;
                        break;
                    case SignType.DIVIDE:
                        if (m_right.Value == 0.0f)
                        {
                            dividedByZero = true;
                            break;
                        }
                        res = m_left.Value / m_right.Value;
                        break;
                }

                if (dividedByZero)
                {
                    MessageBox.Show(new DivideByZeroException().ToString(), "Error :c", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else
                {
                    label2.Text = res.ToString();
                }
            }
        }

        private void Dot_Click(object sender, EventArgs e)
        {
            if (!m_chosen.Dot)
            {
                m_chosen.Dot = true;
            }
        }

        private void TextBox_Click(object sender, EventArgs e)
        {
            var textBox = sender as TextBox;
            if (textBox == m_left.TextBox)
            {
                m_chosen = m_left;
            }
            else if (textBox == m_right.TextBox)
            {
                m_chosen = m_right;
            }
        }

        private void TextBox_Changed(object sender, EventArgs e)
        {
            // TextBox_Changed также вызывается при инициализации всех компонент окна,
            // а потому m_chosen еще может не существовать
            if (m_chosen != null)
            {
                m_chosen.TextBox.Text = (sender as TextBox).Text;
            }
        }

        private void TextBox_KeyDown(object sender, KeyEventArgs e)
        {
            e.SuppressKeyPress = true;
        }

        private enum SignType
        {
            PLUS, MINUS, MULTIPLY, DIVIDE
        };

        private SignType m_sign;

        private class Argument
        {
            public Argument(TextBox textBox)
            {
                TextBox = textBox;
                Reset();
            }

            public void Add(byte digit)
            {
                TextBox.Text += digit.ToString();
            }

            public void Reset()
            {
                Dot = false;
                TextBox.Text = "";
            }

            public double Value
            {
                get
                {
                    return double.Parse(TextBox.Text);
                }
                set
                {
                    TextBox.Text = value.ToString();
                }
            }

            public bool Dot
            {
                get { return m_dot; }
                set
                {
                    if (!m_dot)
                    {
                        m_dot = true;
                        TextBox.Text += ".";
                    }
                }
            }

            public TextBox TextBox { get; set; }

            private bool m_dot;
        };

        private Argument m_left, m_right, m_chosen;

    }
}