namespace C_Meter_Tool
{
    partial class main
    {
        /// <summary>
        /// Erforderliche Designervariable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Verwendete Ressourcen bereinigen.
        /// </summary>
        /// <param name="disposing">True, wenn verwaltete Ressourcen gelöscht werden sollen; andernfalls False.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Vom Windows Form-Designer generierter Code

        /// <summary>
        /// Erforderliche Methode für die Designerunterstützung.
        /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(main));
            this.toolStripContainer1 = new System.Windows.Forms.ToolStripContainer();
            this.button_clear = new System.Windows.Forms.Button();
            this.textBox_c_log = new System.Windows.Forms.TextBox();
            this.label_c_actual = new System.Windows.Forms.Label();
            this.toolStrip_file = new System.Windows.Forms.ToolStrip();
            this.toolStripSplitButton_save = new System.Windows.Forms.ToolStripSplitButton();
            this.toolStripMenuItem_save = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_save_as = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton_print = new System.Windows.Forms.ToolStripButton();
            this.toolStrip_settings = new System.Windows.Forms.ToolStrip();
            this.toolStripComboBox_port = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripButton_connect = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton_timestamp = new System.Windows.Forms.ToolStripButton();
            this.toolStripContainer1.ContentPanel.SuspendLayout();
            this.toolStripContainer1.TopToolStripPanel.SuspendLayout();
            this.toolStripContainer1.SuspendLayout();
            this.toolStrip_file.SuspendLayout();
            this.toolStrip_settings.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStripContainer1
            // 
            this.toolStripContainer1.BottomToolStripPanelVisible = false;
            // 
            // toolStripContainer1.ContentPanel
            // 
            this.toolStripContainer1.ContentPanel.Controls.Add(this.button_clear);
            this.toolStripContainer1.ContentPanel.Controls.Add(this.textBox_c_log);
            this.toolStripContainer1.ContentPanel.Controls.Add(this.label_c_actual);
            this.toolStripContainer1.ContentPanel.Size = new System.Drawing.Size(242, 338);
            this.toolStripContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.toolStripContainer1.LeftToolStripPanelVisible = false;
            this.toolStripContainer1.Location = new System.Drawing.Point(0, 0);
            this.toolStripContainer1.Name = "toolStripContainer1";
            this.toolStripContainer1.RightToolStripPanelVisible = false;
            this.toolStripContainer1.Size = new System.Drawing.Size(242, 363);
            this.toolStripContainer1.TabIndex = 0;
            this.toolStripContainer1.Text = "toolStripContainer1";
            // 
            // toolStripContainer1.TopToolStripPanel
            // 
            this.toolStripContainer1.TopToolStripPanel.BackColor = System.Drawing.SystemColors.ControlDark;
            this.toolStripContainer1.TopToolStripPanel.Controls.Add(this.toolStrip_file);
            this.toolStripContainer1.TopToolStripPanel.Controls.Add(this.toolStrip_settings);
            // 
            // button_clear
            // 
            this.button_clear.Location = new System.Drawing.Point(12, 290);
            this.button_clear.Name = "button_clear";
            this.button_clear.Size = new System.Drawing.Size(218, 34);
            this.button_clear.TabIndex = 2;
            this.button_clear.Text = "Clear";
            this.button_clear.UseVisualStyleBackColor = true;
            this.button_clear.Click += new System.EventHandler(this.clear_log);
            // 
            // textBox_c_log
            // 
            this.textBox_c_log.Location = new System.Drawing.Point(12, 47);
            this.textBox_c_log.Multiline = true;
            this.textBox_c_log.Name = "textBox_c_log";
            this.textBox_c_log.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox_c_log.Size = new System.Drawing.Size(218, 236);
            this.textBox_c_log.TabIndex = 1;
            this.textBox_c_log.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label_c_actual
            // 
            this.label_c_actual.AutoSize = true;
            this.label_c_actual.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_c_actual.Location = new System.Drawing.Point(65, 19);
            this.label_c_actual.Name = "label_c_actual";
            this.label_c_actual.Size = new System.Drawing.Size(105, 25);
            this.label_c_actual.TabIndex = 0;
            this.label_c_actual.Text = "> 12.4uF";
            this.label_c_actual.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // toolStrip_file
            // 
            this.toolStrip_file.Dock = System.Windows.Forms.DockStyle.None;
            this.toolStrip_file.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripSplitButton_save,
            this.toolStripSeparator1,
            this.toolStripButton_print});
            this.toolStrip_file.Location = new System.Drawing.Point(3, 0);
            this.toolStrip_file.Name = "toolStrip_file";
            this.toolStrip_file.Size = new System.Drawing.Size(73, 25);
            this.toolStrip_file.TabIndex = 0;
            // 
            // toolStripSplitButton_save
            // 
            this.toolStripSplitButton_save.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripSplitButton_save.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem_save,
            this.toolStripMenuItem_save_as});
            this.toolStripSplitButton_save.Image = ((System.Drawing.Image)(resources.GetObject("toolStripSplitButton_save.Image")));
            this.toolStripSplitButton_save.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripSplitButton_save.Name = "toolStripSplitButton_save";
            this.toolStripSplitButton_save.Size = new System.Drawing.Size(32, 22);
            this.toolStripSplitButton_save.Text = "Save";
            // 
            // toolStripMenuItem_save
            // 
            this.toolStripMenuItem_save.Name = "toolStripMenuItem_save";
            this.toolStripMenuItem_save.Size = new System.Drawing.Size(152, 22);
            this.toolStripMenuItem_save.Text = "Save";
            // 
            // toolStripMenuItem_save_as
            // 
            this.toolStripMenuItem_save_as.Name = "toolStripMenuItem_save_as";
            this.toolStripMenuItem_save_as.Size = new System.Drawing.Size(152, 22);
            this.toolStripMenuItem_save_as.Text = "Save as";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton_print
            // 
            this.toolStripButton_print.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton_print.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton_print.Image")));
            this.toolStripButton_print.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton_print.Name = "toolStripButton_print";
            this.toolStripButton_print.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton_print.Text = "Print";
            // 
            // toolStrip_settings
            // 
            this.toolStrip_settings.Dock = System.Windows.Forms.DockStyle.None;
            this.toolStrip_settings.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripComboBox_port,
            this.toolStripButton_connect,
            this.toolStripSeparator2,
            this.toolStripButton_timestamp});
            this.toolStrip_settings.Location = new System.Drawing.Point(76, 0);
            this.toolStrip_settings.Name = "toolStrip_settings";
            this.toolStrip_settings.Size = new System.Drawing.Size(141, 25);
            this.toolStrip_settings.TabIndex = 1;
            // 
            // toolStripComboBox_port
            // 
            this.toolStripComboBox_port.Name = "toolStripComboBox_port";
            this.toolStripComboBox_port.Size = new System.Drawing.Size(75, 25);
            this.toolStripComboBox_port.Text = "Port";
            this.toolStripComboBox_port.DropDown += new System.EventHandler(this.update_portlist_event);
            // 
            // toolStripButton_connect
            // 
            this.toolStripButton_connect.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton_connect.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton_connect.Image")));
            this.toolStripButton_connect.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton_connect.Name = "toolStripButton_connect";
            this.toolStripButton_connect.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton_connect.Text = "Dis-/Connect";
            this.toolStripButton_connect.Click += new System.EventHandler(this.dis_connect_event);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton_timestamp
            // 
            this.toolStripButton_timestamp.CheckOnClick = true;
            this.toolStripButton_timestamp.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton_timestamp.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton_timestamp.Image")));
            this.toolStripButton_timestamp.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton_timestamp.Name = "toolStripButton_timestamp";
            this.toolStripButton_timestamp.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton_timestamp.Text = "Timestamp";
            // 
            // main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(242, 363);
            this.Controls.Add(this.toolStripContainer1);
            this.Name = "main";
            this.Text = "C-Meter Tool";
            this.Load += new System.EventHandler(this.main_Load);
            this.toolStripContainer1.ContentPanel.ResumeLayout(false);
            this.toolStripContainer1.ContentPanel.PerformLayout();
            this.toolStripContainer1.TopToolStripPanel.ResumeLayout(false);
            this.toolStripContainer1.TopToolStripPanel.PerformLayout();
            this.toolStripContainer1.ResumeLayout(false);
            this.toolStripContainer1.PerformLayout();
            this.toolStrip_file.ResumeLayout(false);
            this.toolStrip_file.PerformLayout();
            this.toolStrip_settings.ResumeLayout(false);
            this.toolStrip_settings.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ToolStripContainer toolStripContainer1;
        private System.Windows.Forms.ToolStrip toolStrip_file;
        private System.Windows.Forms.ToolStripSplitButton toolStripSplitButton_save;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem_save;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem_save_as;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton toolStripButton_print;
        private System.Windows.Forms.ToolStrip toolStrip_settings;
        private System.Windows.Forms.ToolStripComboBox toolStripComboBox_port;
        private System.Windows.Forms.ToolStripButton toolStripButton_connect;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton toolStripButton_timestamp;
        private System.Windows.Forms.Label label_c_actual;
        private System.Windows.Forms.TextBox textBox_c_log;
        private System.Windows.Forms.Button button_clear;
    }
}

