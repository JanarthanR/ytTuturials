﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace calcTest
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            MouseDown += Window_MouseDown;
        }

        private void Window_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Left)
                this.DragMove();

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {

            string content = (sender as Button).Content.ToString();
            if (content != "=")
            {
                numberTextBox.Text += content;
            }
            else {
                numberTextBox.Text = CalculationPerformer.calculate(numberTextBox.Text).ToString();
            }
            

           
        }

        private void closeCalculator(object sender, MouseEventArgs args)
        {
            System.Windows.Application.Current.Shutdown();
        }
    }
}