namespace Array_lr2
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
            this.listBoxInput = new System.Windows.Forms.ListBox();
            this.listBoxOutput = new System.Windows.Forms.ListBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.buttonFill = new System.Windows.Forms.Button();
            this.buttonProcess = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // listBoxInput
            // 
            this.listBoxInput.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.listBoxInput.FormattingEnabled = true;
            this.listBoxInput.ItemHeight = 16;
            this.listBoxInput.Items.AddRange(new object[] {
            "-10",
            "10",
            "12",
            "131"});
            this.listBoxInput.Location = new System.Drawing.Point(12, 32);
            this.listBoxInput.Name = "listBoxInput";
            this.listBoxInput.Size = new System.Drawing.Size(163, 228);
            this.listBoxInput.TabIndex = 0;
            // 
            // listBoxOutput
            // 
            this.listBoxOutput.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.listBoxOutput.FormattingEnabled = true;
            this.listBoxOutput.ItemHeight = 16;
            this.listBoxOutput.Items.AddRange(new object[] {
            "-10",
            "10",
            "12",
            "131"});
            this.listBoxOutput.Location = new System.Drawing.Point(194, 32);
            this.listBoxOutput.Name = "listBoxOutput";
            this.listBoxOutput.Size = new System.Drawing.Size(160, 228);
            this.listBoxOutput.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold);
            this.label1.Location = new System.Drawing.Point(12, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(143, 17);
            this.label1.TabIndex = 2;
            this.label1.Text = "Исходный массив:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold);
            this.label2.Location = new System.Drawing.Point(191, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(163, 17);
            this.label2.TabIndex = 3;
            this.label2.Text = "Полученный массив:";
            // 
            // buttonFill
            // 
            this.buttonFill.Location = new System.Drawing.Point(12, 266);
            this.buttonFill.Name = "buttonFill";
            this.buttonFill.Size = new System.Drawing.Size(163, 23);
            this.buttonFill.TabIndex = 4;
            this.buttonFill.Text = "Заполнить";
            this.buttonFill.UseVisualStyleBackColor = true;
            this.buttonFill.Click += new System.EventHandler(this.OnFill);
            // 
            // buttonProcess
            // 
            this.buttonProcess.Location = new System.Drawing.Point(191, 266);
            this.buttonProcess.Name = "buttonProcess";
            this.buttonProcess.Size = new System.Drawing.Size(163, 23);
            this.buttonProcess.TabIndex = 5;
            this.buttonProcess.Text = "Обработать";
            this.buttonProcess.UseVisualStyleBackColor = true;
            this.buttonProcess.Click += new System.EventHandler(this.OnProcess);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(372, 300);
            this.Controls.Add(this.buttonProcess);
            this.Controls.Add(this.buttonFill);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.listBoxOutput);
            this.Controls.Add(this.listBoxInput);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox listBoxInput;
        private System.Windows.Forms.ListBox listBoxOutput;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button buttonFill;
        private System.Windows.Forms.Button buttonProcess;
    }
}

