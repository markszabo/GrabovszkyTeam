using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace RoutePlanning
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            trackBar1.Value = pixelsize;
            comboBox1.SelectedIndex = 0;
        }

        int pixelsize = 10;
        Graph g = null;
        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                g = GraphUtil.BuildGraph(ofd.FileName);
                Image i = Image.FromFile(ofd.FileName);
                //pictureBox2.Image = i;
                pictureBox1.Image = i;
                Bitmap bmp2 = null;
                string filename = ofd.FileName.Substring(ofd.FileName.LastIndexOf("\\"));
                switch (comboBox1.SelectedIndex)
                { 
                    case 0:
                        System.Diagnostics.Debug.WriteLine("=============\nPQ\n"+filename);
                        bmp2 = GraphUtil.DrawPath((Bitmap)i, GraphUtil.GetPathPQ(g), trackBar1.Value, g, checkBox1.Checked);
                        break;
                    case 1:
                        System.Diagnostics.Debug.WriteLine("=============\nDA\n" + filename);
                        bmp2 = GraphUtil.DrawPath((Bitmap)i, GraphUtil.GetPath_DA(g), trackBar1.Value, g, checkBox1.Checked);
                        break;
                    case 2:                        
                        System.Diagnostics.Debug.WriteLine("=============\nPQ_DA\n" + filename);
                        bmp2 = GraphUtil.DrawPath((Bitmap)i, GraphUtil.GetPathPQ_DA(g), trackBar1.Value, g, checkBox1.Checked);
                        break;
                    case 3:
                    default:
                        System.Diagnostics.Debug.WriteLine("=============\nList\n" + filename);
                        bmp2 = GraphUtil.DrawPath((Bitmap)i, GraphUtil.GetPath(g), trackBar1.Value, g, checkBox1.Checked);
                        break;
                }
                if (bmp2 != null)
                {
                    pictureBox2.Size = new Size(bmp2.Width, bmp2.Height);
                    pictureBox2.Image = bmp2;
                }
            }
        }

        private void pictureBox2_MouseDown(object sender, MouseEventArgs e)
        {
            Node clicked = null;
            foreach (var n in g.nodes)
            {
                int x, y;
                GraphUtil.GetCoords(n, out x, out y);
                if (x == e.X / pixelsize && y == e.Y / pixelsize)
                {
                    clicked = n;
                    break;
                }
            }
            if(clicked != null)
                pictureBox2.Image = GraphUtil.DrawPath((Bitmap)pictureBox1.Image, GraphUtil.GetPathFromNode(g, clicked), trackBar1.Value, g, checkBox1.Checked);
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            //Point pp = pictureBox2.PointToClient(panel1.PointToScreen(e.Location));
            //pictureBox2_MouseDown(sender, new MouseEventArgs(e.Button, e.Clicks, pp.X, pp.Y, e.Delta));
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            label1.Text = trackBar1.Value.ToString();
            pixelsize = trackBar1.Value;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            pictureBox2.Image = GraphUtil.DrawPath((Bitmap)pictureBox1.Image, GraphUtil.GetPathFromNode(g, g.dest), trackBar1.Value, g, checkBox1.Checked);
        }
    }
}
