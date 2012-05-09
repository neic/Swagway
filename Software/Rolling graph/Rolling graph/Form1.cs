using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports; // Seriel-porte
using System.Text.RegularExpressions; // Regular expressions
using System.Globalization; // Forskel på , og .
using System.Windows.Forms.DataVisualization; // Grafer

namespace Rolling_graph
{
  public partial class Form1 : Form
  {
    string readFromUART; // Holder data læst direkte fra UART
    string rxStringBuffer; // Holder rest af sidste pakke
    List<string> rxListBuffer = new List<string>(); // Holder pakker som liste

    int packageCount = 0;
    int oldPackageCount = 0;

    public Form1()
    {
      InitializeComponent();
    }

    /*****************/
    /* Indstillinger */
    /**********'******/

    /* Kaldes ved opstart: finder seriel-porte */
    private void Form1_Load(object sender, EventArgs e)
    {
      LoadSerialPorts(); // Opdater listen med serialporte
      cbSpeed.SelectedIndex = 10; // Sætter 115200 baud som standardindstilling
    }

    /* Kaldes ved afslutning: lukker seriel-porte */
    private void Form1_FormClosing(object sender, FormClosingEventArgs e)
    {
      if (serialPort.IsOpen) // Luk seriel-porten hvis den er åben
        {
          serialPort.Close();
        }
    }

    /* Finder systemets seriel-porte */
    private void LoadSerialPorts()
    {
      cbComPort.Items.Clear(); // Ryd listen

      foreach (string s in SerialPort.GetPortNames()) // For alle serielporte i systemet
        {
          cbComPort.Items.Add(s); // Føj til listen
        }

      if (cbComPort.Items.Count > 0) // Hvis der er fundet serielporte
        {
          cbComPort.SelectedIndex = 0; // Sætter den første serielport som standardinstilling
        }
      else
        {
          lbConnectionStatus.Text = "No COM-ports found"; // Ellers advar i statuslinjen
        }
    }

    /* Opdater listen med serielporte */
    private void btReload_Click(object sender, EventArgs e)
    {
      LoadSerialPorts();
    }

    /* Forbind og afbryd til serielporten */
    private void btConnect_Click(object sender, EventArgs e)
    {
      if (btConnect.Text == "Connect") // Hvis der skal forbindes
        {
          if (!serialPort.IsOpen) // Hvis der ikke er forbundet
            {
              serialPort.PortName = cbComPort.SelectedItem.ToString(); // Find navnet på porten
              serialPort.BaudRate = int.Parse(cbSpeed.SelectedItem.ToString()); // Find hastigheden
              serialPort.Open(); // Forbind
            }

          if (serialPort.IsOpen) // Hvis forbindelsen lykkedes
            {
              lbConnectionStatus.Text = "Connected to: " + serialPort.PortName; // Skriv i statuslinjen
              btConnect.Text = "Disconnect"; // Lav knappen om til afbryd
            }
        }
      else // Hvis der skal afbrydes
        {
          if (serialPort.IsOpen) // Hvis der er forbindelse
            {
              serialPort.Close(); // Afbryd
            }

          lbConnectionStatus.Text = "Disconnected"; // Skriv i status linjen
          btConnect.Text = "Connect"; // Lav knappen om til forbind
        }
    }

    /* Længden af X-aksen på grafen */
    private void udPackages_ValueChanged(object sender, EventArgs e) // Bliver kaldt hver gang tallet ændres
    {
      if (udPackages.Value <= 1000) // Hvis værdien er under eller ligemed 1000 skal den ændres med 100
        {
          udPackages.Increment = 100;
        }

      if (udPackages.Value > 1000) // Hvis værdien er over 1000 skal den ændres med 1000
        {
          udPackages.Increment = 1000;
        }

      if (udPackages.Value == 1100) // Er værdien 1100 skal den være 2000
        {
          udPackages.Value = 2000;
        }

      chart1.ChartAreas.First().AxisX.Maximum = (double)udPackages.Value; // Set X-aksens maksimum værdi
    }

    /****************************/
    /* Seriel: modtag & monitor */
    /****************************/

    /* Læs inkommende data til buffer og kald ReadToMonitor() */
    private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
    {
      readFromUART = serialPort.ReadExisting();
      this.BeginInvoke(new EventHandler(ReadToMonitor));
    }

    /* Skriver rå data til monitor, ryderop i monitor og kalder CleanData()*/
    private void ReadToMonitor(object sender, EventArgs e)
    {
      tbMonitor.AppendText(readFromUART); // Tilføjer til monitor

      if (tbMonitor.TextLength > 50000) // Hvis der mere end ca. 2000 pakker
        {
          tbMonitor.Lines = tbMonitor.Lines.Skip(20).ToArray(); // Slet 20 linjer
        }
            
      CleanData(readFromUART); // Kalder CleanData()
    }

    /* Tager rå data, rengør det og sender det til graf */
    private void CleanData(string input)
    {
      rxStringBuffer += input; // Tilføjer nyt rå data fra UART
      rxListBuffer = rxStringBuffer.Split('<').ToList(); // Splitter ved hver begyndelse af ny pakke '<'
      rxStringBuffer = rxListBuffer[rxListBuffer.Count() - 1]; // Ligger den sidste, ikke fuldstændige, pakke tilbage i buffer
      rxListBuffer.Remove(rxListBuffer.Last()); // Sletter den ikke fuldstendige pakke fra listen

      /* For alle nye pakker */
      for (int i = 0; i < rxListBuffer.Count(); i++)
        {
          /* Slet alt efter slutningen af pakken '>' */
          int j = rxListBuffer[i].IndexOf('>'); // Finder indexet af '>'
          if (j > 0)
            {
              rxListBuffer[i] = rxListBuffer[i].Substring(0, j); // Klipper fra begyndelsen til indexet af '>'
            }
          /* End : Selt efter slutning*/

          /* God pakke? Så plot den */
          if (Regex.Match(rxListBuffer[i], @"^((-?\d{1,3}[.]\d\d,){3,3}\d{4,})$").Success) //Pakken undersøges om den passer ind.
            {
              string[] stringPackage = rxListBuffer[i].Split(',').ToArray(); // Pakken splittes til et string-array
              float[] floatPackage = new float[4];

              for (int k = 0; k < stringPackage.Length; k++) // String-arrayet parses til et float-array
                {
                  float.TryParse(stringPackage[k], NumberStyles.Float, CultureInfo.InvariantCulture, out floatPackage[k]);
                  /* TryParse prøver at parse, hvis det ikke er muligt bliver pakken droppet.
                   * CultureInfo er nødvendigt for at kunne bruge "." som decimaltegn */
                }
                    
              packageCount++;
              plotPackage(floatPackage); // Send float-arrayet til grafen
            }
          /* End : God pakke */
        }
      /* End : For alle nye */
    }
        
    /****************/
    /* Seriel: send */
    /****************/

    /* Sender ud-buffer til seriel-porten */
    private void SendToSerial()
    {
      if (serialPort.IsOpen)
        {
          serialPort.Write(tbSend.Text); // Send ud-bufferen
          tbSend.Clear(); // Tøm ud-bufferen
        }
    }

    /* Kalder SendToSerial hvis "Send"-knappen trykkes ned */
    private void btSendMon_Click(object sender, EventArgs e)
    {
      SendToSerial();
    }

    /* Kalder SendToSerial hvis der trykkes enter i ud-bufferen */
    private void tbSend_KeyDown(object sender, KeyEventArgs e) // Kaldes ved hver ny tastetryk
    {
      if (e.KeyCode == Keys.Enter) // Er tastetrykket Enter?
        {
          SendToSerial();
        }
    }

    /********/
    /* Graf */
    /********/
    
    /* Tilføjer pakke til graf og rydder op */
    private void plotPackage(float[] package)
    {
      for (int i = 0; i < package.Length-1; i++) // Plot alle punkterne i pakken til hver sin serie
        {
          chart1.Series[i].Points.AddY(package[i]);
        }

      if (packageCount > udPackages.Value) // Slet alle pakker over grænseværdi
        {
          for (int i = 0; i < package.Length-1; i++)
            {
              chart1.Series[i].Points.RemoveAt(0);
            }
        }
    }

    /*************/
    /* Statusbar */
    /*************/

    /* Udregn antal pakker per sekund */
    private void timerSample_Tick(object sender, EventArgs e) // Kaldes hvert sekund
    {
      int diff = packageCount - oldPackageCount; // Forskellen i antallet pakker siden sidste sekund
      lbSamplesPerSec.Text = diff.ToString() + " Samples/sec"; // Skriv det på status linjen
            
      if (diff>pbSamplesPerSec.Maximum) // Hvis forskellen er større en maksimum af statusbjælken 
        {
          pbSamplesPerSec.Maximum = diff; // Forstør makimum
        }

      pbSamplesPerSec.Value = diff; // Set statusbjælken til antallet af pakker per sekund       
      oldPackageCount = packageCount; 
    }
  }
}
