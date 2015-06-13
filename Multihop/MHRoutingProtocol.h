//
//  MHRoutingProtocol.h
//  Multihop
//
//  Created by quarta on 01/06/15.
//  Copyright (c) 2015 quarta. All rights reserved.
//

#ifndef Multihop_MHRoutingProtocol_h
#define Multihop_MHRoutingProtocol_h


#import <Foundation/Foundation.h>
#import "MHConnectionsHandler.h"
#import "MHPacket.h"

// Diagnostics
#import "MHDiagnostics.h"



@protocol MHRoutingProtocolDelegate;

@interface MHRoutingProtocol : NSObject

#pragma mark - Properties

@property(nonatomic, weak) id<MHRoutingProtocolDelegate> delegate;


#pragma mark - Initialization
- (instancetype)initWithServiceType:(NSString *)serviceType
                        displayName:(NSString *)displayName;

- (NSString *)getOwnPeer;


- (void)applicationWillResignActive;

- (void)applicationDidBecomeActive;


#pragma mark - Overridable methods
- (void)disconnect;

- (void)joinGroup:(NSString *)groupName;

- (void)leaveGroup:(NSString *)groupName;

- (void)sendPacket:(MHPacket *)packet
             error:(NSError **)error;

- (int)hopsCountFromPeer:(NSString*)peer;

@end


@protocol MHRoutingProtocolDelegate <NSObject>

@required
- (void)mhProtocol:(MHRoutingProtocol *)mhProtocol
   failedToConnect:(NSError *)error;

- (void)mhProtocol:(MHRoutingProtocol *)mhProtocol
  didReceivePacket:(MHPacket *)packet
     withTraceInfo:(NSArray *)traceInfo;

- (void)mhProtocol:(MHRoutingProtocol *)mhProtocol
      isDiscovered:(NSString *)info
              peer:(NSString *)peer
       displayName:(NSString *)displayName;


#pragma mark - Diagnostics info callbacks
- (void)mhProtocol:(MHRoutingProtocol *)mhProtocol
     forwardPacket:(NSString *)info
        withPacket:(MHPacket *)packet;

- (void)mhProtocol:(MHRoutingProtocol *)mhProtocol
neighbourConnected:(NSString *)info
              peer:(NSString *)peer
       displayName:(NSString *)displayName;

- (void)mhProtocol:(MHRoutingProtocol *)mhProtocol
neighbourDisconnected:(NSString *)info
              peer:(NSString *)peer;

- (void)mhProtocol:(MHRoutingProtocol *)mhProtocol
       joinedGroup:(NSString *)info
              peer:(NSString *)peer
             group:(NSString *)group;
@end


#endif
