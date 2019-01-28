
#include "XAudioPlay.h"
#include <QAudioOutput>
#include <QThread>
#include <QMutex>

XAudioPlay::XAudioPlay()
{
}


XAudioPlay::~XAudioPlay()
{
}

class CXAudioPlay : public XAudioPlay
{
public:
	QAudioOutput *output = NULL;
	QIODevice *io = NULL;
	QMutex mutex;

	void Stop()
	{
		mutex.lock();
		if (output)
		{
			output->stop();
			delete output;
			output = NULL;
			io = NULL;
		}
		mutex.unlock();
	}

	bool Start()
	{
		Stop();
		mutex.lock();
		QAudioFormat fmt;
		fmt.setSampleRate(this->sampleRate);
		fmt.setSampleSize(this->sampleSize);
		fmt.setChannelCount(this->channel);
		fmt.setCodec("audio/pcm");
		fmt.setByteOrder(QAudioFormat::LittleEndian);
		fmt.setSampleType(QAudioFormat::UnSignedInt);
		output = new QAudioOutput(fmt);
		io = output->start();
		mutex.unlock();
		return true;
	}

	void Play(bool isplay)
	{
		mutex.lock();
		if (!output)
		{
			mutex.unlock();
			return;
		}
		if (isplay)
		{
			output->resume();
		}
		else
		{
			output->suspend();
		}
		mutex.unlock();
	}

	virtual int GetFree()
	{
		mutex.lock();
		if (!output)
		{
			mutex.unlock();
			return 0;
		}
		int free = output->bytesFree();
		mutex.unlock();
		return free;
	}

	bool Write(const char *data, int datasize)
	{
		if (!data || datasize <= 0)
			return false;
		mutex.lock();
		if (io)
			io->write(data, datasize);
		mutex.unlock();
		return true;
	}
};

XAudioPlay *XAudioPlay::Get()
{
    static CXAudioPlay ap;
    return &ap;
}
