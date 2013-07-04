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
	public partial class ModifyDlg : Form
	{
		private DataRow m_row;


		public ModifyDlg()
		{
			InitializeComponent();
		}


		public void SetRow( DataRow row )
		{
			m_row = row;

			try
			{
				string path = (string)row["��Ƭ"];
				txtPath.Text = path;
				if( path.Length > 0 )
					pbPhoto.Load( path );
				else
					pbPhoto.Image = pbPhoto.InitialImage;
			}
			catch( Exception )
			{
				pbPhoto.Image = pbPhoto.ErrorImage;
			}

			cbDept.Text = (string)row["����"];
			cbArea.Text = (string)row["����"];
			cbCategory.Text = (string)row["���"];
			txtAreaNo.Text = (string)row["�����"];
			cbColor.Text = (string)row["��ɫ"];
			txtPrice.Text = row["�ۼ�"].ToString();
			txtAsessory.Text = (string)row["���"];

			cbProducer.Text = (string)row["����"];
			txtProducerNo.Text = (string)row["���̺�"];
			dtArchive.Value = (DateTime)row["�뵵����"];
			txtArchiveNo.Text = (string)row["���Ͽ���"];

			txtReq1.Text = (string)row["��������1"];
			dtReq1.Value = (DateTime)row["��������1"];
			txtReq2.Text = (string)row["��������2"];
			dtReq2.Value = (DateTime)row["��������2"];
			txtReq3.Text = (string)row["��������3"];
			dtReq3.Value = (DateTime)row["��������3"];

			dtBuy.Value = (DateTime)row["��������"];
			txtBuyPrice.Text = row["����"].ToString();
			cbBuyer.Text = row["������"].ToString();

		}


		private void btnModify_Click( object sender, EventArgs e )
		{
			float price = 0, buyprice = 0;
			if( (txtPrice.Text.Length > 0 && !float.TryParse( txtPrice.Text, out price )) ||
				(txtBuyPrice.Text.Length > 0 && !float.TryParse( txtBuyPrice.Text, out buyprice )) )
			{
				MessageBox.Show( "�۸��������, �����", Program.AppTitle, MessageBoxButtons.OK, MessageBoxIcon.Hand );
				return;
			}

			OleDbCommand cmd = new OleDbCommand();
			cmd.CommandText =
				"update [WedDress] set ��Ƭ=?,����=?,����=?,���=?,�����=?,��ɫ=?,�ۼ�=?,���=?,����=?,���̺�=?,�뵵����=?,���Ͽ���=?,��������1=?,��������1=?,��������2=?,��������2=?,��������3=?,��������3=?,��������=?,����=?,������=?"
			+ " where [id]=?";
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
			cmd.Parameters.Add( "", OleDbType.Integer ).Value = (int)m_row["ID"];
			cmd.ExecuteNonQuery();
			cmd.Dispose();



			m_row["��Ƭ"] = txtPath.Text;
			m_row["����"] =cbDept.Text;
			m_row["����"] = cbArea.Text;
			m_row["���"]=cbCategory.Text;
			m_row["�����"]=txtAreaNo.Text;
			m_row["��ɫ"]=cbColor.Text;
			m_row["�ۼ�"] = price;
			m_row["���"]=txtAsessory.Text;

			m_row["����"]=cbProducer.Text;
			m_row["���̺�"]=txtProducerNo.Text;
			m_row["�뵵����"] = dtArchive.Value;
			m_row["���Ͽ���"]=txtArchiveNo.Text;

			m_row["��������1"]=txtReq1.Text;
			m_row["��������1"]=dtReq1.Value;
			m_row["��������2"]=txtReq2.Text;
			m_row["��������2"] = dtReq2.Value;
			m_row["��������3"]=txtReq3.Text;
			m_row["��������3"] = dtReq3.Value;

			m_row["��������"] = dtBuy.Value;
			m_row["����"] = buyprice;
			m_row["������"] = cbBuyer.Text;


			this.DialogResult = DialogResult.OK;
			this.Close();
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

		private void ModifyDlg_Load( object sender, EventArgs e )
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
		}

	}
}