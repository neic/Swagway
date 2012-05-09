namespace Rolling_graph
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
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabSettings = new System.Windows.Forms.TabPage();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.udPackages = new System.Windows.Forms.NumericUpDown();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btReload = new System.Windows.Forms.Button();
            this.cbComPort = new System.Windows.Forms.ComboBox();
            this.btConnect = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.cbSpeed = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.tabMonitor = new System.Windows.Forms.TabPage();
            this.btSendMon = new System.Windows.Forms.Button();
            this.tbSend = new System.Windows.Forms.TextBox();
            this.tbMonitor = new System.Windows.Forms.TextBox();
            this.tabGraph = new System.Windows.Forms.TabPage();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.lbConnectionStatus = new System.Windows.Forms.ToolStripStatusLabel();
            this.lbFiller = new System.Windows.Forms.ToolStripStatusLabel();
            this.pbSamplesPerSec = new System.Windows.Forms.ToolStripProgressBar();
            this.lbSamplesPerSec = new System.Windows.Forms.ToolStripStatusLabel();
            this.timerSample = new System.Windows.Forms.Timer(this.components);
            this.tabControl1.SuspendLayout();
            this.tabSettings.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udPackages)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.tabMonitor.SuspendLayout();
            this.tabGraph.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabSettings);
            this.tabControl1.Controls.Add(this.tabMonitor);
            this.tabControl1.Controls.Add(this.tabGraph);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(568, 417);
            this.tabControl1.TabIndex = 1;
            // 
            // tabSettings
            // 
            this.tabSettings.Controls.Add(this.groupBox2);
            this.tabSettings.Controls.Add(this.groupBox1);
            this.tabSettings.Location = new System.Drawing.Point(4, 22);
            this.tabSettings.Name = "tabSettings";
            this.tabSettings.Padding = new System.Windows.Forms.Padding(3);
            this.tabSettings.Size = new System.Drawing.Size(560, 391);
            this.tabSettings.TabIndex = 1;
            this.tabSettings.Text = "Settings";
            this.tabSettings.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.udPackages);
            this.groupBox2.Location = new System.Drawing.Point(153, 6);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(141, 161);
            this.groupBox2.TabIndex = 9;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Graph";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(4, 16);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(87, 13);
            this.label3.TabIndex = 1;
            this.label3.Text = "Number of points";
            // 
            // udPackages
            // 
            this.udPackages.Increment = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.udPackages.Location = new System.Drawing.Point(7, 32);
            this.udPackages.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.udPackages.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.udPackages.Name = "udPackages";
            this.udPackages.Size = new System.Drawing.Size(120, 20);
            this.udPackages.TabIndex = 0;
            this.udPackages.Value = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btReload);
            this.groupBox1.Controls.Add(this.cbComPort);
            this.groupBox1.Controls.Add(this.btConnect);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.cbSpeed);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Location = new System.Drawing.Point(8, 6);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(139, 161);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Serial";
            // 
            // btReload
            // 
            this.btReload.Location = new System.Drawing.Point(9, 59);
            this.btReload.Name = "btReload";
            this.btReload.Size = new System.Drawing.Size(121, 23);
            this.btReload.TabIndex = 5;
            this.btReload.Text = "Reload COM Ports";
            this.btReload.UseVisualStyleBackColor = true;
            this.btReload.Click += new System.EventHandler(this.btReload_Click);
            // 
            // cbComPort
            // 
            this.cbComPort.FormattingEnabled = true;
            this.cbComPort.Location = new System.Drawing.Point(9, 32);
            this.cbComPort.Name = "cbComPort";
            this.cbComPort.Size = new System.Drawing.Size(121, 21);
            this.cbComPort.TabIndex = 0;
            // 
            // btConnect
            // 
            this.btConnect.Location = new System.Drawing.Point(9, 128);
            this.btConnect.Name = "btConnect";
            this.btConnect.Size = new System.Drawing.Size(121, 23);
            this.btConnect.TabIndex = 4;
            this.btConnect.Text = "Connect";
            this.btConnect.UseVisualStyleBackColor = true;
            this.btConnect.Click += new System.EventHandler(this.btConnect_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "COM Port";
            // 
            // cbSpeed
            // 
            this.cbSpeed.FormattingEnabled = true;
            this.cbSpeed.Items.AddRange(new object[] {
            "300",
            "1200",
            "2400",
            "4800",
            "9600",
            "14400",
            "19200",
            "28800",
            "38400",
            "57600",
            "115200"});
            this.cbSpeed.Location = new System.Drawing.Point(9, 101);
            this.cbSpeed.Name = "cbSpeed";
            this.cbSpeed.Size = new System.Drawing.Size(121, 21);
            this.cbSpeed.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 85);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(38, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Speed";
            // 
            // tabMonitor
            // 
            this.tabMonitor.Controls.Add(this.btSendMon);
            this.tabMonitor.Controls.Add(this.tbSend);
            this.tabMonitor.Controls.Add(this.tbMonitor);
            this.tabMonitor.Location = new System.Drawing.Point(4, 22);
            this.tabMonitor.Name = "tabMonitor";
            this.tabMonitor.Padding = new System.Windows.Forms.Padding(3);
            this.tabMonitor.Size = new System.Drawing.Size(560, 391);
            this.tabMonitor.TabIndex = 3;
            this.tabMonitor.Text = "Monitor";
            this.tabMonitor.UseVisualStyleBackColor = true;
            // 
            // btSendMon
            // 
            this.btSendMon.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btSendMon.Location = new System.Drawing.Point(477, 6);
            this.btSendMon.Name = "btSendMon";
            this.btSendMon.Size = new System.Drawing.Size(75, 23);
            this.btSendMon.TabIndex = 2;
            this.btSendMon.Text = "Send";
            this.btSendMon.UseVisualStyleBackColor = true;
            this.btSendMon.Click += new System.EventHandler(this.btSendMon_Click);
            // 
            // tbSend
            // 
            this.tbSend.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tbSend.Location = new System.Drawing.Point(3, 8);
            this.tbSend.Name = "tbSend";
            this.tbSend.Size = new System.Drawing.Size(471, 20);
            this.tbSend.TabIndex = 1;
            this.tbSend.KeyDown += new System.Windows.Forms.KeyEventHandler(this.tbSend_KeyDown);
            // 
            // tbMonitor
            // 
            this.tbMonitor.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tbMonitor.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbMonitor.Location = new System.Drawing.Point(3, 35);
            this.tbMonitor.Multiline = true;
            this.tbMonitor.Name = "tbMonitor";
            this.tbMonitor.ReadOnly = true;
            this.tbMonitor.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.tbMonitor.Size = new System.Drawing.Size(551, 335);
            this.tbMonitor.TabIndex = 0;
            this.tbMonitor.WordWrap = false;
            // 
            // tabGraph
            // 
            this.tabGraph.Controls.Add(this.chart1);
            this.tabGraph.Location = new System.Drawing.Point(4, 22);
            this.tabGraph.Name = "tabGraph";
            this.tabGraph.Padding = new System.Windows.Forms.Padding(3);
            this.tabGraph.Size = new System.Drawing.Size(560, 391);
            this.tabGraph.TabIndex = 0;
            this.tabGraph.Text = "Graph";
            this.tabGraph.UseVisualStyleBackColor = true;
            // 
            // chart1
            // 
            chartArea1.AxisX.IsReversed = true;
            chartArea1.AxisX.Maximum = 500D;
            chartArea1.AxisX.Minimum = 0D;
            chartArea1.AxisY.Maximum = 180D;
            chartArea1.AxisY.Minimum = -180D;
            chartArea1.Name = "ChartArea_rolling";
            this.chart1.ChartAreas.Add(chartArea1);
            this.chart1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.chart1.Location = new System.Drawing.Point(3, 3);
            this.chart1.Name = "chart1";
            this.chart1.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.Bright;
            series1.ChartArea = "ChartArea_rolling";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            series1.Name = "Gyro_rolling";
            series2.ChartArea = "ChartArea_rolling";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            series2.Name = "Acc_rolling";
            series3.ChartArea = "ChartArea_rolling";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            series3.Name = "Est_rolling";
            this.chart1.Series.Add(series1);
            this.chart1.Series.Add(series2);
            this.chart1.Series.Add(series3);
            this.chart1.Size = new System.Drawing.Size(554, 385);
            this.chart1.TabIndex = 0;
            this.chart1.Text = "chart1";
            // 
            // serialPort
            // 
            this.serialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort_DataReceived);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.lbConnectionStatus,
            this.lbFiller,
            this.pbSamplesPerSec,
            this.lbSamplesPerSec});
            this.statusStrip1.Location = new System.Drawing.Point(0, 395);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(568, 22);
            this.statusStrip1.TabIndex = 2;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // lbConnectionStatus
            // 
            this.lbConnectionStatus.Name = "lbConnectionStatus";
            this.lbConnectionStatus.Size = new System.Drawing.Size(104, 17);
            this.lbConnectionStatus.Text = "Connection Status";
            // 
            // lbFiller
            // 
            this.lbFiller.Name = "lbFiller";
            this.lbFiller.Size = new System.Drawing.Size(237, 17);
            this.lbFiller.Spring = true;
            // 
            // pbSamplesPerSec
            // 
            this.pbSamplesPerSec.Maximum = 110;
            this.pbSamplesPerSec.Name = "pbSamplesPerSec";
            this.pbSamplesPerSec.Size = new System.Drawing.Size(110, 16);
            this.pbSamplesPerSec.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            // 
            // lbSamplesPerSec
            // 
            this.lbSamplesPerSec.AutoSize = false;
            this.lbSamplesPerSec.Name = "lbSamplesPerSec";
            this.lbSamplesPerSec.Size = new System.Drawing.Size(100, 17);
            this.lbSamplesPerSec.Text = "Samples/sec";
            this.lbSamplesPerSec.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // timerSample
            // 
            this.timerSample.Enabled = true;
            this.timerSample.Interval = 1000;
            this.timerSample.Tick += new System.EventHandler(this.timerSample_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(568, 417);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.tabControl1);
            this.Name = "Form1";
            this.Text = "Swagway Debugger";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabSettings.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udPackages)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.tabMonitor.ResumeLayout(false);
            this.tabMonitor.PerformLayout();
            this.tabGraph.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabGraph;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.TabPage tabSettings;
        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ComboBox cbSpeed;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cbComPort;
        private System.Windows.Forms.ToolStripStatusLabel lbConnectionStatus;
        private System.Windows.Forms.Button btConnect;
        private System.Windows.Forms.Button btReload;
        private System.Windows.Forms.TabPage tabMonitor;
        private System.Windows.Forms.Button btSendMon;
        private System.Windows.Forms.TextBox tbSend;
        private System.Windows.Forms.TextBox tbMonitor;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.ToolStripStatusLabel lbFiller;
        private System.Windows.Forms.ToolStripProgressBar pbSamplesPerSec;
        private System.Windows.Forms.ToolStripStatusLabel lbSamplesPerSec;
        private System.Windows.Forms.Timer timerSample;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown udPackages;

    }
}

