namespace Crypto_kr
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
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.IsDetailedLog = new System.Windows.Forms.CheckBox();
            this.label3 = new System.Windows.Forms.Label();
            this.comboBoxB = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBoxG = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBoxR = new System.Windows.Forms.ComboBox();
            this.buttonStart = new System.Windows.Forms.Button();
            this.textBox = new System.Windows.Forms.TextBox();
            this.radioButtonDecode = new System.Windows.Forms.RadioButton();
            this.radioButtonEncode = new System.Windows.Forms.RadioButton();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.buttonSave = new System.Windows.Forms.Button();
            this.buttonLoad = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.labelInfo = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(12, 6);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(640, 480);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.WaitOnLoad = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button1);
            this.groupBox1.Controls.Add(this.IsDetailedLog);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.comboBoxB);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.comboBoxG);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.comboBoxR);
            this.groupBox1.Controls.Add(this.buttonStart);
            this.groupBox1.Controls.Add(this.textBox);
            this.groupBox1.Controls.Add(this.radioButtonDecode);
            this.groupBox1.Controls.Add(this.radioButtonEncode);
            this.groupBox1.Location = new System.Drawing.Point(662, 67);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 425);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Текст";
            // 
            // IsDetailedLog
            // 
            this.IsDetailedLog.AutoSize = true;
            this.IsDetailedLog.Checked = true;
            this.IsDetailedLog.CheckState = System.Windows.Forms.CheckState.Checked;
            this.IsDetailedLog.Location = new System.Drawing.Point(6, 89);
            this.IsDetailedLog.Name = "IsDetailedLog";
            this.IsDetailedLog.Size = new System.Drawing.Size(104, 17);
            this.IsDetailedLog.TabIndex = 14;
            this.IsDetailedLog.Text = "Детальный лог";
            this.IsDetailedLog.UseVisualStyleBackColor = true;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(134, 65);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(17, 13);
            this.label3.TabIndex = 13;
            this.label3.Text = "B:";
            // 
            // comboBoxB
            // 
            this.comboBoxB.FormattingEnabled = true;
            this.comboBoxB.Location = new System.Drawing.Point(152, 62);
            this.comboBoxB.MaxLength = 1;
            this.comboBoxB.Name = "comboBoxB";
            this.comboBoxB.Size = new System.Drawing.Size(33, 21);
            this.comboBoxB.Sorted = true;
            this.comboBoxB.TabIndex = 12;
            this.comboBoxB.SelectedIndexChanged += new System.EventHandler(this.comboBox_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(70, 65);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(18, 13);
            this.label2.TabIndex = 11;
            this.label2.Text = "G:";
            // 
            // comboBoxG
            // 
            this.comboBoxG.FormattingEnabled = true;
            this.comboBoxG.Location = new System.Drawing.Point(88, 62);
            this.comboBoxG.MaxLength = 1;
            this.comboBoxG.Name = "comboBoxG";
            this.comboBoxG.Size = new System.Drawing.Size(33, 21);
            this.comboBoxG.Sorted = true;
            this.comboBoxG.TabIndex = 10;
            this.comboBoxG.SelectedIndexChanged += new System.EventHandler(this.comboBox_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 65);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(18, 13);
            this.label1.TabIndex = 9;
            this.label1.Text = "R:";
            // 
            // comboBoxR
            // 
            this.comboBoxR.FormattingEnabled = true;
            this.comboBoxR.Location = new System.Drawing.Point(24, 62);
            this.comboBoxR.MaxLength = 1;
            this.comboBoxR.Name = "comboBoxR";
            this.comboBoxR.Size = new System.Drawing.Size(33, 21);
            this.comboBoxR.Sorted = true;
            this.comboBoxR.TabIndex = 8;
            this.comboBoxR.SelectedIndexChanged += new System.EventHandler(this.comboBox_SelectedIndexChanged);
            // 
            // buttonStart
            // 
            this.buttonStart.Location = new System.Drawing.Point(0, 395);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(75, 23);
            this.buttonStart.TabIndex = 7;
            this.buttonStart.Text = "Запустить";
            this.buttonStart.UseVisualStyleBackColor = true;
            this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // textBox
            // 
            this.textBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textBox.Location = new System.Drawing.Point(2, 110);
            this.textBox.Multiline = true;
            this.textBox.Name = "textBox";
            this.textBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox.Size = new System.Drawing.Size(188, 280);
            this.textBox.TabIndex = 4;
            // 
            // radioButtonDecode
            // 
            this.radioButtonDecode.AutoSize = true;
            this.radioButtonDecode.Location = new System.Drawing.Point(6, 42);
            this.radioButtonDecode.Name = "radioButtonDecode";
            this.radioButtonDecode.Size = new System.Drawing.Size(99, 17);
            this.radioButtonDecode.TabIndex = 1;
            this.radioButtonDecode.Text = "Декодировать";
            this.radioButtonDecode.UseVisualStyleBackColor = true;
            this.radioButtonDecode.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButtonEncode
            // 
            this.radioButtonEncode.AutoSize = true;
            this.radioButtonEncode.Checked = true;
            this.radioButtonEncode.Location = new System.Drawing.Point(6, 19);
            this.radioButtonEncode.Name = "radioButtonEncode";
            this.radioButtonEncode.Size = new System.Drawing.Size(85, 17);
            this.radioButtonEncode.TabIndex = 0;
            this.radioButtonEncode.TabStop = true;
            this.radioButtonEncode.Text = "Кодировать";
            this.radioButtonEncode.UseVisualStyleBackColor = true;
            this.radioButtonEncode.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // buttonSave
            // 
            this.buttonSave.Location = new System.Drawing.Point(6, 19);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(88, 25);
            this.buttonSave.TabIndex = 2;
            this.buttonSave.Text = "Сохранить";
            this.buttonSave.UseVisualStyleBackColor = true;
            this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
            // 
            // buttonLoad
            // 
            this.buttonLoad.Location = new System.Drawing.Point(106, 19);
            this.buttonLoad.Name = "buttonLoad";
            this.buttonLoad.Size = new System.Drawing.Size(88, 25);
            this.buttonLoad.TabIndex = 3;
            this.buttonLoad.Text = "Загрузить";
            this.buttonLoad.UseVisualStyleBackColor = true;
            this.buttonLoad.Click += new System.EventHandler(this.buttonLoad_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.buttonLoad);
            this.groupBox2.Controls.Add(this.buttonSave);
            this.groupBox2.Location = new System.Drawing.Point(658, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(204, 49);
            this.groupBox2.TabIndex = 4;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Фото";
            // 
            // labelInfo
            // 
            this.labelInfo.AutoSize = true;
            this.labelInfo.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelInfo.Location = new System.Drawing.Point(15, 496);
            this.labelInfo.Name = "labelInfo";
            this.labelInfo.Size = new System.Drawing.Size(0, 15);
            this.labelInfo.TabIndex = 5;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(115, 395);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 15;
            this.button1.Text = "Отчистить";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(874, 521);
            this.Controls.Add(this.labelInfo);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.pictureBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(890, 560);
            this.MinimumSize = new System.Drawing.Size(890, 560);
            this.Name = "Form1";
            this.ShowIcon = false;
            this.Text = "Кодирование скрытого текста в изображении";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton radioButtonDecode;
        private System.Windows.Forms.RadioButton radioButtonEncode;
        private System.Windows.Forms.TextBox textBox;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.Button buttonLoad;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.ComboBox comboBoxR;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboBoxB;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBoxG;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label labelInfo;
        private System.Windows.Forms.CheckBox IsDetailedLog;
        private System.Windows.Forms.Button button1;
    }
}

