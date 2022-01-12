using AForge.Video;
using AForge.Video.DirectShow;
using System;
using System.Drawing;
using System.Threading;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Media.Imaging;

namespace WpfApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        FilterInfoCollection filterInfoCollection;
        VideoCaptureDevice videoCaptureDevice1;
        VideoCaptureDevice videoCaptureDevice2;
        VideoCaptureDevice videoCaptureDevice3;
        public MainWindow()
        {
            InitializeComponent();

            filterInfoCollection = new FilterInfoCollection(FilterCategory.VideoInputDevice);
            if (filterInfoCollection.Count > 0)
            {
                videoCaptureDevice1 = new VideoCaptureDevice(filterInfoCollection[0].MonikerString);
                videoCaptureDevice1.NewFrame += VideoCaptureDevice_NewFrame1;
                videoCaptureDevice1.Start();
            }
            if (filterInfoCollection.Count > 1)
            {
                videoCaptureDevice2 = new VideoCaptureDevice(filterInfoCollection[1].MonikerString);
                videoCaptureDevice2.NewFrame += VideoCaptureDevice_NewFrame2;
                videoCaptureDevice2.Start();
            }
            if (filterInfoCollection.Count > 2)
            {
                videoCaptureDevice3 = new VideoCaptureDevice(filterInfoCollection[2].MonikerString);
                videoCaptureDevice3.NewFrame += VideoCaptureDevice_NewFrame3;
                videoCaptureDevice3.Start();
            }
        }

        private void VideoCaptureDevice_NewFrame1(object sender, NewFrameEventArgs eventArgs)
        {
            Dispatcher.BeginInvoke(new ThreadStart(delegate {
                pic1.Source = Imaging.CreateBitmapSourceFromHBitmap(
                     (eventArgs.Frame.Clone() as Bitmap).GetHbitmap(),
                     IntPtr.Zero,
                     Int32Rect.Empty,
                     BitmapSizeOptions.FromEmptyOptions());
            }));
        }

        private void VideoCaptureDevice_NewFrame2(object sender, NewFrameEventArgs eventArgs)
        {
            //Dispatcher.BeginInvoke(new ThreadStart(delegate {
            //    pic2.Source = Imaging.CreateBitmapSourceFromHBitmap(
            //         (eventArgs.Frame.Clone() as Bitmap).GetHbitmap(),
            //         IntPtr.Zero,
            //         Int32Rect.Empty,
            //         BitmapSizeOptions.FromEmptyOptions());
            //}));
        }

        private void VideoCaptureDevice_NewFrame3(object sender, NewFrameEventArgs eventArgs)
        {
            //Dispatcher.BeginInvoke(new ThreadStart(delegate {
            //    pic3.Source = Imaging.CreateBitmapSourceFromHBitmap(
            //         (eventArgs.Frame.Clone() as Bitmap).GetHbitmap(),
            //         IntPtr.Zero,
            //         Int32Rect.Empty,
            //         BitmapSizeOptions.FromEmptyOptions());
            //}));
        }

    }
}
