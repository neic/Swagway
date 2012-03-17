using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;

namespace Rolling_graph
{
    public partial class Form1 : Form
    {
        string RxString;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            /* Serial Port */
            LoadSerialPorts();
            cbSpeed.SelectedIndex = 4; // 9600 as default

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
                serialPort.Close();
                lbConnectionStatus.Text = "Disconnected";
                btConnect.Text = "Connect";

            }
        }

        /* Serial Port & monitor*/
        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            RxString = serialPort.ReadExisting();
            this.BeginInvoke(new EventHandler(ReadToMonitor));
        }

        private void ReadToMonitor(object sender, EventArgs e)
        {
            tbMonitor.AppendText(RxString);
        }

        private void btSendMon_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                serialPort.Write(tbSend.Text);
                tbSend.Text = "";
            }
        }

     
        

    }
}
