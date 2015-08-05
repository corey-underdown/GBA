using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace WindowsFormsApplication1
{
	public partial class Form1 : Form
	{
		string fileName, fileTitle, fileDir;
		bool opened = false;

		public Form1()
		{
			InitializeComponent();
		}

		private void openToolStripMenuItem_Click(object sender, EventArgs e)
		{
			OpenFileDialog openFileDialog1 = new OpenFileDialog();

			openFileDialog1.InitialDirectory = "c:\\";
			openFileDialog1.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
			openFileDialog1.FilterIndex = 2;
			openFileDialog1.RestoreDirectory = true;

			if (openFileDialog1.ShowDialog() == DialogResult.OK)
			{
				Console.WriteLine("File Opened");
				fileName = openFileDialog1.FileName;
				fileTitle = Path.GetFileNameWithoutExtension(fileName);
				fileDir = Path.GetDirectoryName(fileName);
				opened = true;
				button1.Enabled = true;
				Console.WriteLine(fileName);
			}
			else
			{
				opened = false;
				button1.Enabled = false;
			}
		}

		private void button1_Click(object sender, EventArgs e)
		{
			Image img = Image.FromFile(fileName);

			byte[] b = imageToByteArray(img);
			for(int i = 0; i < b.Length; i++)
			{
				Console.WriteLine(b[i]);
			}
		}

		public byte[] imageToByteArray(Image imageIn)
		{
			using (var ms = new MemoryStream())
			{
				imageIn.Save(ms, System.Drawing.Imaging.ImageFormat.Png);
				return ms.ToArray();
			}
		}
	}
}
