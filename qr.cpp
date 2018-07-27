#include <math.h>
#include <iostream>
#include <unistd.h>


#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "zxing/MultiFormatReader.h"
#include "zxing/BinaryBitmap.h"
#include "zxing/LuminanceSource.h"
#include "zxing/Binarizer.h"
#include "zxing/qrcode/QRCodeReader.h"
#include "zxing/Reader.h"
#include "zxing/MatSource.h"
#include "zxing/common/GlobalHistogramBinarizer.h"
#include "zxing/DecodeHints.h"

int main(int argc, char *argv[])
{
    cv::VideoCapture cap;
    //cap.open(argv[1]);
    //std::cout << "打开文件路径为:" << argv[1] << "\n";
    cap.open(0);

    double rate = cap.get(CV_CAP_PROP_FPS);
    //for(int i = 0; i < 10; i++)
    //{
    //    sleep(1);
    //    std::cout << "已延迟" << i+1 << "秒...\n";
    //}
    if(!cap.isOpened())
    {
        return -1;
    }

    cv::Mat edges;
    cv::namedWindow("视频显示窗口", 0);

    while(1)
    {
        cv::Mat frame;
        cap >> frame;
        edges = frame;
        //cv::cvtColor(frame, edges, CV_BGR2GRAY);
        //cv::threshold(edges, edges, 120, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

        cv::imshow("视频显示窗口", edges);

        if(cv::waitKey(30) >= 0)
            break;
    }

#if (0)
    cv::Mat matSrc = cv::imread(argv[1]);
    std::cout << "Open file path: " << argv[1] << "\n";

    cv::Mat matGray;
    cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);
    zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
    int width = source->getWidth();
    int height = source->getHeight();
    std::cout 
        << "Image width: " << width << "\n"
        << "Image Heigth: " << height << "\n";
    
    zxing::Ref<zxing::Reader> reader;
    reader.reset(new zxing::qrcode::QRCodeReader);
    
    zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
    zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
    zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::QR_CODE_HINT)));
    std::cout << "================result is==================\n";
    std::cout << result->getText()->getText() << "\n";
#endif
	return 0;
}


