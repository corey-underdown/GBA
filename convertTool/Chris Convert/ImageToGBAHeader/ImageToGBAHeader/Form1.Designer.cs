namespace ImageToGBAHeader
{
	public class PBOverride : System.Windows.Forms.PictureBox
	{
		public System.Drawing.Drawing2D.InterpolationMode InterpolationMode { get; set; }

		protected override void OnPaint(System.Windows.Forms.PaintEventArgs paintEventArgs)
		{
			paintEventArgs.Graphics.InterpolationMode = InterpolationMode;
			base.OnPaint(paintEventArgs);
		}
	}

	partial class Form1
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.label1 = new System.Windows.Forms.Label();
			this.textPaletteFile = new System.Windows.Forms.TextBox();
			this.buttonOpenPalette = new System.Windows.Forms.Button();
			this.textPaletteOut = new System.Windows.Forms.RichTextBox();
			this.buttonOpenFolder = new System.Windows.Forms.Button();
			this.textSpriteFolder = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.buttonContinue = new System.Windows.Forms.Button();
			this.button_save = new System.Windows.Forms.Button();
			this.picboxSprite = new ImageToGBAHeader.PBOverride();
			this.picboxPalette = new ImageToGBAHeader.PBOverride();
			((System.ComponentModel.ISupportInitialize)(this.picboxSprite)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.picboxPalette)).BeginInit();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(13, 13);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(40, 13);
			this.label1.TabIndex = 0;
			this.label1.Text = "Palette";
			// 
			// textPaletteFile
			// 
			this.textPaletteFile.Location = new System.Drawing.Point(54, 10);
			this.textPaletteFile.Name = "textPaletteFile";
			this.textPaletteFile.Size = new System.Drawing.Size(148, 20);
			this.textPaletteFile.TabIndex = 1;
			// 
			// buttonOpenPalette
			// 
			this.buttonOpenPalette.Location = new System.Drawing.Point(208, 10);
			this.buttonOpenPalette.Name = "buttonOpenPalette";
			this.buttonOpenPalette.Size = new System.Drawing.Size(29, 20);
			this.buttonOpenPalette.TabIndex = 2;
			this.buttonOpenPalette.Text = "...";
			this.buttonOpenPalette.UseVisualStyleBackColor = true;
			this.buttonOpenPalette.Click += new System.EventHandler(this.buttonOpenPalette_Click);
			// 
			// textPaletteOut
			// 
			this.textPaletteOut.Location = new System.Drawing.Point(12, 185);
			this.textPaletteOut.Name = "textPaletteOut";
			this.textPaletteOut.Size = new System.Drawing.Size(985, 362);
			this.textPaletteOut.TabIndex = 5;
			this.textPaletteOut.Text = "";
			// 
			// buttonOpenFolder
			// 
			this.buttonOpenFolder.Location = new System.Drawing.Point(485, 10);
			this.buttonOpenFolder.Name = "buttonOpenFolder";
			this.buttonOpenFolder.Size = new System.Drawing.Size(29, 20);
			this.buttonOpenFolder.TabIndex = 8;
			this.buttonOpenFolder.Text = "...";
			this.buttonOpenFolder.UseVisualStyleBackColor = true;
			this.buttonOpenFolder.Click += new System.EventHandler(this.buttonOpenFolder_Click);
			// 
			// textSpriteFolder
			// 
			this.textSpriteFolder.Location = new System.Drawing.Point(331, 10);
			this.textSpriteFolder.Name = "textSpriteFolder";
			this.textSpriteFolder.Size = new System.Drawing.Size(148, 20);
			this.textSpriteFolder.TabIndex = 7;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(290, 13);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(34, 13);
			this.label2.TabIndex = 6;
			this.label2.Text = "Sprite";
			// 
			// buttonContinue
			// 
			this.buttonContinue.Location = new System.Drawing.Point(496, 94);
			this.buttonContinue.Name = "buttonContinue";
			this.buttonContinue.Size = new System.Drawing.Size(141, 47);
			this.buttonContinue.TabIndex = 10;
			this.buttonContinue.Text = "Continue";
			this.buttonContinue.UseVisualStyleBackColor = true;
			this.buttonContinue.Visible = false;
			this.buttonContinue.Click += new System.EventHandler(this.buttonContinue_Click);
			// 
			// button_save
			// 
			this.button_save.Enabled = false;
			this.button_save.Location = new System.Drawing.Point(867, 134);
			this.button_save.Name = "button_save";
			this.button_save.Size = new System.Drawing.Size(130, 45);
			this.button_save.TabIndex = 11;
			this.button_save.Text = "Save To File";
			this.button_save.UseVisualStyleBackColor = true;
			this.button_save.Click += new System.EventHandler(this.button1_Click);
			// 
			// picboxSprite
			// 
			this.picboxSprite.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
			this.picboxSprite.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
			this.picboxSprite.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
			this.picboxSprite.Location = new System.Drawing.Point(341, 43);
			this.picboxSprite.Margin = new System.Windows.Forms.Padding(10, 10, 0, 0);
			this.picboxSprite.Name = "picboxSprite";
			this.picboxSprite.Size = new System.Drawing.Size(128, 128);
			this.picboxSprite.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.picboxSprite.TabIndex = 9;
			this.picboxSprite.TabStop = false;
			// 
			// picboxPalette
			// 
			this.picboxPalette.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
			this.picboxPalette.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
			this.picboxPalette.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
			this.picboxPalette.Location = new System.Drawing.Point(63, 46);
			this.picboxPalette.Margin = new System.Windows.Forms.Padding(10, 10, 0, 0);
			this.picboxPalette.Name = "picboxPalette";
			this.picboxPalette.Size = new System.Drawing.Size(128, 128);
			this.picboxPalette.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.picboxPalette.TabIndex = 3;
			this.picboxPalette.TabStop = false;
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1009, 559);
			this.Controls.Add(this.button_save);
			this.Controls.Add(this.buttonContinue);
			this.Controls.Add(this.picboxSprite);
			this.Controls.Add(this.buttonOpenFolder);
			this.Controls.Add(this.textSpriteFolder);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.textPaletteOut);
			this.Controls.Add(this.picboxPalette);
			this.Controls.Add(this.buttonOpenPalette);
			this.Controls.Add(this.textPaletteFile);
			this.Controls.Add(this.label1);
			this.Name = "Form1";
			this.Text = "Form1";
			((System.ComponentModel.ISupportInitialize)(this.picboxSprite)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.picboxPalette)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox textPaletteFile;
		private System.Windows.Forms.Button buttonOpenPalette;
		private PBOverride picboxPalette;
		private System.Windows.Forms.RichTextBox textPaletteOut;
		private System.Windows.Forms.Button buttonOpenFolder;
		private System.Windows.Forms.TextBox textSpriteFolder;
		private System.Windows.Forms.Label label2;
		private PBOverride picboxSprite;
		private System.Windows.Forms.Button buttonContinue;
		private System.Windows.Forms.Button button_save;
	}
}

