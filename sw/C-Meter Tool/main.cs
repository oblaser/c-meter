using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace C_Meter_Tool
{
    public partial class main : Form
    {
        public main()
        {
            InitializeComponent();
        }

        private void update_portlist_event(object sender, EventArgs e)
        {
            update_port_list();
        }

        private void dis_connect_event(object sender, EventArgs e)
        {
            if(sPort.IsOpen)
            {
                close_port();
            }

            else
            {
                open_port();
            }
        }

        private void clear_log(object sender, EventArgs e)
        {
            if (MessageBox.Show("Do you really want to clear the log?", "Are you shure?", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
            {
                textBox_c_log.Text = String.Empty;
            }
        }

        private void main_Load(object sender, EventArgs e)
        {
            // set dis-/connect text
            toolStripButton_connect.ToolTipText = "Connect";
            toolStripButton_connect.Checked = false;
        }
    }
}
