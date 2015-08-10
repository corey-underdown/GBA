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
		public class ColorStruct
		{
			public Color[] colors = new Color[16];
		}

		string fileName, fileTitle, fileDir;
		List<ColorStruct> palettes = new List<ColorStruct>();

		public Form1()
		{
			InitializeComponent();
			for (int i = 0; i < 16; i++)
				palettes.Add(new ColorStruct());
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
				button1.Enabled = true;
				Console.WriteLine(fileName);
			}
			else
			{
				button1.Enabled = false;
			}
		}

		private void button1_Click(object sender, EventArgs e)
		{
			Bitmap img = new Bitmap(fileName);

			int[] hexArray = new int[64];

			for(int j = 0; j < img.Height; j++)
			{
				for(int i = 0; i < img.Width; i++)
				{
					Color pixel = img.GetPixel(i, j);
					for(int k = 0; k < palettes[0].colors.Length; k++)
					{
						if(pixel == palettes[0].colors[k])
						{
							hexArray[i + j * 8] = k;
						}
					}
				}
			}

			for(int i = 0; i < 8; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					int value = (hexArray[i * 8 + (j * 2) + 1] << 1) & (hexArray[i * 8 + (j * 2)]);
					Console.WriteLine(value.ToString("X"));
				}
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

		private void button2_Click(object sender, EventArgs e)
		{
			OpenFileDialog openFileDialog2 = new OpenFileDialog();

			openFileDialog2.InitialDirectory = "c:\\";
			openFileDialog2.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
			openFileDialog2.FilterIndex = 2;
			openFileDialog2.RestoreDirectory = true;

			if (openFileDialog2.ShowDialog() == DialogResult.OK)
			{
				Bitmap img = new Bitmap(openFileDialog2.FileName);
				for (int j = 0; j < img.Height; j++)
				{
					for (int i = 0; i < img.Width; i++)
					{
						palettes[j].colors[i] = img.GetPixel(i, j);
					}
				}

				for (int i = 0; i < 16; i++)
					Console.Write(palettes[0].colors[i]);
			}
			else
			{
				Console.WriteLine("Error opening palette");
			}
		}

	}
}
