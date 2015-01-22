//
//  RTCAudioSinkAdapter.m
//  sources_for_indexing
//
//  Created by Ken Kuan on 1/22/15.
//
//
#import "webrtc/base/scoped_ptr.h"

#import "RTCAudioSinkAdapter.h"

namespace webrtc {
    
class RTCAudioSinkNativeAdapter: public AudioTrackSinkInterface {
public:
    RTCAudioSinkNativeAdapter(RTCAudioSinkAdapter *adapter) {
        _adapter = adapter;
    }
    
    virtual void OnData(const void* audio_data,
                        int bits_per_sample,
                        int sample_rate,
                        int number_of_channels,
                        int number_of_frames) {
        [_adapter.audioSink onData:audio_data bitsPerSample:bits_per_sample sampleRate:sample_rate numberOfChannels:number_of_channels numberOfFrames:number_of_frames];
    }
    
private:
    __weak RTCAudioSinkAdapter *_adapter;
};
    
}

@implementation RTCAudioSinkAdapter {
    id<RTCAudioSink> _audioSink;
    rtc::scoped_ptr<webrtc::RTCAudioSinkNativeAdapter> _adapter;
}

- (instancetype)initWithAudioSink:(id<RTCAudioSink>)audioSink {
    if (self = [super init]) {
        _audioSink = audioSink;
        _adapter.reset(new webrtc::RTCAudioSinkNativeAdapter(self));
    }
    return self;
}

- (webrtc::AudioTrackSinkInterface *)nativeAudioSink {
    return _adapter.get();
}

@end
