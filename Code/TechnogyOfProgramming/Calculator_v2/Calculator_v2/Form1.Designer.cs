namespace Calculator_v2
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
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.button9 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.button11 = new System.Windows.Forms.Button();
            this.button12 = new System.Windows.Forms.Button();
            this.button13 = new System.Windows.Forms.Button();
            this.button14 = new System.Windows.Forms.Button();
            this.button15 = new System.Windows.Forms.Button();
            this.button16 = new System.Windows.Forms.Button();
            this.button17 = new System.Windows.Forms.Button();
            this.button18 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textBox1.Location = new System.Drawing.Point(29, 12);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(233, 26);
            this.textBox1.TabIndex = 0;
            this.textBox1.Text = "%arg_1%";
            this.textBox1.Click += new System.EventHandler(this.TextBox_Click);
            this.textBox1.TextChanged += new System.EventHandler(this.TextBox_Changed);
            this.textBox1.KeyDown += new System.Windows.Forms.KeyEventHandler(this.TextBox_KeyDown);
            // 
            // textBox2
            // 
            this.textBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textBox2.Location = new System.Drawing.Point(29, 50);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(233, 26);
            this.textBox2.TabIndex = 1;
            this.textBox2.Text = "%arg_2%";
            this.textBox2.Click += new System.EventHandler(this.TextBox_Click);
            this.textBox2.KeyDown += new System.Windows.Forms.KeyEventHandler(this.TextBox_KeyDown);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(8, 32);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(21, 24);
            this.label1.TabIndex = 20;
            this.label1.Text = "+";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(25, 79);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(88, 20);
            this.label2.TabIndex = 21;
            this.label2.Text = "%answer%";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(12, 102);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(121, 23);
            this.button1.TabIndex = 18;
            this.button1.Text = "CE";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.RemoveAll_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(11, 131);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(58, 23);
            this.button2.TabIndex = 2;
            this.button2.Text = "1";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.Number_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(75, 131);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(58, 23);
            this.button3.TabIndex = 3;
            this.button3.Text = "2";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.Number_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(139, 131);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(58, 23);
            this.button4.TabIndex = 4;
            this.button4.Text = "3";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.Number_Click);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(203, 131);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(58, 23);
            this.button5.TabIndex = 15;
            this.button5.Text = "*";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.Multiply_Click);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(139, 102);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(58, 23);
            this.button6.TabIndex = 19;
            this.button6.Text = "C";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.Remove_Click);
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(203, 102);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(58, 23);
            this.button7.TabIndex = 16;
            this.button7.Text = "/";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.Divide_Click);
            // 
            // button8
            // 
            this.button8.Location = new System.Drawing.Point(203, 160);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(58, 23);
            this.button8.TabIndex = 14;
            this.button8.Text = "-";
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Click += new System.EventHandler(this.Minus_Click);
            // 
            // button9
            // 
            this.button9.Location = new System.Drawing.Point(139, 160);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(58, 23);
            this.button9.TabIndex = 7;
            this.button9.Text = "6";
            this.button9.UseVisualStyleBackColor = true;
            this.button9.Click += new System.EventHandler(this.Number_Click);
            // 
            // button10
            // 
            this.button10.Location = new System.Drawing.Point(75, 160);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(58, 23);
            this.button10.TabIndex = 6;
            this.button10.Text = "5";
            this.button10.UseVisualStyleBackColor = true;
            this.button10.Click += new System.EventHandler(this.Number_Click);
            // 
            // button11
            // 
            this.button11.Location = new System.Drawing.Point(11, 160);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(58, 23);
            this.button11.TabIndex = 5;
            this.button11.Text = "4";
            this.button11.UseVisualStyleBackColor = true;
            this.button11.Click += new System.EventHandler(this.Number_Click);
            // 
            // button12
            // 
            this.button12.Location = new System.Drawing.Point(203, 189);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(58, 23);
            this.button12.TabIndex = 13;
            this.button12.Text = "+";
            this.button12.UseVisualStyleBackColor = true;
            this.button12.Click += new System.EventHandler(this.Plus_Click);
            // 
            // button13
            // 
            this.button13.Location = new System.Drawing.Point(139, 189);
            this.button13.Name = "button13";
            this.button13.Size = new System.Drawing.Size(58, 23);
            this.button13.TabIndex = 10;
            this.button13.Text = "9";
            this.button13.UseVisualStyleBackColor = true;
            this.button13.Click += new System.EventHandler(this.Number_Click);
            // 
            // button14
            // 
            this.button14.Location = new System.Drawing.Point(75, 189);
            this.button14.Name = "button14";
            this.button14.Size = new System.Drawing.Size(58, 23);
            this.button14.TabIndex = 9;
            this.button14.Text = "8";
            this.button14.UseVisualStyleBackColor = true;
            this.button14.Click += new System.EventHandler(this.Number_Click);
            // 
            // button15
            // 
            this.button15.Location = new System.Drawing.Point(11, 189);
            this.button15.Name = "button15";
            this.button15.Size = new System.Drawing.Size(58, 23);
            this.button15.TabIndex = 8;
            this.button15.Text = "7";
            this.button15.UseVisualStyleBackColor = true;
            this.button15.Click += new System.EventHandler(this.Number_Click);
            // 
            // button16
            // 
            this.button16.Location = new System.Drawing.Point(203, 218);
            this.button16.Name = "button16";
            this.button16.Size = new System.Drawing.Size(58, 23);
            this.button16.TabIndex = 17;
            this.button16.Text = "=";
            this.button16.UseVisualStyleBackColor = true;
            this.button16.Click += new System.EventHandler(this.Equal_Click);
            // 
            // button17
            // 
            this.button17.Location = new System.Drawing.Point(139, 218);
            this.button17.Name = "button17";
            this.button17.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.button17.Size = new System.Drawing.Size(58, 23);
            this.button17.TabIndex = 12;
            this.button17.Text = ".";
            this.button17.UseVisualStyleBackColor = true;
            this.button17.Click += new System.EventHandler(this.Dot_Click);
            // 
            // button18
            // 
            this.button18.Location = new System.Drawing.Point(11, 218);
            this.button18.Name = "button18";
            this.button18.Size = new System.Drawing.Size(122, 23);
            this.button18.TabIndex = 11;
            this.button18.Text = "0";
            this.button18.UseVisualStyleBackColor = true;
            this.button18.Click += new System.EventHandler(this.Number_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(272, 251);
            this.Controls.Add(this.button16);
            this.Controls.Add(this.button17);
            this.Controls.Add(this.button18);
            this.Controls.Add(this.button12);
            this.Controls.Add(this.button13);
            this.Controls.Add(this.button14);
            this.Controls.Add(this.button15);
            this.Controls.Add(this.button8);
            this.Controls.Add(this.button9);
            this.Controls.Add(this.button10);
            this.Controls.Add(this.button11);
            this.Controls.Add(this.button7);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.textBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.Button button11;
        private System.Windows.Forms.Button button12;
        private System.Windows.Forms.Button button13;
        private System.Windows.Forms.Button button14;
        private System.Windows.Forms.Button button15;
        private System.Windows.Forms.Button button16;
        private System.Windows.Forms.Button button17;
        private System.Windows.Forms.Button button18;
    }
}

