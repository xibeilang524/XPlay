
#ifndef XFFMPEG
#define XFFMPEG

extern "C"
{
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}

#include <string>
#include <QMutex>

class XFFmpeg
{
public:
	static XFFmpeg *Get()
	{
		static XFFmpeg ff;
		return &ff;
	}
	////////////////////////////////////////////////////////
	///打开视频文件，如果上次已经打开会先关闭
	///@para path 视频文件路径
	///@return int return total ms
	int Open(const char *path);
	void Close();

	///返回值需要用户清理
	AVPacket Read();

	int GetPts(const AVPacket *pkt);

	//return pts
	int Decode(const AVPacket *pkt);

	bool ToRGB( char *out, int outwidth, int outheight);
	int ToPCM(char *out);
	//pos 0~1
	bool Seek(float pos);

	std::string GetError();
	virtual ~XFFmpeg();
	int totalMs = 0;
	int fps = 0;
	int pts = 0;
	int videoStream = 0;
	bool isPlay = false;
	int audioStream = 1;
	int sampleRate = 48000;
	int sampleSize = 16;
	int channel = 2;

protected:
	char errorbuf[1024];
	AVFormatContext *ic = NULL;
	AVFrame *yuv = NULL;
	AVFrame *pcm = NULL;
	SwsContext *cCtx = NULL;
	SwrContext *aCtx = NULL;
	QMutex mutex;
	XFFmpeg();
};

#endif

