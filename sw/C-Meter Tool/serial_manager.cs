using System;
using System.IO.Ports;
using System.Globalization;
using System.Windows.Forms;

namespace C_Meter_Tool
{
    partial class main
    {
        SerialPort sPort = new SerialPort();

        public delegate void set_text_delegate(string myString);
        public set_text_delegate set_text;

        private object[] port_list;

        //
        // update port list
        //
        private void update_port_list()
        {
            // check ports
            port_list = SerialPort.GetPortNames();

            // clear old port items
            toolStripComboBox_port.Items.Clear();

            // set new port items
            toolStripComboBox_port.Items.AddRange(port_list);
        }

        //
        // open port
        //
        private void open_port()
        {
            // port settings
            sPort.PortName = Convert.ToString(toolStripComboBox_port.Text);
            sPort.BaudRate = Convert.ToInt32("9600");
            sPort.DataBits = Convert.ToInt16("8");
            sPort.StopBits = (StopBits)Enum.Parse(typeof(StopBits), "One");
            sPort.Handshake = (Handshake)Enum.Parse(typeof(Handshake), "None");
            sPort.Parity = (Parity)Enum.Parse(typeof(Parity), "None");

            // receive event handler
            sPort.DataReceived += new SerialDataReceivedEventHandler(data_received);
            this.set_text = new set_text_delegate(write_textBox);

            // open port
            try
            {
                // open port
                sPort.Open();

                // change dis-/connect text
                toolStripButton_connect.ToolTipText = "Disconnect";
                toolStripButton_connect.Checked = true;
            }

            catch
            {
                // error message
                MessageBox.Show("Error by opening port!\n\nCheck\tif the port isn't used in another application,\n\tif it isn't the same port selected as port 1,\n\tif you choosed the correct port.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        //
        // close port
        //
        private void close_port()
        {
            // close port
            if (sPort.IsOpen) sPort.Close();

            // change dis-/connect text
            toolStripButton_connect.ToolTipText = "Connect";
            toolStripButton_connect.Checked = false;
        }

        //
        // receive data event
        //
        private void data_received(object sender, SerialDataReceivedEventArgs e)
        {
            // get received data
            SerialPort sp = (SerialPort)sender;
            string s = sp.ReadExisting();

            // put on log textBox
            Invoke(this.set_text, new Object[] { s });
        }

        //
        // write received data to textbox
        //

        // time stamp enable
        private bool time_stamp_en = true;

        public void write_textBox(string rcved_data)
        {
            // data array
            char[] data_arr = rcved_data.ToCharArray();
            uint data_index;
            int data_len = rcved_data.Length;

            // temporary srting
            char[] tmp = new char[100000];
            uint tmp_index;

            // timestamp
            string timstamp = string.Empty;

            // control character flag
            bool _ctrl_char;

            // prepair the string
            data_index = 0;
            tmp_index = 0;

            while (data_index < data_len)
            {
                // timestamp
                if (toolStripButton_timestamp.Checked && time_stamp_en)
                {
                    timstamp = DateTime.UtcNow.ToString("HH:mm:ss.fff >", CultureInfo.InvariantCulture);

                    // integrate timestamp in tmp
                    for (int i = 0; i < timstamp.Length; i++)
                    {
                        tmp[tmp_index] = (timstamp.ToCharArray())[i];
                        tmp_index++;
                    }

                    // disable timestamp
                    time_stamp_en = false;
                }

                // check if it is a control character (0-31)
                _ctrl_char = true;
                for (int i = 0; i <= 31; i++)
                {
                    if (data_arr[data_index] == i)
                    {
                        _ctrl_char = false;
                    }
                }

                // put the character from data in tmp only if it isn't a cantrol character
                if (_ctrl_char)
                {
                    tmp[tmp_index] = data_arr[data_index];
                    tmp_index++;
                }

                // new line at \n
                if (data_arr[data_index] == '\n')
                {
                    // enable timestamp
                    time_stamp_en = true;

                    // make newline in textbox
                    tmp[tmp_index] = '\r';
                    tmp_index++;
                    tmp[tmp_index] = '\n';
                    tmp_index++;
                }

                // go to next data character
                data_index++;
            }

            // put to textbox
            textBox_c_log.Text += new string(tmp);

            // scroll to bottom
            textBox_c_log.SelectionStart = textBox_c_log.Text.Length;
            textBox_c_log.ScrollToCaret();
        }
    }
}
