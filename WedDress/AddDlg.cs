using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Data.OleDb;



namespace WedDress
{
	public partial class AddDlg : Form
	{
		public AddDlg()
		{
			InitializeComponent();
		}

		private void btnSelect_Click( object sender, EventArgs e )
		{
			if( dlgSelImg.ShowDialog() == DialogResult.OK )
			{
				try
				{
					pbPhoto.Load( dlgSelImg.FileName );
				}
				catch( Exception )
				{
					pbPhoto.Image = pbPhoto.ErrorImage;
				}
				txtPath.Text = dlgSelImg.FileName;
			}
		}

		private void AddForm_Load( object sender, EventArgs e )
		{
			if( Program.UserType == UserType.Admin )
			{
				labelBuyDate.Visible = dtBuy.Visible = true;
				labelBuyPrice.Visible = txtBuyPrice.Visible = true;
				labelBuyer.Visible = cbBuyer.Visible = true;
			}
			Program.FillComboBox( "����", cbDept );
			Program.FillComboBox( "����", cbArea );
			Program.FillComboBox( "���", cbCategory );
			Program.FillComboBox( "��ɫ", cbColor );
			Program.FillComboBox( "����", cbProducer );
			Program.FillComboBox( "������", cbBuyer );
			pbPhoto.Image = pbPhoto.InitialImage;
		}

		private void btnAdd_Click( object sender, EventArgs e )
		{
			float price = 0, buyprice = 0;
			if( (txtPrice.Text.Length > 0 && !float.TryParse( txtPrice.Text, out price )) ||
				(txtBuyPrice.Text.Length> 0 && !float.TryParse( txtBuyPrice.Text, out buyprice )) )
			{
				MessageBox.Show( "�۸��������, �����", Program.AppTitle, MessageBoxButtons.OK, MessageBoxIcon.Hand );
				return;
			}

			OleDbCommand cmd = new OleDbCommand();
			cmd.CommandText = "insert into [WedDress](��Ƭ,����,����,���,�����,��ɫ,�ۼ�,���,����,���̺�,�뵵����,���Ͽ���,��������1,��������1,��������2,��������2,��������3,��������3,��������,����,������) "
			+ "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
			cmd.CommandType = CommandType.Text;
			cmd.Connection = Program.Database;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = txtPath.Text;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = cbDept.Text;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = cbArea.Text;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = cbCategory.Text;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = txtAreaNo.Text;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = cbColor.Text;
			cmd.Parameters.Add( "", OleDbType.Currency ).Value = price;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = txtAsessory.Text;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = cbProducer.Text;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = txtProducerNo.Text;
			cmd.Parameters.Add( "", OleDbType.Date ).Value = dtArchive.Value;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = txtArchiveNo.Text;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = txtReq1.Text;
			cmd.Parameters.Add( "", OleDbType.Date ).Value = dtReq1.Value;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = txtReq2.Text;
			cmd.Parameters.Add( "", OleDbType.Date ).Value = dtReq2.Value;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = txtReq3.Text;
			cmd.Parameters.Add( "", OleDbType.Date ).Value = dtReq3.Value;
			cmd.Parameters.Add( "", OleDbType.Date ).Value = dtBuy.Value;
			cmd.Parameters.Add( "", OleDbType.Currency ).Value = buyprice;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = cbBuyer.Text;
			cmd.ExecuteNonQuery();
			cmd.Dispose();

			this.DialogResult = DialogResult.OK;
			this.Close();
		}
	}
}