/*
 * libjingle
 * Copyright 2013, Google Inc.
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

#if !defined(__has_feature) || !__has_feature(objc_arc)
#error "This file requires ARC support."
#endif

#import "RTCAudioTrack+Internal.h"

#import "RTCMediaStreamTrack+Internal.h"

#import "RTCAudioSinkAdapter.h"

@implementation RTCAudioTrack {
    NSMutableArray *_adapters;
}

- (id)initWithMediaTrack:(rtc::scoped_refptr<webrtc::MediaStreamTrackInterface>)mediaTrack {
    if (self = [super initWithMediaTrack:mediaTrack]) {
        _adapters = [NSMutableArray array];
    }
    return self;
}

- (void)dealloc {
    for (RTCAudioSinkAdapter *adapter in _adapters) {
        self.audioTrack->RemoveSink(adapter.nativeAudioSink);
    }
}

- (void)addSink:(id<RTCAudioSink>)sink {
    for (RTCAudioSinkAdapter *adapter in _adapters) {
        NSParameterAssert(adapter.audioSink != sink);
    }
    
    RTCAudioSinkAdapter *adapter = [[RTCAudioSinkAdapter alloc] initWithAudioSink:sink];
    [_adapters addObject:adapter];
    self.audioTrack->AddSink(adapter.nativeAudioSink);
}

- (void)removeSink:(id<RTCAudioSink>)sink {
    RTCAudioSinkAdapter *adapter = nil;
    NSUInteger indexToRemove = NSNotFound;
    for (NSUInteger i = 0; i < _adapters.count; i++) {
        adapter = _adapters[i];
        if (adapter.audioSink == sink) {
            indexToRemove = i;
            break;
        }
    }
    if (indexToRemove == NSNotFound) {
        return;
    }
    self.audioTrack->RemoveSink(adapter.nativeAudioSink);
    [_adapters removeObjectAtIndex:indexToRemove];
}

- (void)startMonitor:(int)cms {
  self.audioTrack->StartMonitor(cms);
}

- (void)stopMonitor {
  self.audioTrack->StopMonitor();
}

- (int)inputLevel {
  return self.audioTrack->GetInputLevel();
}

- (int)outputLevel {
  return self.audioTrack->GetOutputLevel();
}

- (bool)hasActiveStreams {
  return self.audioTrack->HasActiveStreams();
}

@end

@implementation RTCAudioTrack (Internal)

- (rtc::scoped_refptr<webrtc::AudioTrackInterface>)audioTrack {
  return static_cast<webrtc::AudioTrackInterface*>(self.mediaTrack.get());
}

@end
