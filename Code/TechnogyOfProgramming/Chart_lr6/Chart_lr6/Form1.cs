using System;
using System.Diagnostics;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace Chart_lr6
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            InitializeChartArea();
            OnApply(null, null);
        }

        private void InitializeChartArea()
        {
            var area = new ChartArea()
            {
                Name = "graph",
                AxisX =
                {
                    LabelStyle =
                    {
                        Format = "{0:0.00}"
                    }
                }

            };
            chart.ChartAreas.Add(area);

            var series = new Series()
            {
                ChartArea = "graph",
                ChartType = SeriesChartType.Spline,
                BorderWidth = 3,
                LegendText = "b(x, y, z)"
            };
            chart.Series.Add(series);

            var legend = new Legend();
            chart.Legends.Add(legend);
        }

        private void DrawEmptyGraph()
        {
            chart.Series[0].Color = Color.Transparent;
            chart.Series[0].LegendText = " ";
            chart.ChartAreas[0].AxisX.Minimum = 0;
            chart.ChartAreas[0].AxisX.Maximum = 100;
            for (int i = 0; i < 100; i += 10)
            {
                chart.Series[0].Points.AddXY(i, i);
            }
        }

        private void DrawGraph()
        {
            if (_xData == null || _yData == null
                || _xData.Length <= 0 || _yData.Length <= 0
                || double.IsNaN(_xMin) || double.IsNaN(_xMax)
                || double.IsInfinity(_xMin) || double.IsInfinity(_xMax))
            {
                DrawEmptyGraph();
                return;
            }
            
            chart.Series[0].Color = Color.Blue;
            chart.Series[0].LegendText = "b(x, y, z)";

            chart.ChartAreas[0].AxisX.Minimum = _xMin;
            chart.ChartAreas[0].AxisX.Maximum = _xMax;
            
            chart.Series[0].Points.DataBindXY(_xData, _yData);
        }

        private void ComputeData()
        {
            const int count = 100;
            var step = Math.Max( Math.Abs(_xMax - _xMin) / count, 0.001);

            var xData = new double[count];
            var yData = new double[count];

            var yMax = double.NegativeInfinity;
            var yMin = double.PositiveInfinity;
            bool onlyInvalidNumbers = true;
            for (var i = 0; i < count; ++i)
            {
                xData[i] = _xMin + step * i;
                yData[i] = DoFunction(xData[i]);
                
                if (double.IsNaN(yData[i]) || double.IsInfinity(yData[i])) continue;

                yMax = Math.Max(yData[i], yMax);
                yMin = Math.Min(yData[i], yMin);

                onlyInvalidNumbers = false;
            }

            if (onlyInvalidNumbers)
            {
                return;
            }
            
            var newCount = 0;
            for (var i = 0; i < count; ++i)
            {
                if (double.IsNaN(yData[i]))
                {
                    continue;
                } 
                else if (double.IsNegativeInfinity(yData[i]))
                {
                    yData[newCount] = yMin;
                } 
                else if (double.IsPositiveInfinity(yData[i]))
                {
                    yData[newCount] = yMax;
                }
                else
                {
                    yData[newCount] = yData[i];
                }
                ++newCount;
            }
            
            _xData = new double[newCount];
            _yData = new double[newCount];
            for (int i = 0; i < newCount; ++i)
            {
                _xData[i] = xData[i];
                _yData[i] = yData[i];
            }
        }

        private double DoFunctionB(double x)
        {
            var t1 = Math.Pow(_paramA, Math.Pow(Math.Abs(x), 1.0 / 3.0));

            var t2 = Math.Pow(Math.Cos(_paramA), 3);
            
            var t3 = Math.Abs(x - _paramA) * (1.0 + Math.Pow(Math.Sin(_paramB), 2) / Math.Pow(x + _paramA, 1.0 / 2.0));

            var t4 = Math.Pow(Math.E, Math.Abs(x - _paramA)) + x / 2.0;

            var y = t1 + t2 * t3 / t4;

            return y;
        }

        private double DoFunctionF(double x)
        {
            var t1 = Math.Pow(Math.Pow(x - 1, 1.0 / 3.0) + _paramA, 1.0 / 4.0);

            var t2 = Math.Abs(x - _paramA);

            var t3 = Math.Pow(Math.Sin(_paramB), 2) + Math.Tan(_paramB);

            return t1 / (t2 * t3);
        }

        private double DoFunction(double x)
        {
            return DoFunctionB(x) - 2 * DoFunctionF(x);
        }

        private double Normilize(double x, double min, double max)
        {
            return (x - min) / (max - min);
        }

        private void OnApply(object sender, EventArgs e)
        {
            if (!double.TryParse(textBox1.Text, out var xMin)
                || !double.TryParse(textBox2.Text, out var xMax))
            {
                textBox5.Text = "X is incorrect";
                return;
            }

            if (xMin > xMax)
            {
                var t = xMin;
                xMin = xMax;
                xMax = t;
            }

            _xMax = xMax;
            _xMin = xMin;
            
            // Нормализируем значение трекера
            var n = Normilize(trackBarA.Value, trackBarA.Minimum, trackBarA.Maximum);
            _paramA = n;

            // Нормализируем значение трекера
            n = Normilize(trackBarB.Value, trackBarB.Minimum, trackBarB.Maximum);
            _paramB = n * (Math.PI / 2 - double.Epsilon);
            
            textBox5.Text = "Y = " + _paramA + Environment.NewLine + "Z = " + _paramB;

            ComputeData();
            DrawGraph();
        }

        private double[] _xData;
        private double[] _yData;

        private double _xMin;
        private double _xMax;

        private double _paramA, _paramB;
    }
}
