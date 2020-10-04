namespace TypeString_lr1
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
            this.listBox = new System.Windows.Forms.ListBox();
            this.countWordText = new System.Windows.Forms.Label();
            this.index1 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.index2 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.swappedText = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // listBox
            // 
            this.listBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.listBox.FormattingEnabled = true;
            this.listBox.ItemHeight = 20;
            this.listBox.Items.AddRange(new object[] {
            "1",
            "22",
            "33",
            "4444"});
            this.listBox.Location = new System.Drawing.Point(12, 12);
            this.listBox.Name = "listBox";
            this.listBox.Size = new System.Drawing.Size(317, 164);
            this.listBox.TabIndex = 0;
            // 
            // countWordText
            // 
            this.countWordText.AutoSize = true;
            this.countWordText.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.countWordText.Location = new System.Drawing.Point(12, 188);
            this.countWordText.Name = "countWordText";
            this.countWordText.Size = new System.Drawing.Size(207, 17);
            this.countWordText.TabIndex = 2;
            this.countWordText.Text = "Chosen string contains N words";
            // 
            // index1
            // 
            this.index1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.index1.Location = new System.Drawing.Point(299, 182);
            this.index1.Name = "index1";
            this.index1.Size = new System.Drawing.Size(30, 23);
            this.index1.TabIndex = 3;
            this.index1.Text = "1";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.ImageAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.label1.Location = new System.Drawing.Point(266, 185);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(27, 17);
            this.label1.TabIndex = 4;
            this.label1.Text = "i = ";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.ImageAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.label2.Location = new System.Drawing.Point(266, 211);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(27, 17);
            this.label2.TabIndex = 6;
            this.label2.Text = "j = ";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // index2
            // 
            this.index2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.index2.Location = new System.Drawing.Point(299, 208);
            this.index2.Name = "index2";
            this.index2.Size = new System.Drawing.Size(30, 23);
            this.index2.TabIndex = 5;
            this.index2.Text = "3";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(12, 223);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(102, 17);
            this.label3.TabIndex = 7;
            this.label3.Text = "After swapped:";
            // 
            // swappedText
            // 
            this.swappedText.AutoSize = true;
            this.swappedText.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.swappedText.Location = new System.Drawing.Point(12, 240);
            this.swappedText.Name = "swappedText";
            this.swappedText.Size = new System.Drawing.Size(201, 17);
            this.swappedText.TabIndex = 8;
            this.swappedText.Text = "Some text with swapped letters";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(269, 237);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(60, 20);
            this.button1.TabIndex = 9;
            this.button1.Text = "Start";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.OnStart);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(356, 266);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.swappedText);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.index2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.index1);
            this.Controls.Add(this.countWordText);
            this.Controls.Add(this.listBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.ShowIcon = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "Lab 1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox listBox;
        private System.Windows.Forms.Label countWordText;
        private System.Windows.Forms.TextBox index1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox index2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label swappedText;
        private System.Windows.Forms.Button button1;
    }
}

