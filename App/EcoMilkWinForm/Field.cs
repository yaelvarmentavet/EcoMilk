﻿using System;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace EcoMilkWinForm
{
    public enum Place
    {
        None = -1,
        Center = 2000, Start = 1000, End = 3000,
        One = 1, Two = 2, Three = 3, Four = 4, Five = 5, Six = 6, Seven = 7, Eight = 8, Nine = 9, Ten = 10, Eleven = 11, Twelve = 12,
        Zero = 0
    }

    class Field
    {
        public const int DefaultWidthSmall = 180;
        public const int DefaultWidth = 490;//460;//390;
        public const int DefaultWidthLarge = 1200;
        public const int DefaultWidthMedium = 900;
        public const int DefaultHeight = 60;
        public const int DefaultHeightSmall = 12;
        public const int DefaultHeightLarge = 90;
        public const float ScaleFactor = 1F;
        public const float PlaceOne = 200 * ScaleFactor;
        public const float DeltaV = 100 * ScaleFactor;
        public const float DefaultFont = 24F * ScaleFactor;
        public const float DefaultFontLarge = 30F * ScaleFactor;
        private const float BLANK = 10F * ScaleFactor;

        public ErrCode error;
        public string val;
        public string ltext;
        public string dflt;
        public object[] items;
        public Control control;
        public Control lcontrol;
        public Type type;
        public Type ltype;
        private float font;
        private Color color;
        private int width;
        private int height;
        private bool autosize;
        private Place placeh;
        private Place lplaceh;
        private Place placev;
        private Place lplacev;
        public EventHandler eventHandler;
        public LinkLabelLinkClickedEventHandler linkEventHandler;
        public bool view;
        public bool enable;
        public bool check;
        private delegate bool dFCheck();
        private delegate bool dPCheck(string param);
        private dFCheck dfcheck;
        private dPCheck dpcheck;

        public Field(Type type = null, Type ltype = null, string dflt = null, object val = null, string ltext = null, object[] items = null,
            LinkLabelLinkClickedEventHandler linkEventHandler = null,
            EventHandler eventHandler = null,
            bool enable = true, bool check = true,
            float font = DefaultFont, Color color = new Color(),
            int width = DefaultWidth, int height = DefaultHeight, bool autosize = true,
            Place placeh = Place.Center, Place lplaceh = Place.Center, Place placev = Place.None, Place lplacev = Place.None)
        {
            this.dflt = dflt;
            this.val = this.dflt;
            this.ltext = ltext;
            this.items = items;
            this.type = type;
            this.ltype = ltype;
            this.font = font;
            this.color = color;
            this.width = width;
            this.height = height;
            this.autosize = autosize;
            this.placeh = placeh;
            this.lplaceh = lplaceh;
            this.placev = placev;
            if (lplacev == Place.None)
                this.lplacev = placev;
            else
                this.lplacev = lplacev;

            this.linkEventHandler = linkEventHandler;
            this.eventHandler = eventHandler;
            this.view = true;
            this.enable = enable;
            this.check = check;
            this.dfcheck = checkValid;
            this.dpcheck = checkValid;
        }

        public void setValue(string value)
        {
            if (checkValid(value))
                val = value;
            else
                val = dflt;
        }

        public string getValue()
        {
            if (checkValid())
                error = ErrCode.OK;
            else
            {
                error = ErrCode.EPARAM;
                return null;
            }
            return val;
        }

        public bool checkValid()
        {
            int ivalue = stringToInt(val);
            if (!check)
                return true;
            if ((val != null) && (val != string.Empty) && (val != dflt) && (ivalue >= 0))
            {
                return true;
            }
            return false;
        }

        public bool checkValid(string param)
        {
            if (!check)
                return true;
            if (param != null)
            {
                if (param != string.Empty)
                    return true;
            }
            return false;
        }
        
        public static string boolToString(bool bVal)
        {
            if (bVal)
                return "Yes";
            else
                return "No";
        }

        public static bool stringToBool(string sVal)
        {
            if (sVal == null)
                return false;
            if (sVal.Equals("Yes"))
                return true;
            else
                return false;
        }

        public static int stringToInt(string sVal)
        {
            int iVal = 0;
            int.TryParse(sVal, out iVal);
            return iVal;
        }

        public static int? stringToIntOrNull(string sVal)
        {
            if (sVal != null)
            {
                int iVal = 0;
                if (int.TryParse(sVal, out iVal))
                    return iVal;
                else
                    return null;
            }
            return null;
        }

        public static string intToString(int? iVal)
        {
            if (iVal != null)
                return iVal.ToString();
            return null;
        }

        public ErrCode checkField()
        {
            if (control != null)
            {
                if (error == ErrCode.EPARAM)
                {
                    control.ForeColor = Color.Red;
                    control.Text = dflt;
                    TextBox textBox = control as TextBox;
                    if (textBox != null)
                        textBox.PasswordChar = '\0';
                    return ErrCode.EPARAM;
                }
            }
            return ErrCode.OK;
        }

        public Control draw(Form thisForm, bool readnly)
        {
            if(readnly)
            {
                lcontrol = draw(thisForm, ltype, val: ltext, placeh: lplaceh, placev: lplacev);
                return lcontrol;
            }
            else
            {
                control = draw(thisForm, type, val: val, placeh: placeh, placev: placev);
                return control;
            }
        }

        public Control draw(Form thisForm, Type type, string val = null,
            Place placeh = Place.Center, Place placev = Place.Center)
        {
            Control control = null;
            if (type != null)
            {
                control = type.GetConstructor(new Type[] { }).Invoke(null) as Control;
                thisForm.Controls.Add(control);
                control.Anchor = (AnchorStyles.Top) | (AnchorStyles.Left);
                control.Margin = new Padding(4);
                control.Size = new Size(width, height);
                control.Scale(new SizeF(ScaleFactor, ScaleFactor));
                control.TabIndex = 1;
                control.Text = val;
                control.Font = new Font("Segoe UI", font, FontStyle.Regular, GraphicsUnit.Point);

                if (type == typeof(Label))
                {
                    if (color != Color.Empty)
                        control.ForeColor = color;
                    control.AutoSize = autosize;
                }
                if (type == typeof(PictureBox))
                {
                    PictureBox pictureBox = (control as PictureBox);
                    if (pictureBox != null)
                    {
                        control.AutoSize = true;
                        pictureBox.Image = Properties.Resources.ARmentaSmall;
                    }
                }
                if (type == typeof(RichTextBox))
                {
                    RichTextBox richTextBox = control as RichTextBox;
                    if (richTextBox != null)
                    {
                        richTextBox.Multiline = false;
                        richTextBox.TextChanged += textBox_TextChanged;
                        defaultText(control);
                    }
                }
                if (type == typeof(TextBox))
                {
                    TextBox textBox = control as TextBox;
                    if (textBox != null)
                    {
                        textBox.Multiline = false;
                        textBox.TextChanged += textBox_TextChanged;
                        defaultText(control);
                    }
                }
                if (type == typeof(Button))
                    if (eventHandler != null)
                        control.Click += eventHandler;
                if (type == typeof(LinkLabel))
                {
                    LinkLabel linkLabel = control as LinkLabel;
                    if (linkLabel != null)
                    {
                        control.AutoSize = true;
                        if (linkEventHandler != null)
                            linkLabel.LinkClicked += linkEventHandler;
                        if (eventHandler != null)
                            linkLabel.Click += eventHandler;
                    }
                }
                if (type == typeof(ComboBox))
                {
                    ComboBox comboBox = (control as ComboBox);
                    if (comboBox != null)
                    {
                        comboBox.DropDownHeight = DefaultWidth;
                        if (items != null)
                            comboBox.Items.AddRange(items);
                        comboBox.SelectedIndexChanged += comboBox_SelectedIndexChanged;
                        comboBox.TextUpdate += comboBox_TextUpdate;
                        defaultText(control);
                    }
                }
                if (type == typeof(RadioButton))
                {
                    RadioButton radioButton = control as RadioButton;
                    if (radioButton != null)
                        if (eventHandler != null)
                            radioButton.CheckedChanged += eventHandler;
                }

                control.Location = placeCalc(thisForm, control, placeh: placeh, placev: placev);
                control.Enabled = enable;
            }
            return control;
        }

        private void textBox_TextChanged(object sender, EventArgs e)
        {
            Control control = sender as Control;
            if (control != null)
            {
                val = control.Text;
                if (eventHandler != null)
                    eventHandler(sender, e);
            }
        }

        private void comboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox comboBox = sender as ComboBox;
            if(comboBox != null)
            {
                val = comboBox.SelectedItem as string;
                if (eventHandler != null)
                    eventHandler(sender, e);
            }
        }

        private void defaultText(Control control)
        {
            if (control.Text == dflt)
                control.ForeColor = Color.Silver;
            else
                control.ForeColor = Color.Black;
            control.Enter += new EventHandler(controlEnter_Click);
            control.Leave += new EventHandler(controlLeave_Click);
        }

        public static Point placeCalc(Form thisForm,
                Control control, Point location = new System.Drawing.Point(), Place placeh = Place.Center, Place placev = Place.Center)
        {
            //if (placeh == Place.Center)
            //    location.X = thisForm.Width / 2 - control.Width / 2;
            //else if (placeh == Place.Start)
            //    location.X = thisForm.Width / 2 - control.Width / 2 - control.Width * 2 - control.Width * 2 / 4;
            //else if (placeh == Place.End)
            //    location.X = thisForm.Width / 2 + control.Width / 2 + control.Width + control.Width * 2 / 4;
            //else if (placeh == Place.One)
            //    location.X = thisForm.Width / 2 + control.Width / 4 / 2;
            //else if (placeh == Place.Two)
            //    location.X = thisForm.Width / 2 + control.Width / 2 + control.Width / 4;
            //else if (placeh == Place.Three)
            //    location.X = thisForm.Width / 2 + control.Width + control.Width / 4 / 2 + control.Width / 4;
            //else if (placeh == Place.Four)
            //    location.X = thisForm.Width / 2 - control.Width * 2 - control.Width / 4 / 2 - control.Width / 4;
            //else if (placeh == Place.Five)
            //    location.X = thisForm.Width / 2 - control.Width / 2 - control.Width - control.Width / 4;
            //else if (placeh == Place.Six)
            //    location.X = thisForm.Width / 2 - control.Width - control.Width / 4 / 2;

            //if (placev == Place.Zero)
            //    location.Y = 0;
            //if (placev == Place.One)
            //    location.Y = 100;
            //else if (placev == Place.Two)
            //    location.Y = (int)(PlaceOne + 0 * DeltaV);//200;
            //else if (placev == Place.Three)
            //    location.Y = (int)(PlaceOne + 1 * DeltaV);//300;
            //else if (placev == Place.Four)
            //    location.Y = (int)(PlaceOne + 2 * DeltaV);//400;
            //else if (placev == Place.Five)
            //    location.Y = (int)(PlaceOne + 3 * DeltaV);//500;
            //else if (placev == Place.Six)
            //    location.Y = (int)(PlaceOne + 4 * DeltaV);//600;
            //else if (placev == Place.Seven)
            //    location.Y = (int)(PlaceOne + 5 * DeltaV);//700;
            //else if (placev == Place.Eight)
            //    location.Y = (int)(PlaceOne + 6 * DeltaV);//800;
            //else if (placev == Place.Nine)
            //    location.Y = (int)(PlaceOne + 7 * DeltaV);//900;
            //else if (placev == Place.Ten)
            //    location.Y = (int)(PlaceOne + 8 * DeltaV);//1000;
            //else if (placev == Place.Eleven)
            //    location.Y = (int)(PlaceOne + 9 * DeltaV);//1100;
            //else if (placev == Place.End)
            //    location.Y = (int)(PlaceOne + 10 * DeltaV);//1200;
            float x = BLANK;
            float y = BLANK;
            for (int i = (int)Place.Zero; i < (int)Place.Twelve; i++)
            {
                if (i < (int)placeh)
                    x += control.Width + BLANK;
                if (i < (int)placev)
                    y += control.Height + BLANK;
            }
            location.X = (int)x;
            location.Y = (int)y;

            if (placeh == Place.Center)
                location.X = thisForm.Width / 2 - control.Width / 2;

            return location;
        }

        private void controlEnter_Click(object sender, EventArgs e)
        {
            Control control = sender as Control;
            TextBox textBox = sender as TextBox;
            if (control != null)
            {
                if (control.Text == dflt)
                {
                    control.Text = string.Empty;
                    control.ForeColor = Color.Black;
                    if (textBox != null)
                        textBox.PasswordChar = '*';
                }
            }
        }

        private void controlLeave_Click(object sender, EventArgs e)
        {
            Control control = sender as Control;
            TextBox textBox = sender as TextBox;
            if (control != null)
            {
                if (control.Text == string.Empty)
                {
                    control.Text = dflt;
                    control.ForeColor = Color.Silver;
                    if (textBox != null)
                        textBox.PasswordChar = '\0';
                }
            }
        }

        private void comboBox_TextUpdate(object sender, EventArgs e)
        {
            ComboBox comboBox = sender as ComboBox;
            if ((comboBox != null) && (items != null))
            {
                try
                {
                    string combotext = comboBox.Text;
                    removeItems();
                    addItems(items.Where(s => s.ToString().ToLower().StartsWith(combotext.ToLower())).ToArray());
                    comboBox.DroppedDown = true;
                    comboBox.Text = combotext;
                    comboBox.SelectionStart = comboBox.Text.Count();
                }
                catch(Exception ex)
                {
                    LogFile.logWrite(ex.ToString());
                }
            }
        }

        public void addItems(object[] items)
        {
            ComboBox comboBox = control as ComboBox;
            if (comboBox != null)
            {
                comboBox.Items.AddRange(items);
                comboBox.Text = string.Empty;
                //comboBox.ForeColor = Color.Silver;
                //text = dflt;
                //val = dflt;
            }
        }

        public void removeItems()
        {
            ComboBox comboBox = control as ComboBox;
            if (comboBox != null)
            {
                while (comboBox.Items.Count > 0)
                    comboBox.Items.RemoveAt(0);
                comboBox.Text = string.Empty;
                //comboBox.ForeColor = Color.Silver;
                //text = dflt;
                //val = dflt;
            }
        }

        public static void dataGridDraw(Form thisForm, ref DataGridView dataGridView, Place placeh = Place.Center, Place placev = Place.Center)
        {
            dataGridView = new DataGridView();
            ((System.ComponentModel.ISupportInitialize)(dataGridView)).BeginInit();
            dataGridView.Anchor = (AnchorStyles.Top);// | (AnchorStyles.Left);
            dataGridView.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dataGridView.RowHeadersWidth = 62;
            dataGridView.RowTemplate.Height = 33;
            dataGridView.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllCells;
            dataGridView.ReadOnly = true;
            dataGridView.Size = new Size(2200, 800); //1853, 800);
            dataGridView.Scale(new SizeF(ScaleFactor, ScaleFactor));
            dataGridView.Font = new Font("Segoe UI", DefaultFont, FontStyle.Regular, GraphicsUnit.Point);
            dataGridView.Location = placeCalc(thisForm, dataGridView, placeh: placeh, placev: placev);
            dataGridView.TabIndex = 6;
            thisForm.Controls.Add(dataGridView);
            ((System.ComponentModel.ISupportInitialize)(dataGridView)).EndInit();
        }
    }
}
