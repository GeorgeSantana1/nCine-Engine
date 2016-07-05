#include <cstdlib> // for exit()
#define NCINE_INCLUDE_OPENAL
#include "common_headers.h"

#include "AudioStream.h"
#include "IAudioLoader.h"
#include "ServiceLocator.h"
#include "Array.h"

namespace ncine {

///////////////////////////////////////////////////////////
// CONSTRUCTORS and DESTRUCTOR
///////////////////////////////////////////////////////////

/// Constructor creating an audio stream from an audio file
/*! Private constructor called only by AudioStreamPlayer */
AudioStream::AudioStream(const char *filename)
	: nextAvailALBuffer_(0), frequency_(0)
{
	alGenBuffers(NumBuffers, alBuffers_.data());
	memBuffer_ = new char[BufferSize];

	audioLoader_ = IAudioLoader::createFromFile(filename);
	frequency_ = audioLoader_->frequency();
	int numhannels = audioLoader_->numChannels();

	if (numhannels == 1)
	{
		format_ = AL_FORMAT_MONO16;
	}
	else if (numhannels == 2)
	{
		format_ = AL_FORMAT_STEREO16;
	}
	else
	{
		LOGF_X("Unsupported number of channels: %d", numhannels);
		exit(EXIT_FAILURE);
	}
}

AudioStream::~AudioStream()
{
	delete audioLoader_;
	delete[] memBuffer_;
	alDeleteBuffers(NumBuffers, alBuffers_.data());
}

///////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
///////////////////////////////////////////////////////////

/// Enqueues new buffers and unqueues processed ones
/*! /return A flag indicating whether the stream has been entirely decoded and played or not */
bool AudioStream::enqueue(unsigned int source, bool looping)
{
	// Set to false when the queue is empty and there is no more data to decode
	bool shouldKeepPlaying = true;

	ALint numProcessedBuffers;
	alGetSourcei(source, AL_BUFFERS_PROCESSED, &numProcessedBuffers);

	// Unqueueing
	while (numProcessedBuffers > 0)
	{
		ALuint unqueuedAlBuffer;
		alSourceUnqueueBuffers(source, 1, &unqueuedAlBuffer);
		nextAvailALBuffer_--;
		alBuffers_[nextAvailALBuffer_] = unqueuedAlBuffer;
		numProcessedBuffers--;
	}


	// Queueing
	if (nextAvailALBuffer_ < NumBuffers)
	{
		ALuint currentBuffer = alBuffers_[nextAvailALBuffer_];

		long bytes = audioLoader_->read(memBuffer_, BufferSize);

		// EOF reached
		if (bytes < BufferSize)
		{
			if (looping)
			{
				audioLoader_->rewind();
				long moreBytes = audioLoader_->read(memBuffer_ + bytes, BufferSize - bytes);
				bytes += moreBytes;
			}
		}

		// If still decoding data then enqueue
		if (bytes > 0)
		{
			// On iOS alBufferDataStatic could be used instead
			alBufferData(currentBuffer, format_, memBuffer_, bytes, frequency_);
			alSourceQueueBuffers(source, 1, &currentBuffer);
			nextAvailALBuffer_++;
		}
		// If it has no more data to decode and the queue is empty
		else if (nextAvailALBuffer_ == 0)
		{
			shouldKeepPlaying = false;
			stop(source);
		}
	}


	ALenum state;
	alGetSourcei(source, AL_SOURCE_STATE, &state);

	// Handle buffer underrun case
	if (state != AL_PLAYING)
	{
		ALint numQueuedBuffers = 0;
		alGetSourcei(source, AL_BUFFERS_QUEUED, &numQueuedBuffers);
		if (numQueuedBuffers > 0)
		{
			// Need to restart play
			alSourcePlay(source);
		}
	}

	return shouldKeepPlaying;
}

/// Unqueues any left buffer and rewinds the loader
void AudioStream::stop(unsigned int source)
{
	// In order to unqueue all the buffers, the source must be stopped first
	alSourceStop(source);

	ALint numProcessedBuffers;
	alGetSourcei(source, AL_BUFFERS_PROCESSED, &numProcessedBuffers);

	// Unqueueing
	while (numProcessedBuffers > 0)
	{
		ALuint uuqueuedAlBuffer;
		alSourceUnqueueBuffers(source, 1, &uuqueuedAlBuffer);
		nextAvailALBuffer_--;
		alBuffers_[nextAvailALBuffer_] = uuqueuedAlBuffer;
		numProcessedBuffers--;
	}

	audioLoader_->rewind();
}

}