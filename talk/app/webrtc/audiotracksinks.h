//
//  audiotracksinks.h
//  sources_for_indexing
//
//  Created by Ken Kuan on 1/22/15.
//
//

#ifndef __sources_for_indexing__audiotracksinks__
#define __sources_for_indexing__audiotracksinks__

#include "talk/app/webrtc/mediastreaminterface.h"
#include "talk/media/base/audiorenderer.h"

namespace webrtc {

class AudioTrackSinks : public cricket::AudioRenderer {
 public:
  AudioTrackSinks();
  ~AudioTrackSinks();

  // Callback to receive data from the AudioRenderer.
  virtual void OnData(const void* audio_data,
                      int bits_per_sample,
                      int sample_rate,
                      int number_of_channels,
                      int number_of_frames);
  
  // Called when the AudioRenderer is going away.
  virtual void OnClose();
  
  void AddSink(AudioTrackSinkInterface* sink);
  void RemoveSink(AudioTrackSinkInterface* sink);
  void SetEnabled(bool enable);

 private:
  struct SinkObserver {
    explicit SinkObserver(AudioTrackSinkInterface* sink)
        : sink_(sink) { }
    AudioTrackSinkInterface* sink_;
  };

  bool enabled_;
  std::vector<SinkObserver> sinks_;

  rtc::CriticalSection critical_section_;  // Protects the above variables
};

}  // namespace webrtc

#endif /* defined(__sources_for_indexing__audiotracksinks__) */
