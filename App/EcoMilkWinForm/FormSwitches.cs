using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EcoMilkWinForm
{
    public partial class FormSwitches : Form
    {
        private Am am;
        //private Field progress_bar;
        private Button button_Connect;

        public FormSwitches()
        {
            InitializeComponent();

            new Field(ltype: typeof(Label), ltext: "Ecomilk", font: 36F, width: Field.DefaultWidth, height: Field.DefaultHeightLarge, lplacev: Place.Zero).draw(this, true);
            button_Connect = new Field(ltype: typeof(Button), ltext: "Connect", width: Field.DefaultWidth, height: Field.DefaultHeightLarge, eventHandler: button_Connect_Click, lplaceh: Place.Two, lplacev: Place.One).draw(this, true) as Button;

            new Field(ltype: typeof(Label), ltext: "Actuator Backward com", autosize: false, width: Field.DefaultWidth, height: Field.DefaultHeightLarge, lplaceh: Place.Zero, lplacev: Place.Two).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "On", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Actuator_Backward_com_on_Click, lplaceh: Place.Three, lplacev: Place.Two).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Off", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Actuator_Backward_com_off_Click, lplaceh: Place.Four, lplacev: Place.Two).draw(this, true);
            
            new Field(ltype: typeof(Label), ltext: "Actuator Forward com", autosize: false, width: Field.DefaultWidth, height: Field.DefaultHeightLarge, lplaceh: Place.Zero, lplacev: Place.Four).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "On", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Actuator_Forward_com_on_Click, lplaceh: Place.Three, lplacev: Place.Four).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Off", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Actuator_Forward_com_off_Click, lplaceh: Place.Four, lplacev: Place.Four).draw(this, true);

            new Field(ltype: typeof(Label), ltext: "Rotate CW com", autosize: false, width: Field.DefaultWidth, height: Field.DefaultHeightLarge, lplaceh: Place.Zero, lplacev: Place.Six).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "On", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Rotate_CW_com_on_Click, lplaceh: Place.Three, lplacev: Place.Six).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Off", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Rotate_CW_com_off_Click, lplaceh: Place.Four, lplacev: Place.Six).draw(this, true);

            new Field(ltype: typeof(Label), ltext: "Rotate CCW com", autosize: false, width: Field.DefaultWidth, height: Field.DefaultHeightLarge, lplaceh: Place.Zero, lplacev: Place.Eight).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "On", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Rotate_CCW_com_on_Click, lplaceh: Place.Three, lplacev: Place.Eight).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Off", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Rotate_CCW_com_off_Click, lplaceh: Place.Four, lplacev: Place.Eight).draw(this, true);

            new Field(ltype: typeof(Label), ltext: "Tilt CCW com", autosize: false, width: Field.DefaultWidth, height: Field.DefaultHeightLarge, lplaceh: Place.Zero, lplacev: Place.Ten).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "On", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Tilt_CCW_com_on_Click, lplaceh: Place.Three, lplacev: Place.Ten).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Off", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Tilt_CCW_com_off_Click, lplaceh: Place.Four, lplacev: Place.Ten).draw(this, true);

            new Field(ltype: typeof(Label), ltext: "Tilt CW com", autosize: false, width: Field.DefaultWidth, height: Field.DefaultHeightLarge, lplaceh: Place.Zero, lplacev: Place.Twelve).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "On", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Tilt_CW_com_on_Click, lplaceh: Place.Three, lplacev: Place.Twelve).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Off", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Tilt_CW_com_off_Click, lplaceh: Place.Four, lplacev: Place.Twelve).draw(this, true);

            new Field(ltype: typeof(Label), ltext: "Motor Z Down com", autosize: false, width: Field.DefaultWidth, height: Field.DefaultHeightLarge, lplaceh: Place.Three, lplacev: Place.Two).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "On", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Motor_Z_Down_com_on_Click, lplaceh: Place.Eleven, lplacev: Place.Two).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Off", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Motor_Z_Down_com_off_Click, lplaceh: Place.Twelve, lplacev: Place.Two).draw(this, true);

            new Field(ltype: typeof(Label), ltext: "Motor Z Up com", autosize: false, width: Field.DefaultWidth, height: Field.DefaultHeightLarge, lplaceh: Place.Three, lplacev: Place.Four).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "On", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Motor_Z_up_com_on_Click, lplaceh: Place.Eleven, lplacev: Place.Four).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Off", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Motor_Z_up_com_off_Click, lplaceh: Place.Twelve, lplacev: Place.Four).draw(this, true);

            new Field(ltype: typeof(Label), ltext: "Actuator Y Backward com", autosize: false, width: Field.DefaultWidth, height: Field.DefaultHeightLarge, lplaceh: Place.Three, lplacev: Place.Six).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "On", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Actuator_Y_Backward_com_on_Click, lplaceh: Place.Eleven, lplacev: Place.Six).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Off", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Actuator_Y_Backward_com_off_Click, lplaceh: Place.Twelve, lplacev: Place.Six).draw(this, true);

            new Field(ltype: typeof(Label), ltext: "Actuator Y forward com", autosize: false, width: Field.DefaultWidth, height: Field.DefaultHeightLarge, lplaceh: Place.Three, lplacev: Place.Eight).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "On", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Actuator_Y_Forward_com_on_Click, lplaceh: Place.Eleven, lplacev: Place.Eight).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Off", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_Actuator_Y_Forward_com_off_Click, lplaceh: Place.Twelve, lplacev: Place.Eight).draw(this, true);

            new Field(ltype: typeof(Label), ltext: "X Backward com", autosize: false, width: Field.DefaultWidth, height: Field.DefaultHeightLarge, lplaceh: Place.Three, lplacev: Place.Ten).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "On", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_X_Backward_com_on_Click, lplaceh: Place.Eleven, lplacev: Place.Ten).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Off", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_X_Backward_com_off_Click, lplaceh: Place.Twelve, lplacev: Place.Ten).draw(this, true);

            new Field(ltype: typeof(Label), ltext: "X Forward com", autosize: false, width: Field.DefaultWidth, height: Field.DefaultHeightLarge, lplaceh: Place.Three, lplacev: Place.Twelve).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "On", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_X_Forward_com_on_Click, lplaceh: Place.Eleven, lplacev: Place.Twelve).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Off", width: Field.DefaultWidthSmall, height: Field.DefaultHeightLarge, eventHandler: button_X_Forward_com_off_Click, lplaceh: Place.Twelve, lplacev: Place.Twelve).draw(this, true);

            //progress_bar = new Field(ltype: typeof(ProgressBar), width: Field.DefaultWidthLarge, height: Field.DefaultHeightLarge, eventHandler: progressBar_Progress, lplaceh: Place.One, lplacev: Place.Zero);
            //progress_bar.draw(this, true);
        }

        //private async void button_Connect_to_Ecomilk_Click(object sender, EventArgs e)
        //{
        //    this.Enabled = false;
        //    am = new Am();
        //    ErrCode errcode = await am.AMDataCheckConnect();
        //    if (errcode == ErrCode.OK)
        //        MessageBox.Show(string.Format("Ecomilk detected on {0}", am.serialPort.PortName));
        //    else
        //        MessageBox.Show("Ecomilk not found");
        //    this.Enabled = true;
        //}

        private async Task command(string command)
        {
            ErrCode errcode = ErrCode.ERROR;
            this.Enabled = false;
            if (am != null)
                errcode = await am.EcomilkCommand(command);
            else
                errcode = ErrCode.ECONNECT;
            if (errcode == ErrCode.OK)
                MessageBox.Show("Success");
            else if(errcode == ErrCode.ECONNECT)
                MessageBox.Show("Ecomilk is not connected");
            else
                MessageBox.Show("Failed");
            this.Enabled = true;
        }

        //private void progressBar_Progress(object sender, EventArgs e)
        //{
        //    (progress_bar.lcontrol as ProgressBar).Maximum = (e as SerialPortEventArgs).maximum;
        //    (progress_bar.lcontrol as ProgressBar).Value = (e as SerialPortEventArgs).progress;
        //}

        private async Task connect()
        {
            this.Enabled = false;
            //Field progress = new Field(ltype: typeof(Label), ltext: "Connecting to Ecomilk, please wait ..", autosize: false, font: 24F, width: Field.DefaultWidthLarge, height: Field.DefaultHeightLarge, lplacev: Place.One);
            //progress.draw(this, true);
            button_Connect.Text = "Connecting ..";
            am = new Am();
            //am.serialPortProgressEvent += progressBar_Progress;
            ErrCode errcode = await am.AMDataCheckConnect();
            //(progress_bar.lcontrol as ProgressBar).Maximum = 100;
            //(progress_bar.lcontrol as ProgressBar).Value = 100;
            if (errcode == ErrCode.OK)
            {
                MessageBox.Show(string.Format("Ecomilk detected on {0}", am.serialPort.PortName));
                button_Connect.Text = "Disconnect";
                button_Connect.Click -= button_Connect_Click;
                button_Connect.Click += button_Disconnect_Click;
            }
            else
            {
                MessageBox.Show("Ecomilk not found");
                button_Connect.Text = "Connect";
            }
            //progress.lcontrol.Dispose();
            this.Enabled = true;
        }

        private async Task disconnect()
        {
            this.Enabled = false;
            button_Connect.Text = "Disconnecting ..";
            am.serialPort.PortName = "COM1";
            button_Connect.Text = "Connect";
            button_Connect.Click -= button_Disconnect_Click;
            button_Connect.Click += button_Connect_Click;
            this.Enabled = true;
        }

        private async void Form1_Load(object sender, EventArgs e)
        {
            await connect();
        }

        private async void button_Connect_Click(object sender, EventArgs e)
        {
            await connect();
        }

        private async void button_Disconnect_Click(object sender, EventArgs e)
        {
            await disconnect();
        }

        private async void button_X_Forward_com_off_Click(object sender, EventArgs e)
        {
            await command("xf 0\r");
        }

        private async void button_X_Forward_com_on_Click(object sender, EventArgs e)
        {
            await command("xf 1\r");
        }

        private async void button_X_Backward_com_off_Click(object sender, EventArgs e)
        {
            await command("xb 0\r");
        }

        private async void button_X_Backward_com_on_Click(object sender, EventArgs e)
        {
            await command("xb 1\r");
        }

        private async void button_Actuator_Y_Forward_com_on_Click(object sender, EventArgs e)
        {
            await command("ayf 1\r");
        }

        private async void button_Actuator_Y_Forward_com_off_Click(object sender, EventArgs e)
        {
            await command("ayf 0\r");
        }

        private async void button_Actuator_Y_Backward_com_on_Click(object sender, EventArgs e)
        {
            await command("ayb 1\r");
        }

        private async void button_Actuator_Y_Backward_com_off_Click(object sender, EventArgs e)
        {
            await command("ayb 0\r");
        }

        private async void button_Motor_Z_up_com_off_Click(object sender, EventArgs e)
        {
            await command("mzu 0\r");
        }

        private async void button_Motor_Z_up_com_on_Click(object sender, EventArgs e)
        {
            await command("mzu 1\r");
        }

        private async void button_Motor_Z_Down_com_off_Click(object sender, EventArgs e)
        {
            await command("mzd 0\r");
        }

        private async void button_Motor_Z_Down_com_on_Click(object sender, EventArgs e)
        {
            await command("mzd 1\r");
        }

        private async void button_Tilt_CW_com_off_Click(object sender, EventArgs e)
        {
            await command("tcw 0\r");
        }

        private async void button_Tilt_CW_com_on_Click(object sender, EventArgs e)
        {
            await command("tcw 1\r");
        }

        private async void button_Tilt_CCW_com_off_Click(object sender, EventArgs e)
        {
            await command("tccw 0\r");
        }

        private async void button_Tilt_CCW_com_on_Click(object sender, EventArgs e)
        {
            await command("tccw 1\r");
        }

        private async void button_Rotate_CCW_com_off_Click(object sender, EventArgs e)
        {
            await command("rccw 0\r");
        }

        private async void button_Rotate_CCW_com_on_Click(object sender, EventArgs e)
        {
            await command("rccw 1\r");
        }

        private async void button_Rotate_CW_com_off_Click(object sender, EventArgs e)
        {
            await command("rcw 0\r");
        }

        private async void button_Rotate_CW_com_on_Click(object sender, EventArgs e)
        {
            await command("rcw 1\r");
        }

        private async void button_Actuator_Forward_com_off_Click(object sender, EventArgs e)
        {
            await command("af 0\r");
        }

        private async void button_Actuator_Forward_com_on_Click(object sender, EventArgs e)
        {
            await command("af 1\r");
        }

        private async void button_Actuator_Backward_com_off_Click(object sender, EventArgs e)
        {
            await command("ab 0\r");
        }

        private async void button_Actuator_Backward_com_on_Click(object sender, EventArgs e)
        {
            await command("ab 1\r");
        }
    }
}
