//
//  MHSUATPBufferMessage.m
//  Multihop
//
//  Created by quarta on 31/05/15.
//  Copyright (c) 2015 quarta. All rights reserved.
//


#import "MHSUATPBufferMessage.h"

@interface MHSUATPBufferMessage ()

@end

@implementation MHSUATPBufferMessage

- (instancetype)initWithMessage:(MHMessage *)message
                  withTraceInfo:(NSArray *)traceInfo
{
    self = [super init];
    if (self)
    {
        self.message = message;
        self.traceInfo = traceInfo;
    }
    return self;
}


@end