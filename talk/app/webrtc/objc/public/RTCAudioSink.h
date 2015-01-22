//
//  RTCAudioSink.h
//  sources_for_indexing
//
//  Created by Ken Kuan on 1/22/15.
//
//
#import <Foundation/Foundation.h>

@protocol RTCAudioSink <NSObject>

- (void)onData:(const void*)data bitsPerSample:(int)bitsPerSample sampleRate:(int)sampleRate numberOfChannels:(int)numberOfChannels numberOfFrames:(int)numberOfFrames;

@end
