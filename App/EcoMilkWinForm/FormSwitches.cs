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

        public FormSwitches()
        {
            InitializeComponent();

            new Field(ltype: typeof(Button), ltext: "Actuator Backward com On", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Actuator_Backward_com_on_Click, lplaceh: Place.Six, lplacev: Place.One).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Actuator Backward com Off", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Actuator_Backward_com_off_Click, lplaceh: Place.One, lplacev: Place.One).draw(this, true);
            
            new Field(ltype: typeof(Button), ltext: "Actuator Forward com On", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Actuator_Forward_com_on_Click, lplaceh: Place.Six, lplacev: Place.Two).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Actuator Forward com Off", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Actuator_Forward_com_off_Click, lplaceh: Place.One, lplacev: Place.Two).draw(this, true);

            new Field(ltype: typeof(Button), ltext: "Rotate CW com On", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Rotate_CCW_com_on_Click, lplaceh: Place.Six, lplacev: Place.Three).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Rotate CW com Off", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Rotate_CCW_com_off_Click, lplaceh: Place.One, lplacev: Place.Three).draw(this, true);

            new Field(ltype: typeof(Button), ltext: "Rotate CCW com On", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Rotate_CCW_com_on_Click, lplaceh: Place.Six, lplacev: Place.Four).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Rotate CCW com Off", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Rotate_CCW_com_off_Click, lplaceh: Place.One, lplacev: Place.Four).draw(this, true);
            
            new Field(ltype: typeof(Button), ltext: "Tilt CCW com On", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Tilt_CCW_com_on_Click, lplaceh: Place.Six, lplacev: Place.Five).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Tilt CCW com Off", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Tilt_CCW_com_off_Click, lplaceh: Place.One, lplacev: Place.Five).draw(this, true);
            
            new Field(ltype: typeof(Button), ltext: "Tilt CW com On", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Tilt_CW_com_on_Click, lplaceh: Place.Six, lplacev: Place.Six).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Tilt CW com Off", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Tilt_CW_com_off_Click, lplaceh: Place.One, lplacev: Place.Six).draw(this, true);
            
            new Field(ltype: typeof(Button), ltext: "Motor Z Down com On", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Motor_Z_Down_com_on_Click, lplaceh: Place.Six, lplacev: Place.Seven).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Motor Z Down com Off", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Motor_Z_Down_com_off_Click, lplaceh: Place.One, lplacev: Place.Seven).draw(this, true);
            
            new Field(ltype: typeof(Button), ltext: "Motor Z Up com On", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Motor_Z_up_com_on_Click, lplaceh: Place.Six, lplacev: Place.Eight).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Motor Z Up com Off", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Motor_Z_up_com_off_Click, lplaceh: Place.One, lplacev: Place.Eight).draw(this, true);
            
            new Field(ltype: typeof(Button), ltext: "Actuator Y Backward com On", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Actuator_Y_Backward_com_on_Click, lplaceh: Place.Six, lplacev: Place.Nine).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Actuator Y Backward com Off", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Actuator_Y_forward_com_off_Click, lplaceh: Place.One, lplacev: Place.Nine).draw(this, true);
            
            new Field(ltype: typeof(Button), ltext: "Actuator Y forward comOn", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Actuator_Y_forward_com_on_Click, lplaceh: Place.Six, lplacev: Place.Ten).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "Actuator Y forward comOff", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_Actuator_Y_forward_com_off_Click, lplaceh: Place.One, lplacev: Place.Ten).draw(this, true);
            
            new Field(ltype: typeof(Button), ltext: "X Backward com On", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_X_Backward_com_on_Click, lplaceh: Place.Six, lplacev: Place.Eleven).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "X Backward com Off", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_X_Backward_com_off_Click, lplaceh: Place.One, lplacev: Place.Eleven).draw(this, true);

            new Field(ltype: typeof(Button), ltext: "X Forward com On", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_X_Forward_com_on_Click, lplaceh: Place.Six, lplacev: Place.End).draw(this, true);
            new Field(ltype: typeof(Button), ltext: "X Forward com Off", width: Field.DefaultWidthMedium, height: Field.DefaultHeightLarge, eventHandler: button_X_Forward_com_off_Click, lplaceh: Place.One, lplacev: Place.End).draw(this, true);

            am = new Am();
            am.AMDataCheckConnect();

        }

        private void button_X_Forward_com_off_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("xf 0");
        }

        private void button_X_Forward_com_on_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("xf 1");
        }

        private void button_X_Backward_com_off_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("xb 0");
        }

        private void button_X_Backward_com_on_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("xb 1");
        }

        private void button_Actuator_Y_forward_com_on_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("ayf 1");
        }

        private void button_Actuator_Y_forward_com_off_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("ayf 0");
        }

        private void button_Actuator_Y_Backward_com_on_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("ayb 1");
        }

        private void button_Motor_Z_up_com_off_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("mzu 0");
        }

        private void button_Motor_Z_up_com_on_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("mzu 1");
        }

        private void button_Motor_Z_Down_com_off_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("mzd 0");
        }

        private void button_Motor_Z_Down_com_on_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("mzd 1");
        }

        private void button_Tilt_CW_com_off_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("tcw 0");
        }

        private void button_Tilt_CW_com_on_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("tcw 1");
        }

        private void button_Tilt_CCW_com_off_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("tccw 0");
        }

        private void button_Tilt_CCW_com_on_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("tccw 1");
        }

        private void button_Rotate_CCW_com_off_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("rccw 0");
        }

        private void button_Rotate_CCW_com_on_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("rccw 1");
        }

        private void button_Rotate_CW_com_off_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("rcw 0");
        }

        private void button_Rotate_CW_com_on_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("rcw 1");
        }

        private void button_Actuator_Forward_com_off_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("af 0");
        }

        private void button_Actuator_Forward_com_on_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("af 1");
        }

        private void button_Actuator_Backward_com_off_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("ab 0");
        }

        private void button_Actuator_Backward_com_on_Click(object sender, EventArgs e)
        {
            am.EcomilkCommand("ab 1");
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
