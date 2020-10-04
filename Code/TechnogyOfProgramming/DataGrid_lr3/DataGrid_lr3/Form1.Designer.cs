namespace DataGrid_lr3
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
            this.dataGridSource1 = new System.Windows.Forms.DataGridView();
            this.button = new System.Windows.Forms.Button();
            this.dataGridSource2 = new System.Windows.Forms.DataGridView();
            this.dataGridResult = new System.Windows.Forms.DataGridView();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridSource1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridSource2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridResult)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridSource1
            // 
            this.dataGridSource1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridSource1.Location = new System.Drawing.Point(12, 12);
            this.dataGridSource1.Name = "dataGridSource1";
            this.dataGridSource1.Size = new System.Drawing.Size(406, 264);
            this.dataGridSource1.TabIndex = 0;
            // 
            // button
            // 
            this.button.Location = new System.Drawing.Point(424, 282);
            this.button.Name = "button";
            this.button.Size = new System.Drawing.Size(406, 264);
            this.button.TabIndex = 3;
            this.button.Text = "Start";
            this.button.UseVisualStyleBackColor = true;
            this.button.Click += new System.EventHandler(this.OnStart);
            // 
            // dataGridSource2
            // 
            this.dataGridSource2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridSource2.Location = new System.Drawing.Point(424, 12);
            this.dataGridSource2.Name = "dataGridSource2";
            this.dataGridSource2.Size = new System.Drawing.Size(406, 264);
            this.dataGridSource2.TabIndex = 4;
            // 
            // dataGridResult
            // 
            this.dataGridResult.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridResult.Location = new System.Drawing.Point(12, 282);
            this.dataGridResult.Name = "dataGridResult";
            this.dataGridResult.Size = new System.Drawing.Size(406, 264);
            this.dataGridResult.TabIndex = 5;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(843, 555);
            this.Controls.Add(this.dataGridResult);
            this.Controls.Add(this.dataGridSource2);
            this.Controls.Add(this.button);
            this.Controls.Add(this.dataGridSource1);
            this.Location = new System.Drawing.Point(100, 50);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "DataGrid lab 3";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridSource1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridSource2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridResult)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridSource1;
        private System.Windows.Forms.Button button;
        private System.Windows.Forms.DataGridView dataGridSource2;
        private System.Windows.Forms.DataGridView dataGridResult;
    }
}

