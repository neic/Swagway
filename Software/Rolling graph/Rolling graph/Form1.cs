using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports; // Serial port
using System.Text.RegularExpressions; // Regex
using System.Globalization; // . and ,
using System.Windows.Forms.DataVisualization; // Chart

namespace Rolling_graph
{
    public partial class Form1 : Form
    {
        string readFromUART;
        string rxStringBuffer;
        List<string> rxListBuffer = new List<string>();
        int packageCount = 0;
        int oldPackageCount = 0;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            /* Serial Port */
            LoadSerialPorts();
            cbComPort.SelectedIndex = 1;
            cbSpeed.SelectedIndex = 10; // 115200 as default

        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort.IsOpen)
            {
                serialPort.Close();
            }
        }

        private void LoadSerialPorts()
        {
            cbComPort.Items.Clear();

            foreach (string s in SerialPort.GetPortNames())
            {
                cbComPort.Items.Add(s);
            }

            if (cbComPort.Items.Count > 0)
            {
                cbComPort.SelectedIndex = 0;
            }
            else
            {
                lbConnectionStatus.Text = "No COM-ports found";
            }
        }

        /* Settings */
        private void btReload_Click(object sender, EventArgs e)
        {
            LoadSerialPorts();
        }

        private void btConnect_Click(object sender, EventArgs e)
        {
            if (btConnect.Text == "Connect")
            {
                if (!serialPort.IsOpen)
                {
                    serialPort.PortName = cbComPort.SelectedItem.ToString();
                    serialPort.BaudRate = int.Parse(cbSpeed.SelectedItem.ToString());
                    serialPort.Open();
                }

                if (serialPort.IsOpen)
                {
                    lbConnectionStatus.Text = "Connected to: " + serialPort.PortName;
                    btConnect.Text = "Disconnect";
                }
            }
            else
            {
                if (serialPort.IsOpen)
                {
                    serialPort.Close();
                }
                lbConnectionStatus.Text = "Disconnected";
                btConnect.Text = "Connect";

            }
        }

        /* Serial Port & monitor*/
        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            readFromUART = serialPort.ReadExisting();
            this.BeginInvoke(new EventHandler(ReadToMonitor));
        }

        private void ReadToMonitor(object sender, EventArgs e)
        {
            
            int pos = tbMonitor.SelectionStart;
            tbMonitor.AppendText(readFromUART);
            CleanData(readFromUART);
        }

        private void CleanData(string input)
        {
            rxStringBuffer += input; // Add the input to a buffer
            rxListBuffer = rxStringBuffer.Split('<').ToList(); // Split everything in that buffer to a list
            rxStringBuffer = rxListBuffer[rxListBuffer.Count() - 1]; // Take the last bit of text and make put it back to the buffer
            rxListBuffer.Remove(rxListBuffer.Last()); // Remove it from the list

            for (int i = 0; i < rxListBuffer.Count(); i++)
            {
                /* Remove everything after '>' */
                int j = rxListBuffer[i].IndexOf('>');
                if (j > 0)
                {
                    rxListBuffer[i] = rxListBuffer[i].Substring(0, j);
                }
                /* End remove */

                if (Regex.Match(rxListBuffer[i], @"^((-?\d{1,3}[.]\d\d,){3,3}\d{4,})$").Success)
                {
                    string[] stringPackage = rxListBuffer[i].Split(',').ToArray();
                    float[] floatPackage = new float[4];

                    for (int k = 0; k < stringPackage.Length; k++)
			        {
                        float.TryParse(stringPackage[k], NumberStyles.Float, CultureInfo.InvariantCulture, out floatPackage[k]);
		        	}
                    packageCount++;

                    plotPackage(floatPackage);
                }
            }
        }
        private void SendToSerial()
        {
            if (serialPort.IsOpen)
            {
                serialPort.Write(tbSend.Text);
                tbSend.Text = "";
            }
        }
        private void btSendMon_Click(object sender, EventArgs e)
        {
            SendToSerial();
        }

        private void tbSend_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                SendToSerial();
            }
        }
        /* Graph */
        private void plotPackage(float[] package)
        {
           for (int i = 0; i < package.Length-1; i++)
			{
                chart1.Series[i].Points.AddY(package[i]);
			}
           if (packageCount > 500)
           {
               for (int i = 0; i < package.Length-1; i++)
               {
                   chart1.Series[i].Points.RemoveAt(0);
               }
               
           }
           
        }

        /* Statusbar */
        private void timerSample_Tick(object sender, EventArgs e)
        {
            int diff = packageCount - oldPackageCount;
            lbSamplesPerSec.Text = diff.ToString() + " Samples/sec";
            
            if (diff>pbSamplesPerSec.Maximum)
            {
                pbSamplesPerSec.Maximum = diff;
            }

            pbSamplesPerSec.Value = diff;
           
            oldPackageCount = packageCount;
        }
    }
}