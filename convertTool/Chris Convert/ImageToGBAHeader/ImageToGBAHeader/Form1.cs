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


namespace ImageToGBAHeader
{
	public partial class Form1 : Form
	{

		///General TODO
		/// Maybe put in a button to load palette and sprite instead of it being automatic.
		/// Additional to this. If folder selector or file selector are closed without making a selection of a valid file, The thing breaks.
		/// Add in text boxes to allow user input for Palette Name and TileBitmap Name and possibly an output directory.
		/// Add support for images other than PNG
		/// 
		/// 
		/// 
		/// 
		/// 
		///





		string[,] bgPaletteArray = new string[16,16];

		List<Bitmap> sprites = new List<Bitmap>();
		FileInfo[] spriteFiles;

		string paletteOutput;
		string spriteOutput;

		public Form1()
		{
			InitializeComponent();
		}

		private void buttonOpenPalette_Click(object sender, EventArgs e)
		{
			OpenFileDialog openFileDialog1 = new OpenFileDialog();

			DialogResult result = openFileDialog1.ShowDialog(); // Show the dialog.
			if (result == DialogResult.OK) // Test result.
			{
				textPaletteFile.Text = openFileDialog1.FileName;
				LoadPalette();
			}
		}

		private void buttonOpenFolder_Click(object sender, EventArgs e)
		{
			//TODO Do Not Allow all of this code to run unless bgPaletteArray is loaded Properly.
			FolderBrowserDialog openFolderDialog1 = new FolderBrowserDialog();

			DialogResult result = openFolderDialog1.ShowDialog(); // Show the dialog.
			if (result == DialogResult.OK) // Test result.
			{
				textSpriteFolder.Text = openFolderDialog1.SelectedPath;
			}

			DirectoryInfo dinfo = new DirectoryInfo(textSpriteFolder.Text);
			spriteFiles = dinfo.GetFiles("*.png");
			foreach (FileInfo file in spriteFiles)
			{
				sprites.Add(new Bitmap(textSpriteFolder.Text + "\\" + file.Name));
			}

			if (sprites.Count > 0)
			{
				picboxSprite.Image = sprites[0];
				buttonContinue.Visible = true;
			}
		}

		private void buttonContinue_Click(object sender, EventArgs e)
		{
			spriteOutput = "const unsigned char Bitmap[] = {\n\n";

			for (int i = 0; i < sprites.Count; i++)
			{
				int curSpritePalette = FindPalette(sprites[i]);//TODO Bug Find Palette Not Working - Was working then just stoped.

				if (curSpritePalette >= 0)
				{
					//There Is a valid Palette
					spriteOutput += "/////////////////////////////////////////////////////////////////////// \n";
					spriteOutput += "// " + spriteFiles[i] + " : " + i.ToString() + " ///////////////////////////////////////////////// \n";
					spriteOutput += BitmapToHexString(sprites[i], 0);//TODO 0 changed to curSpritePalette When Find Palette works

				}
			}
			spriteOutput += "};";

			textPaletteOut.Text = spriteOutput;

			//TODO Output -> paletteOutput & spriteOutput to a .c with a new line inbetween them both.
		}

		void LoadPalette()
		{
			Bitmap bitPalette = new Bitmap(textPaletteFile.Text);
			picboxPalette.Image = bitPalette;

			string strPalette = "";

			strPalette += "const unsigned short int BGPalette[] = {\n";

			for (int y = 0; y < bitPalette.Height; y++)
			{
				for (int x = 0; x < bitPalette.Width; x++)
				{
					strPalette += ColourToHex(bitPalette.GetPixel(x, y));
					strPalette += ", ";
					bgPaletteArray[x, y] = ColourToHex(bitPalette.GetPixel(x, y));
				}
				strPalette += "\n";
			}
			strPalette += "};";

			textPaletteOut.Text = strPalette;
			paletteOutput = strPalette;
		}

		//COnverts Color(.net) to hex(0xFFFF)
		string ColourToHex(Color col)
		{
			int red = col.R;
			int green = col.G;
			int blue = col.B;

			int hex = (((31 * (red + 4)) / 255) << 11) | (((63 * (green + 2)) / 255) << 5) | ((31 * (blue + 4)) / 255);

			return String.Format("0x{0:X4}", hex);
		}

		string BitmapToHexString(Bitmap bt, int pal)
		{
			string temp = "";

			for (int i = 0; i < bt.Height; i += 8)
			{
				for (int j = 0; j < bt.Width; j += 8)
				{
					temp += "// Tile " + (j / 8).ToString() + "," + (i / 8).ToString() + "\n";
					for (int y = 0; y < 8; y ++)
					{
						for (int x = 0; x < 8; x += 2)
						{
							// Create single entry for 2 pixels 0x00
							string a = ColourToHex(bt.GetPixel(j + x,i + y));
							string b = ColourToHex(bt.GetPixel(j + x + 1, i + y));

							int first = CheckPalForMatch(pal, a);
							int second = CheckPalForMatch(pal, b);

							int hex = second << 4 | first;

							temp +=  String.Format("0x{0:X2}", hex);

							temp += ", ";

						}
						temp += "\n";
					}
					temp += "\n";
				}
			}
			return temp;
		}


		/// <summary>
		/// Loops through all of the paletts that were loaded and checks the image to find the corrisponding palette
		/// Will return the palette if all pixels are acounted for
		/// Will return -1 if a valid palette is not found to hold all pixels.
		/// </summary>
		int FindPalette(Bitmap bt)
		{
			//TODO Fix - Was not working - Returning -1 on control test.
			int pal = 0;

			for (int y = 0; y < bt.Height; y++)
			{
				for (int x = 0; x < bt.Width; x++)
				{
					if (CheckPalForMatch(pal, ColourToHex(bt.GetPixel(x,y))) >= 0)
					{
						pal++;
						y = 0;
						x = 0;

						if (pal > 15)
						{
							Console.WriteLine("Error, Palette Not Found");
							textPaletteOut.Text = "Error, Palette Not Found";
							return -1;
						}
					}
				}
			}

			Console.WriteLine("Palette Found: " + pal.ToString());
			textPaletteOut.Text = "Palette Found: " + pal.ToString();
			return pal;
		}


		/// <summary>
		/// Looks through the given pallet and returns the index of the matching string.
		/// </summary>
		int CheckPalForMatch(int palette, string check)
		{
			for (int i = 0; i < 16; i++)
			{
				string tempCheck = bgPaletteArray[i, palette];
				if (check == tempCheck)
				{
					return i;
				}
			}
			return -1;
		}
	}


	//TODO - can see a problem when the alpha channel is low and the user mistakenly has colour not in the palette. not sure where to fix.



}
