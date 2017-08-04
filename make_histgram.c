void make_histgram(Mat frame) {
	Mat hsv_frame;

	int hist_x, hist_y;
	cvtColor(frame, hsv_frame, CV_BGR2HSV);
	vector<Mat> channels(3);
	split(hsv_frame, channels);
	int h, s, v;
	int h_hist[256], s_hist[256], v_hist[256];

	for (int k = 0; k < 256; k++) {
		h_hist[k] = 0;
		s_hist[k] = 0;
		v_hist[k] = 0;
	}
	for (hist_y = 0; hist_y < hsv_frame.rows; hist_y++) {
		for (hist_x = 0; hist_x < hsv_frame.cols; hist_x++) {
			h = channels[0].at<uchar>(hist_y, hist_x);
			s = channels[1].at<uchar>(hist_y, hist_x);
			v = channels[2].at<uchar>(hist_y, hist_x);
			h_hist[h]++;
			s_hist[s]++;
			v_hist[v]++;
		}
	}

	int h_hist_max = 0, s_hist_max = 0, v_hist_max = 0;
	for (int k = 0; k < 256; k++) {
		if (h_hist[k] > h_hist_max) {
			h_hist_max = h_hist[k];
		}
		if (s_hist[k] > s_hist_max) {
			s_hist_max = s_hist[k];
		}
		if (v_hist[k] > v_hist_max) {
			v_hist_max = v_hist[k];
		}
	}

	float h_histf[256], s_histf[256], v_histf[256];
	for (int k = 0; k < 256; k++) {
		h_histf[k] = h_hist[k] / (float)h_hist_max;
		s_histf[k] = s_hist[k] / (float)s_hist_max;
		v_histf[k] = v_hist[k] / (float)v_hist_max;
	}

	Mat hist_image = Mat(Size(276, 320), CV_8UC3, Scalar(255, 255, 255));
	for (int k = 0; k < 3; k++) {
		rectangle(hist_image, Point(10, 20 + 100 * k), Point(265, 100 + 100 * k), Scalar(220, 220, 220), -1);
	}
	for (int k = 0; k < 256; k++) {
		line(hist_image, Point(10 + k, 100), Point(10 + k, 100 - (int)(h_histf[k] * 80)), Scalar(0, 0, 255), 1, 8, 0);
		line(hist_image, Point(10 + k, 200), Point(10 + k, 200 - (int)(s_histf[k] * 80)), Scalar(0, 255, 0), 1, 8, 0);
		line(hist_image, Point(10 + k, 300), Point(10 + k, 300 - (int)(v_histf[k] * 80)), Scalar(128, 128, 128), 1, 8, 0);
	}

	imshow("histgram", hist_image);
}
