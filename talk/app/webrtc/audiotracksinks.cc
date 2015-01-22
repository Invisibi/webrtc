//
//  audiotracksinks.cpp
//  sources_for_indexing
//
//  Created by Ken Kuan on 1/22/15.
//
//

#include "talk/app/webrtc/audiotracksinks.h"

namespace webrtc {
  
  AudioTrackSinks::AudioTrackSinks()
  : enabled_(true) {
    
  }
  
  AudioTrackSinks::~AudioTrackSinks() {
  }
  
  void AudioTrackSinks::AddSink(AudioTrackSinkInterface *sink) {
    rtc::CritScope cs(&critical_section_);
    std::vector<SinkObserver>::iterator it =  sinks_.begin();
    for (; it != sinks_.end(); ++it) {
      if (it->sink_ == sink)
        return;
    }
    sinks_.push_back(SinkObserver(sink));
  }
  
  void AudioTrackSinks::RemoveSink(AudioTrackSinkInterface* sink) {
    rtc::CritScope cs(&critical_section_);
    std::vector<SinkObserver>::iterator it =  sinks_.begin();
    for (; it != sinks_.end(); ++it) {
      if (it->sink_ == sink) {
        sinks_.erase(it);
        return;
      }
    }
  }
  
  void AudioTrackSinks::SetEnabled(bool enable) {
    rtc::CritScope cs(&critical_section_);
    enabled_ = enable;
  }
  
  // Callback to receive data from the AudioRenderer.
  void AudioTrackSinks::OnData(const void* audio_data,
                               int bits_per_sample,
                               int sample_rate,
                               int number_of_channels,
                               int number_of_frames) {
    rtc::CritScope cs(&critical_section_);
    if (!enabled_) {
      return;
    }
    std::vector<SinkObserver>::iterator it = sinks_.begin();
    for (; it != sinks_.end(); ++it) {
      it->sink_->OnData(audio_data, bits_per_sample, sample_rate, number_of_channels, number_of_frames);
    }
  }
  
  // Called when the AudioRenderer is going away.
  void AudioTrackSinks::OnClose() {
    
  }
  
}  // namespace webrtc
