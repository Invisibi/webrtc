//
//  RTCAudioSinkAdapter.h
//  sources_for_indexing
//
//  Created by Ken Kuan on 1/22/15.
//
//

#import "RTCAudioSink.h"

#include "talk/app/webrtc/mediastreaminterface.h"

@interface RTCAudioSinkAdapter : NSObject

@property(nonatomic, readonly) id<RTCAudioSink> audioSink;
@property(nonatomic, readonly)
    webrtc::AudioTrackSinkInterface* nativeAudioSink;

- (instancetype)initWithAudioSink:(id<RTCAudioSink>)audioSink;

@end
