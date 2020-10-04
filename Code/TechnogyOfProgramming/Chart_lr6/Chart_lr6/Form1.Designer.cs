namespace Chart_lr6
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.chart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.trackBarA = new System.Windows.Forms.TrackBar();
            this.label1 = new System.Windows.Forms.Label();
            this.trackBarB = new System.Windows.Forms.TrackBar();
            ((System.ComponentModel.ISupportInitialize)(this.chart)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarA)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarB)).BeginInit();
            this.SuspendLayout();
            // 
            // chart
            // 
            this.chart.Location = new System.Drawing.Point(12, 12);
            this.chart.Name = "chart";
            this.chart.Size = new System.Drawing.Size(775, 464);
            this.chart.TabIndex = 0;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label2.Location = new System.Drawing.Point(823, 24);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(55, 17);
            this.label2.TabIndex = 2;
            this.label2.Text = "MinX  =";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label3.Location = new System.Drawing.Point(823, 52);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(54, 17);
            this.label3.TabIndex = 3;
            this.label3.Text = "MaxX =";
            // 
            // textBox1
            // 
            this.textBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.textBox1.Location = new System.Drawing.Point(882, 21);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(57, 23);
            this.textBox1.TabIndex = 4;
            this.textBox1.Text = "-0,14";
            // 
            // textBox2
            // 
            this.textBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.textBox2.Location = new System.Drawing.Point(882, 49);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(57, 23);
            this.textBox2.TabIndex = 5;
            this.textBox2.Text = "55";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label4.Location = new System.Drawing.Point(839, 85);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(21, 17);
            this.label4.TabIndex = 6;
            this.label4.Text = "Y:";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(828, 392);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(98, 28);
            this.button1.TabIndex = 10;
            this.button1.Text = "Apply";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.OnApply);
            // 
            // textBox5
            // 
            this.textBox5.Location = new System.Drawing.Point(793, 436);
            this.textBox5.Multiline = true;
            this.textBox5.Name = "textBox5";
            this.textBox5.ReadOnly = true;
            this.textBox5.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox5.Size = new System.Drawing.Size(166, 40);
            this.textBox5.TabIndex = 12;
            this.textBox5.Text = "Error message:\r\nSome wrong happened";
            // 
            // trackBarA
            // 
            this.trackBarA.Location = new System.Drawing.Point(828, 105);
            this.trackBarA.Maximum = 100;
            this.trackBarA.Name = "trackBarA";
            this.trackBarA.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.trackBarA.Size = new System.Drawing.Size(45, 281);
            this.trackBarA.TabIndex = 13;
            this.trackBarA.TickStyle = System.Windows.Forms.TickStyle.TopLeft;
            this.trackBarA.Value = 30;
            this.trackBarA.ValueChanged += new System.EventHandler(this.OnApply);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label1.Location = new System.Drawing.Point(898, 85);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(21, 17);
            this.label1.TabIndex = 14;
            this.label1.Text = "Z:";
            // 
            // trackBarB
            // 
            this.trackBarB.Location = new System.Drawing.Point(896, 105);
            this.trackBarB.Maximum = 100;
            this.trackBarB.Name = "trackBarB";
            this.trackBarB.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.trackBarB.Size = new System.Drawing.Size(45, 281);
            this.trackBarB.TabIndex = 15;
            this.trackBarB.Value = 66;
            this.trackBarB.ValueChanged += new System.EventHandler(this.OnApply);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(974, 488);
            this.Controls.Add(this.trackBarB);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.trackBarA);
            this.Controls.Add(this.textBox5);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.chart);
            this.Name = "Form1";
            this.Text = "Chart";
            ((System.ComponentModel.ISupportInitialize)(this.chart)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarA)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarB)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart chart;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox textBox5;
        private System.Windows.Forms.TrackBar trackBarA;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TrackBar trackBarB;
    }
}

