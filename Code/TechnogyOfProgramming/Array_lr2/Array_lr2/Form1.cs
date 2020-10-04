using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.Design.Serialization;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Array_lr2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            listBoxInput.Items.Clear();
            listBoxOutput.Items.Clear();

            _array = new Array();
        }

        private void OnFill(object sender, EventArgs e)
        {
            _array.Fill(25);

            for (var i = 0; i < _array.Length; ++i)
            {
                listBoxInput.Items.Add(_array[i]);
            }
        }

        private void OnProcess(object sender, EventArgs e)
        {
            _array.Process();

            for (var i = 0; i < _array.Length; ++i)
            {
                listBoxOutput.Items.Add(_array[i]);
            }
        }
        
        private readonly Array _array;
    }

    internal class Array
    {
        public void Fill(int size)
        {
            _data = new int[size];

            var generator = new Random();
            for (var i = 0; i < _data.Length; ++i)
            {
                _data[i] = generator.Next(-10, 10);
            }
        }

        public void Process()
        {
            for (var i = 0; i < _data.Length; ++i)
            {
                var number = _data[i];
                if (number < 0)
                {
                    _data[i] = number * number;
                }
                else if (number > 0)
                {
                    _data[i] += 7;
                }
            }
        }

        public int this[int i] // индексатор
        {
            get => _data[i];
            set => _data[i] = value;
        }

        public int Length => _data.Length;
        
        private int[] _data;
    }
}
