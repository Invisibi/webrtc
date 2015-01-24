/*
 * libjingle
 * Copyright 2011, Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TALK_APP_WEBRTC_AUDIOTRACK_H_
#define TALK_APP_WEBRTC_AUDIOTRACK_H_

#include "talk/app/webrtc/mediastreaminterface.h"
#include "talk/app/webrtc/mediastreamtrack.h"
#include "talk/app/webrtc/notifier.h"
#include "webrtc/base/scoped_ptr.h"
#include "webrtc/base/scoped_ref_ptr.h"

namespace cricket {
  
class VoiceChannel;
  
}

namespace webrtc {

class AudioTrack : public MediaStreamTrack<AudioTrackInterface> {
 public:
  static rtc::scoped_refptr<AudioTrack> Create(
      const std::string& id, AudioSourceInterface* source);

  // AudioTrackInterface implementation.
  virtual AudioSourceInterface* GetSource() const OVERRIDE {
    return audio_source_.get();
  }
  // TODO(xians): Implement these methods.
  virtual void AddSink(AudioTrackSinkInterface* sink) OVERRIDE {}
  virtual void RemoveSink(AudioTrackSinkInterface* sink) OVERRIDE {}
  virtual bool GetSignalLevel(int* level) OVERRIDE { return false; }
  virtual void SetVoiceChannel(cricket::VoiceChannel *voice_channel);
  virtual rtc::scoped_refptr<AudioProcessorInterface> GetAudioProcessor()
      OVERRIDE { return NULL; }
  virtual cricket::AudioRenderer* GetRenderer() OVERRIDE {
    return NULL;
  }

int GetInputLevel();

int GetOutputLevel();

bool HasActiveStreams();

  // MediaStreamTrack implementation.
  virtual std::string kind() const OVERRIDE;

 protected:
  AudioTrack(const std::string& label, AudioSourceInterface* audio_source);

 private:
  cricket::VoiceChannel* voice_channel_;
  rtc::scoped_refptr<AudioSourceInterface> audio_source_;
};

}  // namespace webrtc

#endif  // TALK_APP_WEBRTC_AUDIOTRACK_H_
